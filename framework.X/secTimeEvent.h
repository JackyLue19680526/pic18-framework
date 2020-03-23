/* 
 * File:        secTimeEvent.h
 * Author:      Jacky
 * Comments:    time event related control for this project
 * Revision history: 
 *   2020/03/12 : Created
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_SEC_TIME_EVENT_H
#define	XC_HEADER_SEC_TIME_EVENT_H

#include <xc.h> // include processor files - each processor file is guarded.  
//
#include "projectConfig.h"
#include "mcc_generated_files/mcc.h"

//==============================================================================
// Define Area
//==============================================================================
//configuration, can be define at Top project-config.h
//  0 = OFF
//  1 = ON

//#define USE_HANDLER_IN_ISR_100MS    0
//#define USE_HANDLER_IN_ISR_1_S      0
//#define USE_HANDLER_IN_ISR_N_S      0
////if any of above five define is not 1, then should turn-on follow
//#define CHECK_TIME_EV_IN_MAIN_LOOP  1

//..............................................................................
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
#define set_100ms_timer_callback()  TMR0_SetInterruptHandler(timer_100ms_CallBack)

//For reset MCU
//we will using WDT. if stop clear WDT then MCU will reset after WDT timeout
//link to correct WDT-clear instruction here...
//#define Generic_Clear_WDT()     WATCHDOG_TimerClear()
#define Generic_Clear_WDT()    CLRWDT()

//define values.................................................................
#define TIMER3_1S_CNT           10
//
#define DELAY_5S_USE_1S         5
#define DELAY_7S_USE_1S         7
#define DELAY_10S_USE_1S        10
#define DELAY_15S_USE_1S        15
///// default N=10sec
#define DELAY_N_SECOND          DELAY_10S_USE_1S

//==============================================================================
// Public Types
//==============================================================================

typedef struct ST_timeEvent{
    //###########################
    // Data Member area
    //###########################
    bool    resetMCU; 
    
    //Timer
    uint8_t secCount;
    uint8_t Watting_100ms_Count;
    uint8_t Watting_1sec_Count;
    uint8_t Watting_Nsec_Count;
    uint8_t Tmr100msCount;
    
    //flag
    bool    isMs100;  //100ms
    bool    isSec1;   //1sec
    bool    isSecN;   //Nsec
        
    //###########################
    // Function Menmber area
    //###########################
    
    //for system waiting, (only ISR alive)
    void (*wait_Tsec)(uint8_t Tsec);
    void (*wait_T100ms)(uint8_t T100ms);
    
    //for reset MCU
    void (*setResetMcuFlag)();
    void (*clearResetMcuFlag)();
    
    //run time event in mainloop
    void (*checkInMainLoop)(); 
    
    // Set up call-back function for Event Handler
    void (*SetEventHandler_Run_100ms)(
            void (* eventHandler)(void), uint8_t i);
    void (*SetEventHandler_Run_1_sec)(
            void (* eventHandler)(void));
    void (*SetEventHandler_Run_N_sec)(
            void (* eventHandler)(void));
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

#endif	/* XC_HEADER_SEC_TIME_EVENT_H */

