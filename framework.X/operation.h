/* 
 * File:      Operation.h
 * Author:    Jacky Lue
 * Comments:  Model for this project amin concept.
 * Revision history:
 *   2019/12/24 first version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_OPERATION_H
#define	XC_HEADER_OPERATION_H

//==============================================================================
//  Included header files 
//==============================================================================
#include <xc.h> // include processor files - each processor file is guarded.  
//
#include "projectConfig.h" 
//

//==============================================================================
// Public Macros
//==============================================================================
//configuration, can be define at Top project-config.h
//  0 = OFF
//  1 = ON

//------------------------------------------------------------------------------
// predefine constant 
//------------------------------------------------------------------------------
#define OP_TEST_GO4_COMMAND     93

//==============================================================================
// Public Types
//==============================================================================
typedef struct ST_OpType{
    //###########################
    // Data Member area
    //###########################
           
    //###########################
    // Function Menmber area
    //###########################
    
    //for application main loop
    void (*mainLoopTask)(void);  
 
}OpType;

//==============================================================================
// Public Data
//==============================================================================
extern OpType iOp;

//==============================================================================
// Public API Functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//          We will also initial Timer calback functions 
//Return  : None
void iOp_init();



#endif	/* XC_HEADER_OPERATION_H */

