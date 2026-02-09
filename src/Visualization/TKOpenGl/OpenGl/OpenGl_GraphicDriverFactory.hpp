#pragma once

#include <Graphic3d_GraphicDriverFactory.hpp>
#include <OpenGl_Caps.hpp>

class OpenGl_GraphicDriverFactory : public Graphic3d_GraphicDriverFactory
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_GraphicDriverFactory, Graphic3d_GraphicDriverFactory)
public:
  Standard_EXPORT OpenGl_GraphicDriverFactory();

  Standard_EXPORT occ::handle<Graphic3d_GraphicDriver> CreateDriver(
    const occ::handle<Aspect_DisplayConnection>& theDisp) override;

  const occ::handle<OpenGl_Caps>& DefaultOptions() const { return myDefaultCaps; }

  void SetDefaultOptions(const occ::handle<OpenGl_Caps>& theOptions) { myDefaultCaps = theOptions; }

protected:
  occ::handle<OpenGl_Caps> myDefaultCaps;
};
