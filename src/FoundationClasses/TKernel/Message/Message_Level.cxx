

#include <Message_Level.hpp>

#include <Message.hpp>
#include <Message_AlertExtended.hpp>
#include <Message_CompositeAlerts.hpp>
#include <Message_AttributeMeter.hpp>
#include <Message_Report.hpp>

#include <OSD_Chronometer.hpp>

System::log::Message_Level::Message_Level(const TCollection_AsciiString& theName)
{
  const occ::handle<System::log::Message_Report>& aDefaultReport = System::log::Message::DefaultReport();
  if (!aDefaultReport.IsNull() && aDefaultReport->IsActiveInMessenger())
  {
    aDefaultReport->AddLevel(this, theName);
  }
}

System::log::Message_Level::~Message_Level()
{
  remove();
}

void System::log::Message_Level::SetRootAlert(const occ::handle<System::log::Message_AlertExtended>& theAlert,
                                 const bool                                isRequiredToStart)
{
  myRootAlert = theAlert;
  if (isRequiredToStart)
  {
    System::log::Message_AttributeMeter::StartAlert(myRootAlert);
  }
}

bool System::log::Message_Level::AddAlert(const Message_Gravity             theGravity,
                             const occ::handle<System::log::Message_Alert>& theAlert)
{
  occ::handle<System::log::Message_AlertExtended> anAlertExtended =
    occ::down_cast<System::log::Message_AlertExtended>(theAlert);
  if (anAlertExtended.IsNull())
  {
    return false;
  }

  occ::handle<System::log::Message_AlertExtended>   aRootAlert      = myRootAlert;
  occ::handle<System::log::Message_CompositeAlerts> aCompositeAlert = aRootAlert->CompositeAlerts(true);

  System::log::Message_AttributeMeter::StopAlert(myLastAlert);

  myLastAlert = anAlertExtended;

  System::log::Message_AttributeMeter::StartAlert(myLastAlert);

  aCompositeAlert->AddAlert(theGravity, theAlert);

  return true;
}

void System::log::Message_Level::remove()
{
  const occ::handle<System::log::Message_Report>& aDefaultReport = System::log::Message::DefaultReport();
  if (aDefaultReport.IsNull() || !aDefaultReport->IsActiveInMessenger())
  {
    return;
  }

  System::log::Message_AttributeMeter::StopAlert(myLastAlert);

  if (!System::log::Message::DefaultReport().IsNull())
  {
    System::log::Message::DefaultReport()->RemoveLevel(this);
  }
}
