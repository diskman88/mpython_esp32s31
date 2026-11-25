/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ESP_VISION_BOARD_CONFIG_H
#define ESP_VISION_BOARD_CONFIG_H

#define ESP_VISION_BOARD_ARCH                  "ESP32S31"
#define ESP_VISION_BOARD_TYPE                  "ESP32_S31_LEDONG_MAX"
#define ESP_VISION_PORT_ESP32                       (1)

#define ESP_VISION_IMLIB_PROFILER_ENABLE            (0)
#define ESP_VISION_IMLIB_GPU_ENABLE                 (0)
#define ESP_VISION_IMLIB_JPEG_CODEC_ENABLE          (0)

#define ESP_VISION_CACHE_LINE_SIZE                  (32)
#define ESP_VISION_ALLOC_ALIGNMENT                  (ESP_VISION_CACHE_LINE_SIZE)
#define ESP_VISION_DMA_ALIGNMENT                    (ESP_VISION_CACHE_LINE_SIZE)

#define ESP_VISION_JPEG_QUALITY_LOW                 (60)
#define ESP_VISION_JPEG_QUALITY_HIGH                (60)
#define ESP_VISION_JPEG_QUALITY_THRESHOLD           (320 * 240 * 2)

/* Camera configuration. */
#define ESP_VISION_CAMERA_RAW_INPUT_WIDTH           (640)
#define ESP_VISION_CAMERA_RAW_INPUT_HEIGHT          (480)
#define ESP_VISION_CAMERA_ACTIVE_INPUT_WIDTH        (640)
#define ESP_VISION_CAMERA_ACTIVE_INPUT_HEIGHT       (480)
#define ESP_VISION_CAMERA_PPA_OUTPUT_QQVGA_WIDTH    (160)
#define ESP_VISION_CAMERA_PPA_OUTPUT_QQVGA_HEIGHT   (120)
#define ESP_VISION_CAMERA_PPA_OUTPUT_QVGA_WIDTH     (320)
#define ESP_VISION_CAMERA_PPA_OUTPUT_QVGA_HEIGHT    (240)
#define ESP_VISION_CAMERA_PPA_OUTPUT_VGA_WIDTH      (640)
#define ESP_VISION_CAMERA_PPA_OUTPUT_VGA_HEIGHT     (480)
#define ESP_VISION_CAMERA_BUFFER_COUNT              (1)
#define ESP_VISION_CAMERA_SCCB_I2C_PORT             (0)
#define ESP_VISION_CAMERA_SCCB_I2C_SCL_PIN          (24)
#define ESP_VISION_CAMERA_SCCB_I2C_SDA_PIN          (25)
#define ESP_VISION_CAMERA_SENSOR_RESET_PIN          (-1)
#define ESP_VISION_CAMERA_SENSOR_PWDN_PIN           (-1)
#define ESP_VISION_CAMERA_SCCB_I2C_FREQ             (100000)
#define ESP_VISION_CAMERA_SCCB_INTERNAL_PULLUP      (1)
#define ESP_VISION_CAMERA_XCLK_PIN                  (-1)
#define ESP_VISION_CAMERA_XCLK_FREQ                 (0)
#define ESP_VISION_CAMERA_XCLK_STABLE_MS            (50)
#define ESP_VISION_CAMERA_XCLK_LEDC_TIMER           (1)
#define ESP_VISION_CAMERA_XCLK_LEDC_CHANNEL         (0)
#define ESP_VISION_CAMERA_DVP_PCLK_PIN              (55)
#define ESP_VISION_CAMERA_DVP_VSYNC_PIN             (50)
#define ESP_VISION_CAMERA_DVP_HSYNC_PIN             (51)
#define ESP_VISION_CAMERA_DVP_D0_PIN                (57)
#define ESP_VISION_CAMERA_DVP_D1_PIN                (59)
#define ESP_VISION_CAMERA_DVP_D2_PIN                (60)
#define ESP_VISION_CAMERA_DVP_D3_PIN                (58)
#define ESP_VISION_CAMERA_DVP_D4_PIN                (56)
#define ESP_VISION_CAMERA_DVP_D5_PIN                (54)
#define ESP_VISION_CAMERA_DVP_D6_PIN                (53)
#define ESP_VISION_CAMERA_DVP_D7_PIN                (52)

/* Display configuration. */
#define ESP_VISION_LCD_WIDTH                        (800)
#define ESP_VISION_LCD_HEIGHT                       (480)
#define ESP_VISION_LCD_BPP                          (16)
#define ESP_VISION_LCD_PIXEL_CLOCK_HZ               (18 * 1000 * 1000)
#define ESP_VISION_LCD_DATA_WIDTH                   (16)
#define ESP_VISION_LCD_HSYNC_PULSE_WIDTH            (1)
#define ESP_VISION_LCD_HSYNC_BACK_PORCH             (40)
#define ESP_VISION_LCD_HSYNC_FRONT_PORCH            (20)
#define ESP_VISION_LCD_VSYNC_PULSE_WIDTH            (1)
#define ESP_VISION_LCD_VSYNC_BACK_PORCH             (10)
#define ESP_VISION_LCD_VSYNC_FRONT_PORCH            (5)
#define ESP_VISION_LCD_PIN_D0                       (0)
#define ESP_VISION_LCD_PIN_D1                       (1)
#define ESP_VISION_LCD_PIN_D2                       (2)
#define ESP_VISION_LCD_PIN_D3                       (3)
#define ESP_VISION_LCD_PIN_D4                       (4)
#define ESP_VISION_LCD_PIN_D5                       (5)
#define ESP_VISION_LCD_PIN_D6                       (6)
#define ESP_VISION_LCD_PIN_D7                       (7)
#define ESP_VISION_LCD_PIN_D8                       (8)
#define ESP_VISION_LCD_PIN_D9                       (9)
#define ESP_VISION_LCD_PIN_D10                      (10)
#define ESP_VISION_LCD_PIN_D11                      (11)
#define ESP_VISION_LCD_PIN_D12                      (12)
#define ESP_VISION_LCD_PIN_D13                      (13)
#define ESP_VISION_LCD_PIN_D14                      (14)
#define ESP_VISION_LCD_PIN_D15                      (15)
#define ESP_VISION_LCD_PIN_PCLK                     (16)
#define ESP_VISION_LCD_PIN_DE                       (17)
#define ESP_VISION_LCD_PIN_HSYNC                    (18)
#define ESP_VISION_LCD_PIN_VSYNC                    (19)
#define ESP_VISION_LCD_PIN_DISP_EN                  (-1)
#define ESP_VISION_LCD_PIN_BL                       (49)

/* SD card configuration. */
#define ESP_VISION_SDCARD_MOUNT_PATH                "/sdcard"
#define ESP_VISION_SDCARD_SLOT                      (0)
#define ESP_VISION_SDCARD_BUS_WIDTH                 (4)
#define ESP_VISION_SDCARD_CLK_PIN                   (24)
#define ESP_VISION_SDCARD_CMD_PIN                   (25)
#define ESP_VISION_SDCARD_D0_PIN                    (20)
#define ESP_VISION_SDCARD_D1_PIN                    (21)
#define ESP_VISION_SDCARD_D2_PIN                    (22)
#define ESP_VISION_SDCARD_D3_PIN                    (23)
#define ESP_VISION_SDCARD_CTRL_PIN                  (39)
#define ESP_VISION_SDCARD_CTRL_ACTIVE_LEVEL         (0)

/* EV-MUX v4 physical defaults and background Wi-Fi/TCP policy.
 * Native/Hosted WLAN is enabled separately in the port/IDF configuration.
 * Factory credentials apply only when no saved NVS profile exists.
 */
#define ESP_VISION_ENABLE_BACKGROUND_NETWORK       (1)
#define ESP_VISION_WIFI_DEFAULT_SSID                ""
#define ESP_VISION_WIFI_DEFAULT_PASSWORD            ""
#define ESP_VISION_TRANSPORT_DEFAULT_SINK          "usb"
#define ESP_VISION_TRANSPORT_FALLBACK_SINK         "usb"
#define ESP_VISION_ENABLE_TCP_TRANSPORT            (1)
#define ESP_VISION_TCP_PORT                        (3232)

#endif /* ESP_VISION_BOARD_CONFIG_H */
