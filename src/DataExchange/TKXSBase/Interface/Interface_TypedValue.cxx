

#include <Interface_TypedValue.hpp>
#include <OSD_Path.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(Interface_TypedValue, MoniTool_TypedValue)

Interface_TypedValue::Interface_TypedValue(const char*               name,
                                           const Interface_ParamType type,
                                           const char*               init)
    : MoniTool_TypedValue(name, Interface_TypedValue::ParamTypeToValueType(type), init)
{
}

Interface_ParamType Interface_TypedValue::Type() const
{
  return ValueTypeToParamType(ValueType());
}

MoniTool_ValueType Interface_TypedValue::ParamTypeToValueType(const Interface_ParamType type)
{
  return (MoniTool_ValueType)type;
}

Interface_ParamType Interface_TypedValue::ValueTypeToParamType(const MoniTool_ValueType type)
{
  return (Interface_ParamType)type;
}
