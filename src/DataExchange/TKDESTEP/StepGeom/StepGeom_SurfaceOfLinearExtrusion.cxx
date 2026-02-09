

#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SurfaceOfLinearExtrusion, StepGeom_SweptSurface)

StepGeom_SurfaceOfLinearExtrusion::StepGeom_SurfaceOfLinearExtrusion() = default;

void StepGeom_SurfaceOfLinearExtrusion::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                             const occ::handle<StepGeom_Curve>&  aSweptCurve,
                                             const occ::handle<StepGeom_Vector>& aExtrusionAxis)
{

  extrusionAxis = aExtrusionAxis;

  StepGeom_SweptSurface::Init(aName, aSweptCurve);
}

void StepGeom_SurfaceOfLinearExtrusion::SetExtrusionAxis(
  const occ::handle<StepGeom_Vector>& aExtrusionAxis)
{
  extrusionAxis = aExtrusionAxis;
}

occ::handle<StepGeom_Vector> StepGeom_SurfaceOfLinearExtrusion::ExtrusionAxis() const
{
  return extrusionAxis;
}
