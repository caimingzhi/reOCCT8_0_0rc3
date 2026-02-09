#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class math_Function;

class math_GaussSingleIntegration
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_GaussSingleIntegration();

  Standard_EXPORT math_GaussSingleIntegration(math_Function& F,
                                              const double   Lower,
                                              const double   Upper,
                                              const int      Order);

  Standard_EXPORT math_GaussSingleIntegration(math_Function& F,
                                              const double   Lower,
                                              const double   Upper,
                                              const int      Order,
                                              const double   Tol);

  bool IsDone() const;

  double Value() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT void Perform(math_Function& F,
                               const double   Lower,
                               const double   Upper,
                               const int      Order);

  double Val{};
  bool   Done{};
};

#include <StdFail_NotDone.hpp>

inline Standard_OStream& operator<<(Standard_OStream& o, const math_GaussSingleIntegration& G)
{
  G.Dump(o);
  return o;
}

inline bool math_GaussSingleIntegration::IsDone() const
{
  return Done;
}

inline double math_GaussSingleIntegration::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Val;
}
