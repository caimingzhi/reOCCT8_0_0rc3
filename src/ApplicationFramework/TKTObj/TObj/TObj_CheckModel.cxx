#include <TObj_CheckModel.hpp>

#include <TObj_ObjectIterator.hpp>
#include <Message_Status.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_CheckModel, Message_Algorithm)

//=================================================================================================

bool TObj_CheckModel::Perform()
{
  ClearStatus();
  if (myModel.IsNull() || myModel->GetLabel().IsNull())
  {
    SetStatus(Message_Fail1);
    return false;
  }
  return checkReferences();
}

//=================================================================================================

bool TObj_CheckModel::checkReferences()
{
  // iterate by all objects in the model
  occ::handle<TObj_ObjectIterator> anIt;
  for (anIt = myModel->GetObjects(); anIt->More(); anIt->Next())
  {
    occ::handle<TObj_Object> anObj = anIt->Value();
    if (anObj.IsNull())
    {
      SetStatus(Message_Alarm1, anIt->DynamicType()->Name());
      continue;
    }

    // Check references
    occ::handle<TObj_ObjectIterator> aRefIter;
    for (aRefIter = anObj->GetReferences(); aRefIter->More(); aRefIter->Next())
    {
      occ::handle<TObj_Object> aReferred = aRefIter->Value();
      if (aReferred.IsNull() || !aReferred->IsAlive())
      {
        SetStatus(Message_Alarm2, anObj->GetName());
        continue;
      }

      // check availability of corresponding back reference
      occ::handle<TObj_ObjectIterator> aBackIter = aReferred->GetBackReferences();
      if (aBackIter.IsNull())
        continue; // object does not support back references

      for (; aBackIter->More(); aBackIter->Next())
        if (aBackIter->Value() == anObj)
          break;
      if (aBackIter->More())
        continue; // ok, back reference found

      if (IsToFix())
      {
        SetStatus(Message_Warn1, anObj->GetName());
        aReferred->AddBackReference(anObj);
      }
      else
        SetStatus(Message_Alarm4, anObj->GetName());
    }

    // Checking back references
    aRefIter = anObj->GetBackReferences();
    if (aRefIter.IsNull())
      continue; // object does not support back references
    NCollection_Sequence<occ::handle<TObj_Object>> aBadBackRefs;
    for (; aRefIter->More(); aRefIter->Next())
    {
      occ::handle<TObj_Object> aReferring = aRefIter->Value();
      if (aReferring.IsNull() || !aReferring->IsAlive())
      {
        SetStatus(Message_Alarm3, anObj->GetName());
        continue;
      }

      occ::handle<TObj_ObjectIterator> aForwIter = aReferring->GetReferences();
      for (; aForwIter->More(); aForwIter->Next())
        if (aForwIter->Value() == anObj)
          break;
      if (aForwIter->More())
        continue; // ok, reference found

      if (IsToFix())
      {
        SetStatus(Message_Warn2, anObj->GetName());
        aBadBackRefs.Append(aReferring);
      }
      else
        SetStatus(Message_Alarm5, anObj->GetName());
    }

    // remove back references to objects that are not referenced actually
    for (int i = 1; i <= aBadBackRefs.Length(); i++)
      anObj->RemoveBackReference(aBadBackRefs(i));
  }

  return !GetStatus().IsAlarm() && !GetStatus().IsFail();
}
