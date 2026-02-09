#pragma once

#include <Graphic3d_Buffer.hpp>

class Graphic3d_AttribBuffer : public Graphic3d_Buffer
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AttribBuffer, Graphic3d_Buffer)
public:
  Standard_EXPORT Graphic3d_AttribBuffer(const occ::handle<NCollection_BaseAllocator>& theAlloc);

  Standard_EXPORT bool Init(const int                  theNbElems,
                            const Graphic3d_Attribute* theAttribs,
                            const int                  theNbAttribs);

  bool Init(const int theNbElems, const NCollection_Array1<Graphic3d_Attribute>& theAttribs)
  {
    return Init(theNbElems, &theAttribs.First(), theAttribs.Size());
  }

  bool IsMutable() const override { return myIsMutable; }

  Standard_EXPORT void SetMutable(bool theMutable);

  bool IsInterleaved() const override { return myIsInterleaved; }

  Standard_EXPORT void SetInterleaved(bool theIsInterleaved);

  Graphic3d_BufferRange InvalidatedRange() const override { return myInvalidatedRange; }

  void Validate() override { myInvalidatedRange.Clear(); }

  Standard_EXPORT void Invalidate() override;

  Standard_EXPORT void Invalidate(int theAttributeIndex);

  Standard_EXPORT void Invalidate(int theAttributeIndex, int theVertexLower, int theVertexUpper);

  Standard_EXPORT void Invalidate(int theVertexLower, int theVertexUpper);

  Standard_EXPORT void invalidate(const Graphic3d_BufferRange& theRange);

protected:
  Graphic3d_BufferRange myInvalidatedRange;

  bool myIsInterleaved;

  bool myIsMutable;
};
