#include <BinMDocStd.hpp>

#include <BinMDF_ADriverTable.hpp>
#include <BinMDocStd_XLinkDriver.hpp>
#include <Message_Messenger.hpp>

//=================================================================================================

void BinMDocStd::AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                            const occ::handle<Message_Messenger>&   theMsgDriver)
{
  theDriverTable->AddDriver(new BinMDocStd_XLinkDriver(theMsgDriver));
}
