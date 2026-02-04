#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pln.hpp>
#include <ProjLib_Projector.hpp>
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

//! Projects elementary curves on a plane.
class ProjLib_Plane : public ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined projection.
  Standard_EXPORT ProjLib_Plane();

  //! Projection on the plane <Pl>.
  Standard_EXPORT ProjLib_Plane(const gp_Pln& Pl);

  //! Projection of the line <L> on the plane <Pl>.
  Standard_EXPORT ProjLib_Plane(const gp_Pln& Pl, const gp_Lin& L);

  //! Projection of the circle <C> on the plane <Pl>.
  Standard_EXPORT ProjLib_Plane(const gp_Pln& Pl, const gp_Circ& C);

  //! Projection of the ellipse <E> on the plane <Pl>.
  Standard_EXPORT ProjLib_Plane(const gp_Pln& Pl, const gp_Elips& E);

  //! Projection of the parabola <P> on the plane <Pl>.
  Standard_EXPORT ProjLib_Plane(const gp_Pln& Pl, const gp_Parab& P);

  //! Projection of the hyperbola <H> on the plane <Pl>.
  Standard_EXPORT ProjLib_Plane(const gp_Pln& Pl, const gp_Hypr& H);

  Standard_EXPORT void Init(const gp_Pln& Pl);

  Standard_EXPORT void Project(const gp_Lin& L) override;

  Standard_EXPORT void Project(const gp_Circ& C) override;

  Standard_EXPORT void Project(const gp_Elips& E) override;

  Standard_EXPORT void Project(const gp_Parab& P) override;

  Standard_EXPORT void Project(const gp_Hypr& H) override;

private:
  gp_Pln myPlane;
};

