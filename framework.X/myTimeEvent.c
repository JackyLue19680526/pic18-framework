/* 
 * File:        myTimeEvent.h
 * Author:      Jacky
 * Comments:    time event related control for this project
 * Revision history: 
 *   2019/12/23 : Created
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *         Usage     Notice 
 *  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 1) By project, Timer may link to different real timer
 * 2) We will set Timer interrupt Handler in tEV_init(), it links real 
 *    timer ISR as follow. and User only need to modify Header file
 *          set_1ms_timer_callback();
 *          set_10ms_timer_callback();
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
#include "myTimeEvent.h"
//
#include "mcc_generated_files/mcc.h"


//==============================================================================
// Public Data
//==============================================================================
timeEvent tEV;

//===========================================
// Private Macros
//===========================================
// for access data members
#define _resetMCU               tEV.resetMCU
#define _NSecondCount           tEV.NSecondCount
#define _Watting_100ms_Count    tEV.Watting_100ms_Count
#define _Watting_1sec_Count     tEV.Watting_1sec_Count
#define _Watting_Nsec_Count     tEV.Watting_Nsec_Count
#define _Tmr1Count              tEV.Tmr1Count
#define _Tmr2Count              tEV.Tmr2Count
#define _Tmr3Count              tEV.Tmr3Count
#define _is                     tEV.is

#if INCLUDE_SYSTEM_TIME_MS > 0
#define _System_MsCount         tEV.System_MsCount
#endif

#if INCLUDE_SOFTWARE_RTC > 0
#define _SW_RTC_sec             tEV.SW_RTC_sec
#endif

//==============================================================================
// Private Data
//==============================================================================

//==============================================================================
// Private function pointer HERE
//==============================================================================
// default is empty function here....
void Default_Run_1MS() {}
void Default_Run_10MS() {}
void Default_Run_100MS() {}
static void Default_Run_1_sec() {}
static void Default_Run_N_sec() {}
// function pointer declear..
void (*Run_1MS[])(void) = {Default_Run_1MS, Default_Run_1MS};
void (*Run_10MS[])(void) = {Default_Run_10MS, Default_Run_10MS};
void (*Run_100MS[])(void) = {Default_Run_100MS, Default_Run_100MS};
void (*Run_1_SEC)(void) = Default_Run_1_sec;
void (*Run_N_SEC)(void) = Default_Run_N_sec;

//==============================================================================
// Private (local) functions
//==============================================================================

//-----------------------------------------
//Summary : action for One sec period; (Timer related part)
//Remark  : Called by Timer ISR or event-check loop
//Return  : None
static void Runing_1sec() {
    DB_PROMPT_TIME_SEC_1();

    if(_Watting_1sec_Count>0)_Watting_1sec_Count--;
    
    #if INCLUDE_SOFTWARE_RTC > 0
    Inc1secRTC();
    #endif

    Run_1_SEC();
}
//-----------------------------------------
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
//Summary : Timer call-back for every 1ms
//Return  : None
static void timer_1ms_CallBack(void) {
    _Tmr1Count++;
       
    #if INCLUDE_SYSTEM_TIME_MS > 0
    _System_MsCount++;
    #endif

    #if USE_HANDLER_IN_ISR_1MS == 1
    Run_1MS[1]();
    Run_1MS[0]();
    #else
    _is.ms_0001 = true;
    #endif
}
//-----------------------------------------
//Summary : Timer call-back for every 10ms
//Return  : None
static void timer_10ms_CallBack(void) {
    _Tmr2Count++; 
    
    #if USE_HANDLER_IN_ISR_10MS == 1
    Run_10MS[1](); 
    Run_10MS[0](); 
    #else
    _is.ms_0010 = true;
    #endif
}
//-----------------------------------------
//Summary : Timer call-back for every 100ms
//Return  : None
static void timer_100ms_CallBack(void) {
    _Tmr3Count++;
    
    if(_Tmr3Count >= TIMER3_1S_CNT){
        _Tmr3Count = 0;
        
        #if USE_HANDLER_IN_ISR_1_S == 1
        Runing_1sec();
        #else
        _is.ms_1000 = true;
        #endif
        
        _NSecondCount++;
        if (_NSecondCount >= DELAY_N_SECOND) {
            _NSecondCount = 0;
            
            #if USE_HANDLER_IN_ISR_N_S == 1
            Runing_Nsec();
            #else
            _is.ms_N000 = true;
            #endif
        }
    }
    
    //WDT and reset-MCU
    if(!_resetMCU) Generic_Clear_WDT(); 
    
    #if USE_HANDLER_IN_ISR_100MS == 1
    Run_100MS[1](); 
    Run_100MS[0]();
    #else
    _is.ms_0100 = true;
    #endif
}
/*
 * ===================
 *    Software RTC
 * ===================
 */
#if INCLUDE_SOFTWARE_RTC > 0
static int isLeapYear(int16_t year) {
    return (year%400==0) || ((year%4==0) && (year%100!=0));
}
static void inc_Day(
	int16_t *year, uint8_t *month, uint8_t *day
){
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	days[1] += isLeapYear(*year);
	//======= Inc day and check 
	*day = *day +1;
	if(*day > days[*month-1]){
		 *day=1;
		 if(*month==12) *month=1; 
		 else           *month = *month +1;
	}
	DB0_printf(" (%d-%d-%d) \n",*year, *month, *day);
}
//-----------------------------------------
//Summary : Inc. 1 sec for Software RTC
//Return  : None  
static void Inc1secRTC(void) {
    if(_DT==NULL) {
        DBT_printf("tEV.DT is NULL !\n");
        return;
    }
    _SW_RTC_sec++;
    if(_SW_RTC_sec >= 60){
        _SW_RTC_sec=0;
        _DT->m++;
        if(_DT->m >= 60){
            _DT->m=0;
            _DT->H++;
            if(_DT->H >=24){
                _DT->H=0;
                inc_Day(&(_DT->Y), &(_DT->M), &(_DT->D));
            }//hour
        }//min
    }//sec
}
#endif

//===========================================
// Private (member) functions
//===========================================
//---------------------------------------
//Summary : Wait some second, Blocking programm 
//Param   : T-second
//Return  : None
static void wait_Tsec_Block(uint16_t Tsec) {
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
    #if USE_HANDLER_IN_ISR_1MS != 1
    if(_is.ms_0001) {
        Run_1MS[1]();
        Run_1MS[0]();
        _is.ms_0001 = false;
    }
    #endif

    #if USE_HANDLER_IN_ISR_10MS != 1
    if(_is.ms_0010) {
        Run_10MS[1]();
        Run_10MS[0]();
        _is.ms_0010 = false;
    }
    #endif

    #if USE_HANDLER_IN_ISR_100MS != 1
    if(_is.ms_0100) {
        _is.ms_0100 = false;
        Run_100MS[2]();
        Run_100MS[1]();
        Run_100MS[0]();
        _is.ms_0100 = false;
    }
    #endif

    #if USE_HANDLER_IN_ISR_1_S != 1
    if(_is.ms_1000) {
        Runing_1sec();
        _is.ms_1000 = false;
    }
    #endif

     #if USE_HANDLER_IN_ISR_N_S != 1
    if(_is.ms_N000) {
        Runing_Nsec();
        _is.ms_N000 = false;
    }
    #endif
}
//-----------------------------------------
//Summary : Initial seed for Random number 
//Return  : None
static void random_seed_initial() {
    srand( (unsigned) Generic_SeedFromTimer() );
    //srand( (unsigned) _Tmr1Count );
}
//-----------------------------------------
//Summary : Get Random number in range [low, up]
//Return  : random number value
static int random(int low, int up) {
   return (int)((rand() / (RAND_MAX+1.0)) * (up - low) + low);
}
//-----------------------------------------
//Summary : Set up call-back function for Event Handler
static void SetEventHandler_Run_1ms(
    void (* eventHandler)(void), uint8_t i
) {
    Run_1MS[i] = eventHandler;
}
static void SetEventHandler_Run_10ms(
    void (* eventHandler)(void), uint8_t i
) {
    Run_10MS[i] = eventHandler;
}
static void SetEventHandler_Run_100ms(
    void (* eventHandler)(void), uint8_t i
) {
    Run_100MS[i] = eventHandler;
}
static void SetEventHandler_Run_1_sec(
    void (* eventHandler)(void)
) {
    Run_1_SEC = eventHandler;
}
static void SetEventHandler_Run_N_sec(
    void (* eventHandler)(void)
) {
    Run_N_SEC = eventHandler;
}
/*
 * =============
 *  cycle delay
 * =============
 */
#if INCLUDE_CYCLE_DELAY_US > 0
//---------------------------------------
//Summary : Wait some cycle
//Return  : None
static void DelayInCycle(uint8_t cycle) {
    uint8_t cnt, dummy;
    for(cnt=0; cnt < cycle; cnt++)
        dummy = cnt;
}
//---------------------------------------
//Summary : Wait some us
//Return  : Non
static void delay_in_50us(uint16_t us) {
    uint16_t cnt,uCnt;
    int exLoopCnt;
    exLoopCnt = us;
    if(exLoopCnt <= 0) exLoopCnt=1;
    for(uCnt=0; uCnt < exLoopCnt; uCnt++)
        for(cnt=0; cnt < DELAY_50US_CNT; cnt++)
            DelayInCycle(DELAY_50US_CYL);
}
//---------------------------------------
//Summary : test delau_in_us 
//Return  : Non
static void io_test_delay_us() {
    DELAY_TEST_PIN_Set_L();
    delay_in_50us(1);
    DELAY_TEST_PIN_Set_H() ;
    delay_in_50us(2000/50);  //2ms
    DELAY_TEST_PIN_Set_L();
    delay_in_50us(1);        //50us
    DELAY_TEST_PIN_Set_H() ;
    delay_in_50us(10);       //500us
    DELAY_TEST_PIN_Set_L();
    delay_in_50us(100);      //5ms
    DELAY_TEST_PIN_Set_H() ;
    delay_in_50us(200);      //10ms
    DELAY_TEST_PIN_Set_L();
}
#endif
/*
 * ===================
 * system time ticket 
 * ===================
 */
#if INCLUDE_SYSTEM_TIME_MS > 0
//-----------------------------------------
//Summary : System time ticket in ms
//Return  : Time-ticket in ms  
static uint32_t millis(void) {
    return _System_MsCount;
}
//------------------------------------------
//Summary : calculates the delata time in ms
//Param   : TimeMarker, is a previous time
//Return  : Time value from time marker to now (in ms)  
static uint32_t diff_millis(uint32_t TimeMarker) {
    if (_System_MsCount >= TimeMarker) {
        return (_System_MsCount - TimeMarker);
    } else {
        return ( UINT32_MAX - TimeMarker + _System_MsCount + 1);
    }
}
//-----------------------------------------
//Summary : delay time in ms (blocking)
//Param   : ms, the delat time
//Return  : None 
static void delay_in_ms(int ms) {
    uint32_t diff;
    tEV.tMarker = _System_MsCount;
    if (_System_MsCount >= tEV.tMarker) {
        diff = _System_MsCount - tEV.tMarker;
    } else {
        diff = UINT32_MAX - tEV.tMarker + _System_MsCount + 1;
    }  
    while (diff < ms)
    {
        DB0_printf("(%lu),", _System_MsCount);
        if (_System_MsCount >= tEV.tMarker) {
            diff = _System_MsCount - tEV.tMarker;
        } else {
            diff = UINT32_MAX - tEV.tMarker + _System_MsCount + 1;
        }
    };
}
#endif
//==============================================================================
// Public API functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//Return  : None
void tEV_init() {
    //timer callback link to real timer
    set_1ms_timer_callback();
    set_10ms_timer_callback();
    set_100ms_timer_callback();
    
    //..........................................
    //set default empty time event handler here
    //User could set again at top level main()
    SetEventHandler_Run_1ms(  Default_Run_1MS,0);
    SetEventHandler_Run_1ms(  Default_Run_1MS,1);
    SetEventHandler_Run_10ms( Default_Run_10MS,0);
    SetEventHandler_Run_10ms( Default_Run_10MS,1);
    SetEventHandler_Run_100ms(Default_Run_100MS,0);
    SetEventHandler_Run_100ms(Default_Run_100MS,1);
    SetEventHandler_Run_1_sec(Default_Run_1_sec);
    SetEventHandler_Run_N_sec(Default_Run_N_sec);
    
    //..........................................
    //initial data member
    tEV.resetMCU        = false;
    
    tEV.NSecondCount    = 0;
    tEV.Watting_1sec_Count = 0;
    tEV.Watting_Nsec_Count = 0;
    tEV.Tmr1Count       = 0;
    tEV.Tmr2Count       = 0;
    tEV.Tmr3Count       = 0;
    
    tEV.is.ms_0001 = false;
    tEV.is.ms_0010 = false;
    tEV.is.ms_0100 = false;
    tEV.is.ms_1000 = false;
    tEV.is.ms_N000 = false;
    
    #if INCLUDE_SYSTEM_TIME_MS > 0
    tEV.System_MsCount  = 0;
    #endif

    #if INCLUDE_SOFTWARE_RTC > 0
    tEV.SW_RTC_sec  = 0;
    #endif
    
    //..........................................
    tEV.wait_Tsec_Block     = wait_Tsec_Block;
    tEV.wait_T100ms         = wait_T100ms;
    
    tEV.setResetMcuFlag     = setResetMcuFlag;
    tEV.clearResetMcuFlag   = clearResetMcuFlag;
    
    tEV.checkInMainLoop     = checkInMainLoop;
    
    tEV.random_seed_initial = random_seed_initial;
    tEV.random              = random;
    
    tEV.SetEventHandler_Run_1ms = SetEventHandler_Run_1ms;
    tEV.SetEventHandler_Run_10ms = SetEventHandler_Run_10ms;
    tEV.SetEventHandler_Run_100ms = SetEventHandler_Run_100ms;
    tEV.SetEventHandler_Run_1_sec = SetEventHandler_Run_1_sec;
    tEV.SetEventHandler_Run_N_sec = SetEventHandler_Run_N_sec;
    
    #if INCLUDE_CYCLE_DELAY_US >0
    tEV.DelayInCycle        = DelayInCycle;
    tEV.delay_in_50us       = delay_in_50us;
    tEV.io_test_delay_us    = io_test_delay_us;
    #endif

    #if INCLUDE_SYSTEM_TIME_MS >0
    tEV.millis      = millis;
    tEV.diff_millis = diff_millis;
    tEV.delay_in_ms = delay_in_ms;
    #endif
    
    //last action: setup seed of random()
    //PS: since it will use fastest timer Timer1, and different 
    //    project, we call tEV_init() at different time after 
    //    power on. So, it's OK for most case.
    random_seed_initial();
}
