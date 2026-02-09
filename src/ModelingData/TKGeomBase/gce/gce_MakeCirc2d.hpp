#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Circ2d.hpp>
#include <gce_Root.hpp>
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;

class gce_MakeCirc2d : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeCirc2d(const gp_Ax2d& XAxis,
                                 const double   Radius,
                                 const bool     Sense = true);

  Standard_EXPORT gce_MakeCirc2d(const gp_Ax22d& Axis, const double Radius);

  Standard_EXPORT gce_MakeCirc2d(const gp_Circ2d& Circ, const double Dist);

  Standard_EXPORT gce_MakeCirc2d(const gp_Circ2d& Circ, const gp_Pnt2d& Point);

  Standard_EXPORT gce_MakeCirc2d(const gp_Pnt2d& P1, const gp_Pnt2d& P2, const gp_Pnt2d& P3);

  Standard_EXPORT gce_MakeCirc2d(const gp_Pnt2d& Center,
                                 const double    Radius,
                                 const bool      Sense = true);

  Standard_EXPORT gce_MakeCirc2d(const gp_Pnt2d& Center,
                                 const gp_Pnt2d& Point,
                                 const bool      Sense = true);

  Standard_EXPORT const gp_Circ2d& Value() const;

  Standard_EXPORT const gp_Circ2d& Operator() const;
  Standard_EXPORT                  operator gp_Circ2d() const;

private:
  gp_Circ2d TheCirc2d;
};
