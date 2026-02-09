

#include <Standard_Type.hpp>
#include <Transfer_BinderOfTransientInteger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_BinderOfTransientInteger, Transfer_SimpleBinderOfTransient)

Transfer_BinderOfTransientInteger::Transfer_BinderOfTransientInteger()
    : theintval(0)
{
}

void Transfer_BinderOfTransientInteger::SetInteger(const int val)
{
  theintval = val;
}

int Transfer_BinderOfTransientInteger::Integer() const
{
  return theintval;
}
