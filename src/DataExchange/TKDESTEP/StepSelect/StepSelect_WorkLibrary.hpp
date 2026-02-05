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

//! Performs Read and Write a STEP File with a STEP Model
//! Following the protocols, Copy may be implemented or not
class StepSelect_WorkLibrary : public IFSelect_WorkLibrary
{

public:
  //! Creates a STEP WorkLibrary
  //! <copymode> precises whether Copy is implemented or not
  Standard_EXPORT StepSelect_WorkLibrary(const bool copymode = true);

  //! Selects a mode to dump entities
  //! 0 (D) : prints numbers, then displays table number/label
  //! 1 : prints labels, then displays table label/number
  //! 2 : prints labels onky
  Standard_EXPORT void SetDumpLabel(const int mode);

  //! Reads a STEP File and returns a STEP Model (into <mod>),
  //! or lets <mod> "Null" in case of Error
  //! Returns 0 if OK, 1 if Read Error, -1 if File not opened
  Standard_EXPORT int ReadFile(const char*                            name,
                               occ::handle<Interface_InterfaceModel>& model,
                               const occ::handle<Interface_Protocol>& protocol) const override;

  //! Reads a STEP File from stream and returns a STEP Model (into <mod>),
  //! or lets <mod> "Null" in case of Error
  //! Returns 0 if OK, 1 if Read Error, -1 if File not opened
  Standard_EXPORT int ReadStream(const char*                            theName,
                                 std::istream&                          theIStream,
                                 occ::handle<Interface_InterfaceModel>& model,
                                 const occ::handle<Interface_Protocol>& protocol) const override;

  //! Writes a File from a STEP Model
  //! Returns False (and writes no file) if <ctx> does not bring a
  //! STEP Model
  Standard_EXPORT bool WriteFile(IFSelect_ContextWrite& ctx) const override;

  //! Performs the copy of entities from an original model to a new
  //! one. Works according <copymode> :
  //! if True, standard copy is run
  //! else nothing is done and returned value is False
  Standard_EXPORT bool CopyModel(const occ::handle<Interface_InterfaceModel>& original,
                                 const occ::handle<Interface_InterfaceModel>& newmodel,
                                 const Interface_EntityIterator&              list,
                                 Interface_CopyTool&                          TC) const override;

  //! Dumps an entity under STEP form, i.e. as a part of a Step file
  //! Works with a StepDumper.
  //! Level 0 just displays type; level 1 displays the entity itself
  //! and level 2 displays the entity plus its shared ones (one
  //! sub-level : immediately shared entities)
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
