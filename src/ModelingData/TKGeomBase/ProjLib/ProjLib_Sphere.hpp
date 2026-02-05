#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Sphere.hpp>
#include <ProjLib_Projector.hpp>
class gp_Circ;
class gp_Lin;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

//! Projects elementary curves on a sphere.
class ProjLib_Sphere : public ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined projection.
  Standard_EXPORT ProjLib_Sphere();

  //! Projection on the sphere <Sp>.
  Standard_EXPORT ProjLib_Sphere(const gp_Sphere& Sp);

  //! Projection of the circle <C> on the sphere <Sp>.
  Standard_EXPORT ProjLib_Sphere(const gp_Sphere& Sp, const gp_Circ& C);

  Standard_EXPORT void Init(const gp_Sphere& Sp);

  Standard_EXPORT void Project(const gp_Lin& L) override;

  Standard_EXPORT void Project(const gp_Circ& C) override;

  Standard_EXPORT void Project(const gp_Elips& E) override;

  Standard_EXPORT void Project(const gp_Parab& P) override;

  Standard_EXPORT void Project(const gp_Hypr& H) override;

  //! Set the point of parameter U on C in the natural
  //! restrictions of the sphere.
  Standard_EXPORT void SetInBounds(const double U);

private:
  gp_Sphere mySphere;
};
