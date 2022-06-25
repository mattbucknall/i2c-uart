add_executable(${CMAKE_PROJECT_NAME}
        app-i2c.c
        app-io.c
        app-led.c
        app-uart.c
        main.c
)

include("${CMAKE_SOURCE_DIR}/cmake/avrdude.cmake")
avrdude(${CMAKE_PROJECT_NAME} ${PROG_DONGLE} ${PROG_INTERFACE} ${PROG_TARGET} ${TARGET_E_FUSE} ${TARGET_H_FUSE} ${TARGET_L_FUSE})
