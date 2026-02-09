#include <AppStd_Application.hpp>
#include <DDataStd.hpp>
#include <DDF.hpp>
#include <DDocStd.hpp>
#include <DNaming.hpp>
#include <DPrsStd.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_PluginMacro.hpp>

void DPrsStd::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  DPrsStd::AISPresentationCommands(theCommands);
  DPrsStd::AISViewerCommands(theCommands);
}

void DPrsStd::Factory(Draw_Interpretor& theDI)
{
  static bool DPrsStdFactoryDone = false;
  if (DPrsStdFactoryDone)
    return;
  DPrsStdFactoryDone = true;

  DDF::AllCommands(theDI);
  DNaming::AllCommands(theDI);
  DDataStd::AllCommands(theDI);
  DPrsStd::AllCommands(theDI);
  DDocStd::AllCommands(theDI);
#ifdef OCCT_DEBUG
  std::cout << "Draw Plugin : All DF commands are loaded" << std::endl;
#endif
}

DPLUGIN(DPrsStd)
