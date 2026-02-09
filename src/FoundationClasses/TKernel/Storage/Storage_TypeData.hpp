#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Storage_Error.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Storage_BaseDriver;

class Storage_TypeData : public Standard_Transient
{

public:
  Standard_EXPORT Storage_TypeData();

  Standard_EXPORT bool Read(const occ::handle<Storage_BaseDriver>& theDriver);

  Standard_EXPORT int NumberOfTypes() const;

  Standard_EXPORT void AddType(const TCollection_AsciiString& aName, const int aTypeNum);

  Standard_EXPORT TCollection_AsciiString Type(const int aTypeNum) const;

  Standard_EXPORT int Type(const TCollection_AsciiString& aTypeName) const;

  Standard_EXPORT bool IsType(const TCollection_AsciiString& aName) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> Types() const;

  Standard_EXPORT Storage_Error ErrorStatus() const;

  Standard_EXPORT TCollection_AsciiString ErrorStatusExtension() const;

  Standard_EXPORT void ClearErrorStatus();

  Standard_EXPORT void Clear();

  friend class Storage_Schema;

  DEFINE_STANDARD_RTTIEXT(Storage_TypeData, Standard_Transient)

private:
  Standard_EXPORT void SetErrorStatus(const Storage_Error anError);

  Standard_EXPORT void SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt);

  NCollection_IndexedDataMap<TCollection_AsciiString, int> myPt;
  Storage_Error                                            myErrorStatus;
  TCollection_AsciiString                                  myErrorStatusExt;
};
