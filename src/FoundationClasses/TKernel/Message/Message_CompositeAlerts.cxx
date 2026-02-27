

#include <Message_CompositeAlerts.hpp>

#include <Message_AlertExtended.hpp>
#include <Standard_Assert.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_CompositeAlerts, Standard_Transient)

const NCollection_List<occ::handle<System::log::Message_Alert>>& System::log::Message_CompositeAlerts::Alerts(
  const Message_Gravity theGravity) const
{
  static const NCollection_List<occ::handle<System::log::Message_Alert>> anEmptyList;
  Standard_ASSERT_RETURN(theGravity >= 0
                           && size_t(theGravity) < sizeof(myAlerts) / sizeof(myAlerts[0]),
                         "Requesting alerts for gravity not in valid range",
                         anEmptyList);
  return myAlerts[theGravity];
}

bool System::log::Message_CompositeAlerts::AddAlert(Message_Gravity                   theGravity,
                                       const occ::handle<System::log::Message_Alert>& theAlert)
{
  Standard_ASSERT_RETURN(!theAlert.IsNull(), "Attempt to add null alert", false);
  Standard_ASSERT_RETURN(theGravity >= 0
                           && size_t(theGravity) < sizeof(myAlerts) / sizeof(myAlerts[0]),
                         "Adding alert with gravity not in valid range",
                         false);

  NCollection_List<occ::handle<System::log::Message_Alert>>& aList = myAlerts[theGravity];
  if (theAlert->SupportsMerge() && !aList.IsEmpty())
  {

    const occ::handle<Standard_Type>& aType = theAlert->DynamicType();
    for (NCollection_List<occ::handle<System::log::Message_Alert>>::Iterator anIt(aList); anIt.More();
         anIt.Next())
    {

      if (aType == anIt.Value()->DynamicType() && theAlert->Merge(anIt.Value()))
        return false;
    }
  }

  aList.Append(theAlert);
  return true;
}

bool System::log::Message_CompositeAlerts::RemoveAlert(Message_Gravity                   theGravity,
                                          const occ::handle<System::log::Message_Alert>& theAlert)
{
  Standard_ASSERT_RETURN(!theAlert.IsNull(), "Attempt to add null alert", false);
  Standard_ASSERT_RETURN(theGravity >= 0
                           && size_t(theGravity) < sizeof(myAlerts) / sizeof(myAlerts[0]),
                         "Adding alert with gravity not in valid range",
                         false);

  NCollection_List<occ::handle<System::log::Message_Alert>>& anAlerts = myAlerts[theGravity];
  if (!anAlerts.Contains(theAlert))
  {
    return false;
  }

  return anAlerts.Remove(theAlert);
}

bool System::log::Message_CompositeAlerts::HasAlert(const occ::handle<System::log::Message_Alert>& theAlert)
{
  for (int aGravIter = Message_Trace; aGravIter <= Message_Fail; ++aGravIter)
  {
    const NCollection_List<occ::handle<System::log::Message_Alert>>& anAlerts =
      Alerts((Message_Gravity)aGravIter);
    if (anAlerts.Contains(theAlert))
    {
      return true;
    }
  }
  return false;
}

bool System::log::Message_CompositeAlerts::HasAlert(const occ::handle<Standard_Type>& theType,
                                       Message_Gravity                   theGravity)
{
  Standard_ASSERT_RETURN(theGravity >= 0
                           && size_t(theGravity) < sizeof(myAlerts) / sizeof(myAlerts[0]),
                         "Requesting alerts for gravity not in valid range",
                         false);

  for (NCollection_List<occ::handle<System::log::Message_Alert>>::Iterator anIt(myAlerts[theGravity]);
       anIt.More();
       anIt.Next())
  {
    if (anIt.Value()->IsInstance(theType))
    {
      return true;
    }
  }
  return false;
}

void System::log::Message_CompositeAlerts::Clear()
{
  for (unsigned int i = 0; i < sizeof(myAlerts) / sizeof(myAlerts[0]); ++i)
  {
    myAlerts[i].Clear();
  }
}

void System::log::Message_CompositeAlerts::Clear(Message_Gravity theGravity)
{
  Standard_ASSERT_RETURN(theGravity >= 0
                           && size_t(theGravity) < sizeof(myAlerts) / sizeof(myAlerts[0]),
                         "Requesting alerts for gravity not in valid range",
                         Standard_VOID_RETURN);
  myAlerts[theGravity].Clear();
}

void System::log::Message_CompositeAlerts::Clear(const occ::handle<Standard_Type>& theType)
{
  for (unsigned int i = 0; i < sizeof(myAlerts) / sizeof(myAlerts[0]); ++i)
  {
    for (NCollection_List<occ::handle<System::log::Message_Alert>>::Iterator anIt(myAlerts[i]); anIt.More();)
    {
      if (anIt.Value().IsNull() || anIt.Value()->IsInstance(theType))
      {
        myAlerts[i].Remove(anIt);
      }
      else
      {
        anIt.More();
      }
    }
  }
}

void System::log::Message_CompositeAlerts::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  int anInc = 1;
  for (unsigned int i = 0; i < sizeof(myAlerts) / sizeof(myAlerts[0]); ++i)
  {
    if (myAlerts[i].IsEmpty())
      continue;

    for (NCollection_List<occ::handle<System::log::Message_Alert>>::Iterator anIt(myAlerts[i]); anIt.More();
         anIt.Next(), anInc++)
    {
      const occ::handle<System::log::Message_Alert>& anAlert = anIt.Value();
      OCCT_DUMP_FIELD_VALUES_DUMPED_INC(theOStream, theDepth, anAlert.get(), anInc)
    }
  }
}
