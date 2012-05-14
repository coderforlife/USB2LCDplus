#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/autofiles/usbdsc.o ${OBJECTDIR}/lcd/busyxlcd.o ${OBJECTDIR}/lcd/openxlcd.o ${OBJECTDIR}/lcd/putrxlcd.o ${OBJECTDIR}/lcd/putsxlcd.o ${OBJECTDIR}/lcd/readaddr.o ${OBJECTDIR}/lcd/readdata.o ${OBJECTDIR}/lcd/setcgram.o ${OBJECTDIR}/lcd/setddram.o ${OBJECTDIR}/lcd/wcmdxlcd.o ${OBJECTDIR}/lcd/writdata.o ${OBJECTDIR}/system/interrupt/interrupt.o ${OBJECTDIR}/system/usb/class/cdc/cdc.o ${OBJECTDIR}/system/usb/usb9/usb9.o ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o ${OBJECTDIR}/system/usb/usbmmap.o ${OBJECTDIR}/main.o ${OBJECTDIR}/user/user.o ${OBJECTDIR}/lcd/senddataxlcd.o
POSSIBLE_DEPFILES=${OBJECTDIR}/autofiles/usbdsc.o.d ${OBJECTDIR}/lcd/busyxlcd.o.d ${OBJECTDIR}/lcd/openxlcd.o.d ${OBJECTDIR}/lcd/putrxlcd.o.d ${OBJECTDIR}/lcd/putsxlcd.o.d ${OBJECTDIR}/lcd/readaddr.o.d ${OBJECTDIR}/lcd/readdata.o.d ${OBJECTDIR}/lcd/setcgram.o.d ${OBJECTDIR}/lcd/setddram.o.d ${OBJECTDIR}/lcd/wcmdxlcd.o.d ${OBJECTDIR}/lcd/writdata.o.d ${OBJECTDIR}/system/interrupt/interrupt.o.d ${OBJECTDIR}/system/usb/class/cdc/cdc.o.d ${OBJECTDIR}/system/usb/usb9/usb9.o.d ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o.d ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o.d ${OBJECTDIR}/system/usb/usbmmap.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/user/user.o.d ${OBJECTDIR}/lcd/senddataxlcd.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/autofiles/usbdsc.o ${OBJECTDIR}/lcd/busyxlcd.o ${OBJECTDIR}/lcd/openxlcd.o ${OBJECTDIR}/lcd/putrxlcd.o ${OBJECTDIR}/lcd/putsxlcd.o ${OBJECTDIR}/lcd/readaddr.o ${OBJECTDIR}/lcd/readdata.o ${OBJECTDIR}/lcd/setcgram.o ${OBJECTDIR}/lcd/setddram.o ${OBJECTDIR}/lcd/wcmdxlcd.o ${OBJECTDIR}/lcd/writdata.o ${OBJECTDIR}/system/interrupt/interrupt.o ${OBJECTDIR}/system/usb/class/cdc/cdc.o ${OBJECTDIR}/system/usb/usb9/usb9.o ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o ${OBJECTDIR}/system/usb/usbmmap.o ${OBJECTDIR}/main.o ${OBJECTDIR}/user/user.o ${OBJECTDIR}/lcd/senddataxlcd.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F2550
MP_PROCESSOR_OPTION_LD=18f2550
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x3f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/autofiles/usbdsc.o: autofiles/usbdsc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/autofiles 
	@${RM} ${OBJECTDIR}/autofiles/usbdsc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/autofiles/usbdsc.o   autofiles/usbdsc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/autofiles/usbdsc.o 
	
${OBJECTDIR}/lcd/busyxlcd.o: lcd/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/busyxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/busyxlcd.o   lcd/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/busyxlcd.o 
	
${OBJECTDIR}/lcd/openxlcd.o: lcd/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/openxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/openxlcd.o   lcd/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/openxlcd.o 
	
${OBJECTDIR}/lcd/putrxlcd.o: lcd/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/putrxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/putrxlcd.o   lcd/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/putrxlcd.o 
	
${OBJECTDIR}/lcd/putsxlcd.o: lcd/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/putsxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/putsxlcd.o   lcd/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/putsxlcd.o 
	
${OBJECTDIR}/lcd/readaddr.o: lcd/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/readaddr.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/readaddr.o   lcd/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/readaddr.o 
	
${OBJECTDIR}/lcd/readdata.o: lcd/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/readdata.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/readdata.o   lcd/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/readdata.o 
	
${OBJECTDIR}/lcd/setcgram.o: lcd/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/setcgram.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/setcgram.o   lcd/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/setcgram.o 
	
${OBJECTDIR}/lcd/setddram.o: lcd/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/setddram.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/setddram.o   lcd/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/setddram.o 
	
${OBJECTDIR}/lcd/wcmdxlcd.o: lcd/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/wcmdxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/wcmdxlcd.o   lcd/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/wcmdxlcd.o 
	
${OBJECTDIR}/lcd/writdata.o: lcd/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/writdata.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/writdata.o   lcd/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/writdata.o 
	
${OBJECTDIR}/system/interrupt/interrupt.o: system/interrupt/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/interrupt 
	@${RM} ${OBJECTDIR}/system/interrupt/interrupt.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/interrupt/interrupt.o   system/interrupt/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/interrupt/interrupt.o 
	
${OBJECTDIR}/system/usb/class/cdc/cdc.o: system/usb/class/cdc/cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/class/cdc 
	@${RM} ${OBJECTDIR}/system/usb/class/cdc/cdc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/class/cdc/cdc.o   system/usb/class/cdc/cdc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/class/cdc/cdc.o 
	
${OBJECTDIR}/system/usb/usb9/usb9.o: system/usb/usb9/usb9.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/usb9 
	@${RM} ${OBJECTDIR}/system/usb/usb9/usb9.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usb9/usb9.o   system/usb/usb9/usb9.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usb9/usb9.o 
	
${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o: system/usb/usbctrltrf/usbctrltrf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/usbctrltrf 
	@${RM} ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o   system/usb/usbctrltrf/usbctrltrf.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o 
	
${OBJECTDIR}/system/usb/usbdrv/usbdrv.o: system/usb/usbdrv/usbdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/usbdrv 
	@${RM} ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o   system/usb/usbdrv/usbdrv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o 
	
${OBJECTDIR}/system/usb/usbmmap.o: system/usb/usbmmap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb 
	@${RM} ${OBJECTDIR}/system/usb/usbmmap.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usbmmap.o   system/usb/usbmmap.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usbmmap.o 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	
${OBJECTDIR}/user/user.o: user/user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/user 
	@${RM} ${OBJECTDIR}/user/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/user/user.o   user/user.c 
	@${DEP_GEN} -d ${OBJECTDIR}/user/user.o 
	
${OBJECTDIR}/lcd/senddataxlcd.o: lcd/senddataxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/senddataxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/senddataxlcd.o   lcd/senddataxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/senddataxlcd.o 
	
else
${OBJECTDIR}/autofiles/usbdsc.o: autofiles/usbdsc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/autofiles 
	@${RM} ${OBJECTDIR}/autofiles/usbdsc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/autofiles/usbdsc.o   autofiles/usbdsc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/autofiles/usbdsc.o 
	
${OBJECTDIR}/lcd/busyxlcd.o: lcd/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/busyxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/busyxlcd.o   lcd/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/busyxlcd.o 
	
${OBJECTDIR}/lcd/openxlcd.o: lcd/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/openxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/openxlcd.o   lcd/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/openxlcd.o 
	
${OBJECTDIR}/lcd/putrxlcd.o: lcd/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/putrxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/putrxlcd.o   lcd/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/putrxlcd.o 
	
${OBJECTDIR}/lcd/putsxlcd.o: lcd/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/putsxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/putsxlcd.o   lcd/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/putsxlcd.o 
	
${OBJECTDIR}/lcd/readaddr.o: lcd/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/readaddr.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/readaddr.o   lcd/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/readaddr.o 
	
${OBJECTDIR}/lcd/readdata.o: lcd/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/readdata.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/readdata.o   lcd/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/readdata.o 
	
${OBJECTDIR}/lcd/setcgram.o: lcd/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/setcgram.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/setcgram.o   lcd/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/setcgram.o 
	
${OBJECTDIR}/lcd/setddram.o: lcd/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/setddram.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/setddram.o   lcd/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/setddram.o 
	
${OBJECTDIR}/lcd/wcmdxlcd.o: lcd/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/wcmdxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/wcmdxlcd.o   lcd/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/wcmdxlcd.o 
	
${OBJECTDIR}/lcd/writdata.o: lcd/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/writdata.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/writdata.o   lcd/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/writdata.o 
	
${OBJECTDIR}/system/interrupt/interrupt.o: system/interrupt/interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/interrupt 
	@${RM} ${OBJECTDIR}/system/interrupt/interrupt.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/interrupt/interrupt.o   system/interrupt/interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/interrupt/interrupt.o 
	
${OBJECTDIR}/system/usb/class/cdc/cdc.o: system/usb/class/cdc/cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/class/cdc 
	@${RM} ${OBJECTDIR}/system/usb/class/cdc/cdc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/class/cdc/cdc.o   system/usb/class/cdc/cdc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/class/cdc/cdc.o 
	
${OBJECTDIR}/system/usb/usb9/usb9.o: system/usb/usb9/usb9.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/usb9 
	@${RM} ${OBJECTDIR}/system/usb/usb9/usb9.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usb9/usb9.o   system/usb/usb9/usb9.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usb9/usb9.o 
	
${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o: system/usb/usbctrltrf/usbctrltrf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/usbctrltrf 
	@${RM} ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o   system/usb/usbctrltrf/usbctrltrf.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o 
	
${OBJECTDIR}/system/usb/usbdrv/usbdrv.o: system/usb/usbdrv/usbdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/usbdrv 
	@${RM} ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o   system/usb/usbdrv/usbdrv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o 
	
${OBJECTDIR}/system/usb/usbmmap.o: system/usb/usbmmap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb 
	@${RM} ${OBJECTDIR}/system/usb/usbmmap.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/usbmmap.o   system/usb/usbmmap.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/usbmmap.o 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	
${OBJECTDIR}/user/user.o: user/user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/user 
	@${RM} ${OBJECTDIR}/user/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/user/user.o   user/user.c 
	@${DEP_GEN} -d ${OBJECTDIR}/user/user.o 
	
${OBJECTDIR}/lcd/senddataxlcd.o: lcd/senddataxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lcd 
	@${RM} ${OBJECTDIR}/lcd/senddataxlcd.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd/senddataxlcd.o   lcd/senddataxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd/senddataxlcd.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "18f2550.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"dist/default/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.map" -u_EXTENDEDMODE -g -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PICKIT2=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "18f2550.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"dist/default/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.map" -u_EXTENDEDMODE -g -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB2LCD.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
