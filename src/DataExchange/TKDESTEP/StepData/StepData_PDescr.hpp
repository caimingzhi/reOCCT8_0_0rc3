#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <StepData_EnumTool.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
class StepData_EDescr;
class StepData_Field;
class Interface_Check;

class StepData_PDescr : public Standard_Transient
{

public:
  Standard_EXPORT StepData_PDescr();

  Standard_EXPORT void SetName(const char* name);

  Standard_EXPORT const char* Name() const;

  Standard_EXPORT void SetSelect();

  Standard_EXPORT void AddMember(const occ::handle<StepData_PDescr>& member);

  Standard_EXPORT void SetMemberName(const char* memname);

  Standard_EXPORT void SetInteger();

  Standard_EXPORT void SetReal();

  Standard_EXPORT void SetString();

  Standard_EXPORT void SetBoolean();

  Standard_EXPORT void SetLogical();

  Standard_EXPORT void SetEnum();

  Standard_EXPORT void AddEnumDef(const char* enumdef);

  Standard_EXPORT void SetType(const occ::handle<Standard_Type>& atype);

  Standard_EXPORT void SetDescr(const char* dscnam);

  Standard_EXPORT void AddArity(const int arity = 1);

  Standard_EXPORT void SetArity(const int arity = 1);

  Standard_EXPORT void SetFrom(const occ::handle<StepData_PDescr>& other);

  Standard_EXPORT void SetOptional(const bool opt = true);

  Standard_EXPORT void SetDerived(const bool der = true);

  Standard_EXPORT void SetField(const char* name, const int rank);

  Standard_EXPORT bool IsSelect() const;

  Standard_EXPORT occ::handle<StepData_PDescr> Member(const char* name) const;

  Standard_EXPORT bool IsInteger() const;

  Standard_EXPORT bool IsReal() const;

  Standard_EXPORT bool IsString() const;

  Standard_EXPORT bool IsBoolean() const;

  Standard_EXPORT bool IsLogical() const;

  Standard_EXPORT bool IsEnum() const;

  Standard_EXPORT int EnumMax() const;

  Standard_EXPORT int EnumValue(const char* name) const;

  Standard_EXPORT const char* EnumText(const int val) const;

  Standard_EXPORT bool IsEntity() const;

  Standard_EXPORT bool IsType(const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT occ::handle<Standard_Type> Type() const;

  Standard_EXPORT bool IsDescr(const occ::handle<StepData_EDescr>& descr) const;

  Standard_EXPORT const char* DescrName() const;

  Standard_EXPORT int Arity() const;

  Standard_EXPORT occ::handle<StepData_PDescr> Simple() const;

  Standard_EXPORT bool IsOptional() const;

  Standard_EXPORT bool IsDerived() const;

  Standard_EXPORT bool IsField() const;

  Standard_EXPORT const char* FieldName() const;

  Standard_EXPORT int FieldRank() const;

  Standard_EXPORT virtual void Check(const StepData_Field&         afild,
                                     occ::handle<Interface_Check>& ach) const;

  DEFINE_STANDARD_RTTIEXT(StepData_PDescr, Standard_Transient)

private:
  Standard_EXPORT int Kind() const;

  TCollection_AsciiString      thename;
  int                          thesel;
  TCollection_AsciiString      thesnam;
  occ::handle<StepData_PDescr> thenext;
  int                          thekind;
  StepData_EnumTool            theenum;
  occ::handle<Standard_Type>   thetype;
  TCollection_AsciiString      thednam;
  int                          thearit;
  occ::handle<StepData_PDescr> thefrom;
  bool                         theopt;
  bool                         theder;
  TCollection_AsciiString      thefnam;
  int                          thefnum;
};
