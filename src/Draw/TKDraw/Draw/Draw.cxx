#include <Draw.hpp>
#include <Draw_Appli.hpp>
#include <Draw_Failure.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_ProgressIndicator.hpp>
#include <Draw_Window.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_PrinterOStream.hpp>
#include <OSD.hpp>
#include <OSD_Environment.hpp>
#include <OSD_File.hpp>
#include <OSD_Process.hpp>
#include <OSD_SharedLibrary.hpp>
#include <OSD_Timer.hpp>
#include <OSD_Function.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <Resource_Manager.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Version.hxx>

#include <tcl.h>

#include <Standard_WarningDisableFunctionCast.hpp>

extern bool Draw_ParseFailed;

Standard_EXPORT Draw_Viewer      dout;
Standard_EXPORT Draw_Interpretor theCommands;
Standard_EXPORT bool             Draw_Batch          = false;
Standard_EXPORT bool             Draw_Spying         = false;
Standard_EXPORT bool             Draw_Chrono         = false;
Standard_EXPORT bool             Draw_VirtualWindows = false;
Standard_EXPORT bool             ErrorMessages       = true;

static const char* ColorNames[MAXCOLOR] = {"White",
                                           "Red",
                                           "Green",
                                           "Blue",
                                           "Cyan",
                                           "Gold",
                                           "Magenta",
                                           "Maroon",
                                           "Orange",
                                           "Pink",
                                           "Salmon",
                                           "Violet",
                                           "Yellow",
                                           "Khaki",
                                           "Coral"};

std::filebuf Draw_Spyfile;

static std::ostream spystream(&Draw_Spyfile);

static occ::handle<Draw_ProgressIndicator> global_Progress = nullptr;

Standard_EXPORT bool Draw_Interprete(const char* command);

static void interpreteTclCommand(const TCollection_AsciiString& theCmd)
{
#ifdef _WIN32
  if (!Draw_Batch)
  {
    try
    {
      while (console_semaphore == HAS_CONSOLE_COMMAND)
      {
        Sleep(10);
      }
      {
        TCollection_ExtendedString aCmdWide(theCmd);
        wcscpy_s(console_command, aCmdWide.ToWideString());
      }
      console_semaphore = HAS_CONSOLE_COMMAND;
      while (console_semaphore == HAS_CONSOLE_COMMAND)
      {
        Sleep(10);
      }
    }
    catch (...)
    {
      std::cout << "Error while reading a script file.\n";
      ExitProcess(0);
    }
  }
  else
#endif
  {
    Draw_Interprete(theCmd.ToCString());
  }
}

static void ReadInitFile(const TCollection_AsciiString& theFileName)
{
  TCollection_AsciiString aCmd = theFileName;
#ifdef _WIN32
  aCmd.ChangeAll('\\', '/');
#endif
  aCmd = TCollection_AsciiString("source -encoding utf-8 \"") + aCmd + "\"";
  interpreteTclCommand(aCmd);
}

static void setOcctTclEnv(const TCollection_AsciiString& theName, TCollection_AsciiString& thePath)
{
  if (thePath.IsEmpty())
  {
    return;
  }

  thePath.ChangeAll('\\', '/');
  OSD_Environment aRedPathEnv(theName);
  aRedPathEnv.SetValue(thePath);
  aRedPathEnv.Build();

  const TCollection_AsciiString aPutEnv = theName + "=" + thePath;
  Tcl_PutEnv(aPutEnv.ToCString());
}

static bool searchResources(TCollection_AsciiString&       theCasRoot,
                            TCollection_AsciiString&       theResRoot,
                            const TCollection_AsciiString& theResName,
                            const TCollection_AsciiString& theProbeFile)
{
  const TCollection_AsciiString aResLayouts[] = {
    TCollection_AsciiString("/share/opencascade-" OCC_VERSION_STRING_EXT "/") + theResName,
    TCollection_AsciiString("/share/opencascade-" OCC_VERSION_COMPLETE "/") + theResName,
    TCollection_AsciiString("/share/opencascade-" OCC_VERSION_STRING "/") + theResName,
    TCollection_AsciiString("/share/opencascade/") + theResName,
    TCollection_AsciiString("/share/occt-" OCC_VERSION_STRING_EXT "/") + theResName,
    TCollection_AsciiString("/share/occt-" OCC_VERSION_COMPLETE "/") + theResName,
    TCollection_AsciiString("/share/occt-" OCC_VERSION_STRING "/") + theResName,
    TCollection_AsciiString("/share/occt/") + theResName,
    TCollection_AsciiString("/") + theResName,
    TCollection_AsciiString("/share/opencascade"),
    TCollection_AsciiString("/share/occt"),
    TCollection_AsciiString("/share"),
    TCollection_AsciiString("/src"),
    TCollection_AsciiString("")};

  const TCollection_AsciiString anExeDir(OSD_Process::ExecutableFolder());
  for (int aLayIter = 0;; ++aLayIter)
  {
    const TCollection_AsciiString& aResLayout = aResLayouts[aLayIter];
    const TCollection_AsciiString  aProbeFile = aResLayout + "/" + theProbeFile;
    if (OSD_File(anExeDir + aProbeFile).Exists())
    {
      theCasRoot = anExeDir;
      theResRoot = theCasRoot + aResLayout;
      return true;
    }

    else if (OSD_File(anExeDir + "../" + aProbeFile).Exists())
    {
      theCasRoot = anExeDir + "..";
      theResRoot = theCasRoot + aResLayout;
      return true;
    }

    else if (OSD_File(anExeDir + "../../" + aProbeFile).Exists())
    {
      theCasRoot = anExeDir + "../..";
      theResRoot = theCasRoot + aResLayout;
      return true;
    }

    else if (OSD_File(anExeDir + "../../../" + aProbeFile).Exists())
    {
      theCasRoot = anExeDir + "../../..";
      theResRoot = theCasRoot + aResLayout;
      return true;
    }

    if (aResLayout.IsEmpty())
    {
      return false;
    }
  }
}

Draw_Interpretor& Draw::GetInterpretor()
{
  return theCommands;
}

void Draw::SetProgressBar(const occ::handle<Draw_ProgressIndicator>& theProgress)
{
  global_Progress = theProgress;
}

occ::handle<Draw_ProgressIndicator> Draw::GetProgressBar()
{
  return global_Progress;
}

#ifndef _WIN32

void exitProc(ClientData)
{
  if (!Draw_Batch)
  {
    for (int id = 0; id < MAXVIEW; id++)
      dout.DeleteView(id);
  }
}
#endif

#ifdef _WIN32
Standard_EXPORT void Draw_Appli(HINSTANCE             hInst,
                                HINSTANCE             hPrevInst,
                                int                   nShow,
                                int                   argc,
                                wchar_t**             argv,
                                const FDraw_InitAppli Draw_InitAppli)
#else
void Draw_Appli(int argc, char** argv, const FDraw_InitAppli Draw_InitAppli)
#endif
{

#ifdef _WIN32
  OSD_Environment                  aUserDllEnv("CSF_UserDllPath");
  const TCollection_ExtendedString aUserDllPath(aUserDllEnv.Value());
  if (!aUserDllPath.IsEmpty())
  {

    typedef BOOL(WINAPI * SetDllDirectoryW_t)(const wchar_t* thePathName);
    HMODULE            aKern32Module = GetModuleHandleW(L"kernel32");
    SetDllDirectoryW_t aFunc =
      (aKern32Module != NULL)
        ? (SetDllDirectoryW_t)GetProcAddress(aKern32Module, "SetDllDirectoryW")
        : NULL;
    if (aFunc != NULL)
    {
      aFunc(aUserDllPath.ToWideString());
    }
    else
    {
    }
    if (aKern32Module != NULL)
    {
      FreeLibrary(aKern32Module);
    }
  }
#endif

  Draw_Batch = false;
  TCollection_AsciiString aRunFile, aCommand;
  bool                    isInteractiveForced = false;

  for (int anArgIter = 1; anArgIter < argc; ++anArgIter)
  {
    TCollection_AsciiString anArg(argv[anArgIter]);
    anArg.LowerCase();
    if (anArg == "-h" || anArg == "--help")
    {
      std::cout << "Open CASCADE " << OCC_VERSION_STRING_EXT << " DRAW Test Harness\n\n";
      std::cout << "Options:\n";
      std::cout << "  -b: batch mode (no GUI, no viewers)\n";
      std::cout << "  -v: no GUI, use virtual (off-screen) windows for viewers\n";
      std::cout << "  -i: interactive mode\n";
      std::cout << "  -f file: execute script from file\n";
      std::cout << "  -c command args...: execute command (with optional arguments)\n\n";
      std::cout << "Options -b, -v, and -i are mutually exclusive.\n";
      std::cout << "If -c or -f are given, -v is default; otherwise default is -i.\n";
      std::cout << "Options -c and -f are alternatives and should be at the end \n";
      std::cout << "of the command line.\n";
      std::cout << "Option -c can accept set of commands separated by ';'.\n";
      return;
    }
    else if (anArg == "-b")
    {
      Draw_Batch = true;
    }
    else if (anArg == "-v")
    {

      Draw_VirtualWindows = true;
    }
    else if (anArg == "-i")
    {

      Draw_VirtualWindows = false;
      isInteractiveForced = true;
    }
    else if (anArg == "-f")
    {
      Draw_VirtualWindows = !isInteractiveForced;
      if (++anArgIter < argc)
      {
        aRunFile = TCollection_AsciiString(argv[anArgIter]);
      }
      break;
    }
    else if (anArg == "-c")
    {
      Draw_VirtualWindows = !isInteractiveForced;
      if (++anArgIter < argc)
      {
        aCommand = TCollection_AsciiString(argv[anArgIter]);
      }
      while (++anArgIter < argc)
      {
        aCommand.AssignCat(" ");
        aCommand.AssignCat(argv[anArgIter]);
      }
      break;
    }
    else
    {
      std::cout << "Error: unsupported option " << TCollection_AsciiString(argv[anArgIter]) << "\n";
    }
  }

  OSD::SetSignal(false);

#ifdef _WIN32

  if (!Draw_VirtualWindows && !Draw_Batch)
    ::SetErrorMode(0);
#endif

#ifdef _WIN32
  HWND hWnd = NULL;
#endif

  if (!Draw_Batch)
#ifdef _WIN32
    Draw_Batch = !Init_Appli(hInst, hPrevInst, nShow, hWnd);
#else
    Draw_Batch = !Init_Appli();
#endif
  else
  {
    std::cout << "DRAW is running in batch mode" << std::endl;
    theCommands.Init();
    Tcl_Init(theCommands.Interp());
  }

  if (!Draw_Batch)
  {

    for (int i = 0; i < MAXCOLOR; ++i)
    {
      if (!dout.DefineColor(i, ColorNames[i]))
      {
        std::cout << "Could not allocate default color " << ColorNames[i] << std::endl;
      }
    }
  }

  std::cout.precision(15);

  Draw::BasicCommands(theCommands);
  Draw::MessageCommands(theCommands);
  Draw::VariableCommands(theCommands);
  Draw::UnitCommands(theCommands);
  if (!Draw_Batch)
    Draw::GraphicCommands(theCommands);

  Draw_InitAppli(theCommands);

#ifndef _WIN32
  Tcl_CreateExitHandler(exitProc, nullptr);
#endif

  const TCollection_AsciiString aDrawDef(OSD_Environment("DRAWDEFAULT").Value());
  if (!aDrawDef.IsEmpty())
  {
    ReadInitFile(aDrawDef);
  }
  else
  {
    TCollection_AsciiString aDrawHome;
    TCollection_AsciiString aCasRoot(OSD_Environment("CSF_OCCTResourcePath").Value());
    if (!aCasRoot.IsEmpty())
    {
      aDrawHome = aCasRoot + "/DrawResources";
    }
    else
    {

      TCollection_AsciiString aResPath;
      if (searchResources(aCasRoot, aResPath, "resources", "DrawResources/DrawDefault"))
      {
        aDrawHome = aResPath + "/DrawResources";
        setOcctTclEnv("CASROOT", aCasRoot);
        setOcctTclEnv("DRAWHOME", aDrawHome);
        setOcctTclEnv("CSF_OCCTResourcePath", aResPath);
      }

      TCollection_AsciiString aTestsPath;
      if (OSD_Environment("CSF_TestScriptsPath").Value().IsEmpty()
          && searchResources(aCasRoot, aTestsPath, "tests", "parse.rules"))
      {
        setOcctTclEnv("CSF_TestScriptsPath", aTestsPath);
      }
    }

    if (!aDrawHome.IsEmpty())
    {
      const TCollection_AsciiString aDefStr = aDrawHome + "/DrawDefault";
      ReadInitFile(aDefStr);
    }
    else
    {
#ifdef _WIN32
      ReadInitFile("ddefault");
#else
      std::cout << " the CASROOT variable is mandatory to Run OpenCascade " << std::endl;
      std::cout << "No default file" << std::endl;
#endif
    }
  }

  if (!aRunFile.IsEmpty())
  {
    if (!isInteractiveForced)
    {

      theCommands.SetToColorize(false);
    }
    ReadInitFile(aRunFile);

    if (!isInteractiveForced)
#ifndef _WIN32
      return;
#else
      ExitProcess(0);
#endif
  }

  if (!aCommand.IsEmpty())
  {
#ifdef _WIN32
    if (!Draw_Batch)
    {

      while (console_semaphore == HAS_CONSOLE_COMMAND)
        Sleep(10);
      TCollection_ExtendedString aCmdWide(aCommand);
      wcscpy_s(console_command, aCmdWide.ToWideString());
      console_semaphore = HAS_CONSOLE_COMMAND;
      while (console_semaphore == HAS_CONSOLE_COMMAND)
        Sleep(10);
    }
    else
#endif
      Draw_Interprete(aCommand.ToCString());

    if (!isInteractiveForced)
#ifndef _WIN32
      return;
#else
      ExitProcess(0);
#endif
  }

  if (!Draw_Batch)
  {
#ifdef _WIN32
    Run_Appli(hWnd);
#else
    Run_Appli(Draw_Interprete);
#endif
  }
  else
  {
    const int MAXCMD = 2048;
    char      cmd[MAXCMD];
    for (int ncmd = 1;; ++ncmd)
    {
      std::cout << "Draw[" << ncmd << "]> ";
      if (std::cin.getline(cmd, MAXCMD).fail())
      {
        break;
      }
      Draw_Interprete(cmd);
    }
  }
#ifdef _WIN32

  Destroy_Appli(hInst);
#endif
}

void (*Draw_BeforeCommand)()   = nullptr;
void (*Draw_AfterCommand)(int) = nullptr;

bool Draw_Interprete(const char* com)
{

  static bool        first = true;
  static Tcl_DString command;

  if (first)
  {
    first = false;
    Tcl_DStringInit(&command);
  }

#ifdef _WIN32

  Tcl_DStringAppend(&command, com, -1);
#elif ((TCL_MAJOR_VERSION > 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 1)))

  Tcl_ExternalToUtfDString(nullptr, com, -1, &command);
#else
  Tcl_DStringAppend(&command, com, -1);
#endif

  if (!Draw_Interpretor::Complete(Tcl_DStringValue(&command)))
    return false;

  bool wasspying = Draw_Spying;

  OSD_Timer tictac;
  bool      hadchrono = Draw_Chrono;
  if (hadchrono)
    tictac.Start();

  if (Draw_BeforeCommand)
    (*Draw_BeforeCommand)();

  int c;

  c = theCommands.RecordAndEval(Tcl_DStringValue(&command));

  if (Draw_AfterCommand)
    (*Draw_AfterCommand)(c);

  if (wasspying && Draw_Spying)
  {
    if (c > 0)
      spystream << "# ";
    spystream << Tcl_DStringValue(&command) << "\n";
  }

  dout.Flush();

  if (*theCommands.Result())
  {
    if (c > 0 && theCommands.ToColorize())
    {
      Message_PrinterOStream::SetConsoleTextColor(&std::cout, Message_ConsoleColor_Red, true);
    }
    std::cout << theCommands.Result();
    if (c > 0 && theCommands.ToColorize())
    {
      Message_PrinterOStream::SetConsoleTextColor(&std::cout, Message_ConsoleColor_Default, false);
    }
    std::cout << std::endl;
  }

  if (Draw_Chrono && hadchrono)
  {
    tictac.Stop();
    tictac.Show();
  }

  Tcl_DStringFree(&command);

  return true;
}

int Tcl_AppInit(Tcl_Interp*)
{
  return 0;
}

int Draw_Call(char* c)
{
  int r = theCommands.Eval(c);
  std::cout << theCommands.Result() << std::endl;
  return r;
}

void Draw::Load(Draw_Interpretor&              theDI,
                const TCollection_AsciiString& theKey,
                const TCollection_AsciiString& theResourceFileName,
                const TCollection_AsciiString& theDefaultsDirectory,
                const TCollection_AsciiString& theUserDefaultsDirectory,
                const bool                     theIsVerbose)
{
  static NCollection_DataMap<TCollection_AsciiString, OSD_Function> theMapOfFunctions;
  OSD_Function                                                      aFunc = nullptr;
  if (!theMapOfFunctions.Find(theKey, aFunc))
  {
    TCollection_AsciiString       aPluginLibrary;
    occ::handle<Resource_Manager> aPluginResource = new Resource_Manager(theResourceFileName,
                                                                         theDefaultsDirectory,
                                                                         theUserDefaultsDirectory,
                                                                         theIsVerbose);
    if (!aPluginResource->Find(theKey, aPluginLibrary))
    {
      Message::SendFail() << "could not find the resource:" << theKey;
      Standard_SStream aMsg;
      aMsg << "Could not find the resource:" << theKey << std::endl;
      throw Draw_Failure(aMsg.str().c_str());
    }

#if !defined(_WIN32) || defined(__MINGW32__)
    aPluginLibrary = TCollection_AsciiString("lib") + aPluginLibrary;
#endif
#ifdef _WIN32
    aPluginLibrary += ".dll";
#elif __APPLE__
    aPluginLibrary += ".dylib";
#elif defined(HPUX) || defined(_hpux)
    aPluginLibrary += ".sl";
#else
    aPluginLibrary += ".so";
#endif
    OSD_SharedLibrary aSharedLibrary(aPluginLibrary.ToCString());
    if (!aSharedLibrary.DlOpen(OSD_RTLD_LAZY))
    {
      const TCollection_AsciiString anError(aSharedLibrary.DlError());
      Standard_SStream              aMsg;
      aMsg << "Could not open: " << aPluginLibrary << "; reason: " << anError;
#ifdef OCCT_DEBUG
      std::cout << "could not open: " << aPluginLibrary << " ; reason: " << anError << std::endl;
#endif
      throw Draw_Failure(aMsg.str().c_str());
    }

    aFunc = aSharedLibrary.DlSymb("PLUGINFACTORY");
    if (aFunc == nullptr)
    {
      const TCollection_AsciiString anError(aSharedLibrary.DlError());
      Standard_SStream              aMsg;
      aMsg << "Could not find the factory in: " << aPluginLibrary << anError;
      throw Draw_Failure(aMsg.str().c_str());
    }
    theMapOfFunctions.Bind(theKey, aFunc);
  }

  void (*fp)(Draw_Interpretor&) =
    reinterpret_cast<void (*)(Draw_Interpretor&)>(reinterpret_cast<void*>(aFunc));
  (*fp)(theDI);
}

namespace
{
  const int   THE_MAX_INTEGER_COLOR_COMPONENT = 255;
  const float THE_MAX_REAL_COLOR_COMPONENT    = 1.0f;

  static bool parseNumericalColorComponent(const char* theColorComponentString,
                                           int&        theIntegerColorComponent)
  {
    int anIntegerColorComponent;
    if (!Draw::ParseInteger(theColorComponentString, anIntegerColorComponent))
    {
      return false;
    }
    if ((anIntegerColorComponent < 0)
        || (anIntegerColorComponent > THE_MAX_INTEGER_COLOR_COMPONENT))
    {
      return false;
    }
    theIntegerColorComponent = anIntegerColorComponent;
    return true;
  }

  static bool parseNumericalColorComponent(const char* theColorComponentString,
                                           float&      theRealColorComponent)
  {
    double aRealColorComponent;
    if (!Draw::ParseReal(theColorComponentString, aRealColorComponent))
    {
      return false;
    }
    const float aShortRealColorComponent = static_cast<float>(aRealColorComponent);
    if ((aShortRealColorComponent < 0.0f)
        || (aShortRealColorComponent > THE_MAX_REAL_COLOR_COMPONENT))
    {
      return false;
    }
    theRealColorComponent = aShortRealColorComponent;
    return true;
  }

  static bool parseColorComponent(const char* theColorComponentString, float& theColorComponent)
  {
    int anIntegerColorComponent;
    if (parseNumericalColorComponent(theColorComponentString, anIntegerColorComponent))
    {
      if (anIntegerColorComponent == 1)
      {
        theColorComponent = THE_MAX_REAL_COLOR_COMPONENT;
      }
      else
      {
        theColorComponent = anIntegerColorComponent * 1.0f / THE_MAX_INTEGER_COLOR_COMPONENT;
      }
      return true;
    }
    return parseNumericalColorComponent(theColorComponentString, theColorComponent);
  }

  template <typename TheNumber>
  static bool parseNumericalColor(int&                         theNumberOfColorComponents,
                                  const char* const* const     theColorComponentStrings,
                                  NCollection_Vec4<TheNumber>& theNumericalColor)
  {
    for (int aColorComponentIndex = 0; aColorComponentIndex < theNumberOfColorComponents;
         ++aColorComponentIndex)
    {
      const char* const aColorComponentString = theColorComponentStrings[aColorComponentIndex];
      TheNumber         aNumericalColorComponent;
      if (parseNumericalColorComponent(aColorComponentString, aNumericalColorComponent))
      {
        theNumericalColor[aColorComponentIndex] = aNumericalColorComponent;
      }
      else
      {
        if (aColorComponentIndex == 3)
        {
          theNumberOfColorComponents = 3;
        }
        else
        {
          return false;
        }
      }
    }
    return true;
  }

  static bool parseIntegerColor(int&                     theNumberOfColorComponents,
                                const char* const* const theColorComponentStrings,
                                Quantity_ColorRGBA&      theColor)
  {
    const int             THE_COLOR_COMPONENT_NOT_PARSED = -1;
    NCollection_Vec4<int> anIntegerColor(THE_COLOR_COMPONENT_NOT_PARSED);
    if (!parseNumericalColor(theNumberOfColorComponents, theColorComponentStrings, anIntegerColor)
        || anIntegerColor.maxComp() <= 1)
    {
      return false;
    }
    if (anIntegerColor.a() == THE_COLOR_COMPONENT_NOT_PARSED)
    {
      anIntegerColor.a() = THE_MAX_INTEGER_COLOR_COMPONENT;
    }

    const NCollection_Vec4<float> aRealColor =
      NCollection_Vec4<float>(anIntegerColor) / static_cast<float>(THE_MAX_INTEGER_COLOR_COMPONENT);
    theColor = Quantity_ColorRGBA(Quantity_ColorRGBA::Convert_sRGB_To_LinearRGB(aRealColor));
    return true;
  }

  static bool parseRealColor(int&                     theNumberOfColorComponents,
                             const char* const* const theColorComponentStrings,
                             Quantity_ColorRGBA&      theColor)
  {
    NCollection_Vec4<float> aRealColor(THE_MAX_REAL_COLOR_COMPONENT);
    if (!parseNumericalColor(theNumberOfColorComponents, theColorComponentStrings, aRealColor))
    {
      return false;
    }
    theColor = Quantity_ColorRGBA(aRealColor);
    return true;
  }
} // namespace

int Draw::parseColor(const int                theArgNb,
                     const char* const* const theArgVec,
                     Quantity_ColorRGBA&      theColor,
                     const bool               theToParseAlpha)
{
  if ((theArgNb >= 1) && Quantity_ColorRGBA::ColorFromHex(theArgVec[0], theColor, !theToParseAlpha))
  {
    return 1;
  }
  if (theArgNb >= 1 && Quantity_ColorRGBA::ColorFromName(theArgVec[0], theColor))
  {
    if (theArgNb >= 2 && theToParseAlpha)
    {
      const char* anAlphaStr = theArgVec[1];
      float       anAlphaComponent;
      if (parseColorComponent(anAlphaStr, anAlphaComponent))
      {
        theColor.SetAlpha(anAlphaComponent);
        return 2;
      }
    }
    return 1;
  }
  if (theArgNb >= 3)
  {
    const int aNumberOfColorComponentsToParse = std::min(theArgNb, theToParseAlpha ? 4 : 3);
    int       aNumberOfColorComponentsParsed  = aNumberOfColorComponentsToParse;
    if (parseIntegerColor(aNumberOfColorComponentsParsed, theArgVec, theColor))
    {
      return aNumberOfColorComponentsParsed;
    }
    aNumberOfColorComponentsParsed = aNumberOfColorComponentsToParse;
    if (parseRealColor(aNumberOfColorComponentsParsed, theArgVec, theColor))
    {
      return aNumberOfColorComponentsParsed;
    }
    return 0;
  }
  return 0;
}

bool Draw::ParseOnOff(const char* theArg, bool& theIsOn)
{
  TCollection_AsciiString aFlag(theArg);
  aFlag.LowerCase();
  if (aFlag == "on" || aFlag == "1")
  {
    theIsOn = true;
    return true;
  }
  else if (aFlag == "off" || aFlag == "0")
  {
    theIsOn = false;
    return true;
  }
  return false;
}

bool Draw::ParseOnOffIterator(int theArgsNb, const char** theArgVec, int& theArgIter)
{
  bool isOn = true;
  if (theArgIter + 1 < theArgsNb && Draw::ParseOnOff(theArgVec[theArgIter + 1], isOn))
  {
    ++theArgIter;
  }
  return isOn;
}

bool Draw::ParseOnOffNoIterator(int theArgsNb, const char** theArgVec, int& theArgIter)
{
  bool toReverse = strncasecmp(theArgVec[theArgIter], "no", 2) == 0
                   || strncasecmp(theArgVec[theArgIter], "-no", 3) == 0;
  bool isOn = Draw::ParseOnOffIterator(theArgsNb, theArgVec, theArgIter);
  return toReverse ? !isOn : isOn;
}
