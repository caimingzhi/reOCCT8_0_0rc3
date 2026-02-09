#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Circ.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;
class gp_Dir;
class gp_Pln;
class gp_Ax1;

class gce_MakeCirc : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeCirc(const gp_Ax2& A2, const double Radius);

  Standard_EXPORT gce_MakeCirc(const gp_Circ& Circ, const double Dist);

  Standard_EXPORT gce_MakeCirc(const gp_Circ& Circ, const gp_Pnt& Point);

  Standard_EXPORT gce_MakeCirc(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT gce_MakeCirc(const gp_Pnt& Center, const gp_Dir& Norm, const double Radius);

  Standard_EXPORT gce_MakeCirc(const gp_Pnt& Center, const gp_Pln& Plane, const double Radius);

  Standard_EXPORT gce_MakeCirc(const gp_Pnt& Center, const gp_Pnt& Ptaxis, const double Radius);

  Standard_EXPORT gce_MakeCirc(const gp_Ax1& Axis, const double Radius);

  Standard_EXPORT const gp_Circ& Value() const;

  Standard_EXPORT const gp_Circ& Operator() const;
  Standard_EXPORT                operator gp_Circ() const;

private:
  gp_Circ TheCirc;
};
