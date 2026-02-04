#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

//! An Integer through a Handle (i.e. managed as TShared)
class MoniTool_IntVal : public Standard_Transient
{

public:
  Standard_EXPORT MoniTool_IntVal(const int val = 0);

  Standard_EXPORT int Value() const;

  Standard_EXPORT int& CValue();

  DEFINE_STANDARD_RTTIEXT(MoniTool_IntVal, Standard_Transient)

private:
  int theval;
};

