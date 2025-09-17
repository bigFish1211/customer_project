################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/stm32g0xx_it.c \
../Source/syscalls.c \
../Source/sysmem.c \
../Source/system_stm32g0xx.c 

OBJS += \
./Source/stm32g0xx_it.o \
./Source/syscalls.o \
./Source/sysmem.o \
./Source/system_stm32g0xx.o 

C_DEPS += \
./Source/stm32g0xx_it.d \
./Source/syscalls.d \
./Source/sysmem.d \
./Source/system_stm32g0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o Source/%.su Source/%.cyclo: ../Source/%.c Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G030xx -DSTM32 -DSTM32G0 -DSTM32G030K8Tx -c -I../Source -I../Source/user_lib -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source

clean-Source:
	-$(RM) ./Source/stm32g0xx_it.cyclo ./Source/stm32g0xx_it.d ./Source/stm32g0xx_it.o ./Source/stm32g0xx_it.su ./Source/syscalls.cyclo ./Source/syscalls.d ./Source/syscalls.o ./Source/syscalls.su ./Source/sysmem.cyclo ./Source/sysmem.d ./Source/sysmem.o ./Source/sysmem.su ./Source/system_stm32g0xx.cyclo ./Source/system_stm32g0xx.d ./Source/system_stm32g0xx.o ./Source/system_stm32g0xx.su

.PHONY: clean-Source

