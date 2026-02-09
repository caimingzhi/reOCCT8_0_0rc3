

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBuilderAPI_GTransform.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepFill.hpp>
#include <BRepGProp.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepPrimAPI_MakePrism.hpp>
#include <BRepPrimAPI_MakeRevol.hpp>
#include <BRepTools.hpp>
#include <BSplCLib.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomConvert.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_Trsf.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec.hpp>
#include <GProp_GProps.hpp>
#include <IGESBasic_SingleParent.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_ToolLocation.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_OffsetSurface.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_RuledSurface.hpp>
#include <IGESGeom_SurfaceOfRevolution.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_SphericalSurface.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <IGESToBRep.hpp>
#include <IGESToBRep_BasicCurve.hpp>
#include <IGESToBRep_BasicSurface.hpp>
#include <IGESToBRep_CurveAndSurface.hpp>
#include <IGESToBRep_TopoCurve.hpp>
#include <IGESToBRep_TopoSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Msg.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <ShapeAnalysis.hpp>
#include <ShapeFix_Wire.hpp>
#include <Standard_ErrorHandler.hpp>
#include <NCollection_Array1.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

#include <cstdio>

IGESToBRep_TopoSurface::IGESToBRep_TopoSurface()

  = default;

IGESToBRep_TopoSurface::IGESToBRep_TopoSurface(const IGESToBRep_CurveAndSurface& CS)
    : IGESToBRep_CurveAndSurface(CS)
{
}

IGESToBRep_TopoSurface::IGESToBRep_TopoSurface(const double eps,
                                               const double epsCoeff,
                                               const double epsGeom,
                                               const bool   mode,
                                               const bool   modeapprox,
                                               const bool   optimized)
    : IGESToBRep_CurveAndSurface(eps, epsCoeff, epsGeom, mode, modeapprox, optimized)
{
}

static bool extractCurve3d(const TopoDS_Shape& theEdges, occ::handle<Geom_Curve>& theCurve)
{
  TopExp_Explorer anExp(theEdges, TopAbs_EDGE);
  int             howMuch = 0;
  double          f = 0., l = 0.;
  for (; anExp.More(); anExp.Next())
  {
    TopoDS_Edge anEdge = TopoDS::Edge(anExp.Current());
    if (anEdge.IsNull())
      continue;
    howMuch++;
    theCurve = BRep_Tool::Curve(anEdge, f, l);
  }
  if (howMuch != 1 || theCurve.IsNull())
    return false;

  if (f != theCurve->FirstParameter() || l != theCurve->LastParameter())
    theCurve = new Geom_TrimmedCurve(theCurve, f, l);
  return true;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferTopoSurface(const occ::handle<IGESData_IGESEntity>& st)
{

  TopoDS_Shape res;
  TheULength = 1.;

  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
  }

  else if (HasShapeResult(st))
  {
    res = GetShapeResult(st);
    return res;
  }

  else if (IGESToBRep::IsBasicSurface(st))
  {
    res = TransferTopoBasicSurface(st);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_TrimmedSurface)))
  {
    DeclareAndCast(IGESGeom_TrimmedSurface, st144, st);
    res = TransferTrimmedSurface(st144);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_SurfaceOfRevolution)))
  {
    DeclareAndCast(IGESGeom_SurfaceOfRevolution, st120, st);
    res = TransferSurfaceOfRevolution(st120);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_TabulatedCylinder)))
  {
    DeclareAndCast(IGESGeom_TabulatedCylinder, st122, st);
    res = TransferTabulatedCylinder(st122);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_RuledSurface)))
  {
    DeclareAndCast(IGESGeom_RuledSurface, st118, st);
    res = TransferRuledSurface(st118);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_Plane)))
  {
    DeclareAndCast(IGESGeom_Plane, st108, st);
    res = TransferPlane(st108);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_BoundedSurface)))
  {
    DeclareAndCast(IGESGeom_BoundedSurface, st143, st);
    res = TransferBoundedSurface(st143);
  }
  else if (st->IsKind(STANDARD_TYPE(IGESGeom_OffsetSurface)))
  {
    DeclareAndCast(IGESGeom_OffsetSurface, st140, st);
    res = TransferOffsetSurface(st140);
  }

  else if (st->IsKind(STANDARD_TYPE(IGESBasic_SingleParent)))
  {
    DeclareAndCast(IGESBasic_SingleParent, st402_9, st);
    res = TransferPerforate(st402_9);
  }
  else
  {
  }
  SetShapeResult(st, res);
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferTopoBasicSurface(
  const occ::handle<IGESData_IGESEntity>& st)
{

  TopoDS_Shape res;

  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }
  if (!IGESToBRep::IsBasicSurface(st))
  {

    return res;
  }

  IGESToBRep_BasicSurface BS(*this);

  occ::handle<Geom_Surface> surf = BS.TransferBasicSurface(st);
  if (surf.IsNull())
  {

    return res;
  }

  if (surf->Continuity() < GeomAbs_C1)
  {
    Message_Msg msg1250("IGES_1250");
    SendWarning(st, msg1250);
  }
  if (surf->IsKind(STANDARD_TYPE(Geom_Plane)))
  {
    BRep_Builder B;
    TopoDS_Face  plane;
    B.MakeFace(plane);
    B.UpdateFace(plane, surf, TopLoc_Location(), Precision::Confusion());
    res = plane;
  }
  else
  {
    BRepLib_MakeFace makeFace(surf, Precision::Confusion());
    res = makeFace.Face();
  }

  if (st->HasTransf())
  {
    gp_Trsf trsf;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               st->CompoundLocation(),
                                               trsf,
                                               GetUnitFactor()))
    {
      TopLoc_Location locFace(trsf);
      res.Move(locFace, false);
    }
    else
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(st, msg1035);
    }
  }
  return res;
}

static void reparamBSpline(occ::handle<Geom_Curve>& curve, const double First, const double Last)
{
  occ::handle<Geom_BSplineCurve> bscurve;
  if (!curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    if (curve->FirstParameter() < First || curve->LastParameter() > Last)
      curve = new Geom_TrimmedCurve(curve, First, Last);
    bscurve = GeomConvert::CurveToBSplineCurve(curve, Convert_RationalC1);
  }
  else
  {
    bscurve = occ::down_cast<Geom_BSplineCurve>(curve);
    bscurve->Segment(First, Last);
  }

  if (bscurve.IsNull())
    return;

  NCollection_Array1<double> Knots(1, bscurve->NbKnots());
  bscurve->Knots(Knots);
  BSplCLib::Reparametrize(0., 1., Knots);
  bscurve->SetKnots(Knots);
  curve = bscurve;
}

static void ReparamCurve(TopoDS_Edge& edge)
{
  TopLoc_Location L;
  double          First, Last;

  occ::handle<Geom_Curve> curve =
    occ::down_cast<Geom_Curve>(BRep_Tool::Curve(edge, L, First, Last)->Copy());

  if (!curve->IsKind(STANDARD_TYPE(Geom_Line)))
    return;

  reparamBSpline(curve, First, Last);

  BRep_Builder B;
  B.UpdateEdge(edge, curve, L, Precision::Confusion());
  B.Range(edge, 0., 1);
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferRuledSurface(
  const occ::handle<IGESGeom_RuledSurface>& st)
{

  TopoDS_Shape res;

  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  IGESToBRep_TopoCurve TC(*this);

  TC.SetContinuity(0);
  occ::handle<IGESData_IGESEntity> igesCurve1 = st->FirstCurve();
  occ::handle<IGESData_IGESEntity> igesCurve2 = st->SecondCurve();

  if (igesCurve1.IsNull())
  {
    Message_Msg msg148("XSTEP_148");
    SendFail(st, msg148);
    return res;
  }
  if (igesCurve2.IsNull())
  {
    Message_Msg msg149("XSTEP_149");
    SendFail(st, msg149);
    return res;
  }

  int          nbEdges1, nbEdges2;
  TopoDS_Shape shape1, shape2;
  TopoDS_Wire  wire1, wire2;
  TopoDS_Wire  newWire1, newWire2;

  if (IGESToBRep::IsTopoCurve(igesCurve1))
  {
    shape1 = TC.TransferTopoCurve(igesCurve1);
    if (shape1.IsNull())
    {
      Message_Msg                           msg1156("IGES_1156");
      const char*                           typeName(igesCurve1->DynamicType()->Name());
      occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesCurve1);
      msg1156.Arg(typeName);
      msg1156.Arg(label);
      SendFail(st, msg1156);
      return res;
    }

    TopAbs_ShapeEnum shapeEnum1 = shape1.ShapeType();
    switch (shapeEnum1)
    {
      case TopAbs_EDGE:
      {
        TopoDS_Edge edge1 = TopoDS::Edge(shape1);
        ReparamCurve(edge1);
        nbEdges1 = 1;
      }
      break;
      case TopAbs_WIRE:
      {
        wire1    = TopoDS::Wire(shape1);
        nbEdges1 = 0;
        for (TopoDS_Iterator hulot(wire1); hulot.More(); hulot.Next())
        {
          TopoDS_Edge edge1 = TopoDS::Edge(hulot.Value());
          ReparamCurve(edge1);
          nbEdges1++;
        }
      }
      break;
      default:
      {

        return res;
      }
    }
  }
  else
  {
    Message_Msg msg148("XSTEP_148");
    SendFail(st, msg148);

    return res;
  }

  if (IGESToBRep::IsTopoCurve(igesCurve2))
  {
    shape2 = TC.TransferTopoCurve(igesCurve2);

    if (shape2.IsNull())
    {
      Message_Msg                           msg1156("IGES_1156");
      const char*                           typeName(igesCurve2->DynamicType()->Name());
      occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesCurve2);
      msg1156.Arg(typeName);
      msg1156.Arg(label);
      SendFail(st, msg1156);

      return res;
    }
    int dirflag = st->DirectionFlag();

    TopAbs_ShapeEnum shapeEnum2 = shape2.ShapeType();
    switch (shapeEnum2)
    {
      case TopAbs_EDGE:
      {
        TopoDS_Edge edge2 = TopoDS::Edge(shape2);
        ReparamCurve(edge2);
        if (dirflag == 1)
          shape2.Reverse();
        nbEdges2 = 1;
      }
      break;
      case TopAbs_WIRE:
      {
        wire2    = TopoDS::Wire(shape2);
        nbEdges2 = 0;
        for (TopoDS_Iterator cousto(wire2); cousto.More(); cousto.Next())
        {
          TopoDS_Edge edge2 = TopoDS::Edge(cousto.Value());
          ReparamCurve(edge2);
          nbEdges2++;
        }
        if (dirflag == 1)
        {
          occ::handle<ShapeExtend_WireData> sewd2 = new ShapeExtend_WireData;
          sewd2->Add(shape2);
          sewd2->Reverse();
          wire2 = sewd2->Wire();
        }
      }
      break;
      default:
      {

        return res;
      }
    }
  }
  else
  {
    Message_Msg msg149("XSTEP_149");
    SendFail(st, msg149);

    return res;
  }

  if (nbEdges1 != nbEdges2)
  {
    if (nbEdges1 == 1)
    {
      occ::handle<ShapeExtend_WireData> sewd1 = new ShapeExtend_WireData;
      sewd1->Add(shape1);
      wire1 = sewd1->Wire();
    }
    else if (nbEdges2 == 1)
    {
      occ::handle<ShapeExtend_WireData> sewd2 = new ShapeExtend_WireData;
      sewd2->Add(shape2);
      wire2 = sewd2->Wire();
    }

    if (!st->IsRuledByParameter())
    {
    }
    if (!ShapeAlgo::AlgoContainer()
           ->HomoWires(wire1, wire2, newWire1, newWire2, st->IsRuledByParameter()))
    {
      Message_Msg msg1255("IGES_1255");
      SendFail(st, msg1255);
      return res;
    }
    nbEdges1 = 2;
  }

  else if (nbEdges1 != 1)
  {
    newWire1 = wire1;
    newWire2 = wire2;
  }

  if (nbEdges1 == 1)
  {

    for (int i = 1; i <= 2; i++)
    {

      TopoDS_Edge edge = TopoDS::Edge(i == 1 ? shape1 : shape2);

      TopLoc_Location         L;
      double                  First, Last;
      occ::handle<Geom_Curve> curve =
        occ::down_cast<Geom_Curve>(BRep_Tool::Curve(edge, L, First, Last)->Copy());
      if (std::abs(First) <= Precision::PConfusion()
          && std::abs(Last - 1.) <= Precision::PConfusion())
        continue;

      occ::handle<Geom_BSplineCurve> bscurve;
      if (!curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
      {
        if (curve->FirstParameter() < First || curve->LastParameter() > Last)
          curve = new Geom_TrimmedCurve(curve, First, Last);
        bscurve = GeomConvert::CurveToBSplineCurve(curve, Convert_RationalC1);
      }
      else
      {
        bscurve = occ::down_cast<Geom_BSplineCurve>(curve);
        bscurve->Segment(First, Last);
      }
      NCollection_Array1<double> Knots(1, bscurve->NbKnots());
      bscurve->Knots(Knots);
      BSplCLib::Reparametrize(0., 1., Knots);
      bscurve->SetKnots(Knots);

      BRep_Builder B;
      B.UpdateEdge(edge, bscurve, L, Precision::Confusion());
      B.Range(edge, 0., 1);
      if (i == 1)
        shape1 = edge;
      else
        shape2 = edge;
    }

    res                            = BRepFill::Face(TopoDS::Edge(shape1), TopoDS::Edge(shape2));
    occ::handle<Geom_Surface> surf = BRep_Tool::Surface(TopoDS::Face(res));
    if (surf->Continuity() == GeomAbs_C0)
    {
      Message_Msg msg1250("IGES_1250");
      SendWarning(st, msg1250);
    }
  }
  else
  {
    res = BRepFill::Shell(newWire1, newWire2);
  }
  if (res.IsNull())
  {
    Message_Msg msg1255("IGES_1255");
    SendFail(st, msg1255);
    return res;
  }

  if (st->HasTransf())
  {
    gp_Trsf trsf;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               st->CompoundLocation(),
                                               trsf,
                                               GetUnitFactor()))
    {
      TopLoc_Location shapeLoc(trsf);
      res.Move(shapeLoc, false);
    }
    else
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(st, msg1035);
    }
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferSurfaceOfRevolution(
  const occ::handle<IGESGeom_SurfaceOfRevolution>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  IGESToBRep_TopoCurve             TC(*this);
  IGESToBRep_BasicCurve            BC(*this);
  occ::handle<IGESData_IGESEntity> igesGeneratrix = st->Generatrix();
  occ::handle<IGESGeom_Line>       igesAxis       = st->AxisOfRevolution();

  if (igesGeneratrix.IsNull() || !IGESToBRep::IsTopoCurve(igesGeneratrix))
  {
    Message_Msg msg153("XSTEP_153");
    SendFail(st, msg153);

    return res;
  }

  DeclareAndCast(IGESGeom_Line, srgen, st->Generatrix());
  if (!srgen.IsNull())
  {
    gp_Pnt gen1 = srgen->StartPoint();
    gp_Pnt gen2 = srgen->EndPoint();
    TheULength  = gen1.Distance(gen2) * GetUnitFactor();
  }

  if (igesAxis.IsNull())
  {
    Message_Msg msg152("XSTEP_152");
    SendFail(st, msg152);
    return res;
  }

  TC.SetContinuity(0);
  TopoDS_Shape generatrix = TC.TransferTopoCurve(igesGeneratrix);
  if (generatrix.IsNull())
  {
    Message_Msg                           msg1156("IGES_1156");
    const char*                           typeName("generatrix");
    occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesGeneratrix);
    msg1156.Arg(typeName);
    msg1156.Arg(label);
    SendFail(st, msg1156);

    return res;
  }

  gp_Trsf startLoc;
  gp_Pnt  pt1 = igesAxis->TransformedStartPoint();
  gp_Pnt  pt2 = igesAxis->TransformedEndPoint();
  pt1.Scale(gp_Pnt(0, 0, 0), GetUnitFactor());
  pt2.Scale(gp_Pnt(0, 0, 0), GetUnitFactor());

  gp_Ax1 revolAxis(pt1, gp_Dir(gp_Vec(pt2, pt1)));
  double startAngle  = 2 * M_PI - st->EndAngle();
  double endAngle    = 2 * M_PI - st->StartAngle();
  double deltaAngle  = endAngle - startAngle;
  bool   IsFullAngle = (deltaAngle > 2. * M_PI - Precision::PConfusion());
  if (IsFullAngle)
    deltaAngle = 2. * M_PI;

  startLoc.SetRotation(revolAxis, startAngle);
  generatrix.Move(startLoc);

  occ::handle<Geom_Curve> aBasisCurve;

  {
    try
    {
      OCC_CATCH_SIGNALS
      if (extractCurve3d(generatrix, aBasisCurve))
      {
        BRepBuilderAPI_MakeFace   aMakeF;
        occ::handle<Geom_Surface> aResultSurf =
          new Geom_SurfaceOfRevolution(aBasisCurve, revolAxis);

        if (!aResultSurf.IsNull())
        {
          if (!IsFullAngle)
          {
            const double VF = aBasisCurve->FirstParameter();
            const double VL = aBasisCurve->LastParameter();

            const double UF = 0;
            const double UL = endAngle - startAngle;

            aMakeF.Init(aResultSurf, UF, UL, VF, VL, Precision::Confusion());
          }
          else
          {
            aMakeF.Init(aResultSurf, true, Precision::Confusion());
          }

          if (aMakeF.IsDone())
            res = aMakeF.Face();
        }
      }
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: IgesToBRep_TopoSurface::"
                   "TransferSurfaceOfRevolution(): exception by Geom: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
    }
  }

  if (res.IsNull())
  {

    BRepPrimAPI_MakeRevol revol(generatrix, revolAxis, deltaAngle);

    res = revol.Shape();
  }

  if (res.ShapeType() == TopAbs_FACE)
  {
    occ::handle<Geom_Surface> surf = BRep_Tool::Surface(TopoDS::Face(res));
    if (surf->Continuity() == GeomAbs_C0)
    {
      Message_Msg msg1250("IGES_1250");
      SendWarning(st, msg1250);
    }
  }

  if (st->HasTransf())
  {
    gp_Trsf trsf;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               st->CompoundLocation(),
                                               trsf,
                                               GetUnitFactor()))
    {
      TopLoc_Location shapeLoc(trsf);
      res.Move(shapeLoc, false);
    }
    else
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(st, msg1035);
    }
  }

  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferTabulatedCylinder(
  const occ::handle<IGESGeom_TabulatedCylinder>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  IGESToBRep_TopoCurve TC(*this);

  occ::handle<IGESData_IGESEntity> igesDirectrix = st->Directrix();
  if (igesDirectrix.IsNull() || !IGESToBRep::IsTopoCurve(igesDirectrix))
  {
    Message_Msg msg153("XSTEP_153");
    SendFail(st, msg153);

    return res;
  }

  TC.SetContinuity(0);
  TopoDS_Shape directrix = TC.TransferTopoCurve(igesDirectrix);
  if (directrix.IsNull())
  {
    Message_Msg                           msg1156("IGES_1156");
    const char*                           typeName("directrix");
    occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesDirectrix);
    msg1156.Arg(typeName);
    msg1156.Arg(label);
    SendFail(st, msg1156);

    return res;
  }

  TopoDS_Vertex firstVertex, lastVertex;
  ShapeAnalysis::FindBounds(directrix, firstVertex, lastVertex);
  gp_Pnt pt1 = BRep_Tool::Pnt(firstVertex);
  gp_Pnt pt2 = st->EndPoint();
  pt2.Scale(gp_Pnt(0, 0, 0), GetUnitFactor());

  TheULength = pt1.Distance(pt2);
  if (TheULength < Precision::Confusion())
  {
    Message_Msg msg("Tabulated cylinder with zero length");
    SendFail(st, msg);
    return res;
  }

  occ::handle<Geom_Curve> aBasisCurve;
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (extractCurve3d(directrix, aBasisCurve))
      {
        gp_Vec                    dir(pt1, pt2);
        occ::handle<Geom_Surface> aResultSurf = new Geom_SurfaceOfLinearExtrusion(aBasisCurve, dir);
        if (!aResultSurf.IsNull())
        {

          BRepBuilderAPI_MakeFace aMakeF(aResultSurf,
                                         aBasisCurve->FirstParameter(),
                                         aBasisCurve->LastParameter(),
                                         0.,
                                         dir.Magnitude(),
                                         Precision::Confusion());
          if (aMakeF.IsDone())
            res = aMakeF.Face();
        }
      }
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout
        << "Warning: IgesToBRep_TopoSurface::TransferTabulatedCylinder(): exception by Geom: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
    }
  }

  if (res.IsNull())
  {

    BRepPrimAPI_MakePrism prism(directrix, gp_Vec(pt1, pt2));

    res = prism.Shape();
  }

  if (res.ShapeType() == TopAbs_FACE)
  {
    double UMin, UMax, VMin, VMax;
    BRepTools::UVBounds(TopoDS::Face(res), UMin, UMax, VMin, VMax);
    if (VMax <= Precision::PConfusion() && VMin < -Precision::PConfusion())
    {
      TheULength *= -1;
      res.Reverse();
    }
    occ::handle<Geom_Surface> surf = BRep_Tool::Surface(TopoDS::Face(res));
    if (surf->Continuity() == GeomAbs_C0)
    {
      Message_Msg msg1250("IGES_1250");
      SendWarning(st, msg1250);
    }
  }

  if (st->HasTransf())
  {
    gp_Trsf trsf;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               st->CompoundLocation(),
                                               trsf,
                                               GetUnitFactor()))
    {
      TopLoc_Location shapeLoc(trsf);
      res.Move(shapeLoc, false);
    }
    else
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(st, msg1035);
    }
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferOffsetSurface(
  const occ::handle<IGESGeom_OffsetSurface>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  TopoDS_Shape    igesShape;
  TopoDS_Face     face;
  TopLoc_Location basisLoc;

  occ::handle<IGESData_IGESEntity> igesSrf = st->Surface();
  if (igesSrf.IsNull() || !IGESToBRep::IsTopoSurface(igesSrf))
  {
    Message_Msg msg164("XSTEP_164");
    SendFail(st, msg164);

    return res;
  }

  igesShape = TransferTopoSurface(igesSrf);
  if (igesShape.IsNull())
  {
    Message_Msg                           msg1156("IGES_1156");
    const char*                           typeName("basis surface");
    occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSrf);
    msg1156.Arg(typeName);
    msg1156.Arg(label);
    SendFail(st, msg1156);
    return res;
  }

  TopAbs_ShapeEnum shapeEnum = igesShape.ShapeType();
  switch (shapeEnum)
  {
    case TopAbs_FACE:
    {
      face = TopoDS::Face(igesShape);
      break;
    }
    case TopAbs_SHELL:
    {
      TopoDS_Iterator dabovil(igesShape);
      if (dabovil.More())
      {
        SendWarning(st, "The First Surface only will be transferred.");
        face = TopoDS::Face(dabovil.Value());
        break;
      }
    }
      [[fallthrough]];
    default:
    {
      Message_Msg                           msg1156("IGES_1156");
      const char*                           typeName("basis surface");
      occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSrf);
      msg1156.Arg(typeName);
      msg1156.Arg(label);
      SendFail(st, msg1156);
      return res;
    }
  }

  occ::handle<Geom_Surface>       geomSupport = BRep_Tool::Surface(face);
  occ::handle<Geom_OffsetSurface> basisSrf;

  if (geomSupport->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
  {
    DeclareAndCast(Geom_OffsetSurface, geom140, geomSupport);
    geom140->SetOffsetValue(basisSrf->Offset() + st->Distance() * GetUnitFactor());
    basisSrf = geom140;
  }
  else
  {
    if (geomSupport->Continuity() == GeomAbs_C0)
    {
      res =
        ShapeAlgo::AlgoContainer()->C0ShapeToC1Shape(face,
                                                     std::abs(st->Distance()) * GetUnitFactor());
      if (res.ShapeType() != TopAbs_FACE)
      {
        Message_Msg msg1266("IGES_1266");
        SendFail(st, msg1266);
        return res;
      }
      else
      {
        geomSupport = BRep_Tool::Surface(TopoDS::Face(res));
        if (geomSupport->Continuity() == GeomAbs_C0)
        {
          Message_Msg msg1266("IGES_1266");

          SendFail(st, msg1266);

          res.Nullify();
          return res;
        }
      }
      Message_Msg msg1267("IGES_1267");
      SendWarning(st, msg1267);
    }

    if (res.IsNull())
      res = face;
    geomSupport = BRep_Tool::Surface(TopoDS::Face(res));
    double umin, umax, vmin, vmax;
    geomSupport->Bounds(umin, umax, vmin, vmax);
    if (Precision::IsInfinite(umin) || Precision::IsInfinite(umax) || Precision::IsInfinite(vmin)
        || Precision::IsInfinite(vmax))
    {

      BRepTools::UVBounds(face, umin, umax, vmin, vmax);
      occ::handle<Geom_RectangularTrimmedSurface> TS =
        new Geom_RectangularTrimmedSurface(geomSupport, umin, umax, vmin, vmax);
      occ::handle<Geom_BSplineSurface> BS =
        ShapeAlgo::AlgoContainer()->ConvertSurfaceToBSpline(TS, umin, umax, vmin, vmax);
      if (BS.IsNull() || BS->Continuity() == GeomAbs_C0)
      {
        Message_Msg msg1265("IGES_1265");
        SendFail(st, msg1265);
        return res;
      }
      else
      {
        geomSupport = BS;
      }
    }
    basisSrf = new Geom_OffsetSurface(geomSupport, st->Distance() * GetUnitFactor());
  }

  BRepLib_MakeFace MF(basisSrf, Precision::Confusion());
  if (!MF.IsDone())
  {
    Message_Msg msg1265("IGES_1265");
    SendFail(st, msg1265);
    return res;
  }

  res = MF.Face();

  if (st->HasTransf())
  {
    gp_Trsf trsf;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               st->CompoundLocation(),
                                               trsf,
                                               GetUnitFactor()))
    {
      TopLoc_Location loc2(trsf);
      res.Move(loc2, false);
    }
    else
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(st, msg1035);
    }
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferTrimmedSurface(
  const occ::handle<IGESGeom_TrimmedSurface>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  TopAbs_ShapeEnum     shapeEnum;
  IGESToBRep_TopoCurve TC(*this);

  occ::handle<IGESData_IGESEntity> igesSurface = st->Surface();
  if (igesSurface.IsNull() || !IGESToBRep::IsTopoSurface(igesSurface))
  {
    Message_Msg msg169("XSTEP_169");
    SendFail(st, msg169);

    return res;
  }
  gp_Trsf2d   trans;
  double      uFact;
  TopoDS_Face face, faceres;

  TopoDS_Shape myshape = ParamSurface(igesSurface, trans, uFact);

  if (!myshape.IsNull())
  {
    shapeEnum = myshape.ShapeType();
    switch (shapeEnum)
    {
      case TopAbs_FACE:
      {
        face    = TopoDS::Face(myshape);
        faceres = face;
        break;
      }
      case TopAbs_SHELL:
      {
        TopoDS_Iterator IT(myshape);
        int             nbfaces = 0;
        for (; IT.More(); IT.Next())
        {
          nbfaces++;
          face    = TopoDS::Face(IT.Value());
          faceres = face;
        }

        if (nbfaces != 1)
        {
          Message_Msg                           msg1156("IGES_1156");
          const char*                           typeName("basis surface");
          occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSurface);
          msg1156.Arg(typeName);
          msg1156.Arg(label);
          SendFail(st, msg1156);
          return myshape;
        }
      }
      break;
      default:
      {
        Message_Msg                           msg1156("IGES_1156");
        const char*                           typeName("basis surface");
        occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSurface);
        msg1156.Arg(typeName);
        msg1156.Arg(label);
        SendFail(st, msg1156);
        return res;
      }
    }
  }
  else
  {
    return res;
  }

  TopLoc_Location           L;
  occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(face, L);
  TC.SetSurface(aSurf);

  if (st->HasOuterContour())
  {
    face.EmptyCopy();
    TopoDS_Shape myshape1 = TC.TransferCurveOnFace(face, st->OuterContour(), trans, uFact, false);

    if (myshape1.IsNull())
    {
      face = faceres;
      BRep_Builder B;
      B.NaturalRestriction(face, false);
    }
  }
  for (int i = 1; i <= st->NbInnerContours(); i++)
  {
    TopoDS_Shape myshape2 = TC.TransferCurveOnFace(face, st->InnerContour(i), trans, uFact, false);
  }

  occ::handle<IGESData_TransfEntity> aTransf = st->Transf();
  if (!aTransf.IsNull())
  {

    gp_GTrsf aGT    = aTransf->Value();
    gp_XYZ   aTrans = aGT.TranslationPart();
    gp_Mat   aMat   = aGT.VectorialPart();
    double   s1     = aMat.Value(1, 1) * aMat.Value(1, 1) + aMat.Value(2, 1) * aMat.Value(2, 1)
                + aMat.Value(3, 1) * aMat.Value(3, 1);
    double s2 = aMat.Value(1, 2) * aMat.Value(1, 2) + aMat.Value(2, 2) * aMat.Value(2, 2)
                + aMat.Value(3, 2) * aMat.Value(3, 2);
    double s3 = aMat.Value(1, 3) * aMat.Value(1, 3) + aMat.Value(2, 3) * aMat.Value(2, 3)
                + aMat.Value(3, 3) * aMat.Value(3, 3);
    if (fabs(s1 - s2) > Precision::Confusion() || fabs(s1 - s3) > Precision::Confusion())
    {
      BRepBuilderAPI_GTransform aTransform(aGT);
      aTransform.Perform(face, true);
      if (aTransform.IsDone())
      {
        if (aTransform.Shape().ShapeType() == TopAbs_FACE)
        {
          face = TopoDS::Face(aTransform.Shape());
        }
      }
    }
    else
    {
      double tmpVal = fabs(aMat.Value(1, 1) - 1.) + fabs(aMat.Value(1, 2)) + fabs(aMat.Value(1, 3))
                      + fabs(aMat.Value(2, 1)) + fabs(aMat.Value(2, 2) - 1.)
                      + fabs(aMat.Value(2, 3)) + fabs(aMat.Value(3, 1)) + fabs(aMat.Value(3, 2))
                      + fabs(aMat.Value(3, 3) - 1.);
      if ((tmpVal + aTrans.Modulus()) > Precision::Confusion())
      {

        gp_Trsf aT;
        aT.SetValues(aMat.Value(1, 1),
                     aMat.Value(1, 2),
                     aMat.Value(1, 3),
                     aTrans.X(),
                     aMat.Value(2, 1),
                     aMat.Value(2, 2),
                     aMat.Value(2, 3),
                     aTrans.Y(),
                     aMat.Value(3, 1),
                     aMat.Value(3, 2),
                     aMat.Value(3, 3),
                     aTrans.Z());
        TopLoc_Location aLoc(aT);
        face.Move(aLoc, false);
      }
    }
  }

  BRepTools::Update(face);

  return face;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferBoundedSurface(
  const occ::handle<IGESGeom_BoundedSurface>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  if (st->RepresentationType() == 0)
  {
    Message_Msg msg1275("IGES_1275");
    SendWarning(st, msg1275);
  }

  TopAbs_ShapeEnum                 shapeEnum;
  IGESToBRep_TopoCurve             TC(*this);
  occ::handle<IGESData_IGESEntity> igesSrf = st->Surface();
  if (igesSrf.IsNull() || !IGESToBRep::IsTopoSurface(igesSrf))
  {
    Message_Msg msg166("XSTEP_166");
    SendFail(st, msg166);

    return res;
  }
  gp_Trsf2d   trans;
  double      uFact;
  TopoDS_Face face;

  TopoDS_Shape myshape = ParamSurface(igesSrf, trans, uFact);

  if (myshape.IsNull())
  {

#ifdef OCCT_DEBUG
    std::cout << "Fail: IGESToBRep_TopoSurface::TransferBoundedSurface  UntrimmedSurface is "
                 "translated into Null"
              << std::endl;
#endif
    return res;
  }
  else
  {
    shapeEnum = myshape.ShapeType();
    switch (shapeEnum)
    {
      case TopAbs_FACE:
      {
        face = TopoDS::Face(myshape);
      }
      break;
      case TopAbs_SHELL:
      {
        TopoDS_Iterator IT(myshape);
        int             nbfaces = 0;
        for (; IT.More(); IT.Next())
        {
          nbfaces++;
          face = TopoDS::Face(IT.Value());
        }

        if (nbfaces != 1)
        {
          Message_Msg                           msg1156("IGES_1156");
          const char*                           typeName("basis surface");
          occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSrf);
          msg1156.Arg(typeName);
          msg1156.Arg(label);
          SendFail(st, msg1156);

          return myshape;
        }
      }
      break;
      default:
      {
        Message_Msg                           msg1156("IGES_1156");
        const char*                           typeName("basis surface");
        occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSrf);
        msg1156.Arg(typeName);
        msg1156.Arg(label);
        SendFail(st, msg1156);
        return res;
      }
    }
  }

  face.EmptyCopy();
  for (int i = 1; i <= st->NbBoundaries(); i++)
    TC.TransferBoundaryOnFace(face, st->Boundary(i), trans, uFact);

  BRepTools::Update(face);

  return face;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferPlane(const occ::handle<IGESGeom_Plane>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  gp_Pln  pln;
  gp_Trsf trsf;
  res = TransferPlaneParts(st, pln, trsf, true);

  if (trsf.Form() != gp_Identity)
  {
    TopLoc_Location loc(trsf);
    res.Location(loc, false);
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferPerforate(
  const occ::handle<IGESBasic_SingleParent>& st)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  gp_Pln  pln;
  gp_Trsf trsf;
  DeclareAndCast(IGESGeom_Plane, p0, st->SingleParent());
  BRep_Builder B;
  if (p0.IsNull())
  {
    Message_Msg msg206("XSTEP_206");
    SendFail(st, msg206);

    return res;
  }
  res = TransferPlaneParts(p0, pln, trsf, true);

  int nb = st->NbChildren();
  for (int i = 1; i <= nb; i++)
  {
    DeclareAndCast(IGESGeom_Plane, pi, st->Child(i));
    if (pi.IsNull())
    {
      Message_Msg msg1285("IGES_1285");
      msg1285.Arg(i);

      SendWarning(st, msg1285);
      continue;
    }
    gp_Pln       pli;
    gp_Trsf      trsi;
    TopoDS_Shape wire = TransferPlaneParts(pi, pli, trsi, false);

    if (wire.ShapeType() != TopAbs_WIRE)
    {
      Message_Msg                           msg1156("IGES_1156");
      const char*                           typeName("hole");
      occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(pi);
      msg1156.Arg(typeName);
      msg1156.Arg(label);
      SendWarning(st, msg1156);

      continue;
    }

    if (!pln.Position().IsCoplanar(pli.Position(), GetEpsGeom(), GetEpsilon()))
    {
      Message_Msg msg1295("IGES_1295");
      msg1295.Arg(i);
      SendWarning(st, msg1295);
    }

    if (trsi.Form() != gp_Identity)
    {
      TopLoc_Location locw(trsi);
      wire.Location(locw, false);
    }
    B.Add(res, wire);
  }

  if (trsf.Form() != gp_Identity)
  {
    TopLoc_Location loc(trsf);
    res.Location(loc, false);
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::TransferPlaneParts(const occ::handle<IGESGeom_Plane>& st,
                                                        gp_Pln&                            pln,
                                                        gp_Trsf&                           trsf,
                                                        const bool                         first)
{

  TopoDS_Shape res;
  if (st.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  double a, b, c, d;

  st->Equation(a, b, c, d);
  pln = gp_Pln(a, b, c, -d);

  TopoDS_Face  plane;
  TopoDS_Wire  wire;
  BRep_Builder B;
  if (first)
  {
    B.MakeFace(plane);
    occ::handle<Geom_Plane> geomPln = new Geom_Plane(pln);
    geomPln->Scale(gp_Pnt(0, 0, 0), GetUnitFactor());

    B.UpdateFace(plane, geomPln, TopLoc_Location(), Precision::Confusion());

    plane.Infinite(true);
  }

  if (st->HasTransf())
  {
    SetEpsilon(1.E-04);
    if (!IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                                st->CompoundLocation(),
                                                trsf,
                                                GetUnitFactor()))
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(st, msg1035);
    }
  }

  if (st->HasBoundingCurve())
  {
    IGESToBRep_TopoCurve             TC(*this);
    occ::handle<IGESData_IGESEntity> crv = st->BoundingCurve();

    if (crv.IsNull())
    {
      Message_Msg msg1300("IGES_1300");
      SendWarning(st, msg1300);
    }
    else

      if (IGESToBRep::IsTopoCurve(crv))
    {
      gp_Trsf trans;
      if (crv->IsKind(STANDARD_TYPE(IGESGeom_CurveOnSurface)))
      {
        DeclareAndCast(IGESGeom_CurveOnSurface, crv142, crv);
        TopoDS_Shape myshape = TC.TransferCurveOnFace(plane, crv142, trans, TheULength, false);

        if (first)
        {
          TopExp_Explorer ws(plane, TopAbs_WIRE);
          if (ws.More())
            plane.Infinite(false);
        }
      }
      else
      {
        TopoDS_Shape     shape     = TC.TransferTopoCurve(crv);
        TopAbs_ShapeEnum shapeEnum = shape.ShapeType();
        switch (shapeEnum)
        {
          case TopAbs_EDGE:
          {
            TopoDS_Edge                       edge = TopoDS::Edge(shape);
            occ::handle<ShapeExtend_WireData> sewd = new ShapeExtend_WireData;
            sewd->Add(edge);
            wire = sewd->Wire();
          }
          break;
          case TopAbs_WIRE:
          {
            wire = TopoDS::Wire(shape);
          }
          break;
          default:
          {
            Message_Msg                           msg1156("IGES_1156");
            const char*                           typeName("Bounding curve");
            occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(crv);
            msg1156.Arg(typeName);
            msg1156.Arg(label);
            SendWarning(st, msg1156);
            if (first)
              res = plane;
            else
              res = wire;
            return res;
          }
        }

        occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
        sfw->Load(wire);
        sfw->FixConnected(GetMaxTol());
        wire = sfw->Wire();
        BRepLib_MakeFace MF(pln, wire, false);
        if (!MF.IsDone())
        {

          return res;
        }

        const TopoDS_Face& F = MF.Face();
        GProp_GProps       G;
        BRepGProp::SurfaceProperties(F, G);
        if (G.Mass() < 0)
        {
          if (!st->HasBoundingCurveHole())
            wire.Reverse();
        }
        else if (st->HasBoundingCurveHole())
          wire.Reverse();

        if (first)
        {
          B.Add(plane, wire);
          plane.Infinite(false);
        }
      }
    }
    else
    {
      Message_Msg                           msg1156("IGES_1156");
      const char*                           typeName("Bounding curve");
      occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(crv);
      msg1156.Arg(typeName);
      msg1156.Arg(label);
      SendWarning(st, msg1156);
    }
  }

  if (first)
    res = plane;
  else
    res = wire;
  return res;
}

TopoDS_Shape IGESToBRep_TopoSurface::ParamSurface(const occ::handle<IGESData_IGESEntity>& st,
                                                  gp_Trsf2d&                              trans,
                                                  double&                                 uFact)
{

  TopoDS_Shape res;

  TopoDS_Shape basisSurface = TransferTopoSurface(st);
  double       uscale       = 1.;
  double       cscale       = TheULength;
  if (basisSurface.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(st, msg1005);
    return res;
  }

  TopAbs_ShapeEnum shapeEnum;
  shapeEnum = basisSurface.ShapeType();
  TopoDS_Face face;
  switch (shapeEnum)
  {
    case TopAbs_FACE:
    {
      face = TopoDS::Face(basisSurface);
      break;
    }
    case TopAbs_SHELL:
    {
      TopoDS_Iterator IT(basisSurface);
      int             nbfaces = 0;
      for (; IT.More(); IT.Next())
      {
        nbfaces++;
        face = TopoDS::Face(IT.Value());
      }

      if (nbfaces != 1)
      {
        Message_Msg                           msg1156("IGES_1156");
        const char*                           typeName("basis surface");
        occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(st);
        msg1156.Arg(typeName);
        msg1156.Arg(label);
        SendWarning(st, msg1156);
        return basisSurface;
      }
    }
    break;
    default:
    {

      return res;
    }
  }

  double                    paramu = 0., paramv = 0.;
  TopLoc_Location           L;
  TopoDS_Edge               theedge;
  occ::handle<Geom_Surface> Surf = BRep_Tool::Surface(face);

  if (Surf->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    DeclareAndCast(Geom_RectangularTrimmedSurface, rectang, Surf);
    Surf = rectang->BasisSurface();
  }

  if ((Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))
      || (Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
      || (Surf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
      || (Surf->IsKind(STANDARD_TYPE(Geom_SphericalSurface))))
  {
    TopExp_Explorer TE;
    for (TE.Init(face, TopAbs_EDGE); TE.More(); TE.Next())
    {
      TopoDS_Edge               myedge = TopoDS::Edge(TE.Current());
      double                    First, Last;
      occ::handle<Geom2d_Curve> Curve2d = BRep_Tool::CurveOnSurface(myedge, face, First, Last);
      if (Curve2d->IsKind(STANDARD_TYPE(Geom2d_Line)))
      {
        DeclareAndCast(Geom2d_Line, Line2d, Curve2d);
        if (Line2d->Direction().IsParallel(gp::DY2d(), Precision::Angular()))
        {
          theedge = myedge;
          break;
        }
      }
    }

    double                  First, Last;
    occ::handle<Geom_Curve> Curve3d = BRep_Tool::Curve(theedge, First, Last);
    if (Precision::IsNegativeInfinite(First))
      First = 0.;

    if (Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))
    {
      DeclareAndCast(Geom_CylindricalSurface, Cyl, Surf);
      gp_Cylinder TheCyl = Cyl->Cylinder();
      ElSLib::CylinderParameters(TheCyl.Position(),
                                 TheCyl.Radius(),
                                 Curve3d->Value(First),
                                 paramu,
                                 paramv);
    }

    else if (Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
    {
      DeclareAndCast(Geom_ConicalSurface, Cone, Surf);
      gp_Cone TheCone = Cone->Cone();
      ElSLib::ConeParameters(TheCone.Position(),
                             TheCone.RefRadius(),
                             TheCone.SemiAngle(),
                             Curve3d->Value(First),
                             paramu,
                             paramv);
    }

    else if (Surf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
    {
      DeclareAndCast(Geom_ToroidalSurface, Tore, Surf);
      gp_Torus TheTore = Tore->Torus();
      ElSLib::TorusParameters(TheTore.Position(),
                              TheTore.MajorRadius(),
                              TheTore.MinorRadius(),
                              Curve3d->Value(First),
                              paramu,
                              paramv);
    }
    else if (Surf->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) &&

             !st->IsKind(STANDARD_TYPE(IGESSolid_SphericalSurface)))
    {
      DeclareAndCast(Geom_SphericalSurface, Sphere, Surf);
      gp_Sphere TheSphere = Sphere->Sphere();
      ElSLib::SphereParameters(TheSphere.Position(),
                               TheSphere.Radius(),
                               Curve3d->Value(First),
                               paramu,
                               paramv);
    }

    if (st->IsKind(STANDARD_TYPE(IGESGeom_SurfaceOfRevolution)))
    {
      DeclareAndCast(IGESGeom_SurfaceOfRevolution, revol, st);
      occ::handle<IGESData_IGESEntity> generatrix = revol->Generatrix();
      if (generatrix->IsKind(STANDARD_TYPE(IGESGeom_CircularArc)))
      {
        DeclareAndCast(IGESGeom_CircularArc, circ, generatrix);
        gp_Pnt2d startpoint = circ->StartPoint();
        paramv -= ElCLib::Parameter(
          gp_Circ2d(gp_Ax2d(circ->Center(), gp_Dir2d(gp_Dir2d::D::X)), circ->Radius()),
          startpoint);
        if (Surf->IsKind(STANDARD_TYPE(Geom_SphericalSurface)))
          paramv += ShapeAnalysis::AdjustToPeriod(paramv, -M_PI, M_PI);
        else if (Surf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
          paramv += ShapeAnalysis::AdjustToPeriod(paramv, 0, M_PI * 2);
      }
    }
    else if (st->IsKind(STANDARD_TYPE(IGESGeom_TabulatedCylinder)))
    {
      DeclareAndCast(IGESGeom_TabulatedCylinder, cylinder, st);
      occ::handle<IGESData_IGESEntity> directrix = cylinder->Directrix();
      if (directrix->IsKind(STANDARD_TYPE(IGESGeom_CircularArc)))
      {
        DeclareAndCast(IGESGeom_CircularArc, circ, directrix);
        gp_Pnt2d startpoint = circ->StartPoint();
        paramu -= ElCLib::Parameter(
          gp_Circ2d(gp_Ax2d(circ->Center(), gp_Dir2d(gp_Dir2d::D::X)), circ->Radius()),
          startpoint);
        paramu += ShapeAnalysis::AdjustToPeriod(paramu, 0, M_PI * 2);
      }
    }
  }

  if (std::abs(paramu) <= Precision::Confusion())
    paramu = 0.;
  if (std::abs(paramv) <= Precision::Confusion())
    paramv = 0.;

  occ::handle<IGESData_IGESEntity> isrf = st;
  if (isrf->IsKind(STANDARD_TYPE(IGESGeom_OffsetSurface)))
  {
    DeclareAndCast(IGESGeom_OffsetSurface, offsurf, isrf);
    isrf = offsurf->Surface();
  }
  if (isrf->IsKind(STANDARD_TYPE(IGESGeom_SurfaceOfRevolution)))
  {
    DeclareAndCast(IGESGeom_SurfaceOfRevolution, st120, isrf);

    gp_Trsf2d tmp;
    tmp.SetTranslation(gp_Vec2d(0, -2 * M_PI));
    trans.PreMultiply(tmp);
    tmp.SetMirror(gp::OX2d());
    trans.PreMultiply(tmp);
    tmp.SetMirror(gp_Ax2d(gp::Origin2d(), gp_Dir2d(1., 1.)));
    trans.PreMultiply(tmp);
    uscale = 1. / cscale;

    paramu = -(2 * M_PI - st120->EndAngle());
  }
  else
    paramu = 0.;

  if (isrf->IsKind(STANDARD_TYPE(IGESGeom_RuledSurface)))
  {
    uscale = 1. / cscale;
  }

  if (isrf->IsKind(STANDARD_TYPE(IGESGeom_TabulatedCylinder)))
  {
    occ::handle<IGESGeom_TabulatedCylinder> igtc = occ::down_cast<IGESGeom_TabulatedCylinder>(isrf);
    occ::handle<IGESData_IGESEntity>        idie = igtc->Directrix();
    double                                  uln  = 1;
    double                                  Umin, Umax, Vmin, Vmax;

    Surf->Bounds(Umin, Umax, Vmin, Vmax);
    uln = std::abs(Umax - Umin);

    uscale = uln / cscale;
    paramu = Umin / uln;
  }

  if (isrf->IsKind(STANDARD_TYPE(IGESSolid_CylindricalSurface))
      || isrf->IsKind(STANDARD_TYPE(IGESSolid_ConicalSurface)))
  {
    uscale = M_PI / 180.;
  }

  if (isrf->IsKind(STANDARD_TYPE(IGESSolid_SphericalSurface)))
  {
    cscale = M_PI / 180.;
    uscale = 1.;
  }

  if (isrf->IsKind(STANDARD_TYPE(IGESSolid_ToroidalSurface)))
  {
    gp_Trsf2d tmp;
    tmp.SetTranslation(gp_Vec2d(0, -360.));
    trans.PreMultiply(tmp);
    tmp.SetMirror(gp::OX2d());
    trans.PreMultiply(tmp);
    tmp.SetMirror(gp_Ax2d(gp::Origin2d(), gp_Dir2d(1., 1.)));
    trans.PreMultiply(tmp);
    if (paramv > 0)
      paramv = paramv * 180. / M_PI;
    cscale = M_PI / 180.;
    uscale = 1.;
  }

  gp_Trsf2d tmp;
  tmp.SetTranslation(gp_Pnt2d(0., 0.), gp_Pnt2d(paramu, paramv));
  trans.PreMultiply(tmp);

  tmp.SetScale(gp_Pnt2d(0, 0), cscale);
  trans.PreMultiply(tmp);
  uFact = uscale;
  return face;
}
