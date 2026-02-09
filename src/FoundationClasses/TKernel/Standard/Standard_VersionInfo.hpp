#pragma once

#include <Standard_Macro.hpp>

#ifdef __cplusplus
extern "C"
{
#endif

  Standard_EXPORT const char* OCCT_DevelopmentVersion();

  Standard_EXPORT double OCCT_Version_Double();

  Standard_EXPORT const char* OCCT_Version_String();

  Standard_EXPORT const char* OCCT_Version_String_Complete();

  Standard_EXPORT const char* OCCT_Version_String_Extended();

#ifdef __cplusplus
}
#endif
