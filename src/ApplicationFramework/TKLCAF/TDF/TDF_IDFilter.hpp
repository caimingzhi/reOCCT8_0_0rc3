#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Attribute;

class TDF_IDFilter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDF_IDFilter(const bool ignoreMode = true);

  Standard_EXPORT void IgnoreAll(const bool ignore);

  bool IgnoreAll() const;

  Standard_EXPORT void Keep(const Standard_GUID& anID);

  Standard_EXPORT void Keep(const NCollection_List<Standard_GUID>& anIDList);

  Standard_EXPORT void Ignore(const Standard_GUID& anID);

  Standard_EXPORT void Ignore(const NCollection_List<Standard_GUID>& anIDList);

  bool IsKept(const Standard_GUID& anID) const;

  bool IsKept(const occ::handle<TDF_Attribute>& anAtt) const;

  bool IsIgnored(const Standard_GUID& anID) const;

  bool IsIgnored(const occ::handle<TDF_Attribute>& anAtt) const;

  Standard_EXPORT void IDList(NCollection_List<Standard_GUID>& anIDList) const;

  Standard_EXPORT void Copy(const TDF_IDFilter& fromFilter);

  Standard_EXPORT void Dump(Standard_OStream& anOS) const;

  void Assign(const TDF_IDFilter& theFilter)
  {
    myIgnore = theFilter.myIgnore;
    myIDMap  = theFilter.myIDMap;
  }

private:
  TDF_IDFilter(const TDF_IDFilter& aFilter)             = delete;
  TDF_IDFilter& operator=(const TDF_IDFilter& theOther) = delete;

private:
  bool                           myIgnore;
  NCollection_Map<Standard_GUID> myIDMap;
};

#include <TDF_Attribute.hpp>

inline bool TDF_IDFilter::IgnoreAll() const
{
  return myIgnore;
}

inline bool TDF_IDFilter::IsKept(const Standard_GUID& anID) const
{
  return (myIgnore == myIDMap.Contains(anID));
}

inline bool TDF_IDFilter::IsKept(const occ::handle<TDF_Attribute>& anAtt) const
{
  return IsKept(anAtt->ID());
}

inline bool TDF_IDFilter::IsIgnored(const Standard_GUID& anID) const
{
  return (myIgnore != myIDMap.Contains(anID));
}

inline bool TDF_IDFilter::IsIgnored(const occ::handle<TDF_Attribute>& anAtt) const
{
  return IsIgnored(anAtt->ID());
}
