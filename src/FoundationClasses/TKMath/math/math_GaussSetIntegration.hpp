#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>
#include <Standard_OStream.hpp>
class math_FunctionSet;

class math_GaussSetIntegration
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_GaussSetIntegration(math_FunctionSet&         F,
                                           const math_Vector&        Lower,
                                           const math_Vector&        Upper,
                                           const math_IntegerVector& Order);

  bool IsDone() const;

  const math_Vector& Value() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  math_Vector Val;
  bool        Done;
};

#include <math_Vector.hpp>
#include <StdFail_NotDone.hpp>

inline bool math_GaussSetIntegration::IsDone() const
{
  return Done;
}

inline const math_Vector& math_GaussSetIntegration::Value() const
{
  StdFail_NotDone_Raise_if(!Done, "Integration ");
  return Val;
}
