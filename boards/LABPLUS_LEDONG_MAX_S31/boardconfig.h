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
#define ESP_VISION_CAMERA_BUFFER_COUNT              (2)
/* Camera wiring is configured in bmgr/board_devices.yaml. */

/* Display configuration. */
#define ESP_VISION_LCD_WIDTH                        (480)
#define ESP_VISION_LCD_HEIGHT                       (800)
/* LCD wiring and timing are configured in bmgr/board_devices.yaml. */

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
