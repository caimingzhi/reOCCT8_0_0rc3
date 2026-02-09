#pragma once

#include <DE_Wrapper.hpp>

#include <mutex>
#include <tuple>

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
  occ::handle<TheConfType> myInternalConfiguration;
};

template <typename... TheConfTypes>
class DE_MultiPluginHolder
{
public:
  DE_MultiPluginHolder()
      : myHolders{}
  {
  }

private:
  std::tuple<DE_PluginHolder<TheConfTypes>...> myHolders;
};

#ifdef OCCT_NO_PLUGINS
  #define DEPLUGIN(theNodeType, ...)
#else
  #define DEPLUGIN(theNodeType, ...)                                                               \
    extern "C" Standard_EXPORT void PLUGINFACTORY()                                                \
    {                                                                                              \
      static DE_MultiPluginHolder<theNodeType, ##__VA_ARGS__> aMultiHolder;                        \
    }
#endif
