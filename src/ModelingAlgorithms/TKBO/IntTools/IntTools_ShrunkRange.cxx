#include <BRepLib.hpp>
#include <BndLib_Add3dCurve.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <IntTools_ShrunkRange.hpp>
#include <Precision.hpp>

IntTools_ShrunkRange::IntTools_ShrunkRange()
{
  myT1           = -99;
  myT2           = myT1;
  myTS1          = myT1;
  myTS2          = myT1;
  myIsDone       = false;
  myIsSplittable = false;
  myLength       = 0.0;
}

IntTools_ShrunkRange::~IntTools_ShrunkRange() = default;

void IntTools_ShrunkRange::SetData(const TopoDS_Edge&   aE,
                                   const double         aT1,
                                   const double         aT2,
                                   const TopoDS_Vertex& aV1,
                                   const TopoDS_Vertex& aV2)
{
  myEdge         = aE;
  myV1           = aV1;
  myV2           = aV2;
  myT1           = aT1;
  myT2           = aT2;
  myIsDone       = false;
  myIsSplittable = false;
  myLength       = 0.0;
}

void IntTools_ShrunkRange::SetContext(const occ::handle<IntTools_Context>& aCtx)
{
  myCtx = aCtx;
}

const occ::handle<IntTools_Context>& IntTools_ShrunkRange::Context() const
{
  return myCtx;
}

const TopoDS_Edge& IntTools_ShrunkRange::Edge() const
{
  return myEdge;
}

void IntTools_ShrunkRange::ShrunkRange(double& aT1, double& aT2) const
{
  aT1 = myTS1;
  aT2 = myTS2;
}

const Bnd_Box& IntTools_ShrunkRange::BndBox() const
{
  return myBndBox;
}

void IntTools_ShrunkRange::SetShrunkRange(const double aT1, const double aT2)
{
  myTS1 = aT1;
  myTS2 = aT2;

  BRepAdaptor_Curve aBAC(myEdge);
  BndLib_Add3dCurve::Add(aBAC, aT1, aT2, 0., myBndBox);
}

void IntTools_ShrunkRange::Perform()
{
  myIsDone       = false;
  myIsSplittable = false;

  double aDTol = Precision::Confusion();

  double aPDTol = Precision::PConfusion();

  if (myT2 - myT1 < aPDTol)
  {
    return;
  }

  gp_Pnt aP1 = BRep_Tool::Pnt(myV1);
  gp_Pnt aP2 = BRep_Tool::Pnt(myV2);
  double aTolE, aTolV1, aTolV2;
  aTolE  = BRep_Tool::Tolerance(myEdge);
  aTolV1 = BRep_Tool::Tolerance(myV1);
  aTolV2 = BRep_Tool::Tolerance(myV2);

  if (aTolV1 < aTolE)
  {
    aTolV1 = aTolE;
  }

  if (aTolV2 < aTolE)
  {
    aTolV2 = aTolE;
  }

  aTolV1 += aDTol;
  aTolV2 += aDTol;

  BRepAdaptor_Curve aBAC(myEdge);
  if (!BRepLib::FindValidRange(aBAC, aTolE, myT1, aP1, aTolV1, myT2, aP2, aTolV2, myTS1, myTS2))
  {

    return;
  }
  if ((myTS2 - myTS1) < aPDTol)
  {

    return;
  }

  double aPTolE = aBAC.Resolution(aTolE);

  double aPTolEMin = (myT2 - myT1) / 100.;
  if (aPTolE > aPTolEMin)
  {
    aPTolE = aPTolEMin;
  }
  myLength = GCPnts_AbscissaPoint::Length(aBAC, myTS1, myTS2, aPTolE);
  if (myLength < aDTol)
  {

    return;
  }

  myIsDone = true;

  if (myLength > (2 * aTolE + 2 * aDTol))
  {
    myIsSplittable = true;
  }

  BndLib_Add3dCurve::Add(aBAC, myTS1, myTS2, aTolE + aDTol, myBndBox);
}
