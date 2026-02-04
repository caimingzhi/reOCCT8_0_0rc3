#pragma once


#include <DE_Wrapper.hpp>

#include <mutex>
#include <tuple>

//! Base class to work with DE_Wrapper global registration of components.
//! Control life-time of current configuration node.
//! In creating stage load into global configuration.
//! On destroying stage unload from global configuration.
//! Operation to load/unload are thread safety.
template <class TheConfType>
class DE_PluginHolder
{
public:
  DE_PluginHolder()
  {
    std::lock_guard<std::mutex> aLock(DE_Wrapper::GlobalLoadMutex());
    myInternalConfiguration = new TheConfType;
    myInternalConfiguration->Register(DE_Wrapper::GlobalWrapper());
  }

  ~DE_PluginHolder()
  {
    std::lock_guard<std::mutex> aLock(DE_Wrapper::GlobalLoadMutex());
    myInternalConfiguration->UnRegister(DE_Wrapper::GlobalWrapper());
  }

private:
  occ::handle<TheConfType> myInternalConfiguration; //!< Wrapped object
};

//! Helper class for variadic plugin registration.
//! Allows registration of multiple configuration node types simultaneously.
template <typename... TheConfTypes>
class DE_MultiPluginHolder
{
public:
  DE_MultiPluginHolder()
      : myHolders{}
  {
  }

private:
  std::tuple<DE_PluginHolder<TheConfTypes>...> myHolders; //!< Tuple of individual plugin holders
};

//! Macro to define plugin factory function for DE_Wrapper configuration nodes.
//! @param[in] theNodeType - first configuration node class to instantiate
//! @param[in] ... - additional configuration node classes to instantiate (optional)
//! Needs to be called after loading of the library to register configuration nodes.
//!
//! Example of usage:
//! @code
//! // Inside implementation of the configuration node source file:
//! DEPLUGIN(DESTEP_ConfigurationNode)
//!
//! // For multiple node types:
//! DEPLUGIN(DESTEP_ConfigurationNode, DEIGES_ConfigurationNode, DEVRML_ConfigurationNode)
//! @endcode
//!
//! After loading of the library TKDESTEP:
//! @code
//! OSD_SharedLibrary aSharedLibrary("libTKDESTEP.so");
//! if (!aSharedLibrary.DlOpen(OSD_RTLD_LAZY))
//! {
//!   // Error handling
//!   return;
//! }
//!
//! typedef void (*PluginFactoryFunc)();
//! PluginFactoryFunc aFunc = (PluginFactoryFunc)aSharedLibrary.DlSymb("PLUGINFACTORY");
//! if (aFunc == NULL)
//! {
//!   // Error handling
//!   return;
//! }
//!
//! aFunc(); // Call factory function to register configuration nodes
//! @endcode
//!
//! Will create instances of all specified configuration nodes and set them to DE_Wrapper global
//! configuration.
//!
//! Note: if OCCT_NO_PLUGINS is defined, macro does nothing.
#ifdef OCCT_NO_PLUGINS
  #define DEPLUGIN(theNodeType, ...)
#else
  #define DEPLUGIN(theNodeType, ...)                                                               \
    extern "C" Standard_EXPORT void PLUGINFACTORY()                                                \
    {                                                                                              \
      static DE_MultiPluginHolder<theNodeType, ##__VA_ARGS__> aMultiHolder;                        \
    }
#endif

