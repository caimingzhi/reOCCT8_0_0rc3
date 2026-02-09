#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <Standard_Integer.hpp>

struct Graphic3d_BufferRange
{
  int Start;
  int Length;

  Graphic3d_BufferRange()
      : Start(0),
        Length(0)
  {
  }

  Graphic3d_BufferRange(int theStart, int theLength)
      : Start(theStart),
        Length(theLength)
  {
  }

  bool IsEmpty() const { return Length == 0; }

  int Upper() const { return Start + Length - 1; }

  void Clear()
  {
    Start  = 0;
    Length = 0;
  }

  void Unite(const Graphic3d_BufferRange& theRange)
  {
    if (IsEmpty())
    {
      *this = theRange;
      return;
    }
    else if (theRange.IsEmpty())
    {
      return;
    }

    const int aStart = (std::min)(Start, theRange.Start);
    const int aLast  = (std::max)(Upper(), theRange.Upper());
    Start            = aStart;
    Length           = aLast - aStart + 1;
  }
};

#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Buffer.hpp>
#include <Standard_NotImplemented.hpp>

enum Graphic3d_TypeOfAttribute
{
  Graphic3d_TOA_POS = 0,
  Graphic3d_TOA_NORM,
  Graphic3d_TOA_UV,
  Graphic3d_TOA_COLOR,
  Graphic3d_TOA_CUSTOM,
};

enum Graphic3d_TypeOfData
{
  Graphic3d_TOD_USHORT,
  Graphic3d_TOD_UINT,
  Graphic3d_TOD_VEC2,
  Graphic3d_TOD_VEC3,
  Graphic3d_TOD_VEC4,
  Graphic3d_TOD_VEC4UB,
  Graphic3d_TOD_FLOAT,
};

struct Graphic3d_Attribute
{

  Graphic3d_TypeOfAttribute Id;

  Graphic3d_TypeOfData DataType;

  int Stride() const { return Stride(DataType); }

  static int Stride(const Graphic3d_TypeOfData theType)
  {
    switch (theType)
    {
      case Graphic3d_TOD_USHORT:
        return sizeof(unsigned short);
      case Graphic3d_TOD_UINT:
        return sizeof(unsigned int);
      case Graphic3d_TOD_VEC2:
        return sizeof(NCollection_Vec2<float>);
      case Graphic3d_TOD_VEC3:
        return sizeof(NCollection_Vec3<float>);
      case Graphic3d_TOD_VEC4:
        return sizeof(NCollection_Vec4<float>);
      case Graphic3d_TOD_VEC4UB:
        return sizeof(NCollection_Vec4<uint8_t>);
      case Graphic3d_TOD_FLOAT:
        return sizeof(float);
    }
    return 0;
  }
};

class Graphic3d_Buffer : public NCollection_Buffer
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Buffer, NCollection_Buffer)
public:
  Standard_EXPORT static const occ::handle<NCollection_BaseAllocator>& DefaultAllocator();

public:
  Graphic3d_Buffer(const occ::handle<NCollection_BaseAllocator>& theAlloc)
      : NCollection_Buffer(theAlloc),
        Stride(0),
        NbElements(0),
        NbAttributes(0)
  {
  }

  int NbMaxElements() const { return Stride != 0 ? int(mySize / size_t(Stride)) : 0; }

  const Graphic3d_Attribute* AttributesArray() const
  {
    return (Graphic3d_Attribute*)(myData + mySize);
  }

  const Graphic3d_Attribute& Attribute(const int theAttribIndex) const
  {
    return AttributesArray()[theAttribIndex];
  }

  Graphic3d_Attribute& ChangeAttribute(const int theAttribIndex)
  {
    return *((Graphic3d_Attribute*)(myData + mySize) + theAttribIndex);
  }

  int FindAttribute(Graphic3d_TypeOfAttribute theAttrib) const
  {
    for (int anAttribIter = 0; anAttribIter < NbAttributes; ++anAttribIter)
    {
      const Graphic3d_Attribute& anAttrib = Attribute(anAttribIter);
      if (anAttrib.Id == theAttrib)
      {
        return anAttribIter;
      }
    }
    return -1;
  }

public:
  int AttributeOffset(const int theAttribIndex) const
  {
    int anOffset = 0;
    for (int anAttribIter = 0; anAttribIter < theAttribIndex; ++anAttribIter)
    {
      anOffset += Graphic3d_Attribute::Stride(Attribute(anAttribIter).DataType);
    }
    return anOffset;
  }

  const uint8_t* Data(const int theAttribIndex) const
  {
    return myData + AttributeOffset(theAttribIndex);
  }

  uint8_t* ChangeData(const int theAttribIndex) { return myData + AttributeOffset(theAttribIndex); }

  inline const uint8_t* value(const int theElem) const { return myData + Stride * size_t(theElem); }

  inline uint8_t* changeValue(const int theElem) { return myData + Stride * size_t(theElem); }

  template <typename Type_t>
  inline const Type_t& Value(const int theElem) const
  {
    return *reinterpret_cast<const Type_t*>(value(theElem));
  }

  template <typename Type_t>
  inline Type_t& ChangeValue(const int theElem)
  {
    return *reinterpret_cast<Type_t*>(changeValue(theElem));
  }

public:
  using NCollection_Buffer::ChangeData;
  using NCollection_Buffer::Data;

  uint8_t* ChangeAttributeData(Graphic3d_TypeOfAttribute theAttrib,
                               int&                      theAttribIndex,
                               size_t&                   theAttribStride)
  {
    return (uint8_t*)AttributeData(theAttrib, theAttribIndex, theAttribStride);
  }

  const uint8_t* AttributeData(Graphic3d_TypeOfAttribute theAttrib,
                               int&                      theAttribIndex,
                               size_t&                   theAttribStride) const
  {
    const uint8_t* aDataPtr = Data();
    if (IsInterleaved())
    {
      for (int anAttribIter = 0; anAttribIter < NbAttributes; ++anAttribIter)
      {
        const Graphic3d_Attribute& anAttrib       = Attribute(anAttribIter);
        const size_t               anAttribStride = Graphic3d_Attribute::Stride(anAttrib.DataType);
        if (anAttrib.Id == theAttrib)
        {
          theAttribIndex  = anAttribIter;
          theAttribStride = Stride;
          return aDataPtr;
        }

        aDataPtr += anAttribStride;
      }
    }
    else
    {
      const int aNbMaxVerts = NbMaxElements();
      for (int anAttribIter = 0; anAttribIter < NbAttributes; ++anAttribIter)
      {
        const Graphic3d_Attribute& anAttrib       = Attribute(anAttribIter);
        const size_t               anAttribStride = Graphic3d_Attribute::Stride(anAttrib.DataType);
        if (anAttrib.Id == theAttrib)
        {
          theAttribIndex  = anAttribIter;
          theAttribStride = anAttribStride;
          return aDataPtr;
        }

        aDataPtr += anAttribStride * aNbMaxVerts;
      }
    }
    return nullptr;
  }

public:
  void release()
  {
    Free();
    Stride       = 0;
    NbElements   = 0;
    NbAttributes = 0;
  }

  bool Init(const int theNbElems, const Graphic3d_Attribute* theAttribs, const int theNbAttribs)
  {
    release();
    int aStride = 0;
    for (int anAttribIter = 0; anAttribIter < theNbAttribs; ++anAttribIter)
    {
      const Graphic3d_Attribute& anAttrib = theAttribs[anAttribIter];
      aStride += anAttrib.Stride();
    }
    if (aStride == 0)
    {
      return false;
    }

    Stride       = aStride;
    NbElements   = theNbElems;
    NbAttributes = theNbAttribs;
    if (NbElements != 0)
    {
      const size_t aDataSize = size_t(Stride) * size_t(NbElements);
      if (!Allocate(aDataSize + sizeof(Graphic3d_Attribute) * NbAttributes))
      {
        release();
        return false;
      }

      mySize = aDataSize;
      for (int anAttribIter = 0; anAttribIter < theNbAttribs; ++anAttribIter)
      {
        ChangeAttribute(anAttribIter) = theAttribs[anAttribIter];
      }
    }
    return true;
  }

  bool Init(const int theNbElems, const NCollection_Array1<Graphic3d_Attribute>& theAttribs)
  {
    return Init(theNbElems, &theAttribs.First(), theAttribs.Size());
  }

public:
  virtual bool IsInterleaved() const { return true; }

  virtual bool IsMutable() const { return false; }

  virtual Graphic3d_BufferRange InvalidatedRange() const { return Graphic3d_BufferRange(); }

  virtual void Validate() {}

  virtual void Invalidate() {}

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  int Stride;
  int NbElements;

  int NbAttributes;
};
