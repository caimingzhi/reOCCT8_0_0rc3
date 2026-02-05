#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Storage_Root.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <Storage_Error.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Storage_BaseDriver;
class Storage_Root;
class Standard_Persistent;

class Storage_RootData : public Standard_Transient
{

public:
  Standard_EXPORT Storage_RootData();

  Standard_EXPORT bool Read(const occ::handle<Storage_BaseDriver>& theDriver);

  //! returns the number of roots.
  Standard_EXPORT int NumberOfRoots() const;

  //! add a root to <me>. If a root with same name is present, it
  //! will be replaced by <aRoot>.
  Standard_EXPORT void AddRoot(const occ::handle<Storage_Root>& aRoot);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Storage_Root>>> Roots() const;

  //! find a root with name <aName>.
  Standard_EXPORT occ::handle<Storage_Root> Find(const TCollection_AsciiString& aName) const;

  //! returns true if <me> contains a root named <aName>
  Standard_EXPORT bool IsRoot(const TCollection_AsciiString& aName) const;

  //! remove the root named <aName>.
  Standard_EXPORT void RemoveRoot(const TCollection_AsciiString& aName);

  Standard_EXPORT Storage_Error ErrorStatus() const;

  Standard_EXPORT TCollection_AsciiString ErrorStatusExtension() const;

  Standard_EXPORT void ClearErrorStatus();

  Standard_EXPORT void UpdateRoot(const TCollection_AsciiString&          aName,
                                  const occ::handle<Standard_Persistent>& aPers);

  friend class Storage_Schema;

  DEFINE_STANDARD_RTTIEXT(Storage_RootData, Standard_Transient)

private:
  Standard_EXPORT void SetErrorStatus(const Storage_Error anError);

  Standard_EXPORT void SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt);

  NCollection_DataMap<TCollection_AsciiString, occ::handle<Storage_Root>> myObjects;
  Storage_Error                                                           myErrorStatus;
  TCollection_AsciiString                                                 myErrorStatusExt;
};
