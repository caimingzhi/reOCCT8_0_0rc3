#include <TObj_TObject.hpp>

#include <Standard_GUID.hpp>
#include <TDF_AttributeDelta.hpp>
#include <TDF_ChildIterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_TObject, TDF_Attribute)

TObj_TObject::TObj_TObject() = default;

const Standard_GUID& TObj_TObject::GetID()
{
  static Standard_GUID GInterfaceID("bbdab6a7-dca9-11d4-ba37-0060b0ee18ea");
  return GInterfaceID;
}

const Standard_GUID& TObj_TObject::ID() const
{
  return GetID();
}

void TObj_TObject::Set(const occ::handle<TObj_Object>& theElem)
{
  Backup();
  myElem = theElem;
}

occ::handle<TObj_TObject> TObj_TObject::Set(const TDF_Label&                theLabel,
                                            const occ::handle<TObj_Object>& theElem)
{
  occ::handle<TObj_TObject> A;
  if (!theLabel.FindAttribute(TObj_TObject::GetID(), A))
  {
    A = new TObj_TObject;
    theLabel.AddAttribute(A);
  }
  A->Set(theElem);
  return A;
}

occ::handle<TObj_Object> TObj_TObject::Get() const
{
  return myElem;
}

occ::handle<TDF_Attribute> TObj_TObject::NewEmpty() const
{
  return new TObj_TObject();
}

void TObj_TObject::Restore(const occ::handle<TDF_Attribute>& theWith)
{
  occ::handle<TObj_TObject> R = occ::down_cast<TObj_TObject>(theWith);
  myElem                      = R->Get();
}

void TObj_TObject::Paste(const occ::handle<TDF_Attribute>& theInto,
                         const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TObj_TObject> R = occ::down_cast<TObj_TObject>(theInto);
  R->Set(myElem);
}

void TObj_TObject::BeforeForget()
{
  if (!myElem.IsNull())
  {

    TDF_Label aObjLabel = myElem->myLabel;
    if (!aObjLabel.IsNull())
    {
      TDF_ChildIterator aLI(aObjLabel);
      TDF_Label         aSubLabel;
      for (; aLI.More(); aLI.Next())
      {
        aSubLabel = aLI.Value();
        if (!aSubLabel.IsNull())
          aSubLabel.ForgetAllAttributes(true);
      }
    }

    myElem->RemoveBackReferences(TObj_Forced);
    TDF_Label aNullLabel;
    myElem->myLabel = aNullLabel;
  }
}

bool TObj_TObject::AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta, const bool)
{
  if (!myElem.IsNull())
  {
    TDF_Label                  aLabel = anAttDelta->Label();
    occ::handle<TDF_Attribute> anAttr;
    occ::handle<TObj_TObject>  aTObject;
    occ::handle<TDF_Attribute> me;
    me = this;
    if (!aLabel.IsNull() && aLabel.FindAttribute(GetID(), anAttr))
      aTObject = occ::down_cast<TObj_TObject>(anAttr);

    if (!aTObject.IsNull() && aTObject->Get() == myElem)
      myElem->myLabel = aLabel;
    else
    {
      TDF_Label aNullLabel;
      myElem->myLabel = aNullLabel;
    }
  }
  return true;
}
