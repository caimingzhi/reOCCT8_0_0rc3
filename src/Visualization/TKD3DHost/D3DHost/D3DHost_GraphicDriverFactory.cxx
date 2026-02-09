

#include <D3DHost_GraphicDriverFactory.hpp>

#include <D3DHost_GraphicDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(D3DHost_GraphicDriverFactory, OpenGl_GraphicDriverFactory)

D3DHost_GraphicDriverFactory::D3DHost_GraphicDriverFactory()
{
  myName = "TKD3DHost";
}

occ::handle<Graphic3d_GraphicDriver> D3DHost_GraphicDriverFactory::CreateDriver(
  const occ::handle<Aspect_DisplayConnection>&)
{
  occ::handle<D3DHost_GraphicDriver> aDriver = new D3DHost_GraphicDriver();
  aDriver->ChangeOptions()                   = *myDefaultCaps;
  aDriver->InitContext();
  return aDriver;
}
