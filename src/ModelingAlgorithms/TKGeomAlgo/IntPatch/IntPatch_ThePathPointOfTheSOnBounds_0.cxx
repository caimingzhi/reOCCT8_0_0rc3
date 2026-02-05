#include <IntPatch_ThePathPointOfTheSOnBounds.hpp>

#include <Adaptor3d_HVertex.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Standard_DomainError.hpp>
#include <gp_Pnt.hpp>

IntPatch_ThePathPointOfTheSOnBounds::IntPatch_ThePathPointOfTheSOnBounds()
    : tol(0.0),
      isnew(true),
      param(0.0)
{
}

IntPatch_ThePathPointOfTheSOnBounds::IntPatch_ThePathPointOfTheSOnBounds(
  const gp_Pnt&                         P,
  const double                          Tol,
  const occ::handle<Adaptor3d_HVertex>& V,
  const occ::handle<Adaptor2d_Curve2d>& A,
  const double                          Parameter)
    : point(P),
      tol(Tol),
      isnew(false),
      vtx(V),
      arc(A),
      param(Parameter)
{
}

IntPatch_ThePathPointOfTheSOnBounds::IntPatch_ThePathPointOfTheSOnBounds(
  const gp_Pnt&                         P,
  const double                          Tol,
  const occ::handle<Adaptor2d_Curve2d>& A,
  const double                          Parameter)
    : point(P),
      tol(Tol),
      isnew(true),
      arc(A),
      param(Parameter)
{
}
