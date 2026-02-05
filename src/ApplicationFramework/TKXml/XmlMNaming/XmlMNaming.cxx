#include <XmlMNaming.hpp>

#include <Message_Messenger.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMNaming_NamedShapeDriver.hpp>
#include <XmlMNaming_NamingDriver.hpp>

//=================================================================================================

void XmlMNaming::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                            const occ::handle<Message_Messenger>&   aMessageDriver)
{
  aDriverTable->AddDriver(new XmlMNaming_NamedShapeDriver(aMessageDriver));
  aDriverTable->AddDriver(new XmlMNaming_NamingDriver(aMessageDriver));
}
