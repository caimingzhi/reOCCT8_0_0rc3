#pragma once

#include <OpenGl_Buffer.hpp>

//! Index buffer is just a VBO with special target (GL_ELEMENT_ARRAY_BUFFER).
class OpenGl_IndexBuffer : public OpenGl_Buffer
{
public:
  //! Empty constructor.
  Standard_EXPORT OpenGl_IndexBuffer();

  //! Return buffer object target (GL_ELEMENT_ARRAY_BUFFER).
  Standard_EXPORT unsigned int GetTarget() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_IndexBuffer, OpenGl_Buffer)
};
