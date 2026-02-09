#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepData_EDescr;
class StepData_Simple;
class StepData_Field;
class Interface_Check;
class Interface_EntityIterator;

class StepData_Described : public Standard_Transient
{

public:
  Standard_EXPORT occ::handle<StepData_EDescr> Description() const;

  Standard_EXPORT virtual bool IsComplex() const = 0;

  Standard_EXPORT virtual bool Matches(const char* steptype) const = 0;

  Standard_EXPORT virtual occ::handle<StepData_Simple> As(const char* steptype) const = 0;

  Standard_EXPORT virtual bool HasField(const char* name) const = 0;

  Standard_EXPORT virtual const StepData_Field& Field(const char* name) const = 0;

  Standard_EXPORT virtual StepData_Field& CField(const char* name) = 0;

  Standard_EXPORT virtual void Check(occ::handle<Interface_Check>& ach) const = 0;

  Standard_EXPORT virtual void Shared(Interface_EntityIterator& list) const = 0;

  DEFINE_STANDARD_RTTIEXT(StepData_Described, Standard_Transient)

protected:
  Standard_EXPORT StepData_Described(const occ::handle<StepData_EDescr>& descr);

private:
  occ::handle<StepData_EDescr> thedescr;
};
