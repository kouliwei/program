################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CMD/28335_RAM_lnk.exe: C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/CMD/28335_RAM_lnk.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml --float_support=fpu32 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --obj_directory="C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/Debug" -z --stack_size=1000 -m"C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/CMD/Debug/SD.map" --heap_size=1000 --warn_sections -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" -i"C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/SD" -i"C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="SD_linkInfo.xml" --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMD/DSP2833x_Headers_nonBIOS.exe: C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/CMD/DSP2833x_Headers_nonBIOS.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml --float_support=fpu32 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --obj_directory="C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/Debug" -z --stack_size=1000 -m"C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/CMD/Debug/SD.map" --heap_size=1000 --warn_sections -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" -i"C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs/SD" -i"C:/Users/koukou/Desktop/reposity/program/sd_DSP28335/lab31-SD-SPI-Fatfs" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="SD_linkInfo.xml" --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


