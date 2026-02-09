#include <BOPTools_AlgoTools2D.hpp>

#include <gp_Vec2d.hpp>
#include <gp_Dir2d.hpp>

#include <Geom2d_TrimmedCurve.hpp>
#include <GeomLib.hpp>

#include <GeomAPI_ProjectPointOnCurve.hpp>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>

#include <TopExp_Explorer.hpp>

#include <IntTools_Context.hpp>
#include <IntTools_Tools.hpp>

#include <BOPTools_AlgoTools.hpp>

static int  UpdateClosedPCurve(const TopoDS_Edge&,
                               const TopoDS_Edge&,
                               const TopoDS_Face&,
                               const occ::handle<IntTools_Context>&);
static bool IsClosed(const TopoDS_Edge&, const TopoDS_Face&);

int BOPTools_AlgoTools2D::AttachExistingPCurve(const TopoDS_Edge&                   theE2,
                                               const TopoDS_Edge&                   theE1,
                                               const TopoDS_Face&                   theF,
                                               const occ::handle<IntTools_Context>& aCtx)
{
  bool                      bIsToReverse, bIsClosed, bComp;
  int                       iRet;
  double                    aTol, aT11, aT12, aT21, aT22, aTolPPC;
  double                    aTolSP, aTMax;
  occ::handle<Geom2d_Curve> aC2Dold, aC2DoldC;
  occ::handle<Geom2d_Curve> aC2DT;
  BRep_Builder              aBB;

  iRet = 0;

  TopoDS_Face aF = theF;
  aF.Orientation(TopAbs_FORWARD);
  TopoDS_Edge aE1 = theE1;
  aE1.Orientation(TopAbs_FORWARD);
  TopoDS_Edge aE2 = theE2;
  aE2.Orientation(TopAbs_FORWARD);

  aC2Dold = BRep_Tool::CurveOnSurface(aE2, aF, aT21, aT22);
  if (aC2Dold.IsNull())
  {
    iRet = 1;
    return iRet;
  }

  aC2DoldC = occ::down_cast<Geom2d_Curve>(aC2Dold->Copy());

  bIsToReverse = BOPTools_AlgoTools::IsSplitToReverse(aE1, aE2, aCtx);
  if (bIsToReverse)
  {
    double aT21r, aT22r;

    aC2DoldC->Reverse();

    aT21r = aC2DoldC->ReversedParameter(aT21);
    aT22r = aC2DoldC->ReversedParameter(aT22);
    aT21  = aT22r;
    aT22  = aT21r;
  }

  aC2DT = new Geom2d_TrimmedCurve(aC2DoldC, aT21, aT22);

  aTolPPC = Precision::PConfusion();

  occ::handle<Geom_Curve> aCE1 = BRep_Tool::Curve(aE1, aT11, aT12);

  GeomLib::SameRange(aTolPPC, aC2DT, aT21, aT22, aT11, aT12, aC2DT);

  if (aC2DT.IsNull())
  {
    iRet = 2;
    return iRet;
  }

  occ::handle<Geom_Surface> aSF = BRep_Tool::Surface(aF);

  bComp = IntTools_Tools::ComputeTolerance(aCE1, aC2DT, aSF, aT11, aT12, aTolSP, aTMax, aTolPPC);
  if (!bComp)
  {
    iRet = 3;
    return iRet;
  }

  aTol = BRep_Tool::Tolerance(aE1);

  if ((aTolSP > 10. * aTol) && aTolSP > 0.1)
  {
    iRet = 4;
    return iRet;
  }

  TopoDS_Edge aE1T;
  aBB.MakeEdge(aE1T, aCE1, aTol);
  aBB.Range(aE1T, aT11, aT12);
  aBB.SameRange(aE1T, false);
  aBB.SameParameter(aE1T, false);

  aBB.UpdateEdge(aE1T, aC2DT, aF, aTol);
  try
  {
    BRepLib::SameParameter(aE1T);
    BRepLib::SameRange(aE1T);
  }
  catch (Standard_Failure const&)
  {
    iRet = 6;
    return iRet;
  }

  bIsClosed = IsClosed(aE2, aF);
  if (bIsClosed)
  {
    iRet = UpdateClosedPCurve(aE2, aE1T, aF, aCtx);
    if (iRet)
    {
      iRet = 5;
      return iRet;
    }
  }

  aBB.Transfert(aE1T, aE1);

  double          aNewTol = BRep_Tool::Tolerance(aE1T);
  TopoDS_Iterator it(aE1);
  for (; it.More(); it.Next())
    aBB.UpdateVertex(TopoDS::Vertex(it.Value()), aNewTol);
  return iRet;
}

int UpdateClosedPCurve(const TopoDS_Edge&                   aEold,
                       const TopoDS_Edge&                   aEnew,
                       const TopoDS_Face&                   aF,
                       const occ::handle<IntTools_Context>& aCtx)
{
  bool                             bUClosed, bRevOrder;
  int                              aNbPoints, iRet;
  double                           aTS1, aTS2, aTS, aScPr, aUS1, aVS1, aUS2, aVS2, aT, aU, aV;
  double                           aT1, aT2, aTol;
  gp_Pnt2d                         aP2DS1, aP2DS2, aP2D;
  gp_Vec2d                         aV2DT, aV2D, aV2DS1, aV2DS2;
  gp_Pnt                           aP;
  occ::handle<Geom2d_Curve>        aC2D, aC2DS1, aC2DS2, aC2Dnew, aC2DoldCT;
  occ::handle<Geom2d_Curve>        aC2Dold;
  occ::handle<Geom2d_TrimmedCurve> aC2DTnew;
  occ::handle<Geom_Surface>        aS;
  TopoDS_Edge                      aES;
  BRep_Builder                     aBB;

  iRet = 0;
  aTol = BRep_Tool::Tolerance(aEnew);

  aC2DoldCT = BRep_Tool::CurveOnSurface(aEnew, aF, aT1, aT2);

  aC2Dold = BRep_Tool::CurveOnSurface(aEold, aF, aT1, aT2);

  aES = aEold;
  aES.Orientation(TopAbs_FORWARD);
  aC2DS1 = BRep_Tool::CurveOnSurface(aES, aF, aTS1, aTS2);

  aES.Orientation(TopAbs_REVERSED);
  aC2DS2 = BRep_Tool::CurveOnSurface(aES, aF, aTS1, aTS2);

  aTS = BOPTools_AlgoTools2D::IntermediatePoint(aTS1, aTS2);

  aC2DS1->D1(aTS, aP2DS1, aV2DS1);
  aC2DS2->D1(aTS, aP2DS2, aV2DS2);

  gp_Vec2d        aV2DS12(aP2DS1, aP2DS2);
  gp_Dir2d        aD2DS12(aV2DS12);
  const gp_Dir2d& aD2DX = gp::DX2d();

  aScPr    = aD2DS12 * aD2DX;
  bUClosed = true;
  if (fabs(aScPr) < aTol)
  {
    bUClosed = !bUClosed;
  }

  aP2DS1.Coord(aUS1, aVS1);
  aP2DS2.Coord(aUS2, aVS2);

  aS = BRep_Tool::Surface(aF);
  aS->D0(aUS1, aVS1, aP);

  GeomAPI_ProjectPointOnCurve& aProjPC = aCtx->ProjPC(aEnew);

  aProjPC.Perform(aP);
  aNbPoints = aProjPC.NbPoints();
  if (!aNbPoints)
  {
    iRet = 1;
    return iRet;
  }

  aT = aProjPC.LowerDistanceParameter();

  aC2D = aC2DoldCT;
  aC2D->D1(aT, aP2D, aV2D);
  aP2D.Coord(aU, aV);

  aC2Dnew  = occ::down_cast<Geom2d_Curve>(aC2D->Copy());
  aC2DTnew = new Geom2d_TrimmedCurve(aC2Dnew, aT1, aT2);

  aV2DT = aV2DS12;
  if (!bUClosed)
  {
    if (fabs(aV - aVS2) < aTol)
    {
      aV2DT.Reverse();
    }
  }
  else
  {
    if (fabs(aU - aUS2) < aTol)
    {
      aV2DT.Reverse();
    }
  }

  aC2DTnew->Translate(aV2DT);

  bRevOrder = false;
  aScPr     = aV2D * aV2DS1;
  if (aScPr < 0.)
  {
    bRevOrder = !bRevOrder;
  }

  if (!bRevOrder)
  {
    aBB.UpdateEdge(aEnew, aC2D, aC2DTnew, aF, aTol);
  }
  else
  {
    aBB.UpdateEdge(aEnew, aC2DTnew, aC2D, aF, aTol);
  }
  return iRet;
}

bool IsClosed(const TopoDS_Edge& aE, const TopoDS_Face& aF)
{
  bool bRet;

  bRet = BRep_Tool::IsClosed(aE, aF);
  if (bRet)
  {
    int iCnt;

    iCnt = 0;
    TopExp_Explorer aExp(aF, TopAbs_EDGE);
    for (; (aExp.More() || iCnt == 2); aExp.Next())
    {
      const TopoDS_Shape& aEx = aExp.Current();
      if (aEx.IsSame(aE))
      {
        ++iCnt;
      }
    }
    bRet = (iCnt == 2);
  }
  return bRet;
}
