#include <BRep_Tool.hpp>
#include <BRepClass3d_Intersector3d.hpp>
#include <BRepClass3d_SClassifier.hpp>
#include <BRepClass3d_SolidExplorer.hpp>
#include <ElCLib.hpp>
#include <Geom_Surface.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <IntCurvesFace_Intersector.hpp>
#include <math_BullardGenerator.hpp>
#include <TopoDS.hpp>
#include <TopExp.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Extrema_ExtPS.hpp>

#include <vector>

static bool FaceNormal(const TopoDS_Face& aF, const double U, const double V, gp_Dir& aDN);

static double GetAddToParam(const gp_Lin& L, const double P, const Bnd_Box& B);

static int GetTransi(const TopoDS_Face&                 f1,
                     const TopoDS_Face&                 f2,
                     const TopoDS_Edge&                 e,
                     double                             param,
                     const gp_Lin&                      L,
                     IntCurveSurface_TransitionOnCurve& trans);

static bool GetNormalOnFaceBound(const TopoDS_Edge& E,
                                 const TopoDS_Face& F,
                                 double             param,
                                 gp_Dir&            OutDir);

static void Trans(double parmin, IntCurveSurface_TransitionOnCurve& tran, int& state);

BRepClass3d_SClassifier::BRepClass3d_SClassifier()
    : myState(0)
{
}

BRepClass3d_SClassifier::BRepClass3d_SClassifier(BRepClass3d_SolidExplorer& S,
                                                 const gp_Pnt&              P,
                                                 const double               Tol)
{
  if (S.Reject(P))
  {
    myState = 3;
  }
  else
  {
    Perform(S, P, Tol);
  }
}

void BRepClass3d_SClassifier::PerformInfinitePoint(BRepClass3d_SolidExplorer& aSE, const double)
{

  if (aSE.Reject(gp_Pnt(0, 0, 0)))
  {
    myState = 3;
    return;
  }

  bool   bFound;
  double aParam, aU = 0., aV = 0.;
  gp_Pnt aPoint;
  gp_Dir aDN;

  math_BullardGenerator aRandomGenerator;
  myFace.Nullify();
  myState = 2;

  std::vector<TopoDS_Face> aFaces;
  for (aSE.InitShell(); aSE.MoreShell(); aSE.NextShell())
  {
    for (aSE.InitFace(); aSE.MoreFace(); aSE.NextFace())
    {
      aFaces.push_back(aSE.CurrentFace());
    }
  }

  const int NB_MAX_POINTS_PER_FACE = 10;
  for (int itry = 0; itry < NB_MAX_POINTS_PER_FACE; itry++)
  {
    for (std::vector<TopoDS_Face>::iterator iFace = aFaces.begin(); iFace != aFaces.end(); ++iFace)
    {
      TopoDS_Face aF = *iFace;

      TopAbs_State                      aState      = TopAbs_OUT;
      IntCurveSurface_TransitionOnCurve aTransition = IntCurveSurface_Tangent;

      aParam = 0.1 + 0.8 * aRandomGenerator.NextReal();
      bFound = BRepClass3d_SolidExplorer::FindAPointInTheFace(aF, aPoint, aU, aV, aParam);
      if (!bFound || !FaceNormal(aF, aU, aV, aDN))
        continue;

      gp_Lin aLin(aPoint, -aDN);
      double parmin = RealLast();
      for (aSE.InitShell(); aSE.MoreShell(); aSE.NextShell())
      {
        if (!aSE.RejectShell(aLin))
        {
          for (aSE.InitFace(); aSE.MoreFace(); aSE.NextFace())
          {
            if (!aSE.RejectFace(aLin))
            {
              TopoDS_Shape               aLocalShape   = aSE.CurrentFace();
              TopoDS_Face                CurFace       = TopoDS::Face(aLocalShape);
              IntCurvesFace_Intersector& Intersector3d = aSE.Intersector(CurFace);
              Intersector3d.Perform(aLin, -RealLast(), parmin);

              if (Intersector3d.IsDone())
              {
                if (Intersector3d.NbPnt())
                {
                  int imin = 1;
                  for (int i = 2; i <= Intersector3d.NbPnt(); i++)
                    if (Intersector3d.WParameter(i) < Intersector3d.WParameter(imin))
                      imin = i;
                  parmin      = Intersector3d.WParameter(imin);
                  aState      = Intersector3d.State(imin);
                  aTransition = Intersector3d.Transition(imin);
                }
              }
            }
          }
        }
        else
          myState = 1;
      }

      if (aState == TopAbs_IN)
      {
        if (aTransition == IntCurveSurface_Out)
        {

          myState = 3;
          return;
        }
        else if (aTransition == IntCurveSurface_In)
        {
          myState = 4;
          return;
        }
      }
    }
  }
}

void BRepClass3d_SClassifier::Perform(BRepClass3d_SolidExplorer& SolidExplorer,
                                      const gp_Pnt&              P,
                                      const double               Tol)
{
  if (SolidExplorer.Reject(P))
  {

    myState = 3;
    return;
  }

  const NCollection_UBTree<int, Bnd_Box>& aTree = SolidExplorer.GetTree();
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapEV =
    SolidExplorer.GetMapEV();

  BRepClass3d_BndBoxTreeSelectorPoint aSelectorPoint(aMapEV);
  aSelectorPoint.SetCurrentPoint(P);

  int SelsVE = 0;
  SelsVE     = aTree.Select(aSelectorPoint);

  if (SelsVE > 0)
  {

    myState = 2;
    return;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    mapEF;
  TopExp::MapShapesAndAncestors(SolidExplorer.GetShape(), TopAbs_EDGE, TopAbs_FACE, mapEF);

  BRepClass3d_BndBoxTreeSelectorLine aSelectorLine(aMapEV);

  myFace.Nullify();
  myState = 0;

  gp_Lin L;
  double Par;

  int iFlag;

  bool   isFaultyLine = true;
  int    anIndFace    = 0;
  double parmin       = 0.0;
  while (isFaultyLine)
  {
    if (anIndFace == 0)
      iFlag = SolidExplorer.Segment(P, L, Par);
    else
      iFlag = SolidExplorer.OtherSegment(P, L, Par);

    int aCurInd = SolidExplorer.GetFaceSegmentIndex();

    if (aCurInd > anIndFace)
      anIndFace = aCurInd;
    else
    {
      myState = 1;
      return;
    }

    if (iFlag == 1)
    {

      myState = 2;
      return;
    }
    if (iFlag == 2)
    {
      myState = 4;
      return;
    }

    if (iFlag == 3)
      continue;

    isFaultyLine = false;
    parmin       = RealLast();

    double NearFaultPar = RealLast();
    aSelectorLine.ClearResults();
    aSelectorLine.SetCurrentLine(L, Par);
    int SelsEVL = 0;
    SelsEVL     = aTree.Select(aSelectorLine);

    if (SelsEVL > 0)
    {

      int           VLInterNb = aSelectorLine.GetNbVertParam();
      TopoDS_Vertex NearIntVert;
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> LVInts;
      for (int i = 1; i <= VLInterNb; i++)
      {

        double        LP = 0;
        TopoDS_Vertex V;
        aSelectorLine.GetVertParam(i, V, LP);

        LVInts.Add(V);
        if (std::abs(LP) < std::abs(NearFaultPar))
          NearFaultPar = LP;
      }

      double      param = 0.0;
      TopoDS_Edge EE;
      double      Lpar = RealLast();
      for (int i = 1; i <= aSelectorLine.GetNbEdgeParam(); i++)
      {

        aSelectorLine.GetEdgeParam(i, EE, param, Lpar);
        const NCollection_List<TopoDS_Shape>& ffs = mapEF.FindFromKey(EE);
        if (ffs.Extent() != 2)
          continue;
        TopoDS_Face   f1 = TopoDS::Face(ffs.First());
        TopoDS_Face   f2 = TopoDS::Face(ffs.Last());
        TopoDS_Vertex V1, V2;
        TopExp::Vertices(EE, V1, V2);
        if (LVInts.Contains(V1) || LVInts.Contains(V2))
        {
          continue;
        }

        IntCurveSurface_TransitionOnCurve tran = IntCurveSurface_Tangent;
        int                               Tst  = GetTransi(f1, f2, EE, param, L, tran);
        if (Tst == 1 && std::abs(Lpar) < std::abs(parmin))
        {
          parmin = Lpar;
          Trans(parmin, tran, myState);
        }
        else if (std::abs(Lpar) < std::abs(NearFaultPar))
          NearFaultPar = Lpar;
      }
    }

    for (SolidExplorer.InitShell(); SolidExplorer.MoreShell() && !isFaultyLine;
         SolidExplorer.NextShell())
    {
      if (!SolidExplorer.RejectShell(L))
      {
        for (SolidExplorer.InitFace(); SolidExplorer.MoreFace() && !isFaultyLine;
             SolidExplorer.NextFace())
        {
          if (!SolidExplorer.RejectFace(L))
          {
            TopoDS_Shape               aLocalShape   = SolidExplorer.CurrentFace();
            TopoDS_Face                f             = TopoDS::Face(aLocalShape);
            IntCurvesFace_Intersector& Intersector3d = SolidExplorer.Intersector(f);

            double addW = std::max(10 * Tol, 0.01 * Par);
            double AddW = addW;

            Bnd_Box aBoxF = Intersector3d.Bounding();

            if (!aBoxF.IsVoid() && !aBoxF.IsWhole())
            {
              double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
              aBoxF.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

              double boxaddW = GetAddToParam(L, Par, aBoxF);
              addW           = std::max(addW, boxaddW);
            }

            double minW = -AddW;
            double maxW = std::min(Par * 10, Par + addW);
            Intersector3d.Perform(L, minW, maxW);
            if (Intersector3d.IsDone())
            {
              if (Intersector3d.NbPnt() == 0)
              {
                if (Intersector3d.IsParallel())
                {

                  BRepAdaptor_Surface aBAS(f, false);
                  Extrema_ExtPS       aProj(P,
                                      aBAS,
                                      Precision::PConfusion(),
                                      Precision::PConfusion(),
                                      Extrema_ExtFlag_MIN);
                  if (aProj.IsDone() && aProj.NbExt() > 0)
                  {
                    int    i, indmin = 0;
                    double d = RealLast();
                    for (i = 1; i <= aProj.NbExt(); ++i)
                    {
                      if (aProj.SquareDistance(i) < d)
                      {
                        d      = aProj.SquareDistance(i);
                        indmin = i;
                      }
                    }
                    if (indmin > 0)
                    {
                      if (d <= Tol * Tol)
                      {
                        const Extrema_POnSurf& aPonS = aProj.Point(indmin);
                        double                 anU, anV;
                        aPonS.Parameter(anU, anV);
                        gp_Pnt2d     aP2d(anU, anV);
                        TopAbs_State aSt = Intersector3d.ClassifyUVPoint(aP2d);
                        if (aSt == TopAbs_IN || aSt == TopAbs_ON)
                        {
                          myState = 2;
                          myFace  = f;
                          parmin  = 0.;
                          break;
                        }
                      }
                    }
                  }
                }
              }
              for (int i = 1; i <= Intersector3d.NbPnt(); i++)
              {
                if (std::abs(Intersector3d.WParameter(i))
                    < std::abs(parmin) - Precision::PConfusion())
                {
                  parmin              = Intersector3d.WParameter(i);
                  TopAbs_State aState = Intersector3d.State(i);
                  if (std::abs(parmin) <= Tol)
                  {
                    myState = 2;
                    myFace  = f;
                    break;
                  }

                  else if (aState == TopAbs_IN)
                  {

                    IntCurveSurface_TransitionOnCurve tran = Intersector3d.Transition(i);
                    if (tran == IntCurveSurface_Tangent)
                    {
#ifdef OCCT_DEBUG
                      std::cout << "*Problem ds BRepClass3d_SClassifier.cxx" << std::endl;
#endif
                      continue;
                    }

                    Trans(parmin, tran, myState);
                    myFace = f;
                  }

                  else if (aState == TopAbs_ON)
                  {
                    isFaultyLine = true;
                    break;
                  }
                }
                else
                {
                }
              }
              if (myState == 2)
              {
                break;
              }
            }
            else
              myState = 1;
          }
        }
        if (myState == 2)
        {
          break;
        }
      }
      else
        myState = 1;
    }

    if (NearFaultPar != RealLast()
        && std::abs(parmin) >= std::abs(NearFaultPar) - Precision::PConfusion())
    {
      isFaultyLine = true;
    }
  }

#ifdef OCCT_DEBUG

  SolidExplorer.DumpSegment(P, L, parmin, State());

#endif
}

TopAbs_State BRepClass3d_SClassifier::State() const
{
  if (myState == 2)
    return (TopAbs_ON);
  else if (myState == 3)
    return (TopAbs_IN);
  else if (myState == 4)
    return (TopAbs_OUT);

  return (TopAbs_OUT);
}

TopoDS_Face BRepClass3d_SClassifier::Face() const
{
  return (myFace);
}

bool BRepClass3d_SClassifier::Rejected() const
{
  return (myState == 1);
}

bool BRepClass3d_SClassifier::IsOnAFace() const
{
  return (myState == 2);
}

void BRepClass3d_SClassifier::ForceIn()
{
  myState = 3;
}

void BRepClass3d_SClassifier::ForceOut()
{
  myState = 4;
}

double GetAddToParam(const gp_Lin& L, const double P, const Bnd_Box& B)
{
  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  B.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  double x[2] = {aXmin, aXmax}, y[2] = {aYmin, aYmax}, z[2] = {aZmin, aZmax};
  int    i = 0, j = 0, k = 0;
  double Par = P;
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 2; j++)
    {
      for (k = 0; k < 2; k++)
      {
        double X = fabs(x[i] - L.Location().X());
        double Y = fabs(y[j] - L.Location().Y());
        double Z = fabs(z[k] - L.Location().Z());
        if (X < 1.e+20 && Y < 1.e+20 && Z < 1.e+20)
        {
          gp_Pnt aP(x[i], y[j], z[k]);
          double par = ElCLib::Parameter(L, aP);
          if (par > Par)
            Par = par;
        }
        else
          return 1.e+20;
      }
    }
  }
  return Par - P;
}

bool FaceNormal(const TopoDS_Face& aF, const double U, const double V, gp_Dir& aDN)
{
  gp_Pnt                    aPnt;
  gp_Vec                    aD1U, aD1V, aN;
  occ::handle<Geom_Surface> aS;

  aS = BRep_Tool::Surface(aF);
  aS->D1(U, V, aPnt, aD1U, aD1V);
  aN = aD1U.Crossed(aD1V);
  if (aN.Magnitude() <= gp::Resolution())
    return false;

  aN.Normalize();
  aDN.SetXYZ(aN.XYZ());
  if (aF.Orientation() == TopAbs_REVERSED)
  {
    aDN.Reverse();
  }
  return true;
}

static bool GetNormalOnFaceBound(const TopoDS_Edge& E,
                                 const TopoDS_Face& F,
                                 const double       param,
                                 gp_Dir&            OutDir)
{
  double f = 0, l = 0;

  gp_Pnt2d                  P2d;
  occ::handle<Geom2d_Curve> c2d = BRep_Tool::CurveOnSurface(E, F, f, l);
  if (c2d.IsNull())
    return false;
  if (param < f || param > l)
    return false;
  c2d->D0(param, P2d);
  return FaceNormal(F, P2d.X(), P2d.Y(), OutDir);
}

static int GetTransi(const TopoDS_Face&                 f1,
                     const TopoDS_Face&                 f2,
                     const TopoDS_Edge&                 e,
                     const double                       param,
                     const gp_Lin&                      L,
                     IntCurveSurface_TransitionOnCurve& trans)
{

  gp_Dir nf1, nf2;
  if (!GetNormalOnFaceBound(e, f1, param, nf1))
    return -1;
  if (!GetNormalOnFaceBound(e, f2, param, nf2))
    return -1;

  const gp_Dir& LDir = L.Direction();

  if (std::abs(LDir.Dot(nf1)) < Precision::Angular()
      || std::abs(LDir.Dot(nf2)) < Precision::Angular())
  {

    return -1;
  }

  if (nf1.IsParallel(nf2, Precision::Angular()))
  {
    double angD = nf1.Dot(LDir);
    if (std::abs(angD) < Precision::Angular())
      return -1;
    else if (angD > 0)
      trans = IntCurveSurface_Out;
    else
      trans = IntCurveSurface_In;
    return 1;
  }

  gp_Vec N = nf1 ^ nf2;

  gp_Dir ProjL = N.XYZ() ^ LDir.XYZ() ^ N.XYZ();

  double fAD = nf1.Dot(ProjL);
  double sAD = nf2.Dot(ProjL);

  if (fAD < -Precision::Angular() && sAD < -Precision::Angular())
    trans = IntCurveSurface_In;
  else if (fAD > Precision::Angular() && sAD > Precision::Angular())
    trans = IntCurveSurface_Out;
  else
    return 0;
  return 1;
}

static void Trans(const double parmin, IntCurveSurface_TransitionOnCurve& tran, int& state)
{

  if (parmin < 0)
    tran = (tran == IntCurveSurface_Out ? IntCurveSurface_In : IntCurveSurface_Out);

  if (tran == IntCurveSurface_Out)

    state = 3;
  else
    state = 4;
}
