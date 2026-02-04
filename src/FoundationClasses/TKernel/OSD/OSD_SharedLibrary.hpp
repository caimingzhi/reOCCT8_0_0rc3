#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_PCharacter.hpp>
#include <OSD_LoadMode.hpp>
#include <OSD_Function.hpp>

//! Interface to dynamic library loader.
//! Provides tools to load a shared library
//! and retrieve the address of an entry point.
class OSD_SharedLibrary
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a SharedLibrary object with name NULL.
  Standard_EXPORT OSD_SharedLibrary();

  //! Creates a SharedLibrary object with name aFilename.
  Standard_EXPORT OSD_SharedLibrary(const char* aFilename);

  //! Sets a name associated to the shared object.
  Standard_EXPORT void SetName(const char* aName);

  //! Returns the name associated to the shared object.
  Standard_EXPORT const char* Name() const;

  //! The DlOpen method provides an interface to the
  //! dynamic library loader to allow shared libraries
  //! to be loaded and called at runtime. The DlOpen
  //! function attempts to load Filename, in the address
  //! space of the process, resolving symbols as appropriate.
  //! Any libraries that Filename depends upon are also loaded.
  //! If MODE is RTLD_LAZY, then the runtime loader
  //! does symbol resolution only as needed.
  //! Typically, this means that the first call to a function
  //! in the newly	loaded library will cause the resolution of
  //! the	address	of that	function to occur.
  //! If Mode is RTLD_NOW, then the runtime loader must do all
  //! symbol binding during the DlOpen call.
  //! The DlOpen method returns a	handle that is used by DlSym
  //! or DlClose.
  //! If there is an error, false is returned,
  //! true otherwise.
  //! If a NULL Filename is specified, DlOpen returns a handle
  //! for the main	executable, which allows access to dynamic
  //! symbols in the running program.
  Standard_EXPORT bool DlOpen(const OSD_LoadMode Mode);

  //! The dlsym function returns the address of the
  //! symbol name found in the shared library.
  //! If the symbol is not found, a NULL pointer is
  //! returned.
  Standard_EXPORT OSD_Function DlSymb(const char* Name) const;

  //! Deallocates the address space for the library
  //! corresponding to the shared object.
  //! If any user function continues to call a symbol
  //! resolved in the address space of a library
  //! that has been since been deallocated by DlClose,
  //! the results are undefined.
  Standard_EXPORT void DlClose() const;

  //! The dlerror function returns a string describing
  //! the last error that occurred from
  //! a call to DlOpen, DlClose or DlSym.
  Standard_EXPORT const char* DlError() const;

  //! Frees memory allocated.
  Standard_EXPORT void Destroy();

  ~OSD_SharedLibrary() { Destroy(); }

private:
  void*               myHandle;
  Standard_PCharacter myName;
};

