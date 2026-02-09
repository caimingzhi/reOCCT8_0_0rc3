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

class ShapeProcess_Context : public Standard_Transient
{

public:
  Standard_EXPORT ShapeProcess_Context();

  Standard_EXPORT ShapeProcess_Context(const char* file, const char* scope = "");

  Standard_EXPORT bool Init(const char* file, const char* scope = "");

  Standard_EXPORT occ::handle<Resource_Manager> LoadResourceManager(const char* file);

  Standard_EXPORT const occ::handle<Resource_Manager>& ResourceManager() const;

  Standard_EXPORT void SetScope(const char* scope);

  Standard_EXPORT void UnSetScope();

  Standard_EXPORT bool IsParamSet(const char* param) const;

  Standard_EXPORT bool GetReal(const char* param, double& val) const;

  Standard_EXPORT bool GetInteger(const char* param, int& val) const;

  Standard_EXPORT bool GetBoolean(const char* param, bool& val) const;

  Standard_EXPORT bool GetString(const char* param, TCollection_AsciiString& val) const;

  Standard_EXPORT double RealVal(const char* param, const double def) const;

  Standard_EXPORT int IntegerVal(const char* param, const int def) const;

  Standard_EXPORT bool BooleanVal(const char* param, const bool def) const;

  Standard_EXPORT const char* StringVal(const char* param, const char* def) const;

  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& messenger);

  Standard_EXPORT occ::handle<Message_Messenger> Messenger() const;

  Standard_EXPORT void SetTraceLevel(const int tracelev);

  Standard_EXPORT int TraceLevel() const;

  DEFINE_STANDARD_RTTIEXT(ShapeProcess_Context, Standard_Transient)

private:
  occ::handle<Resource_Manager>                                             myRC;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> myScope;
  occ::handle<Message_Messenger>                                            myMessenger;
  int                                                                       myTraceLev;
};
