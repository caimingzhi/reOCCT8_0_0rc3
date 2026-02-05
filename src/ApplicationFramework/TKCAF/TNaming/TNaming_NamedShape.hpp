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

//! The basis to define an attribute for the storage of
//! topology and naming data.
//! This attribute contains two parts:
//! -   The type of evolution, a term of the
//! enumeration TNaming_Evolution
//! -   A list of pairs of shapes called the "old"
//! shape and the "new" shape. The meaning
//! depends on the type of evolution.
class TNaming_NamedShape : public TDF_Attribute
{

public:
  //! class method
  //! ============
  //! Returns the GUID for named shapes.
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TNaming_NamedShape();

  Standard_EXPORT bool IsEmpty() const;

  //! Returns the shapes contained in <NS>. Returns a null
  //! shape if IsEmpty.
  Standard_EXPORT TopoDS_Shape Get() const;

  //! Returns the Evolution of the attribute.
  TNaming_Evolution Evolution() const;

  //! Returns the Version of the attribute.
  int Version() const;

  //! Set the Version of the attribute.
  void SetVersion(const int version);

  Standard_EXPORT void Clear();

  ~TNaming_NamedShape() override { Clear(); }

  //! Returns the ID of the attribute.
  const Standard_GUID& ID() const override;

  //! Copies the attribute contents into a new other
  //! attribute. It is used by Backup().
  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  //! Restores the contents from <anAttribute> into this
  //! one. It is used when aborting a transaction.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  //! Makes a DeltaOnModification between <me> and
  //! <anOldAttribute.
  Standard_EXPORT occ::handle<TDF_DeltaOnModification> DeltaOnModification(
    const occ::handle<TDF_Attribute>& anOldAttribute) const override;

  //! Applies a DeltaOnModification to <me>.
  Standard_EXPORT void DeltaOnModification(
    const occ::handle<TDF_DeltaOnModification>& aDelta) override;

  //! Makes a DeltaOnRemoval on <me> because <me> has
  //! disappeared from the DS.
  Standard_EXPORT occ::handle<TDF_DeltaOnRemoval> DeltaOnRemoval() const override;

  //! Returns an new empty attribute from the good end
  //! type. It is used by the copy algorithm.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! This method is different from the "Copy" one,
  //! because it is used when copying an attribute from
  //! a source structure into a target structure. This
  //! method pastes the current attribute to the label
  //! corresponding to the insertor. The pasted
  //! attribute may be a brand new one or a new version
  //! of the previous one.
  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocTationable) const override;

  //! Adds the directly referenced attributes and labels
  //! to <aDataSet>. "Directly" means we have only to
  //! look at the first level of references.
  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT void BeforeRemoval() override;

  //! Something to do before applying <anAttDelta>
  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                  const bool                             forceIt = false) override;

  //! Something to do after applying <anAttDelta>.
  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  //! Dumps the attribute on <aStream>.
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  friend class TNaming_Builder;
  friend class TNaming_Iterator;
  friend class TNaming_NewShapeIterator;
  friend class TNaming_OldShapeIterator;

  DEFINE_STANDARD_RTTIEXT(TNaming_NamedShape, TDF_Attribute)

private:
  //! Adds an evolution
  Standard_EXPORT void Add(TNaming_PtrNode& Evolution);

  TNaming_PtrNode   myNode;
  TNaming_Evolution myEvolution;
  int               myVersion;
};

inline const Standard_GUID& TNaming_NamedShape::ID() const
{
  return GetID();
}

//=================================================================================================

inline TNaming_Evolution TNaming_NamedShape::Evolution() const
{
  return myEvolution;
}

//=================================================================================================

inline int TNaming_NamedShape::Version() const
{
  return myVersion;
}

//=================================================================================================

inline void TNaming_NamedShape::SetVersion(const int v)
{
  myVersion = v;
}
