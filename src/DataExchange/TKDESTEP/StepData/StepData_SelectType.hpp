#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Type.hpp>
#include <Standard_CString.hpp>
#include <StepData_Logical.hpp>
class Standard_Transient;
class StepData_PDescr;
class StepData_SelectMember;

class StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual int CaseNum(const occ::handle<Standard_Transient>& ent) const = 0;

  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT void SetValue(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void Nullify();

  Standard_EXPORT const occ::handle<Standard_Transient>& Value() const;

  Standard_EXPORT bool IsNull() const;

  Standard_EXPORT occ::handle<Standard_Type> Type() const;

  Standard_EXPORT int CaseNumber() const;

  Standard_EXPORT virtual occ::handle<StepData_PDescr> Description() const;

  Standard_EXPORT virtual occ::handle<StepData_SelectMember> NewMember() const;

  Standard_EXPORT virtual int CaseMem(const occ::handle<StepData_SelectMember>& ent) const;

  Standard_EXPORT int CaseMember() const;

  Standard_EXPORT occ::handle<StepData_SelectMember> Member() const;

  Standard_EXPORT const char* SelectName() const;

  Standard_EXPORT int Int() const;

  Standard_EXPORT void SetInt(const int val);

  Standard_EXPORT int Integer() const;

  Standard_EXPORT void SetInteger(const int val, const char* name = "");

  Standard_EXPORT bool Boolean() const;

  Standard_EXPORT void SetBoolean(const bool val, const char* name = "");

  Standard_EXPORT StepData_Logical Logical() const;

  Standard_EXPORT void SetLogical(const StepData_Logical val, const char* name = "");

  Standard_EXPORT double Real() const;

  Standard_EXPORT void SetReal(const double val, const char* name = "");

  Standard_EXPORT virtual ~StepData_SelectType();

private:
  occ::handle<Standard_Transient> thevalue;
};
