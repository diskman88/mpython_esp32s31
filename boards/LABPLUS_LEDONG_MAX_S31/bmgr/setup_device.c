/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>

#include "driver/gpio.h"
#include "dev_display_lcd.h"
#include "esp_board_manager.h"
#include "esp_board_manager_defs.h"
#include "esp_lcd_st7102.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch_st7123.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "st7102_init_cmds.h"

esp_err_t lcd_touch_factory_entry_t(esp_lcd_panel_io_handle_t io,
                                    const esp_lcd_touch_config_t *touch_config,
                                    esp_lcd_touch_handle_t *touch_handle)
{
    return esp_lcd_touch_new_i2c_st7123(io, touch_config, touch_handle);
}

esp_err_t lcd_panel_factory_entry_t(esp_lcd_panel_io_handle_t io,
                                    const esp_lcd_panel_dev_config_t *panel_config,
                                    esp_lcd_panel_handle_t *panel_handle)
{
    void *device_config = NULL;
    esp_err_t ret = esp_board_manager_get_device_config(ESP_BOARD_DEVICE_NAME_DISPLAY_LCD,
                                                       &device_config);
    if (ret != ESP_OK) {
        return ret;
    }

    const dev_display_lcd_config_t *lcd_config = device_config;
    const gpio_num_t reset = panel_config->reset_gpio_num;
    if (reset < 0 || reset >= GPIO_NUM_MAX) {
        return ESP_ERR_INVALID_ARG;
    }
    const gpio_config_t reset_config = {
        .pin_bit_mask = 1ULL << reset,
        .mode = GPIO_MODE_OUTPUT,
    };
    ret = gpio_config(&reset_config);
    if (ret != ESP_OK) {
        return ret;
    }
    ret = gpio_set_level(reset, 1);
    if (ret == ESP_OK) {
        vTaskDelay(pdMS_TO_TICKS(500));
        ret = gpio_set_level(reset, 0);
    }
    if (ret == ESP_OK) {
        vTaskDelay(pdMS_TO_TICKS(100));
        ret = gpio_set_level(reset, 1);
    }
    if (ret == ESP_OK) {
        vTaskDelay(pdMS_TO_TICKS(600));
    }
    esp_err_t release_ret = gpio_reset_pin(reset);
    if (ret != ESP_OK || release_ret != ESP_OK) {
        return ret != ESP_OK ? ret : release_ret;
    }

    st7102_vendor_config_t vendor_config = {
        .init_cmds = ledong_st7102_init_cmds,
        .init_cmds_size = sizeof(ledong_st7102_init_cmds) / sizeof(ledong_st7102_init_cmds[0]),
        .rgb_config = &lcd_config->sub_cfg.rgb_3wire_spi.rgb_panel_config,
        .flags.use_rgb_interface = 1,
    };
    esp_lcd_panel_dev_config_t config = *panel_config;
    config.vendor_config = &vendor_config;
    // The external pull-up holds reset inactive after the board-specific pulse.
    config.reset_gpio_num = -1;

    ret = esp_lcd_new_panel_st7102(io, &config, panel_handle);
    if (ret != ESP_OK) {
        return ret;
    }
    const int rgb_gpios[] = {16, 17, 18, 19, 0, 1, 2, 3, 4, 5,
                             6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    for (size_t i = 0; i < sizeof(rgb_gpios) / sizeof(rgb_gpios[0]); i++) {
        ret = gpio_set_drive_capability(rgb_gpios[i], GPIO_DRIVE_CAP_3);
        if (ret != ESP_OK) {
            esp_lcd_panel_del(*panel_handle);
            *panel_handle = NULL;
            return ret;
        }
    }
    return ESP_OK;
}
