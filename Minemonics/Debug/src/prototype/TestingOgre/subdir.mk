################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prototype/TestingOgre/BaseApplication.cpp \
../src/prototype/TestingOgre/TutorialApplication.cpp 

OBJS += \
./src/prototype/TestingOgre/BaseApplication.o \
./src/prototype/TestingOgre/TutorialApplication.o 

CPP_DEPS += \
./src/prototype/TestingOgre/BaseApplication.d \
./src/prototype/TestingOgre/TutorialApplication.d 


# Each subdirectory must supply rules for building sources it contributes
src/prototype/TestingOgre/%.o: ../src/prototype/TestingOgre/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


