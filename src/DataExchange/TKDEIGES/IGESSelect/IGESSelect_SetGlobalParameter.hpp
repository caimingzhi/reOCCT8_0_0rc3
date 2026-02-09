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

class IGESSelect_SetGlobalParameter : public IGESSelect_ModelModifier
{

public:
  Standard_EXPORT IGESSelect_SetGlobalParameter(const int numpar);

  Standard_EXPORT int GlobalNumber() const;

  Standard_EXPORT void SetValue(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Value() const;

  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SetGlobalParameter, IGESSelect_ModelModifier)

private:
  int                                   thenum;
  occ::handle<TCollection_HAsciiString> theval;
};
