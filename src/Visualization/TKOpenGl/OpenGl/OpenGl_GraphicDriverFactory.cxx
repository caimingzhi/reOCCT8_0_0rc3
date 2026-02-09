

#include <OpenGl_GraphicDriverFactory.hpp>

#include <OpenGl_GraphicDriver.hpp>

#ifdef HAVE_GLES2
  #define OpenGl_DRIVER_NAME "TKOpenGles"
#else
  #define OpenGl_DRIVER_NAME "TKOpenGl"
#endif

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_GraphicDriverFactory, Graphic3d_GraphicDriverFactory)

OpenGl_GraphicDriverFactory::OpenGl_GraphicDriverFactory()
    : Graphic3d_GraphicDriverFactory(OpenGl_DRIVER_NAME),
      myDefaultCaps(new OpenGl_Caps())
{
}

occ::handle<Graphic3d_GraphicDriver> OpenGl_GraphicDriverFactory::CreateDriver(
  const occ::handle<Aspect_DisplayConnection>& theDisp)
{
  occ::handle<OpenGl_GraphicDriver> aDriver = new OpenGl_GraphicDriver(theDisp, false);
  aDriver->ChangeOptions()                  = *myDefaultCaps;
  aDriver->InitContext();
  return aDriver;
}
