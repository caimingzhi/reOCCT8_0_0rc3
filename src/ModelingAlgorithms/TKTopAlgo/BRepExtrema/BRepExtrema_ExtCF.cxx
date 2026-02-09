#include <BRepExtrema_ExtCF.hpp>

#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <BRepTopAdaptor_FClass2d.hpp>
#include <gp_Pnt2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepAdaptor_Curve.hpp>

BRepExtrema_ExtCF::BRepExtrema_ExtCF(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  Initialize(E, F);
  Perform(E, F);
}

void BRepExtrema_ExtCF::Initialize(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  BRepAdaptor_Surface Surf(F);
  if (Surf.GetType() == GeomAbs_OtherSurface || !BRep_Tool::IsGeometric(E))
    return;
  BRepAdaptor_Curve aC(E);
  myHS = new BRepAdaptor_Surface(Surf);
  double aTolC, aTolS;

  aTolS = std::min(BRep_Tool::Tolerance(F), Precision::Confusion());
  aTolS = std::min(Surf.UResolution(aTolS), Surf.VResolution(aTolS));
  aTolS = std::max(aTolS, Precision::PConfusion());

  aTolC = std::min(BRep_Tool::Tolerance(E), Precision::Confusion());
  aTolC = aC.Resolution(aTolC);
  aTolC = std::max(aTolC, Precision::PConfusion());

  double U1, U2, V1, V2;
  BRepTools::UVBounds(F, U1, U2, V1, V2);
  myExtCS.Initialize(*myHS, U1, U2, V1, V2, aTolC, aTolS);
}

void BRepExtrema_ExtCF::Perform(const TopoDS_Edge& E, const TopoDS_Face& F2)
{
  mySqDist.Clear();
  myPointsOnS.Clear();
  myPointsOnC.Clear();

  if (myHS.IsNull())
    return;

  double U1, U2;
  BRep_Tool::Range(E, U1, U2);

  BRepAdaptor_Curve              Curv(E);
  occ::handle<BRepAdaptor_Curve> HC = new BRepAdaptor_Curve(Curv);
  myExtCS.Perform(*HC, U1, U2);

  if (!myExtCS.IsDone())
    return;

  if (myExtCS.IsParallel())
    mySqDist.Append(myExtCS.SquareDistance(1));
  else
  {

    const double            Tol = BRep_Tool::Tolerance(F2);
    BRepTopAdaptor_FClass2d classifier(F2, Tol);

    bool isAdjustPeriodic = false;

    Extrema_POnCurv P1;
    Extrema_POnSurf P2;

    for (int i = 1; i <= myExtCS.NbExt(); i++)
    {
      myExtCS.Points(i, P1, P2);
      P2.Parameter(U1, U2);
      const gp_Pnt2d     Puv(U1, U2);
      const TopAbs_State state = classifier.Perform(Puv, isAdjustPeriodic);
      if (state == TopAbs_ON || state == TopAbs_IN)
      {
        mySqDist.Append(myExtCS.SquareDistance(i));
        myPointsOnC.Append(P1);
        myPointsOnS.Append(P2);
      }
    }
  }
}
