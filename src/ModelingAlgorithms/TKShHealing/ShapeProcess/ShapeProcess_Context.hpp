#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class Resource_Manager;
class Message_Messenger;
class TCollection_AsciiString;

//! Provides convenient interface to resource file
//! Allows to load resource file and get values of
//! attributes starting from some scope, for example
//! if scope is defined as "ToV4" and requested parameter
//! is "exec.op", value of "ToV4.exec.op" parameter from
//! the resource file will be returned
class ShapeProcess_Context : public Standard_Transient
{

public:
  //! Creates an empty tool
  Standard_EXPORT ShapeProcess_Context();

  //! Creates a new tool and initialises by name of
  //! resource file and (if specified) starting scope
  //! Calls method Init()
  Standard_EXPORT ShapeProcess_Context(const char* file, const char* scope = "");

  //! Initialises a tool by loading resource file and
  //! (if specified) sets starting scope
  //! Returns False if resource file not found
  Standard_EXPORT bool Init(const char* file, const char* scope = "");

  //! Loading Resource_Manager object if this object not
  //! equal internal static Resource_Manager object or
  //! internal static Resource_Manager object is null
  Standard_EXPORT occ::handle<Resource_Manager> LoadResourceManager(const char* file);

  //! Returns internal Resource_Manager object
  Standard_EXPORT const occ::handle<Resource_Manager>& ResourceManager() const;

  //! Set a new (sub)scope
  Standard_EXPORT void SetScope(const char* scope);

  //! Go out of current scope
  Standard_EXPORT void UnSetScope();

  //! Returns True if parameter is defined in the resource file
  Standard_EXPORT bool IsParamSet(const char* param) const;

  Standard_EXPORT bool GetReal(const char* param, double& val) const;

  Standard_EXPORT bool GetInteger(const char* param, int& val) const;

  Standard_EXPORT bool GetBoolean(const char* param, bool& val) const;

  //! Get value of parameter as being of specific type
  //! Returns False if parameter is not defined or has a wrong type
  Standard_EXPORT bool GetString(const char* param, TCollection_AsciiString& val) const;

  Standard_EXPORT double RealVal(const char* param, const double def) const;

  Standard_EXPORT int IntegerVal(const char* param, const int def) const;

  Standard_EXPORT bool BooleanVal(const char* param, const bool def) const;

  //! Get value of parameter as being of specific type
  //! If parameter is not defined or does not have expected
  //! type, returns default value as specified
  Standard_EXPORT const char* StringVal(const char* param, const char* def) const;

  //! Sets Messenger used for outputting messages.
  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& messenger);

  //! Returns Messenger used for outputting messages.
  Standard_EXPORT occ::handle<Message_Messenger> Messenger() const;

  //! Sets trace level used for outputting messages
  //! - 0: no trace at all
  //! - 1: errors
  //! - 2: errors and warnings
  //! - 3: all messages
  //! Default is 1 : Errors traced
  Standard_EXPORT void SetTraceLevel(const int tracelev);

  //! Returns trace level used for outputting messages.
  Standard_EXPORT int TraceLevel() const;

  DEFINE_STANDARD_RTTIEXT(ShapeProcess_Context, Standard_Transient)

private:
  occ::handle<Resource_Manager>                                             myRC;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> myScope;
  occ::handle<Message_Messenger>                                            myMessenger;
  int                                                                       myTraceLev;
};
