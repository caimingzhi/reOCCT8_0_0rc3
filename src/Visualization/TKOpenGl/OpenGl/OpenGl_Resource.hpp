#pragma once

#include <Standard_Type.hpp>

class OpenGl_Context;

//! Interface for OpenGl resource with following meaning:
//!  - object can be constructed at any time;
//!  - should be explicitly Initialized within active OpenGL context;
//!  - should be explicitly Released    within active OpenGL context (virtual Release() method);
//!  - can be destroyed at any time.
//! Destruction of object with unreleased GPU resources will cause leaks
//! which will be ignored in release mode and will immediately stop program execution in debug mode
//! using assert.
class OpenGl_Resource : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT OpenGl_Resource();

  //! Destructor. Inheritors should call Clean (NULL) within it.
  Standard_EXPORT ~OpenGl_Resource() override;

  //! Release GPU resources.
  //! Notice that implementation should be SAFE for several consecutive calls
  //! (thus should invalidate internal structures / ids to avoid multiple-free errors).
  //! @param theGlCtx - bound GL context, shouldn't be NULL.
  Standard_EXPORT virtual void Release(OpenGl_Context* theGlCtx) = 0;

  //! Returns estimated GPU memory usage for holding data without considering overheads and
  //! allocation alignment rules.
  virtual size_t EstimatedDataSize() const = 0;

  //! Dumps the content of me into the stream
  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    (void)theOStream;
    (void)theDepth;
  };

private:
  //! Copy should be performed only within Handles!
  OpenGl_Resource(const OpenGl_Resource&)            = delete;
  OpenGl_Resource& operator=(const OpenGl_Resource&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_Resource, Standard_Transient) // Type definition
};
