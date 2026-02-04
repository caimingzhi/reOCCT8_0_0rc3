#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Allows to Change the Creation Date indication in the Header
//! (Global Section) of IGES File. It is taken from the operating
//! system (time of application of the Modifier).
//! The Selection of the Modifier is not used : it simply acts as
//! a criterium to select IGES Files to touch up
class IGESSelect_UpdateCreationDate : public IGESSelect_ModelModifier
{

public:
  //! Creates an UpdateCreationDate, which uses the system Date
  Standard_EXPORT IGESSelect_UpdateCreationDate();

  //! Specific action : only <target> is used : the system Date
  //! is set to Global Section Item n0 18.
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Update IGES Header Creation Date"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_UpdateCreationDate, IGESSelect_ModelModifier)
};

