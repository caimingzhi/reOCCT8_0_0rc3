#pragma once

#include <Graphic3d_IndexBuffer.hpp>

class Graphic3d_MutableIndexBuffer : public Graphic3d_IndexBuffer
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_MutableIndexBuffer, Graphic3d_IndexBuffer)
public:
  Graphic3d_MutableIndexBuffer(const occ::handle<NCollection_BaseAllocator>& theAlloc)
      : Graphic3d_IndexBuffer(theAlloc)
  {
  }

  bool IsMutable() const override { return true; }

  Graphic3d_BufferRange InvalidatedRange() const override { return myInvalidatedRange; }

  void Validate() override { myInvalidatedRange.Clear(); }

  void Invalidate() override { invalidate(Graphic3d_BufferRange(0, (int)mySize)); }

  void Invalidate(int theIndexLower, int theIndexUpper)
  {
    Standard_OutOfRange_Raise_if(theIndexLower > theIndexUpper,
                                 "Graphic3d_MutableIndexBuffer::Invalidate()");
    invalidate(
      Graphic3d_BufferRange(Stride * theIndexLower, Stride * (theIndexUpper - theIndexLower + 1)));
  }

  void invalidate(const Graphic3d_BufferRange& theRange) { myInvalidatedRange.Unite(theRange); }

protected:
  Graphic3d_BufferRange myInvalidatedRange;
};
