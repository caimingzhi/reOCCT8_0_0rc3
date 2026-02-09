#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TNaming_PtrRefShape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_AttributeDelta;
class TDF_DeltaOnAddition;
class TDF_DeltaOnRemoval;
class TDF_RelocationTable;
class TDF_DataSet;

class TNaming_UsedShapes : public TDF_Attribute
{

public:
  Standard_EXPORT void Destroy();

  ~TNaming_UsedShapes() override { Destroy(); }

  NCollection_DataMap<TopoDS_Shape, TNaming_PtrRefShape, TopTools_ShapeMapHasher>& Map();

  const Standard_GUID& ID() const override;

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  Standard_EXPORT void BeforeRemoval() override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  Standard_EXPORT occ::handle<TDF_DeltaOnAddition> DeltaOnAddition() const override;

  Standard_EXPORT occ::handle<TDF_DeltaOnRemoval> DeltaOnRemoval() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocTationable) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  friend class TNaming_Builder;

  DEFINE_STANDARD_RTTIEXT(TNaming_UsedShapes, TDF_Attribute)

private:
  Standard_EXPORT TNaming_UsedShapes();

  NCollection_DataMap<TopoDS_Shape, TNaming_PtrRefShape, TopTools_ShapeMapHasher> myMap;
};

inline NCollection_DataMap<TopoDS_Shape, TNaming_PtrRefShape, TopTools_ShapeMapHasher>&
  TNaming_UsedShapes::Map()
{
  return myMap;
}

inline const Standard_GUID& TNaming_UsedShapes::ID() const
{
  return GetID();
}
