#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Dir.hpp>
#include <gce_Root.hpp>
class gp_Vec;
class gp_XYZ;
class gp_Pnt;

class gce_MakeDir : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeDir(const gp_Vec& V);

  Standard_EXPORT gce_MakeDir(const gp_XYZ& Coord);

  Standard_EXPORT gce_MakeDir(const double Xv, const double Yv, const double Zv);

  Standard_EXPORT gce_MakeDir(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT const gp_Dir& Value() const;

  Standard_EXPORT const gp_Dir& Operator() const;
  Standard_EXPORT               operator gp_Dir() const;

private:
  gp_Dir TheDir;
};
