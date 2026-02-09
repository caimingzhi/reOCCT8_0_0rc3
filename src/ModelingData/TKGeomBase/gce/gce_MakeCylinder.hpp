#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Cylinder.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;
class gp_Ax1;
class gp_Circ;

class gce_MakeCylinder : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeCylinder(const gp_Ax2& A2, const double Radius);

  Standard_EXPORT gce_MakeCylinder(const gp_Cylinder& Cyl, const gp_Pnt& Point);

  Standard_EXPORT gce_MakeCylinder(const gp_Cylinder& Cyl, const double Dist);

  Standard_EXPORT gce_MakeCylinder(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT gce_MakeCylinder(const gp_Ax1& Axis, const double Radius);

  Standard_EXPORT gce_MakeCylinder(const gp_Circ& Circ);

  Standard_EXPORT const gp_Cylinder& Value() const;

  Standard_EXPORT const gp_Cylinder& Operator() const;
  Standard_EXPORT                    operator gp_Cylinder() const;

private:
  gp_Cylinder TheCylinder;
};
