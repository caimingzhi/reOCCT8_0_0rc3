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

class TDF_Label
{
public:
  DEFINE_STANDARD_ALLOC

  TDF_Label();

  void Nullify();

  occ::handle<TDF_Data> Data() const;

  int Tag() const;

  const TDF_Label Father() const;

  bool IsNull() const;

  Standard_EXPORT void Imported(const bool aStatus) const;

  bool IsImported() const;

  bool IsEqual(const TDF_Label& aLabel) const;

  bool operator==(const TDF_Label& aLabel) const { return IsEqual(aLabel); }

  bool IsDifferent(const TDF_Label& aLabel) const;

  bool operator!=(const TDF_Label& aLabel) const { return IsDifferent(aLabel); }

  bool IsRoot() const;

  Standard_EXPORT bool IsAttribute(const Standard_GUID& anID) const;

  Standard_EXPORT void AddAttribute(const occ::handle<TDF_Attribute>& anAttribute,
                                    const bool                        append = true) const;

  Standard_EXPORT void ForgetAttribute(const occ::handle<TDF_Attribute>& anAttribute) const;

  Standard_EXPORT bool ForgetAttribute(const Standard_GUID& aguid) const;

  Standard_EXPORT void ForgetAllAttributes(const bool clearChildren = true) const;

  Standard_EXPORT void ResumeAttribute(const occ::handle<TDF_Attribute>& anAttribute) const;

  Standard_EXPORT bool FindAttribute(const Standard_GUID&        anID,
                                     occ::handle<TDF_Attribute>& anAttribute) const;

  template <class T>
  bool FindAttribute(const Standard_GUID& theID, occ::handle<T>& theAttr) const
  {
    occ::handle<TDF_Attribute> anAttr;
    return FindAttribute(theID, anAttr) && !(theAttr = occ::down_cast<T>(anAttr)).IsNull();
  }

  Standard_EXPORT bool FindAttribute(const Standard_GUID&        anID,
                                     const int                   aTransaction,
                                     occ::handle<TDF_Attribute>& anAttribute) const;

  bool MayBeModified() const;

  bool AttributesModified() const;

  Standard_EXPORT bool HasAttribute() const;

  Standard_EXPORT int NbAttributes() const;

  Standard_EXPORT int Depth() const;

  Standard_EXPORT bool IsDescendant(const TDF_Label& aLabel) const;

  Standard_EXPORT const TDF_Label Root() const;

  bool HasChild() const;

  Standard_EXPORT int NbChildren() const;

  Standard_EXPORT TDF_Label FindChild(const int aTag, const bool create = true) const;

  TDF_Label NewChild() const;

  Standard_EXPORT int Transaction() const;

  Standard_EXPORT bool HasLowerNode(const TDF_Label& otherLabel) const;

  Standard_EXPORT bool HasGreaterNode(const TDF_Label& otherLabel) const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  Standard_EXPORT void ExtendedDump(Standard_OStream&                                   anOS,
                                    const TDF_IDFilter&                                 aFilter,
                                    NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap) const;

  Standard_EXPORT void EntryDump(Standard_OStream& anOS) const;

  friend class TDF_ChildIterator;
  friend class TDF_Attribute;
  friend class TDF_AttributeIterator;
  friend class TDF_Data;

  template <class T>
  friend struct std::hash;

private:
  TDF_Label(const TDF_LabelNodePtr& aNode);

  Standard_EXPORT void AddToNode(const TDF_LabelNodePtr&           toNode,
                                 const occ::handle<TDF_Attribute>& anAttribute,
                                 const bool                        append) const;

  Standard_EXPORT void ForgetFromNode(const TDF_LabelNodePtr&           fromNode,
                                      const occ::handle<TDF_Attribute>& anAttribute) const;

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
