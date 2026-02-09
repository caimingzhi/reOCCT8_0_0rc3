#include <DBRep.hpp>
#include <Draw.hpp>
#include <DrawTrSurf.hpp>
#include <Message.hpp>
#include <Message_PrinterOStream.hpp>
#include <Message_PrinterSystemLog.hpp>
#include <NCollection_IndexedMap.hpp>
#include <OSD.hpp>
#include <OSD_Thread.hpp>
#include <Standard_ErrorHandler.hpp>

#ifdef OCCT_NO_PLUGINS
  #include <BOPTest.hpp>
  #include <DPrsStd.hpp>
  #if defined(HAVE_OPENGL) || defined(HAVE_GLES2)
    #include <OpenGlTest.hpp>
  #endif
  #include <TObjDRAW.hpp>
  #include <ViewerTest.hpp>
  #include <XDEDRAW.hpp>
  #include <XSDRAW.hpp>
  #include <XSDRAWDE.hpp>
  #include <XSDRAWGLTF.hpp>
  #include <XSDRAWIGES.hpp>
  #include <XSDRAWOBJ.hpp>
  #include <XSDRAWPLY.hpp>
  #include <XSDRAWSTEP.hpp>
  #include <XSDRAWSTL.hpp>
  #include <XSDRAWVRML.hpp>
#endif

Standard_IMPORT bool Draw_Interprete(const char* theCommand);

#if defined(__EMSCRIPTEN__)
  #include <emscripten/bind.h>
  #include <emscripten/emscripten.h>
  #include <emscripten/threading.h>

EM_JS(void, occJSEvalAsyncCompleted, (int theResult), {
  if (Module.evalAsyncCompleted != undefined)
  {
    Module.evalAsyncCompleted(theResult);
  }
  else
  {
    console.error("Module.evalAsyncCompleted() is undefined");
  }
});

class DRAWEXE
{
public:
  static int eval(const std::string& theCommand)
  {
    int aRes = 0;
    try
    {
      OCC_CATCH_SIGNALS

      aRes = Draw_Interprete(theCommand.c_str()) ? 1 : 0;
    }
    catch (Standard_Failure& anExcept)
    {
      std::cout << "Failed to evaluate command: " << anExcept.what() << std::endl;
    }
    return aRes;
  }

  static bool isComplete(const std::string& theCommand)
  {
    return Draw::GetInterpretor().Complete(theCommand.c_str());
  }

  static void evalAsync(const std::string& theCommand)
  {
  #if defined(__EMSCRIPTEN_PTHREADS__)
    std::string* aCmdPtr = new std::string(theCommand);
    OSD_Thread   aThread(&evalAsyncEntry);
    aThread.Run(aCmdPtr);
  #else

    int aRes = eval(theCommand);
    occJSEvalAsyncCompleted(aRes);
  #endif
  }

  #if defined(__EMSCRIPTEN_PTHREADS__)
private:
  static void* evalAsyncEntry(void* theData)
  {
    OSD::SetSignal(false);
    std::string*      aCmdPtr = (std::string*)theData;
    const std::string aCmd    = *aCmdPtr;
    delete aCmdPtr;
    int aRes = eval(aCmd);
    emscripten_async_run_in_main_runtime_thread(EM_FUNC_SIG_VI, evalAsyncCompletedEntry, aRes);
    return 0;
  }

  static void evalAsyncCompletedEntry(int theResult) { occJSEvalAsyncCompleted(theResult); }
  #endif
};

EM_JS(void, occJSPrintMessage, (const char* theStr, int theGravity), {
  const aStr = Number(theStr);
  if (Module.printMessage != undefined && Module.printMessage != null)
  {
    Module.printMessage(UTF8ToString(aStr), theGravity);
  }
  else if (Module.print != undefined && Module.print != null)
  {
    Module.print(UTF8ToString(aStr));
  }
  else
  {
  }
});

class DRAWEXE_WasmModulePrinter : public Message_Printer
{
  DEFINE_STANDARD_RTTI_INLINE(DRAWEXE_WasmModulePrinter, Message_Printer)
public:
  DRAWEXE_WasmModulePrinter(const Message_Gravity theTraceLevel = Message_Info)
  {
    SetTraceLevel(theTraceLevel);
  }

  virtual ~DRAWEXE_WasmModulePrinter() {}

protected:
  virtual void send(const TCollection_AsciiString& theString,
                    const Message_Gravity          theGravity) const override
  {
    if (theGravity >= myTraceLevel)
    {
      occJSPrintMessage(theString.ToCString(), (int)theGravity);
    }
  }
};

EMSCRIPTEN_BINDINGS(DRAWEXE)
{
  emscripten::function("eval", &DRAWEXE::eval);
  emscripten::function("evalAsync", &DRAWEXE::evalAsync);
  emscripten::function("isComplete", &DRAWEXE::isComplete);
}
#endif

#ifdef OCCT_NO_PLUGINS
  #include <functional>
  #include <string>
  #include <unordered_map>

static int Pload(Draw_Interpretor& theDI, int theNbArgs, const char** theArgVec)
{

  std::unordered_map<std::string, std::function<void(Draw_Interpretor&)>> aPluginMap = {
    {"TOPTEST", BOPTest::Factory},
    {"DCAF", DPrsStd::Factory},
    {"AISV", ViewerTest::Factory},
  #if defined(HAVE_OPENGL)
    {"GL", OpenGlTest::Factory},
    {"OPENGL", OpenGlTest::Factory},
  #endif
  #if defined(HAVE_GLES2)
    {"GLES", OpenGlTest::Factory},
    {"OPENGLES", OpenGlTest::Factory},
  #endif
    {"XSDRAW", XSDRAW::Factory},
    {"XDEDRAW", XDEDRAW::Factory},
    {"STEP", XSDRAWSTEP::Factory},
    {"IGES", XSDRAWIGES::Factory},
    {"PLY", XSDRAWPLY::Factory},
    {"GLTF", XSDRAWGLTF::Factory},
    {"VRML", XSDRAWVRML::Factory},
    {"STL", XSDRAWSTL::Factory},
    {"OBJ", XSDRAWOBJ::Factory},
    {"DE", XSDRAWDE::Factory}};

  std::unordered_map<std::string, std::vector<std::string>> anAliasMap = {
    {"DEFAULT", {"MODELING"}},
    {"MODELING", {"TOPTEST"}},
    {"VISUALIZATION", {"AISV"}},
    {"OCAFKERNEL", {"DCAF"}},
    {"DATAEXCHANGEKERNEL", {"XSDRAW", "DE"}},
    {"OCAF", {"VISUALIZATION", "OCAFKERNEL"}},
    {"DATAEXCHANGE", {"XDE", "VISUALIZATION"}},
    {"XDE", {"DATAEXCHANGEKERNEL", "XDEDRAW", "STEP", "IGES", "GLTF", "OBJ", "PLY", "STL", "VRML"}},
    {"ALL", {"MODELING", "OCAFKERNEL", "DATAEXCHANGE"}}};

  NCollection_IndexedMap<TCollection_AsciiString> aPlugins;

  std::function<void(const TCollection_AsciiString&)> processAlias;
  processAlias = [&](const TCollection_AsciiString& theAlias) -> void
  {
    auto anAliasIt = anAliasMap.find(theAlias.ToCString());
    if (anAliasIt != anAliasMap.end())
    {
      for (const auto& aPlugin : anAliasIt->second)
      {
        processAlias(TCollection_AsciiString(aPlugin.c_str()));
      }
    }
    else
    {
      aPlugins.Add(theAlias);
    }
  };

  for (int anArgIter = 1; anArgIter < theNbArgs; ++anArgIter)
  {
    TCollection_AsciiString anArg(theArgVec[anArgIter]);
    anArg.UpperCase();
    processAlias(anArg);
  }

  for (NCollection_IndexedMap<TCollection_AsciiString>::Iterator aPluginIter(aPlugins);
       aPluginIter.More();
       aPluginIter.Next())
  {
    const TCollection_AsciiString& aPlugin = aPluginIter.Value();
    auto                           anIter  = aPluginMap.find(aPlugin.ToCString());
    if (anIter != aPluginMap.end())
    {
      anIter->second(theDI);
    }
    else
    {
      theDI << "Error: unknown plugin '" << aPlugin << "'";
      return 1;
    }
  }

  return 0;
}
#endif

void Draw_InitAppli(Draw_Interpretor& theDI)
{
#if defined(__EMSCRIPTEN__)

  Message_Gravity                       aGravity = Message_Info;
  occ::handle<Message_PrinterSystemLog> aJSConsolePrinter =
    new Message_PrinterSystemLog("DRAWEXE", aGravity);
  Message::DefaultMessenger()->AddPrinter(aJSConsolePrinter);

  Message::DefaultMessenger()->RemovePrinters(STANDARD_TYPE(Message_PrinterOStream));
  occ::handle<DRAWEXE_WasmModulePrinter> aJSModulePrinter = new DRAWEXE_WasmModulePrinter(aGravity);
  Message::DefaultMessenger()->AddPrinter(aJSModulePrinter);
#endif

  Draw::Commands(theDI);
  DBRep::BasicCommands(theDI);
  DrawTrSurf::BasicCommands(theDI);

#ifdef OCCT_NO_PLUGINS
  theDI.Add("pload",
            "pload [[Key1] [Key2] ...]: Loads Draw plugins",
            __FILE__,
            Pload,
            "Draw Plugin");
#endif
}

#include <Draw_Main.hpp>
DRAW_MAIN
