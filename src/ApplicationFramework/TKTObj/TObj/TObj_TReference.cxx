#include <TObj_Object.hpp>
#include <TObj_TReference.hpp>
#include <TObj_TObject.hpp>

#include <Standard_GUID.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_DeltaOnAddition.hpp>
#include <TDF_DeltaOnRemoval.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_TReference, TDF_Attribute)

TObj_TReference::TObj_TReference() = default;

const Standard_GUID& TObj_TReference::GetID()
{
  static Standard_GUID theGUID("3bbefb44-e618-11d4-ba38-0060b0ee18ea");
  return theGUID;
}

const Standard_GUID& TObj_TReference::ID() const
{
  return GetID();
}

occ::handle<TObj_TReference> TObj_TReference::Set(const TDF_Label&                theLabel,
                                                  const occ::handle<TObj_Object>& theObject,
                                                  const occ::handle<TObj_Object>& theMaster)
{
  occ::handle<TObj_TReference> A;
  if (!theLabel.FindAttribute(TObj_TReference::GetID(), A))
  {
    A = new TObj_TReference;
    theLabel.AddAttribute(A);
  }
  else
  {
    occ::handle<TObj_Object> anObj = A->Get();
    if (!anObj.IsNull())
      anObj->RemoveBackReference(theMaster);
  }
  A->Set(theObject, theMaster->GetLabel());
  if (!theObject.IsNull())
    theObject->AddBackReference(theMaster);
  return A;
}

void TObj_TReference::Set(const occ::handle<TObj_Object>& theElem, const TDF_Label& theMasterLabel)
{
  Backup();
  if (theElem.IsNull())
    myLabel.Nullify();
  else
    myLabel = theElem->GetLabel();

  myMasterLabel = theMasterLabel;
}

void TObj_TReference::Set(const TDF_Label& theLabel, const TDF_Label& theMasterLabel)
{
  Backup();
  myLabel       = theLabel;
  myMasterLabel = theMasterLabel;
}

occ::handle<TObj_Object> TObj_TReference::Get() const
{
  occ::handle<TObj_TObject> aTObject;
  occ::handle<TObj_Object>  anObject;

  if (myLabel.IsNull() || !myLabel.FindAttribute(TObj_TObject::GetID(), aTObject))
  {
    return anObject;
  }
  anObject = aTObject->Get();
  return anObject;
}

occ::handle<TDF_Attribute> TObj_TReference::NewEmpty() const
{
  return new TObj_TReference();
}

void TObj_TReference::Restore(const occ::handle<TDF_Attribute>& theWith)
{
  occ::handle<TObj_TReference> aReference = occ::down_cast<TObj_TReference>(theWith);
  myLabel                                 = aReference->myLabel;
  myMasterLabel                           = aReference->myMasterLabel;
}

void TObj_TReference::Paste(const occ::handle<TDF_Attribute>&       theInto,
                            const occ::handle<TDF_RelocationTable>& RT) const
{
  occ::handle<TObj_TReference> aReference = occ::down_cast<TObj_TReference>(theInto);
  occ::handle<TObj_TObject>    aObject, aMasterTObj;
  if (myLabel.IsNull())
  {

    aReference->myLabel.Nullify();
    return;
  }

  TDF_Label aRefLabel = myLabel;
  if (!RT->HasRelocation(myLabel, aRefLabel))
    aRefLabel = myLabel;
  aRefLabel.FindAttribute(TObj_TObject::GetID(), aObject);
  occ::handle<TObj_Object> anIObject;
  if (!aObject.IsNull())
    anIObject = aObject->Get();

  occ::handle<TObj_Object> aMasterObj;
  TObj_Object::GetObj(aReference->Label(), aMasterObj, true);
  TDF_Label aMasterLabel;
  if (!aMasterObj.IsNull())
    aMasterLabel = aMasterObj->GetLabel();
  if (aMasterLabel.IsNull() || !aMasterLabel.FindAttribute(TObj_TObject::GetID(), aMasterTObj))
    return;

  aReference->Set(anIObject, aMasterLabel);

  if (!anIObject.IsNull())
    anIObject->AddBackReference(aMasterTObj->Get());
}

void TObj_TReference::BeforeForget()
{

  if (myMasterLabel.IsNull())
    return;

  occ::handle<TObj_Object>  aMasterObject;
  occ::handle<TObj_TObject> aTObject;
  if (!myMasterLabel.FindAttribute(TObj_TObject::GetID(), aTObject))
    return;
  aMasterObject = aTObject->Get();

  occ::handle<TObj_Object> anObj = Get();
  if (anObj.IsNull())
    return;

  aMasterObject->BeforeForgetReference(GetLabel());
  anObj->RemoveBackReference(aMasterObject);
}

bool TObj_TReference::BeforeUndo(const occ::handle<TDF_AttributeDelta>& theDelta, const bool)
{
  if (!theDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition)))
    return true;

  if (myMasterLabel.IsNull())
    return true;

  occ::handle<TObj_Object> anObject = Get();
  if (anObject.IsNull())
    return true;

  occ::handle<TObj_Object>  aMasterObject;
  occ::handle<TObj_TObject> aTObject;
  if (!myMasterLabel.FindAttribute(TObj_TObject::GetID(), aTObject))
    return true;
  aMasterObject = aTObject->Get();

  if (!anObject.IsNull())
    anObject->RemoveBackReference(aMasterObject);

  return true;
}

bool TObj_TReference::AfterUndo(const occ::handle<TDF_AttributeDelta>& theDelta, const bool)
{
  if (!theDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnRemoval)))
    return true;

  if (myMasterLabel.IsNull())
    return true;

  occ::handle<TObj_Object> anObject = Get();
  if (anObject.IsNull())
    return true;

  occ::handle<TObj_Object>  aMasterObject;
  occ::handle<TObj_TObject> aTObject;

  if (!myMasterLabel.FindAttribute(TObj_TObject::GetID(), aTObject))
    return true;
  aMasterObject = aTObject->Get();

  if (!anObject.IsNull())
    anObject->AddBackReference(aMasterObject);

  return true;
}

void TObj_TReference::AfterResume()
{
  if (myMasterLabel.IsNull())
    return;

  occ::handle<TObj_Object>  aMasterObject;
  occ::handle<TObj_TObject> aTObject;
  if (!myMasterLabel.FindAttribute(TObj_TObject::GetID(), aTObject))
    return;
  aMasterObject                     = aTObject->Get();
  occ::handle<TObj_Object> anObject = Get();

  if (!anObject.IsNull())
    anObject->AddBackReference(aMasterObject);
}

bool TObj_TReference::AfterRetrieval(const bool)
{
  if (myMasterLabel.IsNull())
    return true;

  occ::handle<TObj_Object>  anObject = Get();
  occ::handle<TObj_Object>  aMasterObject;
  occ::handle<TObj_TObject> aTObject;
  if (!myMasterLabel.FindAttribute(TObj_TObject::GetID(), aTObject))
    return false;

  aMasterObject = aTObject->Get();
  if (!anObject.IsNull())
    anObject->AddBackReference(aMasterObject);

  return true;
}
