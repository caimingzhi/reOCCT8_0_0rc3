#pragma once

#include <Standard_Macro.hpp>

#ifdef __cplusplus
extern "C"
{
#endif
  //! Returns development version of Open CASCADE Technology.
  //! "" - in case of official release,
  //! "dev" - in case of development version between releases,
  //! "beta..." or "rc..." - in case of beta releases or release candidates,
  //! "project..." - in case of version containing project-specific fixes.
  Standard_EXPORT const char* OCCT_DevelopmentVersion();

  //! Returns version of Open CASCADE Technology as a double "major.minor"
  Standard_EXPORT double OCCT_Version_Double();

  //! Returns version of Open CASCADE Technology as a string "major.minor"
  Standard_EXPORT const char* OCCT_Version_String();

  //! Returns complete version of Open CASCADE Technology as a string "major.minor.maintenance"
  Standard_EXPORT const char* OCCT_Version_String_Complete();

  //! Returns extended version of Open CASCADE Technology as a string
  //! "major.minor.maintenance.devext". In case if no development version is defined, returns the
  //! same as OCCT_Version_String_Complete().
  Standard_EXPORT const char* OCCT_Version_String_Extended();

#ifdef __cplusplus
}
#endif
