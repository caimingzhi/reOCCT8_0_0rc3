#include <TObj_ReferenceIterator.hpp>
#include <TObj_TReference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_ReferenceIterator, TObj_LabelIterator)

//=================================================================================================

TObj_ReferenceIterator::TObj_ReferenceIterator(const TDF_Label&                  theLabel,
                                               const occ::handle<Standard_Type>& theType,
                                               const bool                        theRecursive)
    : TObj_LabelIterator(theLabel, theRecursive),
      myType(theType)
{
  MakeStep();
}

//=================================================================================================

void TObj_ReferenceIterator::MakeStep()
{
  for (; myIterator.More() && myNode.IsNull(); myIterator.Next())
  {
    TDF_Label L = myIterator.Value();

    occ::handle<TObj_TReference> A;
    if (L.FindAttribute(TObj_TReference::GetID(), A))
    {
      myObject = A->Get();
      if (!myType.IsNull() && !myObject.IsNull() && !myObject->IsKind(myType))
        continue;

      myNode = L;
    }
  }
}
