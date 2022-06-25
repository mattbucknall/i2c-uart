add_executable(${CMAKE_PROJECT_NAME}
        main.c
)

include("${CMAKE_SOURCE_DIR}/cmake/avrdude.cmake")
avrdude(${CMAKE_PROJECT_NAME} ${PROG_DONGLE} ${PROG_INTERFACE} ${PROG_TARGET})
