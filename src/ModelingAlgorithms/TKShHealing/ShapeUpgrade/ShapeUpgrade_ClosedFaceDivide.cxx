#include <Bnd_Box2d.hpp>
#include <BRep_Tool.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <ShapeAnalysis.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeAnalysis_Surface.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeExtend.hpp>
#include <ShapeExtend_CompositeSurface.hpp>
#include <ShapeExtend_WireData.hpp>
#include <ShapeFix_ComposeShell.hpp>
#include <ShapeUpgrade_ClosedFaceDivide.hpp>
#include <ShapeUpgrade_SplitSurface.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Wire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_ClosedFaceDivide, ShapeUpgrade_FaceDivide)

ShapeUpgrade_ClosedFaceDivide::ShapeUpgrade_ClosedFaceDivide()

{
  myNbSplit = 1;
}

ShapeUpgrade_ClosedFaceDivide::ShapeUpgrade_ClosedFaceDivide(const TopoDS_Face& F)
    : ShapeUpgrade_FaceDivide(F)
{
  myNbSplit = 1;
}

bool ShapeUpgrade_ClosedFaceDivide::SplitSurface(const double)
{
  occ::handle<ShapeUpgrade_SplitSurface> SplitSurf = GetSplitSurfaceTool();
  if (SplitSurf.IsNull())
    return false;

  if (myResult.IsNull() || myResult.ShapeType() != TopAbs_FACE)
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL3);
    return false;
  }
  TopoDS_Face face = TopoDS::Face(myResult);

  double Uf, Ul, Vf, Vl;
  ShapeAnalysis::GetFaceUVBounds(myFace, Uf, Ul, Vf, Vl);

  if (::Precision::IsInfinite(Uf) || ::Precision::IsInfinite(Ul) || ::Precision::IsInfinite(Vf)
      || ::Precision::IsInfinite(Vl))
    return false;

  TopLoc_Location           L;
  occ::handle<Geom_Surface> surf;
  surf = BRep_Tool::Surface(face, L);

  bool                                       isUSplit = false;
  bool                                       doSplit  = false;
  occ::handle<NCollection_HSequence<double>> split    = new NCollection_HSequence<double>;

  for (TopoDS_Iterator iter(face); iter.More() && !doSplit; iter.Next())
  {
    if (iter.Value().ShapeType() != TopAbs_WIRE)
      continue;
    TopoDS_Wire                       wire = TopoDS::Wire(iter.Value());
    occ::handle<ShapeExtend_WireData> sewd = new ShapeExtend_WireData(wire);
    for (int i = 1; i <= sewd->NbEdges() && !doSplit; i++)
      if (sewd->IsSeam(i))
      {
        doSplit                        = true;
        TopoDS_Edge               edge = sewd->Edge(i);
        ShapeAnalysis_Edge        sae;
        occ::handle<Geom2d_Curve> c1, c2;
        double                    f1, f2, l1, l2;
        if (!sae.PCurve(edge, face, c1, f1, l1, false))
          continue;

        TopoDS_Shape tmpE = edge.Reversed();
        if (!sae.PCurve(TopoDS::Edge(tmpE), face, c2, f2, l2, false))
          continue;
        if (c2 == c1)
          continue;

        ShapeAnalysis_Curve sac;
        Bnd_Box2d           B1, B2;
        sac.FillBndBox(c1, f1, l1, 20, true, B1);
        sac.FillBndBox(c2, f2, l2, 20, true, B2);
        double x1min, y1min, x1max, y1max;
        double x2min, y2min, x2max, y2max;
        B1.Get(x1min, y1min, x1max, y1max);
        B2.Get(x2min, y2min, x2max, y2max);
        double xf, xl, yf, yl;
        if (x1min < x2min)
        {
          xf = x1max;
          xl = x2min;
        }
        else
        {
          xf = x2max;
          xl = x1min;
        }
        if (y1min < y2min)
        {
          yf = y1max;
          yl = y2min;
        }
        else
        {
          yf = y2max;
          yl = y1min;
        }

        double dU = xl - xf;
        double dV = yl - yf;
        if (dU > dV)
        {
          double step = dU / (myNbSplit + 1);
          double val  = xf + step;
          for (int j = 1; j <= myNbSplit; j++, val += step)
            split->Append(val);
          isUSplit = true;
        }
        else
        {
          double step = dV / (myNbSplit + 1);
          double val  = yf + step;
          for (int j = 1; j <= myNbSplit; j++, val += step)
            split->Append(val);
          isUSplit = false;
        }
      }
  }

  if (!doSplit)
  {

    occ::handle<ShapeAnalysis_Surface> sas     = new ShapeAnalysis_Surface(surf);
    bool                               uclosed = sas->IsUClosed(Precision());
    bool                               vclosed = sas->IsVClosed(Precision());
    double                             U1, U2, V1, V2;
    if (uclosed)
    {
      surf->Bounds(U1, U2, V1, V2);
      GeomAdaptor_Surface GAS(surf);
      double              toler = GAS.UResolution(Precision());
      if ((U2 - U1) - (Ul - Uf) < toler)
      {
        occ::handle<Geom_RectangularTrimmedSurface> rts =
          new Geom_RectangularTrimmedSurface(surf, U1, (U2 + U1) / 2, true);
        occ::handle<ShapeAnalysis_Surface> sast = new ShapeAnalysis_Surface(rts);
        if (!sast->IsUClosed(Precision()))
        {
          doSplit     = true;
          double step = (Ul - Uf) / (myNbSplit + 1);
          double val  = Uf + step;
          for (int i = 1; i <= myNbSplit; i++, val += step)
            split->Append(val);
          isUSplit = true;
        }
#ifdef OCCT_DEBUG
        else
          std::cout << "Warning: SU_ClosedFaceDivide: Thin face, not split" << std::endl;
#endif
      }
    }
    if (vclosed && !doSplit)
    {
      surf->Bounds(U1, U2, V1, V2);
      GeomAdaptor_Surface GAS(surf);
      double              toler = GAS.VResolution(Precision());
      if ((V2 - V1) - (Vl - Vf) < toler)
      {
        occ::handle<Geom_RectangularTrimmedSurface> rts =
          new Geom_RectangularTrimmedSurface(surf, V1, (V2 + V1) / 2, false);
        occ::handle<ShapeAnalysis_Surface> sast = new ShapeAnalysis_Surface(rts);
        if (!sast->IsVClosed(Precision()))
        {
          doSplit     = true;
          double step = (Vl - Vf) / (myNbSplit + 1);
          double val  = Vf + step;
          for (int i = 1; i <= myNbSplit; i++, val += step)
            split->Append(val);
          isUSplit = false;
        }
#ifdef OCCT_DEBUG
        else
          std::cout << "Warning: SU_ClosedFaceDivide: Thin face, not split" << std::endl;
#endif
      }
    }
  }

  if (!doSplit)
    return false;

  SplitSurf->Init(surf, Uf, Ul, Vf, Vl);
  if (isUSplit)
    SplitSurf->SetUSplitValues(split);
  else
    SplitSurf->SetVSplitValues(split);

  SplitSurf->Perform(mySegmentMode);
  if (!SplitSurf->Status(ShapeExtend_DONE))
    return false;
  occ::handle<ShapeExtend_CompositeSurface> Grid = SplitSurf->ResSurfaces();

  ShapeFix_ComposeShell CompShell;
  CompShell.Init(Grid, L, face, Precision());
  CompShell.SetMaxTolerance(MaxTolerance());
  CompShell.SetContext(Context());
  CompShell.Perform();
  if (CompShell.Status(ShapeExtend_FAIL) || !CompShell.Status(ShapeExtend_DONE))
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);

  TopoDS_Shape res = CompShell.Result();
  myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
  for (TopExp_Explorer exp(res, TopAbs_FACE); exp.More(); exp.Next())
  {

    TopoDS_Shape tempf = Context()->Apply(exp.Current());
    TopoDS_Face  f     = TopoDS::Face(tempf);
    myResult           = f;
    if (SplitSurface())
      Context()->Replace(f, myResult);
  }
  myResult = Context()->Apply(res);
  return true;
}

void ShapeUpgrade_ClosedFaceDivide::SetNbSplitPoints(const int num)
{
  if (num > 0)
    myNbSplit = num;
}

int ShapeUpgrade_ClosedFaceDivide::GetNbSplitPoints() const
{
  return myNbSplit;
}
