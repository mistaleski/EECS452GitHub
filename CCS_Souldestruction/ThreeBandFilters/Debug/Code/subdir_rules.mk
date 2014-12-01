################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Code/tunable_filter.obj: ../Code/tunable_filter.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/SW/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O3 -g --include_path="C:/SW/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="H:/eecs452/CSS_workspace/Tunable_IIR_Filter/Code" --include_path="H:/eecs452/CSS_workspace/C5515_Support_Files/452_Support" --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="Code/tunable_filter.pp" --obj_directory="Code" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


