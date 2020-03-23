/* 
 * File:        myTimeEvent.h
 * Author:      Jacky
 * Comments:    time event related control for this project
 * Revision history: 
 *   2019/12/23 : Created
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TIME_EVENT_H
#define	XC_HEADER_TIME_EVENT_H

#include <xc.h> // include processor files - each processor file is guarded.  
//
#include "projectConfig.h"
//
#include "mcc_generated_files/mcc.h"

//==============================================================================
// Define Area
//==============================================================================
//configuration, can be define at Top project-config.h
//  0 = OFF
//  1 = ON

//#define INCLUDE_SOFTWARE_RTC    0
//#define INCLUDE_SYSTEM_TIME_MS  1
//#define INCLUDE_CYCLE_DELAY_US  1

//#define USE_HANDLER_IN_ISR_1MS      1
//#define USE_HANDLER_IN_ISR_10MS     1
//#define USE_HANDLER_IN_ISR_100MS    0
//#define USE_HANDLER_IN_ISR_1_S      0
//#define USE_HANDLER_IN_ISR_N_S      0
////if any of above five define is not 1, then should turn-on follow
//#define CHECK_TIME_EV_IN_MAIN_LOOP  1

//debug-print-hint, can change define at Top project-config.h
//#define DBP_SEC_1 
//#define DBP_SEC_N  
//#ifdef DBP_SEC_1
//#define DB_PROMPT_TIME_SEC_1() printf(".\n")
//#else
//#define DB_PROMPT_TIME_SEC_1() ((void)0)
//#endif
//#ifdef DBP_SEC_N
//#define DB_PROMPT_TIME_SEC_N() printf("|>\n")
//#else
//#define DB_PROMPT_TIME_SEC_N() ((void)0)
//#endif

//..............................................................................
//define link function..........................................................
//Notice that: this command maybe change by MCU-family
//   that's to said: in PIC18, PIC24... 
//   it maybe require different function,
//..............................................................................

//for real timer linkage
#define set_1ms_timer_callback()    TMR2_SetInterruptHandler(timer_1ms_CallBack)
#define set_10ms_timer_callback()   TMR3_SetInterruptHandler(timer_10ms_CallBack)
#define set_100ms_timer_callback()  TMR0_SetInterruptHandler(timer_100ms_CallBack)

//For reset MCU
//we will using WDT. if stop clear WDT then MCU will reset after WDT timeout
//link to correct WDT-clear instruction here...
//#define Generic_Clear_WDT()     WATCHDOG_TimerClear()
#define Generic_Clear_WDT()     CLRWDT()

//for random seed from timer
//#define Generic_SeedFromTimer() TMR1_Counter16BitGet() 
#define Generic_SeedFromTimer() TMR2_ReadTimer()

//define values.................................................................
#define TIMER3_1S_CNT           10
//
#define DELAY_5S_USE_1S         5
#define DELAY_7S_USE_1S         7
#define DELAY_10S_USE_1S        10
#define DELAY_15S_USE_1S        15
///// default N=10sec
#define DELAY_N_SECOND          DELAY_10S_USE_1S

//cycle delay----------------...................................................
//Notice 1: Test pin location may change by different project
//Notice 2: Tunning define-value by measure waveform at development-stage.
//PS: Current setting is tunning for 48mhz system clock
#if INCLUDE_CYCLE_DELAY_US > 0
#define DELAY_TEST_PIN_Set_H()  TEST0_SetHigh()
#define DELAY_TEST_PIN_Set_L()  TEST0_SetLow()
#define DELAY_50US_CNT          4
#define DELAY_50US_CYL          18
#endif


//==============================================================================
// Public Types
//==============================================================================
typedef struct ST_DateTimeType {
        int16_t   Y;  //year   
        uint8_t   M;  //month
        uint8_t   D;  //day
        uint8_t   H;  //hour
        uint8_t   m;  //min
}DateTimeType;

typedef struct ST_EventFalges {
        bool   ms_0001;  //1ms  
        bool   ms_0010;  //10ms 
        bool   ms_0100;  //100ms 
        bool   ms_1000;  //1 sec
        bool   ms_N000;  //N sec
}EventFlags;

typedef struct ST_timeEvent{
    //###########################
    // Data Member area
    //###########################
    bool        resetMCU; 
    
    //Timer
    uint8_t     NSecondCount;
    uint8_t     Watting_100ms_Count;
    uint16_t    Watting_1sec_Count;
    uint16_t    Watting_Nsec_Count;
    uint8_t     Tmr1Count;
    uint16_t    Tmr2Count;
    uint8_t     Tmr3Count;
    
    //time event flag
    EventFlags  is; 
    
    #if INCLUDE_SYSTEM_TIME_MS > 0
    uint32_t System_MsCount;
    uint32_t tMarker;
    #endif

    #if INCLUDE_SOFTWARE_RTC > 0
    uint8_t SW_RTC_sec;
    #endif
     
    //###########################
    // Function Menmber area
    //###########################
    
    //for system waiting, (only ISR alive)
    void (*wait_Tsec_Block)(uint16_t Tsec);
    void (*wait_T100ms)(uint8_t T100ms);
    
    //for reset MCU
    void (*setResetMcuFlag)();
    void (*clearResetMcuFlag)();
    
    //for time event flages
    void (*checkInMainLoop)();  
    
    //for random nuber
    void (*random_seed_initial)();
    int (*random)(int low, int up);
    
    //Set up call-back function for Event Handler
    void (*SetEventHandler_Run_1ms)(
            void (* eventHandler)(void),
            uint8_t i);
    void (*SetEventHandler_Run_10ms)(
            void (* eventHandler)(void),
            uint8_t i);
    void (*SetEventHandler_Run_100ms)(
            void (* eventHandler)(void),
            uint8_t i);
    void (*SetEventHandler_Run_1_sec)(
            void (* eventHandler)(void));
    void (*SetEventHandler_Run_N_sec)(
            void (* eventHandler)(void));

    #if INCLUDE_CYCLE_DELAY_US >0
    void (*DelayInCycle)(uint8_t cycle);
    void (*delay_in_50us)(uint16_t us);
    void (*io_test_delay_us)();
    #endif

    #if INCLUDE_SYSTEM_TIME_MS > 0  
    uint32_t (*millis)(void); 
    uint32_t (*diff_millis)(uint32_t TimeMarker);
    void (*delay_in_ms)(int ms);
    #endif    
}timeEvent;

//==============================================================================
// Public Data
//==============================================================================
extern timeEvent tEV;

//==============================================================================
// Public API Functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//          We will also initial Timer calback functions 
//Return  : None
void tEV_init();


#endif	/* XC_HEADER_TIME_EVENT_H */

