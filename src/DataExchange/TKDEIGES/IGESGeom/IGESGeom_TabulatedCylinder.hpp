#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESGeom_TabulatedCylinder : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_TabulatedCylinder();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aDirectrix,
                            const gp_XYZ&                           anEnd);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Directrix() const;

  Standard_EXPORT gp_Pnt EndPoint() const;

  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_TabulatedCylinder, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theDirectrix;
  gp_XYZ                           theEnd;
};
