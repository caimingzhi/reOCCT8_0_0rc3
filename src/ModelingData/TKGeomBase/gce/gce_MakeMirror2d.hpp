#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf2d.hpp>
class gp_Pnt2d;
class gp_Ax2d;
class gp_Lin2d;
class gp_Dir2d;

class gce_MakeMirror2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeMirror2d(const gp_Pnt2d& Point);

  Standard_EXPORT gce_MakeMirror2d(const gp_Ax2d& Axis);

  Standard_EXPORT gce_MakeMirror2d(const gp_Lin2d& Line);

  Standard_EXPORT gce_MakeMirror2d(const gp_Pnt2d& Point, const gp_Dir2d& Direc);

  Standard_EXPORT const gp_Trsf2d& Value() const;

  Standard_EXPORT const gp_Trsf2d& Operator() const;
  Standard_EXPORT                  operator gp_Trsf2d() const;

private:
  gp_Trsf2d TheMirror2d;
};
