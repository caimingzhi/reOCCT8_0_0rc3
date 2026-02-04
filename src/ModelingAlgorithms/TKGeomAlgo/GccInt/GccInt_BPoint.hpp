#pragma once


#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

//! Describes a point as a bisecting object between two 2D geometric objects.
class GccInt_BPoint : public GccInt_Bisec
{

public:
  //! Constructs a bisecting object whose geometry is the 2D point Point.
  Standard_EXPORT GccInt_BPoint(const gp_Pnt2d& Point);

  //! Returns a 2D point which is the geometry of this bisecting object.
  Standard_EXPORT gp_Pnt2d Point() const override;

  //! Returns GccInt_Pnt, which is the type of any GccInt_BPoint bisecting object.
  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BPoint, GccInt_Bisec)

private:
  gp_Pnt2d pnt;
};

