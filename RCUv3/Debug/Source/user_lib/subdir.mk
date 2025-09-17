################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/user_lib/PCA9555.c \
../Source/user_lib/queue.c 

OBJS += \
./Source/user_lib/PCA9555.o \
./Source/user_lib/queue.o 

C_DEPS += \
./Source/user_lib/PCA9555.d \
./Source/user_lib/queue.d 


# Each subdirectory must supply rules for building sources it contributes
Source/user_lib/%.o Source/user_lib/%.su Source/user_lib/%.cyclo: ../Source/user_lib/%.c Source/user_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32G0B0RETx -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G0B0xx -DSTM32 -DSTM32G0 -c -I../Source -I../Source/user_lib -I../Ethernet -I../Ethernet/W5500 -I../modbusTCP -I../modbusTCP/inc -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source-2f-user_lib

clean-Source-2f-user_lib:
	-$(RM) ./Source/user_lib/PCA9555.cyclo ./Source/user_lib/PCA9555.d ./Source/user_lib/PCA9555.o ./Source/user_lib/PCA9555.su ./Source/user_lib/queue.cyclo ./Source/user_lib/queue.d ./Source/user_lib/queue.o ./Source/user_lib/queue.su

.PHONY: clean-Source-2f-user_lib

