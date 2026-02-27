#include <XmlMDocStd.hpp>

#include <Message_Messenger.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMDocStd_XLinkDriver.hpp>

void XmlMDocStd::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                            const occ::handle<System::log::Message_Messenger>&   aMessageDriver)
{
  aDriverTable->AddDriver(new XmlMDocStd_XLinkDriver(aMessageDriver));
}
