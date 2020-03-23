/**
 * File Name: main.c
 *
 * Project: XXXXXXXX
 *
 * Information:
 *   Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
 *   Device            :  PIC18F46K22
 *   Driver Version    :  2.00
 */
/* MCU setting:
 *    Timer2 : 1ms
 *    Timer3 : 10ms
 *    Timer0 : 100ms
 */
//----------- system include ----------------
#include "mcc_generated_files/mcc.h"
#include "projectConfig.h"
//----------- sub-module include ------------
//#include "myTimeEvent.h"
#include "secTimeEvent.h"

//==============================================================================
// Private Macros
//==============================================================================

//==============================================================================
// Private Data
//==============================================================================

//==============================================================================
// Private (local) functions
//==============================================================================

void xxxx(void) {
    DBT_printf("~~~~\n");
}

void Software_initial() {
  // time-event initial
  tEV_init();
  // tEV.SetEventHandler_Run_1ms(xxxx, 0);
  // tEV.SetEventHandler_Run_10ms(xxxx, 1);
  // tEV.SetEventHandler_Run_10ms(xxxx, 0);
  tEV.SetEventHandler_Run_100ms(xxxx, 0);
  // tEV.SetEventHandler_Run_100ms(xxxx, 1);
  // tEV.SetEventHandler_Run_1_sec(xxxx);
  // tEV.SetEventHandler_Run_N_sec(xxxx);

  // ---- start ----
  tEV.wait_T100ms(100); // some delay is must for first prinf().
  DBT_printf("\n------------------\n");
  DBT_printf("  UWB + AHRS Test \n");
  DBT_printf("------------------\n");
}

/*******************************************************************************
                         Main application
 ******************************************************************************
 */
void main(void) {
  // Initialize the device
  SYSTEM_Initialize();

  // If using interrupts in PIC18 High/Low Priority Mode you need to enable the
  // Global High and Low Interrupts If using interrupts in PIC Mid-Range
  // Compatibility Mode you need to enable the Global and Peripheral Interrupts
  // Use the following macros to:

  // Enable the Global Interrupts
  INTERRUPT_GlobalInterruptEnable();

  // Disable the Global Interrupts
  // INTERRUPT_GlobalInterruptDisable();

  // Enable the Peripheral Interrupts
  INTERRUPT_PeripheralInterruptEnable();

  // Disable the Peripheral Interrupts
  // INTERRUPT_PeripheralInterruptDisable();

  // project SW module initial
  Software_initial();

  DBT_printf("--- Loop start ---\n");

  while (tEV.resetMCU == false) {
    // ------ For time event flags ------
    #if CHECK_TIME_EV_IN_MAIN_LOOP == 1
    tEV.checkInMainLoop();
    #endif
    
    // TODO add job in main loop ...
    
    // unmark this when only a few job in loop
    // tEV.delay_in_ms(1);
  }
}
/**
 End of File
*/