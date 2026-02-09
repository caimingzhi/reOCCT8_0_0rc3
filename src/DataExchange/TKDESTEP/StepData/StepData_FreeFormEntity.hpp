#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_Field.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
class StepData_Field;

class StepData_FreeFormEntity : public Standard_Transient
{

public:
  Standard_EXPORT StepData_FreeFormEntity();

  Standard_EXPORT void SetStepType(const char* typenam);

  Standard_EXPORT const char* StepType() const;

  Standard_EXPORT void SetNext(const occ::handle<StepData_FreeFormEntity>& next,
                               const bool                                  last = true);

  Standard_EXPORT occ::handle<StepData_FreeFormEntity> Next() const;

  Standard_EXPORT bool IsComplex() const;

  Standard_EXPORT occ::handle<StepData_FreeFormEntity> Typed(const char* typenam) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> TypeList() const;

  Standard_EXPORT static bool Reorder(occ::handle<StepData_FreeFormEntity>& ent);

  Standard_EXPORT void SetNbFields(const int nb);

  Standard_EXPORT int NbFields() const;

  Standard_EXPORT const StepData_Field& Field(const int num) const;

  Standard_EXPORT StepData_Field& CField(const int num);

  DEFINE_STANDARD_RTTIEXT(StepData_FreeFormEntity, Standard_Transient)

private:
  TCollection_AsciiString                          thetype;
  occ::handle<NCollection_HArray1<StepData_Field>> thefields;
  occ::handle<StepData_FreeFormEntity>             thenext;
};
