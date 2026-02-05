#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Computes Status of IGES Entities for a whole IGESModel.
//! This concerns SubordinateStatus and UseFlag, which must have
//! some definite values according the way they are referenced.
//! (see definitions of Logical use, Physical use, etc...)
//!
//! Works by calling a BasicEditor from IGESData. Works on the
//! whole produced (target) model, because computation is global.
class IGESSelect_ComputeStatus : public IGESSelect_ModelModifier
{

public:
  //! Creates an ComputeStatus, which uses the system Date
  Standard_EXPORT IGESSelect_ComputeStatus();

  //! Specific action : it first evaluates the required values for
  //! Subordinate Status and Use Flag (in Directory Part of each
  //! IGES Entity). Then it corrects them, for the whole target.
  //! Works with a Protocol. Implementation uses BasicEditor
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Compute Subordinate Status and Use Flag"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_ComputeStatus, IGESSelect_ModelModifier)
};
