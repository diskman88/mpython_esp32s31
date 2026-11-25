# SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
#
# SPDX-License-Identifier: Apache-2.0

if(NOT DEFINED ESP_VISION_IDF_OVERLAY)
    set(ESP_VISION_IDF_OVERLAY "unknown")
endif()

if(NOT ESP_VISION_IDF_OVERLAY STREQUAL "release6.1")
    message(FATAL_ERROR
        "ESP32_S31_KORVO is supported only with ESP-IDF release/v6.1. "
        "Current overlay: ${ESP_VISION_IDF_OVERLAY}. "
        "Source an ESP-IDF release/v6.1 environment before building this board."
    )
endif()

set(ESP_VISION_USE_BOARD_MANAGER ON)

# The board enables these devices in its defaults. Link their components
# even if the manager evaluates the upstream conditional deps before Kconfig.
idf_component_get_property(ledong_board_manager espressif__esp_board_manager COMPONENT_LIB)
target_link_libraries(${ledong_board_manager} PRIVATE
    idf::espressif__esp_lcd_panel_io_additions
    idf::espressif__esp_lcd_touch
)

set(ESP_VISION_BOARD_MANAGER_SETUP_SOURCES
    "${ESP_VISION_BOARD_DIR}/bmgr/setup_device.c"
    "${ESP_VISION_BOARD_DIR}/sensors/gc0328/gc0328.c"
)
