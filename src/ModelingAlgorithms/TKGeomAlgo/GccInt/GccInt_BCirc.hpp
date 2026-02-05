#pragma once

#include <Standard.hpp>

#include <gp_Circ2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

//! Describes a circle as a bisecting curve between two 2D
//! geometric objects (such as circles or points).
class GccInt_BCirc : public GccInt_Bisec
{

public:
  //! Constructs a bisecting curve whose geometry is the 2D circle Circ.
  Standard_EXPORT GccInt_BCirc(const gp_Circ2d& Circ);

  //! Returns a 2D circle which is the geometry of this bisecting curve.
  Standard_EXPORT gp_Circ2d Circle() const override;

  //! Returns GccInt_Cir, which is the type of any GccInt_BCirc bisecting curve.
  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BCirc, GccInt_Bisec)

private:
  gp_Circ2d cir;
};
