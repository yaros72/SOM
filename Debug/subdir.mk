################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../deviation.c \
../functions.c \
../main.c \
../montecarlo.c \
../setConfiguration.c \
../updates.c 

OBJS += \
./deviation.o \
./functions.o \
./main.o \
./montecarlo.o \
./setConfiguration.o \
./updates.o 

C_DEPS += \
./deviation.d \
./functions.d \
./main.d \
./montecarlo.d \
./setConfiguration.d \
./updates.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -Os -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


