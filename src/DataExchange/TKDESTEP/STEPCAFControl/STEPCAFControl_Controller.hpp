#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <STEPControl_Controller.hpp>

//! Extends Controller from STEPControl in order to provide
//! ActorWrite adapted for writing assemblies from DECAF
//! Note that ActorRead from STEPControl is used for reading
//! (inherited automatically)
class STEPCAFControl_Controller : public STEPControl_Controller
{

public:
  //! Initializes the use of STEP Norm (the first time)
  Standard_EXPORT STEPCAFControl_Controller();

  //! Standard Initialisation. It creates a Controller for STEP-XCAF
  //! and records it to various names, available to select it later
  //! Returns True when done, False if could not be done
  Standard_EXPORT static bool Init();

  DEFINE_STANDARD_RTTIEXT(STEPCAFControl_Controller, STEPControl_Controller)
};

