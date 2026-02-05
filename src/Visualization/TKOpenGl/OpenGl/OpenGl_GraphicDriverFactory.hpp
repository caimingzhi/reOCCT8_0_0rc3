#pragma once

#include <Graphic3d_GraphicDriverFactory.hpp>
#include <OpenGl_Caps.hpp>

//! This class for creation of OpenGl_GraphicDriver.
class OpenGl_GraphicDriverFactory : public Graphic3d_GraphicDriverFactory
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_GraphicDriverFactory, Graphic3d_GraphicDriverFactory)
public:
  //! Empty constructor.
  Standard_EXPORT OpenGl_GraphicDriverFactory();

  //! Creates new empty graphic driver.
  Standard_EXPORT occ::handle<Graphic3d_GraphicDriver> CreateDriver(
    const occ::handle<Aspect_DisplayConnection>& theDisp) override;

  //! Return default driver options.
  const occ::handle<OpenGl_Caps>& DefaultOptions() const { return myDefaultCaps; }

  //! Set default driver options.
  void SetDefaultOptions(const occ::handle<OpenGl_Caps>& theOptions) { myDefaultCaps = theOptions; }

protected:
  occ::handle<OpenGl_Caps> myDefaultCaps;
};
