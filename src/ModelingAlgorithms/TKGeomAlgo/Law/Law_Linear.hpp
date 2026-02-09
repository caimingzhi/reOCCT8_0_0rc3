#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_Function.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

class Law_Linear : public Law_Function
{

public:
  Standard_EXPORT Law_Linear();

  Standard_EXPORT void Set(const double Pdeb,
                           const double Valdeb,
                           const double Pfin,
                           const double Valfin);

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT double Value(const double X) override;

  Standard_EXPORT void D1(const double X, double& F, double& D) override;

  Standard_EXPORT void D2(const double X, double& F, double& D, double& D2) override;

  Standard_EXPORT occ::handle<Law_Function> Trim(const double PFirst,
                                                 const double PLast,
                                                 const double Tol) const override;

  Standard_EXPORT void Bounds(double& PFirst, double& PLast) override;

  DEFINE_STANDARD_RTTIEXT(Law_Linear, Law_Function)

private:
  double valdeb;
  double valfin;
  double pdeb;
  double pfin;
};
