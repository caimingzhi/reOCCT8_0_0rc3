

#include <Standard_Transient.hpp>

#include <Standard_Type.hpp>
#include <Standard_CString.hpp>
#include <Standard_ProgramError.hpp>

const Handle(Standard_Type)& Standard_Transient::get_type_descriptor()
{
  static const Handle(Standard_Type) THE_TYPE_INSTANCE =
    Standard_Type::Register(typeid(Standard_Transient),
                            get_type_name(),
                            sizeof(Standard_Transient),
                            nullptr);
  return THE_TYPE_INSTANCE;
}

const Handle(Standard_Type)& Standard_Transient::DynamicType() const
{
  return get_type_descriptor();
}

bool Standard_Transient::IsInstance(const Handle(Standard_Type)& AType) const
{
  return (AType == DynamicType());
}

bool Standard_Transient::IsInstance(const char* theTypeName) const
{
  return IsEqual(DynamicType()->Name(), theTypeName);
}

bool Standard_Transient::IsKind(const Handle(Standard_Type)& aType) const
{
  return DynamicType()->SubType(aType);
}

bool Standard_Transient::IsKind(const char* theTypeName) const
{
  return DynamicType()->SubType(theTypeName);
}

Standard_Transient* Standard_Transient::This() const
{
  if (GetRefCount() == 0)
    throw Standard_ProgramError(
      "Attempt to create handle to object created in stack, not yet constructed, or destroyed");
  return const_cast<Standard_Transient*>(this);
}
