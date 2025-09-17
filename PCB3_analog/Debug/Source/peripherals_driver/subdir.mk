################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/peripherals_driver/drv_dma.c \
../Source/peripherals_driver/drv_i2c.c \
../Source/peripherals_driver/iwdt.c \
../Source/peripherals_driver/uart.c 

OBJS += \
./Source/peripherals_driver/drv_dma.o \
./Source/peripherals_driver/drv_i2c.o \
./Source/peripherals_driver/iwdt.o \
./Source/peripherals_driver/uart.o 

C_DEPS += \
./Source/peripherals_driver/drv_dma.d \
./Source/peripherals_driver/drv_i2c.d \
./Source/peripherals_driver/iwdt.d \
./Source/peripherals_driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Source/peripherals_driver/%.o Source/peripherals_driver/%.su Source/peripherals_driver/%.cyclo: ../Source/peripherals_driver/%.c Source/peripherals_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G030xx -DSTM32 -DSTM32G0 -DSTM32G030K8Tx -c -I../Source -I../Source/user_lib -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source-2f-peripherals_driver

clean-Source-2f-peripherals_driver:
	-$(RM) ./Source/peripherals_driver/drv_dma.cyclo ./Source/peripherals_driver/drv_dma.d ./Source/peripherals_driver/drv_dma.o ./Source/peripherals_driver/drv_dma.su ./Source/peripherals_driver/drv_i2c.cyclo ./Source/peripherals_driver/drv_i2c.d ./Source/peripherals_driver/drv_i2c.o ./Source/peripherals_driver/drv_i2c.su ./Source/peripherals_driver/iwdt.cyclo ./Source/peripherals_driver/iwdt.d ./Source/peripherals_driver/iwdt.o ./Source/peripherals_driver/iwdt.su ./Source/peripherals_driver/uart.cyclo ./Source/peripherals_driver/uart.d ./Source/peripherals_driver/uart.o ./Source/peripherals_driver/uart.su

.PHONY: clean-Source-2f-peripherals_driver

