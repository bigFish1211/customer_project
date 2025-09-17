################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/bsp/platform.c 

OBJS += \
./Source/bsp/platform.o 

C_DEPS += \
./Source/bsp/platform.d 


# Each subdirectory must supply rules for building sources it contributes
Source/bsp/%.o Source/bsp/%.su Source/bsp/%.cyclo: ../Source/bsp/%.c Source/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32G0B0RETx -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G0B0xx -DSTM32 -DSTM32G0 -c -I../Source -I../Source/user_lib -I../Ethernet -I../Ethernet/W5500 -I../modbusTCP -I../modbusTCP/inc -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source-2f-bsp

clean-Source-2f-bsp:
	-$(RM) ./Source/bsp/platform.cyclo ./Source/bsp/platform.d ./Source/bsp/platform.o ./Source/bsp/platform.su

.PHONY: clean-Source-2f-bsp

