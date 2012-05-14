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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/autofiles/usbdsc.o ${OBJECTDIR}/system/usb/usb9/usb9.o ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o ${OBJECTDIR}/system/usb/usbmmap.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system/usb/class/boot/boot.o
POSSIBLE_DEPFILES=${OBJECTDIR}/autofiles/usbdsc.o.d ${OBJECTDIR}/system/usb/usb9/usb9.o.d ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o.d ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o.d ${OBJECTDIR}/system/usb/usbmmap.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/system/usb/class/boot/boot.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/autofiles/usbdsc.o ${OBJECTDIR}/system/usb/usb9/usb9.o ${OBJECTDIR}/system/usb/usbctrltrf/usbctrltrf.o ${OBJECTDIR}/system/usb/usbdrv/usbdrv.o ${OBJECTDIR}/system/usb/usbmmap.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system/usb/class/boot/boot.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
	
${OBJECTDIR}/system/usb/class/boot/boot.o: system/usb/class/boot/boot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/class/boot 
	@${RM} ${OBJECTDIR}/system/usb/class/boot/boot.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/class/boot/boot.o   system/usb/class/boot/boot.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/class/boot/boot.o 
	
else
${OBJECTDIR}/autofiles/usbdsc.o: autofiles/usbdsc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/autofiles 
	@${RM} ${OBJECTDIR}/autofiles/usbdsc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/autofiles/usbdsc.o   autofiles/usbdsc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/autofiles/usbdsc.o 
	
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
	
${OBJECTDIR}/system/usb/class/boot/boot.o: system/usb/class/boot/boot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/system/usb/class/boot 
	@${RM} ${OBJECTDIR}/system/usb/class/boot/boot.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"." --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/system/usb/class/boot/boot.o   system/usb/class/boot/boot.c 
	@${DEP_GEN} -d ${OBJECTDIR}/system/usb/class/boot/boot.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "18f2550.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"dist/default/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.map" -u_EXTENDEDMODE -g -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PICKIT2=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "18f2550.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"dist/default/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.map" -u_EXTENDEDMODE -g -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/bootloader.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
