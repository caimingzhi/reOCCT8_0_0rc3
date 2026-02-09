#pragma once

#include <Standard.hpp>

#include <MoniTool_TypedValue.hpp>
#include <Interface_ParamType.hpp>
#include <MoniTool_ValueType.hpp>
class TCollection_HAsciiString;

class Interface_TypedValue : public MoniTool_TypedValue
{

public:
  Standard_EXPORT Interface_TypedValue(const char*               name,
                                       const Interface_ParamType type = Interface_ParamText,
                                       const char*               init = "");

  Standard_EXPORT Interface_ParamType Type() const;

  Standard_EXPORT static MoniTool_ValueType ParamTypeToValueType(const Interface_ParamType typ);

  Standard_EXPORT static Interface_ParamType ValueTypeToParamType(const MoniTool_ValueType typ);

  DEFINE_STANDARD_RTTIEXT(Interface_TypedValue, MoniTool_TypedValue)

private:
  TCollection_AsciiString                                   thename;
  TCollection_AsciiString                                   thedef;
  TCollection_AsciiString                                   thelabel;
  occ::handle<Standard_Type>                                theotyp;
  TCollection_AsciiString                                   theunidef;
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> theenums;
  NCollection_DataMap<TCollection_AsciiString, int>         theeadds;
  TCollection_AsciiString                                   thesatisn;
  occ::handle<TCollection_HAsciiString>                     thehval;
  occ::handle<Standard_Transient>                           theoval;
};
