#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class GeomFill_CornerState
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_CornerState();

  Standard_EXPORT double Gap() const;

  Standard_EXPORT void Gap(const double G);

  Standard_EXPORT double TgtAng() const;

  Standard_EXPORT void TgtAng(const double Ang);

  Standard_EXPORT bool HasConstraint() const;

  Standard_EXPORT void Constraint();

  Standard_EXPORT double NorAng() const;

  Standard_EXPORT void NorAng(const double Ang);

  Standard_EXPORT bool IsToKill(double& Scal) const;

  Standard_EXPORT void DoKill(const double Scal);

private:
  double gap;
  double tgtang;
  bool   isconstrained;
  double norang;
  double scal;
  bool   coonscnd;
};
