#pragma once


#include <Standard.hpp>

#include <gp_Hypr2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

//! Describes a hyperbola as a bisecting curve between two
//! 2D geometric objects (such as circles or points).
class GccInt_BHyper : public GccInt_Bisec
{

public:
  //! Constructs a bisecting curve whose geometry is the 2D hyperbola Hyper.
  Standard_EXPORT GccInt_BHyper(const gp_Hypr2d& Hyper);

  //! Returns a 2D hyperbola which is the geometry of this bisecting curve.
  Standard_EXPORT gp_Hypr2d Hyperbola() const override;

  //! Returns GccInt_Hpr, which is the type of any GccInt_BHyper bisecting curve.
  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BHyper, GccInt_Bisec)

private:
  gp_Hypr2d hyp;
};

