################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_lpc845.c 

OBJS += \
./startup/startup_lpc845.o 

C_DEPS += \
./startup/startup_lpc845.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\board" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\source" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\drivers" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\device" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\CMSIS" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\component\uart" -I"C:\Users\Control 01\Documents\Personal Information\Workspaces\MCUXpresso\LPC84x\Tutorial_WebServer__1\utilities" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


