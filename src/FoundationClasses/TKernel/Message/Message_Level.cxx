

#include <Message_Level.hpp>

#include <Message.hpp>
#include <Message_AlertExtended.hpp>
#include <Message_CompositeAlerts.hpp>
#include <Message_AttributeMeter.hpp>
#include <Message_Report.hpp>

#include <OSD_Chronometer.hpp>

Message_Level::Message_Level(const TCollection_AsciiString& theName)
{
  const occ::handle<Message_Report>& aDefaultReport = Message::DefaultReport();
  if (!aDefaultReport.IsNull() && aDefaultReport->IsActiveInMessenger())
  {
    aDefaultReport->AddLevel(this, theName);
  }
}

Message_Level::~Message_Level()
{
  remove();
}

void Message_Level::SetRootAlert(const occ::handle<Message_AlertExtended>& theAlert,
                                 const bool                                isRequiredToStart)
{
  myRootAlert = theAlert;
  if (isRequiredToStart)
  {
    Message_AttributeMeter::StartAlert(myRootAlert);
  }
}

bool Message_Level::AddAlert(const Message_Gravity             theGravity,
                             const occ::handle<Message_Alert>& theAlert)
{
  occ::handle<Message_AlertExtended> anAlertExtended =
    occ::down_cast<Message_AlertExtended>(theAlert);
  if (anAlertExtended.IsNull())
  {
    return false;
  }

  occ::handle<Message_AlertExtended>   aRootAlert      = myRootAlert;
  occ::handle<Message_CompositeAlerts> aCompositeAlert = aRootAlert->CompositeAlerts(true);

  Message_AttributeMeter::StopAlert(myLastAlert);

  myLastAlert = anAlertExtended;

  Message_AttributeMeter::StartAlert(myLastAlert);

  aCompositeAlert->AddAlert(theGravity, theAlert);

  return true;
}

void Message_Level::remove()
{
  const occ::handle<Message_Report>& aDefaultReport = Message::DefaultReport();
  if (aDefaultReport.IsNull() || !aDefaultReport->IsActiveInMessenger())
  {
    return;
  }

  Message_AttributeMeter::StopAlert(myLastAlert);

  if (!Message::DefaultReport().IsNull())
  {
    Message::DefaultReport()->RemoveLevel(this);
  }
}
