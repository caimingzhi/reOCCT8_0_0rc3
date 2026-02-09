#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pln.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;
class gp_Dir;
class gp_Ax1;

class gce_MakePln : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakePln(const gp_Ax2& A2);

  Standard_EXPORT gce_MakePln(const gp_Pnt& P, const gp_Dir& V);

  Standard_EXPORT gce_MakePln(const double A, const double B, const double C, const double D);

  Standard_EXPORT gce_MakePln(const gp_Pln& Pln, const gp_Pnt& Point);

  Standard_EXPORT gce_MakePln(const gp_Pln& Pln, const double Dist);

  Standard_EXPORT gce_MakePln(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  Standard_EXPORT gce_MakePln(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT gce_MakePln(const gp_Ax1& Axis);

  Standard_EXPORT const gp_Pln& Value() const;

  Standard_EXPORT const gp_Pln& Operator() const;
  Standard_EXPORT               operator gp_Pln() const;

private:
  gp_Pln ThePln;
};
