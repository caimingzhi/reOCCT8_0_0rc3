#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Modifier.hpp>
class IFSelect_ContextModif;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_CopyTool;
class TCollection_AsciiString;

class IFSelect_ModifReorder : public IFSelect_Modifier
{

public:
  Standard_EXPORT IFSelect_ModifReorder(const bool rootlast = true);

  Standard_EXPORT void Perform(IFSelect_ContextModif&                       ctx,
                               const occ::handle<Interface_InterfaceModel>& target,
                               const occ::handle<Interface_Protocol>&       protocol,
                               Interface_CopyTool&                          TC) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_ModifReorder, IFSelect_Modifier)

private:
  bool thertl;
};
