#include <OpenGl_GlCore11.hpp>
#include <OpenGl_StencilTest.hpp>
#include <OpenGl_Context.hpp>
#include <OpenGl_Workspace.hpp>
#include <Standard_Dump.hpp>

OpenGl_StencilTest::OpenGl_StencilTest() = default;

//=================================================================================================

void OpenGl_StencilTest::Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const
{
  const occ::handle<OpenGl_Context>& aCtx = theWorkspace->GetGlContext();
  if (myIsEnabled)
  {
    aCtx->core11fwd->glEnable(GL_STENCIL_TEST);
    aCtx->core11fwd->glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  }
  else
  {
    aCtx->core11fwd->glDisable(GL_STENCIL_TEST);
  }
}

//=================================================================================================

void OpenGl_StencilTest::Release(OpenGl_Context*) {}

//=================================================================================================

void OpenGl_StencilTest::SetOptions(const bool theIsEnabled)
{
  myIsEnabled = theIsEnabled;
}

//=================================================================================================

OpenGl_StencilTest::~OpenGl_StencilTest() = default;

//=================================================================================================

void OpenGl_StencilTest::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, OpenGl_StencilTest)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, OpenGl_Element)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsEnabled)
}
