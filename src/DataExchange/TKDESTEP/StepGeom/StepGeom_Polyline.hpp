#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepGeom_Polyline : public StepGeom_BoundedCurve
{

public:
  //! Returns a Polyline
  Standard_EXPORT StepGeom_Polyline();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                  aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPoints);

  Standard_EXPORT void SetPoints(
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPoints);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> Points()
    const;

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> PointsValue(const int num) const;

  Standard_EXPORT int NbPoints() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Polyline, StepGeom_BoundedCurve)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> points;
};
