#pragma once

#include <Standard.hpp>

#include <IFSelect_Signature.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

class IFSelect_SignType : public IFSelect_Signature
{

public:
  Standard_EXPORT IFSelect_SignType(const bool nopk = false);

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignType, IFSelect_Signature)

private:
  bool thenopk;
};
