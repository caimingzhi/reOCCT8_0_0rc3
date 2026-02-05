#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_SweptSurface.hpp>
class StepGeom_Vector;
class TCollection_HAsciiString;
class StepGeom_Curve;

class StepGeom_SurfaceOfLinearExtrusion : public StepGeom_SweptSurface
{

public:
  //! Returns a SurfaceOfLinearExtrusion
  Standard_EXPORT StepGeom_SurfaceOfLinearExtrusion();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Curve>&           aSweptCurve,
                            const occ::handle<StepGeom_Vector>&          aExtrusionAxis);

  Standard_EXPORT void SetExtrusionAxis(const occ::handle<StepGeom_Vector>& aExtrusionAxis);

  Standard_EXPORT occ::handle<StepGeom_Vector> ExtrusionAxis() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfaceOfLinearExtrusion, StepGeom_SweptSurface)

private:
  occ::handle<StepGeom_Vector> extrusionAxis;
};
