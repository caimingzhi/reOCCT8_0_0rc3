#include <Contap_ThePathPointOfTheSearch.hpp>

#include <Adaptor3d_HVertex.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Standard_DomainError.hpp>
#include <gp_Pnt.hpp>

Contap_ThePathPointOfTheSearch::Contap_ThePathPointOfTheSearch()
    : tol(0.0),
      isnew(true),
      param(0.0)
{
}

Contap_ThePathPointOfTheSearch::Contap_ThePathPointOfTheSearch(
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

Contap_ThePathPointOfTheSearch::Contap_ThePathPointOfTheSearch(
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
