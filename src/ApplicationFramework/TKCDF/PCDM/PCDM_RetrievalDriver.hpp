#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <PCDM_Reader.hpp>
#include <PCDM_ReferenceIterator.hpp>
#include <PCDM_Reference.hpp>
#include <NCollection_Sequence.hpp>

class CDM_MetaData;
class Message_Messenger;

class PCDM_RetrievalDriver : public PCDM_Reader
{
  friend Standard_EXPORT void PCDM_ReferenceIterator::Init(
    const occ::handle<CDM_MetaData>& aMetaData);

public:
  Standard_EXPORT static int DocumentVersion(const TCollection_ExtendedString&     theFileName,
                                             const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT static int ReferenceCounter(const TCollection_ExtendedString&     theFileName,
                                              const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT void SetFormat(const TCollection_ExtendedString& aformat);

  Standard_EXPORT TCollection_ExtendedString GetFormat() const;

  DEFINE_STANDARD_RTTIEXT(PCDM_RetrievalDriver, PCDM_Reader)

private:
  Standard_EXPORT static void References(const TCollection_ExtendedString&     theFileName,
                                         NCollection_Sequence<PCDM_Reference>& theReferences,
                                         const occ::handle<Message_Messenger>& theMsgDriver);

  TCollection_ExtendedString myFormat;
};

