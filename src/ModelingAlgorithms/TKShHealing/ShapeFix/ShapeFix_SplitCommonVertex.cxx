

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <Message_Msg.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeBuild_Edge.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeExtend.hpp>
#include <ShapeExtend_WireData.hpp>
#include <ShapeFix_SplitCommonVertex.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_SplitCommonVertex, ShapeFix_Root)

ShapeFix_SplitCommonVertex::ShapeFix_SplitCommonVertex()
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  SetPrecision(Precision::Confusion());
}

void ShapeFix_SplitCommonVertex::Init(const TopoDS_Shape& S)
{
  myShape = S;
  if (Context().IsNull())
    SetContext(new ShapeBuild_ReShape);
  myResult = myShape;
  Context()->Apply(myShape);
}

void ShapeFix_SplitCommonVertex::Perform()
{
  TopAbs_ShapeEnum st = myShape.ShapeType();
  if (st > TopAbs_FACE)
    return;
  for (TopExp_Explorer itf(myShape, TopAbs_FACE); itf.More(); itf.Next())
  {
    TopoDS_Shape tmpFace = Context()->Apply(itf.Current());
    TopoDS_Face  F       = TopoDS::Face(tmpFace);
    if (F.IsNull())
      continue;

    NCollection_Sequence<TopoDS_Shape> wires;
    for (TopoDS_Iterator itw(F, false); itw.More(); itw.Next())
    {
      if (itw.Value().ShapeType() != TopAbs_WIRE)
        continue;
      wires.Append(itw.Value());
    }
    if (wires.Length() < 2)
      continue;
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> MapVV;
    MapVV.Clear();
    for (int nw1 = 1; nw1 < wires.Length(); nw1++)
    {
      TopoDS_Wire                       w1    = TopoDS::Wire(wires.Value(nw1));
      occ::handle<ShapeExtend_WireData> sewd1 = new ShapeExtend_WireData(w1);
      for (int nw2 = nw1 + 1; nw2 <= wires.Length(); nw2++)
      {
        TopoDS_Wire                       w2    = TopoDS::Wire(wires.Value(nw2));
        occ::handle<ShapeExtend_WireData> sewd2 = new ShapeExtend_WireData(w2);

        for (TopExp_Explorer expv1(w1, TopAbs_VERTEX); expv1.More(); expv1.Next())
        {
          TopoDS_Vertex V1 = TopoDS::Vertex(expv1.Current());
          for (TopExp_Explorer expv2(w2, TopAbs_VERTEX); expv2.More(); expv2.Next())
          {
            TopoDS_Vertex V2 = TopoDS::Vertex(expv2.Current());
            if (V1 == V2)
            {

              TopoDS_Vertex Vnew;
              if (MapVV.IsBound(V2))
              {
                Vnew = TopoDS::Vertex(MapVV.Find(V2));
              }
              else
              {
                gp_Pnt       P   = BRep_Tool::Pnt(V2);
                double       tol = BRep_Tool::Tolerance(V2);
                BRep_Builder B;
                B.MakeVertex(Vnew, P, tol);
                MapVV.Bind(V2, Vnew);
              }
              ShapeBuild_Edge    sbe;
              ShapeAnalysis_Edge sae;
              for (int ne2 = 1; ne2 <= sewd2->NbEdges(); ne2++)
              {
                TopoDS_Edge   E       = sewd2->Edge(ne2);
                TopoDS_Vertex FV      = sae.FirstVertex(E);
                TopoDS_Vertex LV      = sae.LastVertex(E);
                bool          IsCoinc = false;
                if (FV == V2)
                {
                  FV      = Vnew;
                  IsCoinc = true;
                }
                if (LV == V2)
                {
                  LV      = Vnew;
                  IsCoinc = true;
                }
                if (IsCoinc)
                {
                  TopoDS_Edge NewE = sbe.CopyReplaceVertices(E, FV, LV);
                  Context()->Replace(E, NewE);
                }
              }
            }
          }
        }
      }
    }
    if (!MapVV.IsEmpty())
      SendWarning(Message_Msg("Fix.SplitCommonVertex.MSG0"));
  }

  myShape = Context()->Apply(myShape);
}

TopoDS_Shape ShapeFix_SplitCommonVertex::Shape()
{
  return myShape;
}
