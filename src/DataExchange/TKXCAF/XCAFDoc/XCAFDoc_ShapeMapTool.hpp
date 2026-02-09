#pragma once

#include <Standard.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Boolean.hpp>
class Standard_GUID;
class TDF_Label;
class TopoDS_Shape;
class TDF_RelocationTable;

class XCAFDoc_ShapeMapTool : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_ShapeMapTool> Set(const TDF_Label& L);

  Standard_EXPORT XCAFDoc_ShapeMapTool();

  Standard_EXPORT bool IsSubShape(const TopoDS_Shape& sub) const;

  Standard_EXPORT void SetShape(const TopoDS_Shape& S);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& GetMap()
    const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_ShapeMapTool, TDF_Attribute)

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};
