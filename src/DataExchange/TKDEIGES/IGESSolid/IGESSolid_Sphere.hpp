#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESSolid_Sphere : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Sphere();

  Standard_EXPORT void Init(const double aRadius, const gp_XYZ& aCenter);

  Standard_EXPORT double Radius() const;

  Standard_EXPORT gp_Pnt Center() const;

  Standard_EXPORT gp_Pnt TransformedCenter() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Sphere, IGESData_IGESEntity)

private:
  double theRadius;
  gp_XYZ theCenter;
};
