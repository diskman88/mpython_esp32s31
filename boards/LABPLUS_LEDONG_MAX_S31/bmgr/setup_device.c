/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>

#include "dev_display_lcd.h"
#include "esp_board_manager.h"
#include "esp_board_manager_defs.h"
#include "esp_lcd_st7102.h"
#include "esp_lcd_touch_st7123.h"
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
    st7102_vendor_config_t vendor_config = {
        .init_cmds = ledong_st7102_init_cmds,
        .init_cmds_size = sizeof(ledong_st7102_init_cmds) / sizeof(ledong_st7102_init_cmds[0]),
        .rgb_config = &lcd_config->sub_cfg.rgb_3wire_spi.rgb_panel_config,
        .flags.use_rgb_interface = 1,
    };
    esp_lcd_panel_dev_config_t config = *panel_config;
    config.vendor_config = &vendor_config;

    return esp_lcd_new_panel_st7102(io, &config, panel_handle);
}
