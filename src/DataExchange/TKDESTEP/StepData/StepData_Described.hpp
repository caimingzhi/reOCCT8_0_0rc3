#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepData_EDescr;
class StepData_Simple;
class StepData_Field;
class Interface_Check;
class Interface_EntityIterator;

//! General frame to describe entities with Description (Simple or
//! Complex)
class StepData_Described : public Standard_Transient
{

public:
  //! Returns the Description used to define this entity
  Standard_EXPORT occ::handle<StepData_EDescr> Description() const;

  //! Tells if a described entity is complex
  Standard_EXPORT virtual bool IsComplex() const = 0;

  //! Tells if a step type is matched by <me>
  //! For a Simple Entity : own type or super type
  //! For a Complex Entity : one of the members
  Standard_EXPORT virtual bool Matches(const char* steptype) const = 0;

  //! Returns a Simple Entity which matches with a Type in <me> :
  //! For a Simple Entity : me if it matches, else a null handle
  //! For a Complex Entity : the member which matches, else null
  Standard_EXPORT virtual occ::handle<StepData_Simple> As(const char* steptype) const = 0;

  //! Tells if a Field brings a given name
  Standard_EXPORT virtual bool HasField(const char* name) const = 0;

  //! Returns a Field from its name; read-only
  Standard_EXPORT virtual const StepData_Field& Field(const char* name) const = 0;

  //! Returns a Field from its name; read or write
  Standard_EXPORT virtual StepData_Field& CField(const char* name) = 0;

  //! Fills a Check by using its Description
  Standard_EXPORT virtual void Check(occ::handle<Interface_Check>& ach) const = 0;

  //! Fills an EntityIterator with entities shared by <me>
  Standard_EXPORT virtual void Shared(Interface_EntityIterator& list) const = 0;

  DEFINE_STANDARD_RTTIEXT(StepData_Described, Standard_Transient)

protected:
  //! Initializes a Described Entity from a Description
  //! (i.e. puts it in a field ...)
  Standard_EXPORT StepData_Described(const occ::handle<StepData_EDescr>& descr);

private:
  occ::handle<StepData_EDescr> thedescr;
};
