#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

#ifdef SetForm
  #undef SetForm
#endif

class IGESSelect_IGESTypeForm : public IFSelect_Signature
{

public:
  Standard_EXPORT IGESSelect_IGESTypeForm(const bool withform = true);

  Standard_EXPORT void SetForm(const bool withform);

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_IGESTypeForm, IFSelect_Signature)

private:
  bool theform;
};
