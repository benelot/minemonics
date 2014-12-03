################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/TestGenome.cpp \
../src/test/TestPopulation.cpp \
../src/test/TestRandomnessDouble.cpp \
../src/test/TestRandomnessInt.cpp \
../src/test/TestSettings.cpp 

OBJS += \
./src/test/TestGenome.o \
./src/test/TestPopulation.o \
./src/test/TestRandomnessDouble.o \
./src/test/TestRandomnessInt.o \
./src/test/TestSettings.o 

CPP_DEPS += \
./src/test/TestGenome.d \
./src/test/TestPopulation.d \
./src/test/TestRandomnessDouble.d \
./src/test/TestRandomnessInt.d \
./src/test/TestSettings.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


