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

//! Performs Read and Write an IGES File with an IGES Model
class IGESSelect_WorkLibrary : public IFSelect_WorkLibrary
{

public:
  //! Creates a IGES WorkLibrary
  //! If <modefnes> is given as True, it will work for FNES
  Standard_EXPORT IGESSelect_WorkLibrary(const bool modefnes = false);

  //! Reads a IGES File and returns a IGES Model (into <mod>),
  //! or lets <mod> "Null" in case of Error
  //! Returns 0 if OK, 1 if Read Error, -1 if File not opened
  Standard_EXPORT int ReadFile(const char*                            name,
                               occ::handle<Interface_InterfaceModel>& model,
                               const occ::handle<Interface_Protocol>& protocol) const override;

  //! Writes a File from a IGES Model (brought by <ctx>)
  //! Returns False (and writes no file) if <ctx> is not for IGES
  Standard_EXPORT bool WriteFile(IFSelect_ContextWrite& ctx) const override;

  //! Defines a protocol to be adequate for IGES
  //! (encompasses ALL the IGES norm including IGESSolid, IGESAppli)
  Standard_EXPORT static occ::handle<IGESData_Protocol> DefineProtocol();

  //! Dumps an IGES Entity with an IGES Dumper. <level> is the one
  //! used by IGESDumper.
  Standard_EXPORT void DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                  const occ::handle<Interface_Protocol>&       protocol,
                                  const occ::handle<Standard_Transient>&       entity,
                                  Standard_OStream&                            S,
                                  const int level) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_WorkLibrary, IFSelect_WorkLibrary)

private:
  bool themodefnes;
};
