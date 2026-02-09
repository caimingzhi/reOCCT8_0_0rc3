#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Vec;

class IGESGeom_Direction : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Direction();

  Standard_EXPORT void Init(const gp_XYZ& aDirection);

  Standard_EXPORT gp_Vec Value() const;

  Standard_EXPORT gp_Vec TransformedValue() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Direction, IGESData_IGESEntity)

private:
  gp_XYZ theDirection;
};
