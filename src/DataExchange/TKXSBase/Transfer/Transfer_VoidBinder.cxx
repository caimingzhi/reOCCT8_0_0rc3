#include <Standard_Type.hpp>
#include <Transfer_VoidBinder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_VoidBinder, Transfer_Binder)

Transfer_VoidBinder::Transfer_VoidBinder() = default;

//    bool  Transfer_VoidBinder::IsMultiple () const
//      { return false;  }

occ::handle<Standard_Type> Transfer_VoidBinder::ResultType() const
{
  return DynamicType();
}

const char* Transfer_VoidBinder::ResultTypeName() const
{
  return "(void)";
}
