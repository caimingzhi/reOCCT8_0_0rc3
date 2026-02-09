#pragma once

#include <OpenGl_Buffer.hpp>

class OpenGl_UniformBuffer : public OpenGl_Buffer
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_UniformBuffer, OpenGl_Buffer)
public:
  Standard_EXPORT OpenGl_UniformBuffer();

  Standard_EXPORT unsigned int GetTarget() const override;

  using OpenGl_Buffer::BindBufferBase;
  using OpenGl_Buffer::BindBufferRange;
  using OpenGl_Buffer::UnbindBufferBase;
};
