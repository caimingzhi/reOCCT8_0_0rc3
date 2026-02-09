#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_Loop.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepShape_PolyLoop : public StepShape_Loop
{

public:
  Standard_EXPORT StepShape_PolyLoop();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                  aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPolygon);

  Standard_EXPORT void SetPolygon(
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPolygon);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> Polygon()
    const;

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> PolygonValue(const int num) const;

  Standard_EXPORT int NbPolygon() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_PolyLoop, StepShape_Loop)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> polygon;
};
