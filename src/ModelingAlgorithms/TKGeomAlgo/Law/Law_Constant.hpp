#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Law_Function.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

//! Loi constante
class Law_Constant : public Law_Function
{

public:
  Standard_EXPORT Law_Constant();

  //! Set the radius and the range of the constant Law.
  Standard_EXPORT void Set(const double Radius, const double PFirst, const double PLast);

  //! Returns GeomAbs_CN
  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  //! Returns 1
  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  //! Returns the value at parameter X.
  Standard_EXPORT double Value(const double X) override;

  //! Returns the value and the first derivative at parameter X.
  Standard_EXPORT void D1(const double X, double& F, double& D) override;

  //! Returns the value, first and second derivatives
  //! at parameter X.
  Standard_EXPORT void D2(const double X, double& F, double& D, double& D2) override;

  Standard_EXPORT occ::handle<Law_Function> Trim(const double PFirst,
                                                 const double PLast,
                                                 const double Tol) const override;

  //! Returns the parametric bounds of the function.
  Standard_EXPORT void Bounds(double& PFirst, double& PLast) override;

  DEFINE_STANDARD_RTTIEXT(Law_Constant, Law_Function)

private:
  double radius;
  double first;
  double last;
};
