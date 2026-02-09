

#include <OpenGlTest.hpp>

#include <Draw_PluginMacro.hpp>
#include <OpenGl_GraphicDriverFactory.hpp>

void OpenGlTest::Factory(Draw_Interpretor& theDI)
{
  static const occ::handle<OpenGl_GraphicDriverFactory> aFactory =
    new OpenGl_GraphicDriverFactory();
  Graphic3d_GraphicDriverFactory::RegisterFactory(aFactory);
  OpenGlTest::Commands(theDI);
#ifdef DEB
  theDI << "Draw Plugin : OpenGL commands are loaded.\n";
#endif
}

DPLUGIN(OpenGlTest)
