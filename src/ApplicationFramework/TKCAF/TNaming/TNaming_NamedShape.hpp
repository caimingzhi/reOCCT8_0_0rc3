#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TNaming_PtrNode.hpp>
#include <TNaming_Evolution.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TopoDS_Shape;
class TDF_DeltaOnModification;
class TDF_DeltaOnRemoval;
class TDF_RelocationTable;
class TDF_DataSet;
class TDF_AttributeDelta;

class TNaming_NamedShape : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TNaming_NamedShape();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT TopoDS_Shape Get() const;

  TNaming_Evolution Evolution() const;

  int Version() const;

  void SetVersion(const int version);

  Standard_EXPORT void Clear();

  ~TNaming_NamedShape() override { Clear(); }

  const Standard_GUID& ID() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  Standard_EXPORT occ::handle<TDF_DeltaOnModification> DeltaOnModification(
    const occ::handle<TDF_Attribute>& anOldAttribute) const override;

  Standard_EXPORT void DeltaOnModification(
    const occ::handle<TDF_DeltaOnModification>& aDelta) override;

  Standard_EXPORT occ::handle<TDF_DeltaOnRemoval> DeltaOnRemoval() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocTationable) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT void BeforeRemoval() override;

  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                  const bool                             forceIt = false) override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  friend class TNaming_Builder;
  friend class TNaming_Iterator;
  friend class TNaming_NewShapeIterator;
  friend class TNaming_OldShapeIterator;

  DEFINE_STANDARD_RTTIEXT(TNaming_NamedShape, TDF_Attribute)

private:
  Standard_EXPORT void Add(TNaming_PtrNode& Evolution);

  TNaming_PtrNode   myNode;
  TNaming_Evolution myEvolution;
  int               myVersion;
};

inline const Standard_GUID& TNaming_NamedShape::ID() const
{
  return GetID();
}

inline TNaming_Evolution TNaming_NamedShape::Evolution() const
{
  return myEvolution;
}

inline int TNaming_NamedShape::Version() const
{
  return myVersion;
}

inline void TNaming_NamedShape::SetVersion(const int v)
{
  myVersion = v;
}
