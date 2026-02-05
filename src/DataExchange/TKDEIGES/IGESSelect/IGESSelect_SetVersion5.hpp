#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Sets IGES Version (coded in global parameter 23) to be at least
//! IGES 5.1 . If it is older, it is set to IGES 5.1, and
//! LastChangeDate (new Global n0 25) is added (current time)
//! Else, it does nothing (i.e. changes neither IGES Version nor
//! LastChangeDate)
class IGESSelect_SetVersion5 : public IGESSelect_ModelModifier
{

public:
  //! Creates an SetVersion5, which uses the system Date for Last
  //! Change Date
  Standard_EXPORT IGESSelect_SetVersion5();

  //! Specific action : only <target> is used : IGES Version (coded)
  //! is upgraded to 5.1 if it is older, and it this case the new
  //! global parameter 25 (LastChangeDate) is set to current time
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Update IGES Version to 5.1"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SetVersion5, IGESSelect_ModelModifier)
};
