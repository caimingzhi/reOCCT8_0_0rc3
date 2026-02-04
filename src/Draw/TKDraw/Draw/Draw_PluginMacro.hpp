#pragma once


#ifdef OCCT_NO_PLUGINS
  #define DPLUGIN(name)
#else
  #define DPLUGIN(name)                                                                            \
    extern "C" Standard_EXPORT void PLUGINFACTORY(Draw_Interpretor& theDI)                         \
    {                                                                                              \
      name::Factory(theDI);                                                                        \
    }
#endif

