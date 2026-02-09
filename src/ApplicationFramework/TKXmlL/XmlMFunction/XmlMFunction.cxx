#include <XmlMFunction.hpp>

#include <Message_Messenger.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMFunction_FunctionDriver.hpp>
#include <XmlMFunction_GraphNodeDriver.hpp>
#include <XmlMFunction_ScopeDriver.hpp>

void XmlMFunction::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                              const occ::handle<Message_Messenger>&   aMessageDriver)
{
  aDriverTable->AddDriver(new XmlMFunction_FunctionDriver(aMessageDriver));
  aDriverTable->AddDriver(new XmlMFunction_ScopeDriver(aMessageDriver));
  aDriverTable->AddDriver(new XmlMFunction_GraphNodeDriver(aMessageDriver));
}
