#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

class IGESSelect_SignLevelNumber : public IFSelect_Signature
{

public:
  Standard_EXPORT IGESSelect_SignLevelNumber(const bool countmode);

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SignLevelNumber, IFSelect_Signature)

private:
  bool thecountmode;
};
