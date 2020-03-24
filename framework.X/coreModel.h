/* 
 * File:      CoreModel.h
 * Author:    Jacky Lue
 * Comments:  Model for this project amin concept.
 * Revision history:
 *   2019/12/24 first version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_CORE_MODEL_H
#define	XC_HEADER_CORE_MODEL_H

//==============================================================================
//  Included header files 
//==============================================================================
#include <xc.h> // include processor files - each processor file is guarded.  
//
#include "projectConfig.h" 

//==============================================================================
// Public Macros
//==============================================================================
//configuration, can be define at Top project-config.h
//  0 = OFF
//  1 = ON

//------------------------------------------------------------------------------
// predefine constant 
//------------------------------------------------------------------------------

//==============================================================================
// Public Types
//==============================================================================
typedef struct ST_FlagType {
    bool        PowerOn; 
    // TODO: add more for project purpose
}FlagType;

typedef struct ST_CoreModelType{
    //###########################
    // Data Member area
    //###########################
    
    //flags for program control
    FlagType is;
    
    // TODO: add project's model-variable
    
    //###########################
    // Function Menmber area
    //###########################
    
    // TODO: add access or conversion for model-variable
 
}CoreModel;

//==============================================================================
// Public Data
//==============================================================================
extern CoreModel cMdl;

//==============================================================================
// Public API Functions
//==============================================================================
//------------------------------------------------------------------------------
//Summary : Initial Time-event ctrl module
//Remark  : initial object's function pointers & data members
//          We will also initial Timer calback functions 
//Return  : None
void cMdl_init();

#endif	/* XC_HEADER_CORE_MODEL_H */

