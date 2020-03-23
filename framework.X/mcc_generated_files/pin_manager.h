/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F46K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set TEST0 aliases
#define TEST0_TRIS                 TRISBbits.TRISB3
#define TEST0_LAT                  LATBbits.LATB3
#define TEST0_PORT                 PORTBbits.RB3
#define TEST0_WPU                  WPUBbits.WPUB3
#define TEST0_ANS                  ANSELBbits.ANSB3
#define TEST0_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define TEST0_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define TEST0_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define TEST0_GetValue()           PORTBbits.RB3
#define TEST0_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define TEST0_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define TEST0_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define TEST0_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define TEST0_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define TEST0_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set TEST1 aliases
#define TEST1_TRIS                 TRISBbits.TRISB4
#define TEST1_LAT                  LATBbits.LATB4
#define TEST1_PORT                 PORTBbits.RB4
#define TEST1_WPU                  WPUBbits.WPUB4
#define TEST1_ANS                  ANSELBbits.ANSB4
#define TEST1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define TEST1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define TEST1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define TEST1_GetValue()           PORTBbits.RB4
#define TEST1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define TEST1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define TEST1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define TEST1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define TEST1_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define TEST1_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set TEST2 aliases
#define TEST2_TRIS                 TRISBbits.TRISB5
#define TEST2_LAT                  LATBbits.LATB5
#define TEST2_PORT                 PORTBbits.RB5
#define TEST2_WPU                  WPUBbits.WPUB5
#define TEST2_ANS                  ANSELBbits.ANSB5
#define TEST2_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define TEST2_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define TEST2_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define TEST2_GetValue()           PORTBbits.RB5
#define TEST2_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define TEST2_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define TEST2_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define TEST2_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define TEST2_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define TEST2_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RD6 procedures
#define RD6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define RD6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define RD6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define RD6_GetValue()              PORTDbits.RD6
#define RD6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define RD6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define RD6_SetAnalogMode()         do { ANSELDbits.ANSD6 = 1; } while(0)
#define RD6_SetDigitalMode()        do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set RD7 procedures
#define RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define RD7_GetValue()              PORTDbits.RD7
#define RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define RD7_SetAnalogMode()         do { ANSELDbits.ANSD7 = 1; } while(0)
#define RD7_SetDigitalMode()        do { ANSELDbits.ANSD7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/