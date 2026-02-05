#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CompositeCurveSegment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_Logical.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepGeom_CompositeCurveSegment;

class StepGeom_CompositeCurve : public StepGeom_BoundedCurve
{

public:
  //! Returns a CompositeCurve
  Standard_EXPORT StepGeom_CompositeCurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                         aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>>& aSegments,
    const StepData_Logical aSelfIntersect);

  Standard_EXPORT void SetSegments(
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>>& aSegments);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>>
                  Segments() const;

  Standard_EXPORT occ::handle<StepGeom_CompositeCurveSegment> SegmentsValue(const int num) const;

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT void SetSelfIntersect(const StepData_Logical aSelfIntersect);

  Standard_EXPORT StepData_Logical SelfIntersect() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CompositeCurve, StepGeom_BoundedCurve)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>> segments;
  StepData_Logical                                                              selfIntersect;
};
