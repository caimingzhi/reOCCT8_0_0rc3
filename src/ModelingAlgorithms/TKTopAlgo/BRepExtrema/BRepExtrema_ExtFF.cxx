#include <BRepExtrema_ExtFF.hpp>

#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <BRepClass_FaceClassifier.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <BRepAdaptor_Surface.hpp>

BRepExtrema_ExtFF::BRepExtrema_ExtFF(const TopoDS_Face& F1, const TopoDS_Face& F2)
{
  Initialize(F2);
  Perform(F1, F2);
}

void BRepExtrema_ExtFF::Initialize(const TopoDS_Face& F2)
{
  BRepAdaptor_Surface Surf(F2);
  if (Surf.GetType() == GeomAbs_OtherSurface)
    return;

  myHS       = new BRepAdaptor_Surface(Surf);
  double Tol = std::min(BRep_Tool::Tolerance(F2), Precision::Confusion());
  Tol        = std::min(Surf.UResolution(Tol), Surf.VResolution(Tol));
  Tol        = std::max(Tol, Precision::PConfusion());
  double U1, U2, V1, V2;
  BRepTools::UVBounds(F2, U1, U2, V1, V2);
  myExtSS.Initialize(*myHS, U1, U2, V1, V2, Tol);
}

void BRepExtrema_ExtFF::Perform(const TopoDS_Face& F1, const TopoDS_Face& F2)
{
  mySqDist.Clear();
  myPointsOnS1.Clear();
  myPointsOnS2.Clear();

  BRepAdaptor_Surface Surf1(F1);
  if (myHS.IsNull() || Surf1.GetType() == GeomAbs_OtherSurface)
    return;

  occ::handle<BRepAdaptor_Surface> HS1 = new BRepAdaptor_Surface(Surf1);
  double Tol1                          = std::min(BRep_Tool::Tolerance(F1), Precision::Confusion());
  Tol1                                 = std::min(Surf1.UResolution(Tol1), Surf1.VResolution(Tol1));
  Tol1                                 = std::max(Tol1, Precision::PConfusion());
  double U1, U2, V1, V2;
  BRepTools::UVBounds(F1, U1, U2, V1, V2);
  myExtSS.Perform(*HS1, U1, U2, V1, V2, Tol1);

  if (!myExtSS.IsDone())
    return;

  if (myExtSS.IsParallel())
    mySqDist.Append(myExtSS.SquareDistance(1));
  else
  {

    BRepClass_FaceClassifier classifier;
    const double             Tol2 = BRep_Tool::Tolerance(F2);
    Extrema_POnSurf          P1, P2;

    int i;
    for (i = 1; i <= myExtSS.NbExt(); i++)
    {
      myExtSS.Points(i, P1, P2);
      P1.Parameter(U1, U2);
      const gp_Pnt2d Puv1(U1, U2);
      classifier.Perform(F1, Puv1, Tol1);
      const TopAbs_State state1 = classifier.State();
      if (state1 == TopAbs_ON || state1 == TopAbs_IN)
      {
        P2.Parameter(U1, U2);
        const gp_Pnt2d Puv2(U1, U2);
        classifier.Perform(F2, Puv2, Tol2);
        const TopAbs_State state2 = classifier.State();
        if (state2 == TopAbs_ON || state2 == TopAbs_IN)
        {
          mySqDist.Append(myExtSS.SquareDistance(i));
          myPointsOnS1.Append(P1);
          myPointsOnS2.Append(P2);
        }
      }
    }
  }
}
