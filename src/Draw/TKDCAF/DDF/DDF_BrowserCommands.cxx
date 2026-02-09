#include <cstdio>

#include <DDF.hpp>
#include <DDF_Browser.hpp>

#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>
#include <Message.hpp>

#include <TDF_Label.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Tool.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_File.hpp>

static int DFBrowse(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
  {
    Message::SendFail() << "Use: " << a[0] << " document [brower_name]";
    return 1;
  }

  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(a[1], DF))
  {
    Message::SendFail() << "Error: document " << a[1] << " is not found";
    return 1;
  }

  occ::handle<DDF_Browser> NewDDFBrowser = new DDF_Browser(DF);
  TCollection_AsciiString  name("browser_");
  name += ((n == 3) ? a[2] : a[1]);
  Draw::Set(name.ToCString(), NewDDFBrowser);

  TCollection_AsciiString aTclScript(getenv("CSF_DrawPluginDefaults"));
  aTclScript.AssignCat("/dftree.tcl");
  OSD_File aTclScriptFile(aTclScript);
  if (aTclScriptFile.Exists())
  {
#ifdef OCCT_DEBUG
    std::cout << "Load " << aTclScript << std::endl;
#endif
    di.EvalFile(aTclScript.ToCString());
  }
  else
  {
    Message::SendFail() << "Error: Could not load script " << aTclScript << "\n"
                        << "Check environment variable CSF_DrawPluginDefaults";
  }

  TCollection_AsciiString aCommand = "dftree ";
  aCommand.AssignCat(name);
  di.Eval(aCommand.ToCString());
  return 0;
}

static int DFOpenLabel(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<DDF_Browser> browser = occ::down_cast<DDF_Browser>(Draw::GetExisting(a[1]));
  if (browser.IsNull())
  {
    Message::SendFail() << "Syntax error: browser '" << a[1] << "' not found";
    return 1;
  }

  TDF_Label lab;
  if (n == 3)
    TDF_Tool::Label(browser->Data(), a[2], lab);

  TCollection_AsciiString list(lab.IsNull() ? browser->OpenRoot() : browser->OpenLabel(lab));
  di << list.ToCString();
  return 0;
}

static int DFOpenAttributeList(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 3)
    return 1;

  occ::handle<DDF_Browser> browser = occ::down_cast<DDF_Browser>(Draw::GetExisting(a[1]));
  if (browser.IsNull())
  {
    Message::SendFail() << "Syntax error: browser '" << a[1] << "' not found";
    return 1;
  }

  TDF_Label lab;
  TDF_Tool::Label(browser->Data(), a[2], lab);

  if (lab.IsNull())
    return 1;

  TCollection_AsciiString list(browser->OpenAttributeList(lab));
  di << list.ToCString();
  return 0;
}

static int DFOpenAttribute(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 3)
    return 1;

  occ::handle<DDF_Browser> browser = occ::down_cast<DDF_Browser>(Draw::GetExisting(a[1]));
  if (browser.IsNull())
  {
    Message::SendFail() << "Syntax error: browser '" << a[1] << "' not found";
    return 1;
  }

  const int               index = Draw::Atoi(a[2]);
  TCollection_AsciiString list  = browser->OpenAttribute(index);
  di << list.ToCString();
  return 0;
}

void DDF::BrowserCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DF browser commands";

  theCommands.Add("DFBrowse",
                  "Creates a browser on a df: DFBrowse dfname [browsername]",
                  __FILE__,
                  DFBrowse,
                  g);

  theCommands.Add("DFOpenLabel",
                  "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns the list of sub-label "
                  "entries: DFOpenLabel browsername [label]",
                  __FILE__,
                  DFOpenLabel,
                  g);

  theCommands.Add("DFOpenAttributeList",
                  "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns the attribute list of "
                  "a label: DFOpenLabel browsername label",
                  __FILE__,
                  DFOpenAttributeList,
                  g);

  theCommands.Add("DFOpenAttribute",
                  "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns the reference list of "
                  "an attribute: DFOpenLabel browsername attributeindex",
                  __FILE__,
                  DFOpenAttribute,
                  g);
#if 0
  theCommands.Add
    ("DFDisplayInfo",
     "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns information about an attribute, a df or a label: DFDisplayInfo {#} | {browsername [label]}",
     __FILE__, DFDisplayInfo, g);
#endif
}
