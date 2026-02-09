#pragma once

#include <Standard.hpp>

#include <MoniTool_ValueType.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include <TCollection_HAsciiString.hpp>

class MoniTool_TypedValue;
typedef occ::handle<TCollection_HAsciiString> (*MoniTool_ValueInterpret)(
  const occ::handle<MoniTool_TypedValue>&      typval,
  const occ::handle<TCollection_HAsciiString>& val,
  const bool                                   native);

#include <TCollection_HAsciiString.hpp>

typedef bool (*MoniTool_ValueSatisfies)(const occ::handle<TCollection_HAsciiString>& val);

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class TCollection_HAsciiString;

class MoniTool_TypedValue : public Standard_Transient
{

public:
  Standard_EXPORT MoniTool_TypedValue(const char*              name,
                                      const MoniTool_ValueType type = MoniTool_ValueText,
                                      const char*              init = "");

  Standard_EXPORT MoniTool_TypedValue(const occ::handle<MoniTool_TypedValue>& other);

  Standard_EXPORT void Internals(MoniTool_ValueInterpret&                           interp,
                                 MoniTool_ValueSatisfies&                           satisf,
                                 const char*&                                       satisname,
                                 NCollection_DataMap<TCollection_AsciiString, int>& enums) const;

  Standard_EXPORT const char* Name() const;

  Standard_EXPORT MoniTool_ValueType ValueType() const;

  Standard_EXPORT TCollection_AsciiString Definition() const;

  Standard_EXPORT void SetDefinition(const char* deftext);

  Standard_EXPORT virtual void Print(Standard_OStream& S) const;

  Standard_EXPORT void PrintValue(Standard_OStream& S) const;

  Standard_EXPORT bool AddDef(const char* initext);

  Standard_EXPORT void SetLabel(const char* label);

  Standard_EXPORT const char* Label() const;

  Standard_EXPORT void SetMaxLength(const int max);

  Standard_EXPORT int MaxLength() const;

  Standard_EXPORT void SetIntegerLimit(const bool max, const int val);

  Standard_EXPORT bool IntegerLimit(const bool max, int& val) const;

  Standard_EXPORT void SetRealLimit(const bool max, const double val);

  Standard_EXPORT bool RealLimit(const bool max, double& val) const;

  Standard_EXPORT void SetUnitDef(const char* def);

  Standard_EXPORT const char* UnitDef() const;

  Standard_EXPORT void StartEnum(const int start = 0, const bool match = true);

  Standard_EXPORT void AddEnum(const char* v1  = "",
                               const char* v2  = "",
                               const char* v3  = "",
                               const char* v4  = "",
                               const char* v5  = "",
                               const char* v6  = "",
                               const char* v7  = "",
                               const char* v8  = "",
                               const char* v9  = "",
                               const char* v10 = "");

  Standard_EXPORT void AddEnumValue(const char* val, const int num);

  Standard_EXPORT bool EnumDef(int& startcase, int& endcase, bool& match) const;

  Standard_EXPORT const char* EnumVal(const int num) const;

  Standard_EXPORT int EnumCase(const char* val) const;

  Standard_EXPORT void SetObjectType(const occ::handle<Standard_Type>& typ);

  Standard_EXPORT occ::handle<Standard_Type> ObjectType() const;

  Standard_EXPORT void SetInterpret(const MoniTool_ValueInterpret func);

  Standard_EXPORT virtual bool HasInterpret() const;

  Standard_EXPORT void SetSatisfies(const MoniTool_ValueSatisfies func, const char* name);

  Standard_EXPORT const char* SatisfiesName() const;

  Standard_EXPORT bool IsSetValue() const;

  Standard_EXPORT const char* CStringValue() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> HStringValue() const;

  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> Interpret(
    const occ::handle<TCollection_HAsciiString>& hval,
    const bool                                   native) const;

  Standard_EXPORT virtual bool Satisfies(const occ::handle<TCollection_HAsciiString>& hval) const;

  Standard_EXPORT void ClearValue();

  Standard_EXPORT virtual bool SetCStringValue(const char* val);

  Standard_EXPORT virtual bool SetHStringValue(const occ::handle<TCollection_HAsciiString>& hval);

  Standard_EXPORT int IntegerValue() const;

  Standard_EXPORT virtual bool SetIntegerValue(const int ival);

  Standard_EXPORT double RealValue() const;

  Standard_EXPORT virtual bool SetRealValue(const double rval);

  Standard_EXPORT occ::handle<Standard_Transient> ObjectValue() const;

  Standard_EXPORT void GetObjectValue(occ::handle<Standard_Transient>& val) const;

  Standard_EXPORT virtual bool SetObjectValue(const occ::handle<Standard_Transient>& obj);

  Standard_EXPORT const char* ObjectTypeName() const;

  Standard_EXPORT static bool AddLib(const occ::handle<MoniTool_TypedValue>& tv,
                                     const char*                             def = "");

  Standard_EXPORT static occ::handle<MoniTool_TypedValue> Lib(const char* def);

  Standard_EXPORT static occ::handle<MoniTool_TypedValue> FromLib(const char* def);

  Standard_EXPORT static occ::handle<NCollection_HSequence<TCollection_AsciiString>> LibList();

  Standard_EXPORT static occ::handle<MoniTool_TypedValue> StaticValue(const char* name);

  DEFINE_STANDARD_RTTIEXT(MoniTool_TypedValue, Standard_Transient)

protected:
  Standard_EXPORT static NCollection_DataMap<TCollection_AsciiString,
                                             occ::handle<Standard_Transient>>&
    Stats();

private:
  TCollection_AsciiString                                   thename;
  TCollection_AsciiString                                   thedef;
  TCollection_AsciiString                                   thelabel;
  MoniTool_ValueType                                        thetype;
  occ::handle<Standard_Type>                                theotyp;
  int                                                       thelims;
  int                                                       themaxlen;
  int                                                       theintlow;
  int                                                       theintup;
  double                                                    therealow;
  double                                                    therealup;
  TCollection_AsciiString                                   theunidef;
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> theenums;
  NCollection_DataMap<TCollection_AsciiString, int>         theeadds;
  MoniTool_ValueInterpret                                   theinterp;
  MoniTool_ValueSatisfies                                   thesatisf;
  TCollection_AsciiString                                   thesatisn;
  int                                                       theival;
  occ::handle<TCollection_HAsciiString>                     thehval;
  occ::handle<Standard_Transient>                           theoval;
};
