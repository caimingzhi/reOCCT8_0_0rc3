#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Torus.hpp>
#include <ProjLib_Projector.hpp>
class gp_Circ;
class gp_Lin;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

//! Projects elementary curves on a torus.
class ProjLib_Torus : public ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  //! Undefined projection.
  Standard_EXPORT ProjLib_Torus();

  //! Projection on the torus <To>.
  Standard_EXPORT ProjLib_Torus(const gp_Torus& To);

  //! Projection of the circle <C> on the torus <To>.
  Standard_EXPORT ProjLib_Torus(const gp_Torus& To, const gp_Circ& C);

  Standard_EXPORT void Init(const gp_Torus& To);

  Standard_EXPORT void Project(const gp_Lin& L) override;

  Standard_EXPORT void Project(const gp_Circ& C) override;

  Standard_EXPORT void Project(const gp_Elips& E) override;

  Standard_EXPORT void Project(const gp_Parab& P) override;

  Standard_EXPORT void Project(const gp_Hypr& H) override;

private:
  gp_Torus myTorus;
};

