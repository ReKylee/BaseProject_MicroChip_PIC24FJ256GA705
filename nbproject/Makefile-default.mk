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
SOURCEFILES_QUOTED_IF_SPACED=accel3Driver/ACCEL3.c adcDriver/ADC.c i2cDriver/I2C.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c switchDriver/Switch.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s Timers/Timers.c WatchApp/pomodoroTimer/pomodoro.c WatchApp/shared/watch_state.c WatchApp/watchCore/alarm.c WatchApp/watchCore/timekeeper.c WatchApp/watchDebug/debug_menu.c WatchApp/watchFaces/analog_face.c WatchApp/watchFaces/binary_face.c WatchApp/watchFaces/digital_face.c WatchApp/watchFaces/alarm_face.c WatchApp/watchFaces/watch_face_common.c WatchApp/watchFaces/watch_face_geometry.c WatchApp/watchInput/accel_input.c WatchApp/watchInput/buttons.c WatchApp/watchInput/potentiometer.c WatchApp/watchManagers/app_display_manager.c WatchApp/watchManagers/app_input_handler.c WatchApp/watchManagers/app_time_manager.c WatchApp/watchMenu/menu.c WatchApp/watchMenu/menu_core.c WatchApp/watchMenu/menu_state.c WatchApp/watchMenu/menu_render.c WatchApp/watchMenu/menu_input.c WatchApp/app_init.c WatchApp/watch_main.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/accel3Driver/ACCEL3.o ${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/i2cDriver/I2C.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/switchDriver/Switch.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/Timers/Timers.o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o ${OBJECTDIR}/WatchApp/shared/watch_state.o ${OBJECTDIR}/WatchApp/watchCore/alarm.o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o ${OBJECTDIR}/WatchApp/watchInput/buttons.o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o ${OBJECTDIR}/WatchApp/watchMenu/menu.o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o ${OBJECTDIR}/WatchApp/app_init.o ${OBJECTDIR}/WatchApp/watch_main.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/accel3Driver/ACCEL3.o.d ${OBJECTDIR}/adcDriver/ADC.o.d ${OBJECTDIR}/i2cDriver/I2C.o.d ${OBJECTDIR}/ledDriver/LED_tests.o.d ${OBJECTDIR}/oledDriver/oledC.o.d ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d ${OBJECTDIR}/oledDriver/oledC_shapes.o.d ${OBJECTDIR}/spiDriver/spi1_driver.o.d ${OBJECTDIR}/switchDriver/Switch.o.d ${OBJECTDIR}/System/clock.o.d ${OBJECTDIR}/System/delay.o.d ${OBJECTDIR}/System/interrupt_manager.o.d ${OBJECTDIR}/System/pin_manager.o.d ${OBJECTDIR}/System/system.o.d ${OBJECTDIR}/System/traps.o.d ${OBJECTDIR}/System/where_was_i.o.d ${OBJECTDIR}/Timers/Timers.o.d ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d ${OBJECTDIR}/WatchApp/shared/watch_state.o.d ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d ${OBJECTDIR}/WatchApp/app_init.o.d ${OBJECTDIR}/WatchApp/watch_main.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/accel3Driver/ACCEL3.o ${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/i2cDriver/I2C.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/switchDriver/Switch.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/Timers/Timers.o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o ${OBJECTDIR}/WatchApp/shared/watch_state.o ${OBJECTDIR}/WatchApp/watchCore/alarm.o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o ${OBJECTDIR}/WatchApp/watchInput/buttons.o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o ${OBJECTDIR}/WatchApp/watchMenu/menu.o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o ${OBJECTDIR}/WatchApp/app_init.o ${OBJECTDIR}/WatchApp/watch_main.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=accel3Driver/ACCEL3.c adcDriver/ADC.c i2cDriver/I2C.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c switchDriver/Switch.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s Timers/Timers.c WatchApp/pomodoroTimer/pomodoro.c WatchApp/shared/watch_state.c WatchApp/watchCore/alarm.c WatchApp/watchCore/timekeeper.c WatchApp/watchDebug/debug_menu.c WatchApp/watchFaces/analog_face.c WatchApp/watchFaces/binary_face.c WatchApp/watchFaces/digital_face.c WatchApp/watchFaces/alarm_face.c WatchApp/watchFaces/watch_face_common.c WatchApp/watchFaces/watch_face_geometry.c WatchApp/watchInput/accel_input.c WatchApp/watchInput/buttons.c WatchApp/watchInput/potentiometer.c WatchApp/watchManagers/app_display_manager.c WatchApp/watchManagers/app_input_handler.c WatchApp/watchManagers/app_time_manager.c WatchApp/watchMenu/menu.c WatchApp/watchMenu/menu_core.c WatchApp/watchMenu/menu_state.c WatchApp/watchMenu/menu_render.c WatchApp/watchMenu/menu_input.c WatchApp/app_init.c WatchApp/watch_main.c main.c



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
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/default/5a14b3715d4049af1db62523608db05bf9e547d6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/f93b35258ea889dd771b51de9cfa1ea54b7c2778 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/default/6ca0a098db9df9924ebd244cc2473aad74c4521f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/default/cca32830c864cce7ee13ae7ae477b1c12cf5a451 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/default/b8e61881a73460b0724389ab3dbffcae1c2088fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/default/355a618a95e86053972bd00326dbf1bfd77bd0be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/default/a4985a48ff345f4de47901614a1254e19d8334e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/default/36f72b7d395953db31c3554150a113ec7940bac0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/default/ca971d4feeb0c915a10f96493a6491c4d59b2cb3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/default/32b36db37693426fc84eeb74230fd6fa48e08a37 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/default/70115abbed35f1f8d84238dd25de515374ffd113 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/default/55eecada4916fef59ad7412c6d582454bd7f713f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/default/2d00afe998a9cdd3f3a9eb6577eb69b45d1a67a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/default/fe0fec176b621ddab4f6082ee1c9967ea6d585eb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/default/38561c7c3eee1fc362553d856f456b985aec5e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/default/4cc7bcf99ed5ceb118252c70f7331e44f4e78de3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/default/6b79e932f7aec31e2b6c9b53b3226aed453fd20d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/default/caca582d23d5378fdedf2e26c383624b23764545 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/default/362d99ff5a4763e2ce1466e200047954ca7cb26f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/default/84760134fecd09d2b9868eb918350703b9d5f68f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o: WatchApp/watchDebug/debug_menu.c  .generated_files/flags/default/8706406587c92448e5c71deae8cad81b07a24ccb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchDebug" 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchDebug/debug_menu.c  -o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/default/bf50fb9d904ce562b4e4d846886c8f265b7ee09d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/default/1c3bb34b420bd333e657140659bb136c665e4356 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/default/4bc0f162e5bf592a01751d559d01ddaa0c160ee2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/default/8cdc5811dc7a500b80f02539eecb72fce8141aa6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/default/db7fc6a34842ece8dc5c35c51fc17b9743b5b12f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/default/56afab4bc24bfc007451d9b9a8ad6e3122f366b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/default/66484bbf91425d3079b42945b47af8ee99d060a9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/default/6f01c700b4b7053089a30c5b6eea9e358e61770d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/default/5210a9ab080f6a6d28add58f229285b62b18e01e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/default/508c9b759bda871fead3a8700708c691bbd124dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/default/97a1bb45d0aef7efd240788f95eb0399f00f96ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/default/cfec157c43061efb8888ed770e3d5c162f33dcc1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/default/695193746cfbbb329f498c13bc8c8487c4bfb2bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_core.o: WatchApp/watchMenu/menu_core.c  .generated_files/flags/default/928e3101f747465102a1a43aa42a0a7b3b5b1033 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_core.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_state.o: WatchApp/watchMenu/menu_state.c  .generated_files/flags/default/5725e5fe61a52192170d06b3479d7fdae959a7aa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_state.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_render.o: WatchApp/watchMenu/menu_render.c  .generated_files/flags/default/cbde78f721dc294506eac902a1491fae0f5f784b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_render.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_input.o: WatchApp/watchMenu/menu_input.c  .generated_files/flags/default/b0f145c486b24cd9f5d2e766ca6fe197c1cfcbca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_input.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/default/ca94ef141384dea2959277b9b49a15a9a1bcd848 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/default/934fc8fc991e1d95fc5d6081c34d4c990d9c5076 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/6e76c4a5105a2d7a3a1826c7d92ce91730296e46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/default/34ae312a90703c57e1aec3615c1f4a518fc0fc80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/3cb90f386532c9192207e6e38f65e5484f47df24 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/default/1e6bb9f27dfc3e8af48329faf09fbdb38b9cb218 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/default/109527daba706ed875bb499cbc29a60ab336e1e1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/default/beb63a9979d027a5fe14bfaa32dce543eabebaf2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/default/19bf14c9bdece96ac4912a215b406893fd2b1231 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/default/ad699e714cb3990e9787beef370e51e1a68e64cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/default/1d60216abc8516abd6cbab15ea09525b15aaf294 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/default/22613dea773eab8fd41a5e5a6b15f6c5f5dfc2d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/default/ebaa175bf58420f336fa22b446349c2796c74f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/default/59badb71fc8f1766928c5b2da59408050d8e6d47 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/default/ba539931e9954784ff8e2034d77c13ffd77bc923 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/default/cea5eec54b319d7d77fd0c60186211b805a17dee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/default/5d87f8ff6ac2b8cb6b96b115a72dfe254102bc7c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/default/fad2c79c0aff8c86af1bc365953646ebcf842df6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/default/153848f908b2d0a233a48e46137e6e1366423dd7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/default/2889507763377a76b2dacdd21c6f1a610a047f24 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/default/ff981b9f682096e45cadaaab052809dd1eb03f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/default/a606da41086bac1466602271c9dda5b8ec1a60bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/default/b6e4da89f9834102fb5311befc23cbe2e6254e23 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o: WatchApp/watchDebug/debug_menu.c  .generated_files/flags/default/a2cd300a5ab2ec7905f41d0cb7b5e5235f79560 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchDebug" 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchDebug/debug_menu.c  -o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/default/bff27ba35a0b485bef17f2a86f8126bcea4e0194 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/default/55ac18ba67c743ccd32f4eec42976c902d170794 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/default/14c1b1b9ba518bab43921ac0cd070617a8079b62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/default/7966936824a1bbe87768be5d1b537f4b1ed6c93 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/default/85a8f5a7a4f49595584235a85fa92131a7aae2a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/default/bd71c7a762eec2bc11df2b00b6fc0b087bb703ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/default/e9f711e7b33f45f4ddafc495f14d7d16be90f4a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/default/544de0fe96428ea99c1fba405fb8b5cbcc7b701 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/default/b66806c2289200427e531d84bc1b717e9a70d4d5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/default/61c9f0d0c0eedda636eb91c12f9b896391b19f7a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/default/d43acee4e905a2dcbf14c3ca8754148e96ba4852 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/default/de45a0ad26a8b8ad25e9c1cbe8341d317c80be0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/default/fd802f5f227e3861397b7ed32e501b8515203efa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_core.o: WatchApp/watchMenu/menu_core.c  .generated_files/flags/default/82a87c08fad20c723ecf48931c78948eba3a46dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_core.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_state.o: WatchApp/watchMenu/menu_state.c  .generated_files/flags/default/c065a0f8806b2d105e96c734ef54e7ac12ac3d1e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_state.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_render.o: WatchApp/watchMenu/menu_render.c  .generated_files/flags/default/76488b5a5e22e651b8d88307dc92a140dc7cecac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_render.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_input.o: WatchApp/watchMenu/menu_input.c  .generated_files/flags/default/db69e55b5cffd276e0673855db5a15a9b83f881f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_input.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/default/30f557398258cab8287bb5beb592003e640a4a8e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/default/5b98e0f18a6cf0d4a866f4bb0c37d6f74aa96b20 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/1380a883379275a222e761bd8ef963e5d969e83a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
