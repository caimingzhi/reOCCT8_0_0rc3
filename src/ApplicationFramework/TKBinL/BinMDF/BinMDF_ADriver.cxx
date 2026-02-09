#include <BinMDF_ADriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDF_ADriver, Standard_Transient)

BinMDF_ADriver::BinMDF_ADriver(const occ::handle<Message_Messenger>& theMsgDriver,
                               const char*                           theName)
    : myMessageDriver(theMsgDriver)
{
  if (theName)
    myTypeName = theName;
}

const occ::handle<Standard_Type>& BinMDF_ADriver::SourceType() const
{
  return NewEmpty()->DynamicType();
}
