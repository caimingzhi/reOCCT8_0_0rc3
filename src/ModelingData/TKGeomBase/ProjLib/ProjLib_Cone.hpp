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

//! Projects elementary curves on a cone.
class ProjLib_Cone : public ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined projection.
  Standard_EXPORT ProjLib_Cone();

  //! Projection on the cone <Co>.
  Standard_EXPORT ProjLib_Cone(const gp_Cone& Co);

  //! Projection of the line <L> on the cone <Co>.
  Standard_EXPORT ProjLib_Cone(const gp_Cone& Co, const gp_Lin& L);

  //! Projection of the circle <C> on the cone <Co>.
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
