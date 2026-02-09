

#include <Graphic3d_SequenceOfHClipPlane.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_SequenceOfHClipPlane, Standard_Transient)

Graphic3d_SequenceOfHClipPlane::Graphic3d_SequenceOfHClipPlane()
    : myToOverrideGlobal(false)
{
}

bool Graphic3d_SequenceOfHClipPlane::Append(const occ::handle<Graphic3d_ClipPlane>& theItem)
{
  for (NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator anItemIter(myItems);
       anItemIter.More();
       anItemIter.Next())
  {
    if (anItemIter.Value() == theItem)
    {
      return false;
    }
  }
  myItems.Append(theItem);
  return true;
}

bool Graphic3d_SequenceOfHClipPlane::Remove(const occ::handle<Graphic3d_ClipPlane>& theItem)
{
  for (NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator anItemIter(myItems);
       anItemIter.More();
       anItemIter.Next())
  {
    if (anItemIter.Value() == theItem)
    {
      myItems.Remove(anItemIter);
      return true;
    }
  }
  return false;
}

void Graphic3d_SequenceOfHClipPlane::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToOverrideGlobal)

  for (NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator anIterator(myItems);
       anIterator.More();
       anIterator.Next())
  {
    const occ::handle<Graphic3d_ClipPlane>& aClipPlane = anIterator.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aClipPlane.get())
  }
}
