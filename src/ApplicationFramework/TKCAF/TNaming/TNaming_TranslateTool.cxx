#include <BRep_Builder.hpp>
#include <BRep_Curve3D.hpp>
#include <BRep_CurveOn2Surfaces.hpp>
#include <BRep_CurveOnClosedSurface.hpp>
#include <BRep_CurveOnSurface.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_PointRepresentation.hpp>
#include <NCollection_List.hpp>
#include <BRep_PointOnCurve.hpp>
#include <BRep_PointOnCurveOnSurface.hpp>
#include <BRep_PointOnSurface.hpp>
#include <BRep_Polygon3D.hpp>
#include <BRep_PolygonOnClosedSurface.hpp>
#include <BRep_PolygonOnClosedTriangulation.hpp>
#include <BRep_PolygonOnSurface.hpp>
#include <BRep_PolygonOnTriangulation.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_TFace.hpp>
#include <BRep_TVertex.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_Type.hpp>
#include <TNaming_CopyShape.hpp>
#include <TNaming_TranslateTool.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TNaming_TranslateTool, Standard_Transient)

void TNaming_TranslateTool::Add(TopoDS_Shape& S1, const TopoDS_Shape& S2) const
{
  BRep_Builder B;
  B.Add(S1, S2);
}

void TNaming_TranslateTool::MakeVertex(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeVertex(TopoDS::Vertex(S));
}

void TNaming_TranslateTool::MakeEdge(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeEdge(TopoDS::Edge(S));
}

void TNaming_TranslateTool::MakeWire(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeWire(TopoDS::Wire(S));
}

void TNaming_TranslateTool::MakeFace(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeFace(TopoDS::Face(S));
}

void TNaming_TranslateTool::MakeShell(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeShell(TopoDS::Shell(S));
}

void TNaming_TranslateTool::MakeSolid(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(S));
}

void TNaming_TranslateTool::MakeCompSolid(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeCompSolid(TopoDS::CompSolid(S));
}

void TNaming_TranslateTool::MakeCompound(TopoDS_Shape& S) const
{
  BRep_Builder B;
  B.MakeCompound(TopoDS::Compound(S));
}

void TNaming_TranslateTool::UpdateVertex(
  const TopoDS_Shape& S1,
  TopoDS_Shape&       S2,
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
    aMap) const
{
  const occ::handle<BRep_TVertex>& TTV1 = *((occ::handle<BRep_TVertex>*)&(S1.TShape()));
  const occ::handle<BRep_TVertex>& TTV2 = *((occ::handle<BRep_TVertex>*)&(S2.TShape()));

  TTV2->Pnt(TTV1->Pnt());

  TTV2->Tolerance(TTV1->Tolerance());

  NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TTV1->Points());

  NCollection_List<occ::handle<BRep_PointRepresentation>>& lpr = TTV2->ChangePoints();
  lpr.Clear();

  while (itpr.More())
  {

    const occ::handle<BRep_PointRepresentation>& PR1 = itpr.Value();
    occ::handle<BRep_PointRepresentation>        PR2;

    if (PR1->IsPointOnCurve())
    {
      occ::handle<BRep_PointOnCurve> OC =
        new BRep_PointOnCurve(PR1->Parameter(),
                              PR1->Curve(),
                              TNaming_CopyShape::Translate(PR1->Location(), aMap));
      PR2 = OC;
    }

    else if (PR1->IsPointOnCurveOnSurface())
    {

      occ::handle<BRep_PointOnCurveOnSurface> OCS =
        new BRep_PointOnCurveOnSurface(PR1->Parameter(),
                                       PR1->PCurve(),
                                       PR1->Surface(),
                                       TNaming_CopyShape::Translate(PR1->Location(), aMap));
      PR2 = OCS;
    }

    else if (PR1->IsPointOnSurface())
    {

      occ::handle<BRep_PointOnSurface> OS =
        new BRep_PointOnSurface(PR1->Parameter(),
                                PR1->Parameter2(),
                                PR1->Surface(),
                                TNaming_CopyShape::Translate(PR1->Location(), aMap));
      PR2 = OS;
    }

    lpr.Append(PR2);
    itpr.Next();
  }

  UpdateShape(S1, S2);
}

void TNaming_TranslateTool::UpdateEdge(
  const TopoDS_Shape& S1,
  TopoDS_Shape&       S2,
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
    aMap) const
{
  const occ::handle<BRep_TEdge>& TTE1 = *((occ::handle<BRep_TEdge>*)&(S1.TShape()));
  const occ::handle<BRep_TEdge>& TTE2 = *((occ::handle<BRep_TEdge>*)&(S2.TShape()));

  TTE2->Tolerance(TTE1->Tolerance());

  TTE2->SameParameter(TTE1->SameParameter());

  TTE2->SameRange(TTE1->SameRange());

  TTE2->Degenerated(TTE1->Degenerated());

  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TTE1->Curves());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>&          lcr = TTE2->ChangeCurves();
  lcr.Clear();

  occ::handle<BRep_GCurve> GC;
  double                   f, l;
  while (itcr.More())
  {

    const occ::handle<BRep_CurveRepresentation>& CR = itcr.Value();
    occ::handle<BRep_CurveRepresentation>        CR2;

    GC = occ::down_cast<BRep_GCurve>(CR);
    if (!GC.IsNull())
    {
      GC->Range(f, l);

      if (CR->IsCurve3D())
      {

        CR2 = (occ::down_cast<BRep_Curve3D>(GC))->Copy();
      }

      else if (CR->IsCurveOnSurface())
      {

        if (!CR->IsCurveOnClosedSurface())
        {

          CR2 = (occ::down_cast<BRep_CurveOnSurface>(GC))->Copy();
        }

        else
        {

          CR2 = (occ::down_cast<BRep_CurveOnClosedSurface>(GC))->Copy();
        }
      }

      (occ::down_cast<BRep_GCurve>(CR2))->SetRange(f, l);
    }

    else if (CR->IsRegularity())
    {

      CR2                = (occ::down_cast<BRep_CurveOn2Surfaces>(CR))->Copy();
      TopLoc_Location L2 = TNaming_CopyShape::Translate(CR->Location2(), aMap);
      CR2->Location(L2);
    }

    else if (CR->IsPolygon3D())
    {

      CR2 = (occ::down_cast<BRep_Polygon3D>(CR))->Copy();
    }

    else if (CR->IsPolygonOnSurface())
    {

      if (CR->IsPolygonOnClosedSurface())
      {

        CR2 = (occ::down_cast<BRep_PolygonOnClosedSurface>(CR))->Copy();
      }

      else
      {

        CR2 = (occ::down_cast<BRep_PolygonOnSurface>(CR))->Copy();
      }
    }

    else if (CR->IsPolygonOnTriangulation())
    {

      if (CR->IsPolygonOnClosedTriangulation())
      {

        CR2 = (occ::down_cast<BRep_PolygonOnClosedTriangulation>(CR))->Copy();
      }

      else
      {

        CR2 = (occ::down_cast<BRep_PolygonOnTriangulation>(CR))->Copy();
      }
    }

    else
    {

      itcr.Next();
      continue;
    }

    TopLoc_Location L = TNaming_CopyShape::Translate(CR->Location(), aMap);
    CR2->Location(L);

    Standard_NullObject_Raise_if(CR2.IsNull(), "Null CurveRepresentation");

    lcr.Append(CR2);
    itcr.Next();
  }

  UpdateShape(S1, S2);
}

void TNaming_TranslateTool::UpdateFace(
  const TopoDS_Shape& S1,
  TopoDS_Shape&       S2,
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
    aMap) const
{
  const occ::handle<BRep_TFace>& TTF1 = *((occ::handle<BRep_TFace>*)&(S1.TShape()));
  const occ::handle<BRep_TFace>& TTF2 = *((occ::handle<BRep_TFace>*)&(S2.TShape()));

  TTF2->NaturalRestriction(TTF1->NaturalRestriction());

  TTF2->Tolerance(TTF1->Tolerance());

  TTF2->Location(TNaming_CopyShape::Translate(TTF1->Location(), aMap));

  TTF2->Surface(TTF1->Surface());

  TTF2->Triangulation(TTF1->Triangulation());

  UpdateShape(S1, S2);
}

void TNaming_TranslateTool::UpdateShape(const TopoDS_Shape& S1, TopoDS_Shape& S2) const
{

  S2.TShape()->Free(S1.TShape()->Free());
  S2.TShape()->Modified(S1.TShape()->Modified());
  S2.TShape()->Checked(S1.TShape()->Checked());
  S2.TShape()->Orientable(S1.TShape()->Orientable());
  S2.TShape()->Closed(S1.TShape()->Closed());
  S2.TShape()->Infinite(S1.TShape()->Infinite());
  S2.TShape()->Convex(S1.TShape()->Convex());
}
