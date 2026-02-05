#include <XmlMDataStd.hpp>

#include <Message_Messenger.hpp>
#include <XmlMDataStd_AsciiStringDriver.hpp>
#include <XmlMDataStd_BooleanArrayDriver.hpp>
#include <XmlMDataStd_BooleanListDriver.hpp>
#include <XmlMDataStd_ByteArrayDriver.hpp>
#include <XmlMDataStd_ExpressionDriver.hpp>
#include <XmlMDataStd_ExtStringArrayDriver.hpp>
#include <XmlMDataStd_ExtStringListDriver.hpp>
#include <XmlMDataStd_IntegerArrayDriver.hpp>
#include <XmlMDataStd_IntegerDriver.hpp>
#include <XmlMDataStd_IntegerListDriver.hpp>
#include <XmlMDataStd_IntPackedMapDriver.hpp>
#include <XmlMDataStd_NamedDataDriver.hpp>
#include <XmlMDataStd_GenericExtStringDriver.hpp>
#include <XmlMDataStd_RealArrayDriver.hpp>
#include <XmlMDataStd_RealDriver.hpp>
#include <XmlMDataStd_RealListDriver.hpp>
#include <XmlMDataStd_ReferenceArrayDriver.hpp>
#include <XmlMDataStd_ReferenceListDriver.hpp>
#include <XmlMDataStd_GenericEmptyDriver.hpp>
#include <XmlMDataStd_TreeNodeDriver.hpp>
#include <XmlMDataStd_UAttributeDriver.hpp>
#include <XmlMDataStd_VariableDriver.hpp>
#include <XmlMDF_ADriverTable.hpp>

//=================================================================================================

void XmlMDataStd::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                             const occ::handle<Message_Messenger>&   anMsgDrv)
{
  aDriverTable->AddDriver(new XmlMDataStd_IntegerArrayDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_RealArrayDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_UAttributeDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_GenericExtStringDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_IntegerDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_RealDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_VariableDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_ExpressionDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_TreeNodeDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_ExtStringArrayDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_GenericEmptyDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_IntegerListDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_RealListDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_ExtStringListDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_BooleanListDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_ReferenceListDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_BooleanArrayDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_ReferenceArrayDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_ByteArrayDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_NamedDataDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_AsciiStringDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMDataStd_IntPackedMapDriver(anMsgDrv));
}
