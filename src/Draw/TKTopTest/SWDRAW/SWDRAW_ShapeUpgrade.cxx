#include <BRep_Tool.hpp>
#include <BRep_Builder.hpp>
#include <BRepBuilderAPI.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <BRepTest_Objects.hpp>
#include <BRepTools.hpp>
#include <DBRep.hpp>
#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <DrawTrSurf.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Message.hpp>
#include <Precision.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeCustom.hpp>
#include <ShapeExtend_CompositeSurface.hpp>
#include <ShapeFix.hpp>
#include <ShapeFix_ComposeShell.hpp>
#include <ShapeUpgrade_RemoveInternalWires.hpp>
#include <ShapeUpgrade_RemoveLocations.hpp>
#include <ShapeUpgrade_ShapeConvertToBezier.hpp>
#include <ShapeUpgrade_ShapeDivideAngle.hpp>
#include <ShapeUpgrade_ShapeDivideArea.hpp>
#include <ShapeUpgrade_ShapeDivideClosed.hpp>
#include <ShapeUpgrade_ShapeDivideContinuity.hpp>
#include <ShapeUpgrade_SplitCurve2dContinuity.hpp>
#include <ShapeUpgrade_SplitCurve3dContinuity.hpp>
#include <ShapeUpgrade_SplitSurfaceContinuity.hpp>
#include <ShapeUpgrade_UnifySameDomain.hpp>
#include <SWDRAW.hpp>
#include <SWDRAW_ShapeUpgrade.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

#include <cstdio>

static int DT_ShapeDivide(Draw_Interpretor& di, int n, const char** a)
{

  if (n < 3)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(a[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }

  ShapeUpgrade_ShapeDivideContinuity tool(inputShape);

  if (n == 4)
  {
    double Tol = Draw::Atof(a[3]);
    tool.SetTolerance(Tol);
  }

  tool.Perform();
  TopoDS_Shape res = tool.Result();

  if (tool.Status(ShapeExtend_OK))
    di << "Status: OK\n";
  if (tool.Status(ShapeExtend_DONE1))
    di << "Status: DONE1\n";
  if (tool.Status(ShapeExtend_DONE2))
    di << "Status: DONE2\n";
  if (tool.Status(ShapeExtend_DONE3))
    di << "Status: DONE3\n";
  if (tool.Status(ShapeExtend_DONE4))
    di << "Status: DONE4\n";
  if (tool.Status(ShapeExtend_DONE5))
    di << "Status: DONE5\n";
  if (tool.Status(ShapeExtend_DONE6))
    di << "Status: DONE6\n";
  if (tool.Status(ShapeExtend_DONE7))
    di << "Status: DONE7\n";
  if (tool.Status(ShapeExtend_DONE8))
    di << "Status: DONE8\n";
  if (tool.Status(ShapeExtend_FAIL1))
    di << "Status: FAIL1\n";
  if (tool.Status(ShapeExtend_FAIL2))
    di << "Status: FAIL2\n";
  if (tool.Status(ShapeExtend_FAIL3))
    di << "Status: FAIL3\n";
  if (tool.Status(ShapeExtend_FAIL4))
    di << "Status: FAIL4\n";
  if (tool.Status(ShapeExtend_FAIL5))
    di << "Status: FAIL5\n";
  if (tool.Status(ShapeExtend_FAIL6))
    di << "Status: FAIL6\n";
  if (tool.Status(ShapeExtend_FAIL7))
    di << "Status: FAIL7\n";
  if (tool.Status(ShapeExtend_FAIL8))
    di << "Status: FAIL8\n";

  ShapeFix::SameParameter(res, false);

  DBRep::Set(a[1], res);
  return 0;
}

static int DT_ShapeConvertRev(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 5)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(a[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }

  int          c2d   = Draw::Atoi(a[3]);
  int          c3d   = Draw::Atoi(a[4]);
  TopoDS_Shape revsh = ShapeCustom::ConvertToRevolution(inputShape);
  if (revsh.IsNull())
  {
    di << "NO RESULT\n";
    return 1;
  }
  else if (revsh == inputShape)
  {
    di << "No modif\n";
  }
  else
    di << "ConvertToRevolution -> Result : \n";

  ShapeUpgrade_ShapeConvertToBezier tool(revsh);
  tool.SetSurfaceConversion(true);
  if (c2d)
    tool.Set2dConversion(true);
  if (c3d)
  {
    tool.Set3dConversion(true);
    if (n > 5)
      tool.Set3dLineConversion(false);
    if (n > 6)
      tool.Set3dCircleConversion(false);
    if (n > 7)
      tool.Set3dConicConversion(false);
  }
  tool.Perform();
  TopoDS_Shape res = tool.Result();

  if (tool.Status(ShapeExtend_OK))
    di << "Status: OK\n";
  if (tool.Status(ShapeExtend_DONE1))
    di << "Status: DONE1\n";
  if (tool.Status(ShapeExtend_DONE2))
    di << "Status: DONE2\n";
  if (tool.Status(ShapeExtend_DONE3))
    di << "Status: DONE3\n";
  if (tool.Status(ShapeExtend_DONE4))
    di << "Status: DONE4\n";
  if (tool.Status(ShapeExtend_DONE5))
    di << "Status: DONE5\n";
  if (tool.Status(ShapeExtend_DONE6))
    di << "Status: DONE6\n";
  if (tool.Status(ShapeExtend_DONE7))
    di << "Status: DONE7\n";
  if (tool.Status(ShapeExtend_DONE8))
    di << "Status: DONE8\n";
  if (tool.Status(ShapeExtend_FAIL1))
    di << "Status: FAIL1\n";
  if (tool.Status(ShapeExtend_FAIL2))
    di << "Status: FAIL2\n";
  if (tool.Status(ShapeExtend_FAIL3))
    di << "Status: FAIL3\n";
  if (tool.Status(ShapeExtend_FAIL4))
    di << "Status: FAIL4\n";
  if (tool.Status(ShapeExtend_FAIL5))
    di << "Status: FAIL5\n";
  if (tool.Status(ShapeExtend_FAIL6))
    di << "Status: FAIL6\n";
  if (tool.Status(ShapeExtend_FAIL7))
    di << "Status: FAIL7\n";
  if (tool.Status(ShapeExtend_FAIL8))
    di << "Status: FAIL8\n";

  ShapeFix::SameParameter(res, false);

  DBRep::Set(a[1], res);
  return 0;
}

static int DT_ShapeConvert(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 5)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(a[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }

  int c2d = Draw::Atoi(a[3]);
  int c3d = Draw::Atoi(a[4]);

  ShapeUpgrade_ShapeConvertToBezier tool(inputShape);
  tool.SetSurfaceConversion(true);
  if (c2d)
    tool.Set2dConversion(true);
  if (c3d)
    tool.Set3dConversion(true);
  tool.Perform();
  TopoDS_Shape res = tool.Result();

  if (tool.Status(ShapeExtend_OK))
    di << "Status: OK\n";
  if (tool.Status(ShapeExtend_DONE1))
    di << "Status: DONE1\n";
  if (tool.Status(ShapeExtend_DONE2))
    di << "Status: DONE2\n";
  if (tool.Status(ShapeExtend_DONE3))
    di << "Status: DONE3\n";
  if (tool.Status(ShapeExtend_DONE4))
    di << "Status: DONE4\n";
  if (tool.Status(ShapeExtend_DONE5))
    di << "Status: DONE5\n";
  if (tool.Status(ShapeExtend_DONE6))
    di << "Status: DONE6\n";
  if (tool.Status(ShapeExtend_DONE7))
    di << "Status: DONE7\n";
  if (tool.Status(ShapeExtend_DONE8))
    di << "Status: DONE8\n";
  if (tool.Status(ShapeExtend_FAIL1))
    di << "Status: FAIL1\n";
  if (tool.Status(ShapeExtend_FAIL2))
    di << "Status: FAIL2\n";
  if (tool.Status(ShapeExtend_FAIL3))
    di << "Status: FAIL3\n";
  if (tool.Status(ShapeExtend_FAIL4))
    di << "Status: FAIL4\n";
  if (tool.Status(ShapeExtend_FAIL5))
    di << "Status: FAIL5\n";
  if (tool.Status(ShapeExtend_FAIL6))
    di << "Status: FAIL6\n";
  if (tool.Status(ShapeExtend_FAIL7))
    di << "Status: FAIL7\n";
  if (tool.Status(ShapeExtend_FAIL8))
    di << "Status: FAIL8\n";

  ShapeFix::SameParameter(res, false);

  DBRep::Set(a[1], res);
  return 0;
}

static int DT_SplitAngle(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 3)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(a[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }

  double maxangle = 95;
  if (n > 3)
  {
    maxangle = Draw::Atof(a[3]);
    if (maxangle < 1)
      maxangle = 1;
  }

  ShapeUpgrade_ShapeDivideAngle tool(maxangle * M_PI / 180, inputShape);
  tool.Perform();
  TopoDS_Shape res = tool.Result();

  if (tool.Status(ShapeExtend_OK))
    di << "Status: OK\n";
  if (tool.Status(ShapeExtend_DONE1))
    di << "Status: DONE1\n";
  if (tool.Status(ShapeExtend_DONE2))
    di << "Status: DONE2\n";
  if (tool.Status(ShapeExtend_DONE3))
    di << "Status: DONE3\n";
  if (tool.Status(ShapeExtend_DONE4))
    di << "Status: DONE4\n";
  if (tool.Status(ShapeExtend_DONE5))
    di << "Status: DONE5\n";
  if (tool.Status(ShapeExtend_DONE6))
    di << "Status: DONE6\n";
  if (tool.Status(ShapeExtend_DONE7))
    di << "Status: DONE7\n";
  if (tool.Status(ShapeExtend_DONE8))
    di << "Status: DONE8\n";
  if (tool.Status(ShapeExtend_FAIL1))
    di << "Status: FAIL1\n";
  if (tool.Status(ShapeExtend_FAIL2))
    di << "Status: FAIL2\n";
  if (tool.Status(ShapeExtend_FAIL3))
    di << "Status: FAIL3\n";
  if (tool.Status(ShapeExtend_FAIL4))
    di << "Status: FAIL4\n";
  if (tool.Status(ShapeExtend_FAIL5))
    di << "Status: FAIL5\n";
  if (tool.Status(ShapeExtend_FAIL6))
    di << "Status: FAIL6\n";
  if (tool.Status(ShapeExtend_FAIL7))
    di << "Status: FAIL7\n";
  if (tool.Status(ShapeExtend_FAIL8))
    di << "Status: FAIL8\n";

  ShapeFix::SameParameter(res, false);

  DBRep::Set(a[1], res);
  return 0;
}

static int DT_SplitCurve(Draw_Interpretor& di, int n, const char** a)

{

  if (n < 3)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  double                  Tol = Draw::Atof(a[2]);
  occ::handle<Geom_Curve> GC  = DrawTrSurf::GetCurve(a[1]);
  if (GC.IsNull())
    return 1;
  int                                              Split = Draw::Atoi(a[3]);
  occ::handle<ShapeUpgrade_SplitCurve3dContinuity> theTool =
    new ShapeUpgrade_SplitCurve3dContinuity;
  theTool->Init(GC);
  theTool->SetTolerance(Tol);
  theTool->SetCriterion(GeomAbs_C1);
  if (Split == 1)
  {
    occ::handle<NCollection_HSequence<double>> spval = new NCollection_HSequence<double>;
    for (int i = 1; i <= 5; i++)
      spval->Append(i);
    theTool->SetSplitValues(spval);
  }
  theTool->Perform(true);
  occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>> theCurves = theTool->GetCurves();
  int                                                       NbC       = theCurves->Length();
  for (int icurv = 1; icurv <= NbC; icurv++)
  {
    char name[100];
    Sprintf(name, "%s%s%d", a[1], "_", icurv);
    char* newname = name;
    DrawTrSurf::Set(newname, theCurves->Value(icurv));
    di.AppendElement(newname);
  }
  return 0;
}

static int DT_SplitCurve2d(Draw_Interpretor& di, int n, const char** a)

{

  if (n < 3)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  double                    Tol = Draw::Atof(a[2]);
  occ::handle<Geom2d_Curve> GC  = DrawTrSurf::GetCurve2d(a[1]);
  if (GC.IsNull())
    return 1;
  int                                              Split = Draw::Atoi(a[3]);
  occ::handle<ShapeUpgrade_SplitCurve2dContinuity> theTool =
    new ShapeUpgrade_SplitCurve2dContinuity;
  theTool->Init(GC);
  theTool->SetTolerance(Tol);
  theTool->SetCriterion(GeomAbs_C1);
  if (Split == 1)
  {
    occ::handle<NCollection_HSequence<double>> spval = new NCollection_HSequence<double>;
    for (int i = 1; i <= 5; i++)
      spval->Append(i);
    theTool->SetSplitValues(spval);
  }
  theTool->Perform(true);
  occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> theCurves = theTool->GetCurves();
  int                                                         NbC       = theCurves->Length();
  for (int icurv = 1; icurv <= NbC; icurv++)
  {
    char name[100];
    Sprintf(name, "%s%s%d", a[1], "_", icurv);
    char* newname = name;
    DrawTrSurf::Set(newname, theCurves->Value(icurv));
    di.AppendElement(newname);
  }
  return 0;
}

static int DT_SplitSurface(Draw_Interpretor& di, int n, const char** a)

{

  if (n < 4)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  occ::handle<ShapeUpgrade_SplitSurfaceContinuity> theTool =
    new ShapeUpgrade_SplitSurfaceContinuity;

  double Tol   = Draw::Atof(a[3]);
  int    Split = Draw::Atoi(a[4]);
  theTool->SetTolerance(Tol);
  theTool->SetCriterion(GeomAbs_C1);
  occ::handle<Geom_Surface> GS = DrawTrSurf::GetSurface(a[2]);

  di << "single surf\n";

  di << "appel a SplitSurface::Init\n";
  theTool->Init(GS);
  if (Split == 1)
  {
    occ::handle<NCollection_HSequence<double>> spval = new NCollection_HSequence<double>;
    for (int i = 1; i <= 5; i++)
      spval->Append(i);
    theTool->SetUSplitValues(spval);
    theTool->SetVSplitValues(spval);
  }

  di << "appel a SplitSurface::Build\n";
  theTool->Build(true);

  di << "appel a SplitSurface::GlobalU/VKnots\n";
  occ::handle<ShapeExtend_CompositeSurface> Grid    = theTool->ResSurfaces();
  occ::handle<NCollection_HArray1<double>>  GlobalU = Grid->UJointValues();
  occ::handle<NCollection_HArray1<double>>  GlobalV = Grid->VJointValues();
  int                                       nbGlU   = GlobalU->Length();
  int                                       nbGlV   = GlobalV->Length();
  di << "nb GlobalU ; nb GlobalV=" << nbGlU << " " << nbGlV;
  for (int iu = 1; iu <= nbGlU; iu++)
    di << " " << GlobalU->Value(iu);

  for (int iv = 1; iv <= nbGlV; iv++)
    di << " " << GlobalV->Value(iv);
  di << "\n";

  di << "appel a Surfaces\n";
  occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>> theSurfaces = Grid->Patches();

  di << "transfert resultat\n";
  int NbRow = theSurfaces->ColLength();
  int NbCol = theSurfaces->RowLength();
  for (int irow = 1; irow <= NbRow; irow++)
  {
    for (int icol = 1; icol <= NbCol; icol++)
    {
      char name[100];
      Sprintf(name, "%s%s%d%s%d", a[1], "_", irow, "_", icol);
      char* newname = name;
      DrawTrSurf::Set(newname, theSurfaces->Value(irow, icol));
      di.AppendElement(newname);
    }
  }
  return 0;
}

static int offset2dcurve(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "result + curve + offset\n";

    return 1;
  }

  double                    Offset = Draw::Atof(argv[3]);
  occ::handle<Geom2d_Curve> GC     = DrawTrSurf::GetCurve2d(argv[2]);
  if (GC.IsNull())
    return 1;
  occ::handle<Geom2d_OffsetCurve> offcrv = new Geom2d_OffsetCurve(GC, Offset);
  DrawTrSurf::Set(argv[1], offcrv);
  return 0;
}

static int offsetcurve(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 5)
  {
    di << "result + curve + offset + Dir\n";

    return 1;
  }

  double                  Offset = Draw::Atof(argv[3]);
  occ::handle<Geom_Curve> GC     = DrawTrSurf::GetCurve(argv[2]);
  if (GC.IsNull())
    return 1;
  gp_Pnt point;
  DrawTrSurf::GetPoint(argv[4], point);
  gp_Dir                        dir(point.XYZ());
  occ::handle<Geom_OffsetCurve> offcrv = new Geom_OffsetCurve(GC, Offset, dir);
  DrawTrSurf::Set(argv[1], offcrv);
  return 0;
}

static int splitface(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 5)
  {
    di << "Split face: splitface result face [u usplit1 usplit2...] [v vsplit1 vsplit2 ...]\n";
    return 1;
  }

  TopoDS_Shape aLocalShape = DBRep::Get(argv[2]);
  TopoDS_Face  face        = TopoDS::Face(aLocalShape);
  if (face.IsNull())
  {
    di << argv[2] << " is not Face\n";
    return 1;
  }

  occ::handle<Geom_Surface> S = BRep_Tool::Surface(face);
  double                    Uf, Ul, Vf, Vl;
  BRepTools::UVBounds(face, Uf, Ul, Vf, Vl);
  double Umin, Umax, Vmin, Vmax;
  S->Bounds(Umin, Umax, Vmin, Vmax);
  if (Uf < Umin && !S->IsUPeriodic())
    Uf = Umin;
  else if (Uf > Umin)
  {
    if (Precision::IsInfinite(Umin))
      Uf -= 100;
    else
      Uf = Umin;
  }
  if (Vf < Vmin && !S->IsVPeriodic())
    Vf = Vmin;
  else if (Vf > Vmin)
  {
    if (Precision::IsInfinite(Vmin))
      Vf -= 100;
    else
      Vf = Vmin;
  }
  if (Ul > Umax && !S->IsUPeriodic())
    Ul = Umax;
  else if (Ul < Umax)
  {
    if (Precision::IsInfinite(Umax))
      Ul += 100;
    else
      Ul = Umax;
  }
  if (Vl > Vmax && !S->IsVPeriodic())
    Vl = Vmax;
  else if (Vl < Vmax)
  {
    if (Precision::IsInfinite(Vmax))
      Vl += 100;
    else
      Vl = Vmax;
  }

  NCollection_Sequence<double> uval;
  NCollection_Sequence<double> vval;

  bool byV = false;
  int  i;
  for (i = 3; i < argc; i++)
  {
    if (argv[i][0] == 'u')
      byV = false;
    else if (argv[i][0] == 'v')
      byV = true;
    else
    {
      double                        val  = Draw::Atof(argv[i]);
      NCollection_Sequence<double>& vals = (byV ? vval : uval);
      if (vals.Length() > 0 && val - vals.Last() < Precision::PConfusion())
      {
        di << "Values should be sorted in increasing order; skipped\n";
        continue;
      }
      if ((byV && (val < Vf + Precision::PConfusion() || val > Vl - Precision::PConfusion()))
          || (!byV && (val < Uf + Precision::PConfusion() || val > Ul - Precision::PConfusion())))
      {
        di << "Values should be inside range of surface; skipped\n";
        continue;
      }
      vals.Append(val);
    }
  }
  if (uval.Length() < 1 && vval.Length() < 1)
  {
    di << "No splitting defined\n";
    return 1;
  }
  if (uval.Length() > 0)
  {
    di << "Splitting by U: ";
    for (int j = 1; j <= uval.Length(); j++)
    {

      if (i > j)
      {
        di << ", ";
      }
      else
      {
        di << "";
      }
      di << uval(j);
    }
    di << "\n";
  }
  if (vval.Length() > 0)
  {
    di << "Splitting by V: ";
    for (int j = 1; j <= vval.Length(); j++)
    {

      if (j > 1)
      {
        di << ", ";
      }
      else
      {
        di << "";
      }
      di << vval(j);
    }
    di << "\n";
  }

  occ::handle<NCollection_HArray2<occ::handle<Geom_Surface>>> AS =
    new NCollection_HArray2<occ::handle<Geom_Surface>>(1, uval.Length() + 1, 1, vval.Length() + 1);
  for (i = 0; i <= uval.Length(); i++)
  {
    double umin = (i ? uval(i) : Uf);
    double umax = (i < uval.Length() ? uval(i + 1) : Ul);
    for (int j = 0; j <= vval.Length(); j++)
    {
      double                                      vmin = (j ? vval(j) : Vf);
      double                                      vmax = (j < vval.Length() ? vval(j + 1) : Vl);
      occ::handle<Geom_RectangularTrimmedSurface> rect =
        new Geom_RectangularTrimmedSurface(S, umin, umax, vmin, vmax);
      AS->SetValue(i + 1, j + 1, rect);
    }
  }

  occ::handle<ShapeExtend_CompositeSurface> Grid = new ShapeExtend_CompositeSurface;
  if (!Grid->Init(AS))
    di << "Grid badly connected!\n";

  ShapeFix_ComposeShell SUCS;
  TopLoc_Location       l;
  SUCS.Init(Grid, l, face, Precision::Confusion());
  occ::handle<ShapeBuild_ReShape> RS = new ShapeBuild_ReShape;
  SUCS.SetContext(RS);
  SUCS.Perform();

  if (SUCS.Status(ShapeExtend_OK))
    di << "Status: OK\n";
  if (SUCS.Status(ShapeExtend_DONE1))
    di << "Status: DONE1\n";
  if (SUCS.Status(ShapeExtend_DONE2))
    di << "Status: DONE2\n";
  if (SUCS.Status(ShapeExtend_DONE3))
    di << "Status: DONE3\n";
  if (SUCS.Status(ShapeExtend_DONE4))
    di << "Status: DONE4\n";
  if (SUCS.Status(ShapeExtend_DONE5))
    di << "Status: DONE5\n";
  if (SUCS.Status(ShapeExtend_DONE6))
    di << "Status: DONE6\n";
  if (SUCS.Status(ShapeExtend_DONE7))
    di << "Status: DONE7\n";
  if (SUCS.Status(ShapeExtend_DONE8))
    di << "Status: DONE8\n";
  if (SUCS.Status(ShapeExtend_FAIL1))
    di << "Status: FAIL1\n";
  if (SUCS.Status(ShapeExtend_FAIL2))
    di << "Status: FAIL2\n";
  if (SUCS.Status(ShapeExtend_FAIL3))
    di << "Status: FAIL3\n";
  if (SUCS.Status(ShapeExtend_FAIL4))
    di << "Status: FAIL4\n";
  if (SUCS.Status(ShapeExtend_FAIL5))
    di << "Status: FAIL5\n";
  if (SUCS.Status(ShapeExtend_FAIL6))
    di << "Status: FAIL6\n";
  if (SUCS.Status(ShapeExtend_FAIL7))
    di << "Status: FAIL7\n";
  if (SUCS.Status(ShapeExtend_FAIL8))
    di << "Status: FAIL8\n";

  TopoDS_Shape sh = SUCS.Result();
  ShapeFix::SameParameter(sh, false);
  DBRep::Set(argv[1], sh);
  return 0;
}

static int converttobspline(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 3)
  {
    di << "Use: " << argv[0] << " result shape [options=ero]\n";
    di << "where options is combination of letters indicating kinds of\n";
    di << "surfaces to be converted:\n";
    di << "e - extrusion\n";
    di << "r - revolution\n";
    di << "o - offset\n";
    di << "p - plane";
    return 1;
  }
  const char* options = (argc > 3 ? argv[3] : "ero");

  TopoDS_Shape inputShape = DBRep::Get(argv[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }
  TopoDS_Shape revsh = ShapeCustom::ConvertToRevolution(inputShape);
  TopoDS_Shape res   = ShapeCustom::ConvertToBSpline(revsh,
                                                   strchr(options, 'e') != nullptr,
                                                   strchr(options, 'r') != nullptr,
                                                   strchr(options, 'o') != nullptr,
                                                   strchr(options, 'p') != nullptr);
  ShapeFix::SameParameter(res, false);
  DBRep::Set(argv[1], res);
  return 0;
}

static int splitclosed(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 3)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(argv[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }

  ShapeUpgrade_ShapeDivideClosed tool(inputShape);
  tool.Perform();
  TopoDS_Shape res = tool.Result();

  ShapeFix::SameParameter(res, false);
  DBRep::Set(argv[1], res);
  return 0;
}

static int splitarea(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(argv[2]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }
  double aMaxArea = Draw::Atof(argv[3]);

  ShapeUpgrade_ShapeDivideArea tool(inputShape);
  if (argc > 4)
  {
    double prec = Draw::Atof(argv[4]);
    tool.SetPrecision(prec);
  }
  tool.MaxArea() = aMaxArea;
  tool.Perform();
  TopoDS_Shape res = tool.Result();

  ShapeFix::SameParameter(res, false);
  DBRep::Set(argv[1], res);
  return 0;
}

static int splitbynumber(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "bad number of arguments\n";
    return 1;
  }

  TopoDS_Shape inputShape = DBRep::Get(argv[2], TopAbs_FACE);
  if (inputShape.IsNull())
  {
    di << "Unknown face\n";
    return 1;
  }

  int aNbParts, aNumber1 = 0, aNumber2 = 0;
  aNbParts = aNumber1 = Draw::Atoi(argv[3]);
  if (argc > 4)
    aNumber2 = Draw::Atoi(argv[4]);

  if (argc == 4 && aNbParts <= 0)
  {
    di << "Incorrect number of parts\n";
    return 1;
  }
  if (argc == 5 && (aNumber1 <= 0 || aNumber2 <= 0))
  {
    di << "Incorrect numbers in U or V\n";
    return 1;
  }

  ShapeUpgrade_ShapeDivideArea tool(inputShape);
  tool.SetSplittingByNumber(true);
  if (argc == 4)
    tool.NbParts() = aNbParts;
  else
    tool.SetNumbersUVSplits(aNumber1, aNumber2);
  tool.Perform();
  TopoDS_Shape res = tool.Result();

  ShapeFix::SameParameter(res, false);
  DBRep::Set(argv[1], res);
  return 0;
}

static int removeinternalwires(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "bad number of arguments\n";
    return 1;
  }
  double       aMinArea   = Draw::Atof(argv[2]);
  TopoDS_Shape inputShape = DBRep::Get(argv[3]);
  if (inputShape.IsNull())
  {
    di << "Unknown shape\n";
    return 1;
  }
  occ::handle<ShapeUpgrade_RemoveInternalWires> aTool;
  NCollection_Sequence<TopoDS_Shape>            aSeqShapes;
  if (inputShape.ShapeType() < TopAbs_WIRE)
    aTool = new ShapeUpgrade_RemoveInternalWires(inputShape);
  else
  {
    di << "Invalid type of first shape: should be FACE,SHELL,SOLID or COMPOUND\n";
    return 1;
  }

  int  k                = 4;
  bool isShape          = true;
  bool aModeRemoveFaces = true;

  for (; k < argc; k++)
  {
    if (isShape)
    {
      TopoDS_Shape aShape = DBRep::Get(argv[k]);
      isShape             = !aShape.IsNull();
      if (isShape)
      {
        if (aShape.ShapeType() == TopAbs_FACE || aShape.ShapeType() == TopAbs_WIRE)
          aSeqShapes.Append(aShape);
      }
    }
    if (!isShape)
      aModeRemoveFaces = (Draw::Atoi(argv[k]) == 1);
  }

  aTool->MinArea()        = aMinArea;
  aTool->RemoveFaceMode() = aModeRemoveFaces;
  if (aSeqShapes.Length())
    aTool->Perform(aSeqShapes);
  else
    aTool->Perform();
  if (aTool->Status(ShapeExtend_FAIL1))
    di << "Initial shape has invalid type\n";
  else if (aTool->Status(ShapeExtend_FAIL2))
    di << "Specified sub-shape is not belonged to whole shape\n";
  if (aTool->Status(ShapeExtend_DONE1))
  {
    const NCollection_Sequence<TopoDS_Shape>& aRemovedWires = aTool->RemovedWires();
    di << aRemovedWires.Length() << " internal wires were removed\n";
  }
  if (aTool->Status(ShapeExtend_DONE2))
  {
    const NCollection_Sequence<TopoDS_Shape>& aRemovedFaces = aTool->RemovedFaces();
    di << aRemovedFaces.Length() << " small faces were removed\n";
  }
  TopoDS_Shape res = aTool->GetResult();

  DBRep::Set(argv[1], res);
  return 0;
}

static int removeloc(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 3)
  {
    di
      << "bad number of arguments. Should be:  removeloc res shape [remove_level(see ShapeEnum)]\n";
    return 1;
  }

  TopoDS_Shape aShape = DBRep::Get(argv[2]);
  if (aShape.IsNull())
    return 1;
  ShapeUpgrade_RemoveLocations aRemLoc;
  if (argc > 3)
    aRemLoc.SetRemoveLevel((TopAbs_ShapeEnum)Draw::Atoi(argv[3]));
  aRemLoc.Remove(aShape);
  TopoDS_Shape aNewShape = aRemLoc.GetResult();

  DBRep::Set(argv[1], aNewShape);
  return 0;
}

static ShapeUpgrade_UnifySameDomain& Unifier()
{
  static ShapeUpgrade_UnifySameDomain sUnifier;
  return sUnifier;
}

static int unifysamedom(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 3)
  {
    di << "Use unifysamedom result shape [s1 s2 ...] [-f] [-e] [-nosafe] [+b] [+i] [-t val] [-a "
          "val]\n";
    di << "options:\n";
    di << "s1 s2 ... to keep the given edges during unification of faces\n";
    di << "-f to switch off 'unify-faces' mode \n";
    di << "-e to switch off 'unify-edges' mode\n";
    di << "-nosafe to switch off 'safe input shape' mode\n";
    di << "+b to switch on 'concat bspline' mode\n";
    di << "+i to switch on 'allow internal edges' mode\n";
    di << "-t val to set linear tolerance\n";
    di << "-a val to set angular tolerance (in degrees)\n";
    di << "'unify-faces' and 'unify-edges' modes are switched on by default";
    return 1;
  }

  TopoDS_Shape aShape = DBRep::Get(a[2]);
  if (aShape.IsNull())
    return 1;

  bool                                                   anUFaces        = true;
  bool                                                   anUEdges        = true;
  bool                                                   anConBS         = false;
  bool                                                   isAllowInternal = false;
  bool                                                   isSafeInputMode = true;
  double                                                 aLinTol         = Precision::Confusion();
  double                                                 aAngTol         = Precision::Angular();
  TopoDS_Shape                                           aKeepShape;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapOfShapes;

  if (n > 3)
    for (int i = 3; i < n; i++)
    {
      aKeepShape = DBRep::Get(a[i]);
      if (!aKeepShape.IsNull())
      {
        aMapOfShapes.Add(aKeepShape);
      }
      else
      {
        if (!strcmp(a[i], "-f"))
          anUFaces = false;
        else if (!strcmp(a[i], "-e"))
          anUEdges = false;
        else if (!strcmp(a[i], "-nosafe"))
          isSafeInputMode = false;
        else if (!strcmp(a[i], "+b"))
          anConBS = true;
        else if (!strcmp(a[i], "+i"))
          isAllowInternal = true;
        else if (!strcmp(a[i], "-t") || !strcmp(a[i], "-a"))
        {
          if (++i < n)
          {
            if (a[i - 1][1] == 't')
              aLinTol = Draw::Atof(a[i]);
            else
              aAngTol = Draw::Atof(a[i]) * (M_PI / 180.0);
          }
          else
          {
            di << "value expected after " << a[i - 1];
            return 1;
          }
        }
      }
    }

  Unifier().Initialize(aShape, anUEdges, anUFaces, anConBS);
  Unifier().KeepShapes(aMapOfShapes);
  Unifier().SetSafeInputMode(isSafeInputMode);
  Unifier().AllowInternalEdges(isAllowInternal);
  Unifier().SetLinearTolerance(aLinTol);
  Unifier().SetAngularTolerance(aAngTol);
  Unifier().Build();
  TopoDS_Shape Result = Unifier().Shape();

  if (BRepTest_Objects::IsHistoryNeeded())
    BRepTest_Objects::SetHistory(Unifier().History());

  DBRep::Set(a[1], Result);
  return 0;
}

static int copytranslate(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 6)
  {
    di << "bad number of arguments. Should be:  copytranslate res shape dx dy dz\n";
    return 1;
  }
  TopoDS_Shape aShape = DBRep::Get(argv[2]);
  if (aShape.IsNull())
    return 1;
  double  aDx = Draw::Atof(argv[3]);
  double  aDy = Draw::Atof(argv[4]);
  double  aDz = Draw::Atof(argv[5]);
  gp_Trsf aTrsf;
  aTrsf.SetTranslation(gp_Vec(aDx, aDy, aDz));
  BRepBuilderAPI_Transform builderTransform(aTrsf);
  builderTransform.Perform(aShape, true);
  TopoDS_Shape aNewShape = builderTransform.Shape();
  DBRep::Set(argv[1], aNewShape);
  return 0;
}

static int reshape(Draw_Interpretor&, int theArgc, const char** theArgv)
{
  if (theArgc < 4)
  {
    Message::SendFail() << "Error: wrong number of arguments. Type 'help " << theArgv[0] << "'";
    return 1;
  }

  TopoDS_Shape aSource = DBRep::Get(theArgv[2]);
  if (aSource.IsNull())
  {
    Message::SendFail() << "Error: source shape ('" << theArgv[2] << "') is null";
    return 1;
  }

  occ::handle<BRepTools_ReShape> aReShaper = new BRepTools_ReShape;

  TopAbs_ShapeEnum aShapeLevel = TopAbs_SHAPE;

  for (int i = 3; i < theArgc; ++i)
  {
    const char*             anArg = theArgv[i];
    TCollection_AsciiString anOpt(anArg);
    anOpt.LowerCase();

    if (anOpt == "-replace")
    {
      if (theArgc - i < 3)
      {
        Message::SendFail() << "Error: not enough arguments for replacement";
        return 1;
      }

      TopoDS_Shape aWhat = DBRep::Get(theArgv[++i]);
      if (aWhat.IsNull())
      {
        Message::SendFail() << "Error: argument shape ('" << theArgv[i] << "') is null";
        return 1;
      }

      TopoDS_Shape aWith = DBRep::Get(theArgv[++i]);
      if (aWith.IsNull())
      {
        Message::SendFail() << "Error: replacement shape ('" << theArgv[i] << "') is null";
        return 1;
      }

      aReShaper->Replace(aWhat, aWith);
    }
    else if (anOpt == "-remove")
    {
      if (theArgc - i < 2)
      {
        Message::SendFail() << "Error: not enough arguments for removal";
        return 1;
      }

      TopoDS_Shape aWhat = DBRep::Get(theArgv[++i]);
      if (aWhat.IsNull())
      {
        Message::SendFail() << "Error: shape to remove ('" << theArgv[i] << "') is null";
        return 1;
      }

      aReShaper->Remove(aWhat);
    }
    else if (anOpt == "-until")
    {
      if (theArgc - i < 2)
      {
        Message::SendFail() << "Error: not enough arguments for level specification";
        return 1;
      }

      const char*             aLevelCStr = theArgv[++i];
      TCollection_AsciiString aLevelStr(aLevelCStr);
      aLevelStr.LowerCase();
      if (aLevelStr == "compound" || aLevelStr == "cd")
        aShapeLevel = TopAbs_COMPOUND;
      else if (aLevelStr == "compsolid" || aLevelStr == "c")
        aShapeLevel = TopAbs_COMPSOLID;
      else if (aLevelStr == "solid" || aLevelStr == "so")
        aShapeLevel = TopAbs_SOLID;
      else if (aLevelStr == "shell" || aLevelStr == "sh")
        aShapeLevel = TopAbs_SHELL;
      else if (aLevelStr == "face" || aLevelStr == "f")
        aShapeLevel = TopAbs_FACE;
      else if (aLevelStr == "wire" || aLevelStr == "w")
        aShapeLevel = TopAbs_WIRE;
      else if (aLevelStr == "edge" || aLevelStr == "e")
        aShapeLevel = TopAbs_EDGE;
      else if (aLevelStr == "vertex" || aLevelStr == "v")
        aShapeLevel = TopAbs_VERTEX;
      else if (aLevelStr == "shape" || aLevelStr == "s")
        aShapeLevel = TopAbs_SHAPE;
      else
      {
        Message::SendFail() << "Error: unknown shape type '" << theArgv[i] << "'";
        return 1;
      }
    }
    else
    {
      Message::SendFail() << "Error: invalid syntax at " << anOpt;
      return 1;
    }
  }

  TopoDS_Shape aResult = aReShaper->Apply(aSource, aShapeLevel);
  if (aResult.IsNull())
  {
    Message::SendFail() << "Error: result shape is null";
    return 1;
  }

  DBRep::Set(theArgv[1], aResult);
  return 0;
}

void SWDRAW_ShapeUpgrade::InitCommands(Draw_Interpretor& theCommands)
{
  static int initactor = 0;
  if (initactor)
  {
    return;
  }
  initactor = 1;

  const char* g = SWDRAW::GroupName();

  theCommands.Add("DT_ShapeDivide",
                  "DT_ShapeDivide Result Shape Tol: Divides shape with C1 Criterion",
                  __FILE__,
                  DT_ShapeDivide,
                  g);

  theCommands.Add("DT_SplitAngle",
                  "DT_SplitAngle Result Shape [MaxAngle=95]: Divides revolved surfaces on segments "
                  "less MaxAngle deg",
                  __FILE__,
                  DT_SplitAngle,
                  g);

  theCommands.Add("DT_ShapeConvert",
                  "DT_ShapeConvert Result Shape convert2d convert3d: Converts curves to beziers",
                  __FILE__,
                  DT_ShapeConvert,
                  g);

  theCommands.Add("DT_ShapeConvertRev",
                  "DT_ShapeConvert Result Shape convert2d convert3d: Converts curves to beziers",
                  __FILE__,
                  DT_ShapeConvertRev,
                  g);

  theCommands.Add("DT_SplitCurve2d",
                  "DT_SplitCurve2d Curve Tol: Splits the curve with C1 criterion",
                  __FILE__,
                  DT_SplitCurve2d,
                  g);

  theCommands.Add("DT_SplitCurve",
                  "DT_SplitCurve Curve Tol: Splits the curve with C1 criterion",
                  __FILE__,
                  DT_SplitCurve,
                  g);

  theCommands.Add(
    "DT_SplitSurface",
    "DT_SplitSurface Result Surface/GridSurf Tol: Splits the surface with C1 criterion",
    __FILE__,
    DT_SplitSurface,
    g);

  theCommands.Add("offset2dcurve", "result curve offset", __FILE__, offset2dcurve, g);

  theCommands.Add("offsetcurve", "result curve offset dir", __FILE__, offsetcurve, g);

  theCommands.Add("splitface",
                  "result face [u usplit1 usplit2...] [v vsplit1 vsplit2 ...]",
                  __FILE__,
                  splitface,
                  g);

  theCommands.Add("DT_ToBspl", "result shape [options=erop]", __FILE__, converttobspline, g);
  theCommands.Add("DT_ClosedSplit", "result shape", __FILE__, splitclosed, g);
  theCommands.Add("DT_SplitByArea", "result shape maxarea [preci]", __FILE__, splitarea, g);
  theCommands.Add("DT_SplitByNumber", "result face number [number2]", __FILE__, splitbynumber, g);

  theCommands.Add("RemoveIntWires",
                  "result minarea wholeshape [faces or wires] [moderemoveface ]",
                  __FILE__,
                  removeinternalwires,
                  g);

  theCommands.Add("removeloc",
                  "result shape [remove_level(see ShapeEnum)]",
                  __FILE__,
                  removeloc,
                  g);

  theCommands.Add(
    "unifysamedom",
    "unifysamedom result shape [s1 s2 ...] [-f] [-e] [-nosafe] [+b] [+i] [-t val] [-a val]",
    __FILE__,
    unifysamedom,
    g);

  theCommands.Add("copytranslate", "result shape dx dy dz", __FILE__, copytranslate, g);

  theCommands.Add("reshape",
                  "\n    reshape : result shape [-replace what with] [-remove what] [-until level]"
                  "\n    Basic utility for topological modification: "
                  "\n      '-replace what with'   Replaces 'what' sub-shape with 'with' sub-shape"
                  "\n      '-remove what'         Removes 'what' sub-shape"
                  "\n    Requests '-replace' and '-remove' can be repeated many times."
                  "\n    '-until level' specifies level until which shape for replcement/removal"
                  "\n    will be searched.",
                  __FILE__,
                  reshape,
                  g);
}
