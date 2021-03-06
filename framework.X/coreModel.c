/* 
 * File:      CoreModel.c
 * Author:    Jacky Lue
 * Comments:  Model for this project amin concept.
 * Revision history:
 *   2019/12/24 first version
 */

//==============================================================================
//  Included header files 
//==============================================================================
#include "projectConfig.h"
#include "mcc_generated_files/mcc.h"
//
#include "coreModel.h"

//==============================================================================
// Public Data
//==============================================================================
CoreModel cMdl;

//==============================================================================
// Private Macros
//==============================================================================
#define _is             cMdl.is    

//==============================================================================
// Private Data
//==============================================================================

//==============================================================================
// Private (local) functions
//==============================================================================

//==============================================================================
// Private (member) functions
//==============================================================================

//==============================================================================
// Public API Functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//          We will also initial Timer calback functions 
//Return  : None
void cMdl_init()
{
    //###########################
    // Data Member area
    //###########################
    _is.PowerOn = false;
    
    //###########################
    // Function Menmber area
    //###########################

}