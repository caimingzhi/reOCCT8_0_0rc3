#include <TObj_OcafObjectIterator.hpp>
#include <TObj_Object.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_OcafObjectIterator, TObj_LabelIterator)

//=================================================================================================

TObj_OcafObjectIterator::TObj_OcafObjectIterator(const TDF_Label&                  theLabel,
                                                 const occ::handle<Standard_Type>& theType,
                                                 const bool                        theRecursive,
                                                 const bool theAllSubChildren)
    : TObj_LabelIterator(theLabel, theRecursive),
      myType(theType),
      myAllSubChildren(theAllSubChildren)
{
  MakeStep();
}

//=================================================================================================

void TObj_OcafObjectIterator::MakeStep()
{
  for (; myIterator.More() && myNode.IsNull();)
  {
    TDF_Label                L = myIterator.Value();
    occ::handle<TObj_Object> anObject;
    if (TObj_Object::GetObj(L, anObject))
    {
      if (myType.IsNull() || anObject->IsKind(myType))
      {
        myObject = anObject;
        myNode   = L;
      }
      myAllSubChildren ? myIterator.Next() : myIterator.NextBrother();
    }
    else
      myIterator.Next();
  }
}
