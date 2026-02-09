#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <StepData_Logical.hpp>
#include <Standard_CString.hpp>
class StepData_SelectMember;

class StepData_Field
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_Field();

  Standard_EXPORT StepData_Field(const StepData_Field& other, const bool copy = false);

  Standard_EXPORT void CopyFrom(const StepData_Field& other);

  StepData_Field& operator=(const StepData_Field& theOther)
  {
    CopyFrom(theOther);
    return *this;
  }

  Standard_EXPORT void Clear(const int kind = 0);

  Standard_EXPORT void SetDerived();

  Standard_EXPORT void SetInt(const int val);

  Standard_EXPORT void SetInteger(const int val = 0);

  Standard_EXPORT void SetBoolean(const bool val = false);

  Standard_EXPORT void SetLogical(const StepData_Logical val = StepData_LFalse);

  Standard_EXPORT void SetReal(const double val = 0.0);

  Standard_EXPORT void SetString(const char* val = "");

  Standard_EXPORT void SetEnum(const int val = -1, const char* text = "");

  Standard_EXPORT void SetSelectMember(const occ::handle<StepData_SelectMember>& val);

  Standard_EXPORT void SetEntity(const occ::handle<Standard_Transient>& val);

  Standard_EXPORT void SetEntity();

  Standard_EXPORT void SetList(const int size, const int first = 1);

  Standard_EXPORT void SetList2(const int siz1, const int siz2, const int f1 = 1, const int f2 = 1);

  Standard_EXPORT void Set(const occ::handle<Standard_Transient>& val);

  Standard_EXPORT void ClearItem(const int num);

  Standard_EXPORT void SetInt(const int num, const int val, const int kind);

  Standard_EXPORT void SetInteger(const int num, const int val);

  Standard_EXPORT void SetBoolean(const int num, const bool val);

  Standard_EXPORT void SetLogical(const int num, const StepData_Logical val);

  Standard_EXPORT void SetEnum(const int num, const int val, const char* text = "");

  Standard_EXPORT void SetReal(const int num, const double val);

  Standard_EXPORT void SetString(const int num, const char* val);

  Standard_EXPORT void SetEntity(const int num, const occ::handle<Standard_Transient>& val);

  Standard_EXPORT bool IsSet(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT int ItemKind(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT int Kind(const bool type = true) const;

  Standard_EXPORT int Arity() const;

  Standard_EXPORT int Length(const int index = 1) const;

  Standard_EXPORT int Lower(const int index = 1) const;

  Standard_EXPORT int Int() const;

  Standard_EXPORT int Integer(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT bool Boolean(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT StepData_Logical Logical(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT double Real(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT const char* String(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT int Enum(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT const char* EnumText(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT occ::handle<Standard_Transient> Entity(const int n1 = 1, const int n2 = 1) const;

  Standard_EXPORT occ::handle<Standard_Transient> Transient() const;

private:
  int                             thekind;
  int                             theint;
  double                          thereal;
  occ::handle<Standard_Transient> theany;
};
