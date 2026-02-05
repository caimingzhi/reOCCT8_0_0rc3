#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Sets/Clears Short Label of Entities, those designated by the
//! Selection. No Selection means all the file
//!
//! May enforce, else it sets only if no label is yet set
//! Mode : 0 to clear (always enforced)
//! 1 to set label to DE number (changes it if already set)
class IGESSelect_SetLabel : public IGESSelect_ModelModifier
{

public:
  //! Creates a SetLabel for IGESEntity
  //! Mode : see Purpose of the class
  Standard_EXPORT IGESSelect_SetLabel(const int mode, const bool enforce);

  //! Specific action : Sets or Clears the Label
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Clear Short Label" or "Set Label to DE"
  //! With possible additional information " (enforced)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SetLabel, IGESSelect_ModelModifier)

private:
  int  themode;
  bool theforce;
};
