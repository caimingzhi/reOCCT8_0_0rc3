#include <OSD_SharedLibrary.hpp>
#include <Plugin.hpp>
#include <Plugin_Failure.hpp>
#include <OSD_Function.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <Resource_Manager.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Transient.hpp>

#include <Standard_WarningDisableFunctionCast.hpp>

static char                tc[1000];
static Standard_PCharacter thePluginId = tc;

//=================================================================================================

occ::handle<Standard_Transient> Plugin::Load(const Standard_GUID& aGUID, const bool theVerbose)
{

  aGUID.ToCString(thePluginId);
  TCollection_AsciiString                                           pid(thePluginId);
  static NCollection_DataMap<TCollection_AsciiString, OSD_Function> theMapOfFunctions;
  OSD_Function                                                      f;

  if (!theMapOfFunctions.IsBound(pid))
  {

    occ::handle<Resource_Manager> PluginResource = new Resource_Manager("Plugin");
    TCollection_AsciiString       theResource(thePluginId);
    theResource += ".Location";

    if (!PluginResource->Find(theResource.ToCString()))
    {
      Standard_SStream aMsg;
      aMsg << "could not find the resource:";
      aMsg << theResource.ToCString() << std::endl;
      if (theVerbose)
        std::cout << "could not find the resource:" << theResource.ToCString() << std::endl;
      throw Plugin_Failure(aMsg.str().c_str());
    }

    TCollection_AsciiString thePluginLibrary("");
#ifndef _WIN32
    thePluginLibrary += "lib";
#endif
    thePluginLibrary += PluginResource->Value(theResource.ToCString());
#ifdef _WIN32
    thePluginLibrary += ".dll";
#elif defined(__APPLE__)
    thePluginLibrary += ".dylib";
#elif defined(HPUX) || defined(_hpux)
    thePluginLibrary += ".sl";
#else
    thePluginLibrary += ".so";
#endif
    OSD_SharedLibrary theSharedLibrary(thePluginLibrary.ToCString());
    if (!theSharedLibrary.DlOpen(OSD_RTLD_LAZY))
    {
      TCollection_AsciiString error(theSharedLibrary.DlError());
      Standard_SStream        aMsg;
      aMsg << "could not open:";
      aMsg << PluginResource->Value(theResource.ToCString());
      aMsg << "; reason:";
      aMsg << error.ToCString();
      if (theVerbose)
        std::cout << "could not open: " << PluginResource->Value(theResource.ToCString())
                  << " ; reason: " << error.ToCString() << std::endl;
      throw Plugin_Failure(aMsg.str().c_str());
    }
    f = theSharedLibrary.DlSymb("PLUGINFACTORY");
    if (f == nullptr)
    {
      TCollection_AsciiString error(theSharedLibrary.DlError());
      Standard_SStream        aMsg;
      aMsg << "could not find the factory in:";
      aMsg << PluginResource->Value(theResource.ToCString());
      aMsg << error.ToCString();
      throw Plugin_Failure(aMsg.str().c_str());
    }
    theMapOfFunctions.Bind(pid, f);
  }
  else
    f = theMapOfFunctions(pid);

  // Cast through void* to avoid -Wcast-function-type-mismatch warning.
  // This is safe for dynamically loaded plugin symbols.
  Standard_Transient* (*fp)(const Standard_GUID&) =
    reinterpret_cast<Standard_Transient* (*)(const Standard_GUID&)>(reinterpret_cast<void*>(f));
  occ::handle<Standard_Transient> theServiceFactory = (*fp)(aGUID);
  return theServiceFactory;
}
