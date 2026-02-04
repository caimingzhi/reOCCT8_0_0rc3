#pragma once


#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>

//! defines SolidInstance, Type <430> Form Number <0>
//! in package IGESSolid
//! This provides a mechanism for replicating a solid
//! representation.
//!
//! From IGES-5.3, Form may be <1> for a BREP
//! Else it is for a Boolean Tree, Primitive, other Solid Inst.
class IGESSolid_SolidInstance : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidInstance();

  //! This method is used to set the fields of the class
  //! SolidInstance
  //! - anEntity : the entity corresponding to the solid
  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& anEntity);

  //! Tells if a SolidInstance is for a BREP
  //! Default is False
  Standard_EXPORT bool IsBrep() const;

  //! Sets or unsets the Brep status (FormNumber = 1 else 0)
  Standard_EXPORT void SetBrep(const bool brep);

  //! returns the solid entity
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidInstance, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theEntity;
};

