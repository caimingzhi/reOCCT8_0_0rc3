#pragma once

#include <Standard_Type.hpp>

class OpenGl_Context;

class OpenGl_Resource : public Standard_Transient
{

public:
  Standard_EXPORT OpenGl_Resource();

  Standard_EXPORT ~OpenGl_Resource() override;

  Standard_EXPORT virtual void Release(OpenGl_Context* theGlCtx) = 0;

  virtual size_t EstimatedDataSize() const = 0;

  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theOStream;
    (void)theDepth;
  };

private:
  OpenGl_Resource(const OpenGl_Resource&)            = delete;
  OpenGl_Resource& operator=(const OpenGl_Resource&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_Resource, Standard_Transient)
};
