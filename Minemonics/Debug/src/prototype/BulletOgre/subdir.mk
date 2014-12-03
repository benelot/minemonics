################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prototype/BulletOgre/BaseApplication.cpp \
../src/prototype/BulletOgre/TutorialApplication.cpp 

OBJS += \
./src/prototype/BulletOgre/BaseApplication.o \
./src/prototype/BulletOgre/TutorialApplication.o 

CPP_DEPS += \
./src/prototype/BulletOgre/BaseApplication.d \
./src/prototype/BulletOgre/TutorialApplication.d 


# Each subdirectory must supply rules for building sources it contributes
src/prototype/BulletOgre/%.o: ../src/prototype/BulletOgre/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


