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

//! A Simple Entity is defined by a type (which can heve super
//! types) and a list of parameters
class StepData_Simple : public StepData_Described
{

public:
  //! Creates a Simple Entity
  Standard_EXPORT StepData_Simple(const occ::handle<StepData_ESDescr>& descr);

  //! Returns description, as for simple
  Standard_EXPORT occ::handle<StepData_ESDescr> ESDescr() const;

  //! Returns the recorded StepType (TypeName of its ESDescr)
  Standard_EXPORT const char* StepType() const;

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

  //! Returns the count of fields
  Standard_EXPORT int NbFields() const;

  //! Returns a field from its rank, for read-only use
  Standard_EXPORT const StepData_Field& FieldNum(const int num) const;

  //! Returns a field from its rank, in order to modify it
  Standard_EXPORT StepData_Field& CFieldNum(const int num);

  //! Returns the entire field list, read-only
  Standard_EXPORT const StepData_FieldListN& Fields() const;

  //! Returns the entire field list, read or write
  Standard_EXPORT StepData_FieldListN& CFields();

  //! Fills a Check by using its Description
  Standard_EXPORT void Check(occ::handle<Interface_Check>& ach) const override;

  //! Fills an EntityIterator with entities shared by <me>
  Standard_EXPORT void Shared(Interface_EntityIterator& list) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_Simple, StepData_Described)

private:
  StepData_FieldListN thefields;
};
