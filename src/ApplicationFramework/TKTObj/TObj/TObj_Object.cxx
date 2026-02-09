#include <TObj_Object.hpp>

#include <TObj_Assistant.hpp>
#include <TObj_Model.hpp>
#include <TObj_ObjectIterator.hpp>
#include <TObj_OcafObjectIterator.hpp>
#include <TObj_Persistence.hpp>
#include <TObj_ReferenceIterator.hpp>
#include <TObj_SequenceIterator.hpp>
#include <TDataStd_AsciiString.hpp>
#include <TObj_TModel.hpp>
#include <TObj_TNameContainer.hpp>
#include <TObj_TObject.hpp>
#include <TObj_TReference.hpp>

#include <TCollection_HAsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Sequence.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIDIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_CopyLabel.hpp>
#include <TDF_Data.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>
#include <TDataStd_ExtStringArray.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_IntegerArray.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_Owner.hpp>
#include <TDF_TagSource.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_Object, Standard_Transient)

TObj_Object::TObj_Object(const TDF_Label& theLabel, const bool theSetName)
    : myLabel(theLabel)
{
  occ::handle<TObj_Object> aMe = this;
  TObj_TObject::Set(myLabel, aMe);
  if (theSetName)
    TObj_Model::SetNewName(aMe);
}

occ::handle<TObj_Model> TObj_Object::GetModel() const
{
  occ::handle<TObj_Model> aModel;

  if (myLabel.IsNull())
    return aModel;

  occ::handle<TDF_Data> aData = myLabel.Data();
  if (aData.IsNull())
    return aModel;

  TDF_Label                     aLabel = aData->Root();
  occ::handle<TDocStd_Owner>    anOwnerAttr;
  occ::handle<TDocStd_Document> aTDoc;
  if (!aLabel.IsNull() && aLabel.FindAttribute(TDocStd_Owner::GetID(), anOwnerAttr))
    aTDoc = anOwnerAttr->GetDocument();
  if (aTDoc.IsNull())
    return aModel;

  aLabel = aTDoc->Main();
  occ::handle<TObj_TModel> aModelAttr;
  if (!aLabel.IsNull() && aLabel.FindAttribute(TObj_TModel::GetID(), aModelAttr))
    aModel = aModelAttr->Model();

  return aModel;
}

static void addObjToOrderSequence(
  const occ::handle<TObj_Object>&                               theObj,
  const int                                                     theOrder,
  occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>>& theHSeqOfObj,
  const int                                                     theHSeqLength,
  int&                                                          theLastIndex,
  int&                                                          theLastOrder)
{
  if (theOrder > theLastOrder)
  {
    while (theOrder > theLastOrder)
    {

      if (++theLastIndex > theHSeqLength)
      {
        theHSeqOfObj->Append(theObj);
        theLastIndex = theHSeqLength + 1;
        theLastOrder = theOrder;
        return;
      }
      occ::handle<TObj_Object> aNext = theHSeqOfObj->Value(theLastIndex);
      theLastOrder                   = aNext->GetOrder();
    }

    theHSeqOfObj->InsertBefore(theLastIndex, theObj);
    theLastOrder = theOrder;
  }
  else
  {
    while (theOrder < theLastOrder)
    {
      if (--theLastIndex < 1)
      {
        theHSeqOfObj->InsertBefore(1, theObj);
        theLastIndex = 1;
        theLastOrder = theOrder;
        return;
      }

      occ::handle<TObj_Object> aNext = theHSeqOfObj->Value(theLastIndex);
      theLastOrder                   = aNext->GetOrder();
    }

    theHSeqOfObj->InsertAfter(theLastIndex, theObj);
    theLastIndex++;
    theLastOrder = theOrder;
    return;
  }
}

occ::handle<TObj_ObjectIterator> TObj_Object::GetChildren(
  const occ::handle<Standard_Type>& theType) const
{
  occ::handle<TObj_ObjectIterator> anItr =
    new TObj_OcafObjectIterator(GetChildLabel(), theType, true);
  if (!TestFlags(ObjectState_Ordered))
    return anItr;

  int                                                          aLastIndex = 0;
  int                                                          aLastOrder = 0;
  occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>> aHSeqOfObj =
    new NCollection_HSequence<occ::handle<TObj_Object>>();
  for (; anItr->More(); anItr->Next())
  {
    occ::handle<TObj_Object> anObj = anItr->Value();
    if (anObj.IsNull())
      continue;
    int anOrder = anObj->GetOrder();
    if (!aLastIndex)
    {
      aHSeqOfObj->Append(anObj);
      aLastIndex = 1;
      aLastOrder = anOrder;
    }
    else
      addObjToOrderSequence(anObj,
                            anOrder,
                            aHSeqOfObj,
                            aHSeqOfObj->Length(),
                            aLastIndex,
                            aLastOrder);
  }
  return new TObj_SequenceIterator(aHSeqOfObj);
}

#ifdef DFBROWSE
static TDF_Label getLabelByRank(const TDF_Label& theL, const int theRank, const char* theName)
{
  TDF_Label L = theL.FindChild(theRank, false);
  if (L.IsNull())
  {
    L = theL.FindChild(theRank, true);
    TDataStd_Name::Set(L, theName);
  }
  return L;
}
#endif

TDF_Label TObj_Object::GetChildLabel() const
{
#ifdef DFBROWSE
  return getLabelByRank(GetLabel(), 4, "Children");
#else
  return GetLabel().FindChild(4, true);
#endif
}

TDF_Label TObj_Object::getChildLabel(const int theRank) const
{
  TDF_Label aLabel = GetChildLabel();
  if (theRank > 0)
    aLabel = aLabel.FindChild(theRank, true);
  return aLabel;
}

TDF_Label TObj_Object::GetLabel() const
{
  return myLabel;
}

bool TObj_Object::SetName(const occ::handle<TCollection_HExtendedString>& theName) const
{

  occ::handle<TCollection_HExtendedString> anOldName = GetName();
  if (!anOldName.IsNull() && theName->String().IsEqual(anOldName->String()))
    return true;

  const occ::handle<TObj_TNameContainer> aDictionary = GetDictionary();
  occ::handle<TObj_Model>                aModel      = GetModel();
  if (aModel->IsRegisteredName(theName, aDictionary))
    return false;

  if (!anOldName.IsNull())
    aModel->UnRegisterName(anOldName, aDictionary);
  if (theName.IsNull())
    GetLabel().ForgetAttribute(TDataStd_Name::GetID());
  else
  {
    aModel->RegisterName(theName, GetLabel(), aDictionary);
    TDataStd_Name::Set(GetLabel(), theName->String());
  }
  return true;
}

bool TObj_Object::SetName(const occ::handle<TCollection_HAsciiString>& theName) const
{
  occ::handle<TCollection_HExtendedString> aName = new TCollection_HExtendedString(theName);
  return SetName(aName);
}

bool TObj_Object::SetName(const char* theName) const
{
  occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString(theName);
  return SetName(aName);
}

occ::handle<TCollection_HExtendedString> TObj_Object::GetName() const
{
  occ::handle<TCollection_HExtendedString> aName;
  occ::handle<TDataStd_Name>               A;
  if (GetLabel().FindAttribute(TDataStd_Name::GetID(), A))
    aName = new TCollection_HExtendedString(A->Get());
  else
    aName = new TCollection_HExtendedString("");
  return aName;
}

bool TObj_Object::GetName(TCollection_ExtendedString& theStr) const
{
  occ::handle<TCollection_HExtendedString> aName = GetName();
  theStr                                         = aName->String();
  return theStr.Length() != 0;
}

bool TObj_Object::GetName(TCollection_AsciiString& theName) const
{
  occ::handle<TCollection_HExtendedString> aName = GetName();
  if (aName.IsNull())
    return false;
  theName = TCollection_AsciiString(aName->String());
  return theName.Length() != 0;
}

bool TObj_Object::HasReference(const occ::handle<TObj_Object>& theObject) const
{
  if (theObject.IsNull())
    return false;
  occ::handle<TObj_ObjectIterator> anItr = GetReferences(theObject->DynamicType());
  if (anItr.IsNull() || !anItr->More())
    return false;
  for (; anItr->More(); anItr->Next())
    if (anItr->Value() == theObject)
      return true;
  return false;
}

occ::handle<TObj_ObjectIterator> TObj_Object::GetReferences(
  const occ::handle<Standard_Type>& theType) const
{
  return new TObj_ReferenceIterator(GetReferenceLabel(), theType);
}

void TObj_Object::RemoveAllReferences()
{
  GetReferenceLabel().ForgetAllAttributes();
}

void TObj_Object::AddBackReference(const occ::handle<TObj_Object>& theObject)
{
  if (myHSeqBackRef.IsNull())
    myHSeqBackRef = new NCollection_HSequence<occ::handle<TObj_Object>>;

  myHSeqBackRef->Append(theObject);
}

void TObj_Object::RemoveBackReference(const occ::handle<TObj_Object>& theObject,
                                      const bool                      theSingleOnly)
{
  if (myHSeqBackRef.IsNull())
    return;

  for (int i = 1; i <= myHSeqBackRef->Length(); i++)
  {
    if (theObject != myHSeqBackRef->Value(i))
      continue;

    myHSeqBackRef->Remove(i--);
    if (theSingleOnly)
      break;
  }
  if (myHSeqBackRef->Length() < 1)
    myHSeqBackRef.Nullify();
}

occ::handle<TObj_ObjectIterator> TObj_Object::GetBackReferences(
  const occ::handle<Standard_Type>& theType) const
{
  return new TObj_SequenceIterator(myHSeqBackRef, theType);
}

void TObj_Object::ClearBackReferences()
{
  myHSeqBackRef.Nullify();
}

bool TObj_Object::HasBackReferences() const
{
  occ::handle<TObj_ObjectIterator> anItr = GetBackReferences();
  return !anItr.IsNull() && anItr->More();
}

bool TObj_Object::CanRemoveReference(const occ::handle<TObj_Object>&) const
{
  return false;
}

void TObj_Object::RemoveReference(const occ::handle<TObj_Object>& theObject)
{
  occ::handle<TObj_Object> aNullObj;
  ReplaceReference(theObject, aNullObj);
}

bool TObj_Object::CanDetach(const TObj_DeletingMode theMode)
{
  if (!IsAlive())
    return false;

  occ::handle<TObj_ObjectIterator> aRefs = GetBackReferences();

  if (aRefs.IsNull() || !aRefs->More())
    return true;

  if (theMode == TObj_FreeOnly)
    return false;

  if (theMode == TObj_Forced)
    return true;

  occ::handle<TObj_Object> aMe = this;
  for (; aRefs->More(); aRefs->Next())
  {
    occ::handle<TObj_Object> anObject = aRefs->Value();
    if (!anObject->CanRemoveReference(aMe))
      return false;
  }

  return true;
}

bool TObj_Object::Detach(const TObj_DeletingMode theMode)
{
  if (!IsAlive())
    return false;

  if (!RemoveBackReferences(theMode))
    return false;

  occ::handle<TCollection_HExtendedString> anOldName = GetName();

  occ::handle<TObj_ObjectIterator> aChildren = GetChildren();

  for (; aChildren->More(); aChildren->Next())
    aChildren->Value()->Detach(theMode);

  GetReferenceLabel().ForgetAllAttributes();

  ClearBackReferences();

  GetDataLabel().ForgetAllAttributes();

  if (!anOldName.IsNull())
  {
    const occ::handle<TObj_TNameContainer> aDictionary = GetDictionary();

    if (!aDictionary.IsNull() && aDictionary->IsRegistered(anOldName))
    {
      TDF_Label aRegisteredLabel = aDictionary->Get().Find(anOldName);
      if (!aRegisteredLabel.IsNull() && aRegisteredLabel == GetLabel())
        aDictionary->RemoveName(anOldName);
    }
  }
  GetLabel().ForgetAllAttributes();

  return true;
}

bool TObj_Object::Detach(const TDF_Label& theLabel, const TObj_DeletingMode theMode)
{
  occ::handle<TObj_Object> anObject;
  if (GetObj(theLabel, anObject))
    return anObject->Detach(theMode);
  return true;
}

bool TObj_Object::GetObj(const TDF_Label&          theLabel,
                         occ::handle<TObj_Object>& theResult,
                         const bool                isSuper)
{
  if (theLabel.IsNull())
    return false;

  occ::handle<TObj_TObject> A;

  if (theLabel.FindAttribute(TObj_TObject::GetID(), A))
    theResult = A->Get();
  else
    theResult.Nullify();

  if (!theResult.IsNull())
  {
    if (!theResult->myLabel.IsNull())
      return true;

    theResult.Nullify();
  }
  else if (isSuper)
  {

    return GetObj(theLabel.Father(), theResult, isSuper);
  }

  return false;
}

occ::handle<TObj_Object> TObj_Object::GetFatherObject(
  const occ::handle<Standard_Type>& theType) const
{
  occ::handle<TObj_Object> aFather;

  if (myLabel.IsNull())
    return aFather;

  occ::handle<TObj_Object> aSon(this);
  while (aSon->GetObj(aSon->GetLabel().Father(), aFather, true))
  {
    if (theType.IsNull() || aFather->IsKind(theType))
      break;
    else
    {
      aSon = aFather;
      aFather.Nullify();
    }
  }

  return aFather;
}

void TObj_Object::AfterRetrieval()
{

  occ::handle<TObj_Model> aModel = GetModel();
  if (!aModel.IsNull())
    aModel->RegisterName(GetName(), GetLabel(), GetDictionary());
}

void TObj_Object::BeforeStoring() {}

TDF_Label TObj_Object::GetReferenceLabel() const
{
#ifdef DFBROWSE
  return getLabelByRank(GetLabel(), 1, "References");
#else
  return GetLabel().FindChild(1, true);
#endif
}

TDF_Label TObj_Object::GetDataLabel() const
{
#ifdef DFBROWSE
  return getLabelByRank(GetLabel(), 3, "Data");
#else
  return GetLabel().FindChild(3, true);
#endif
}

TDF_Label TObj_Object::getDataLabel(const int theRank1, const int theRank2) const
{
  TDF_Label aLabel;
  if (theRank1 > 0)
  {
    aLabel = GetDataLabel().FindChild(theRank1, true);
    if (theRank2 > 0)
      aLabel = aLabel.FindChild(theRank2, true);
  }
  return aLabel;
}

TDF_Label TObj_Object::getReferenceLabel(const int theRank1, const int theRank2) const
{
  TDF_Label aLabel;
  if (theRank1 > 0)
  {
    aLabel = GetReferenceLabel().FindChild(theRank1, true);
    if (theRank2 > 0)
      aLabel = aLabel.FindChild(theRank2, true);
  }
  return aLabel;
}

bool TObj_Object::isDataAttribute(const Standard_GUID& theGUID,
                                  const int            theRank1,
                                  const int            theRank2) const
{
  return getDataLabel(theRank1, theRank2).IsAttribute(theGUID);
}

double TObj_Object::getReal(const int theRank1, const int theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);

  occ::handle<TDataStd_Real> aReal;
  aLabel.FindAttribute(TDataStd_Real::GetID(), aReal);
  return aReal.IsNull() ? 0. : aReal->Get();
}

bool TObj_Object::setReal(const double theValue,
                          const int    theRank1,
                          const int    theRank2,
                          const double theTolerance) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);

  occ::handle<TDataStd_Real> A;
  if (aLabel.FindAttribute(TDataStd_Real::GetID(), A) && fabs(A->Get() - theValue) <= theTolerance)
    return false;

  TDataStd_Real::Set(aLabel, theValue);
  return true;
}

occ::handle<TCollection_HExtendedString> TObj_Object::getExtString(const int theRank1,
                                                                   const int theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);

  occ::handle<TDataStd_Name> aName;
  aLabel.FindAttribute(TDataStd_Name::GetID(), aName);
  return aName.IsNull() ? nullptr : new TCollection_HExtendedString(aName->Get());
}

void TObj_Object::setExtString(const occ::handle<TCollection_HExtendedString>& theValue,
                               const int                                       theRank1,
                               const int                                       theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);
  if (!theValue.IsNull())
    TDataStd_Name::Set(aLabel, theValue->String());
  else
    aLabel.ForgetAttribute(TDataStd_Name::GetID());
}

occ::handle<TCollection_HAsciiString> TObj_Object::getAsciiString(const int theRank1,
                                                                  const int theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);

  occ::handle<TDataStd_AsciiString> aStrAttr;
  aLabel.FindAttribute(TDataStd_AsciiString::GetID(), aStrAttr);
  return aStrAttr.IsNull() ? nullptr : new TCollection_HAsciiString(aStrAttr->Get());
}

void TObj_Object::setAsciiString(const occ::handle<TCollection_HAsciiString>& theValue,
                                 const int                                    theRank1,
                                 const int                                    theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);
  if (!theValue.IsNull())
    TDataStd_AsciiString::Set(aLabel, theValue->String());
  else
    aLabel.ForgetAttribute(TDataStd_AsciiString::GetID());
}

int TObj_Object::getInteger(const int theRank1, const int theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);

  occ::handle<TDataStd_Integer> aNum;
  aLabel.FindAttribute(TDataStd_Integer::GetID(), aNum);
  return aNum.IsNull() ? 0 : aNum->Get();
}

bool TObj_Object::setInteger(const int theValue, const int theRank1, const int theRank2) const
{
  TDF_Label aLabel = getDataLabel(theRank1, theRank2);

  occ::handle<TDataStd_Integer> A;
  if (aLabel.FindAttribute(TDataStd_Integer::GetID(), A) && A->Get() == theValue)
    return false;

  TDataStd_Integer::Set(aLabel, theValue);
  return true;
}

occ::handle<TObj_Object> TObj_Object::getReference(const int theRank1, const int theRank2) const
{
  TDF_Label aLabel = getReferenceLabel(theRank1, theRank2);

  occ::handle<TObj_TReference> aRef;
  aLabel.FindAttribute(TObj_TReference::GetID(), aRef);
  return aRef.IsNull() ? occ::handle<TObj_Object>() : aRef->Get();
}

bool TObj_Object::setReference(const occ::handle<TObj_Object>& theObject,
                               const int                       theRank1,
                               const int                       theRank2)
{
  TDF_Label aLabel = getReferenceLabel(theRank1, theRank2);

  if (theObject.IsNull())
    return aLabel.ForgetAttribute(TObj_TReference::GetID());

  occ::handle<TObj_TReference> A;
  if (aLabel.FindAttribute(TObj_TReference::GetID(), A) && A->Get() == theObject)
    return false;

  aLabel.ForgetAttribute(TObj_TReference::GetID());

  occ::handle<TObj_Object> me = this;
  TObj_TReference::Set(aLabel, theObject, me);
  return true;
}

TDF_Label TObj_Object::addReference(const int theRank1, const occ::handle<TObj_Object>& theObject)
{
  TDF_Label aRefLabel = GetReferenceLabel();
  if (theRank1 > 0)
    aRefLabel = aRefLabel.FindChild(theRank1, true);

  TDF_TagSource aTag;
  TDF_Label     aLabel = TDF_TagSource::NewChild(aRefLabel);

  occ::handle<TObj_Object> me = this;
  TObj_TReference::Set(aLabel, theObject, me);
  return aLabel;
}

occ::handle<NCollection_HArray1<double>> TObj_Object::getRealArray(
  const int    theLength,
  const int    theRank1,
  const int    theRank2,
  const double theInitialValue) const
{
  TDF_Label                       aLabel = getDataLabel(theRank1, theRank2);
  occ::handle<TDataStd_RealArray> anArrAttribute;
  if (!aLabel.FindAttribute(TDataStd_RealArray::GetID(), anArrAttribute))
    if (theLength > 0)
    {
      anArrAttribute = TDataStd_RealArray::Set(aLabel, 1, theLength);
      anArrAttribute->Array()->Init(theInitialValue);
    }
  occ::handle<NCollection_HArray1<double>> anArr;
  if (!anArrAttribute.IsNull())
    anArr = anArrAttribute->Array();
  return anArr;
}

occ::handle<NCollection_HArray1<int>> TObj_Object::getIntegerArray(const int theLength,
                                                                   const int theRank1,
                                                                   const int theRank2,
                                                                   const int theInitialValue) const
{
  TDF_Label                          aLabel = getDataLabel(theRank1, theRank2);
  occ::handle<TDataStd_IntegerArray> anArrAttribute;
  if (!aLabel.FindAttribute(TDataStd_IntegerArray::GetID(), anArrAttribute))
    if (theLength > 0)
    {
      anArrAttribute = TDataStd_IntegerArray::Set(aLabel, 1, theLength);
      anArrAttribute->Array()->Init(theInitialValue);
    }
  occ::handle<NCollection_HArray1<int>> anArr;
  if (!anArrAttribute.IsNull())
    anArr = anArrAttribute->Array();
  return anArr;
}

occ::handle<NCollection_HArray1<TCollection_ExtendedString>> TObj_Object::getExtStringArray(
  const int theLength,
  const int theRank1,
  const int theRank2) const
{
  TDF_Label                            aLabel = getDataLabel(theRank1, theRank2);
  occ::handle<TDataStd_ExtStringArray> anArrAttribute;
  if (!aLabel.FindAttribute(TDataStd_ExtStringArray::GetID(), anArrAttribute))
    if (theLength > 0)
      anArrAttribute = TDataStd_ExtStringArray::Set(aLabel, 1, theLength);

  occ::handle<NCollection_HArray1<TCollection_ExtendedString>> anArr;
  if (!anArrAttribute.IsNull())
    anArr = anArrAttribute->Array();
  return anArr;
}

void TObj_Object::setArray(const occ::handle<NCollection_HArray1<double>>& theArray,
                           const int                                       theRank1,
                           const int                                       theRank2)
{
  TDF_Label                       aLabel = getDataLabel(theRank1, theRank2);
  occ::handle<TDataStd_RealArray> anArrAttribute;
  if (!aLabel.FindAttribute(TDataStd_RealArray::GetID(), anArrAttribute) && !theArray.IsNull())
    anArrAttribute = TDataStd_RealArray::Set(aLabel, 1, 1);

  if (theArray.IsNull())
  {

    if (!anArrAttribute.IsNull())
      aLabel.ForgetAttribute(anArrAttribute);
    return;
  }

  if (anArrAttribute->Array() == theArray)

    anArrAttribute->Init(1, 1);

  anArrAttribute->ChangeArray(theArray);
}

void TObj_Object::setArray(const occ::handle<NCollection_HArray1<int>>& theArray,
                           const int                                    theRank1,
                           const int                                    theRank2)
{
  TDF_Label                          aLabel = getDataLabel(theRank1, theRank2);
  occ::handle<TDataStd_IntegerArray> anArrAttribute;
  if (!aLabel.FindAttribute(TDataStd_IntegerArray::GetID(), anArrAttribute) && !theArray.IsNull())
    anArrAttribute = TDataStd_IntegerArray::Set(aLabel, 1, 1);

  if (theArray.IsNull())
  {

    if (!anArrAttribute.IsNull())
      aLabel.ForgetAttribute(anArrAttribute);
    return;
  }

  if (anArrAttribute->Array() == theArray)

    anArrAttribute->Init(1, 1);

  anArrAttribute->ChangeArray(theArray);
}

void TObj_Object::setArray(
  const occ::handle<NCollection_HArray1<TCollection_ExtendedString>>& theArray,
  const int                                                           theRank1,
  const int                                                           theRank2)
{
  TDF_Label                            aLabel = getDataLabel(theRank1, theRank2);
  occ::handle<TDataStd_ExtStringArray> anArrAttribute;
  if (!aLabel.FindAttribute(TDataStd_ExtStringArray::GetID(), anArrAttribute) && !theArray.IsNull())
    anArrAttribute = TDataStd_ExtStringArray::Set(aLabel, 1, 1);

  if (theArray.IsNull())
  {

    if (!anArrAttribute.IsNull())
      aLabel.ForgetAttribute(anArrAttribute);
    return;
  }

  if (anArrAttribute->Array() == theArray)

    anArrAttribute->Init(1, 1);

  anArrAttribute->ChangeArray(theArray);
}

static void copyTagSources(const TDF_Label& theSourceLabel, const TDF_Label& theTargetLabel)
{

  occ::handle<TDF_Attribute> anAttr;
  if (theSourceLabel.FindAttribute(TDF_TagSource::GetID(), anAttr))
  {
    occ::handle<TDF_TagSource> aTagSource       = occ::down_cast<TDF_TagSource>(anAttr);
    occ::handle<TDF_TagSource> aTargetTagSource = TDF_TagSource::Set(theTargetLabel);
    aTargetTagSource->Set(aTagSource->Get());
  }

  TDF_ChildIterator aLI(theTargetLabel);
  for (; aLI.More(); aLI.Next())
  {
    TDF_Label aSourceLabel = theSourceLabel.FindChild(aLI.Value().Tag(), false);
    if (!aSourceLabel.IsNull())
      copyTagSources(aSourceLabel, aLI.Value());
  }
}

occ::handle<TObj_Object> TObj_Object::Clone(const TDF_Label&                 theTargetLabel,
                                            occ::handle<TDF_RelocationTable> theRelocTable)
{
  occ::handle<TDF_RelocationTable> aRelocTable = theRelocTable;
  if (theRelocTable.IsNull())
    aRelocTable = new TDF_RelocationTable;
  occ::handle<TObj_Object> aNewObj;

  const occ::handle<TObj_Model>& aCurrentModel = TObj_Assistant::GetCurrentModel();

  occ::handle<TObj_Model>  aTargetModel;
  TDF_Label                aLabel = TDocStd_Document::Get(theTargetLabel)->Main();
  occ::handle<TObj_TModel> aModelAttr;
  if (aLabel.FindAttribute(TObj_TModel::GetID(), aModelAttr))
    aTargetModel = aModelAttr->Model();

  if (aCurrentModel != aTargetModel)
    TObj_Assistant::SetCurrentModel(aTargetModel);

  aNewObj = TObj_Persistence::CreateNewObject(DynamicType()->Name(), theTargetLabel);

  if (!aNewObj.IsNull())
  {
    TObj_TObject::Set(theTargetLabel, aNewObj);

    aRelocTable->SetRelocation(GetLabel(), theTargetLabel);

    const occ::handle<TCollection_HExtendedString> aCloneName = GetNameForClone(aNewObj);
    if (!aCloneName.IsNull() && !aCloneName->IsEmpty())
      aNewObj->SetName(new TCollection_HExtendedString(aCloneName));

    copyData(aNewObj);

    TDF_Label aTargetLabel = aNewObj->GetChildLabel();
    CopyChildren(aTargetLabel, aRelocTable);

    copyTagSources(GetChildLabel(), aTargetLabel);

    if (theRelocTable.IsNull())
      CopyReferences(aNewObj, aRelocTable);
  }

  if (aCurrentModel != aTargetModel)
    TObj_Assistant::SetCurrentModel(aCurrentModel);

  return aNewObj;
}

bool TObj_Object::copyData(const occ::handle<TObj_Object>& theTargetObject)
{
  bool IsDone = false;
  if (!theTargetObject->DynamicType()->SubType(DynamicType()))
    return IsDone;

  TDF_Label aDataLabel    = GetDataLabel();
  TDF_Label aNewDataLabel = theTargetObject->GetDataLabel();

  if (aDataLabel.IsNull() || aNewDataLabel.IsNull())
    return IsDone;

  TDF_CopyLabel aCopier(aDataLabel, aNewDataLabel);
  aCopier.Perform();

  return aCopier.IsDone();
}

void TObj_Object::CopyChildren(TDF_Label&                              theTargetLabel,
                               const occ::handle<TDF_RelocationTable>& theRelocTable)
{
  TDF_Label                        aSourceChildLabel = GetChildLabel();
  occ::handle<TObj_ObjectIterator> aChildren =

    new TObj_OcafObjectIterator(aSourceChildLabel, nullptr, true);

  for (; aChildren->More(); aChildren->Next())
  {
    occ::handle<TObj_Object> aChild = aChildren->Value();
    if (!aChild.IsNull())
    {

      NCollection_Sequence<int> aTags;
      TDF_Label                 aCurChildLab = aChild->GetLabel();
      while (!aCurChildLab.IsNull() && aCurChildLab != aSourceChildLabel)
      {
        aTags.Append(aCurChildLab.Tag());
        aCurChildLab = aCurChildLab.Father();
      }
      TDF_Label aChildLabel = theTargetLabel;
      for (int i = aTags.Length(); i > 0; i--)
        aChildLabel = aChildLabel.FindChild(aTags.Value(i), true);

      aChild->Clone(aChildLabel, theRelocTable);
    }
  }
}

void TObj_Object::CopyReferences(const occ::handle<TObj_Object>&         theTargetObject,
                                 const occ::handle<TDF_RelocationTable>& theRelocTable)
{

  occ::handle<TObj_ObjectIterator> aSrcChildren =

    new TObj_OcafObjectIterator(GetChildLabel(), nullptr, true);
  for (; aSrcChildren->More(); aSrcChildren->Next())
  {
    occ::handle<TObj_Object> aSrcChild = aSrcChildren->Value();
    TDF_Label                aSrcL     = aSrcChild->GetLabel();
    TDF_Label                aDestLabel;
    if (!theRelocTable->HasRelocation(aSrcL, aDestLabel))
      continue;
    occ::handle<TObj_Object> aDstChild;
    if (!TObj_Object::GetObj(aDestLabel, aDstChild))
      continue;
    if (aDstChild.IsNull() || !aDstChild->IsAlive()
        || aSrcChild->DynamicType() != aDstChild->DynamicType())
      continue;

    aSrcChild->CopyReferences(aDstChild, theRelocTable);
  }

  theTargetObject->GetReferenceLabel().ForgetAllAttributes(true);

  TDF_Label aTargetLabel = theTargetObject->GetReferenceLabel();
  copyReferences(GetReferenceLabel(), aTargetLabel, theRelocTable);
}

void TObj_Object::copyReferences(const TDF_Label&                        theSourceLabel,
                                 TDF_Label&                              theTargetLabel,
                                 const occ::handle<TDF_RelocationTable>& theRelocTable)
{
  TDF_AttributeIterator anIter(theSourceLabel);
  for (; anIter.More(); anIter.Next())
  {
    occ::handle<TDF_Attribute> anAttr = anIter.Value()->NewEmpty();
    theTargetLabel.AddAttribute(anAttr);
    anIter.Value()->Paste(anAttr, theRelocTable);
  }
  TDF_ChildIterator aLI(theSourceLabel);
  TDF_Label         aTargetLabel;
  for (; aLI.More(); aLI.Next())
  {
    aTargetLabel = theTargetLabel.FindChild(aLI.Value().Tag(), true);
    copyReferences(aLI.Value(), aTargetLabel, theRelocTable);
  }
}

void TObj_Object::ReplaceReference(const occ::handle<TObj_Object>& theOldObject,
                                   const occ::handle<TObj_Object>& theNewObject)
{
  occ::handle<TObj_LabelIterator> anItr = occ::down_cast<TObj_LabelIterator>(GetReferences());
  if (anItr.IsNull())
    return;

  for (; anItr->More(); anItr->Next())
  {
    occ::handle<TObj_Object> anObj = anItr->Value();
    if (anObj != theOldObject)
      continue;

    TDF_Label aRefLabel = anItr->LabelValue();

    if (theNewObject.IsNull())
    {
      aRefLabel.ForgetAllAttributes();
      break;
    }

    occ::handle<TObj_Object> me = this;
    TObj_TReference::Set(aRefLabel, theNewObject, me);
    break;
  }
}

bool TObj_Object::IsAlive() const
{
  if (myLabel.IsNull())
    return false;

  occ::handle<TObj_Object> anObj;
  return GetObj(myLabel, anObj);
}

int TObj_Object::GetFlags() const
{
  return getInteger(DataTag_Flags);
}

void TObj_Object::SetFlags(const int theMask)
{
  int aFlags = getInteger(DataTag_Flags);
  aFlags     = aFlags | theMask;
  setInteger(aFlags, DataTag_Flags);
}

bool TObj_Object::TestFlags(const int theMask) const
{
  int aFlags = getInteger(DataTag_Flags);
  return (aFlags & theMask) != 0;
}

void TObj_Object::ClearFlags(const int theMask)
{
  int aFlags = getInteger(DataTag_Flags);
  aFlags     = aFlags & (~theMask);
  setInteger(aFlags, DataTag_Flags);
}

bool TObj_Object::RemoveBackReferences(const TObj_DeletingMode theMode)
{
  occ::handle<TObj_ObjectIterator> aRefs = GetBackReferences();

  if (aRefs.IsNull() || !aRefs->More())
    return true;

  if (theMode == TObj_FreeOnly)
    return false;

  NCollection_Sequence<occ::handle<TObj_Object>> aContainers;
  NCollection_Sequence<occ::handle<TObj_Object>> aStrongs;
  occ::handle<TObj_Object>                       aMe = this;

  for (; aRefs->More(); aRefs->Next())
  {
    occ::handle<TObj_Object> anObject = aRefs->Value();
    if (anObject.IsNull() || !anObject->IsAlive())
      continue;
    if (anObject->CanRemoveReference(aMe))
      aContainers.Append(anObject);
    else
      aStrongs.Append(anObject);
  }

  if (theMode == TObj_KeepDepending && aStrongs.Length() > 0)
    return false;

  int                   i;
  occ::handle<TDF_Data> anOwnData = GetLabel().Data();
  for (i = 1; i <= aContainers.Length(); i++)
  {
    occ::handle<TObj_Object> anObj = aContainers(i);
    if (anObj.IsNull() || anObj->GetLabel().IsNull())
      continue;
    occ::handle<TDF_Data> aData      = anObj->GetLabel().Data();
    bool                  aModifMode = aData->IsModificationAllowed();
    if (anOwnData != aData)
      aData->AllowModification(true);
    anObj->RemoveReference(aMe);
    if (anOwnData != aData)
      aData->AllowModification(aModifMode);
  }

  for (i = 1; i <= aStrongs.Length(); i++)
  {
    occ::handle<TObj_Object> anObj = aStrongs(i);
    if (anObj.IsNull() || anObj->GetLabel().IsNull())
      continue;
    occ::handle<TDF_Data> aData      = anObj->GetLabel().Data();
    bool                  aModifMode = aData->IsModificationAllowed();
    if (anOwnData != aData)
      aData->AllowModification(true);
    anObj->Detach(theMode);
    if (anOwnData != aData)
      aData->AllowModification(aModifMode);
  }

  return true;
}

bool TObj_Object::RelocateReferences(const TDF_Label& theFromRoot,
                                     const TDF_Label& theToRoot,
                                     const bool       theUpdateBackRefs)
{
  TDF_ChildIDIterator      aRefIt(GetReferenceLabel(), TObj_TReference::GetID(), true);
  occ::handle<TObj_Object> anObj;
  for (; aRefIt.More(); aRefIt.Next())
  {
    occ::handle<TObj_TReference> aRef = occ::down_cast<TObj_TReference>(aRefIt.Value());

    TDF_Label aNewLabel, aLabel = aRef->GetLabel();
    if (aLabel.Data() != theFromRoot.Data() || aLabel.IsDescendant(theToRoot))
      continue;

    TDF_Tool::RelocateLabel(aLabel, theFromRoot, theToRoot, aNewLabel);
    if (aNewLabel.IsNull() || !TObj_Object::GetObj(aNewLabel, anObj))
      return false;

    if (theUpdateBackRefs)
    {
      occ::handle<TObj_Object> me = this;

      anObj->AddBackReference(me);

      anObj = aRef->Get();
      if (!anObj.IsNull())
        anObj->RemoveBackReference(me);
    }

    aRef->Set(aNewLabel, aRef->GetMasterLabel());
  }

  return true;
}

bool TObj_Object::GetBadReference(const TDF_Label& theRoot, TDF_Label& theBadReference) const
{
  TDF_ChildIDIterator      aRefIt(GetReferenceLabel(), TObj_TReference::GetID(), true);
  occ::handle<TObj_Object> anObj;
  for (; aRefIt.More(); aRefIt.Next())
  {
    occ::handle<TObj_TReference> aRef = occ::down_cast<TObj_TReference>(aRefIt.Value());

    TDF_Label aLabel = aRef->GetLabel();
    if (aLabel.Data() == theRoot.Data() && !aLabel.IsDescendant(theRoot))
    {
      theBadReference = aLabel;
      return true;
    }
  }

  return false;
}

int TObj_Object::GetTypeFlags() const
{
  return Visible;
}

occ::handle<TObj_TNameContainer> TObj_Object::GetDictionary() const
{
  occ::handle<TObj_Model> aModel = GetModel();
  if (!aModel.IsNull())
    return aModel->GetDictionary();
  return nullptr;
}

bool TObj_Object::SetOrder(const int& theIndx)
{
  setInteger(theIndx, DataTag_Order);
  return true;
}

int TObj_Object::GetOrder() const
{
  int order = getInteger(DataTag_Order);
  if (!order)
    order = GetLabel().Tag();
  return order;
}

bool TObj_Object::HasModifications() const
{
  return (!IsAlive() ? false : GetLabel().MayBeModified());
}
