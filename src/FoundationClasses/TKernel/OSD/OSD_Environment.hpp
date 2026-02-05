#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>

//! Management of system environment variables
//! An environment variable is composed of a variable name
//! and its value.
//!
//! To be portable among various systems, environment variables
//! are local to a process.
class OSD_Environment
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates the object Environment.
  Standard_EXPORT OSD_Environment();

  //! Creates an Environment variable initialized with value
  //! set to an empty AsciiString.
  Standard_EXPORT OSD_Environment(const TCollection_AsciiString& Name);

  //! Creates an Environment variable initialized with Value.
  Standard_EXPORT OSD_Environment(const TCollection_AsciiString& Name,
                                  const TCollection_AsciiString& Value);

  //! Changes environment variable value.
  //! Raises ConstructionError either if the string contains
  //! characters not in range of ' '...'~' or if the string
  //! contains the character '$' which is forbidden.
  Standard_EXPORT void SetValue(const TCollection_AsciiString& Value);

  //! Gets the value of an environment variable
  Standard_EXPORT TCollection_AsciiString Value();

  //! Changes environment variable name.
  //! Raises ConstructionError either if the string contains
  //! characters not in range of ' '...'~' or if the string
  //! contains the character '$' which is forbidden.
  Standard_EXPORT void SetName(const TCollection_AsciiString& name);

  //! Gets the name of <me>.
  Standard_EXPORT TCollection_AsciiString Name() const;

  //! Sets the value of an environment variable
  //! into system (physically).
  Standard_EXPORT void Build();

  //! Removes (physically) an environment variable
  Standard_EXPORT void Remove();

  //! Returns TRUE if an error occurs
  Standard_EXPORT bool Failed() const;

  //! Resets error counter to zero
  Standard_EXPORT void Reset();

  //! Raises OSD_Error
  Standard_EXPORT void Perror();

  //! Returns error number if 'Failed' is TRUE.
  Standard_EXPORT int Error() const;

private:
  TCollection_AsciiString myName;
  TCollection_AsciiString myValue;
  OSD_Error               myError;
};
