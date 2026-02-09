#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_GeneralModifier.hpp>
class IFSelect_ContextModif;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_CopyTool;

class IFSelect_Modifier : public IFSelect_GeneralModifier
{

public:
  Standard_EXPORT virtual void Perform(IFSelect_ContextModif&                       ctx,
                                       const occ::handle<Interface_InterfaceModel>& target,
                                       const occ::handle<Interface_Protocol>&       protocol,
                                       Interface_CopyTool&                          TC) const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_Modifier, IFSelect_GeneralModifier)

protected:
  Standard_EXPORT IFSelect_Modifier(const bool maychangegraph);
};
