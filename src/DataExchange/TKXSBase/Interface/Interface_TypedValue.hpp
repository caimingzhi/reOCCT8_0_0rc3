#pragma once


#include <Standard.hpp>

#include <MoniTool_TypedValue.hpp>
#include <Interface_ParamType.hpp>
#include <MoniTool_ValueType.hpp>
class TCollection_HAsciiString;

//! Now strictly equivalent to TypedValue from MoniTool,
//! except for ParamType which remains for compatibility reasons
//!
//! This class allows to dynamically manage .. typed values, i.e.
//! values which have an alphanumeric expression, but with
//! controls. Such as "must be an Integer" or "Enumerative Text"
//! etc
//!
//! Hence, a TypedValue brings a specification (type + constraints
//! if any) and a value. Its basic form is a string, it can be
//! specified as integer or real or enumerative string, then
//! queried as such.
//! Its string content, which is a occ::handle<HAsciiString> can be
//! shared by other data structures, hence gives a direct on line
//! access to its value.
class Interface_TypedValue : public MoniTool_TypedValue
{

public:
  //! Creates a TypedValue, with a name
  //!
  //! type gives the type of the parameter, default is free text
  //! Also available : Integer, Real, Enum, Entity (i.e. Object)
  //! More precise specifications, titles, can be given to the
  //! TypedValue once created
  //!
  //! init gives an initial value. If it is not given, the
  //! TypedValue begins as "not set", its value is empty
  Standard_EXPORT Interface_TypedValue(const char*               name,
                                       const Interface_ParamType type = Interface_ParamText,
                                       const char*               init = "");

  //! Returns the type
  //! I.E. calls ValueType then makes correspondence between
  //! ParamType from Interface (which remains for compatibility
  //! reasons) and ValueType from MoniTool
  Standard_EXPORT Interface_ParamType Type() const;

  //! Correspondence ParamType from Interface to ValueType from MoniTool
  Standard_EXPORT static MoniTool_ValueType ParamTypeToValueType(const Interface_ParamType typ);

  //! Correspondence ParamType from Interface to ValueType from MoniTool
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

