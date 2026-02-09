#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class IGESSelect_SignStatus : public IFSelect_Signature
{

public:
  Standard_EXPORT IGESSelect_SignStatus();

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const TCollection_AsciiString&               text,
                               const bool                                   exact) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SignStatus, IFSelect_Signature)
};
