#include <Message_Alert.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_Alert, Standard_Transient)

const char* Message_Alert::GetMessageKey() const
{
  return DynamicType()->Name();
}

bool Message_Alert::SupportsMerge() const
{

  return true;
}

bool Message_Alert::Merge(const occ::handle<Message_Alert>&)
{

  return true;
}

void Message_Alert::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
}
