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
ifeq "$(wildcard nbproject/Makefile-local-debug.mk)" "nbproject/Makefile-local-debug.mk"
include nbproject/Makefile-local-debug.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=debug
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
	${MAKE}  -f nbproject/Makefile-debug.mk ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA705
MP_LINKER_FILE_OPTION=,--script=p24FJ256GA705.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/debug/c2dd59d1db6ca703ec5e1b98ad1c4a7c046301dd .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/debug/6b9bbd4dbec636101e5652b54650c23065a46d58 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/debug/7424c2233c269a42cc93cbcb9226626eb22b8e4d .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/debug/5e84388d6611f0b25323c9f88c7c95a2c60c4e3 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/debug/17699c1096c91ba17d29258244e29dc8da4fa9e3 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/debug/7b0b76584353c8fa02d625e399df6d2b57524c69 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/debug/ba331514ea175c0160e0d5b8f980e2dd94f919e2 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/debug/6de105517ed599cbcc0f1a11f0c24247864e0c9f .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/debug/e430b1986b3108b2a06050d4dbbdf6b62e65eb5c .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/debug/736e525cb3fa2ab50afd6f85ee251cc1716fc61f .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/debug/dcd98dba02b2430ba02e5f69b5418733752b927c .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/debug/234e769397597b4b5d73c93eab8cf768a756f534 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/debug/73e11ba46feb07c8daba292e29d2c63be27c3196 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/debug/ce8d939c9bffff3c47f7195afbe1d6296d3649ae .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/debug/74201170ff3efd3a124e84088117cb610052d87d .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/debug/1e9988f1e9f5560e83e623111347503ed627005a .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/debug/9234ef68e3c0d77e74e78940ec69b33ae40997dc .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/debug/f8f1615575f9cd922c797aadd22af17d57f8a76e .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/debug/609d7afb40707d297149e5b4db441e9f4fa46db4 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/debug/5a04d2ccc54ed449e5fe98b1c4fa926a3fa2aa77 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o: WatchApp/watchDebug/debug_menu.c  .generated_files/flags/debug/c12379f29808f17d4e609afe7748c6ca48b830ef .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchDebug" 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchDebug/debug_menu.c  -o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/debug/999635b577b34c1b885060c8478c91267b8c17fa .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/debug/d3feee7734a4cffd293d096849837cd38dc1af66 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/debug/81b695c83516e91920c91ba59289251b6a8df9ca .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/debug/a2ab01c5f4a293a3e0e0e439c6f7cec5e1abeba1 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/debug/cd59a65ee26e13f7afbf0f6106f898a7033bf3a5 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/debug/4cfb1f16064300f8beb825652f1e2096f78c68c9 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/debug/a0af27d1b8f58b27bda8e617fd840edb611943c4 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/debug/cf74547723520c48a77cd63d885a40d6474a513a .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/debug/1366d37150b1228bda54ec9f7fad1fccb44c1c02 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/debug/e1ca59fc78811287c6b17d08167524e5d4b50389 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/debug/61137a6562531a612e7f35beef326600aee2de5 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/debug/5927f7b991b85de26ccc1dc991679c0b263076cd .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/debug/15359aac02465542c77e7208b193cd30ae93dee5 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_core.o: WatchApp/watchMenu/menu_core.c  .generated_files/flags/debug/cbbaa1f5a4c74750681f8698d6c441065e7feec6 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_core.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_state.o: WatchApp/watchMenu/menu_state.c  .generated_files/flags/debug/c41b4eb78e25e6496d1b9b5f12c5ce232e0418b .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_state.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_render.o: WatchApp/watchMenu/menu_render.c  .generated_files/flags/debug/451ac55d14c6f25b3bda97ea279a8c65a5be8b42 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_render.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_input.o: WatchApp/watchMenu/menu_input.c  .generated_files/flags/debug/14963ea189205f6239d882036fe78c14a452cd6e .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_input.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/debug/7c68c463e9d856f6fb1b64f3feed25d16d97aaa4 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/debug/2768969245b44a3de10179d3e15a870047f33d1b .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/debug/65906b65c4ddbc4eb9292c972ad77b3e34b48e0e .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/debug/745a45404eb0b91d6ce8f1f69d7b974cd0762db4 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/debug/3b139c52c57f3e2629ee4322c6f90c3658c1d63c .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/debug/5a1b81e134b28eaf87b07d9e4c0ccd61669bd074 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ledDriver/LED_tests.o: ledDriver/LED_tests.c  .generated_files/flags/debug/565d9efcb53252ab5ac5e97056ffe42ae56aac6e .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ledDriver" 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o.d 
	@${RM} ${OBJECTDIR}/ledDriver/LED_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ledDriver/LED_tests.c  -o ${OBJECTDIR}/ledDriver/LED_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ledDriver/LED_tests.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC.o: oledDriver/oledC.c  .generated_files/flags/debug/5b82dc03b4e9d86ba09d76b6d848c0a885e750a4 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC.c  -o ${OBJECTDIR}/oledDriver/oledC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapeHandler.o: oledDriver/oledC_shapeHandler.c  .generated_files/flags/debug/f563128ed9ca5a1a0164e783c5481a665731164d .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapeHandler.c  -o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/oledDriver/oledC_shapes.o: oledDriver/oledC_shapes.c  .generated_files/flags/debug/39a7a1846d1b996c684b0117ffd79e5635eeb03e .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/oledDriver" 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o.d 
	@${RM} ${OBJECTDIR}/oledDriver/oledC_shapes.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  oledDriver/oledC_shapes.c  -o ${OBJECTDIR}/oledDriver/oledC_shapes.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oledDriver/oledC_shapes.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/spiDriver/spi1_driver.o: spiDriver/spi1_driver.c  .generated_files/flags/debug/7f17ff6d7b4069360ad965cb5ce3865d19eb96be .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/spiDriver" 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o.d 
	@${RM} ${OBJECTDIR}/spiDriver/spi1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spiDriver/spi1_driver.c  -o ${OBJECTDIR}/spiDriver/spi1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spiDriver/spi1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/debug/3ba11a176cd2fdb622623165e8a0c9767a032f77 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/clock.o: System/clock.c  .generated_files/flags/debug/c15ebd561778c95414c88ced78ccab7321b21ce4 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/clock.o.d 
	@${RM} ${OBJECTDIR}/System/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/clock.c  -o ${OBJECTDIR}/System/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/delay.o: System/delay.c  .generated_files/flags/debug/91a8f6fb3c267fe605079cc7c0838c86bc386529 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/delay.o.d 
	@${RM} ${OBJECTDIR}/System/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/delay.c  -o ${OBJECTDIR}/System/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/interrupt_manager.o: System/interrupt_manager.c  .generated_files/flags/debug/7b011032469ca3d7ae78d167c35218b024136018 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/System/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/interrupt_manager.c  -o ${OBJECTDIR}/System/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/pin_manager.o: System/pin_manager.c  .generated_files/flags/debug/c5177e2641aae6e34fb11295163800a5b2815488 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/System/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/pin_manager.c  -o ${OBJECTDIR}/System/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/system.o: System/system.c  .generated_files/flags/debug/808fe46e5e4a15f8ab04f378b31851a90c738d86 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/system.o.d 
	@${RM} ${OBJECTDIR}/System/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/system.c  -o ${OBJECTDIR}/System/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/System/traps.o: System/traps.c  .generated_files/flags/debug/93de690816db7d937e83930799e04e49a683712 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/traps.o.d 
	@${RM} ${OBJECTDIR}/System/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  System/traps.c  -o ${OBJECTDIR}/System/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/System/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/debug/9e5f1925ba6f556c662c8b5f96c8f144dd2e0715 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/debug/be92f9e7686164e597d0984e0db08c4abeae39ec .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/debug/5ad302e8d4943129f38e488827defd694d0d30e0 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/debug/d912bb1f2c2c38341c3234c6f11d07a99d280202 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/debug/3f35714ec8d649315b18a91c31e640807ead5d7f .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o: WatchApp/watchDebug/debug_menu.c  .generated_files/flags/debug/e3bbe06cec204e724230183e3126f6ad610c26d0 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchDebug" 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchDebug/debug_menu.c  -o ${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchDebug/debug_menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/debug/81007201d590e8b0cbd5c1b1ac00796603716d5b .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/debug/cdcb8864c37e51f6b38407913e1e246f84bf5b65 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/debug/c8cf2feb953e395447079a9313afb476418c6f97 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/debug/96c72e3b46c3dc098634a9d994f7ef54fecbba51 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/debug/b64ea6a5a9eaf1ba2c071804b4840ae9e7674fe1 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/debug/5065f5638c85dc80cd937842ef14259aa12b704 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/debug/64ea18b0d9478e0de3a5fbd53772c8bd90573644 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/debug/c720a2fb989ac92a556d0d1e069139a368f39b07 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/debug/5638898202898fec4d0b428934fce90d9f792fe2 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/debug/4247b3f924a1efe9820bb2c5303ad7c7ecc2b987 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/debug/cbe28711a24b8ab865ff2c8e1e08512ecfdae8ec .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/debug/4ac774f56a1b73d70adc751194e81c35cbe710c8 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/debug/9c7512a1ce6abd736a3aba9081efefc86a9fa343 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_core.o: WatchApp/watchMenu/menu_core.c  .generated_files/flags/debug/5044c87ce4df1f0f8fdbe7341d94fcb66b5cbe4e .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_core.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_core.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_state.o: WatchApp/watchMenu/menu_state.c  .generated_files/flags/debug/77b38d5cc5f5435767bcaf012b757131c3670f16 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_state.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_render.o: WatchApp/watchMenu/menu_render.c  .generated_files/flags/debug/f16c4664dcc6e3829cb50f6533f344e5e57fa706 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_render.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_render.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_render.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu_input.o: WatchApp/watchMenu/menu_input.c  .generated_files/flags/debug/6e34644364bb206aa74317c86ee90103a8fdbdab .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu_input.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/debug/68de924f90bf192e6179592e7308f71afe893ba3 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/debug/41e4093d27ffd479f8e8da11f9c0934f8fa699e3 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/debug/30707ca45fb6332599380e635b154ced82030fd .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -DDEBUG_MODE -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/System/where_was_i.o: System/where_was_i.s  .generated_files/flags/debug/4ec65a4ba8d59cde5f122d8bdcefc41fac662bf6 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/System/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  System/where_was_i.s  -o ${OBJECTDIR}/System/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_debug=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/System/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/System/where_was_i.o: System/where_was_i.s  .generated_files/flags/debug/bf457dd33bf5b7d3149b32aedc37ad73cdf6f5f1 .generated_files/flags/debug/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/where_was_i.o.d 
	@${RM} ${OBJECTDIR}/System/where_was_i.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  System/where_was_i.s  -o ${OBJECTDIR}/System/where_was_i.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_debug=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/System/where_was_i.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/CuriosityOledBase.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_debug=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
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
