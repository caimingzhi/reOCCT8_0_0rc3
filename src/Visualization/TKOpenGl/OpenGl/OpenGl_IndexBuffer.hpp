#pragma once

#include <OpenGl_Buffer.hpp>

class OpenGl_IndexBuffer : public OpenGl_Buffer
{
public:
  Standard_EXPORT OpenGl_IndexBuffer();

  Standard_EXPORT unsigned int GetTarget() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_IndexBuffer, OpenGl_Buffer)
};
