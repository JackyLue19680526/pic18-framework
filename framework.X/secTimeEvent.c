/* 
 * File:        secTimeEvent.c
 * Author:      Jacky
 * Comments:    time event related control for this project
 * Revision history: 
 *   2020/03/12 : Created
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *         Usage     Notice 
 *  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 1) By project, Timer may link to different real timer
 * 2) We will set Timer interrupt Handler in tEV_init(), it links real 
 *    timer ISR as follow. and User only need to modify Header file
 *          set_100ms_timer_callback();
 * 3) User could add call-bck function at run time from main.c
 *    Typical usage is intial and setup call-back before main loop:
 *          tEV_init();
 *          tEV.SetEventHandler_Run_100ms(xxxx, 0);
 *          while(1){ //maim loop
 *              .....
 *          }
 */

//==============================================================================
//  Included header files 
//==============================================================================
#include "projectConfig.h"
//
#include "secTimeEvent.h"

//==============================================================================
// Public Data
//==============================================================================
timeEvent tEV;

//==============================================================================
// Private Macros
//==============================================================================
// for access data members
#define _resetMCU               tEV.resetMCU

#define _secCount               tEV.secCount
#define _Watting_100ms_Count    tEV.Watting_100ms_Count
#define _Watting_1sec_Count     tEV.Watting_1sec_Count
#define _Watting_Nsec_Count     tEV.Watting_Nsec_Count
#define _Tmr100msCount          tEV.Tmr100msCount

#define _isMs100                tEV.isMs100
#define _isSec1                 tEV.isSec1
#define _isSecN                 tEV.isSecN

//==============================================================================
// Private Data
//==============================================================================


//==============================================================================
// Private (local) function pointer HERE
//==============================================================================
//default is empty function here....

static void Default_Run_100MS() {}
static void Default_Run_1_sec() {}
static void Default_Run_N_sec() {}
//function pointer declear..
void (*Run_100MS[])(void) = {Default_Run_100MS, Default_Run_100MS, Default_Run_100MS};
void (*Run_1_SEC)(void) = Default_Run_1_sec;
void (*Run_N_SEC)(void) = Default_Run_N_sec;

//==============================================================================
// Private (local) functions
//==============================================================================

//---------------------------------------
//Summary : action for One sec period; (Timer related part)
//Remark  : Called by Timer ISR or event-check loop
//Return  : None
static void Runing_1sec() {
    DB_PROMPT_TIME_SEC_1();
    if(_Watting_1sec_Count>0)_Watting_1sec_Count--;
    //
    Run_1_SEC(); 
}
//---------------------------------------
//Summary : action for N sec period; (Timer related part)
//Remark  : Called by Timer ISR or event-check loop
//Return  : None
static void Runing_Nsec() {
    DB_PROMPT_TIME_SEC_N();
    if(_Watting_Nsec_Count>0)_Watting_Nsec_Count--;
    //
    Run_N_SEC();
}
//-----------------------------------------
//Summary : Timer call-back for every 100ms
//Return  : None
static void timer_100ms_CallBack(void) {
    _Tmr100msCount++; 
    if(_Tmr100msCount >= TIMER3_1S_CNT){
        _Tmr100msCount = 0;
        
        #if USE_HANDLER_IN_ISR_1_S == 1
        Runing_1sec();
        #else
        _isSec1 = true;
        #endif

        _secCount++;
        if (_secCount >= DELAY_N_SECOND) {
            _secCount = 0;
            
            #if USE_HANDLER_IN_ISR_N_S == 1
            Runing_Nsec();
            #else
            _isSecN = true;
            #endif
        }
    }
    if(_Watting_100ms_Count>0)_Watting_100ms_Count--;
    
    //WDT and reset-MCU
    if(!_resetMCU) Generic_Clear_WDT(); 
    
    #if USE_HANDLER_IN_ISR_100MS == 1
    Run_100MS[1](); 
    Run_100MS[0]();
    #else
    _isMs100 = true;
    #endif
}

//==============================================================================
// Private (member) functions
//==============================================================================

//---------------------------------------
//Summary : Wait some second, Blocking programm 
//Param   : T-second
//Return  : None
static void wait_Tsec(uint8_t Tsec) {
    _Watting_1sec_Count=Tsec;
    while(_Watting_1sec_Count>0)
    {
        //Just Block and waitting
    }   
}
//---------------------------------------
//Summary : Wait 100ms, Blocking programm 
//Param   : T-100ms
//Return  : None
static void wait_T100ms(uint8_t T100ms) {
    _Watting_100ms_Count=T100ms;
    while(_Watting_100ms_Count>0)
    {
        //Just Block and waitting
    }   
}
//-----------------------------------------
//Summary :  set flage for reset MCU
static void setResetMcuFlag() {
    DBT_printf("\n reset MCU !! \n");
    _resetMCU = true;
}
//-----------------------------------------
//Summary :  clear flage and dont reset MCU
static void clearResetMcuFlag() {
    _resetMCU = false;
}
//-----------------------------------------
//Summary: Checking Time-event flages in main loop
static void checkInMainLoop() {
    #if USE_HANDLER_IN_ISR_100MS != 1
    if(_isMs100) {
        Run_100MS[1]();
        Run_100MS[0]();
        _isMs100 = false;
    }
    #endif

    #if USE_HANDLER_IN_ISR_1_S != 1
    if(_isSec1) {
        Runing_1sec();
        _isSec1 = false;
    }
    #endif

     #if USE_HANDLER_IN_ISR_N_S != 1
    if(_isSecN) {
        Runing_Nsec();
        _isSecN = false;
    }
    #endif
}

//---------------------------------------
// Set up call-back function for Event Handler
static void SetEventHandler_Run_100ms(
            void (* eventHandler)(void), uint8_t i
){
    Run_100MS[i] = eventHandler;
}
static void SetEventHandler_Run_1_sec(
            void (* eventHandler)(void)
){
    Run_1_SEC = eventHandler;
}
static void SetEventHandler_Run_N_sec(
            void (* eventHandler)(void)
){
    Run_N_SEC = eventHandler;
}

//==============================================================================
// Public API functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//Return  : None
void tEV_init() {
    //timer callback link to real timer
    set_100ms_timer_callback();
    
    //..........................................
    //set default empty time event handler here
    //User could set again at top level main()
    SetEventHandler_Run_100ms(Default_Run_100MS,0);
    SetEventHandler_Run_100ms(Default_Run_100MS,1);
    SetEventHandler_Run_1_sec(Default_Run_1_sec);
    SetEventHandler_Run_N_sec(Default_Run_N_sec);
    
    //..........................................
    //initial data member
    _resetMCU = false;
    
    _secCount = 0;
    _Watting_100ms_Count = 0;
    _Watting_1sec_Count = 0;
    _Watting_Nsec_Count = 0;
    _Tmr100msCount = 0;
    
    _isMs100 = false;
    _isSec1 = false;
    _isSecN = false;
        
    //..........................................
    //initial fnction member (pointer) 
    tEV.wait_Tsec           = wait_Tsec;
    tEV.wait_T100ms         = wait_T100ms;
    
    tEV.setResetMcuFlag     = setResetMcuFlag;
    tEV.clearResetMcuFlag   = clearResetMcuFlag;
    
    tEV.checkInMainLoop     = checkInMainLoop;
    
    tEV.SetEventHandler_Run_100ms = SetEventHandler_Run_100ms;
    tEV.SetEventHandler_Run_1_sec = SetEventHandler_Run_1_sec;
    tEV.SetEventHandler_Run_N_sec = SetEventHandler_Run_N_sec;
}
