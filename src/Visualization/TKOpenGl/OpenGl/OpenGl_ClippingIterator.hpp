#pragma once

#include <OpenGl_Clipping.hpp>

class OpenGl_ClippingIterator
{
public:
  OpenGl_ClippingIterator(const OpenGl_Clipping& theClipping)
      : myDisabled(&theClipping.myDisabledPlanes),
        myCurrIndex(1)
  {
    myIter1.Init(theClipping.myPlanesGlobal);
    myIter2.Init(theClipping.myPlanesLocal);
  }

  bool More() const { return myIter1.More() || myIter2.More(); }

  void Next()
  {
    ++myCurrIndex;
    if (myIter1.More())
    {
      myIter1.Next();
    }
    else
    {
      myIter2.Next();
    }
  }

  bool IsDisabled() const { return myDisabled->Value(myCurrIndex) || !Value()->IsOn(); }

  const occ::handle<Graphic3d_ClipPlane>& Value() const
  {
    return myIter1.More() ? myIter1.Value() : myIter2.Value();
  }

  bool IsGlobal() const { return myIter1.More(); }

  int PlaneIndex() const { return myCurrIndex; }

private:
  Graphic3d_SequenceOfHClipPlane::Iterator myIter1;
  Graphic3d_SequenceOfHClipPlane::Iterator myIter2;
  const NCollection_Vector<bool>*          myDisabled;
  int                                      myCurrIndex;
};
