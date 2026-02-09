#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Cylinder.hpp>
#include <ProjLib_Projector.hpp>
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

class ProjLib_Cylinder : public ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_Cylinder();

  Standard_EXPORT ProjLib_Cylinder(const gp_Cylinder& Cyl);

  Standard_EXPORT ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Lin& L);

  Standard_EXPORT ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Circ& C);

  Standard_EXPORT ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Elips& E);

  Standard_EXPORT void Init(const gp_Cylinder& Cyl);

  Standard_EXPORT void Project(const gp_Lin& L) override;

  Standard_EXPORT void Project(const gp_Circ& C) override;

  Standard_EXPORT void Project(const gp_Elips& E) override;

  Standard_EXPORT void Project(const gp_Parab& P) override;

  Standard_EXPORT void Project(const gp_Hypr& H) override;

private:
  gp_Cylinder myCylinder;
};
