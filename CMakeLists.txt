# Project Configuration
project(i2c-uart NONE)
cmake_minimum_required(VERSION 3.16)

# Build Type
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type specified so defaulting to 'Release'")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# Toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING true)

set(TOOLCHAIN_TUPLE "avr")
set(TOOLCHAIN_INSTALL_DIR "/usr")
set(TOOLCHAIN_BIN_DIR "${TOOLCHAIN_INSTALL_DIR}/bin")

set(CMAKE_C_COMPILER "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_TUPLE}-gcc")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_TUPLE}-gcc")
set(CMAKE_OBJCOPY "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_TUPLE}-objcopy")
set(CMAKE_OBJDUMP "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_TUPLE}-objdump")
set(CMAKE_SIZE "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN_TUPLE}-size")

set(CMAKE_C_COMPILER_WORKS true)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Programming Languages
enable_language(C)

# Target Parameters
set(TARGET_MCU "atmega328p")
set(TARGET_XTAL_FREQ "16000000")
set(TARGET_E_FUSE "0xFC")
set(TARGET_H_FUSE "0xDA")
set(TARGET_L_FUSE "0xFF")

# AVRDUDE Parameters
set(PROG_DONGLE "avrispmkII")
set(PROG_INTERFACE "usb")
set(PROG_TARGET "m328p")

# Toolchain Flags
set(TARGET_DEFINITIONS "-DTARGET_XTAL_FREQ=${TARGET_XTAL_FREQ}")
set(TARGET_OPTIMIZATION_LEVEL "s")
set(TARGET_C_FLAGS "-Wall -std=c11 -gdwarf-2 -fsigned-char -fpack-struct -fshort-enums -funsigned-bitfields -mmcu=${TARGET_MCU}")
set(TARGET_LD_FLAGS "-Wl,--gc-sections")

set(CMAKE_C_FLAGS "${TARGET_DEFINITIONS} ${TARGET_C_FLAGS}")
set(CMAKE_LD_FLAGS "${TARGET_LD_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE "-O${TARGET_OPTIMIZATION_LEVEL} -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-g -Og")

# Project Layout
set(CMAKE_INCLUDE_CURRENT_DIR true)

add_subdirectory(src)
