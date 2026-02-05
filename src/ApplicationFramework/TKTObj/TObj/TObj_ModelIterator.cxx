#include <TObj_ModelIterator.hpp>

#include <TObj_Model.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_ModelIterator, TObj_ObjectIterator)

//=================================================================================================

TObj_ModelIterator::TObj_ModelIterator(const occ::handle<TObj_Model>& theModel)
{
  myObject = theModel->GetRoot();
  if (!myObject.IsNull())
    addIterator(myObject);
}

//=================================================================================================

void TObj_ModelIterator::addIterator(const occ::handle<TObj_Object>& theObj)
{
  occ::handle<TObj_ObjectIterator> anIter = theObj->GetChildren();
  if (anIter.IsNull())
    return; // object has no children.
  myIterSeq.Append(anIter);
}

//=================================================================================================

bool TObj_ModelIterator::More() const
{
  return !myObject.IsNull();
}

//=================================================================================================

occ::handle<TObj_Object> TObj_ModelIterator::Value() const
{
  return myObject;
}

//=================================================================================================

void TObj_ModelIterator::Next()
{
  myObject.Nullify();
  while (myIterSeq.Length() > 0)
  {
    if (myIterSeq.Last()->More())
    {
      myObject = myIterSeq.Last()->Value();
      myIterSeq.Last()->Next();
      addIterator(myObject);
      return;
    }
    else
      myIterSeq.Remove(myIterSeq.Length());
  }
}
