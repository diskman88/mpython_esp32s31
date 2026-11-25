set(IDF_TARGET esp32s31)

set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/LABPLUS_LEDONG_MAX_S31/sdkconfig.s31_ledong_max
    boards/LABPLUS_LEDONG_MAX_S31/sdkconfig.defaults.board
    boards/LABPLUS_LEDONG_MAX_S31/sdkconfig.board
)

set(MICROPY_PY_BTREE OFF)
