#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <StepData_Described.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_HSequence.hpp>
class StepData_ECDescr;
class StepData_Simple;
class StepData_Field;
class Interface_Check;
class Interface_EntityIterator;

class StepData_Plex : public StepData_Described
{

public:
  Standard_EXPORT StepData_Plex(const occ::handle<StepData_ECDescr>& descr);

  Standard_EXPORT void Add(const occ::handle<StepData_Simple>& member);

  Standard_EXPORT occ::handle<StepData_ECDescr> ECDescr() const;

  Standard_EXPORT bool IsComplex() const override;

  Standard_EXPORT bool Matches(const char* steptype) const override;

  Standard_EXPORT occ::handle<StepData_Simple> As(const char* steptype) const override;

  Standard_EXPORT bool HasField(const char* name) const override;

  Standard_EXPORT const StepData_Field& Field(const char* name) const override;

  Standard_EXPORT StepData_Field& CField(const char* name) override;

  Standard_EXPORT int NbMembers() const;

  Standard_EXPORT occ::handle<StepData_Simple> Member(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> TypeList() const;

  Standard_EXPORT void Check(occ::handle<Interface_Check>& ach) const override;

  Standard_EXPORT void Shared(Interface_EntityIterator& list) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_Plex, StepData_Described)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> themembers;
};
