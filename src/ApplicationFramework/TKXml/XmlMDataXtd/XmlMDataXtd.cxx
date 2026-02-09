#include <XmlMDataXtd.hpp>

#include <Message_Messenger.hpp>
#include <XmlMDataXtd_ConstraintDriver.hpp>
#include <XmlMDataXtd_GeometryDriver.hpp>
#include <XmlMDataXtd_PatternStdDriver.hpp>
#include <XmlMDataXtd_TriangulationDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>

#include <XmlMDataXtd_PresentationDriver.hpp>
#include <XmlMDataXtd_PositionDriver.hpp>

static int myDocumentVersion = -1;

void XmlMDataXtd::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                             const occ::handle<Message_Messenger>&   anMsgDrv)
{
  aDriverTable->AddDriver(new XmlMDataXtd_GeometryDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataXtd_ConstraintDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataXtd_PatternStdDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataXtd_TriangulationDriver(anMsgDrv));

  aDriverTable->AddDriver(new XmlMDataXtd_PresentationDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataXtd_PositionDriver(anMsgDrv));
}

void XmlMDataXtd::SetDocumentVersion(const int theVersion)
{
  myDocumentVersion = theVersion;
}

int XmlMDataXtd::DocumentVersion()
{
  return myDocumentVersion;
}
