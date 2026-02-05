#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Adds a Group to contain the entities designated by the
//! Selection. If no Selection is given, nothing is done
class IGESSelect_AddGroup : public IGESSelect_ModelModifier
{

public:
  //! Creates an AddGroup
  Standard_EXPORT IGESSelect_AddGroup();

  //! Specific action : Adds a new group
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Add Group"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_AddGroup, IGESSelect_ModelModifier)
};
