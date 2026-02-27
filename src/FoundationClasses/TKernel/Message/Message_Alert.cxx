#include <Message_Alert.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_Alert, Standard_Transient)

const char* System::log::Message_Alert::GetMessageKey() const
{
  return DynamicType()->Name();
}

bool System::log::Message_Alert::SupportsMerge() const
{

  return true;
}

bool System::log::Message_Alert::Merge(const occ::handle<System::log::Message_Alert>&)
{

  return true;
}

void System::log::Message_Alert::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
}
