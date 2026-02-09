#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_FieldListN.hpp>
#include <StepData_Described.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
class StepData_ESDescr;
class StepData_Field;
class Interface_Check;
class Interface_EntityIterator;

class StepData_Simple : public StepData_Described
{

public:
  Standard_EXPORT StepData_Simple(const occ::handle<StepData_ESDescr>& descr);

  Standard_EXPORT occ::handle<StepData_ESDescr> ESDescr() const;

  Standard_EXPORT const char* StepType() const;

  Standard_EXPORT bool IsComplex() const override;

  Standard_EXPORT bool Matches(const char* steptype) const override;

  Standard_EXPORT occ::handle<StepData_Simple> As(const char* steptype) const override;

  Standard_EXPORT bool HasField(const char* name) const override;

  Standard_EXPORT const StepData_Field& Field(const char* name) const override;

  Standard_EXPORT StepData_Field& CField(const char* name) override;

  Standard_EXPORT int NbFields() const;

  Standard_EXPORT const StepData_Field& FieldNum(const int num) const;

  Standard_EXPORT StepData_Field& CFieldNum(const int num);

  Standard_EXPORT const StepData_FieldListN& Fields() const;

  Standard_EXPORT StepData_FieldListN& CFields();

  Standard_EXPORT void Check(occ::handle<Interface_Check>& ach) const override;

  Standard_EXPORT void Shared(Interface_EntityIterator& list) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_Simple, StepData_Described)

private:
  StepData_FieldListN thefields;
};
