#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Dir;

class IGESSolid_SolidOfLinearExtrusion : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidOfLinearExtrusion();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                            const double                            aLength,
                            const gp_XYZ&                           aDirection);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve() const;

  Standard_EXPORT double ExtrusionLength() const;

  Standard_EXPORT gp_Dir ExtrusionDirection() const;

  Standard_EXPORT gp_Dir TransformedExtrusionDirection() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidOfLinearExtrusion, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theCurve;
  double                           theLength;
  gp_XYZ                           theDirection;
};
