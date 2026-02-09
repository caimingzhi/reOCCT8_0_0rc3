#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

class IGESSolid_SolidOfRevolution : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidOfRevolution();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                            const double                            aFract,
                            const gp_XYZ&                           aAxisPnt,
                            const gp_XYZ&                           aDirection);

  Standard_EXPORT void SetClosedToAxis(const bool mode);

  Standard_EXPORT bool IsClosedToAxis() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve() const;

  Standard_EXPORT double Fraction() const;

  Standard_EXPORT gp_Pnt AxisPoint() const;

  Standard_EXPORT gp_Pnt TransformedAxisPoint() const;

  Standard_EXPORT gp_Dir Axis() const;

  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidOfRevolution, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theCurve;
  double                           theFraction;
  gp_XYZ                           theAxisPoint;
  gp_XYZ                           theAxis;
};
