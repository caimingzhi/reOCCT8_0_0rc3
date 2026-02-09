#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunction;

class math_GaussMultipleIntegration
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_GaussMultipleIntegration(math_MultipleVarFunction& F,
                                                const math_Vector&        Lower,
                                                const math_Vector&        Upper,
                                                const math_IntegerVector& Order);

  bool IsDone() const;

  double Value() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  double Val;
  bool   Done;
};

#include <StdFail_NotDone.hpp>

inline bool math_GaussMultipleIntegration::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_GaussMultipleIntegration& G)
{
  G.Dump(o);
  return o;
}

inline double math_GaussMultipleIntegration::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Val;
}
