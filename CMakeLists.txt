# Toolchain must come before first project
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake
  CACHE FILEPATH "CMake ARM GCC toolchain file" FORCE
)

cmake_minimum_required(VERSION 3.15)
project(stm32_spinner_project)
enable_language(C ASM)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

# Build type
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# set location of project
set(PRJ_DIR ${CMAKE_SOURCE_DIR}/lib/STM32Cube_FW_F4_V1.25.1)

# set startup file
set(STARTUP ${PRJ_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s)
message (STATUS "[DBG]: ${STARTUP}")

# set system file for Controller
set(SYSTEM ${PRJ_DIR}/Projects/STM32F4-Discovery/Examples/GPIO/GPIO_EXTI/Src/system_stm32f4xx.c)

# set paths
set(HAL_PATH ${PRJ_DIR}/Drivers/STM32F4xx_HAL_Driver)
set(CMSIS_PATH ${PRJ_DIR}/Drivers/CMSIS)
set(BSP_PATH ${PRJ_DIR}/Drivers/BSP)
set(FREE_RTOS_PATH ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source)
    

#add_executable(stm32_spinner_project-2 Core/Src/main.c)

# set CMSIS files needed for the project
set(CMSIS_SRCS  
  ${CMSIS_PATH}/Device/ST/STM32F4xx/Include/stm32f4xx.h
  ${CMSIS_PATH}/Device/ST/STM32F4xx/Include/stm32f407xx.h
  ${CMSIS_PATH}/Core/Include/cmsis_gcc.h
  ${CMSIS_PATH}/Core/Include/cmsis_armcc.h
  ${CMSIS_PATH}/Core/Include/cmsis_compiler.h
  ${CMSIS_PATH}/Core/Include/cmsis_version.h
  ${CMSIS_PATH}/Core/Include/core_cm4.h
  ${CMSIS_PATH}/Core/Include/mpu_armv7.h
)

# set HAL files needed for the project
set(HAL_SRCS
  ${HAL_PATH}/Src/stm32f4xx_hal_pwr.c
  ${HAL_PATH}/Src/stm32f4xx_hal_cortex.c
  ${HAL_PATH}/Src/stm32f4xx_hal_gpio.c
  ${HAL_PATH}/Src/stm32f4xx_hal_flash.c
  ${HAL_PATH}/Src/stm32f4xx_hal_spi.c
  ${HAL_PATH}/Src/stm32f4xx_hal_rcc.c
  ${HAL_PATH}/Src/stm32f4xx_hal_flash_ex.c
  ${HAL_PATH}/Src/stm32f4xx_hal_rcc_ex.c
  ${HAL_PATH}/Src/stm32f4xx_hal_i2c.c
  ${HAL_PATH}/Src/stm32f4xx_hal.c
  ${HAL_PATH}/Src/stm32f4xx_hal_pwr_ex.c
  ${HAL_PATH}/Src/stm32f4xx_hal_dma.c
  ${HAL_PATH}/Src/stm32f4xx_hal_i2c_ex.c
  ${HAL_PATH}/Src/stm32f4xx_hal_uart.c
)

# set BSP files needed for the project
SET (BSP_SRCS
  ${BSP_PATH}/STM32F4-Discovery/stm32f4_discovery.c
  ${BSP_PATH}/STM32F4-Discovery/stm32f4_discovery.h
)
message (STATUS "[DBG]: ${BSP_SRCS}")

# set Application files needed for the project
SET (APP_SRCS
${CMAKE_SOURCE_DIR}/Core/Src/freertos.c
${CMAKE_SOURCE_DIR}/Core/Src/main.c
${CMAKE_SOURCE_DIR}/Core/Src/stm32f4xx_it.c
${CMAKE_SOURCE_DIR}/Core/Src/system_stm32f4xx.c
${CMAKE_SOURCE_DIR}/Core/Src/stm32f4xx_hal_msp.c
${CMAKE_SOURCE_DIR}/Core/Src/syscalls.c
${CMAKE_SOURCE_DIR}/Core/Src/sysmem.c
${CMAKE_SOURCE_DIR}/Core/Inc/FreeRTOSConfig.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/drivers/uart/uart.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/drivers/uart/uart.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/drivers/led/led.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/drivers/led/led.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/drivers/button/button.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/drivers/button/button.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/utils/queue.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/utils/queue.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/spinner/spinner.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/spinner/spinner.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/button_controler/button_controler.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/button_controler/button_controler.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_config/io_config.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_config/io_config.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_package_convertor/io_package_convertor.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_package_convertor/io_package_convertor.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_generic/io_generic.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_generic/io_generic.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_uart/io_uart.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_uart/io_uart.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_spi/io_spi.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_spi/io_spi.c
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_i2c/io_i2c.h
${CMAKE_SOURCE_DIR}/Core/Src/lib/UL/io/io_i2c/io_i2c.c
)

# set FreeRtos files needed for the project
SET (FREE_RTOS_SRCS
${FREE_RTOS_PATH}/CMSIS_RTOS_V2/cmsis_os.h
${FREE_RTOS_PATH}/CMSIS_RTOS_V2/cmsis_os2.h
${FREE_RTOS_PATH}/CMSIS_RTOS_V2/cmsis_os2.c
${FREE_RTOS_PATH}/portable/GCC/ARM_CM4F/portmacro.h
${FREE_RTOS_PATH}/portable/GCC/ARM_CM4F/port.c
${FREE_RTOS_PATH}/portable/MemMang/heap_4.c
${FREE_RTOS_PATH}/croutine.c
${FREE_RTOS_PATH}/event_groups.c
${FREE_RTOS_PATH}/list.c
${FREE_RTOS_PATH}/queue.c
${FREE_RTOS_PATH}/stream_buffer.c
${FREE_RTOS_PATH}/tasks.c
${FREE_RTOS_PATH}/timers.c
)

SET(INCLUDE_DIRS 
${CMAKE_SOURCE_DIR}/Core/Inc/
${HAL_PATH}/Inc/
${FREE_RTOS_PATH}/Include/
)

message (STATUS "[DBG]: ${APP_SRCS}")

set(EXECUTABLE ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${INCLUDE_DIRS} ${APP_SRCS} ${HAL_SRCS} ${CMSIS_SRCS} ${BSP_SRCS} ${FREE_RTOS_SRCS} ${STARTUP} ${SOURCE_ESP})

#add target device
target_compile_definitions(${PROJECT_NAME} PRIVATE
  -DSTM32F407x32
  $<$<CONFIG:Debug>: -DDEBUG>
)

# include directories for the project
include_directories (
  ${CMSIS_PATH}/Device/ST/STM32F4xx/Source/Templates/gcc
  ${CMAKE_SOURCE_DIR}/Core/Src
  ${CMAKE_SOURCE_DIR}/Core/Inc
  ${BSP_PATH}/STM32F4-Discovery
  ${HAL_PATH}/Src
  ${HAL_PATH}/Inc
  ${HAL_PATH}/Inc/Legacy
  ${CMSIS_PATH}/Core/Include
  ${CMSIS_PATH}/Device/ST/STM32F4xx/Include
  ${FREE_RTOS_PATH}/Include/
  ${FREE_RTOS_PATH}/CMSIS_RTOS_V2/
  ${FREE_RTOS_PATH}/portable/GCC/ARM_CM4F/
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  C_STANDARD ${CMAKE_C_STANDARD}

  if(CMAKE_C_STANDARD_REQUIRED)
    C_STANDARD_REQUIRED YES
  else()
    C_STANDARD_REQUIRED NO
  endif()

  if(CMAKE_C_EXTENSIONS)
    C_EXTENSIONS YES
  else()
    C_EXTENSIONS NO
  endif()
  
)

#add settings for target device
target_compile_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m4
  -mthumb
  -mfloat-abi=hard
  -DSTM32F407xx
  -fdata-sections
  -ffunction-sections
  -Wall
  -Winline
  -fstack-usage

  --specs=nano.specs
  --specs=nosys.specs

  $<$<CONFIG:Debug>: -Og>
  $<$<CONFIG:Release>: -Os>
)

target_link_options(${PROJECT_NAME} PRIVATE
  -T${CMAKE_SOURCE_DIR}/STM32F407VGTX_FLASH.ld
  -mcpu=cortex-m4
  -mthumb
  -mfloat-abi=hard
  -u _printf_float

  --specs=nano.specs
  --specs=nosys.specs

  -Wl,-Map=${EXECUTABLE}.map,--cref
  -Wl,--gc-sections
  -static
  -Wl,--start-group -lc -lm -Wl,--end-group
)


# configure assembler due to the startup file, which is an assembler file
set_source_files_properties(${STARTUP} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")
set_property(SOURCE ${STARTUP} PROPERTY LANGUAGE C)

# Summerize all sources
SET(USER_SOURCES ${STARTUP} ${SYSTEM} ${CMSIS_SRCS} ${HAL_SRCS} ${BSP_SRCS} ${APP_SRCS} ${LINKER_SCRIPT})
message(STATUS "[DBG]: ${USER_SOURCES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${TARGET}.map")

# create possibility to create a *.bin file
add_custom_target (${TARGET}.bin DEPENDS ${TARGET}.elf COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET}.elf ${TARGET}.bin)

# create possibility to create a *.list file
add_custom_target (${TARGET}.lst DEPENDS ${TARGET}.elf COMMAND ${CMAKE_OBJDUMP} -Sdh ${TARGET}.elf > ${TARGET}.lst)

# Print executable size
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND arm-none-eabi-size ${EXECUTABLE}${CMAKE_EXECUTABLE_SUFFIX}
)

# Create hex file
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  #COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE}${CMAKE_EXECUTABLE_SUFFIX} ${EXECUTABLE}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE}${CMAKE_EXECUTABLE_SUFFIX} ${EXECUTABLE}.bin
)