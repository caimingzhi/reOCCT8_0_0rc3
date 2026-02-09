

#include <XCAFDoc_ShapeMapTool.hpp>

#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFDoc_ShapeMapTool, TDF_Attribute)

#define AUTONAMING

const Standard_GUID& XCAFDoc_ShapeMapTool::GetID()
{
  static Standard_GUID ShapeToolID("3B913F4D-4A82-44ef-A0BF-9E01E9FF317A");
  return ShapeToolID;
}

occ::handle<XCAFDoc_ShapeMapTool> XCAFDoc_ShapeMapTool::Set(const TDF_Label& L)
{
  occ::handle<XCAFDoc_ShapeMapTool> A;
  if (!L.FindAttribute(XCAFDoc_ShapeMapTool::GetID(), A))
  {
    A = new XCAFDoc_ShapeMapTool();
    L.AddAttribute(A);
  }
  return A;
}

const Standard_GUID& XCAFDoc_ShapeMapTool::ID() const
{
  return GetID();
}

void XCAFDoc_ShapeMapTool::Restore(const occ::handle<TDF_Attribute>&) {}

occ::handle<TDF_Attribute> XCAFDoc_ShapeMapTool::NewEmpty() const
{
  return new XCAFDoc_ShapeMapTool;
}

void XCAFDoc_ShapeMapTool::Paste(const occ::handle<TDF_Attribute>&,
                                 const occ::handle<TDF_RelocationTable>&) const
{
}

XCAFDoc_ShapeMapTool::XCAFDoc_ShapeMapTool() = default;

bool XCAFDoc_ShapeMapTool::IsSubShape(const TopoDS_Shape& sub) const
{
  return myMap.Contains(sub);
}

static void AddSubShape(const TopoDS_Shape&                                            S,
                        NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& myMap)
{
  myMap.Add(S);
  for (TopoDS_Iterator it(S); it.More(); it.Next())
    AddSubShape(it.Value(), myMap);
}

void XCAFDoc_ShapeMapTool::SetShape(const TopoDS_Shape& S)
{
  myMap.Clear();
  for (TopoDS_Iterator it(S); it.More(); it.Next())
    AddSubShape(it.Value(), myMap);
}

const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& XCAFDoc_ShapeMapTool::GetMap()
  const
{
  return myMap;
}

void XCAFDoc_ShapeMapTool::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  for (NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aMapIt(myMap);
       aMapIt.More();
       aMapIt.Next())
  {
    const occ::handle<TopoDS_TShape>& aShape = aMapIt.Value().TShape();
    OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, aShape)
  }
}
