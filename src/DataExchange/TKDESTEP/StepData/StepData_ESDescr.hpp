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

//! This class is intended to describe the authorized form for a
//! Simple (not Plex) Entity, as a list of fields
class StepData_ESDescr : public StepData_EDescr
{

public:
  //! Creates an ESDescr with a type name
  Standard_EXPORT StepData_ESDescr(const char* name);

  //! Sets a new count of fields
  //! Each one is described by a PDescr
  Standard_EXPORT void SetNbFields(const int nb);

  //! Sets a PDescr to describe a field
  //! A Field is designated by its rank and name
  Standard_EXPORT void SetField(const int                           num,
                                const char*                         name,
                                const occ::handle<StepData_PDescr>& descr);

  //! Sets an ESDescr as based on another one
  //! Hence, if there are inherited fields, the derived ESDescr
  //! cumulates all them, while the base just records its own ones
  Standard_EXPORT void SetBase(const occ::handle<StepData_ESDescr>& base);

  //! Sets an ESDescr as "super-type". Applies an a base (non
  //! derived) ESDescr
  Standard_EXPORT void SetSuper(const occ::handle<StepData_ESDescr>& super);

  //! Returns the type name given at creation time
  Standard_EXPORT const char* TypeName() const;

  //! Returns the type name as an AsciiString
  Standard_EXPORT const TCollection_AsciiString& StepType() const;

  //! Returns the basic ESDescr, null if <me> is not derived
  Standard_EXPORT occ::handle<StepData_ESDescr> Base() const;

  //! Returns the super-type ESDescr, null if <me> is root
  Standard_EXPORT occ::handle<StepData_ESDescr> Super() const;

  //! Tells if <me> is sub-type of (or equal to) another one
  Standard_EXPORT bool IsSub(const occ::handle<StepData_ESDescr>& other) const;

  //! Returns the count of fields
  Standard_EXPORT int NbFields() const;

  //! Returns the rank of a field from its name. 0 if unknown
  Standard_EXPORT int Rank(const char* name) const;

  //! Returns the name of a field from its rank. empty if outofrange
  Standard_EXPORT const char* Name(const int num) const;

  //! Returns the PDescr for the field <num> (or Null)
  Standard_EXPORT occ::handle<StepData_PDescr> Field(const int num) const;

  //! Returns the PDescr for the field named <name> (or Null)
  Standard_EXPORT occ::handle<StepData_PDescr> NamedField(const char* name) const;

  //! Tells if a ESDescr matches a step type : exact or super type
  Standard_EXPORT bool Matches(const char* steptype) const override;

  //! Returns False
  Standard_EXPORT bool IsComplex() const override;

  //! Creates a described entity (i.e. a simple one)
  Standard_EXPORT occ::handle<StepData_Described> NewEntity() const override;

  DEFINE_STANDARD_RTTIEXT(StepData_ESDescr, StepData_EDescr)

private:
  TCollection_AsciiString                                           thenom;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> thedescr;
  NCollection_DataMap<TCollection_AsciiString, int>                 thenames;
  occ::handle<StepData_ESDescr>                                     thebase;
  occ::handle<StepData_ESDescr>                                     thesuper;
};
