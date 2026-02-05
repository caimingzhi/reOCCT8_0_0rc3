#include <OpenGl_IndexBuffer.hpp>

#include <OpenGl_Context.hpp>
#include <OpenGl_GlCore15.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_IndexBuffer, OpenGl_Buffer)

//=================================================================================================

OpenGl_IndexBuffer::OpenGl_IndexBuffer()

  = default;

//=================================================================================================

unsigned int OpenGl_IndexBuffer::GetTarget() const
{
  return GL_ELEMENT_ARRAY_BUFFER;
}

//=================================================================================================

void OpenGl_IndexBuffer::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, OpenGl_Buffer)
}
