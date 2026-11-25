// SPDX-License-Identifier: Apache-2.0

#include <stdlib.h>

#include "esp_cam_sensor_detect.h"
#include "esp_check.h"
#include "esp_sccb_intf.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gc0328.h"
#include "gc0328_settings.h"

#define GC0328_SCCB_ADDR 0x21
#define GC0328_REG_PAGE 0xfe
#define GC0328_REG_CHIP_ID 0xf0
#define GC0328_REG_PAD_OUTPUT 0xf1
#define GC0328_REG_PIXEL_OUTPUT 0xf2
#define GC0328_REG_FORMAT 0x44

static const char *TAG = "gc0328";

const esp_cam_sensor_format_t esp_vision_gc0328_format = {
    .name = "DVP_8bit_YUYV_320x240",
    .format = ESP_CAM_SENSOR_PIXFORMAT_YUV422_YUYV,
    .port = ESP_CAM_SENSOR_DVP,
    .width = 320,
    .height = 240,
    .fps = 16,
    .regs = gc0328_default_regs,
    .regs_size = sizeof(gc0328_default_regs) / sizeof(gc0328_default_regs[0]),
};

static esp_err_t gc0328_write_table(esp_sccb_io_handle_t sccb,
                                    const uint8_t (*regs)[2], size_t count)
{
    for (size_t i = 0; i < count; i++) {
        if (regs[i][0] == GC0328_REG_DELAY) {
            vTaskDelay(pdMS_TO_TICKS(regs[i][1]));
            continue;
        }
        esp_err_t ret = esp_sccb_transmit_reg_a8v8(sccb, regs[i][0], regs[i][1]);
        ESP_RETURN_ON_ERROR(ret, TAG, "write register 0x%02x", regs[i][0]);
    }
    return ESP_OK;
}

static esp_err_t gc0328_read_id(esp_sccb_io_handle_t sccb, uint8_t *pid)
{
    esp_err_t ret = esp_sccb_transmit_reg_a8v8(sccb, GC0328_REG_PAGE, 0);
    if (ret != ESP_OK) {
        return ret;
    }
    return esp_sccb_transmit_receive_reg_a8v8(sccb, GC0328_REG_CHIP_ID, pid);
}

static esp_err_t gc0328_set_stream(esp_cam_sensor_device_t *dev, bool enable)
{
    const uint8_t registers[][2] = {
        {GC0328_REG_PAGE, 0},
        {GC0328_REG_PAD_OUTPUT, enable ? 0x07 : 0},
        {GC0328_REG_PIXEL_OUTPUT, enable ? 0x01 : 0},
    };
    esp_err_t ret = gc0328_write_table(dev->sccb_handle, registers,
                                      sizeof(registers) / sizeof(registers[0]));
    if (ret == ESP_OK) {
        dev->stream_status = enable;
    }
    return ret;
}

static esp_err_t gc0328_set_format(esp_cam_sensor_device_t *dev,
                                   const esp_cam_sensor_format_t *format)
{
    if (format != NULL && (format->format != esp_vision_gc0328_format.format ||
                           format->port != ESP_CAM_SENSOR_DVP ||
                           format->width != esp_vision_gc0328_format.width ||
                           format->height != esp_vision_gc0328_format.height)) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    if (dev->stream_status) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_sccb_io_handle_t sccb = dev->sccb_handle;
    esp_err_t ret = esp_sccb_transmit_reg_a8v8(sccb, GC0328_REG_PAGE, 0xf0);
    ESP_RETURN_ON_ERROR(ret, TAG, "reset sensor");
    vTaskDelay(pdMS_TO_TICKS(80));

    ret = gc0328_write_table(sccb, gc0328_default_regs, esp_vision_gc0328_format.regs_size);
    ESP_RETURN_ON_ERROR(ret, TAG, "load sensor defaults");
    vTaskDelay(pdMS_TO_TICKS(80));

    ret = gc0328_set_stream(dev, false);
    ESP_RETURN_ON_ERROR(ret, TAG, "disable output during format setup");
    ret = gc0328_write_table(sccb, gc0328_qvga_regs,
                             sizeof(gc0328_qvga_regs) / sizeof(gc0328_qvga_regs[0]));
    ESP_RETURN_ON_ERROR(ret, TAG, "configure QVGA subsampling");
    ret = esp_sccb_transmit_reg_a8v8(sccb, GC0328_REG_FORMAT, 0x22);
    ESP_RETURN_ON_ERROR(ret, TAG, "configure YUYV output");
    dev->cur_format = &esp_vision_gc0328_format;
    return ESP_OK;
}

static esp_err_t gc0328_get_format(esp_cam_sensor_device_t *dev,
                                   esp_cam_sensor_format_t *format)
{
    *format = *dev->cur_format;
    return ESP_OK;
}

static esp_err_t gc0328_query_formats(esp_cam_sensor_device_t *dev,
                                      esp_cam_sensor_format_array_t *formats)
{
    (void)dev;
    formats->count = 1;
    formats->format_array = &esp_vision_gc0328_format;
    return ESP_OK;
}

static esp_err_t gc0328_query_capability(esp_cam_sensor_device_t *dev,
                                         esp_cam_sensor_capability_t *capability)
{
    (void)dev;
    *capability = (esp_cam_sensor_capability_t){.fmt_yuv = 1};
    return ESP_OK;
}

static esp_err_t gc0328_ioctl(esp_cam_sensor_device_t *dev, uint32_t cmd, void *arg)
{
    switch (cmd) {
    case ESP_CAM_SENSOR_IOC_S_STREAM:
        return gc0328_set_stream(dev, *(const int *)arg != 0);
    case ESP_CAM_SENSOR_IOC_G_CHIP_ID:
        *(esp_cam_sensor_id_t *)arg = dev->id;
        return ESP_OK;
    default:
        return ESP_ERR_NOT_SUPPORTED;
    }
}

static esp_err_t gc0328_delete(esp_cam_sensor_device_t *dev)
{
    esp_err_t ret = dev->stream_status ? gc0328_set_stream(dev, false) : ESP_OK;
    free(dev);
    return ret;
}

static const esp_cam_sensor_ops_t gc0328_ops = {
    .query_support_formats = gc0328_query_formats,
    .query_support_capability = gc0328_query_capability,
    .set_format = gc0328_set_format,
    .get_format = gc0328_get_format,
    .priv_ioctl = gc0328_ioctl,
    .del = gc0328_delete,
};

ESP_CAM_SENSOR_DETECT_FN(esp_vision_gc0328, ESP_CAM_SENSOR_DVP, GC0328_SCCB_ADDR)
{
    const esp_cam_sensor_config_t *sensor_config = config;
    uint8_t pid;
    if (gc0328_read_id(sensor_config->sccb_handle, &pid) != ESP_OK ||
            pid != ESP_VISION_GC0328_PID) {
        return NULL;
    }

    esp_cam_sensor_device_t *dev = calloc(1, sizeof(*dev));
    if (dev == NULL) {
        return NULL;
    }
    dev->name = "GC0328";
    dev->sccb_handle = sensor_config->sccb_handle;
    dev->sensor_port = ESP_CAM_SENSOR_DVP;
    dev->xclk_pin = sensor_config->xclk_pin;
    dev->reset_pin = sensor_config->reset_pin;
    dev->pwdn_pin = sensor_config->pwdn_pin;
    dev->ops = &gc0328_ops;
    dev->cur_format = &esp_vision_gc0328_format;
    dev->id.pid = pid;
    ESP_LOGI(TAG, "Detected GC0328 PID=0x%02x", pid);
    return dev;
}
