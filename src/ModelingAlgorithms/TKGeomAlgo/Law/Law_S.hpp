#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_BSpFunc.hpp>

class Law_S : public Law_BSpFunc
{

public:
  Standard_EXPORT Law_S();

  Standard_EXPORT void Set(const double Pdeb,
                           const double Valdeb,
                           const double Pfin,
                           const double Valfin);

  Standard_EXPORT void Set(const double Pdeb,
                           const double Valdeb,
                           const double Ddeb,
                           const double Pfin,
                           const double Valfin,
                           const double Dfin);

  DEFINE_STANDARD_RTTIEXT(Law_S, Law_BSpFunc)
};
