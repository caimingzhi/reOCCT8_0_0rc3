#pragma once

#include <TDocStd_Application.hpp>
#include <Message_Gravity.hpp>
#include <Message_Messenger.hpp>

class TObj_Application : public TDocStd_Application
{
public:
  Standard_EXPORT static occ::handle<TObj_Application> GetInstance();

  occ::handle<Message_Messenger>& Messenger() { return myMessenger; }

public:
  Standard_EXPORT virtual bool SaveDocument(const occ::handle<TDocStd_Document>& theSourceDoc,
                                            const TCollection_ExtendedString&    theTargetFile);

  Standard_EXPORT virtual bool SaveDocument(const occ::handle<TDocStd_Document>& theSourceDoc,
                                            Standard_OStream&                    theOStream);

  Standard_EXPORT virtual bool LoadDocument(const TCollection_ExtendedString& theSourceFile,
                                            occ::handle<TDocStd_Document>&    theTargetDoc);

  Standard_EXPORT virtual bool LoadDocument(Standard_IStream&              theIStream,
                                            occ::handle<TDocStd_Document>& theTargetDoc);

  virtual Standard_EXPORT bool CreateNewDocument(occ::handle<TDocStd_Document>&    theDoc,
                                                 const TCollection_ExtendedString& theFormat);

  virtual Standard_EXPORT void ErrorMessage(const TCollection_ExtendedString& theMsg,
                                            const Message_Gravity             theLevel);

  virtual void ErrorMessage(const TCollection_ExtendedString& theMsg)
  {
    ErrorMessage(theMsg, Message_Alarm);
  }

  void SetVerbose(const bool isVerbose) { myIsVerbose = isVerbose; }

  bool IsVerbose() const { return myIsVerbose; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Standard_EXPORT const char* ResourcesName() override;

protected:
  Standard_EXPORT TObj_Application();

  void SetError(const PCDM_StoreStatus theStatus, const TCollection_ExtendedString& theInfo);

  void SetError(const PCDM_ReaderStatus theStatus, const TCollection_ExtendedString& theInfo);

private:
  bool                           myIsError;
  bool                           myIsVerbose;
  occ::handle<Message_Messenger> myMessenger;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_Application, TDocStd_Application)
};
