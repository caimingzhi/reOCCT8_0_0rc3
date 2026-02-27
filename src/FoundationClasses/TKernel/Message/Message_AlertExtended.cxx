

#include <Message_AlertExtended.hpp>

#include <Message_Attribute.hpp>
#include <Message_CompositeAlerts.hpp>
#include <Message_Report.hpp>

#include <Precision.hpp>
#include <Standard_Assert.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_AlertExtended, System::log::Message_Alert)

occ::handle<System::log::Message_Alert> System::log::Message_AlertExtended::AddAlert(
  const occ::handle<System::log::Message_Report>&    theReport,
  const occ::handle<System::log::Message_Attribute>& theAttribute,
  const Message_Gravity                 theGravity)
{
  occ::handle<System::log::Message_AlertExtended> anAlert = new System::log::Message_AlertExtended();
  anAlert->SetAttribute(theAttribute);
  theReport->AddAlert(theGravity, anAlert);
  return anAlert;
}

const char* System::log::Message_AlertExtended::GetMessageKey() const
{
  if (myAttribute.IsNull())
  {
    return System::log::Message_Alert::GetMessageKey();
  }
  return myAttribute->GetMessageKey();
}

occ::handle<System::log::Message_CompositeAlerts> System::log::Message_AlertExtended::CompositeAlerts(const bool theToCreate)
{
  if (myCompositAlerts.IsNull() && theToCreate)
  {
    myCompositAlerts = new System::log::Message_CompositeAlerts();
  }
  return myCompositAlerts;
}

bool System::log::Message_AlertExtended::SupportsMerge() const
{
  if (myCompositAlerts.IsNull())
  {
    return true;
  }

  for (int aGravIter = Message_Trace; aGravIter <= Message_Fail; ++aGravIter)
  {
    if (!myCompositAlerts->Alerts((Message_Gravity)aGravIter).IsEmpty())
    {
      return false;
    }
  }

  return true;
}

bool System::log::Message_AlertExtended::Merge(const occ::handle<System::log::Message_Alert>&)
{

  return false;
}

void System::log::Message_AlertExtended::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  if (!myCompositAlerts.IsNull())
  {
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myCompositAlerts.get())
  }
  if (!myAttribute.IsNull())
  {
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAttribute.get())
  }
}
