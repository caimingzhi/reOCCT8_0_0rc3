#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_IntParam;
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

class IGESSelect_ChangeLevelList : public IGESSelect_ModelModifier
{

public:
  Standard_EXPORT IGESSelect_ChangeLevelList();

  Standard_EXPORT bool HasOldNumber() const;

  Standard_EXPORT occ::handle<IFSelect_IntParam> OldNumber() const;

  Standard_EXPORT void SetOldNumber(const occ::handle<IFSelect_IntParam>& param);

  Standard_EXPORT bool HasNewNumber() const;

  Standard_EXPORT occ::handle<IFSelect_IntParam> NewNumber() const;

  Standard_EXPORT void SetNewNumber(const occ::handle<IFSelect_IntParam>& param);

  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_ChangeLevelList, IGESSelect_ModelModifier)

private:
  occ::handle<IFSelect_IntParam> theold;
  occ::handle<IFSelect_IntParam> thenew;
};
