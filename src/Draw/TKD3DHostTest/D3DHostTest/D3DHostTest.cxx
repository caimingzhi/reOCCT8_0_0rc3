

#include <D3DHostTest.hpp>

#include <Draw_PluginMacro.hpp>
#include <D3DHost_GraphicDriverFactory.hpp>

void D3DHostTest::Factory(Draw_Interpretor&)
{
  static const occ::handle<D3DHost_GraphicDriverFactory> aFactory =
    new D3DHost_GraphicDriverFactory();
  Graphic3d_GraphicDriverFactory::RegisterFactory(aFactory);
#ifdef DEB
  theDI << "Draw Plugin : D3DHost commands are loaded.\n";
#endif
}

DPLUGIN(D3DHostTest)
