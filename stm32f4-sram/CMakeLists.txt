cmake_minimum_required(VERSION 3.5)
project(stm32f4 CXX C ASM)

set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_AR arm-none-eabi-ar)

# -DSTM32F407VG
set(COMMON_FLAGS "-DSTM32F40XX -O2 -DUSE_STDPERIPH_DRIVER  -mcpu=cortex-m4    \
    -lc -specs=nosys.specs -mthumb -mthumb-interwork -ffunction-sections   \
    -fdata-sections -g -fno-common -fmessage-length=0 ")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
set(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m4")

include_directories(
        /usr/lib/arm-none-eabi/include
        driver/CMSIS
        driver/STM32F4xx_StdPeriph_Driver/inc
        users/driver
        ../tools
)

file(GLOB_RECURSE SOURCE_FILES
        driver/*.hpp
        driver/*.cpp
        driver/*.c
        driver/*.h
        driver/*.s
        users/*.hpp
        users/*.cpp
        users/*.c
        users/*.h
        ../tools/*.cpp
        ../tools/*.c
        ../tools/*.h
        )

set(LINK_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F407IGHx_FLASH.ld)

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES})

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -T ${LINK_SCRIPT} -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map")
###########################################################

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/build
        COMMENT "Creating build directory")
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}")

add_custom_target(flash
        stm32flash -n 100 -b 460800 -w ${BIN_FILE} /dev/ttyUSB0)

add_custom_target(remoteflash
        cat ${BIN_FILE} | nc 192.168.1.149 8888)

add_custom_target(chmod
        sudo chmod 777 /dev/ttyUSB0)
