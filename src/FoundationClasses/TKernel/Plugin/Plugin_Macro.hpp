#pragma once

#ifdef OCCT_NO_PLUGINS
  #define PLUGIN(name)
#else

  #define PLUGIN(name)                                                                             \
    extern "C" Standard_EXPORT Standard_Transient* PLUGINFACTORY(const Standard_GUID& aGUID)       \
    {                                                                                              \
      return const_cast<Standard_Transient*>(name::Factory(aGUID).get());                          \
    }
#endif
