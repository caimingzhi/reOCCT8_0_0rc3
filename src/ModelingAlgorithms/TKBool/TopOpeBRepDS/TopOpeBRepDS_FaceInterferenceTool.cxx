#include <BRep_Tool.hpp>
#include <BRepLProp_SLProps.hpp>
#include <Extrema_ExtPS.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <Precision.hpp>
#include <Standard_ProgramError.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_FaceInterferenceTool.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_ShapeTool.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

static bool STATIC_TOREVERSE = false;
#define M_FORWARD(ori) (ori == TopAbs_FORWARD)
#define M_REVERSED(ori) (ori == TopAbs_REVERSED)

static void FUN_RaiseError()
{
  throw Standard_ProgramError("TopOpeBRepDS_FaceInterferenceTool");
}

Standard_EXPORT bool FUN_Parameters(const gp_Pnt& Pnt, const TopoDS_Shape& F, double& u, double& v)
{
  BRepAdaptor_Surface Surf(TopoDS::Face(F));

  double        uvtol = Surf.Tolerance();
  double        fu = Surf.FirstUParameter(), lu = Surf.LastUParameter();
  double        fv = Surf.FirstVParameter(), lv = Surf.LastVParameter();
  Extrema_ExtPS extps(Pnt, Surf, fu, lu, fv, lv, uvtol, uvtol, Extrema_ExtFlag_MIN);
  if (!extps.IsDone())
  {
    return false;
  }
  if (extps.NbExt() == 0)
  {
    return false;
  }
  extps.Point(1).Parameter(u, v);

  double d2   = extps.SquareDistance(1);
  double tolF = BRep_Tool::Tolerance(TopoDS::Face(F));
  bool   ok   = (d2 < tolF * tolF * 1.e6);
  return ok;
}

Standard_EXPORT void FUN_ComputeGeomData(const TopoDS_Shape& F, const gp_Pnt2d& uv, gp_Dir& Norm)
{
  gp_Vec ngF = FUN_tool_nggeomF(uv, TopoDS::Face(F));
  Norm       = gp_Dir(ngF);
}

static bool FUN_sphere(const TopoDS_Shape& F)
{
  occ::handle<Geom_Surface> su = TopOpeBRepTool_ShapeTool::BASISSURFACE(TopoDS::Face(F));
  GeomAdaptor_Surface       GAS(su);
  return (GAS.GetType() == GeomAbs_Sphere);
}

Standard_EXPORT void FUN_ComputeGeomData(const TopoDS_Shape& F,
                                         const gp_Pnt2d&     uv,
                                         gp_Dir&             Norm,
                                         gp_Dir&             D1,
                                         gp_Dir&             D2,
                                         double&             Cur1,
                                         double&             Cur2)
{
  BRepAdaptor_Surface surf(TopoDS::Face(F));
  double              uu = uv.X(), vv = uv.Y();

  bool sphere = FUN_sphere(F);
  bool plane  = FUN_tool_plane(F);

  BRepLProp_SLProps props(surf, uu, vv, 2, Precision::Confusion());
  bool              curdef = props.IsCurvatureDefined();
  if (!curdef)
    throw Standard_ProgramError("TopOpeBRepDS_FaceInterferenceTool::Init");
  bool umbilic = props.IsUmbilic();
  if (umbilic)
  {
    Cur1 = Cur2 = props.MeanCurvature();

    double toll    = 1.e-8;
    bool   ooplane = (std::abs(Cur1) < toll) && (std::abs(Cur2) < toll);
    plane          = plane || ooplane;

    if (plane)
      Norm = FUN_tool_nggeomF(uv, TopoDS::Face(F));
    else if (sphere)
    {
      gp_Pnt center = surf.Sphere().Location();
      gp_Pnt value  = surf.Value(uu, vv);
      Norm          = gp_Dir(gp_Vec(center, value));
    }
    else
      throw Standard_Failure("FUN_ComputeGeomData");

    D1       = Norm;
    double x = D1.X(), y = D1.Y(), z = D1.Z(), tol = Precision::Confusion();
    bool   nullx = (std::abs(x) < tol), nully = (std::abs(y) < tol), nullz = (std::abs(z) < tol);
    if (nullx && nully)
      D2 = gp_Dir(gp_Dir::D::X);
    else if (nullx && nullz)
      D2 = gp_Dir(gp_Dir::D::X);
    else if (nully && nullz)
      D2 = gp_Dir(gp_Dir::D::Y);
    else
      D2 = gp_Dir(y * z, x * z, -2. * x * y);
  }
  else
  {
    Cur1 = props.MaxCurvature();
    Cur2 = props.MinCurvature();
    props.CurvatureDirections(D1, D2);
    Norm = FUN_tool_nggeomF(uv, TopoDS::Face(F));
  }
}

TopOpeBRepDS_FaceInterferenceTool::TopOpeBRepDS_FaceInterferenceTool(
  const TopOpeBRepDS_PDataStructure& PBDS)
    : myPBDS(PBDS),
      myrefdef(false),
      myOnEdDef(false)
{
}

void TopOpeBRepDS_FaceInterferenceTool::Init(const TopoDS_Shape&                           FFI,
                                             const TopoDS_Shape&                           EE,
                                             const bool                                    EEisnew,
                                             const occ::handle<TopOpeBRepDS_Interference>& Iin)
{
  occ::handle<TopOpeBRepDS_ShapeShapeInterference> I(
    occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(Iin));
  if (I.IsNull())
    return;
  const TopoDS_Face& FI = TopoDS::Face(FFI);
  const TopoDS_Edge& E  = TopoDS::Edge(EE);

  STATIC_TOREVERSE = false;
  if (EEisnew)
  {
    int                 G  = I->Geometry();
    const TopoDS_Edge&  EG = TopoDS::Edge(myPBDS->Shape(G));
    TopOpeBRepDS_Config cf;
    bool                cfok = FDS_Config3d(E, EG, cf);
    if (!cfok)
    {
      FUN_RaiseError();
      return;
    }
    if (cf == TopOpeBRepDS_DIFFORIENTED)
      STATIC_TOREVERSE = true;
  }

  myFaceOrientation = FI.Orientation();
  myFaceOriented    = I->Support();

  myEdge = E;

  TopAbs_Orientation oEinFI;
  bool               edonfa = FUN_tool_orientEinFFORWARD(E, FI, oEinFI);

  isLine = false;

  if (!myOnEdDef)
  {
    bool ok = FUN_tool_findPinE(E, myPntOnEd, myParOnEd);
    if (!ok)
    {
      FUN_RaiseError();
      return;
    }
  }

  myTole = Precision::Angular();
  gp_Pnt2d uv;
  bool     ok = false;
  double   d  = 0.;
  if (edonfa)
    ok = FUN_tool_paronEF(E, myParOnEd, FI, uv);
  else
    ok = FUN_tool_projPonF(myPntOnEd, FI, uv, d);
  if (!ok)
  {
    FUN_RaiseError();
    return;
  }

  gp_Vec tmp;
  ok = TopOpeBRepTool_TOOL::TggeomE(myParOnEd, E, tmp);
  if (!ok)
  {
    FUN_RaiseError();
    return;
  }
  gp_Dir Tgt(tmp);
  gp_Dir Norm;
  if (isLine)
  {
    FUN_ComputeGeomData(FI, uv, Norm);
    myTool.Reset(Tgt, Norm);
  }
  else
  {
    gp_Dir D1, D2;
    double Cur1, Cur2;
    FUN_ComputeGeomData(FI, uv, Norm, D1, D2, Cur1, Cur2);
    myTool.Reset(Tgt, Norm, D1, D2, Cur1, Cur2);
  }
  myrefdef = true;
}

void TopOpeBRepDS_FaceInterferenceTool::Add(const TopoDS_Shape&                           FFI,
                                            const TopoDS_Shape&                           FFT,
                                            const TopoDS_Shape&                           EE,
                                            const bool                                    EEisnew,
                                            const occ::handle<TopOpeBRepDS_Interference>& Iin)
{
  occ::handle<TopOpeBRepDS_ShapeShapeInterference> I(
    occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(Iin));
  if (I.IsNull())
    return;
  const TopoDS_Face& FI = TopoDS::Face(FFI);
  const TopoDS_Face& FT = TopoDS::Face(FFT);
  const TopoDS_Edge& E  = TopoDS::Edge(EE);
  myPBDS->Shape(FI);

  if (!E.IsSame(myEdge))
  {
    FUN_RaiseError();
    return;
  }

  if (!myrefdef)
  {
    Init(FI, E, EEisnew, I);
    return;
  }
  TopOpeBRepDS_Kind GT, ST;
  int               G, S;
  FDS_data(I, GT, G, ST, S);
  const TopoDS_Edge& EG = TopoDS::Edge(myPBDS->Shape(G));
  FDS_HasSameDomain3d(*myPBDS, EG);
  bool same = !STATIC_TOREVERSE;

  TopAbs_Orientation oriloc = I->Transition().Orientation(TopAbs_IN);

  bool rev = !same && (M_FORWARD(oriloc) || M_REVERSED(oriloc));
  if (rev)
    oriloc = TopAbs::Complement(oriloc);

  TopAbs_Orientation oritan;
  TopAbs_Orientation oriEFT;
  bool               egofft = FUN_tool_orientEinFFORWARD(EG, FT, oriEFT);
  TopAbs_Orientation oriEFI;
  bool               egoffi = FUN_tool_orientEinFFORWARD(EG, FI, oriEFI);
  if (egofft)
  {
    oritan = oriEFT;
    if (EEisnew && !same)
      oritan = TopAbs::Complement(oriEFT);
  }
  else if (egoffi)
  {
    oritan = oriEFI;
    if (EEisnew && !same)
      oritan = TopAbs::Complement(oriEFI);
  }
  else
  {
    FUN_RaiseError();
    return;
  }

  gp_Pnt2d uv;
  bool     ok = false;
  if (egofft)
    ok = FUN_tool_paronEF(E, myParOnEd, FT, uv);
  if (!ok)
  {
    double d;
    ok = FUN_tool_projPonF(myPntOnEd, FT, uv, d);
  }
  if (!ok)
  {
    FUN_RaiseError();
    return;
  }

  gp_Dir Norm;
  if (isLine)
  {
    FUN_ComputeGeomData(FT, uv, Norm);

    myTool.Compare(myTole, Norm, oriloc, oritan);
  }
  else
  {
    gp_Dir D1, D2;
    double Cur1, Cur2;
    FUN_ComputeGeomData(FT, uv, Norm, D1, D2, Cur1, Cur2);

    myTool.Compare(myTole, Norm, D1, D2, Cur1, Cur2, oriloc, oritan);
  }
}

void TopOpeBRepDS_FaceInterferenceTool::Add

  (const TopoDS_Shape&, const TopOpeBRepDS_Curve&, const occ::handle<TopOpeBRepDS_Interference>&)
{
}

void TopOpeBRepDS_FaceInterferenceTool::Transition(
  const occ::handle<TopOpeBRepDS_Interference>& I) const
{
  TopOpeBRepDS_Transition& T = I->ChangeTransition();

  if (myFaceOrientation == TopAbs_INTERNAL)
  {
    T.Set(TopAbs_IN, TopAbs_IN);
  }
  else if (myFaceOrientation == TopAbs_EXTERNAL)
  {
    T.Set(TopAbs_OUT, TopAbs_OUT);
  }
  else
  {
    I->Support(myFaceOriented);
    TopAbs_State stb = myTool.StateBefore();
    TopAbs_State sta = myTool.StateAfter();
    T.Set(stb, sta);

    TopAbs_Orientation o   = T.Orientation(TopAbs_IN);
    bool               rev = STATIC_TOREVERSE && (M_FORWARD(o) || M_REVERSED(o));
    if (rev)
      o = TopAbs::Complement(o);
    T.Set(o);
  }
}

void TopOpeBRepDS_FaceInterferenceTool::SetEdgePntPar(const gp_Pnt& P, const double p)
{
  myPntOnEd = P;
  myParOnEd = p;
  myOnEdDef = true;
}

void TopOpeBRepDS_FaceInterferenceTool::GetEdgePntPar(gp_Pnt& P, double& p) const
{
  if (!myOnEdDef)
    throw Standard_ProgramError("GetEdgePntPar");
  P = myPntOnEd;
  p = myParOnEd;
}

bool TopOpeBRepDS_FaceInterferenceTool::IsEdgePntParDef() const
{
  return myOnEdDef;
}
