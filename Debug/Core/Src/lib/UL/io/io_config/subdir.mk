################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/lib/UL/io/io_config/io_config.c 

OBJS += \
./Core/Src/lib/UL/io/io_config/io_config.o 

C_DEPS += \
./Core/Src/lib/UL/io/io_config/io_config.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lib/UL/io/io_config/io_config.o: ../Core/Src/lib/UL/io/io_config/io_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yevhen.surkov/Documents/STM_WORKPLACE/led_blink/Core/Src" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/lib/UL/io/io_config/io_config.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

