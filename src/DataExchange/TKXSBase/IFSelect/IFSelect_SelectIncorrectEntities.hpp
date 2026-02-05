#pragma once

#include <Standard.hpp>

#include <IFSelect_SelectFlag.hpp>

//! A SelectIncorrectEntities sorts the Entities which have been
//! noted as Incorrect in the Graph of the Session
//! (flag "Incorrect")
//! It can find a result only if ComputeCheck has formerly been
//! called on the WorkSession. Else, its result will be empty.
class IFSelect_SelectIncorrectEntities : public IFSelect_SelectFlag
{

public:
  //! Creates a SelectIncorrectEntities
  //! i.e. a SelectFlag("Incorrect")
  Standard_EXPORT IFSelect_SelectIncorrectEntities();

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectIncorrectEntities, IFSelect_SelectFlag)
};
