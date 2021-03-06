/* 
 * File:      Operation.c
 * Author:    Jacky Lue
 * Comments:  Model for this project amin concept.
 * Revision history:
 *   2019/12/24 first version
 */

//==============================================================================
//  Included header files 
//==============================================================================
#include "projectConfig.h"
#include "mcc_generated_files/pin_manager.h"
//
#include "Operation.h"
#include "coreModel.h"


//==============================================================================
// Public Data
//==============================================================================
OpType iOp;

//==============================================================================
// Private Macros
//==============================================================================

//==============================================================================
// Private Data
//==============================================================================

//==============================================================================
// Private (local) functions
//==============================================================================

//==============================================================================
// Private (member) functions
//==============================================================================

//for application main loop
static void mainLoopTask(void)
{   
    // TODO add main loop job here!
}

//==============================================================================
// Public API Functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//          We will also initial Timer calback functions 
//Return  : None
void iOp_init()
{    
    //###########################
    // Data Member area
    //###########################
        
    //###########################
    // Function Menmber area
    //###########################
    iOp.mainLoopTask = mainLoopTask;

}