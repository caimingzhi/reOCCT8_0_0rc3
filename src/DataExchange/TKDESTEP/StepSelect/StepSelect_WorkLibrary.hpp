#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_WorkLibrary.hpp>
class Interface_InterfaceModel;
class Interface_Protocol;
class IFSelect_ContextWrite;
class Interface_EntityIterator;
class Interface_CopyTool;

class StepSelect_WorkLibrary : public IFSelect_WorkLibrary
{

public:
  Standard_EXPORT StepSelect_WorkLibrary(const bool copymode = true);

  Standard_EXPORT void SetDumpLabel(const int mode);

  Standard_EXPORT int ReadFile(const char*                            name,
                               occ::handle<Interface_InterfaceModel>& model,
                               const occ::handle<Interface_Protocol>& protocol) const override;

  Standard_EXPORT int ReadStream(const char*                            theName,
                                 std::istream&                          theIStream,
                                 occ::handle<Interface_InterfaceModel>& model,
                                 const occ::handle<Interface_Protocol>& protocol) const override;

  Standard_EXPORT bool WriteFile(IFSelect_ContextWrite& ctx) const override;

  Standard_EXPORT bool CopyModel(const occ::handle<Interface_InterfaceModel>& original,
                                 const occ::handle<Interface_InterfaceModel>& newmodel,
                                 const Interface_EntityIterator&              list,
                                 Interface_CopyTool&                          TC) const override;

  Standard_EXPORT void DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                  const occ::handle<Interface_Protocol>&       protocol,
                                  const occ::handle<Standard_Transient>&       entity,
                                  Standard_OStream&                            S,
                                  const int level) const override;

  DEFINE_STANDARD_RTTIEXT(StepSelect_WorkLibrary, IFSelect_WorkLibrary)

private:
  bool thecopymode;
  int  thelabmode;
};
