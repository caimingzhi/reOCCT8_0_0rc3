#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_EDescr.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
class StepData_PDescr;
class StepData_Described;

class StepData_ESDescr : public StepData_EDescr
{

public:
  Standard_EXPORT StepData_ESDescr(const char* name);

  Standard_EXPORT void SetNbFields(const int nb);

  Standard_EXPORT void SetField(const int                           num,
                                const char*                         name,
                                const occ::handle<StepData_PDescr>& descr);

  Standard_EXPORT void SetBase(const occ::handle<StepData_ESDescr>& base);

  Standard_EXPORT void SetSuper(const occ::handle<StepData_ESDescr>& super);

  Standard_EXPORT const char* TypeName() const;

  Standard_EXPORT const TCollection_AsciiString& StepType() const;

  Standard_EXPORT occ::handle<StepData_ESDescr> Base() const;

  Standard_EXPORT occ::handle<StepData_ESDescr> Super() const;

  Standard_EXPORT bool IsSub(const occ::handle<StepData_ESDescr>& other) const;

  Standard_EXPORT int NbFields() const;

  Standard_EXPORT int Rank(const char* name) const;

  Standard_EXPORT const char* Name(const int num) const;

  Standard_EXPORT occ::handle<StepData_PDescr> Field(const int num) const;

  Standard_EXPORT occ::handle<StepData_PDescr> NamedField(const char* name) const;

  Standard_EXPORT bool Matches(const char* steptype) const override;

  Standard_EXPORT bool IsComplex() const override;

  Standard_EXPORT occ::handle<StepData_Described> NewEntity() const override;

  DEFINE_STANDARD_RTTIEXT(StepData_ESDescr, StepData_EDescr)

private:
  TCollection_AsciiString                                           thenom;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> thedescr;
  NCollection_DataMap<TCollection_AsciiString, int>                 thenames;
  occ::handle<StepData_ESDescr>                                     thebase;
  occ::handle<StepData_ESDescr>                                     thesuper;
};
