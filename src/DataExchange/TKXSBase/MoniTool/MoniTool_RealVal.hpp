#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>

class MoniTool_RealVal : public Standard_Transient
{

public:
  Standard_EXPORT MoniTool_RealVal(const double val = 0.0);

  Standard_EXPORT double Value() const;

  Standard_EXPORT double& CValue();

  DEFINE_STANDARD_RTTIEXT(MoniTool_RealVal, Standard_Transient)

private:
  double theval;
};
