#pragma once

#include <Standard.hpp>

#include <gp_Elips2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

//! Describes an ellipse as a bisecting curve between two
//! 2D geometric objects (such as circles or points).
class GccInt_BElips : public GccInt_Bisec
{

public:
  //! Constructs a bisecting curve whose geometry is the 2D ellipse Ellipse.
  Standard_EXPORT GccInt_BElips(const gp_Elips2d& Ellipse);

  //! Returns a 2D ellipse which is the geometry of this bisecting curve.
  Standard_EXPORT gp_Elips2d Ellipse() const override;

  //! Returns GccInt_Ell, which is the type of any GccInt_BElips bisecting curve.
  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BElips, GccInt_Bisec)

private:
  gp_Elips2d eli;
};
