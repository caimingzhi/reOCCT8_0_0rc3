#pragma once


#include <Graphic3d_Buffer.hpp>

//! Index buffer.
class Graphic3d_IndexBuffer : public Graphic3d_Buffer
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_IndexBuffer, Graphic3d_Buffer)
public:
  //! Empty constructor.
  Graphic3d_IndexBuffer(const occ::handle<NCollection_BaseAllocator>& theAlloc)
      : Graphic3d_Buffer(theAlloc)
  {
  }

  //! Allocates new empty index array
  template <typename IndexType_t>
  bool Init(const int theNbElems)
  {
    release();
    Stride = sizeof(IndexType_t);
    if (Stride != sizeof(unsigned short) && Stride != sizeof(unsigned int))
    {
      return false;
    }

    NbElements   = theNbElems;
    NbAttributes = 0;
    if (NbElements != 0 && !Allocate(size_t(Stride) * size_t(NbElements)))
    {
      release();
      return false;
    }
    return true;
  }

  //! Allocates new empty index array
  bool InitInt32(const int theNbElems) { return Init<int>(theNbElems); }

  //! Access index at specified position
  int Index(const int theIndex) const
  {
    return Stride == sizeof(unsigned short) ? int(Value<unsigned short>(theIndex))
                                            : int(Value<unsigned int>(theIndex));
  }

  //! Change index at specified position
  void SetIndex(const int theIndex, const int theValue)
  {
    if (Stride == sizeof(unsigned short))
    {
      ChangeValue<unsigned short>(theIndex) = (unsigned short)theValue;
    }
    else
    {
      ChangeValue<unsigned int>(theIndex) = (unsigned int)theValue;
    }
  }

  //! Dumps the content of me into the stream
  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override
  {
    OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
    OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Graphic3d_Buffer)
  }
};

