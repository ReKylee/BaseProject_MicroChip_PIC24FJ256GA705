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
SOURCEFILES_QUOTED_IF_SPACED=accel3Driver/ACCEL3.c adcDriver/ADC.c flash_generated/flash.s i2cDriver/I2C.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c switchDriver/Switch.c System/config_bits.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s Timers/Timers.c WatchApp/pomodoroTimer/pomodoro.c WatchApp/shared/watch_ui_widgets.c WatchApp/shared/watch_state.c WatchApp/watchCore/alarm.c WatchApp/watchCore/timekeeper.c WatchApp/watchDebug/debug_menu.c WatchApp/watchFaces/analog_face.c WatchApp/watchFaces/binary_face.c WatchApp/watchFaces/digital_face.c WatchApp/watchFaces/alarm_face.c WatchApp/watchFaces/watch_face_common.c WatchApp/watchFaces/watch_face_geometry.c WatchApp/watchInput/accel_input.c WatchApp/watchInput/buttons.c WatchApp/watchInput/potentiometer.c WatchApp/watchManagers/app_display_manager.c WatchApp/watchManagers/app_input_handler.c WatchApp/watchManagers/app_time_manager.c WatchApp/watchMenu/menu.c WatchApp/watchMenu/menu_core.c WatchApp/watchMenu/menu_state.c WatchApp/watchMenu/menu_render.c WatchApp/watchMenu/menu_input.c WatchApp/app_init.c WatchApp/watch_main.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/accel3Driver/ACCEL3.o ${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/flash_generated/flash.o ${OBJECTDIR}/i2cDriver/I2C.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/switchDriver/Switch.o ${OBJECTDIR}/System/config_bits.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/Timers/Timers.o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o ${OBJECTDIR}/WatchApp/shared/watch_state.o ${OBJECTDIR}/WatchApp/watchCore/alarm.o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o ${OBJECTDIR}/WatchApp/watchInput/buttons.o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o ${OBJECTDIR}/WatchApp/watchMenu/menu.o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o ${OBJECTDIR}/WatchApp/app_init.o ${OBJECTDIR}/WatchApp/watch_main.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/accel3Driver/ACCEL3.o.d ${OBJECTDIR}/adcDriver/ADC.o.d ${OBJECTDIR}/flash_generated/flash.o.d ${OBJECTDIR}/i2cDriver/I2C.o.d ${OBJECTDIR}/ledDriver/LED_tests.o.d ${OBJECTDIR}/oledDriver/oledC.o.d ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d ${OBJECTDIR}/oledDriver/oledC_shapes.o.d ${OBJECTDIR}/spiDriver/spi1_driver.o.d ${OBJECTDIR}/switchDriver/Switch.o.d ${OBJECTDIR}/System/config_bits.o.d ${OBJECTDIR}/System/clock.o.d ${OBJECTDIR}/System/delay.o.d ${OBJECTDIR}/System/interrupt_manager.o.d ${OBJECTDIR}/System/pin_manager.o.d ${OBJECTDIR}/System/system.o.d ${OBJECTDIR}/System/traps.o.d ${OBJECTDIR}/System/where_was_i.o.d ${OBJECTDIR}/Timers/Timers.o.d ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o.d ${OBJECTDIR}/WatchApp/shared/watch_state.o.d ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d ${OBJECTDIR}/WatchApp/app_init.o.d ${OBJECTDIR}/WatchApp/watch_main.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/accel3Driver/ACCEL3.o ${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/flash_generated/flash.o ${OBJECTDIR}/i2cDriver/I2C.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/switchDriver/Switch.o ${OBJECTDIR}/System/config_bits.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/Timers/Timers.o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o ${OBJECTDIR}/WatchApp/shared/watch_state.o ${OBJECTDIR}/WatchApp/watchCore/alarm.o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o ${OBJECTDIR}/WatchApp/watchInput/buttons.o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o ${OBJECTDIR}/WatchApp/watchMenu/menu.o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o ${OBJECTDIR}/WatchApp/app_init.o ${OBJECTDIR}/WatchApp/watch_main.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=accel3Driver/ACCEL3.c adcDriver/ADC.c flash_generated/flash.s i2cDriver/I2C.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c switchDriver/Switch.c System/config_bits.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s Timers/Timers.c WatchApp/pomodoroTimer/pomodoro.c WatchApp/shared/watch_ui_widgets.c WatchApp/shared/watch_state.c WatchApp/watchCore/alarm.c WatchApp/watchCore/timekeeper.c WatchApp/watchDebug/debug_menu.c WatchApp/watchFaces/analog_face.c WatchApp/watchFaces/binary_face.c WatchApp/watchFaces/digital_face.c WatchApp/watchFaces/alarm_face.c WatchApp/watchFaces/watch_face_common.c WatchApp/watchFaces/watch_face_geometry.c WatchApp/watchInput/accel_input.c WatchApp/watchInput/buttons.c WatchApp/watchInput/potentiometer.c WatchApp/watchManagers/app_display_manager.c WatchApp/watchManagers/app_input_handler.c WatchApp/watchManagers/app_time_manager.c WatchApp/watchMenu/menu.c WatchApp/watchMenu/menu_core.c WatchApp/watchMenu/menu_state.c WatchApp/watchMenu/menu_render.c WatchApp/watchMenu/menu_input.c WatchApp/app_init.c WatchApp/watch_main.c main.c



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
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/default/8227437e92a75f812dbbac737cd515bc8e4b2dde .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/905efee592dd9d3ea35e5c425fc28e34871416cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/default/2e724e9d69d013271bf94070764fa1feac394f69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/default/4e830d8ef646b617f186de3639626d4a002dd4d3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/default/fd863c124f4905363b37cd33a76c84bd61d8df5f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/default/5a6229ea574d38baa832e805e704f38301fd988f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/default/8ec01c71e34d0f6a37d882a478452323444aeb9e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/default/470bafa678dbe832d6156d7603f2daaa3ddc5be7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/default/4742b4e3bc4b137cc907dd5e79e949d0b514a2d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/config_bits.o: System/config_bits.c  .generated_files/flags/default/8595967e4ba71afb42bcb5f746724e27908286b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/config_bits.o.d 
	@${RM} ${OBJECTDIR}/System/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/config_bits.c  -o ${OBJECTDIR}/System/config_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/config_bits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/default/62d042ee78c1ee5b42114f7f7b94a9aef8beb017 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/default/ca127430ec50f1df2c5d6aa794eececb1eaf2ea7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/default/3f604e994ebf3aef243cadae7dc81ebf33c08da .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/default/a7893d6618ea0933363a17bc55ee9938229034b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/default/ebcb82767879a077642d12e10f8d88ad600af417 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/default/a8bc5d41a58847ab489258ca336d29fdbb232819 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/default/560a9e3a610e7296b1e2fe706868fbf28f9ec840 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/default/5aab4ceb756559256d230c8b94e8ce7886a5e4bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o: WatchApp/shared/watch_ui_widgets.c  .generated_files/flags/default/b3c2a2b1084d09699fc5786768c987f135134fbd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_ui_widgets.c  -o ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/default/e2d45868bbaf89242d66c4850028c08971e957f2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/default/a4c7d0bb6ead396b9a85da677a757d7107bbe07d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/default/ce1a3d60bfad9371de0877d22f2b78a3483b6cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o: WatchApp/watchDebug/debug_menu.c  .generated_files/flags/default/86ceb263559685ac952c425846beeb806f8c3619 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchDebug" 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchDebug/debug_menu.c  -o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/default/44e3a8cb68711ccffc6d017074b606abd18642d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/default/7d9f253d3386ef66beb21627e93f96405d02fc07 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/default/d31195410fbf48b784783313f3559d802c7c65fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/default/748b34abd6fe902d131af2ec4cd63876a25fd3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/default/cd4e6a034e286433dae13da2d81dd2601a6bb7ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/default/856ece981e768d4ba6b2bc473f35bebbffad8120 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/default/a3b4f3554972fce13a65b19dc249fd871244f6ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/default/7defc776193a1e39ec172355fe811ff4eaff7140 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/default/1ffbc6215857e68329e5e22e6f21abae779e2f63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/default/59292ff191d6f26cfc9d501d3cea0edca34e36d0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/default/76a906bf42e93d2e7f27a585ae5d8e21d1f530b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/default/801daeb4b66cb8791cf2ea9cd6b8f4043549773c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/default/5a6b48abead6bc570e8f5c37b0b2fb7a8dbe4b4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_core.o: WatchApp/watchMenu/menu_core.c  .generated_files/flags/default/6c0b1872729e2383f82e5769d04f5aff04daa09 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_core.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_state.o: WatchApp/watchMenu/menu_state.c  .generated_files/flags/default/3fc79ae034b8287b4918328bf06bd3d4bae12c2f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_state.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_render.o: WatchApp/watchMenu/menu_render.c  .generated_files/flags/default/107095f42486a93349d8c7aea47196de5d8ccfb4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_render.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_input.o: WatchApp/watchMenu/menu_input.c  .generated_files/flags/default/1345467afc300fb4392a35cc326abd9d379dd3b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_input.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/default/89ebd4d18efdc851674afa06911ee4bce502ee72 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/default/f15b6aabe8c5e9434f5780255718894d000b1e2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/274454ce07946d1acd11777cff5890acdf98587b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/default/56bcaa08f3d7002635c8c7f827bbba980f8f315d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/163f2825afcad35c38a3d90f768552f370c337c4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/default/1dcabbc66c7a116bc260a949948f2e90c9d37e67 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/default/f4a0cbf2f9d03b510543b7563a3a32822eaee16e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/default/f82da0135710453853a186214372c5e1abe5f563 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/default/1aebfdc239a1868d1f2cc266c69d63eb4cef68f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/default/db45bb391fa51e653547ee636b47d17a6fb30151 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/default/663d8808509b4da46924323d43ae77f2ed0d8abc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/default/589aad560c1b6eb1e59c690590075d4c383f8c25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/config_bits.o: System/config_bits.c  .generated_files/flags/default/74701e4798f22761e2ca6f03a08c46b39c1a0b32 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/config_bits.o.d 
	@${RM} ${OBJECTDIR}/System/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/config_bits.c  -o ${OBJECTDIR}/System/config_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/config_bits.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/default/984ad3510fcf30b5093209f9d9a0f095e14982ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/default/8fe8b9ed6925499bf4a02cd439ec194789ace01e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/default/d5e82128e6f1b7b512c33697dd87613b4bc64e69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/default/4db0c3b361b65a1fecf3bd4bde95df92a4d73c25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/default/7b3b577b28377e557f7fa37a0e8dc6e3ef55e30f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/default/d4e3c6124b41481664eb074f9df67b80b18fe4a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/default/8742a0d259bc05ca53a2604cf16aaed91115d189 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/default/4fdfaeb911945f8a857bbd766e5555b3846bb8df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o: WatchApp/shared/watch_ui_widgets.c  .generated_files/flags/default/d67cfedee1cc08ebcf65d425f2c7f11d0ef403f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_ui_widgets.c  -o ${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_ui_widgets.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/default/a67cae900e21792715ec20654178f802e86d7bfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/default/732900a8f3ee31814db5db06c01c88270aab9d60 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/default/4b679e54c3159b8908b90b2a44353deafb8c138f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o: WatchApp/watchDebug/debug_menu.c  .generated_files/flags/default/6d7b763954678d91491abd7b23a5fa0eb3af488 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchDebug" 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchDebug/debug_menu.c  -o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/default/36e5049825b36c82ecde4c545fba7a0d83e6d199 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/default/6991ee9a6cb9c1b038aefa8e560148f027a22199 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/default/9aa48af3b487dc85e6a393f4420e43800f573087 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/default/97c82cf74ba16ebf9ca5b364f34113a6ee1e0f90 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/default/741b089fff200e84fb7b8b3a8f39e4e7dc313d79 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/default/86a0839d3472a403bce6ef0bd76fc9eda609f72f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/default/98052883e90d80edf199c6240b9b16e4add1bb26 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/default/273417e4fd5d4403c89cf9bebbb04ea438c3c57c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/default/d5acce6106cf58c45a9bd61758ddc6fa784a45c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/default/2e7505d6ee6b076c1a1f10e9e91b3929faa925a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/default/f4b0029d3082e3b42bbbed2c90d58c6dd325e84f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/default/cd015634035935f2847d77992c0ff077371f9302 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/default/e71c738ca2e7e8169c64a9bf3cb9609160ceb007 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_core.o: WatchApp/watchMenu/menu_core.c  .generated_files/flags/default/d541fd62ac86738e06455d4371a4617434317f9f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_core.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_state.o: WatchApp/watchMenu/menu_state.c  .generated_files/flags/default/bc7d1829d50a837cf8c3a802bf9cf422f58c8e4c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_state.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_render.o: WatchApp/watchMenu/menu_render.c  .generated_files/flags/default/b1ded01bdef7ded49b600fa2d3c8d301dbdd360d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_render.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_input.o: WatchApp/watchMenu/menu_input.c  .generated_files/flags/default/d4e843f2e5a3433cf5103c7fdc853bd709b57172 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_input.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/default/cb17724771d5a68472b25defe234b6911896a14e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/default/2b6abdf701324e9a86a8318e50cf253b43321c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/ab9a1ae3ccc5c510297054c82d61d4d1418796d8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -O3 -I"bsp" -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/flash_generated/flash.o: flash_generated/flash.s  .generated_files/flags/default/c7c7b1df8af73ea9f848d206db0137832bc03137 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/flash_generated" 
	@${RM} ${OBJECTDIR}/flash_generated/flash.o.d 
	@${RM} ${OBJECTDIR}/flash_generated/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  flash_generated/flash.s  -o ${OBJECTDIR}/flash_generated/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -specs=cmd.txt -Wa,-MD,"${OBJECTDIR}/flash_generated/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/where_was_i.o: System/where_was_i.s  .generated_files/flags/default/1ec1919497d9a18f819834a302214f92cdc53f63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/System/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  System/where_was_i.s  -o ${OBJECTDIR}/System/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -specs=cmd.txt -Wa,-MD,"${OBJECTDIR}/System/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/flash_generated/flash.o: flash_generated/flash.s  .generated_files/flags/default/aef9779b5d13d37f94c11088de660e3d0620aa13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/flash_generated" 
	@${RM} ${OBJECTDIR}/flash_generated/flash.o.d 
	@${RM} ${OBJECTDIR}/flash_generated/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  flash_generated/flash.s  -o ${OBJECTDIR}/flash_generated/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -specs=cmd.txt -Wa,-MD,"${OBJECTDIR}/flash_generated/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/where_was_i.o: System/where_was_i.s  .generated_files/flags/default/98b80531cdc00208f70f617eadd4e2f929316faf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/System/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  System/where_was_i.s  -o ${OBJECTDIR}/System/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -specs=cmd.txt -Wa,-MD,"${OBJECTDIR}/System/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -specs=cmd.txt -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
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
