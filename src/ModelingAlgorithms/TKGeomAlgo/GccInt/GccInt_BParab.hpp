#pragma once

#include <Standard.hpp>

#include <gp_Parab2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

//! Describes a parabola as a bisecting curve between two
//! 2D geometric objects (such as lines, circles or points).
class GccInt_BParab : public GccInt_Bisec
{

public:
  //! Constructs a bisecting curve whose geometry is the 2D parabola Parab.
  Standard_EXPORT GccInt_BParab(const gp_Parab2d& Parab);

  //! Returns a 2D parabola which is the geometry of this bisecting curve.
  Standard_EXPORT gp_Parab2d Parabola() const override;

  //! Returns GccInt_Par, which is the type of any GccInt_BParab bisecting curve.
  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BParab, GccInt_Bisec)

private:
  gp_Parab2d par;
};
