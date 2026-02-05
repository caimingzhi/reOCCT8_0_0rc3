#pragma once

#include <Graphic3d_ShaderProgram.hpp>

class Graphic3d_Aspects;
class OpenGl_Context;
class OpenGl_ShaderProgram;

//! OpenGl resources for custom shading program.
class OpenGl_AspectsProgram
{
public:
  DEFINE_STANDARD_ALLOC
public:
  //! Empty constructor.
  OpenGl_AspectsProgram()
      : myIsShaderReady(false)
  {
  }

  //! Return shading program.
  const occ::handle<OpenGl_ShaderProgram>& ShaderProgram(
    const occ::handle<OpenGl_Context>&          theCtx,
    const occ::handle<Graphic3d_ShaderProgram>& theShader)
  {
    if (!myIsShaderReady)
    {
      build(theCtx, theShader);
      myIsShaderReady = true;
    }
    return myShaderProgram;
  }

  //! Update shader resource up-to-date state.
  Standard_EXPORT void UpdateRediness(const occ::handle<Graphic3d_Aspects>& theAspect);

  //! Release resource.
  Standard_EXPORT void Release(OpenGl_Context* theCtx);

private:
  //! Build shader resource.
  Standard_EXPORT void build(const occ::handle<OpenGl_Context>&          theCtx,
                             const occ::handle<Graphic3d_ShaderProgram>& theShader);

private:
  occ::handle<OpenGl_ShaderProgram> myShaderProgram;
  TCollection_AsciiString           myShaderProgramId;
  bool                              myIsShaderReady;
};
