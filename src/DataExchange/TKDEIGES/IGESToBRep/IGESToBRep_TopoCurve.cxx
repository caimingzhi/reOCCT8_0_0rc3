

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepTools.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Dir.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_ToolLocation.hpp>
#include <IGESGeom_Boundary.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <IGESGeom_CurveOnSurface.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_SplineCurve.hpp>
#include <IGESToBRep.hpp>
#include <IGESToBRep_AlgoContainer.hpp>
#include <IGESToBRep_BasicCurve.hpp>
#include <IGESToBRep_CurveAndSurface.hpp>
#include <IGESToBRep_IGESBoundary.hpp>
#include <IGESToBRep_ToolContainer.hpp>
#include <IGESToBRep_TopoCurve.hpp>
#include <IGESToBRep_TopoSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Msg.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <ShapeBuild_Edge.hpp>
#include <ShapeFix_Wire.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Geom2d_BoundedCurve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Geom_BoundedCurve.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

#include <cstdio>

IGESToBRep_TopoCurve::IGESToBRep_TopoCurve()

  = default;

IGESToBRep_TopoCurve::IGESToBRep_TopoCurve(const IGESToBRep_TopoCurve& other)
    : IGESToBRep_CurveAndSurface(other)
{
  TheCurves.Assign(other.TheCurves);
  TheCurves2d.Assign(other.TheCurves2d);
}

IGESToBRep_TopoCurve::IGESToBRep_TopoCurve(const IGESToBRep_CurveAndSurface& CS)
    : IGESToBRep_CurveAndSurface(CS)
{
}

IGESToBRep_TopoCurve::IGESToBRep_TopoCurve(const double eps,
                                           const double epsCoeff,
                                           const double epsGeom,
                                           const bool   mode,
                                           const bool   modeapprox,
                                           const bool   optimized)
    : IGESToBRep_CurveAndSurface(eps, epsCoeff, epsGeom, mode, modeapprox, optimized)
{
}

TopoDS_Vertex IGESToBRep_TopoCurve::TransferPoint(const occ::handle<IGESGeom_Point>& start)

{
  TopoDS_Vertex V1;
  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return V1;
  }

  BRep_Builder B;
  gp_Pnt       point;

  if (!GetModeTransfer() && start->HasTransf())
    point = start->TransformedValue();
  else
    point = start->Value();

  point.Scale(gp_Pnt(0, 0, 0), GetUnitFactor());
  B.MakeVertex(V1, point, Precision::Confusion());

  if (GetModeTransfer() && start->HasTransf())
  {
    gp_Trsf T;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               start->CompoundLocation(),
                                               T,
                                               GetUnitFactor()))
    {
      TopLoc_Location L(T);
      V1.Move(L);
    }
  }

  return V1;
}

TopoDS_Vertex IGESToBRep_TopoCurve::Transfer2dPoint(const occ::handle<IGESGeom_Point>& start)

{
  TopoDS_Vertex V1;
  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return V1;
  }

  BRep_Builder B;
  gp_Pnt       point;

  if (!GetModeTransfer() && start->HasTransf())
    point = gp_Pnt(start->TransformedValue().X(), start->TransformedValue().Y(), 0.);
  else
    point = gp_Pnt(start->Value().X(), start->Value().Y(), 0.);

  B.MakeVertex(V1, point, Precision::Confusion());
  return V1;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferCompositeCurveGeneral(
  const occ::handle<IGESGeom_CompositeCurve>& start,
  const bool                                  is2d,
  const TopoDS_Face&                          face,
  const gp_Trsf2d&                            trans,
  const double                                uFact)

{
  TopoDS_Shape res;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }

  double precision = GetEpsGeom() * GetUnitFactor(), maxtol = GetMaxTol();

  occ::handle<ShapeExtend_WireData> sewd = new ShapeExtend_WireData();
  occ::handle<ShapeAnalysis_Wire>   saw  = new ShapeAnalysis_Wire;
  saw->Load(sewd);
  saw->SetPrecision(precision);

  for (int i = 1; i <= start->NbCurves(); i++)
  {

    occ::handle<IGESData_IGESEntity> IgesEnt = start->Curve(i);

    if (i > 1 && IgesEnt == start->Curve(i - 1))
    {

      Message_Msg Msg1045("IGES_1045");

      Msg1045.Arg(i);
      SendWarning(start, Msg1045);

      continue;
    }
    if (IgesEnt.IsNull())
    {
      Message_Msg Msg1040("IGES_1040");
      Msg1040.Arg(i);
      SendFail(start, Msg1040);
      return res;
    }

    if (is2d
        && (IgesEnt->IsKind(STANDARD_TYPE(IGESGeom_Boundary))
            || IgesEnt->IsKind(STANDARD_TYPE(IGESGeom_CurveOnSurface))))
    {

      Message_Msg Msg1040("IGES_1040");
      Msg1040.Arg(i);
      SendFail(start, Msg1040);
      return res;
    }
    else if (IGESToBRep::IsTopoCurve(IgesEnt))
    {
      TopoDS_Shape shape;
      if (is2d)
        shape = Transfer2dTopoCurve(IgesEnt, face, trans, uFact);
      else
        shape = TransferTopoCurve(IgesEnt);
      if (!shape.IsNull())
      {
        if (shape.ShapeType() == TopAbs_VERTEX)
          continue;

        occ::handle<ShapeExtend_WireData> nextsewd = new ShapeExtend_WireData;
        nextsewd->Add(shape);
        double distmin;
        bool   revsewd, revnextsewd;
        bool   isConnected = ShapeAlgo::AlgoContainer()->ConnectNextWire(saw,
                                                                       nextsewd,
                                                                       maxtol,
                                                                       distmin,
                                                                       revsewd,
                                                                       revnextsewd);
        if (isConnected)
        {
          if (revsewd)
          {

            Message_Msg Msg1051("IGES_1051");

            Msg1051.Arg((is2d ? 2 : 3));
            Msg1051.Arg(i);
            SendWarning(start, Msg1051);
          }
          if (revnextsewd)
          {
            Message_Msg Msg1050("IGES_1050");
            Msg1050.Arg((is2d ? 2 : 3));
            Msg1050.Arg(i);
            SendWarning(start, Msg1050);
          }
          if (distmin > precision)
          {
            Message_Msg Msg1055("IGES_1055");
            Msg1055.Arg((is2d ? 2 : 3));
            Msg1055.Arg(i);
            SendWarning(start, Msg1055);
          }
        }
        else
        {
          Message_Msg Msg1060("IGES_1060");
          Msg1060.Arg((is2d ? 2 : 3));
          Msg1060.Arg(i);
          SendFail(start, Msg1060);
          return res;
        }
      }
    }
  }

  occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
  sfw->Load(sewd);
  sfw->ClosedWireMode() = false;
  sfw->FixConnected(maxtol);
  sfw->FixConnected(1, precision);
  res = sewd->Wire();

  SetShapeResult(start, res);
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferCompositeCurve(
  const occ::handle<IGESGeom_CompositeCurve>& start)

{
  TopoDS_Shape res;
  TopoDS_Face  f;
  gp_Trsf      trans;
  res = TransferCompositeCurveGeneral(start, false, f, trans, 1.);

  if (!res.IsNull() && start->HasTransf())
  {
    gp_Trsf T;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               start->CompoundLocation(),
                                               T,
                                               GetUnitFactor()))
    {
      TopLoc_Location L(T);
      res.Move(L);
    }
    else
    {
      Message_Msg Msg1035("IGES_1035");
      SendWarning(start, Msg1035);
    }
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::Transfer2dCompositeCurve(
  const occ::handle<IGESGeom_CompositeCurve>& start,
  const TopoDS_Face&                          face,
  const gp_Trsf2d&                            trans,
  const double                                uFact)

{
  TopoDS_Shape res;
  res = TransferCompositeCurveGeneral(start, true, face, trans, uFact);

  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferCurveOnSurface(
  const occ::handle<IGESGeom_CurveOnSurface>& start)
{
  TopoDS_Shape res;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }

  TopoDS_Face                      face;
  occ::handle<IGESData_IGESEntity> igesSurface = start->Surface();
  if (igesSurface.IsNull() || !IGESToBRep::IsTopoSurface(igesSurface))
  {
    Message_Msg Msg131("XSTEP_131");
    SendFail(start, Msg131);

    return res;
  }
  TopAbs_ShapeEnum       shapeEnum;
  IGESToBRep_TopoSurface TS(*this);
  gp_Trsf2d              trans;
  double                 uFact;
  TopoDS_Shape           myshape = TS.ParamSurface(igesSurface, trans, uFact);

  if (!myshape.IsNull())
  {
    shapeEnum = myshape.ShapeType();
    switch (shapeEnum)
    {
      case TopAbs_FACE:
      {
        face = TopoDS::Face(myshape);
        break;
      }
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
          if (!start->Curve3D().IsNull())
          {
            if (IGESToBRep::IsTopoCurve(start->Curve3D()))
            {
              TopoDS_Shape Sh = TransferTopoCurve(start->Curve3D());
              if (!Sh.IsNull())
              {
                Message_Msg Msg1062("IGES_1062");

                SendWarning(start, Msg1062);
                res = Sh;
              }
            }
          }
          else
          {
            Message_Msg Msg1061("IGES_1061");
            Msg1061.Arg("CurveOnSurface");
            SendFail(start, Msg1061);
          }
          return res;
        }
      }
      break;
      default:
      {
        if (!start->Curve3D().IsNull())
        {
          if (IGESToBRep::IsTopoCurve(start->Curve3D()))
          {
            TopoDS_Shape Sh = TransferTopoCurve(start->Curve3D());
            if (!Sh.IsNull())
            {
              Message_Msg Msg1062("IGES_1062");
              SendWarning(start, Msg1062);

              res = Sh;
            }
          }
        }
        else
        {
          Message_Msg Msg1061("IGES_1061");
          Msg1061.Arg("CurveOnSurface");
          SendFail(start, Msg1061);
        }

        return res;
      }
    }
  }

  face.EmptyCopy();
  res = TransferCurveOnFace(face, start, trans, uFact, true);
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferCurveOnFace(
  TopoDS_Face&                                face,
  const occ::handle<IGESGeom_CurveOnSurface>& start,
  const gp_Trsf2d&                            trans,
  const double                                uFact,
  const bool                                  isCurveOnSurf)
{
  TopoDS_Shape res;
  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);
    return res;
  }

  bool okCurve = true, okCurve3d = true, okCurve2d = true;
  int  filepreference = 0;
  if (start->PreferenceMode() == 1)
    filepreference = 2;
  else if (start->PreferenceMode() == 2)
    filepreference = 3;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Curves2d =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, 1);
  Curves2d->SetValue(1, start->CurveUV());

  occ::handle<IGESToBRep_IGESBoundary> IB =
    IGESToBRep::AlgoContainer()->ToolContainer()->IGESBoundary();
  IB->Init(*this, start, face, trans, uFact, filepreference);
  bool Result = IB->Transfer(okCurve, okCurve3d, okCurve2d, start->Curve3D(), false, Curves2d, 1);
  IB->Check(Result, !isCurveOnSurf, okCurve3d, okCurve2d);
  occ::handle<ShapeExtend_WireData> sewd = IB->WireData();
  if (sewd->NbEdges() == 0)
  {
    Message_Msg Msg1095("IGES_1095");
    SendFail(start, Msg1095);
    return res;
  }

  TopoDS_Wire mywire = sewd->Wire();

  if (start->HasTransf())
  {
    gp_Trsf T;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(), start->CompoundLocation(), T))
    {
      TopLoc_Location L(T);
      mywire.Move(L);
    }
    else
    {
      Message_Msg Msg1035("IGES_1035");
      SendWarning(start, Msg1035);
    }
  }

  BRepLib_MakeFace MF(face);
  MF.Add(mywire);
  face = MF.Face();
  SetShapeResult(start, mywire);
  return mywire;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferOffsetCurve(
  const occ::handle<IGESGeom_OffsetCurve>& start)

{
  TopoDS_Shape res;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }
  if (start->OffsetType() != 1)
  {
    Message_Msg Msg1100("IGES_1100");
    SendFail(start, Msg1100);

    return res;
  }

  double Offset = start->FirstOffsetDistance();
  gp_Dir NrmDir;
  if (start->HasTransf())
    NrmDir = start->TransformedNormalVector();
  else
    NrmDir = start->NormalVector();

  NrmDir.Reverse();

  occ::handle<IGESData_IGESEntity> BaseCrv = start->BaseCurve();

  while (BaseCrv->IsKind(STANDARD_TYPE(IGESGeom_OffsetCurve)))
  {
    DeclareAndCast(IGESGeom_OffsetCurve, OffCrv, BaseCrv);
    if (OffCrv->OffsetType() != 1)
    {
      Message_Msg Msg1100("IGES_1100");
      SendFail(start, Msg1100);
      return res;
    }
    BaseCrv = OffCrv->BaseCurve();
    Offset  = Offset + OffCrv->FirstOffsetDistance();
  }

  if (!IGESToBRep::IsTopoCurve(BaseCrv))
  {
    Message_Msg Msg110("XSTEP_110");
    SendFail(start, Msg110);
    return res;
  }

  occ::handle<Geom_Curve>       Crv;
  occ::handle<Geom_OffsetCurve> OffCrv;

  IGESToBRep_TopoCurve TC(*this);
  TopoDS_Shape         Sh = TC.TransferTopoCurve(BaseCrv);

  if (Sh.IsNull() || ((Sh.ShapeType() != TopAbs_EDGE) && (Sh.ShapeType() != TopAbs_WIRE)))
  {
    Message_Msg                           Msg1156("IGES_1156");
    occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(BaseCrv);
    Msg1156.Arg("basis curve");
    Msg1156.Arg(label);
    SendFail(start, Msg1156);

    return res;
  }

  if (Sh.ShapeType() == TopAbs_EDGE)
  {
    TopLoc_Location aLoc;
    double          a, b;
    Crv    = BRep_Tool::Curve(TopoDS::Edge(Sh), aLoc, a, b);
    OffCrv = new Geom_OffsetCurve(Crv, Offset, NrmDir);
    BRepBuilderAPI_MakeEdge ME(OffCrv, start->StartParameter(), start->EndParameter());
    if (!ME.IsDone())
    {

      Message_Msg Msg1005("IGES_1005");
      SendFail(start, Msg1005);

      return res;
    }
    TopoDS_Edge anEdge = ME.Edge();
    anEdge.Move(aLoc);
    res = anEdge;
  }

  else if (Sh.ShapeType() == TopAbs_WIRE)
  {
    occ::handle<ShapeExtend_WireData> sewd   = new ShapeExtend_WireData;
    TopoDS_Wire                       aWire  = TopoDS::Wire(Sh);
    bool                              begin  = true;
    double                            length = 0.0;
    double                            staPar = start->StartParameter();
    double                            endPar = start->EndParameter();

    for (TopoDS_Iterator Iter(aWire); Iter.More(); Iter.Next())
    {
      TopoDS_Edge     anEdge = TopoDS::Edge(Iter.Value());
      TopLoc_Location aLoc;
      double          first, last;
      Crv = BRep_Tool::Curve(anEdge, aLoc, first, last);
      if ((length + last - first) <= staPar)
        continue;
      if (length >= endPar)
      {
        if (begin)
        {
          Message_Msg Msg1105("IGES_1105");
          SendFail(start, Msg1105);

          return res;
        }
        break;
      }
      OffCrv = new Geom_OffsetCurve(Crv, Offset, NrmDir);
      BRepBuilderAPI_MakeEdge ME(OffCrv, staPar - length, endPar - length);

      if (!ME.IsDone())
      {
        Message_Msg Msg1005("IGES_1005");
        SendFail(start, Msg1005);

        return res;
      }
      TopoDS_Edge anotherEdge = ME.Edge();
      anotherEdge.Move(aLoc);
      begin = false;
      length += last - first;
      sewd->Add(anotherEdge);
    }
    occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
    sfw->Load(sewd);

    sfw->FixConnected();
    res = sfw->Wire();
  }

  if (start->HasTransf())
  {
    gp_Trsf T;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               start->CompoundLocation(),
                                               T,
                                               GetUnitFactor()))
    {
      TopLoc_Location L(T);
      res.Move(L);
    }
    else
    {
      Message_Msg Msg1035("IGES_1035");
      SendWarning(start, Msg1035);
    }
  }
  SetShapeResult(start, res);
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::Transfer2dOffsetCurve(
  const occ::handle<IGESGeom_OffsetCurve>& start,
  const TopoDS_Face&                       face,
  const gp_Trsf2d&                         trans,
  const double                             uFact)

{
  TopoDS_Shape res;
  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }

  if (start->OffsetType() != 1)
  {
    Message_Msg Msg1100("IGES_1100");
    SendFail(start, Msg1100);
  }

  double                           Offset  = start->FirstOffsetDistance();
  occ::handle<IGESData_IGESEntity> BaseCrv = start->BaseCurve();
  occ::handle<Geom2d_Curve>        Crv;
  occ::handle<Geom2d_OffsetCurve>  OffCrv;

  if (IGESToBRep::IsTopoCurve(BaseCrv))
  {
    IGESToBRep_TopoCurve TC(*this);
    TC.SetModeTransfer(false);
    TopoDS_Shape Sh = TC.Transfer2dTopoCurve(BaseCrv, face, trans, uFact);
    if (Sh.IsNull() || ((Sh.ShapeType() != TopAbs_EDGE) && (Sh.ShapeType() != TopAbs_WIRE)))
    {
      Message_Msg                           Msg1156("IGES_1156");
      occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(BaseCrv);
      Msg1156.Arg("2D basis curve");
      Msg1156.Arg(label);
      SendFail(start, Msg1156);
      return res;
    }

    if (Sh.ShapeType() == TopAbs_EDGE)
    {
      occ::handle<Geom_Surface> Srf;
      TopLoc_Location           aLoc;
      double                    a, b;
      BRep_Tool::CurveOnSurface(TopoDS::Edge(Sh), Crv, Srf, aLoc, a, b);
      OffCrv = new Geom2d_OffsetCurve(Crv, Offset * uFact);
      TopoDS_Edge anEdge;
      ShapeBuild_Edge().MakeEdge(anEdge,
                                 OffCrv,
                                 face,
                                 start->StartParameter(),
                                 start->EndParameter());
      if (anEdge.IsNull())
      {
        Message_Msg Msg1005("IGES_1005");
        SendFail(start, Msg1005);
        return res;
      }
      res = anEdge;
    }
    else if (Sh.ShapeType() == TopAbs_WIRE)
    {
      TopoDS_Wire                       aWire = TopoDS::Wire(Sh);
      occ::handle<ShapeExtend_WireData> sewd  = new ShapeExtend_WireData;
      for (TopoDS_Iterator Iter(aWire); Iter.More(); Iter.Next())
      {
        TopoDS_Edge               anEdge = TopoDS::Edge(Iter.Value());
        occ::handle<Geom_Surface> Srf;
        TopLoc_Location           aLoc;
        double                    a, b;
        BRep_Tool::CurveOnSurface(anEdge, Crv, Srf, aLoc, a, b);
        OffCrv = new Geom2d_OffsetCurve(Crv, Offset * uFact);
        TopoDS_Edge anotherEdge;
        ShapeBuild_Edge().MakeEdge(anotherEdge,
                                   OffCrv,
                                   face,
                                   start->StartParameter(),
                                   start->EndParameter());
        if (anotherEdge.IsNull())
        {
          Message_Msg Msg1005("IGES_1005");
          SendFail(start, Msg1005);
          return res;
        }
        sewd->Add(anotherEdge);
      }
      occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
      sfw->Load(sewd);

      sfw->FixConnected();
      res = sfw->Wire();
    }
  }
  SetShapeResult(start, res);
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferTopoCurve(const occ::handle<IGESData_IGESEntity>& start)
{
  TopoDS_Shape res;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }

  if (IGESToBRep::IsBasicCurve(start))
  {
    res = TransferTopoBasicCurve(start);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_CompositeCurve)))
  {
    DeclareAndCast(IGESGeom_CompositeCurve, st102, start);
    res = TransferCompositeCurve(st102);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_CurveOnSurface)))
  {
    DeclareAndCast(IGESGeom_CurveOnSurface, st142, start);
    res = TransferCurveOnSurface(st142);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_Boundary)))
  {
    DeclareAndCast(IGESGeom_Boundary, st141, start);
    res = TransferBoundary(st141);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_Point)))
  {
    DeclareAndCast(IGESGeom_Point, st116, start);
    res = TransferPoint(st116);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_OffsetCurve)))
  {
    DeclareAndCast(IGESGeom_OffsetCurve, st130, start);
    res = TransferOffsetCurve(st130);
  }
  else
  {
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::Transfer2dTopoCurve(
  const occ::handle<IGESData_IGESEntity>& start,
  const TopoDS_Face&                      face,
  const gp_Trsf2d&                        trans,
  const double                            uFact)
{
  TopoDS_Shape res;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }

  if (IGESToBRep::IsBasicCurve(start))
    res = Transfer2dTopoBasicCurve(start, face, trans, uFact);

  else if (start->IsKind(STANDARD_TYPE(IGESGeom_CompositeCurve)))
  {
    DeclareAndCast(IGESGeom_CompositeCurve, st102, start);
    res = Transfer2dCompositeCurve(st102, face, trans, uFact);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_Point)))
  {
    DeclareAndCast(IGESGeom_Point, st116, start);
    res = Transfer2dPoint(st116);
  }
  else if (start->IsKind(STANDARD_TYPE(IGESGeom_OffsetCurve)))
  {
    DeclareAndCast(IGESGeom_OffsetCurve, st130, start);
    res = Transfer2dOffsetCurve(st130, face, trans, uFact);
  }
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferTopoBasicCurve(
  const occ::handle<IGESData_IGESEntity>& start)
{
  TopoDS_Shape myshape;
  TopoDS_Edge  myedge;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return myshape;
  }

  IGESToBRep_BasicCurve BC(*this);

  BC.SetModeTransfer(false);
  occ::handle<Geom_Curve> C = BC.TransferBasicCurve(start);

  if (C.IsNull())
  {

    return myshape;
  }

  TheCurves.Clear();
  if ((C->IsKind(STANDARD_TYPE(Geom_BSplineCurve))) && GetModeApprox())
  {
    occ::handle<Geom_BSplineCurve> BSplineC = occ::down_cast<Geom_BSplineCurve>(C);
    if (BSplineC->Degree() == 1)
      ApproxBSplineCurve(BSplineC);
    else
      TheCurves.Append(C);
  }
  else
    TheCurves.Append(C);

  int nbcurves = NbCurves();
  if (nbcurves == 0)
  {
    Message_Msg                           Msg1156("IGES_1156");
    occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(start);
    Msg1156.Arg("Geom_Curve");
    Msg1156.Arg(label);
    SendFail(start, Msg1156);
    return myshape;
  }

  occ::handle<ShapeExtend_WireData> sewd = new ShapeExtend_WireData;

  for (int icurve = 1; icurve <= nbcurves; icurve++)
  {
    occ::handle<Geom_Curve> mycurve = Curve(icurve);
    if ((mycurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve))) && (mycurve->Continuity() < GeomAbs_C1)
        && GetContinuity() >= 1)
    {
      occ::handle<Geom_BSplineCurve> BSplineC = occ::down_cast<Geom_BSplineCurve>(mycurve);

      occ::handle<NCollection_HSequence<occ::handle<Geom_BoundedCurve>>> seqBS;
      ShapeAlgo::AlgoContainer()->C0BSplineToSequenceOfC1BSplineCurve(BSplineC, seqBS);
      int NbC0 = seqBS->Length();
      for (int i = 1; i <= NbC0; i++)
      {
        BRepBuilderAPI_MakeEdge ME(seqBS->Value(i));
        if (!ME.IsDone())
        {
          Message_Msg Msg1005("IGES_1005");
          SendFail(start, Msg1005);

          return myshape;
        }
        myedge = ME.Edge();
        sewd->Add(myedge);
      }
    }
    else
    {
      double a = mycurve->FirstParameter(), b = mycurve->LastParameter();
      if (mycurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
      {
        occ::handle<Geom_TrimmedCurve> tmp = occ::down_cast<Geom_TrimmedCurve>(mycurve);
        mycurve                            = tmp->BasisCurve();
      }
      BRepBuilderAPI_MakeEdge ME(mycurve, a, b);
      if (!ME.IsDone() || (Precision::IsInfinite(a) || Precision::IsInfinite(b)))
      {
        Message_Msg Msg1005("IGES_1005");
        SendFail(start, Msg1005);

        return myshape;
      }
      myedge = ME.Edge();
      sewd->Add(myedge);
    }
  }

  occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
  sfw->Load(sewd);

  sfw->FixConnected();
  myshape = sewd->Wire();

  bool bIsNeedTransf = start->IsKind(STANDARD_TYPE(IGESGeom_SplineCurve));
  if (start->HasTransf() && bIsNeedTransf)
  {
    gp_Trsf T;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(),
                                               start->CompoundLocation(),
                                               T,
                                               GetUnitFactor()))
    {
      TopLoc_Location L(T);
      myshape.Move(L);
    }
    else
    {
      Message_Msg Msg1035("IGES_1035");
      SendWarning(start, Msg1035);
    }
  }

  if (sewd->NbEdges() != 1)
  {

    Message_Msg Msg1120("IGES_1120");
    SendWarning(start, Msg1120);

    return myshape;
  }
  else
    myedge = TopoDS::Edge(TopoDS_Iterator(myshape).Value());

  if (start->IsKind(STANDARD_TYPE(IGESGeom_CircularArc))
      && occ::down_cast<IGESGeom_CircularArc>(start)->IsClosed())
    TheBadCase = true;
  SetShapeResult(start, myshape);
  return myedge;
}

TopoDS_Shape IGESToBRep_TopoCurve::Transfer2dTopoBasicCurve(
  const occ::handle<IGESData_IGESEntity>& start,
  const TopoDS_Face&                      face,
  const gp_Trsf2d&                        trans,
  const double                            uFact)
{
  TopoDS_Edge  edge, myedge;
  TopoDS_Shape myshape;

  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return edge;
  }

  TopLoc_Location           L;
  occ::handle<Geom_Surface> mysurf = BRep_Tool::Surface(face, L);

  IGESToBRep_BasicCurve BC(*this);
  BC.SetModeTransfer(false);

  occ::handle<Geom2d_Curve> C2d = BC.Transfer2dBasicCurve(start);
  if (C2d.IsNull())
  {

    return edge;
  }

  TheCurves2d.Clear();
  if ((C2d->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve))) && GetModeApprox())
  {
    occ::handle<Geom2d_BSplineCurve> BSplineC2d = occ::down_cast<Geom2d_BSplineCurve>(C2d);
    if (BSplineC2d->Degree() == 1)
      Approx2dBSplineCurve(BSplineC2d);
    else
      TheCurves2d.Append(C2d);
  }
  else
    TheCurves2d.Append(C2d);

  int nbcurves = NbCurves2d();
  if (nbcurves == 0)
  {
    Message_Msg                           Msg1156("IGES_1156");
    occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(start);
    Msg1156.Arg("Geom2d_Curve");
    Msg1156.Arg(label);
    SendFail(start, Msg1156);

    return myshape;
  }

  occ::handle<ShapeExtend_WireData> sewd = new ShapeExtend_WireData;

  for (int icurve = 1; icurve <= nbcurves; icurve++)
  {
    occ::handle<Geom2d_Curve> mycurve2d = Curve2d(icurve);

    if (trans.Form() != gp_Identity)
      mycurve2d->Transform(trans);

    gp_Trsf2d ntrsf;
    if (mysurf->IsKind(STANDARD_TYPE(Geom_Plane)))
      ntrsf.SetScale(gp_Pnt2d(0, 0), GetUnitFactor());

    double          a = mycurve2d->FirstParameter(), b = mycurve2d->LastParameter();
    ShapeBuild_Edge sbe;
    mycurve2d = sbe.TransformPCurve(mycurve2d, ntrsf, uFact, a, b);

    if ((mycurve2d->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
        && (mycurve2d->Continuity() < GeomAbs_C1) && GetContinuity() >= 1)
    {
      occ::handle<Geom2d_BSplineCurve> BSplineC2d = occ::down_cast<Geom2d_BSplineCurve>(mycurve2d);

      occ::handle<NCollection_HSequence<occ::handle<Geom2d_BoundedCurve>>> seqBS;
      ShapeAlgo::AlgoContainer()->C0BSplineToSequenceOfC1BSplineCurve(BSplineC2d, seqBS);
      int NbC0 = seqBS->Length();
      for (int i = 1; i <= NbC0; i++)
      {
        ShapeBuild_Edge().MakeEdge(myedge, seqBS->Value(i), face);

        if (myedge.IsNull())
        {
          Message_Msg Msg1005("IGES_1005");
          SendFail(start, Msg1005);

          return myshape;
        }

        sewd->Add(myedge);
      }
    }
    else
    {
      if (mycurve2d->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)))
      {
        occ::handle<Geom2d_TrimmedCurve> tmp = occ::down_cast<Geom2d_TrimmedCurve>(mycurve2d);
        mycurve2d                            = tmp->BasisCurve();
      }
      ShapeBuild_Edge().MakeEdge(myedge, mycurve2d, face, a, b);

      if (myedge.IsNull())
      {
        Message_Msg Msg1005("IGES_1005");
        SendFail(start, Msg1005);
        return myshape;
      }

      sewd->Add(myedge);
    }
  }

  occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
  sfw->Load(sewd);

  sfw->FixConnected();
  myshape = sewd->Wire();

  if (sewd->NbEdges() != 1)
  {

    Message_Msg Msg1120("IGES_1120");
    SendWarning(start, Msg1120);

    return myshape;
  }

  if (start->IsKind(STANDARD_TYPE(IGESGeom_CircularArc))
      && occ::down_cast<IGESGeom_CircularArc>(start)->IsClosed())
    TheBadCase = true;
  return myedge;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferBoundary(const occ::handle<IGESGeom_Boundary>& start)
{
  TopoDS_Shape res;
  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);

    return res;
  }

  if (start->BoundaryType() == 0)
  {
    Message_Msg Msg1125("IGES_1125");
    SendFail(start, Msg1125);

    return res;
  }

  occ::handle<IGESData_IGESEntity> igesSurface = start->Surface();
  if (igesSurface.IsNull() || !IGESToBRep::IsTopoSurface(igesSurface))
  {
    Message_Msg Msg124("XSTEP_124");
    SendFail(start, Msg124);

    return res;
  }

  TopoDS_Face            face;
  TopAbs_ShapeEnum       shapeEnum;
  IGESToBRep_TopoSurface TS(*this);
  gp_Trsf2d              trans;
  double                 uFact;
  TopoDS_Shape           myshape = TS.ParamSurface(igesSurface, trans, uFact);

  if (!myshape.IsNull())
  {
    shapeEnum = myshape.ShapeType();
    switch (shapeEnum)
    {
      case TopAbs_FACE:
      {
        face = TopoDS::Face(myshape);
        break;
      }
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
          Message_Msg Msg1061("IGES_1061");
          SendFail(start, Msg1061);

          return res;
        }
      }
      break;
      default:
      {
        Message_Msg                           Msg1156("IGES_1156");
        occ::handle<TCollection_HAsciiString> label = GetModel()->StringLabel(igesSurface);
        Msg1156.Arg("basic surface");
        Msg1156.Arg(label);
        SendFail(start, Msg1156);

        return res;
      }
    }
  }

  face.EmptyCopy();
  res = TransferBoundaryOnFace(face, start, trans, uFact);
  return res;
}

TopoDS_Shape IGESToBRep_TopoCurve::TransferBoundaryOnFace(
  TopoDS_Face&                          face,
  const occ::handle<IGESGeom_Boundary>& start,
  const gp_Trsf2d&                      trans,
  const double                          uFact)
{
  TopoDS_Shape res;
  if (start.IsNull())
  {
    Message_Msg Msg1005("IGES_1005");
    SendFail(start, Msg1005);
    return res;
  }

  bool okCurve = true, okCurve3d = true, okCurve2d = true;
  int  filepreference = 0;
  if (start->PreferenceType() == 2)
    filepreference = 2;
  else if (start->PreferenceType() == 1)
    filepreference = 3;
  bool Result = true;

  occ::handle<IGESToBRep_IGESBoundary> IB =
    IGESToBRep::AlgoContainer()->ToolContainer()->IGESBoundary();
  IB->Init(*this, start, face, trans, uFact, filepreference);
  for (int i = 1; i <= start->NbModelSpaceCurves(); i++)
  {
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Curves2d;
    if (start->NbParameterCurves(i) == 0 && start->BoundaryType() == 1)
    {
      Message_Msg Msg1135("IGES_1135");
      Msg1135.Arg(2);
      Msg1135.Arg(3);
      SendWarning(start, Msg1135);
    }
    else
      Curves2d = start->ParameterCurves(i);
    Result = Result
             & IB->Transfer(okCurve,
                            okCurve3d,
                            okCurve2d,
                            start->ModelSpaceCurve(i),
                            start->Sense(i) == 2,
                            Curves2d,
                            i);
  }
  IB->Check(Result, true, okCurve3d, okCurve2d);
  occ::handle<ShapeExtend_WireData> sewd = IB->WireData();
  if (sewd->NbEdges() == 0)
  {
    Message_Msg Msg1095("IGES_1095");
    SendFail(start, Msg1095);
    return res;
  }

  TopoDS_Wire mywire = sewd->Wire();

  if (start->HasTransf())
  {
    gp_Trsf T;
    SetEpsilon(1.E-04);
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(), start->CompoundLocation(), T))
    {
      TopLoc_Location L(T);
      mywire.Move(L);
    }
    else
    {
      Message_Msg Msg1035("IGES_1035");
      SendWarning(start, Msg1035);
    }
  }
  BRep_Builder B;
  B.Add(face, mywire);
  SetShapeResult(start, mywire);
  return mywire;
}

void IGESToBRep_TopoCurve::ApproxBSplineCurve(const occ::handle<Geom_BSplineCurve>& start)

{
  ShapeAlgo::AlgoContainer()->ApproxBSplineCurve(start, TheCurves);
}

int IGESToBRep_TopoCurve::NbCurves() const
{
  return TheCurves.Length();
}

occ::handle<Geom_Curve> IGESToBRep_TopoCurve::Curve(const int num) const
{
  occ::handle<Geom_Curve> res;
  if (num > 0 && num <= TheCurves.Length())
    res = TheCurves.Value(num);
  return res;
}

void IGESToBRep_TopoCurve::Approx2dBSplineCurve(const occ::handle<Geom2d_BSplineCurve>& start)

{
  ShapeAlgo::AlgoContainer()->ApproxBSplineCurve(start, TheCurves2d);
}

int IGESToBRep_TopoCurve::NbCurves2d() const
{
  return TheCurves2d.Length();
}

occ::handle<Geom2d_Curve> IGESToBRep_TopoCurve::Curve2d(const int num) const
{
  occ::handle<Geom2d_Curve> res;
  if (num > 0 && num <= TheCurves2d.Length())
    res = TheCurves2d.Value(num);
  return res;
}

void IGESToBRep_TopoCurve::SetBadCase(const bool value)
{
  TheBadCase = value;
}

bool IGESToBRep_TopoCurve::BadCase() const
{
  return TheBadCase;
}
