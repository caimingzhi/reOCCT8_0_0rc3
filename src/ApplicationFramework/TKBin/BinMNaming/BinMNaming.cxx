#include <BinMNaming.hpp>

#include <BinMDF_ADriverTable.hpp>
#include <BinMNaming_NamedShapeDriver.hpp>
#include <BinMNaming_NamingDriver.hpp>
#include <Message_Messenger.hpp>

//=================================================================================================

void BinMNaming::AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                            const occ::handle<Message_Messenger>&   aMessageDriver)
{
  aDriverTable->AddDriver(new BinMNaming_NamedShapeDriver(aMessageDriver));
  aDriverTable->AddDriver(new BinMNaming_NamingDriver(aMessageDriver));
}
