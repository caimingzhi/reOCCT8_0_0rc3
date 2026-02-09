#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <StepData_EDescr.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_CString.hpp>
class StepData_ESDescr;
class StepData_Described;

class StepData_ECDescr : public StepData_EDescr
{

public:
  Standard_EXPORT StepData_ECDescr();

  Standard_EXPORT void Add(const occ::handle<StepData_ESDescr>& member);

  Standard_EXPORT int NbMembers() const;

  Standard_EXPORT occ::handle<StepData_ESDescr> Member(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> TypeList() const;

  Standard_EXPORT bool Matches(const char* steptype) const override;

  Standard_EXPORT bool IsComplex() const override;

  Standard_EXPORT occ::handle<StepData_Described> NewEntity() const override;

  DEFINE_STANDARD_RTTIEXT(StepData_ECDescr, StepData_EDescr)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> thelist;
};
