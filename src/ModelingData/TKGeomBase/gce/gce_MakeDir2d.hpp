#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Dir2d.hpp>
#include <gce_Root.hpp>
class gp_Vec2d;
class gp_XY;
class gp_Pnt2d;

class gce_MakeDir2d : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeDir2d(const gp_Vec2d& V);

  Standard_EXPORT gce_MakeDir2d(const gp_XY& Coord);

  Standard_EXPORT gce_MakeDir2d(const double Xv, const double Yv);

  Standard_EXPORT gce_MakeDir2d(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT const gp_Dir2d& Value() const;

  Standard_EXPORT const gp_Dir2d& Operator() const;
  Standard_EXPORT                 operator gp_Dir2d() const;

private:
  gp_Dir2d TheDir2d;
};
