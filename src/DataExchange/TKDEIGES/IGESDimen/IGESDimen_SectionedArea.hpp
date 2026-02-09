#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class gp_Pnt;

class IGESDimen_SectionedArea : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_SectionedArea();

  Standard_EXPORT void Init(
    const occ::handle<IGESData_IGESEntity>&                                   aCurve,
    const int                                                                 aPattern,
    const gp_XYZ&                                                             aPoint,
    const double                                                              aDistance,
    const double                                                              anAngle,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& someIslands);

  Standard_EXPORT void SetInverted(const bool mode);

  Standard_EXPORT bool IsInverted() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ExteriorCurve() const;

  Standard_EXPORT int Pattern() const;

  Standard_EXPORT gp_Pnt PassingPoint() const;

  Standard_EXPORT gp_Pnt TransformedPassingPoint() const;

  Standard_EXPORT double ZDepth() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT double Angle() const;

  Standard_EXPORT int NbIslands() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> IslandCurve(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_SectionedArea, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity>                                   theExteriorCurve;
  int                                                                thePattern;
  gp_XYZ                                                             thePassingPoint;
  double                                                             theDistance;
  double                                                             theAngle;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theIslandCurves;
};
