#include <CDM_Application.hpp>
#include <CDM_Document.hpp>
#include <CDM_MetaData.hpp>
#include <Resource_Manager.hpp>
#include <Standard_Dump.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(CDM_Application, Standard_Transient)

CDM_Application::CDM_Application()
{
  myMessenger = new Message_Messenger;
}

void CDM_Application::SetDocumentVersion(const occ::handle<CDM_Document>& aDocument,
                                         const occ::handle<CDM_MetaData>& aMetaData) const
{
  aDocument->SetModifications(aMetaData->DocumentVersion(this));
}

void CDM_Application::SetReferenceCounter(const occ::handle<CDM_Document>& aDocument,
                                          const int                        aReferenceCounter)
{
  aDocument->SetReferenceCounter(aReferenceCounter);
}

occ::handle<Message_Messenger> CDM_Application::MessageDriver()
{
  return myMessenger;
}

void CDM_Application::Write(const char16_t* aString)
{
  MessageDriver()->Send(aString);
}

void CDM_Application::BeginOfUpdate(const occ::handle<CDM_Document>&)
{
  TCollection_ExtendedString updating("Updating: ");
  updating += "Document";
  Write(updating.ToExtString());
}

void CDM_Application::EndOfUpdate(const occ::handle<CDM_Document>&,
                                  const bool theStatus,
                                  const TCollection_ExtendedString&)
{
  TCollection_ExtendedString message;
  if (theStatus)
    message = "Updated: ";
  else
    message = "Error during updating: ";

  message += "Document";
  Write(message.ToExtString());
}

TCollection_ExtendedString CDM_Application::Name() const
{

  return TCollection_ExtendedString();
}

TCollection_AsciiString CDM_Application::Version() const
{

  return TCollection_AsciiString();
}

NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& CDM_Application::
  MetaDataLookUpTable()
{
  return myMetaDataLookUpTable;
}

void CDM_Application::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
}
