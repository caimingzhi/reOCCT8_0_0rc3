

#include <Message_AlertExtended.hpp>

#include <Message_Attribute.hpp>
#include <Message_CompositeAlerts.hpp>
#include <Message_Report.hpp>

#include <Precision.hpp>
#include <Standard_Assert.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_AlertExtended, Message_Alert)

occ::handle<Message_Alert> Message_AlertExtended::AddAlert(
  const occ::handle<Message_Report>&    theReport,
  const occ::handle<Message_Attribute>& theAttribute,
  const Message_Gravity                 theGravity)
{
  occ::handle<Message_AlertExtended> anAlert = new Message_AlertExtended();
  anAlert->SetAttribute(theAttribute);
  theReport->AddAlert(theGravity, anAlert);
  return anAlert;
}

const char* Message_AlertExtended::GetMessageKey() const
{
  if (myAttribute.IsNull())
  {
    return Message_Alert::GetMessageKey();
  }
  return myAttribute->GetMessageKey();
}

occ::handle<Message_CompositeAlerts> Message_AlertExtended::CompositeAlerts(const bool theToCreate)
{
  if (myCompositAlerts.IsNull() && theToCreate)
  {
    myCompositAlerts = new Message_CompositeAlerts();
  }
  return myCompositAlerts;
}

bool Message_AlertExtended::SupportsMerge() const
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

bool Message_AlertExtended::Merge(const occ::handle<Message_Alert>&)
{

  return false;
}

void Message_AlertExtended::DumpJson(Standard_OStream& theOStream, int theDepth) const
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
