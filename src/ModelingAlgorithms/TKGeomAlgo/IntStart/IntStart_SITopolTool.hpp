#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <TopAbs_State.hpp>
#include <Standard_Real.hpp>
class gp_Pnt2d;

class IntStart_SITopolTool : public Standard_Transient
{

public:
  Standard_EXPORT virtual TopAbs_State Classify(const gp_Pnt2d& P, const double Tol) = 0;

  DEFINE_STANDARD_RTTIEXT(IntStart_SITopolTool, Standard_Transient)
};
