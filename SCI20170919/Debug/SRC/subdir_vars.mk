################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../SRC/DSP2833x_ADC_cal.asm \
../SRC/DSP2833x_CodeStartBranch.asm \
../SRC/DSP2833x_usDelay.asm 

C_SRCS += \
../SRC/DSP2833x_Adc.c \
../SRC/DSP2833x_CpuTimers.c \
../SRC/DSP2833x_DefaultIsr.c \
../SRC/DSP2833x_GlobalVariableDefs.c \
../SRC/DSP2833x_I2C.c \
../SRC/DSP2833x_MemCopy.c \
../SRC/DSP2833x_PieCtrl.c \
../SRC/DSP2833x_PieVect.c \
../SRC/DSP2833x_Sci.c \
../SRC/DSP2833x_Spi.c \
../SRC/DSP2833x_SysCtrl.c \
../SRC/DSP2833x_Xintf.c \
../SRC/SCI.c \
../SRC/SD_SPI_Erase.c \
../SRC/SD_SPI_Initialization.c \
../SRC/SD_SPI_Read.c \
../SRC/SD_SPI_Registers.c \
../SRC/SD_SPI_Transmission.c \
../SRC/SD_SPI_Write.c \
../SRC/USER_ADC.c \
../SRC/USER_Common.c \
../SRC/USER_Distance.c \
../SRC/USER_I2C.c \
../SRC/USER_Motion.c \
../SRC/USER_Pwm.c \
../SRC/USER_Sci.c \
../SRC/USER_Sensor.c \
../SRC/USER_Sliding.c \
../SRC/USER_Spi.c \
../SRC/disk_sd.c \
../SRC/diskio.c \
../SRC/ff.c 

OBJS += \
./SRC/DSP2833x_ADC_cal.obj \
./SRC/DSP2833x_Adc.obj \
./SRC/DSP2833x_CodeStartBranch.obj \
./SRC/DSP2833x_CpuTimers.obj \
./SRC/DSP2833x_DefaultIsr.obj \
./SRC/DSP2833x_GlobalVariableDefs.obj \
./SRC/DSP2833x_I2C.obj \
./SRC/DSP2833x_MemCopy.obj \
./SRC/DSP2833x_PieCtrl.obj \
./SRC/DSP2833x_PieVect.obj \
./SRC/DSP2833x_Sci.obj \
./SRC/DSP2833x_Spi.obj \
./SRC/DSP2833x_SysCtrl.obj \
./SRC/DSP2833x_Xintf.obj \
./SRC/DSP2833x_usDelay.obj \
./SRC/SCI.obj \
./SRC/SD_SPI_Erase.obj \
./SRC/SD_SPI_Initialization.obj \
./SRC/SD_SPI_Read.obj \
./SRC/SD_SPI_Registers.obj \
./SRC/SD_SPI_Transmission.obj \
./SRC/SD_SPI_Write.obj \
./SRC/USER_ADC.obj \
./SRC/USER_Common.obj \
./SRC/USER_Distance.obj \
./SRC/USER_I2C.obj \
./SRC/USER_Motion.obj \
./SRC/USER_Pwm.obj \
./SRC/USER_Sci.obj \
./SRC/USER_Sensor.obj \
./SRC/USER_Sliding.obj \
./SRC/USER_Spi.obj \
./SRC/disk_sd.obj \
./SRC/diskio.obj \
./SRC/ff.obj 

ASM_DEPS += \
./SRC/DSP2833x_ADC_cal.pp \
./SRC/DSP2833x_CodeStartBranch.pp \
./SRC/DSP2833x_usDelay.pp 

C_DEPS += \
./SRC/DSP2833x_Adc.pp \
./SRC/DSP2833x_CpuTimers.pp \
./SRC/DSP2833x_DefaultIsr.pp \
./SRC/DSP2833x_GlobalVariableDefs.pp \
./SRC/DSP2833x_I2C.pp \
./SRC/DSP2833x_MemCopy.pp \
./SRC/DSP2833x_PieCtrl.pp \
./SRC/DSP2833x_PieVect.pp \
./SRC/DSP2833x_Sci.pp \
./SRC/DSP2833x_Spi.pp \
./SRC/DSP2833x_SysCtrl.pp \
./SRC/DSP2833x_Xintf.pp \
./SRC/SCI.pp \
./SRC/SD_SPI_Erase.pp \
./SRC/SD_SPI_Initialization.pp \
./SRC/SD_SPI_Read.pp \
./SRC/SD_SPI_Registers.pp \
./SRC/SD_SPI_Transmission.pp \
./SRC/SD_SPI_Write.pp \
./SRC/USER_ADC.pp \
./SRC/USER_Common.pp \
./SRC/USER_Distance.pp \
./SRC/USER_I2C.pp \
./SRC/USER_Motion.pp \
./SRC/USER_Pwm.pp \
./SRC/USER_Sci.pp \
./SRC/USER_Sensor.pp \
./SRC/USER_Sliding.pp \
./SRC/USER_Spi.pp \
./SRC/disk_sd.pp \
./SRC/diskio.pp \
./SRC/ff.pp 

C_DEPS__QUOTED += \
"SRC\DSP2833x_Adc.pp" \
"SRC\DSP2833x_CpuTimers.pp" \
"SRC\DSP2833x_DefaultIsr.pp" \
"SRC\DSP2833x_GlobalVariableDefs.pp" \
"SRC\DSP2833x_I2C.pp" \
"SRC\DSP2833x_MemCopy.pp" \
"SRC\DSP2833x_PieCtrl.pp" \
"SRC\DSP2833x_PieVect.pp" \
"SRC\DSP2833x_Sci.pp" \
"SRC\DSP2833x_Spi.pp" \
"SRC\DSP2833x_SysCtrl.pp" \
"SRC\DSP2833x_Xintf.pp" \
"SRC\SCI.pp" \
"SRC\SD_SPI_Erase.pp" \
"SRC\SD_SPI_Initialization.pp" \
"SRC\SD_SPI_Read.pp" \
"SRC\SD_SPI_Registers.pp" \
"SRC\SD_SPI_Transmission.pp" \
"SRC\SD_SPI_Write.pp" \
"SRC\USER_ADC.pp" \
"SRC\USER_Common.pp" \
"SRC\USER_Distance.pp" \
"SRC\USER_I2C.pp" \
"SRC\USER_Motion.pp" \
"SRC\USER_Pwm.pp" \
"SRC\USER_Sci.pp" \
"SRC\USER_Sensor.pp" \
"SRC\USER_Sliding.pp" \
"SRC\USER_Spi.pp" \
"SRC\disk_sd.pp" \
"SRC\diskio.pp" \
"SRC\ff.pp" 

OBJS__QUOTED += \
"SRC\DSP2833x_ADC_cal.obj" \
"SRC\DSP2833x_Adc.obj" \
"SRC\DSP2833x_CodeStartBranch.obj" \
"SRC\DSP2833x_CpuTimers.obj" \
"SRC\DSP2833x_DefaultIsr.obj" \
"SRC\DSP2833x_GlobalVariableDefs.obj" \
"SRC\DSP2833x_I2C.obj" \
"SRC\DSP2833x_MemCopy.obj" \
"SRC\DSP2833x_PieCtrl.obj" \
"SRC\DSP2833x_PieVect.obj" \
"SRC\DSP2833x_Sci.obj" \
"SRC\DSP2833x_Spi.obj" \
"SRC\DSP2833x_SysCtrl.obj" \
"SRC\DSP2833x_Xintf.obj" \
"SRC\DSP2833x_usDelay.obj" \
"SRC\SCI.obj" \
"SRC\SD_SPI_Erase.obj" \
"SRC\SD_SPI_Initialization.obj" \
"SRC\SD_SPI_Read.obj" \
"SRC\SD_SPI_Registers.obj" \
"SRC\SD_SPI_Transmission.obj" \
"SRC\SD_SPI_Write.obj" \
"SRC\USER_ADC.obj" \
"SRC\USER_Common.obj" \
"SRC\USER_Distance.obj" \
"SRC\USER_I2C.obj" \
"SRC\USER_Motion.obj" \
"SRC\USER_Pwm.obj" \
"SRC\USER_Sci.obj" \
"SRC\USER_Sensor.obj" \
"SRC\USER_Sliding.obj" \
"SRC\USER_Spi.obj" \
"SRC\disk_sd.obj" \
"SRC\diskio.obj" \
"SRC\ff.obj" 

ASM_DEPS__QUOTED += \
"SRC\DSP2833x_ADC_cal.pp" \
"SRC\DSP2833x_CodeStartBranch.pp" \
"SRC\DSP2833x_usDelay.pp" 

ASM_SRCS__QUOTED += \
"../SRC/DSP2833x_ADC_cal.asm" \
"../SRC/DSP2833x_CodeStartBranch.asm" \
"../SRC/DSP2833x_usDelay.asm" 

C_SRCS__QUOTED += \
"../SRC/DSP2833x_Adc.c" \
"../SRC/DSP2833x_CpuTimers.c" \
"../SRC/DSP2833x_DefaultIsr.c" \
"../SRC/DSP2833x_GlobalVariableDefs.c" \
"../SRC/DSP2833x_I2C.c" \
"../SRC/DSP2833x_MemCopy.c" \
"../SRC/DSP2833x_PieCtrl.c" \
"../SRC/DSP2833x_PieVect.c" \
"../SRC/DSP2833x_Sci.c" \
"../SRC/DSP2833x_Spi.c" \
"../SRC/DSP2833x_SysCtrl.c" \
"../SRC/DSP2833x_Xintf.c" \
"../SRC/SCI.c" \
"../SRC/SD_SPI_Erase.c" \
"../SRC/SD_SPI_Initialization.c" \
"../SRC/SD_SPI_Read.c" \
"../SRC/SD_SPI_Registers.c" \
"../SRC/SD_SPI_Transmission.c" \
"../SRC/SD_SPI_Write.c" \
"../SRC/USER_ADC.c" \
"../SRC/USER_Common.c" \
"../SRC/USER_Distance.c" \
"../SRC/USER_I2C.c" \
"../SRC/USER_Motion.c" \
"../SRC/USER_Pwm.c" \
"../SRC/USER_Sci.c" \
"../SRC/USER_Sensor.c" \
"../SRC/USER_Sliding.c" \
"../SRC/USER_Spi.c" \
"../SRC/disk_sd.c" \
"../SRC/diskio.c" \
"../SRC/ff.c" 


