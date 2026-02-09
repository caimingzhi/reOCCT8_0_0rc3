#include <TopOpeBRepDS_define.hpp>

#include <gp_Pnt2d.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepDS_FaceInterferenceTool.hpp>
#include <TopExp.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_PShapeClassifier.hpp>
#include <TopOpeBRepTool_SC.hpp>
#include <TopOpeBRepTool_tol.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <BRepTools.hpp>
#include <GeomProjLib.hpp>
#include <Geom2d_Curve.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepAdaptor_Curve.hpp>

Standard_EXPORT occ::handle<Geom2d_Curve> MakePCurve(const ProjLib_ProjectedCurve& PC);

static TopAbs_State FUN_staPinF3d(const gp_Pnt& P, const TopoDS_Face& F)

{
  TopAbs_State st = TopAbs_UNKNOWN;
  gp_Pnt2d     UV;
  double       d  = 1.e2;
  bool         ok = FUN_tool_projPonboundedF(P, F, UV, d);
  if (!ok)
    return st;
  double tolF = BRep_Tool::Tolerance(F);
  if (d < tolF)
    return TopAbs_IN;
  gp_Pnt pF;
  FUN_tool_value(UV, F, pF);
  gp_Dir ntF = FUN_tool_nggeomF(UV, F);
  if (F.Orientation() == TopAbs_REVERSED)
    ntF.Reverse();
  gp_Dir PpF(gp_Vec(P, pF));
  double dot = ntF.Dot(PpF);
  st         = (dot > 0) ? TopAbs_IN : TopAbs_OUT;
  return st;
}

Standard_EXPORT void FUN_UNKFstasta(const TopoDS_Face&              FF,
                                    const TopoDS_Face&              FS,
                                    const TopoDS_Edge&              EE,
                                    const bool                      EEofFF,
                                    TopAbs_State&                   stateb,
                                    TopAbs_State&                   statea,
                                    TopOpeBRepTool_PShapeClassifier pClassif)
{
  BRep_Builder BB;

  stateb = statea = TopAbs_UNKNOWN;
  double                  fE, lE;
  occ::handle<Geom_Curve> CEE = BRep_Tool::Curve(EE, fE, lE);

  if (CEE.IsNull())
    return;
  occ::handle<Geom_Surface> SFF = BRep_Tool::Surface(FF);

  double ttE  = 0.41237118973;
  double parE = (1 - ttE) * fE + ttE * lE;
  gp_Pnt PE;
  gp_Vec VE;
  CEE->D1(parE, PE, VE);

  GeomAPI_ProjectPointOnSurf PonS(PE, SFF);
  if (!PonS.Extrema().IsDone())
    return;
  if (PonS.NbPoints() == 0)
    return;

  double u, v;
  PonS.Parameters(1, u, v);
  gp_Vec d1u, d1v;
  gp_Pnt puv;
  SFF->D1(u, v, puv, d1u, d1v);
  gp_Vec N = d1u.Crossed(d1v);
  double FUMin, FUMax, FVMin, FVMax;

  BRepTools::UVBounds(FF, FUMin, FUMax, FVMin, FVMax);

  double EUMin, EUMax, EVMin, EVMax;
  if (EEofFF)
  {
    BRepTools::UVBounds(FF, EE, EUMin, EUMax, EVMin, EVMax);
  }
  else
  {
    occ::handle<Geom2d_Curve> CEEFFx;
    if (CEE.IsNull())
    {
      bool                             compminmaxUV = false;
      BRepAdaptor_Surface              BAS(FS, compminmaxUV);
      occ::handle<BRepAdaptor_Surface> BAHS = new BRepAdaptor_Surface(BAS);
      BRepAdaptor_Curve                AC(EE, FS);
      occ::handle<BRepAdaptor_Curve>   AHC = new BRepAdaptor_Curve(AC);
      double                           tolin;
      FTOL_FaceTolerances3d(FF, FS, tolin);
      ProjLib_ProjectedCurve projcurv(BAHS, AHC, tolin);
      CEEFFx = MakePCurve(projcurv);
    }
    else
    {

      TopExp_Explorer anExp(FF, TopAbs_EDGE);
      for (; anExp.More(); anExp.Next())
      {
        if (EE.IsSame(anExp.Current()))
        {
          CEEFFx = BRep_Tool::CurveOnSurface(EE, FF, fE, lE);
        }
      }
      if (CEEFFx.IsNull())
      {

        CEEFFx = GeomProjLib::Curve2d(CEE, fE, lE, SFF);
      }
    }
    if (CEEFFx.IsNull())
      return;

    TopoDS_Edge EEx;
    BB.MakeEdge(EEx, CEE, BRep_Tool::Tolerance(EE));
    TopoDS_Vertex vf, vr;
    TopExp::Vertices(EE, vf, vr);
    BB.Add(EEx, vf);
    BB.UpdateVertex(vf, fE, EEx, BRep_Tool::Tolerance(vf));
    BB.Add(EEx, vr);
    BB.UpdateVertex(vr, lE, EEx, BRep_Tool::Tolerance(vr));

    TopoDS_Face FFx;
    BB.MakeFace(FFx, SFF, BRep_Tool::Tolerance(FF));
    BB.UpdateEdge(EEx, CEEFFx, FFx, BRep_Tool::Tolerance(FF));
    BRepTools::UVBounds(FFx, EEx, EUMin, EUMax, EVMin, EVMax);
  }

  bool EisoU = (fabs(EVMax - EVMin) < Precision::Confusion());

  bool EisoV = (fabs(EUMax - EUMin) < Precision::Confusion());

  double ttu  = 1.e-2;
  double paru = fabs(ttu * (FUMax - FUMin));
  double ttv  = 1.e-2;
  double parv = fabs(ttv * (FVMax - FVMin));

  double up = u;
  double vp = v;
  if (EisoV)
    up += paru;
  else if (EisoU)
    vp += parv;
  else
  {
    up += paru;
    vp += parv;
  }
  gp_Pnt Pb;
  SFF->D0(up, vp, Pb);

  double um = u;
  double vm = v;
  if (EisoV)
    um -= paru;
  else if (EisoU)
    vm -= parv;
  else
  {
    um -= paru;
    vm -= parv;
  }
  gp_Pnt Pa;
  SFF->D0(um, vm, Pa);

  bool   permute = false;
  double dot;
  gp_Vec VEcroN = VE.Crossed(N);
  if (EisoV)
  {
    dot = VEcroN.Dot(d1u);
    if (dot < 0.)
      permute = true;
  }
  else if (EisoU)
  {
    dot = VEcroN.Dot(d1v);
    if (dot < 0.)
      permute = true;
  }
  else
  {
    dot = VEcroN.Dot(d1v);
    if (dot < 0.)
      permute = true;
  }
  if (permute)
  {
    gp_Pnt P;
    P  = Pa;
    Pa = Pb;
    Pb = P;
  }

  if (pClassif)
  {

    pClassif->StateP3DReference(Pb);
    stateb = pClassif->State();
    pClassif->StateP3DReference(Pa);
    statea = pClassif->State();
  }
  else
  {
    stateb = ::FUN_staPinF3d(Pb, FS);
    statea = ::FUN_staPinF3d(Pa, FS);
  }
}
