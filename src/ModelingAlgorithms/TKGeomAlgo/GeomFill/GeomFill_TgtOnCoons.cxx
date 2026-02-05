#include <GeomFill_Boundary.hpp>
#include <GeomFill_CoonsAlgPatch.hpp>
#include <GeomFill_TgtOnCoons.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_TgtOnCoons, GeomFill_TgtField)

//=================================================================================================

GeomFill_TgtOnCoons::GeomFill_TgtOnCoons(const occ::handle<GeomFill_CoonsAlgPatch>& K, const int I)
    : myK(K),
      ibound(I)
{
}

//=================================================================================================

gp_Vec GeomFill_TgtOnCoons::Value(const double W) const
{
  double U = 0., V = 0., bid = 0.;
  switch (ibound)
  {
    case 0:
      myK->Bound(1)->Bounds(V, bid);
      break;
    case 1:
      myK->Bound(0)->Bounds(bid, U);
      break;
    case 2:
      myK->Bound(1)->Bounds(bid, V);
      break;
    case 3:
      myK->Bound(0)->Bounds(U, bid);
      break;
  }

  gp_Vec tgk;

  switch (ibound)
  {
    case 0:
    case 2:
      U   = W;
      tgk = myK->D1V(U, V);
      break;
    case 1:
    case 3:
      V   = W;
      tgk = myK->D1U(U, V);
      break;
  }

  gp_Vec n    = myK->Bound(ibound)->Norm(W);
  double scal = tgk.Dot(n);
  n.Multiply(-scal);
  tgk.Add(n);
  return tgk;
}

//=================================================================================================

gp_Vec GeomFill_TgtOnCoons::D1(const double W) const
{
  double U = 0., V = 0., bid = 0.;
  switch (ibound)
  {
    case 0:
      myK->Bound(1)->Bounds(V, bid);
      break;
    case 1:
      myK->Bound(0)->Bounds(bid, U);
      break;
    case 2:
      myK->Bound(1)->Bounds(bid, V);
      break;
    case 3:
      myK->Bound(0)->Bounds(U, bid);
      break;
  }

  gp_Vec tgsc, dtgsc;

  switch (ibound)
  {
    case 0:
    case 2:
      U    = W;
      tgsc = myK->D1V(U, V);
      break;
    case 1:
    case 3:
      V    = W;
      tgsc = myK->D1U(U, V);
      break;
  }
  dtgsc = myK->DUV(U, V);

  gp_Vec n, dn;
  myK->Bound(ibound)->D1Norm(W, n, dn);

  double scal  = tgsc.Dot(n);
  gp_Vec scaln = n.Multiplied(-scal);
  tgsc.Add(scaln);

  gp_Vec scaldn = dn.Multiplied(-scal);

  double scal2 = -dtgsc.Dot(n) - tgsc.Dot(dn);
  gp_Vec temp  = n.Multiplied(scal2);

  temp.Add(scaldn);
  gp_Vec dtpur = dtgsc.Added(temp);

  return dtpur;
}

//=================================================================================================

void GeomFill_TgtOnCoons::D1(const double W, gp_Vec& T, gp_Vec& DT) const
{
  double U = 0., V = 0., bid = 0.;
  switch (ibound)
  {
    case 0:
      myK->Bound(1)->Bounds(V, bid);
      break;
    case 1:
      myK->Bound(0)->Bounds(bid, U);
      break;
    case 2:
      myK->Bound(1)->Bounds(bid, V);
      break;
    case 3:
      myK->Bound(0)->Bounds(U, bid);
      break;
  }

  gp_Vec tgsc, dtgsc;

  switch (ibound)
  {
    case 0:
    case 2:
      U    = W;
      tgsc = myK->D1V(U, V);
      break;
    case 1:
    case 3:
      V    = W;
      tgsc = myK->D1U(U, V);
      break;
  }
  dtgsc = myK->DUV(U, V);

  gp_Vec n, dn;
  myK->Bound(ibound)->D1Norm(W, n, dn);

  double scal  = tgsc.Dot(n);
  gp_Vec scaln = n.Multiplied(-scal);
  T            = tgsc.Added(scaln);

  gp_Vec scaldn = dn.Multiplied(-scal);

  double scal2 = -dtgsc.Dot(n) - tgsc.Dot(dn);
  gp_Vec temp  = n.Multiplied(scal2);

  temp.Add(scaldn);
  DT = dtgsc.Added(temp);
}
