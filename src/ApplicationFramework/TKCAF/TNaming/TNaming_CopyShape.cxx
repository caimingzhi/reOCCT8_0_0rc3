#include <TNaming_CopyShape.hpp>
#include <TNaming_TranslateTool.hpp>
#include <TopLoc_Datum3D.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

void TNaming_CopyShape::CopyTool(const TopoDS_Shape& aShape,
                                 NCollection_IndexedDataMap<occ::handle<Standard_Transient>,
                                                            occ::handle<Standard_Transient>>& aMap,
                                 TopoDS_Shape& aResult)
{

  occ::handle<TNaming_TranslateTool> TrTool = new TNaming_TranslateTool();
  TNaming_CopyShape::Translate(aShape, aMap, aResult, TrTool);
}

void TNaming_CopyShape::Translate(const TopoDS_Shape& aShape,
                                  NCollection_IndexedDataMap<occ::handle<Standard_Transient>,
                                                             occ::handle<Standard_Transient>>& aMap,
                                  TopoDS_Shape&                             aResult,
                                  const occ::handle<TNaming_TranslateTool>& TrTool)
{
  aResult.Nullify();

  if (aShape.IsNull())
    return;

  if (aMap.Contains(aShape.TShape()))
  {

    occ::handle<TopoDS_TShape> TS =
      *((occ::handle<TopoDS_TShape>*)&aMap.FindFromKey(aShape.TShape()));
    aResult.TShape(TS);
  }
  else
  {

    switch (aShape.ShapeType())
    {

      case TopAbs_VERTEX:
        TrTool->MakeVertex(aResult);
        TrTool->UpdateVertex(aShape, aResult, aMap);
        break;

      case TopAbs_EDGE:
        TrTool->MakeEdge(aResult);
        TrTool->UpdateEdge(aShape, aResult, aMap);
        break;

      case TopAbs_WIRE:
        TrTool->MakeWire(aResult);
        TrTool->UpdateShape(aShape, aResult);
        break;

      case TopAbs_FACE:
        TrTool->MakeFace(aResult);
        TrTool->UpdateFace(aShape, aResult, aMap);
        break;

      case TopAbs_SHELL:
        TrTool->MakeShell(aResult);
        TrTool->UpdateShape(aShape, aResult);
        break;

      case TopAbs_SOLID:
        TrTool->MakeSolid(aResult);
        TrTool->UpdateShape(aShape, aResult);
        break;

      case TopAbs_COMPSOLID:
        TrTool->MakeCompSolid(aResult);
        TrTool->UpdateShape(aShape, aResult);
        break;

      case TopAbs_COMPOUND:
        TrTool->MakeCompound(aResult);
        TrTool->UpdateShape(aShape, aResult);
        break;

      default:
        break;
    }

    aMap.Add(aShape.TShape(), aResult.TShape());
    TopoDS_Shape S = aShape;
    S.Orientation(TopAbs_FORWARD);
    S.Location(TopLoc_Location());

    TopoDS_Iterator itr(S, false);
    bool            wasFree = aResult.Free();
    aResult.Free(true);

    for (; itr.More(); itr.Next())
    {
      TopoDS_Shape subShape;
      TNaming_CopyShape::Translate(itr.Value(), aMap, subShape, TrTool);
      TrTool->Add(aResult, subShape);
    }

    aResult.Free(wasFree);
  }

  aResult.Orientation(aShape.Orientation());
  aResult.Location(TNaming_CopyShape::Translate(aShape.Location(), aMap), false);
  TrTool->UpdateShape(aShape, aResult);
}

static occ::handle<TopLoc_Datum3D> TranslateDatum3D(
  const occ::handle<TopLoc_Datum3D>& D,
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
    aMap)
{
  occ::handle<TopLoc_Datum3D> TD;
  if (aMap.Contains(D))
    TD = occ::down_cast<TopLoc_Datum3D>(aMap.FindFromKey(D));
  else
  {
    TD = new TopLoc_Datum3D(D->Transformation());
    aMap.Add(D, TD);
  }
  return TD;
}

TopLoc_Location TNaming_CopyShape::Translate(
  const TopLoc_Location& L,
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
    aMap)
{
  TopLoc_Location result;

  if (!L.IsIdentity())
  {
    result = Translate(L.NextLocation(), aMap)
             * TopLoc_Location(TranslateDatum3D(L.FirstDatum(), aMap)).Powered(L.FirstPower());
  }
  return result;
}
