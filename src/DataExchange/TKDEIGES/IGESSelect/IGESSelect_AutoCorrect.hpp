#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Does the absolutely effective corrections on IGES Entity.
//! That is to say : regarding the norm in details, some values
//! have mandatory values, or set of values with constraints.
//! When such values/constraints are univoque, they can be forced.
//! Also nullifies items of Directory Part, Associativities, and
//! Properties, which are not (or not longer) in <target> Model.
//!
//! Works by calling a BasicEditor from IGESData
//! Works with the specific IGES Services : DirChecker which
//! allows to correct data in "Directory Part" of Entities (such
//! as required values for status, or references to be null), and
//! the specific IGES service OwnCorrect, which is specialised for
//! each type of entity.
//!
//! Remark : this does not comprise the computation of use flag or
//! subordinate status according references, which is made by
//! the ModelModifier class ComputeStatus.
//!
//! The Input Selection, when present, designates the entities to
//! be corrected. If it is not present, all the entities of the
//! model are corrected.
class IGESSelect_AutoCorrect : public IGESSelect_ModelModifier
{

public:
  //! Creates an AutoCorrect.
  Standard_EXPORT IGESSelect_AutoCorrect();

  //! Specific action : corrects entities when it is absolutely
  //! obvious, i.e. non equivoque (by DirChecker and specific
  //! service OwnCorrect) : works with a protocol.
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Auto-correction of IGES Entities"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_AutoCorrect, IGESSelect_ModelModifier)
};

