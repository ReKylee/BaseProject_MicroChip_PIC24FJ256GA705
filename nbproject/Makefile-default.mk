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
SOURCEFILES_QUOTED_IF_SPACED=accel3Driver/ACCEL3.c adcDriver/ADC.c i2cDriver/I2C.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c switchDriver/Switch.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s WatchApp/pomodoroTimer/pomodoro.c WatchApp/shared/watch_state.c WatchApp/watchCore/alarm.c WatchApp/watchCore/timekeeper.c WatchApp/watchFaces/analog_face.c WatchApp/watchFaces/binary_face.c WatchApp/watchFaces/digital_face.c WatchApp/watchInput/accel_input.c WatchApp/watchInput/buttons.c WatchApp/watchInput/potentiometer.c WatchApp/watchMenu/menu.c Timers/Timers.c WatchApp/app_init.c WatchApp/watchManagers/app_display_manager.c WatchApp/watchManagers/app_input_handler.c WatchApp/watchManagers/app_time_manager.c main.c WatchApp/watch_main.c WatchApp/watchFaces/alarm_face.c WatchApp/watchFaces/watch_face_common.c WatchApp/watchFaces/watch_face_geometry.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/accel3Driver/ACCEL3.o ${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/i2cDriver/I2C.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/switchDriver/Switch.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o ${OBJECTDIR}/WatchApp/shared/watch_state.o ${OBJECTDIR}/WatchApp/watchCore/alarm.o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o ${OBJECTDIR}/WatchApp/watchInput/buttons.o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o ${OBJECTDIR}/WatchApp/watchMenu/menu.o ${OBJECTDIR}/Timers/Timers.o ${OBJECTDIR}/WatchApp/app_init.o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o ${OBJECTDIR}/main.o ${OBJECTDIR}/WatchApp/watch_main.o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o
POSSIBLE_DEPFILES=${OBJECTDIR}/accel3Driver/ACCEL3.o.d ${OBJECTDIR}/adcDriver/ADC.o.d ${OBJECTDIR}/i2cDriver/I2C.o.d ${OBJECTDIR}/ledDriver/LED_tests.o.d ${OBJECTDIR}/oledDriver/oledC.o.d ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o.d ${OBJECTDIR}/oledDriver/oledC_shapes.o.d ${OBJECTDIR}/spiDriver/spi1_driver.o.d ${OBJECTDIR}/switchDriver/Switch.o.d ${OBJECTDIR}/System/clock.o.d ${OBJECTDIR}/System/delay.o.d ${OBJECTDIR}/System/interrupt_manager.o.d ${OBJECTDIR}/System/pin_manager.o.d ${OBJECTDIR}/System/system.o.d ${OBJECTDIR}/System/traps.o.d ${OBJECTDIR}/System/where_was_i.o.d ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d ${OBJECTDIR}/WatchApp/shared/watch_state.o.d ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d ${OBJECTDIR}/Timers/Timers.o.d ${OBJECTDIR}/WatchApp/app_init.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/WatchApp/watch_main.o.d ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/accel3Driver/ACCEL3.o ${OBJECTDIR}/adcDriver/ADC.o ${OBJECTDIR}/i2cDriver/I2C.o ${OBJECTDIR}/ledDriver/LED_tests.o ${OBJECTDIR}/oledDriver/oledC.o ${OBJECTDIR}/oledDriver/oledC_shapeHandler.o ${OBJECTDIR}/oledDriver/oledC_shapes.o ${OBJECTDIR}/spiDriver/spi1_driver.o ${OBJECTDIR}/switchDriver/Switch.o ${OBJECTDIR}/System/clock.o ${OBJECTDIR}/System/delay.o ${OBJECTDIR}/System/interrupt_manager.o ${OBJECTDIR}/System/pin_manager.o ${OBJECTDIR}/System/system.o ${OBJECTDIR}/System/traps.o ${OBJECTDIR}/System/where_was_i.o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o ${OBJECTDIR}/WatchApp/shared/watch_state.o ${OBJECTDIR}/WatchApp/watchCore/alarm.o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o ${OBJECTDIR}/WatchApp/watchInput/buttons.o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o ${OBJECTDIR}/WatchApp/watchMenu/menu.o ${OBJECTDIR}/Timers/Timers.o ${OBJECTDIR}/WatchApp/app_init.o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o ${OBJECTDIR}/main.o ${OBJECTDIR}/WatchApp/watch_main.o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o

# Source Files
SOURCEFILES=accel3Driver/ACCEL3.c adcDriver/ADC.c i2cDriver/I2C.c ledDriver/LED_tests.c oledDriver/oledC.c oledDriver/oledC_shapeHandler.c oledDriver/oledC_shapes.c spiDriver/spi1_driver.c switchDriver/Switch.c System/clock.c System/delay.c System/interrupt_manager.c System/pin_manager.c System/system.c System/traps.c System/where_was_i.s WatchApp/pomodoroTimer/pomodoro.c WatchApp/shared/watch_state.c WatchApp/watchCore/alarm.c WatchApp/watchCore/timekeeper.c WatchApp/watchFaces/analog_face.c WatchApp/watchFaces/binary_face.c WatchApp/watchFaces/digital_face.c WatchApp/watchInput/accel_input.c WatchApp/watchInput/buttons.c WatchApp/watchInput/potentiometer.c WatchApp/watchMenu/menu.c Timers/Timers.c WatchApp/app_init.c WatchApp/watchManagers/app_display_manager.c WatchApp/watchManagers/app_input_handler.c WatchApp/watchManagers/app_time_manager.c main.c WatchApp/watch_main.c WatchApp/watchFaces/alarm_face.c WatchApp/watchFaces/watch_face_common.c WatchApp/watchFaces/watch_face_geometry.c



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
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/default/234851ef00960967dac5f883b0543c23bedba35c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/26da2ef0610a4e8c6f3148e258fd1b9ce5dde94c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/default/7f9c6ffc4230650d19e44f5e7233d467ee100223 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/default/7a16ba9e36fe14e5001cfb5d4883ad900e4461d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/default/25f43f259695c068d22a890474982f9b7d2842dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/default/49e2665bc4a9a8920549e4516563a2b3f179afde .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/default/39b9dcaee5fc303ba1d17cd30891cde6cd8aa6bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/default/4d62d615692929f50304f0cccc36b23279ac8026 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/default/58c80db4078e6feeb67cdbe7d5595e3da0bb5132 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/default/ac75d0a8158e87d16a1988172a5cc80c9d1cbfcc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/default/e3df2f79939bcf9702e5427be7c501b21009c77e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/default/8d0d70e052564737b105762a3e1c8b0f66d57b39 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/default/d01f3b61946877e04b384d20c1dbafd3b941561b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/default/3cff8f89a4671c1e276eb6d56b74137b299a8e63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/default/d20c04ed8bc4868385f91b6758d8b53fd5404e5d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/default/e0bf5926ed1f48b210179becfe19ae1315f7d385 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/default/210fd2306db70ba2a0707cfe07294fa0fa55e8e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/default/af42309cd352a6cc87a13cc80bc3ac9432cf6cc1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/default/aa91f0662fb63acf4b1f3b40d52fe3112f3d1142 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/default/3941cc04b85d5cca9bc75a66506bd7fa79582672 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4b1addb59371ffc563aebc1ccb39accaeff02fc2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/default/aeba45439f6a1f8dce112555f28c2dae104d6e2f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/default/786964f1125d7bcb63e0f6d5fa646f9220985d65 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/default/5ff01803f907e211541bbc1bb1763b6a38b10fc9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/default/e9a5b225567f1fbce2becfc47c037146abaee333 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/accel3Driver/ACCEL3.o: accel3Driver/ACCEL3.c  .generated_files/flags/default/36478faf6c3301c6b2c2194516e965c2be03a8e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/accel3Driver" 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o.d 
	@${RM} ${OBJECTDIR}/accel3Driver/ACCEL3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  accel3Driver/ACCEL3.c  -o ${OBJECTDIR}/accel3Driver/ACCEL3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel3Driver/ACCEL3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adcDriver/ADC.o: adcDriver/ADC.c  .generated_files/flags/default/b4efa2508eda2fa35c3f586458e8fbc277578713 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adcDriver" 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o.d 
	@${RM} ${OBJECTDIR}/adcDriver/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adcDriver/ADC.c  -o ${OBJECTDIR}/adcDriver/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adcDriver/ADC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cDriver/I2C.o: i2cDriver/I2C.c  .generated_files/flags/default/c3b9ae819fe8496dd85341792dd866b92f7afeef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/i2cDriver" 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o.d 
	@${RM} ${OBJECTDIR}/i2cDriver/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cDriver/I2C.c  -o ${OBJECTDIR}/i2cDriver/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cDriver/I2C.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	
${OBJECTDIR}/switchDriver/Switch.o: switchDriver/Switch.c  .generated_files/flags/default/47b29a2adc1adbe8ad838556490134e57b716f95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/switchDriver" 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o.d 
	@${RM} ${OBJECTDIR}/switchDriver/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  switchDriver/Switch.c  -o ${OBJECTDIR}/switchDriver/Switch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/switchDriver/Switch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
	
${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o: WatchApp/pomodoroTimer/pomodoro.c  .generated_files/flags/default/fffa3a6aa3038cb0dd9ef3c5b6c2708c745a6984 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/pomodoroTimer" 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/pomodoroTimer/pomodoro.c  -o ${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/pomodoroTimer/pomodoro.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/shared/watch_state.o: WatchApp/shared/watch_state.c  .generated_files/flags/default/4810e8711e84b3d3ff1b82af435ddb64082b2970 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/shared" 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/shared/watch_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/shared/watch_state.c  -o ${OBJECTDIR}/WatchApp/shared/watch_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/shared/watch_state.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/alarm.o: WatchApp/watchCore/alarm.c  .generated_files/flags/default/3287371568cc4d08cad40066c1ede07f95dd8779 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/alarm.c  -o ${OBJECTDIR}/WatchApp/watchCore/alarm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/alarm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchCore/timekeeper.o: WatchApp/watchCore/timekeeper.c  .generated_files/flags/default/48358b3c874c31f38bb5335cf83c2f46960c188b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchCore" 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchCore/timekeeper.c  -o ${OBJECTDIR}/WatchApp/watchCore/timekeeper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchCore/timekeeper.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/analog_face.o: WatchApp/watchFaces/analog_face.c  .generated_files/flags/default/2dfe3d45d06d98a6cc1d6e245531b2c17f9f6883 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/analog_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/analog_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/analog_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/binary_face.o: WatchApp/watchFaces/binary_face.c  .generated_files/flags/default/95cbd3827ae3d08ffe36462e1e066cf36745cb6e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/binary_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/binary_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/binary_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/digital_face.o: WatchApp/watchFaces/digital_face.c  .generated_files/flags/default/db749a19e6cdeb51faba02574ee71b008ffe4d80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/digital_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/digital_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/digital_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/accel_input.o: WatchApp/watchInput/accel_input.c  .generated_files/flags/default/b38a0c3d5e725eae8dc45dee0ee9d348c0ab9aca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/accel_input.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/accel_input.c  -o ${OBJECTDIR}/WatchApp/watchInput/accel_input.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/accel_input.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/buttons.o: WatchApp/watchInput/buttons.c  .generated_files/flags/default/9af880bcbfc34dda353a9a907a00bf41c5638d19 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/buttons.c  -o ${OBJECTDIR}/WatchApp/watchInput/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/buttons.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchInput/potentiometer.o: WatchApp/watchInput/potentiometer.c  .generated_files/flags/default/453ea8030aedddbe7678009bbe77f56d7c7f72d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchInput" 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchInput/potentiometer.c  -o ${OBJECTDIR}/WatchApp/watchInput/potentiometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchInput/potentiometer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchMenu/menu.o: WatchApp/watchMenu/menu.c  .generated_files/flags/default/3f8f13441cf073239060a3fbd621ab06efab7624 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchMenu" 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchMenu/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchMenu/menu.c  -o ${OBJECTDIR}/WatchApp/watchMenu/menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchMenu/menu.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timers/Timers.o: Timers/Timers.c  .generated_files/flags/default/b8478c977633c843a9538775759ff1365ef24690 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Timers" 
	@${RM} ${OBJECTDIR}/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timers/Timers.c  -o ${OBJECTDIR}/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/app_init.o: WatchApp/app_init.c  .generated_files/flags/default/bfc359453585dfd31110243142f1e8e9863c5d62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/app_init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/app_init.c  -o ${OBJECTDIR}/WatchApp/app_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/app_init.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o: WatchApp/watchManagers/app_display_manager.c  .generated_files/flags/default/fc3a878fd32f2428cfb8e5160dd71fbfe15ce2df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_display_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_display_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o: WatchApp/watchManagers/app_input_handler.c  .generated_files/flags/default/a8f05b32442c6cab742e98284b4f4fef244ee74 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_input_handler.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_input_handler.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o: WatchApp/watchManagers/app_time_manager.c  .generated_files/flags/default/fd74e260b19c460d6ccdcaac42fff0463d462425 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchManagers" 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchManagers/app_time_manager.c  -o ${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchManagers/app_time_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/d29791c61f6db6483700fa87ec7415f027fed6fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watch_main.o: WatchApp/watch_main.c  .generated_files/flags/default/878dfa593f631b149c46b0fb71e16815d0db1e6e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp" 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watch_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watch_main.c  -o ${OBJECTDIR}/WatchApp/watch_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watch_main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o: WatchApp/watchFaces/alarm_face.c  .generated_files/flags/default/a959859e0e720ebde952472927084bcb49e01cae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/alarm_face.c  -o ${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/alarm_face.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o: WatchApp/watchFaces/watch_face_common.c  .generated_files/flags/default/9f337b16f256ff8357de71f88430f588084480cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_common.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_common.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o: WatchApp/watchFaces/watch_face_geometry.c  .generated_files/flags/default/559c487fd2e9c8847c7b9b9654ea3c2206be1b71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/WatchApp/watchFaces" 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d 
	@${RM} ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  WatchApp/watchFaces/watch_face_geometry.c  -o ${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/WatchApp/watchFaces/watch_face_geometry.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"bsp" -DFCY=4000000 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
