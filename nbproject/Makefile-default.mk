#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=adcDriver/ADC.c i2c1_driver/i2c1_driver.c i2c1_driver/i2c_master.c i2c1_driver/i2c_simple_master.c i2c1_driver/i2c_types.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s systemExtensions/systemExtensions.c main.c app.c ACCEL3.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/i2c1_driver/i2c1_driver.o ${OBJECTDIR}/i2c1_driver/i2c_master.o ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o ${OBJECTDIR}/i2c1_driver/i2c_types.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/systemExtensions/systemExtensions.o ${OBJECTDIR}/main.o ${OBJECTDIR}/app.o ${OBJECTDIR}/ACCEL3.o
POSSIBLE_DEPFILES=${OBJECTDIR}/adcDriver/ADC.o.d ${OBJECTDIR}/i2c1_driver/i2c1_driver.o.d ${OBJECTDIR}/i2c1_driver/i2c_master.o.d ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o.d ${OBJECTDIR}/i2c1_driver/i2c_types.o.d ${OBJECTDIR}/ledDriver/LED_tests.o.d ${OBJECTDIR}/oledDriver/oledC.o.d ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d ${OBJECTDIR}/oledDriver/oledC_shapes.o.d ${OBJECTDIR}/spiDriver/spi1_driver.o.d ${OBJECTDIR}/System/clock.o.d ${OBJECTDIR}/System/delay.o.d ${OBJECTDIR}/System/interrupt_manager.o.d ${OBJECTDIR}/System/pin_manager.o.d ${OBJECTDIR}/System/system.o.d ${OBJECTDIR}/System/traps.o.d ${OBJECTDIR}/System/where_was_i.o.d ${OBJECTDIR}/systemExtensions/systemExtensions.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/app.o.d ${OBJECTDIR}/ACCEL3.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/i2c1_driver/i2c1_driver.o ${OBJECTDIR}/i2c1_driver/i2c_master.o ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o ${OBJECTDIR}/i2c1_driver/i2c_types.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/systemExtensions/systemExtensions.o ${OBJECTDIR}/main.o ${OBJECTDIR}/app.o ${OBJECTDIR}/ACCEL3.o

# Source Files
SOURCEFILES=adcDriver/ADC.c i2c1_driver/i2c1_driver.c i2c1_driver/i2c_master.c i2c1_driver/i2c_simple_master.c i2c1_driver/i2c_types.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s systemExtensions/systemExtensions.c main.c app.c ACCEL3.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA705
MP_LINKER_FILE_OPTION=,--script=p24FJ256GA705.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/26da2ef0610a4e8c6f3148e258fd1b9ce5dde94c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c1_driver.o: i2c1_driver/i2c1_driver.c  .generated_files/flags/default/b7e3aeda6828768b8d512c2e759e785a5f443871 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c1_driver.c  -o ${OBJECTDIR}/i2c1_driver/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c_master.o: i2c1_driver/i2c_master.c  .generated_files/flags/default/e075abdee6baf197289a00683ad82e75638894e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c_master.c  -o ${OBJECTDIR}/i2c1_driver/i2c_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c_master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c_simple_master.o: i2c1_driver/i2c_simple_master.c  .generated_files/flags/default/aa835b6e8ed2f85670fc04f765c6ebbd69b37be3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c_simple_master.c  -o ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c_simple_master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c_types.o: i2c1_driver/i2c_types.c  .generated_files/flags/default/44c3082b351b3d866c4fd638a5544f5deeb4a82a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_types.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_types.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c_types.c  -o ${OBJECTDIR}/i2c1_driver/i2c_types.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c_types.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/default/38f4a47099bb85aec6e671adbb32b561ba28cbe9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/default/9a15f7f9e5a2acdbbf98420248c0113e096a6497 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/default/37da7bc5ef1c5bed414dd60106bd7dadd5138742 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/default/2bef3ef4108ada176a0224ef59ce454be5888f8f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/default/119648bfedc8e32ddf0ded5e8a6b907b6feab52b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/default/73900e32b45088564e6a8edb9f6fc8d524fd2129 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/default/f172b48113184e9ca752ba49333723c17f2caf8f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/default/3aca754a131063a919cc58342cb8520e2c717891 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/default/493eccdd5fe162d9036247e137c4c188ce619831 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/default/ae6c0d5aefc1626315a8c59934a19a8b4445b267 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/default/f33ae3da61e9342a0a6887c794d88559d13d1f29 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/systemExtensions/systemExtensions.o: systemExtensions/systemExtensions.c  .generated_files/flags/default/2e4624e771737f8ccbf5ac824386080ce6642480 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/systemExtensions" 
	@${RM} ${OBJECTDIR}/systemExtensions/systemExtensions.o.d 
	@${RM} ${OBJECTDIR}/systemExtensions/systemExtensions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  systemExtensions/systemExtensions.c  -o ${OBJECTDIR}/systemExtensions/systemExtensions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/systemExtensions/systemExtensions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4b1addb59371ffc563aebc1ccb39accaeff02fc2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app.o: app.c  .generated_files/flags/default/c00b8b8791305d96a214d655d7d11fb14ad6be4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app.o.d 
	@${RM} ${OBJECTDIR}/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app.c  -o ${OBJECTDIR}/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ACCEL3.o: ACCEL3.c  .generated_files/flags/default/3807efa9cd1dbbed2c5ec7e50835f525a074ba81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ACCEL3.c  -o ${OBJECTDIR}/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ACCEL3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/b4efa2508eda2fa35c3f586458e8fbc277578713 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c1_driver.o: i2c1_driver/i2c1_driver.c  .generated_files/flags/default/dc65907447accd941c82a59cada1578d1e54cffb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c1_driver.c  -o ${OBJECTDIR}/i2c1_driver/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c_master.o: i2c1_driver/i2c_master.c  .generated_files/flags/default/e87eaeade5ecda4d43066848ae5536aac279522a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c_master.c  -o ${OBJECTDIR}/i2c1_driver/i2c_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c_master.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c_simple_master.o: i2c1_driver/i2c_simple_master.c  .generated_files/flags/default/641fafa8b6fcefbbda8af41bd6dea41bd60b7006 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c_simple_master.c  -o ${OBJECTDIR}/i2c1_driver/i2c_simple_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c_simple_master.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2c1_driver/i2c_types.o: i2c1_driver/i2c_types.c  .generated_files/flags/default/b8721479df4ea2c85d4c87e556bb5689fb41f198 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2c1_driver" 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_types.o.d 
	@${RM} ${OBJECTDIR}/i2c1_driver/i2c_types.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2c1_driver/i2c_types.c  -o ${OBJECTDIR}/i2c1_driver/i2c_types.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2c1_driver/i2c_types.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/default/ee0ac07de3e7a899a05c41ce24c87c5711ef0421 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/default/5b5d095c7e902f5f048f8712c54ce2ac63890c0a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/default/4d51ad48e82859b052a526b1cf6abf6b8b2e73e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/default/7c49197980c090c94b17f9885ea34fce1f6cc05e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/default/4b2dc95928609e2861a410420ab2c44d2105fc5e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/default/5e6c5e68b86cb461881ffd08c7892145f02d287c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/default/137f72ffaafc4d2fdd4c918b99f3cd636006b553 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/default/b24b34795cc10d717f037f5fa9623baa7db7ef24 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/default/52c19c53348c25232c0d5a93365ca375e3a1a009 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/default/25c4c7671bf47eaba7b844be5878be5b2c03f898 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/default/d8e0f926a61333bb2d3d95ac434a286b49adb03d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/systemExtensions/systemExtensions.o: systemExtensions/systemExtensions.c  .generated_files/flags/default/852b91d7426090c8943311074ba8e8e84099667e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/systemExtensions" 
	@${RM} ${OBJECTDIR}/systemExtensions/systemExtensions.o.d 
	@${RM} ${OBJECTDIR}/systemExtensions/systemExtensions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  systemExtensions/systemExtensions.c  -o ${OBJECTDIR}/systemExtensions/systemExtensions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/systemExtensions/systemExtensions.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/d29791c61f6db6483700fa87ec7415f027fed6fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/app.o: app.c  .generated_files/flags/default/473344684ea4f56230f909be4461f3b87d30c85e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app.o.d 
	@${RM} ${OBJECTDIR}/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app.c  -o ${OBJECTDIR}/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/app.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ACCEL3.o: ACCEL3.c  .generated_files/flags/default/2d8c1de25198456328ca544ac70b2cd9b4fee50a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ACCEL3.c  -o ${OBJECTDIR}/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ACCEL3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/System/where_was_i.o: System/where_was_i.s  .generated_files/flags/default/1c1c20cfc5c9c979a1f29224b337b593b2251328 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/System/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  System/where_was_i.s  -o ${OBJECTDIR}/System/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/System/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/System/where_was_i.o: System/where_was_i.s  .generated_files/flags/default/58f5ba38eb25e6393df09484e96300792385b312 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/System/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  System/where_was_i.s  -o ${OBJECTDIR}/System/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/System/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
