#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Law_Function.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

class Law_Constant : public Law_Function
{

public:
  Standard_EXPORT Law_Constant();

  Standard_EXPORT void Set(const double Radius, const double PFirst, const double PLast);

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

  DEFINE_STANDARD_RTTIEXT(Law_Constant, Law_Function)

private:
  double radius;
  double first;
  double last;
};
