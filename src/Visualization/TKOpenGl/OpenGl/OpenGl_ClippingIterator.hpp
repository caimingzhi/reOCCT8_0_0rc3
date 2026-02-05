#pragma once

#include <OpenGl_Clipping.hpp>

//! The iterator through clipping planes.
class OpenGl_ClippingIterator
{
public:
  //! Main constructor.
  OpenGl_ClippingIterator(const OpenGl_Clipping& theClipping)
      : myDisabled(&theClipping.myDisabledPlanes),
        myCurrIndex(1)
  {
    myIter1.Init(theClipping.myPlanesGlobal);
    myIter2.Init(theClipping.myPlanesLocal);
  }

  //! Return true if iterator points to the valid clipping plane.
  bool More() const { return myIter1.More() || myIter2.More(); }

  //! Go to the next clipping plane.
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

  //! Return true if plane has been temporarily disabled either by Graphic3d_ClipPlane->IsOn()
  //! property or by temporary filter. Beware that this method does NOT handle a Chain filter for
  //! Capping algorithm OpenGl_Clipping::CappedChain()!
  bool IsDisabled() const { return myDisabled->Value(myCurrIndex) || !Value()->IsOn(); }

  //! Return the plane at current iterator position.
  const occ::handle<Graphic3d_ClipPlane>& Value() const
  {
    return myIter1.More() ? myIter1.Value() : myIter2.Value();
  }

  //! Return true if plane from the global (view) list.
  bool IsGlobal() const { return myIter1.More(); }

  //! Return the plane index.
  int PlaneIndex() const { return myCurrIndex; }

private:
  Graphic3d_SequenceOfHClipPlane::Iterator myIter1;
  Graphic3d_SequenceOfHClipPlane::Iterator myIter2;
  const NCollection_Vector<bool>*          myDisabled;
  int                                      myCurrIndex;
};
