#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESPick, Type <406> Form <21>
//! in package IGESGraph
//!
//! Attaches information that an entity may be picked
//! by whatever pick device is used in the receiving
//! system
class IGESGraph_Pick : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_Pick();

  //! This method is used to set the fields of the class Pick
  //! - nbProps     : Number of property values (NP = 1)
  //! - aPickStatus : Pick Flag
  Standard_EXPORT void Init(const int nbProps, const int aPickStatus);

  //! returns the number of property values in <me>.
  Standard_EXPORT int NbPropertyValues() const;

  //! returns 0 if <me> is pickable(default),
  //! 1 if <me> is not pickable.
  Standard_EXPORT int PickFlag() const;

  //! returns True if thePick is 0.
  Standard_EXPORT bool IsPickable() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_Pick, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int thePick;
};
