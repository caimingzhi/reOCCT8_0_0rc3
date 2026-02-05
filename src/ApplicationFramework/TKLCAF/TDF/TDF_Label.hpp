#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_LabelNodePtr.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <NCollection_IndexedMap.hpp>
class TDF_Attribute;
class TDF_Data;
class Standard_GUID;
class TDF_IDFilter;

//! This class provides basic operations to define
//! a label in a data structure.
//! A label is a feature in the feature hierarchy. A
//! label is always connected to a Data from TDF.
//! To a label is attached attributes containing the
//! software components information.
//!
//! Label information:
//!
//! It is possible to know the tag, the father, the
//! depth in the tree of the label, if the label is
//! root, null or equal to another label.
//!
//! Comfort methods:
//! Some methods useful on a label.
//!
//! Attributes:
//!
//! It is possible to get an attribute in accordance
//! to an ID, or the yougest previous version of a
//! current attribute.
class TDF_Label
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty label object.
  TDF_Label();

  //! Nullifies the label.
  void Nullify();

  //! Returns the Data owning <me>.
  occ::handle<TDF_Data> Data() const;

  //! Returns the tag of the label.
  //! This is the integer assigned randomly to a label
  //! in a data framework. This integer is used to
  //! identify this label in an entry.
  int Tag() const;

  //! Returns the label father. This label may be null
  //! if the label is root.
  const TDF_Label Father() const;

  //! Returns True if the <aLabel> is null, i.e. it has
  //! not been included in the data framework.
  bool IsNull() const;

  //! Sets or unsets <me> and all its descendants as
  //! imported label, according to <aStatus>.
  Standard_EXPORT void Imported(const bool aStatus) const;

  //! Returns True if the <aLabel> is imported.
  bool IsImported() const;

  //! Returns True if the <aLabel> is equal to me (same
  //! LabelNode*).
  bool IsEqual(const TDF_Label& aLabel) const;

  bool operator==(const TDF_Label& aLabel) const { return IsEqual(aLabel); }

  bool IsDifferent(const TDF_Label& aLabel) const;

  bool operator!=(const TDF_Label& aLabel) const { return IsDifferent(aLabel); }

  bool IsRoot() const;

  //! Returns true if <me> owns an attribute with <anID> as ID.
  Standard_EXPORT bool IsAttribute(const Standard_GUID& anID) const;

  //! Adds an Attribute to the current label. Raises if
  //! there is already one.
  Standard_EXPORT void AddAttribute(const occ::handle<TDF_Attribute>& anAttribute,
                                    const bool                        append = true) const;

  //! Forgets an Attribute from the current label,
  //! setting its forgotten status true and its valid
  //! status false. Raises if the attribute is not in
  //! the structure.
  Standard_EXPORT void ForgetAttribute(const occ::handle<TDF_Attribute>& anAttribute) const;

  //! Forgets the Attribute of GUID <aguid> from the
  //! current label. If the attribute doesn't exist
  //! returns False. Otherwise returns True.
  Standard_EXPORT bool ForgetAttribute(const Standard_GUID& aguid) const;

  //! Forgets all the attributes. Does it on also on the
  //! sub-labels if <clearChildren> is set to true. Of
  //! course, this method is compatible with Transaction
  //! & Delta mechanisms.
  Standard_EXPORT void ForgetAllAttributes(const bool clearChildren = true) const;

  //! Undo Forget action, setting its forgotten status
  //! false and its valid status true. Raises if the
  //! attribute is not in the structure.
  Standard_EXPORT void ResumeAttribute(const occ::handle<TDF_Attribute>& anAttribute) const;

  //! Finds an attribute of the current label, according
  //! to <anID>.
  //! If anAttribute is not a valid one, false is returned.
  //!
  //! The method returns True if found, False otherwise.
  //!
  //! A removed attribute cannot be found.
  Standard_EXPORT bool FindAttribute(const Standard_GUID&        anID,
                                     occ::handle<TDF_Attribute>& anAttribute) const;

  //! Safe variant of FindAttribute() for arbitrary type of argument
  template <class T>
  bool FindAttribute(const Standard_GUID& theID, occ::handle<T>& theAttr) const
  {
    occ::handle<TDF_Attribute> anAttr;
    return FindAttribute(theID, anAttr) && !(theAttr = occ::down_cast<T>(anAttr)).IsNull();
  }

  //! Finds an attribute of the current label, according
  //! to <anID> and <aTransaction>. This attribute
  //! has/had to be a valid one for the given
  //! transaction index. So, this attribute is not
  //! necessarily a valid one.
  //!
  //! The method returns True if found, False otherwise.
  //!
  //! A removed attribute cannot be found nor a backuped
  //! attribute of a removed one.
  Standard_EXPORT bool FindAttribute(const Standard_GUID&        anID,
                                     const int                   aTransaction,
                                     occ::handle<TDF_Attribute>& anAttribute) const;

  //! Returns true if <me> or a DESCENDANT of <me> owns
  //! attributes not yet available in transaction 0. It
  //! means at least one of their attributes is new,
  //! modified or deleted.
  bool MayBeModified() const;

  //! Returns true if <me> owns attributes not yet
  //! available in transaction 0. It means at least one
  //! attribute is new, modified or deleted.
  bool AttributesModified() const;

  //! Returns true if this label has at least one attribute.
  Standard_EXPORT bool HasAttribute() const;

  //! Returns the number of attributes.
  Standard_EXPORT int NbAttributes() const;

  //! Returns the depth of the label in the data framework.
  //! This corresponds to the number of fathers which
  //! this label has, and is used in determining
  //! whether a label is root, null or equivalent to another label.
  //! Exceptions:
  //! Standard_NullObject if this label is null. This is
  //! because a null object can have no depth.
  Standard_EXPORT int Depth() const;

  //! Returns True if <me> is a descendant of
  //! <aLabel>. Attention: every label is its own
  //! descendant.
  Standard_EXPORT bool IsDescendant(const TDF_Label& aLabel) const;

  //! Returns the root label Root of the data structure.
  //! This has a depth of 0.
  //! Exceptions:
  //! Standard_NullObject if this label is null. This is
  //! because a null object can have no depth.
  Standard_EXPORT const TDF_Label Root() const;

  //! Returns true if this label has at least one child.
  bool HasChild() const;

  //! Returns the number of children.
  Standard_EXPORT int NbChildren() const;

  //! Finds a child label having <aTag> as tag. Creates
  //! The tag aTag identifies the label which will be the parent.
  //! If create is true and no child label is found, a new one is created.
  //! Example:
  //! //creating a label with tag 10 at Root
  //! TDF_Label lab1 = aDF->Root().FindChild(10);
  //! //creating labels 7 and 2 on label 10
  //! TDF_Label lab2 = lab1.FindChild(7);
  //! TDF_Label lab3 = lab1.FindChild(2);
  Standard_EXPORT TDF_Label FindChild(const int aTag, const bool create = true) const;

  //! Create a new child label of me using automatic
  //! delivery tags provided by TagSource.
  TDF_Label NewChild() const;

  //! Returns the current transaction index.
  Standard_EXPORT int Transaction() const;

  //! Returns true if node address of <me> is lower than
  //! <otherLabel> one. Used to quickly sort labels (not
  //! on entry criterion).
  //!
  //! -C++: inline
  Standard_EXPORT bool HasLowerNode(const TDF_Label& otherLabel) const;

  //! Returns true if node address of <me> is greater
  //! than <otherLabel> one. Used to quickly sort labels
  //! (not on entry criterion).
  //!
  //! -C++: inline
  Standard_EXPORT bool HasGreaterNode(const TDF_Label& otherLabel) const;

  //! Dumps the minimum information about <me> on
  //! <aStream>.
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  //! Dumps the label on <aStream> and its attributes
  //! rank in <aMap> if their IDs are kept by <IDFilter>.
  Standard_EXPORT void ExtendedDump(Standard_OStream&                                   anOS,
                                    const TDF_IDFilter&                                 aFilter,
                                    NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap) const;

  //! Dumps the label entry.
  Standard_EXPORT void EntryDump(Standard_OStream& anOS) const;

  friend class TDF_ChildIterator;
  friend class TDF_Attribute;
  friend class TDF_AttributeIterator;
  friend class TDF_Data;

  template <class T>
  friend struct std::hash;

private:
  //! Reserved to the friends.
  TDF_Label(const TDF_LabelNodePtr& aNode);

  //! Adds an Attribute to <toNode>. Raises if there is
  //! already one.
  Standard_EXPORT void AddToNode(const TDF_LabelNodePtr&           toNode,
                                 const occ::handle<TDF_Attribute>& anAttribute,
                                 const bool                        append) const;

  //! Forgets an Attribute from <fromNode>. Raises if
  //! the attribute is not in the structure.
  Standard_EXPORT void ForgetFromNode(const TDF_LabelNodePtr&           fromNode,
                                      const occ::handle<TDF_Attribute>& anAttribute) const;

  //! Resumes a forgotten Attribute to <toNode>. Raises
  //! if the attribute is not in the structure.
  Standard_EXPORT void ResumeToNode(const TDF_LabelNodePtr&           fromNode,
                                    const occ::handle<TDF_Attribute>& anAttribute) const;

  Standard_EXPORT TDF_LabelNodePtr FindOrAddChild(const int aTag, const bool create) const;

  Standard_EXPORT void InternalDump(Standard_OStream&                                   anOS,
                                    const TDF_IDFilter&                                 aFilter,
                                    NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap,
                                    const bool extended) const;

  TDF_LabelNodePtr myLabelNode;
};

#include <TDF_LabelNode.hpp>
#include <TDF_TagSource.hpp>
#include <TDF_Data.hpp>

#include <cstdint>

namespace std
{
  template <>
  struct hash<TDF_Label>
  {
    size_t operator()(const TDF_Label& theLabel) const noexcept
    {
      return static_cast<size_t>(reinterpret_cast<std::uintptr_t>(theLabel.myLabelNode));
    }
  };
} // namespace std

inline TDF_Label::TDF_Label()
    : myLabelNode(nullptr)
{
}

inline TDF_Label::TDF_Label(const TDF_LabelNodePtr& aNode)
    : myLabelNode(aNode)
{
}

inline void TDF_Label::Nullify()
{
  myLabelNode = nullptr;
}

inline bool TDF_Label::IsRoot() const
{
  return myLabelNode->IsRoot();
}

inline bool TDF_Label::IsNull() const
{
  return (myLabelNode == nullptr);
}

inline bool TDF_Label::IsImported() const
{
  return myLabelNode->IsImported();
}

inline bool TDF_Label::IsEqual(const TDF_Label& aLabel) const
{
  return (myLabelNode == aLabel.myLabelNode);
}

inline bool TDF_Label::IsDifferent(const TDF_Label& aLabel) const
{
  return (myLabelNode != aLabel.myLabelNode);
}

inline int TDF_Label::Tag() const
{
  return myLabelNode->Tag();
}

inline const TDF_Label TDF_Label::Father() const
{
  return TDF_Label(myLabelNode->Father());
}

inline bool TDF_Label::HasChild() const
{
  return (myLabelNode->FirstChild() != nullptr);
}

inline bool TDF_Label::AttributesModified() const
{
  return myLabelNode->AttributesModified();
}

inline bool TDF_Label::MayBeModified() const
{
  return myLabelNode->MayBeModified();
}

inline occ::handle<TDF_Data> TDF_Label::Data() const
{
  return myLabelNode->Data();
}

inline Standard_OStream& operator<<(Standard_OStream& anOS, const TDF_Label& aLab)
{
  aLab.Dump(anOS);
  return anOS;
}

inline TDF_Label TDF_Label::NewChild() const
{
  return TDF_TagSource::NewChild(*this);
}
