#include <BinMDataXtd.hpp>
#include <BinMDataXtd_ConstraintDriver.hpp>
#include <BinMDataXtd_GeometryDriver.hpp>
#include <BinMDataXtd_PatternStdDriver.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <Message_Messenger.hpp>
#include <BinMDataXtd_PresentationDriver.hpp>
#include <BinMDataXtd_PositionDriver.hpp>
#include <BinMDataXtd_TriangulationDriver.hpp>

static int myDocumentVersion = -1;

void BinMDataXtd::AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                             const occ::handle<Message_Messenger>&   theMsgDriver)
{
  theDriverTable->AddDriver(new BinMDataXtd_ConstraintDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataXtd_GeometryDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataXtd_PatternStdDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataXtd_TriangulationDriver(theMsgDriver));

  theDriverTable->AddDriver(new BinMDataXtd_PresentationDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataXtd_PositionDriver(theMsgDriver));
}

void BinMDataXtd::SetDocumentVersion(const int theVersion)
{
  myDocumentVersion = theVersion;
}

int BinMDataXtd::DocumentVersion()
{
  return myDocumentVersion;
}
