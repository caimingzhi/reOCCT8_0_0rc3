#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESSelect_ModelModifier.hpp>
class TCollection_HAsciiString;
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Sets a Global (Header) Parameter to a new value, directly given
//! Controls the form of the parameter (Integer, Real, String
//! with such or such form), but not the consistence of the new
//! value regarding the rest of the file.
//!
//! The new value is given under the form of a HAsciiString, even
//! for Integer or Real values. For String values, Hollerith forms
//! are accepted but not mandatory
//! Warning : a Null (not set) value is not accepted. For an empty string,
//! give a Text Parameter which is empty
class IGESSelect_SetGlobalParameter : public IGESSelect_ModelModifier
{

public:
  //! Creates an SetGlobalParameter, to be applied on Global
  //! Parameter <numpar>
  Standard_EXPORT IGESSelect_SetGlobalParameter(const int numpar);

  //! Returns the global parameter number to which this modifiers
  //! applies
  Standard_EXPORT int GlobalNumber() const;

  //! Sets a Text Parameter for the new value
  Standard_EXPORT void SetValue(const occ::handle<TCollection_HAsciiString>& text);

  //! Returns the value to set to the global parameter (Text Param)
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Value() const;

  //! Specific action : only <target> is used : the form of the new
  //! value is checked regarding the parameter number (given at
  //! creation time).
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Sets Global Parameter <numpar> to <new value>"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SetGlobalParameter, IGESSelect_ModelModifier)

private:
  int                                   thenum;
  occ::handle<TCollection_HAsciiString> theval;
};

