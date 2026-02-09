#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Cone.hpp>
#include <ProjLib_Projector.hpp>
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

class ProjLib_Cone : public ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_Cone();

  Standard_EXPORT ProjLib_Cone(const gp_Cone& Co);

  Standard_EXPORT ProjLib_Cone(const gp_Cone& Co, const gp_Lin& L);

  Standard_EXPORT ProjLib_Cone(const gp_Cone& Co, const gp_Circ& C);

  Standard_EXPORT void Init(const gp_Cone& Co);

  Standard_EXPORT void Project(const gp_Lin& L) override;

  Standard_EXPORT void Project(const gp_Circ& C) override;

  Standard_EXPORT void Project(const gp_Elips& E) override;

  Standard_EXPORT void Project(const gp_Parab& P) override;

  Standard_EXPORT void Project(const gp_Hypr& H) override;

private:
  gp_Cone myCone;
};
