#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Lin2d.hpp>
#include <gce_Root.hpp>
class gp_Ax2d;
class gp_Pnt2d;
class gp_Dir2d;

class gce_MakeLin2d : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeLin2d(const gp_Ax2d& A);

  Standard_EXPORT gce_MakeLin2d(const gp_Pnt2d& P, const gp_Dir2d& V);

  Standard_EXPORT gce_MakeLin2d(const double A, const double B, const double C);

  Standard_EXPORT gce_MakeLin2d(const gp_Lin2d& Lin, const double Dist);

  Standard_EXPORT gce_MakeLin2d(const gp_Lin2d& Lin, const gp_Pnt2d& Point);

  Standard_EXPORT gce_MakeLin2d(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT gp_Lin2d Value() const;

  Standard_EXPORT gp_Lin2d Operator() const;
  Standard_EXPORT          operator gp_Lin2d() const;

private:
  gp_Lin2d TheLin2d;
};
