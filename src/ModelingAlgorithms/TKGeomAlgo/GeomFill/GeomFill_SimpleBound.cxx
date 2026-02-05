#include <Adaptor3d_Curve.hpp>
#include <GeomFill_SimpleBound.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Law.hpp>
#include <Law_BSpFunc.hpp>
#include <Law_Function.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_SimpleBound, GeomFill_Boundary)

//=================================================================================================

GeomFill_SimpleBound::GeomFill_SimpleBound(const occ::handle<Adaptor3d_Curve>& Curve,
                                           const double                        Tol3d,
                                           const double                        Tolang)
    : GeomFill_Boundary(Tol3d, Tolang),
      myC3d(Curve)
{
}

//=================================================================================================

gp_Pnt GeomFill_SimpleBound::Value(const double U) const
{
  double x = U;
  if (!myPar.IsNull())
    x = myPar->Value(U);
  return myC3d->Value(x);
}

//=================================================================================================

void GeomFill_SimpleBound::D1(const double U, gp_Pnt& P, gp_Vec& V) const
{
  double x = U, dx = 1.;
  if (!myPar.IsNull())
    myPar->D1(U, x, dx);
  myC3d->D1(x, P, V);
  V.Multiply(dx);
}

//=================================================================================================

void GeomFill_SimpleBound::Reparametrize(const double First,
                                         const double Last,
                                         const bool   HasDF,
                                         const bool   HasDL,
                                         const double DF,
                                         const double DL,
                                         const bool   Rev)
{
  occ::handle<Law_BSpline> curve =
    Law::Reparametrize(*myC3d, First, Last, HasDF, HasDL, DF, DL, Rev, 30);
  myPar = new Law_BSpFunc();
  occ::down_cast<Law_BSpFunc>(myPar)->SetCurve(curve);
}

//=================================================================================================

void GeomFill_SimpleBound::Bounds(double& First, double& Last) const
{
  if (!myPar.IsNull())
    myPar->Bounds(First, Last);
  else
  {
    First = myC3d->FirstParameter();
    Last  = myC3d->LastParameter();
  }
}

//=================================================================================================

bool GeomFill_SimpleBound::IsDegenerated() const
{
  return false;
}
