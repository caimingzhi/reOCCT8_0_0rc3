#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_Binder.hpp>

class Transfer_SimpleBinderOfTransient : public Transfer_Binder
{

public:
  Standard_EXPORT Transfer_SimpleBinderOfTransient();

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  Standard_EXPORT const char* ResultTypeName() const override;

  Standard_EXPORT void SetResult(const occ::handle<Standard_Transient>& res);

  Standard_EXPORT const occ::handle<Standard_Transient>& Result() const;

  Standard_EXPORT static bool GetTypedResult(const occ::handle<Transfer_Binder>& bnd,
                                             const occ::handle<Standard_Type>&   atype,
                                             occ::handle<Standard_Transient>&    res);

  DEFINE_STANDARD_RTTIEXT(Transfer_SimpleBinderOfTransient, Transfer_Binder)

private:
  occ::handle<Standard_Transient> theres;
};
