################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/task/handlerIOTask.c \
../Source/task/main.c 

OBJS += \
./Source/task/handlerIOTask.o \
./Source/task/main.o 

C_DEPS += \
./Source/task/handlerIOTask.d \
./Source/task/main.d 


# Each subdirectory must supply rules for building sources it contributes
Source/task/%.o Source/task/%.su Source/task/%.cyclo: ../Source/task/%.c Source/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G030xx -DSTM32 -DSTM32G0 -DSTM32G030K8Tx -c -I../Source -I../Source/user_lib -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Source-2f-task

clean-Source-2f-task:
	-$(RM) ./Source/task/handlerIOTask.cyclo ./Source/task/handlerIOTask.d ./Source/task/handlerIOTask.o ./Source/task/handlerIOTask.su ./Source/task/main.cyclo ./Source/task/main.d ./Source/task/main.o ./Source/task/main.su

.PHONY: clean-Source-2f-task

