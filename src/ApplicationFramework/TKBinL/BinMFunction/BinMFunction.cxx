#include <BinMFunction.hpp>

#include <BinMDF_ADriverTable.hpp>
#include <BinMFunction_FunctionDriver.hpp>
#include <BinMFunction_GraphNodeDriver.hpp>
#include <BinMFunction_ScopeDriver.hpp>
#include <Message_Messenger.hpp>

//=================================================================================================

void BinMFunction::AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                              const occ::handle<Message_Messenger>&   theMsgDriver)
{
  theDriverTable->AddDriver(new BinMFunction_FunctionDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMFunction_GraphNodeDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMFunction_ScopeDriver(theMsgDriver));
}
