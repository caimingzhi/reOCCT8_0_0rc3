#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESSolid_BooleanTree;
class gp_Pnt;

class IGESSolid_SelectedComponent : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SelectedComponent();

  Standard_EXPORT void Init(const occ::handle<IGESSolid_BooleanTree>& anEntity,
                            const gp_XYZ&                             selectPnt);

  Standard_EXPORT occ::handle<IGESSolid_BooleanTree> Component() const;

  Standard_EXPORT gp_Pnt SelectPoint() const;

  Standard_EXPORT gp_Pnt TransformedSelectPoint() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SelectedComponent, IGESData_IGESEntity)

private:
  occ::handle<IGESSolid_BooleanTree> theEntity;
  gp_XYZ                             theSelectPoint;
};
