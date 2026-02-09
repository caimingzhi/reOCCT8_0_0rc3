#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <STEPControl_Controller.hpp>

class STEPCAFControl_Controller : public STEPControl_Controller
{

public:
  Standard_EXPORT STEPCAFControl_Controller();

  Standard_EXPORT static bool Init();

  DEFINE_STANDARD_RTTIEXT(STEPCAFControl_Controller, STEPControl_Controller)
};
