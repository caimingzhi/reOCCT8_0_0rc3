#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepFill_CurveConstraint.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomPlate_CurveConstraint.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <ProjLib_ProjectOnPlane.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_CurveConstraint, GeomPlate_CurveConstraint)

BRepFill_CurveConstraint ::BRepFill_CurveConstraint(
  const occ::handle<Adaptor3d_CurveOnSurface>& Boundary,
  const int                                    Tang,
  const int                                    NPt,
  const double                                 TolDist,
  const double                                 TolAng,
  const double                                 TolCurv)
{
  myFrontiere = Boundary;
  myTolDist   = TolDist;
  myTolAng    = TolAng;
  myTolCurv   = TolCurv;
  GeomLProp_SLProps SLP(2, TolDist);
  myLProp = SLP;
  myOrder = Tang;
  if ((Tang < -1) || (Tang > 2))
    throw Standard_Failure("BRepFill : The continuity is not G0 G1 or G2");
  myNbPoints = NPt;
  myConstG0  = true;
  myConstG1  = true;
  myConstG2  = true;
  if (myFrontiere.IsNull())
    throw Standard_Failure("BRepFill_CurveConstraint : Curve must be on a Surface");
  occ::handle<Geom_Surface>        Surf;
  occ::handle<GeomAdaptor_Surface> GS1;
  GS1 = occ::down_cast<GeomAdaptor_Surface>(myFrontiere->GetSurface());
  if (!GS1.IsNull())
  {
    Surf = GS1->Surface();
  }
  else
  {
    occ::handle<BRepAdaptor_Surface> BS1;
    BS1  = occ::down_cast<BRepAdaptor_Surface>(myFrontiere->GetSurface());
    Surf = BRep_Tool::Surface(BS1->Face());
  }
  myLProp.SetSurface(Surf);
}

BRepFill_CurveConstraint ::BRepFill_CurveConstraint(const occ::handle<Adaptor3d_Curve>& Boundary,
                                                    const int                           Tang,
                                                    const int                           NPt,
                                                    const double                        TolDist)
    : GeomPlate_CurveConstraint(Boundary, Tang, NPt, TolDist)

{
}
