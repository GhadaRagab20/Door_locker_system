################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/gpio.c \
../MCAL/i2c.c \
../MCAL/timer.c \
../MCAL/uart.c 

OBJS += \
./MCAL/gpio.o \
./MCAL/i2c.o \
./MCAL/timer.o \
./MCAL/uart.o 

C_DEPS += \
./MCAL/gpio.d \
./MCAL/i2c.d \
./MCAL/timer.d \
./MCAL/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\out\Embedded system\embedded diploma 52\final_project\Control_ECU\APP" -I"E:\out\Embedded system\embedded diploma 52\final_project\Control_ECU\HAL" -I"E:\out\Embedded system\embedded diploma 52\final_project\Control_ECU\Infra_structure" -I"E:\out\Embedded system\embedded diploma 52\final_project\Control_ECU\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


