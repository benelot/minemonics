################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/settings/ControlSettings.cpp \
../src/model/settings/EnvironmentSettings.cpp \
../src/model/settings/GeneticAlgorithmSettings.cpp \
../src/model/settings/MorphologySettings.cpp \
../src/model/settings/PhysicsSettings.cpp 

OBJS += \
./src/model/settings/ControlSettings.o \
./src/model/settings/EnvironmentSettings.o \
./src/model/settings/GeneticAlgorithmSettings.o \
./src/model/settings/MorphologySettings.o \
./src/model/settings/PhysicsSettings.o 

CPP_DEPS += \
./src/model/settings/ControlSettings.d \
./src/model/settings/EnvironmentSettings.d \
./src/model/settings/GeneticAlgorithmSettings.d \
./src/model/settings/MorphologySettings.d \
./src/model/settings/PhysicsSettings.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/settings/%.o: ../src/model/settings/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


