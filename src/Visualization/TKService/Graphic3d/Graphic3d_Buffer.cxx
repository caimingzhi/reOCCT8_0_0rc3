

#include <Graphic3d_Buffer.hpp>

#include <Graphic3d_BoundBuffer.hpp>
#include <Graphic3d_MutableIndexBuffer.hpp>
#include <NCollection_AlignedAllocator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_Buffer, NCollection_Buffer)
IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_IndexBuffer, Graphic3d_Buffer)
IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_BoundBuffer, NCollection_Buffer)
IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_MutableIndexBuffer, Graphic3d_IndexBuffer)

const occ::handle<NCollection_BaseAllocator>& Graphic3d_Buffer::DefaultAllocator()
{
  static const occ::handle<NCollection_BaseAllocator> THE_ALLOC =
    new NCollection_AlignedAllocator(16);
  return THE_ALLOC;
}

void Graphic3d_Buffer::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, NCollection_Buffer)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Stride)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, NbElements)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, NbAttributes)
}
