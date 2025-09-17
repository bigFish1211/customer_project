################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ethernet/W5500/w5500.c 

OBJS += \
./Ethernet/W5500/w5500.o 

C_DEPS += \
./Ethernet/W5500/w5500.d 


# Each subdirectory must supply rules for building sources it contributes
Ethernet/W5500/%.o Ethernet/W5500/%.su Ethernet/W5500/%.cyclo: ../Ethernet/W5500/%.c Ethernet/W5500/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32G0B0RETx -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G0B0xx -DSTM32 -DSTM32G0 -c -I../Source -I../Source/user_lib -I../Ethernet -I../Ethernet/W5500 -I../modbusTCP -I../modbusTCP/inc -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Ethernet-2f-W5500

clean-Ethernet-2f-W5500:
	-$(RM) ./Ethernet/W5500/w5500.cyclo ./Ethernet/W5500/w5500.d ./Ethernet/W5500/w5500.o ./Ethernet/W5500/w5500.su

.PHONY: clean-Ethernet-2f-W5500

