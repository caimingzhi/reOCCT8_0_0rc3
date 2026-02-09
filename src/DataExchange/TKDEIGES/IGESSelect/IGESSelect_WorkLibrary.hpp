#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_WorkLibrary.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class Interface_Protocol;
class IFSelect_ContextWrite;
class IGESData_Protocol;
class Standard_Transient;

class IGESSelect_WorkLibrary : public IFSelect_WorkLibrary
{

public:
  Standard_EXPORT IGESSelect_WorkLibrary(const bool modefnes = false);

  Standard_EXPORT int ReadFile(const char*                            name,
                               occ::handle<Interface_InterfaceModel>& model,
                               const occ::handle<Interface_Protocol>& protocol) const override;

  Standard_EXPORT bool WriteFile(IFSelect_ContextWrite& ctx) const override;

  Standard_EXPORT static occ::handle<IGESData_Protocol> DefineProtocol();

  Standard_EXPORT void DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                  const occ::handle<Interface_Protocol>&       protocol,
                                  const occ::handle<Standard_Transient>&       entity,
                                  Standard_OStream&                            S,
                                  const int level) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_WorkLibrary, IFSelect_WorkLibrary)

private:
  bool themodefnes;
};
