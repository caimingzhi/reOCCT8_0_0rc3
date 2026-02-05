#include <BinMDF.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMDF_ReferenceDriver.hpp>
#include <BinMDF_TagSourceDriver.hpp>
#include <Message_Messenger.hpp>

//=================================================================================================

void BinMDF::AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                        const occ::handle<Message_Messenger>&   aMsgDrv)
{
  aDriverTable->AddDriver(new BinMDF_ReferenceDriver(aMsgDrv));
  aDriverTable->AddDriver(new BinMDF_TagSourceDriver(aMsgDrv));
}
