#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_BSpFunc.hpp>

//! Describes an "S" evolution law.
class Law_S : public Law_BSpFunc
{

public:
  //! Constructs an empty "S" evolution law.
  Standard_EXPORT Law_S();

  //! Defines this S evolution law by assigning both:
  //! -   the bounds Pdeb and Pfin of the parameter, and
  //! -   the values Valdeb and Valfin of the function at these
  //! two parametric bounds.
  //! The function is assumed to have the first derivatives
  //! equal to 0 at the two parameter points Pdeb and Pfin.
  Standard_EXPORT void Set(const double Pdeb,
                           const double Valdeb,
                           const double Pfin,
                           const double Valfin);

  //! Defines this S evolution law by assigning
  //! -   the bounds Pdeb and Pfin of the parameter,
  //! -   the values Valdeb and Valfin of the function at these
  //! two parametric bounds, and
  //! -   the values Ddeb and Dfin of the first derivative of the
  //! function at these two parametric bounds.
  Standard_EXPORT void Set(const double Pdeb,
                           const double Valdeb,
                           const double Ddeb,
                           const double Pfin,
                           const double Valfin,
                           const double Dfin);

  DEFINE_STANDARD_RTTIEXT(Law_S, Law_BSpFunc)
};
