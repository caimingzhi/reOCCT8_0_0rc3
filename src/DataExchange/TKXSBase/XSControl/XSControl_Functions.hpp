#pragma once


//! Functions from XSControl gives access to actions which can be
//! commanded with the resources provided by XSControl: especially
//! Controller and Transfer
//!
//! It works by adding functions by method Init
class XSControl_Functions
{
public:
  //! Defines and loads all functions for XSControl (as ActFunc)
  Standard_EXPORT static void Init();
};

