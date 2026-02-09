#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <PCDM_Reference.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>

class Message_Messenger;
class CDM_Document;
class CDM_MetaData;
class CDM_Application;

class PCDM_ReferenceIterator : public Standard_Transient
{

public:
  Standard_EXPORT PCDM_ReferenceIterator(const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT void LoadReferences(const occ::handle<CDM_Document>&    aDocument,
                                      const occ::handle<CDM_MetaData>&    aMetaData,
                                      const occ::handle<CDM_Application>& anApplication,
                                      const bool                          UseStorageConfiguration);

  Standard_EXPORT virtual void Init(const occ::handle<CDM_MetaData>& aMetaData);

  DEFINE_STANDARD_RTTIEXT(PCDM_ReferenceIterator, Standard_Transient)

private:
  Standard_EXPORT virtual bool More() const;

  Standard_EXPORT virtual void Next();

  Standard_EXPORT virtual occ::handle<CDM_MetaData> MetaData(
    NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable,
    const bool UseStorageConfiguration) const;

  Standard_EXPORT virtual int ReferenceIdentifier() const;

  Standard_EXPORT virtual int DocumentVersion() const;

private:
  NCollection_Sequence<PCDM_Reference> myReferences;
  int                                  myIterator;
  occ::handle<Message_Messenger>       myMessageDriver;
};
