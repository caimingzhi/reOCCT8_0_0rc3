#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_Ellipse.hpp>

class gp_Elips2d;
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;

class GCE2d_MakeEllipse : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeEllipse(const gp_Elips2d& E);

  Standard_EXPORT GCE2d_MakeEllipse(const gp_Ax2d& MajorAxis,
                                    const double   MajorRadius,
                                    const double   MinorRadius,
                                    const bool     Sense = true);

  Standard_EXPORT GCE2d_MakeEllipse(const gp_Ax22d& Axis,
                                    const double    MajorRadius,
                                    const double    MinorRadius);

  Standard_EXPORT GCE2d_MakeEllipse(const gp_Pnt2d& S1, const gp_Pnt2d& S2, const gp_Pnt2d& Center);

  Standard_EXPORT const occ::handle<Geom2d_Ellipse>& Value() const;

  operator const occ::handle<Geom2d_Ellipse>&() const { return Value(); }

private:
  occ::handle<Geom2d_Ellipse> TheEllipse;
};
