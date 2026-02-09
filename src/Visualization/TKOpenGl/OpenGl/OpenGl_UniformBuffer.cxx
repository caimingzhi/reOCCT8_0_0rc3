

#include <OpenGl_UniformBuffer.hpp>

#include <OpenGl_GlCore15.hpp>
#include <Standard_Assert.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_UniformBuffer, OpenGl_Buffer)

OpenGl_UniformBuffer::OpenGl_UniformBuffer()

  = default;

unsigned int OpenGl_UniformBuffer::GetTarget() const
{
  return GL_UNIFORM_BUFFER;
}
