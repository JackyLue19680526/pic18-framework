/* 
 * File:        projectConfig.h
 * Author:      Jacky
 * Comments:    program configuration for this project
 * Revision history: 
 *   2019/12/24 : First version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_PROJECT_CONFIG_H
#define	XC_HEADER_PROJECT_CONFIG_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//=== Project Top CONFIG =======================================================

//=======================================
// Function define for GPIO pin related 
//=======================================

//=======================================
// Software modules related configration
//=======================================
// =0: not select
// =1: select
//time_event ....................
#define INCLUDE_SOFTWARE_RTC        0
#define INCLUDE_SYSTEM_TIME_MS      1
#define INCLUDE_CYCLE_DELAY_US      1
//
#define USE_HANDLER_IN_ISR_1MS      1
#define USE_HANDLER_IN_ISR_10MS     1
#define USE_HANDLER_IN_ISR_100MS    0
#define USE_HANDLER_IN_ISR_1_S      0
#define USE_HANDLER_IN_ISR_N_S      0
//if any of above five define is not 1, then should turn-on follow
#define CHECK_TIME_EV_IN_MAIN_LOOP  1

//in main.c
#define INCLUDE_SWITCH_IN_DBT       1
#define INCLUDE_TESTING_SPI         0
#define INCLUDE_TESTING_SPI_ALL     0

//=======================================
// Constant which may changing by Project
//=======================================

//OpModel------------------------12345678
#define MY_FIRMWARE_VER_STRING  "WFv1.00 "
#define MY_HARDWARE_VER_STRING  "WHv1.00 "

//UART 
//this should match the setting at MCC
#define MY_UART1_RX_BUFFER_ZISE     32
#define MY_UART2_RX_BUFFER_ZISE     32

//==============================================================================
// Debug Config
//==============================================================================
//Debug related configuration ....

//mark or un-mark HERE..........................................................
/*  for 1-second & N-second promt print
 *  also could change prompt here...
 */
#define DBP_SEC_1 
//#define DBP_SEC_N  

#ifdef DBP_SEC_1
#define DB_PROMPT_TIME_SEC_1() printf(".\n")
#else
#define DB_PROMPT_TIME_SEC_1() ((void)0)
#endif

#ifdef DBP_SEC_N
#define DB_PROMPT_TIME_SEC_N() printf(":\n")
#else
#define DB_PROMPT_TIME_SEC_N() ((void)0)
#endif

/* mark or un-mark HERE.........................................................
 * Top = Top level (also some important message)
 * 0 = myTimeEvent, ... etc main control messag 
 * 1 = 
 */
#define DEBUG_TOP
//#define DEBUG_0
//#define DEBUG_1
//#define DEBUG_2
//#define DEBUG_3
//#define DEBUG_4
//#define DEBUG_5
//#define DEBUG_6
//#define DEBUG_7
//#define DEBUG_8
//#define DEBUG_9
//#define DEBUG_10


//****************************************************
//Top level (basic , less debug message...)
#ifdef DEBUG_TOP
#define DBT_printf printf
#else
#define DBT_printf(format, args...) ((void)0)
#endif

//sub-module debug messages...
#ifdef DEBUG_0
#define DB0_printf printf
#else
#define DB0_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_1
#define DB1_printf printf
#else
#define DB1_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_2
#define DB2_printf printf
#else
#define DB2_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_3
#define DB3_printf printf
#else
#define DB3_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_4
#define DB4_printf printf
#else
#define DB4_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_5
#define DB5_printf printf
#else
#define DB5_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_6
#define DB6_printf printf
#else
#define DB6_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_7
#define DB7_printf printf
#else
#define DB7_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_8
#define DB8_printf printf
#
#else
#define DB8_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_9
#define DB9_printf printf
#else
#define DB9_printf(format, args...) ((void)0)
#endif

#ifdef DEBUG_10
#define DB10_printf printf
#else
#define DB10_printf(format, args...) ((void)0)
#endif



//==============================================================================
//Debug waveform switch
//==============================================================================
/* mark or un-mark HERE.........................................................
 * 0 : T0 = 
 *     T1 = 
 *     T2 = 
 */
//#define DB_WAV_0
//#define DB_WAV_1
//#define DB_WAV_2
//#define DB_WAV_3
//#define DB_WAV_4
//#define DB_WAV_5
//#define DB_WAV_6
//#define DB_WAV_7
//#define DB_WAV_8
//#define DB_WAV_9

//****************************************************
#ifdef DB_WAV_0
#define DV0_TEST2_H()     TEST2_SetHigh()
#define DV0_TEST2_L()     TEST2_SetLow()
#define DV0_TEST1_H()     TEST1_SetHigh()
#define DV0_TEST1_L()     TEST1_SetLow()
#define DV0_TEST0_H()     TEST0_SetHigh()
#define DV0_TEST0_L()     TEST0_SetLow()
#else
#define DV0_TEST2_H()     ((void)0)
#define DV0_TEST2_L()     ((void)0)
#define DV0_TEST1_H()     ((void)0)
#define DV0_TEST1_L()     ((void)0)
#define DV0_TEST0_H()     ((void)0)
#define DV0_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_1
#define DV1_TEST2_H()     TEST2_SetHigh()
#define DV1_TEST2_L()     TEST2_SetLow()
#define DV1_TEST1_H()     TEST1_SetHigh()
#define DV1_TEST1_L()     TEST1_SetLow()
#define DV1_TEST0_H()     TEST0_SetHigh()
#define DV1_TEST0_L()     TEST0_SetLow()
#else
#define DV1_TEST2_H()     ((void)0)
#define DV1_TEST2_L()     ((void)0)
#define DV1_TEST1_H()     ((void)0)
#define DV1_TEST1_L()     ((void)0)
#define DV1_TEST0_H()     ((void)0)
#define DV1_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_2
#define DV2_TEST2_H()     TEST2_SetHigh()
#define DV2_TEST2_L()     TEST2_SetLow()
#define DV2_TEST1_H()     TEST1_SetHigh()
#define DV2_TEST1_L()     TEST1_SetLow()
#define DV2_TEST0_H()     TEST0_SetHigh()
#define DV2_TEST0_L()     TEST0_SetLow()
#else
#define DV2_TEST2_H()     ((void)0)
#define DV2_TEST2_L()     ((void)0)
#define DV2_TEST1_H()     ((void)0)
#define DV2_TEST1_L()     ((void)0)
#define DV2_TEST0_H()     ((void)0)
#define DV2_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_3
#define DV3_TEST2_H()     TEST2_SetHigh()
#define DV3_TEST2_L()     TEST2_SetLow()
#define DV3_TEST1_H()     TEST1_SetHigh()
#define DV3_TEST1_L()     TEST1_SetLow()
#define DV3_TEST0_H()     TEST0_SetHigh()
#define DV3_TEST0_L()     TEST0_SetLow()
#else
#define DV3_TEST2_H()     ((void)0)
#define DV3_TEST2_L()     ((void)0)
#define DV3_TEST1_H()     ((void)0)
#define DV3_TEST1_L()     ((void)0)
#define DV3_TEST0_H()     ((void)0)
#define DV3_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_4
#define DV4_TEST2_H()     TEST2_SetHigh()
#define DV4_TEST2_L()     TEST2_SetLow()
#define DV4_TEST1_H()     TEST1_SetHigh()
#define DV4_TEST1_L()     TEST1_SetLow()
#define DV4_TEST0_H()     TEST0_SetHigh()
#define DV4_TEST0_L()     TEST0_SetLow()
#else
#define DV4_TEST2_H()     ((void)0)
#define DV4_TEST2_L()     ((void)0)
#define DV4_TEST1_H()     ((void)0)
#define DV4_TEST1_L()     ((void)0)
#define DV4_TEST0_H()     ((void)0)
#define DV4_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_5
#define DV5_TEST2_H()     TEST2_SetHigh()
#define DV5_TEST2_L()     TEST2_SetLow()
#define DV5_TEST1_H()     TEST1_SetHigh()
#define DV5_TEST1_L()     TEST1_SetLow()
#define DV5_TEST0_H()     TEST0_SetHigh()
#define DV5_TEST0_L()     TEST0_SetLow()
#else
#define DV5_TEST2_H()     ((void)0)
#define DV5_TEST2_L()     ((void)0)
#define DV5_TEST1_H()     ((void)0)
#define DV5_TEST1_L()     ((void)0)
#define DV5_TEST0_H()     ((void)0)
#define DV5_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_6
#define DV6_TEST2_H()     TEST2_SetHigh()
#define DV6_TEST2_L()     TEST2_SetLow()
#define DV6_TEST1_H()     TEST1_SetHigh()
#define DV6_TEST1_L()     TEST1_SetLow()
#define DV6_TEST0_H()     TEST0_SetHigh()
#define DV6_TEST0_L()     TEST0_SetLow()
#else
#define DV6_TEST2_H()     ((void)0)
#define DV6_TEST2_L()     ((void)0)
#define DV6_TEST1_H()     ((void)0)
#define DV6_TEST1_L()     ((void)0)
#define DV6_TEST0_H()     ((void)0)
#define DV6_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_7
#define DV7_TEST2_H()     TEST2_SetHigh()
#define DV7_TEST2_L()     TEST2_SetLow()
#define DV7_TEST1_H()     TEST1_SetHigh()
#define DV7_TEST1_L()     TEST1_SetLow()
#define DV7_TEST0_H()     TEST0_SetHigh()
#define DV7_TEST0_L()     TEST0_SetLow()
#else
#define DV7_TEST2_H()     ((void)0)
#define DV7_TEST2_L()     ((void)0)
#define DV7_TEST1_H()     ((void)0)
#define DV7_TEST1_L()     ((void)0)
#define DV7_TEST0_H()     ((void)0)
#define DV7_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_8
#define DV8_TEST2_H()     TEST2_SetHigh()
#define DV8_TEST2_L()     TEST2_SetLow()
#define DV8_TEST1_H()     TEST1_SetHigh()
#define DV8_TEST1_L()     TEST1_SetLow()
#define DV8_TEST0_H()     TEST0_SetHigh()
#define DV8_TEST0_L()     TEST0_SetLow()
#else
#define DV8_TEST2_H()     ((void)0)
#define DV8_TEST2_L()     ((void)0)
#define DV8_TEST1_H()     ((void)0)
#define DV8_TEST1_L()     ((void)0)
#define DV8_TEST0_H()     ((void)0)
#define DV8_TEST0_L()     ((void)0)
#endif

#ifdef DB_WAV_9
#define DV9_TEST2_H()     TEST2_SetHigh()
#define DV9_TEST2_L()     TEST2_SetLow()
#define DV9_TEST1_H()     TEST1_SetHigh()
#define DV9_TEST1_L()     TEST1_SetLow()
#define DV9_TEST0_H()     TEST0_SetHigh()
#define DV9_TEST0_L()     TEST0_SetLow()
#else
#define DV9_TEST2_H()     ((void)0)
#define DV9_TEST2_L()     ((void)0)
#define DV9_TEST1_H()     ((void)0)
#define DV9_TEST1_L()     ((void)0)
#define DV9_TEST0_H()     ((void)0)
#define DV9_TEST0_L()     ((void)0)
#endif

//==============================================================================
//Generic Bit operation related Macro 
//==============================================================================
#define BIT(n)          (1<<(n))
#define SET_BIT(x,n)    ((x)|=(1<<(n)))
#define CLR_BIT(x,n)    ((x)&=(~(1<<(n))))
#define CHK_BIT(x,n)    (((x)&(1<<(n)))!=0)
#define FLIP_BIT(x,n)   ((x)^=(1<<(n)))
//
#define LOW_BYTE(x)     ((uint8_t)((x)&0xFF))
#define HIGH_BYTE(x)    ((uint8_t)(((x)>>8)&0xFF))


#endif	/* XC_HEADER_PROJECT_CONFIG_H */

