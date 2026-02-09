#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_PCharacter.hpp>
#include <OSD_LoadMode.hpp>
#include <OSD_Function.hpp>

class OSD_SharedLibrary
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_SharedLibrary();

  Standard_EXPORT OSD_SharedLibrary(const char* aFilename);

  Standard_EXPORT void SetName(const char* aName);

  Standard_EXPORT const char* Name() const;

  Standard_EXPORT bool DlOpen(const OSD_LoadMode Mode);

  Standard_EXPORT OSD_Function DlSymb(const char* Name) const;

  Standard_EXPORT void DlClose() const;

  Standard_EXPORT const char* DlError() const;

  Standard_EXPORT void Destroy();

  ~OSD_SharedLibrary() { Destroy(); }

private:
  void*               myHandle;
  Standard_PCharacter myName;
};
