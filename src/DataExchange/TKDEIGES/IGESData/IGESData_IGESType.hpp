#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! taken from directory part of an entity (from file or model),
//! gives "type" and "form" data, used to recognize entity's type
class IGESData_IGESType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_IGESType();

  Standard_EXPORT IGESData_IGESType(const int atype, const int aform);

  //! returns "type" data
  Standard_EXPORT int Type() const;

  //! returns "form" data
  Standard_EXPORT int Form() const;

  //! compares two IGESTypes, avoiding comparing their fields
  Standard_EXPORT bool IsEqual(const IGESData_IGESType& another) const;

  bool operator==(const IGESData_IGESType& another) const { return IsEqual(another); }

  //! resets fields (useful when an IGESType is stored as mask)
  Standard_EXPORT void Nullify();

private:
  int thetype;
  int theform;
};

