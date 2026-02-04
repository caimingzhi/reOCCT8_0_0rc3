#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESData_DefType.hpp>

//! description of a directory component which can be either
//! undefined (let Void), defined as a Reference to an entity,
//! or as a Rank, integer value addressing a builtin table
//! The entity reference is not included here, only reference
//! status is kept (because entity type must be adapted)
class IGESData_DefSwitch
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates a DefSwitch as Void
  Standard_EXPORT IGESData_DefSwitch();

  //! sets DefSwitch to "Void" status (in file : Integer = 0)
  Standard_EXPORT void SetVoid();

  //! sets DefSwitch to "Reference" Status (in file : Integer < 0)
  Standard_EXPORT void SetReference();

  //! sets DefSwitch to "Rank" with a Value (in file : Integer > 0)
  Standard_EXPORT void SetRank(const int val);

  //! returns DefType status (Void,Reference,Rank)
  Standard_EXPORT IGESData_DefType DefType() const;

  //! returns Value as Integer (sensefull for a Rank)
  Standard_EXPORT int Value() const;

private:
  int theval;
};

