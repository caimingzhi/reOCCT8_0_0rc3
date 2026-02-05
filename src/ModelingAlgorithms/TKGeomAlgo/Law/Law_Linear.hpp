#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_Function.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

//! Describes an linear evolution law.
class Law_Linear : public Law_Function
{

public:
  //! Constructs an empty linear evolution law.
  Standard_EXPORT Law_Linear();

  //! Defines this linear evolution law by assigning both:
  //! -   the bounds Pdeb and Pfin of the parameter, and
  //! -   the values Valdeb and Valfin of the function at these
  //! two parametric bounds.
  Standard_EXPORT void Set(const double Pdeb,
                           const double Valdeb,
                           const double Pfin,
                           const double Valfin);

  //! Returns GeomAbs_CN
  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  //! Returns 1
  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  //! Returns the value of this function at the point of parameter X.
  Standard_EXPORT double Value(const double X) override;

  //! Returns the value F and the first derivative D of this
  //! function at the point of parameter X.
  Standard_EXPORT void D1(const double X, double& F, double& D) override;

  //! Returns the value, first and second derivatives
  //! at parameter X.
  Standard_EXPORT void D2(const double X, double& F, double& D, double& D2) override;

  //! Returns a law equivalent of <me> between
  //! parameters <First> and <Last>. <Tol> is used to
  //! test for 3d points confusion.
  //! It is usfule to determines the derivatives
  //! in these values <First> and <Last> if
  //! the Law is not Cn.
  Standard_EXPORT occ::handle<Law_Function> Trim(const double PFirst,
                                                 const double PLast,
                                                 const double Tol) const override;

  //! Returns the parametric bounds of the function.
  Standard_EXPORT void Bounds(double& PFirst, double& PLast) override;

  DEFINE_STANDARD_RTTIEXT(Law_Linear, Law_Function)

private:
  double valdeb;
  double valfin;
  double pdeb;
  double pfin;
};
