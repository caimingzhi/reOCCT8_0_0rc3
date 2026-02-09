

#include <OpenGl_AspectsProgram.hpp>

#include <OpenGl_ShaderManager.hpp>
#include <OpenGl_ShaderProgram.hpp>

void OpenGl_AspectsProgram::Release(OpenGl_Context* theCtx)
{
  if (!myShaderProgram.IsNull() && theCtx != nullptr)
  {
    theCtx->ShaderManager()->Unregister(myShaderProgramId, myShaderProgram);
  }
  myShaderProgramId.Clear();
  myIsShaderReady = false;
}

void OpenGl_AspectsProgram::UpdateRediness(const occ::handle<Graphic3d_Aspects>& theAspect)
{
  const TCollection_AsciiString& aShaderKey = theAspect->ShaderProgram().IsNull()
                                                ? TCollection_AsciiString::EmptyString()
                                                : theAspect->ShaderProgram()->GetId();
  if (aShaderKey.IsEmpty() || myShaderProgramId != aShaderKey)
  {
    myIsShaderReady = false;
  }
}

void OpenGl_AspectsProgram::build(const occ::handle<OpenGl_Context>&          theCtx,
                                  const occ::handle<Graphic3d_ShaderProgram>& theShader)
{
  if (theCtx->core20fwd == nullptr)
  {
    return;
  }

  if (!myShaderProgram.IsNull())
  {
    theCtx->ShaderManager()->Unregister(myShaderProgramId, myShaderProgram);
    myShaderProgramId.Clear();
    myShaderProgram.Nullify();
  }
  if (theShader.IsNull())
  {
    return;
  }

  theCtx->ShaderManager()->Create(theShader, myShaderProgramId, myShaderProgram);
}
