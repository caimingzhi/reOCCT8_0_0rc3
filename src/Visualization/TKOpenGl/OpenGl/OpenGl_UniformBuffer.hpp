#pragma once


#include <OpenGl_Buffer.hpp>

//! Uniform buffer object.
class OpenGl_UniformBuffer : public OpenGl_Buffer
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_UniformBuffer, OpenGl_Buffer)
public:
  //! Empty constructor.
  Standard_EXPORT OpenGl_UniformBuffer();

  //! Return buffer object target (GL_UNIFORM_BUFFER).
  Standard_EXPORT unsigned int GetTarget() const override;

  using OpenGl_Buffer::BindBufferBase;
  using OpenGl_Buffer::BindBufferRange;
  using OpenGl_Buffer::UnbindBufferBase;
};

