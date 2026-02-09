#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

class IGESSolid_Torus : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Torus();

  Standard_EXPORT void Init(const double  R1,
                            const double  R2,
                            const gp_XYZ& aPoint,
                            const gp_XYZ& anAxisdir);

  Standard_EXPORT double MajorRadius() const;

  Standard_EXPORT double DiscRadius() const;

  Standard_EXPORT gp_Pnt AxisPoint() const;

  Standard_EXPORT gp_Pnt TransformedAxisPoint() const;

  Standard_EXPORT gp_Dir Axis() const;

  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Torus, IGESData_IGESEntity)

private:
  double theR1;
  double theR2;
  gp_XYZ thePoint;
  gp_XYZ theAxis;
};
