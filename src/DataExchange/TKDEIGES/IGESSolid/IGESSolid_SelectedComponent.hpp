#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESSolid_BooleanTree;
class gp_Pnt;

//! defines SelectedComponent, Type <182> Form Number <0>
//! in package IGESSolid
//! The Selected Component entity provides a means of
//! selecting one component of a disjoint CSG solid
class IGESSolid_SelectedComponent : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SelectedComponent();

  //! This method is used to set the fields of the class
  //! SelectedComponent
  //! - anEntity  : the Boolean tree entity
  //! - selectPnt : Point in or on the desired component
  Standard_EXPORT void Init(const occ::handle<IGESSolid_BooleanTree>& anEntity,
                            const gp_XYZ&                             selectPnt);

  //! returns the Boolean tree entity
  Standard_EXPORT occ::handle<IGESSolid_BooleanTree> Component() const;

  //! returns the point on/in the selected component
  Standard_EXPORT gp_Pnt SelectPoint() const;

  //! returns the point on/in the selected component
  //! after applying TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedSelectPoint() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SelectedComponent, IGESData_IGESEntity)

private:
  occ::handle<IGESSolid_BooleanTree> theEntity;
  gp_XYZ                             theSelectPoint;
};
