

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransferFailure.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_SimpleBinderOfTransient, Transfer_Binder)

Transfer_SimpleBinderOfTransient::Transfer_SimpleBinderOfTransient() = default;

occ::handle<Standard_Type> Transfer_SimpleBinderOfTransient::ResultType() const
{
  if (!HasResult() || theres.IsNull())
    return STANDARD_TYPE(Standard_Transient);
  return Result()->DynamicType();
}

const char* Transfer_SimpleBinderOfTransient::ResultTypeName() const
{
  if (!HasResult() || theres.IsNull())
    return "(void)";
  return Result()->DynamicType()->Name();
}

void Transfer_SimpleBinderOfTransient::SetResult(const occ::handle<Standard_Transient>& res)
{
  SetResultPresent();
  theres = res;
}

const occ::handle<Standard_Transient>& Transfer_SimpleBinderOfTransient::Result() const
{
  return theres;
}

bool Transfer_SimpleBinderOfTransient::GetTypedResult(const occ::handle<Transfer_Binder>& bnd,
                                                      const occ::handle<Standard_Type>&   atype,
                                                      occ::handle<Standard_Transient>&    res)
{
  if (atype.IsNull())
    return false;
  occ::handle<Transfer_Binder> bn = bnd;
  while (!bn.IsNull())
  {
    occ::handle<Transfer_SimpleBinderOfTransient> trb =
      occ::down_cast<Transfer_SimpleBinderOfTransient>(bn);
    bn = bn->NextResult();
    if (trb.IsNull())
      continue;
    const occ::handle<Standard_Transient>& rs = trb->Result();
    if (rs.IsNull())
      continue;
    if (!rs->IsKind(atype))
      continue;
    res = rs;
    return true;
  }
  return false;
}
