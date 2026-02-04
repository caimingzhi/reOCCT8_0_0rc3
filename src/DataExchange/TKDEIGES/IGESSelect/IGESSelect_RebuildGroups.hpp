#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Rebuilds Groups which were bypassed to produce new models.
//! If a set of entities, all put into a same IGESModel, were
//! part of a same Group in the starting Model, this Modifier
//! rebuilds the original group, but only with the transferred
//! entities. The distinctions (Ordered or not, "WithoutBackP"
//! or not) are renewed, also the name of the group.
//!
//! If the Input Selection is present, tries to rebuild groups
//! only for the selected entities. Else, tries to rebuild
//! groups for all the transferred entities.
class IGESSelect_RebuildGroups : public IGESSelect_ModelModifier
{

public:
  //! Creates an RebuildGroups, which uses the system Date
  Standard_EXPORT IGESSelect_RebuildGroups();

  //! Specific action : Rebuilds the original groups
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Rebuild Groups"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_RebuildGroups, IGESSelect_ModelModifier)
};

