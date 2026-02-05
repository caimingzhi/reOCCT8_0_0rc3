#include <TNaming_CopyShape.hpp>
#include <TNaming_TranslateTool.hpp>
#include <TopLoc_Datum3D.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

//=======================================================================
// function : CopyTool
// purpose  : Tool to copy a set of shape(s), using the aMap
//=======================================================================
void TNaming_CopyShape::CopyTool(const TopoDS_Shape& aShape,
                                 NCollection_IndexedDataMap<occ::handle<Standard_Transient>,
                                                            occ::handle<Standard_Transient>>& aMap,
                                 TopoDS_Shape& aResult)
{

  occ::handle<TNaming_TranslateTool> TrTool = new TNaming_TranslateTool();
  TNaming_CopyShape::Translate(aShape, aMap, aResult, TrTool);
}

//=================================================================================================

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
    // get the translated TShape
    occ::handle<TopoDS_TShape> TS =
      *((occ::handle<TopoDS_TShape>*)&aMap.FindFromKey(aShape.TShape()));
    aResult.TShape(TS);
  }
  else
  {

    // create if not translated and update

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

    // bind and copy the sub-elements
    aMap.Add(aShape.TShape(), aResult.TShape()); // TShapes
    TopoDS_Shape S = aShape;
    S.Orientation(TopAbs_FORWARD);
    S.Location(TopLoc_Location()); // Identity
    // copy current Shape
    TopoDS_Iterator itr(S, false);
    bool            wasFree = aResult.Free();
    aResult.Free(true);
    // translate <sub-shapes>
    for (; itr.More(); itr.Next())
    {
      TopoDS_Shape subShape;
      TNaming_CopyShape::Translate(itr.Value(), aMap, subShape, TrTool);
      TrTool->Add(aResult, subShape); // add subshapes
    }

    aResult.Free(wasFree);
  }

  aResult.Orientation(aShape.Orientation());
  aResult.Location(TNaming_CopyShape::Translate(aShape.Location(), aMap), false);
  TrTool->UpdateShape(aShape, aResult);
  // #ifdef OCCT_DEBUG
  //     if(fShar) {
  //       std::cout << "=== Shareable shape ===" << std::endl;
  //       std::cout << "aShape Type = " <<(aShape.TShape())->DynamicType() << std::endl;
  //       if(aShape.Orientation() == aResult.Orientation())
  // 	std::cout<<"\tSource and result shapes have the same Orientation"<< std::endl;
  //       if((aShape.Location().IsEqual(aResult.Location())))
  // 	std::cout <<"\tSource and result shapes have the same Locations" << std::endl;
  //       if((aShape.IsSame(aResult)))
  // 	 std::cout <<"\tShapes arew the same (i.e. the same TShape and the same Locations)" <<
  // std::endl;
  //     }
  // #endif
}

//=======================================================================
// static TranslateDatum3D
//=======================================================================
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

//=================================================================================================

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
