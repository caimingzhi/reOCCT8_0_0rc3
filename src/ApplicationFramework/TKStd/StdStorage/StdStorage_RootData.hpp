#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Storage_Error.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <StdStorage_Root.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Storage_BaseDriver;
class StdStorage_Root;

class StdStorage_RootData : public Standard_Transient
{
  friend class StdStorage_Data;

public:
  DEFINE_STANDARD_RTTIEXT(StdStorage_RootData, Standard_Transient)

  Standard_EXPORT bool Read(const occ::handle<Storage_BaseDriver>& theDriver);

  Standard_EXPORT bool Write(const occ::handle<Storage_BaseDriver>& theDriver);

  Standard_EXPORT int NumberOfRoots() const;

  Standard_EXPORT void AddRoot(const occ::handle<StdStorage_Root>& aRoot);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<StdStorage_Root>>> Roots() const;

  Standard_EXPORT occ::handle<StdStorage_Root> Find(const TCollection_AsciiString& aName) const;

  Standard_EXPORT bool IsRoot(const TCollection_AsciiString& aName) const;

  Standard_EXPORT void RemoveRoot(const TCollection_AsciiString& aName);

  Standard_EXPORT Storage_Error ErrorStatus() const;

  Standard_EXPORT TCollection_AsciiString ErrorStatusExtension() const;

  Standard_EXPORT void ClearErrorStatus();

  Standard_EXPORT void Clear();

private:
  Standard_EXPORT StdStorage_RootData();

  Standard_EXPORT void SetErrorStatus(const Storage_Error anError);

  Standard_EXPORT void SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt);

  NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<StdStorage_Root>> myObjects;
  Storage_Error                                                                     myErrorStatus;
  TCollection_AsciiString myErrorStatusExt;
};
