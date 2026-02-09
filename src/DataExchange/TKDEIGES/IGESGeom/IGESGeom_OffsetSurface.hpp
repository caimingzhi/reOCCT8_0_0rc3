#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Vec;

class IGESGeom_OffsetSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_OffsetSurface();

  Standard_EXPORT void Init(const gp_XYZ&                           anIndicatoR,
                            const double                            aDistance,
                            const occ::handle<IGESData_IGESEntity>& aSurface);

  Standard_EXPORT gp_Vec OffsetIndicator() const;

  Standard_EXPORT gp_Vec TransformedOffsetIndicator() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_OffsetSurface, IGESData_IGESEntity)

private:
  gp_XYZ                           theIndicator;
  double                           theDistance;
  occ::handle<IGESData_IGESEntity> theSurface;
};
