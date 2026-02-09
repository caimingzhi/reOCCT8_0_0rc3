#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
class gp_Pnt;
class gp_Ax1;
class gp_Lin;
class gp_Dir;
class gp_Pln;
class gp_Ax2;

class gce_MakeMirror
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeMirror(const gp_Pnt& Point);

  Standard_EXPORT gce_MakeMirror(const gp_Ax1& Axis);

  Standard_EXPORT gce_MakeMirror(const gp_Lin& Line);

  Standard_EXPORT gce_MakeMirror(const gp_Pnt& Point, const gp_Dir& Direc);

  Standard_EXPORT gce_MakeMirror(const gp_Pln& Plane);

  Standard_EXPORT gce_MakeMirror(const gp_Ax2& Plane);

  Standard_EXPORT const gp_Trsf& Value() const;

  Standard_EXPORT const gp_Trsf& Operator() const;
  Standard_EXPORT                operator gp_Trsf() const;

private:
  gp_Trsf TheMirror;
};
