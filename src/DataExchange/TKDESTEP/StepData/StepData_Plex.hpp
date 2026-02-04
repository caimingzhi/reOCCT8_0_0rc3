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

//! A Plex (for Complex) Entity is defined as a list of Simple
//! Members ("external mapping")
//! The types of these members must be in alphabetic order
class StepData_Plex : public StepData_Described
{

public:
  //! Creates a Plex (empty). The complete creation is made by the
  //! ECDescr itself, by calling Add
  Standard_EXPORT StepData_Plex(const occ::handle<StepData_ECDescr>& descr);

  //! Adds a member to <me>
  Standard_EXPORT void Add(const occ::handle<StepData_Simple>& member);

  //! Returns the Description as for a Plex
  Standard_EXPORT occ::handle<StepData_ECDescr> ECDescr() const;

  //! Returns False
  Standard_EXPORT bool IsComplex() const override;

  //! Tells if a step type is matched by <me>
  //! For a Simple Entity : own type or super type
  //! For a Complex Entity : one of the members
  Standard_EXPORT bool Matches(const char* steptype) const override;

  //! Returns a Simple Entity which matches with a Type in <me> :
  //! For a Simple Entity : me if it matches, else a null handle
  //! For a Complex Entity : the member which matches, else null
  Standard_EXPORT occ::handle<StepData_Simple> As(const char* steptype) const override;

  //! Tells if a Field brings a given name
  Standard_EXPORT bool HasField(const char* name) const override;

  //! Returns a Field from its name; read-only
  Standard_EXPORT const StepData_Field& Field(const char* name) const override;

  //! Returns a Field from its name; read or write
  Standard_EXPORT StepData_Field& CField(const char* name) override;

  //! Returns the count of simple members
  Standard_EXPORT int NbMembers() const;

  //! Returns a simple member from its rank
  Standard_EXPORT occ::handle<StepData_Simple> Member(const int num) const;

  //! Returns the actual list of members types
  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> TypeList() const;

  //! Fills a Check by using its Description
  Standard_EXPORT void Check(occ::handle<Interface_Check>& ach) const override;

  //! Fills an EntityIterator with entities shared by <me>
  Standard_EXPORT void Shared(Interface_EntityIterator& list) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_Plex, StepData_Described)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> themembers;
};

