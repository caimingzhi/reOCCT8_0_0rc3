#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
class Interface_InterfaceModel;
class Interface_Protocol;
class IFSelect_ContextWrite;
class Interface_EntityIterator;
class Interface_CopyTool;

class IFSelect_WorkLibrary : public Standard_Transient
{

public:
  Standard_EXPORT virtual int ReadFile(const char*                            name,
                                       occ::handle<Interface_InterfaceModel>& model,
                                       const occ::handle<Interface_Protocol>& protocol) const = 0;

  Standard_EXPORT virtual int ReadStream(const char*                            theName,
                                         std::istream&                          theIStream,
                                         occ::handle<Interface_InterfaceModel>& model,
                                         const occ::handle<Interface_Protocol>& protocol) const;

  Standard_EXPORT virtual bool WriteFile(IFSelect_ContextWrite& ctx) const = 0;

  Standard_EXPORT virtual bool CopyModel(const occ::handle<Interface_InterfaceModel>& original,
                                         const occ::handle<Interface_InterfaceModel>& newmodel,
                                         const Interface_EntityIterator&              list,
                                         Interface_CopyTool&                          TC) const;

  Standard_EXPORT virtual void DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                          const occ::handle<Interface_Protocol>&       protocol,
                                          const occ::handle<Standard_Transient>&       entity,
                                          Standard_OStream&                            S,
                                          const int level) const = 0;

  Standard_EXPORT void DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                  const occ::handle<Interface_Protocol>&       protocol,
                                  const occ::handle<Standard_Transient>&       entity,
                                  Standard_OStream&                            S) const;

  Standard_EXPORT void SetDumpLevels(const int def, const int max);

  Standard_EXPORT void DumpLevels(int& def, int& max) const;

  Standard_EXPORT void SetDumpHelp(const int level, const char* help);

  Standard_EXPORT const char* DumpHelp(const int level) const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_WorkLibrary, Standard_Transient)

protected:
  Standard_EXPORT IFSelect_WorkLibrary();

private:
  int                                                                     thelevdef;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> thelevhlp;
};
