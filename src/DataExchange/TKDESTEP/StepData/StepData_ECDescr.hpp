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

//! Describes a Complex Entity (Plex) as a list of Simple ones
class StepData_ECDescr : public StepData_EDescr
{

public:
  //! Creates an ECDescr, empty
  Standard_EXPORT StepData_ECDescr();

  //! Adds a member
  //! Warning : members are added in alphabetic order
  Standard_EXPORT void Add(const occ::handle<StepData_ESDescr>& member);

  //! Returns the count of members
  Standard_EXPORT int NbMembers() const;

  //! Returns a Member from its rank
  Standard_EXPORT occ::handle<StepData_ESDescr> Member(const int num) const;

  //! Returns the ordered list of types
  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> TypeList() const;

  //! Tells if a ESDescr matches a step type : exact or super type
  Standard_EXPORT bool Matches(const char* steptype) const override;

  //! Returns True
  Standard_EXPORT bool IsComplex() const override;

  //! Creates a described entity (i.e. a complex one, made of one
  //! simple entity per member)
  Standard_EXPORT occ::handle<StepData_Described> NewEntity() const override;

  DEFINE_STANDARD_RTTIEXT(StepData_ECDescr, StepData_EDescr)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> thelist;
};

