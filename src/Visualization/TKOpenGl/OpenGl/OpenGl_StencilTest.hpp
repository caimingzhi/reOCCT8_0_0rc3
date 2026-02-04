#pragma once


#include <OpenGl_Element.hpp>

class OpenGl_StencilTest : public OpenGl_Element
{
public:
  //! Default constructor
  Standard_EXPORT OpenGl_StencilTest();

  //! Render primitives to the window
  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;

  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  Standard_EXPORT void SetOptions(const bool theIsEnabled);

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  //! Destructor
  Standard_EXPORT ~OpenGl_StencilTest() override;

private:
  bool myIsEnabled;

public:
  DEFINE_STANDARD_ALLOC
};

