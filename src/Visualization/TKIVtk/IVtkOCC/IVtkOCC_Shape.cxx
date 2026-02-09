#include <IVtkOCC_Shape.hpp>

#include <TopExp.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IVtkOCC_Shape, IVtk_IShape)

IVtkOCC_Shape::IVtkOCC_Shape(const TopoDS_Shape&              theShape,
                             const occ::handle<Prs3d_Drawer>& theDrawerLink)
    : myTopoDSShape(theShape),
      myOCCTDrawer(new Prs3d_Drawer())
{
  if (!theDrawerLink.IsNull())
  {
    myOCCTDrawer->SetLink(theDrawerLink);
  }
  else
  {

    myOCCTDrawer->SetDeviationCoefficient(0.0001);
    myOCCTDrawer->SetupOwnDefaults();
  }
  buildSubShapeIdMap();
}

IVtkOCC_Shape::~IVtkOCC_Shape() = default;

IVtk_IdType IVtkOCC_Shape::GetSubShapeId(const TopoDS_Shape& theSubShape) const
{
  int anIndex = theSubShape.IsSame(myTopoDSShape) ? -1 : mySubShapeIds.FindIndex(theSubShape);
  if (anIndex == 0)
  {
    return (IVtk_IdType)-1;
  }
  return (IVtk_IdType)anIndex;
}

NCollection_List<IVtk_IdType> IVtkOCC_Shape::GetSubIds(const IVtk_IdType theId) const
{
  NCollection_List<IVtk_IdType> aRes;

  TopoDS_Shape     aShape     = mySubShapeIds.FindKey((int)theId);
  TopAbs_ShapeEnum aShapeType = aShape.ShapeType();
  if (aShapeType == TopAbs_VERTEX || aShapeType == TopAbs_EDGE || aShapeType == TopAbs_FACE)
  {

    aRes.Append(theId);
  }
  else
  {

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aSubShapes;
    if (aShape.IsSame(myTopoDSShape))
    {
      aSubShapes = mySubShapeIds;
    }
    else
    {
      TopExp::MapShapes(aShape, aSubShapes);
    }

    for (int anIt = 1; anIt <= aSubShapes.Extent(); anIt++)
    {
      aShape     = aSubShapes.FindKey(anIt);
      aShapeType = aShape.ShapeType();
      if (aShapeType == TopAbs_VERTEX || aShapeType == TopAbs_EDGE || aShapeType == TopAbs_FACE)
      {

        aRes.Append(mySubShapeIds.FindIndex(aShape));
      }
    }
  }

  return aRes;
}

const TopoDS_Shape& IVtkOCC_Shape::GetSubShape(const IVtk_IdType theId) const
{
  return mySubShapeIds.FindKey((int)theId);
}

void IVtkOCC_Shape::buildSubShapeIdMap()
{
  mySubShapeIds.Clear();
  TopExp::MapShapes(myTopoDSShape, mySubShapeIds);
}
