################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ethernet/delay.c \
../Ethernet/dhcp.c \
../Ethernet/led.c \
../Ethernet/socket.c \
../Ethernet/spi.c \
../Ethernet/usart.c \
../Ethernet/wizchip_conf.c 

OBJS += \
./Ethernet/delay.o \
./Ethernet/dhcp.o \
./Ethernet/led.o \
./Ethernet/socket.o \
./Ethernet/spi.o \
./Ethernet/usart.o \
./Ethernet/wizchip_conf.o 

C_DEPS += \
./Ethernet/delay.d \
./Ethernet/dhcp.d \
./Ethernet/led.d \
./Ethernet/socket.d \
./Ethernet/spi.d \
./Ethernet/usart.d \
./Ethernet/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Ethernet/%.o Ethernet/%.su Ethernet/%.cyclo: ../Ethernet/%.c Ethernet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32G0B0RETx -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32G0B0xx -DSTM32 -DSTM32G0 -c -I../Source -I../Source/user_lib -I../Ethernet -I../Ethernet/W5500 -I../modbusTCP -I../modbusTCP/inc -I../Source/config -I../Source/task -I../Source/peripherals_driver -I../Source/bsp -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Ethernet

clean-Ethernet:
	-$(RM) ./Ethernet/delay.cyclo ./Ethernet/delay.d ./Ethernet/delay.o ./Ethernet/delay.su ./Ethernet/dhcp.cyclo ./Ethernet/dhcp.d ./Ethernet/dhcp.o ./Ethernet/dhcp.su ./Ethernet/led.cyclo ./Ethernet/led.d ./Ethernet/led.o ./Ethernet/led.su ./Ethernet/socket.cyclo ./Ethernet/socket.d ./Ethernet/socket.o ./Ethernet/socket.su ./Ethernet/spi.cyclo ./Ethernet/spi.d ./Ethernet/spi.o ./Ethernet/spi.su ./Ethernet/usart.cyclo ./Ethernet/usart.d ./Ethernet/usart.o ./Ethernet/usart.su ./Ethernet/wizchip_conf.cyclo ./Ethernet/wizchip_conf.d ./Ethernet/wizchip_conf.o ./Ethernet/wizchip_conf.su

.PHONY: clean-Ethernet

