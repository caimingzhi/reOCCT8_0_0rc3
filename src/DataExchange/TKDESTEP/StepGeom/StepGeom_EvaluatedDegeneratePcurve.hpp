#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_DegeneratePcurve.hpp>
class StepGeom_CartesianPoint;
class TCollection_HAsciiString;
class StepGeom_Surface;
class StepRepr_DefinitionalRepresentation;

class StepGeom_EvaluatedDegeneratePcurve : public StepGeom_DegeneratePcurve
{

public:
  //! Returns a EvaluatedDegeneratePcurve
  Standard_EXPORT StepGeom_EvaluatedDegeneratePcurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&            aName,
    const occ::handle<StepGeom_Surface>&                    aBasisSurface,
    const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve,
    const occ::handle<StepGeom_CartesianPoint>&             aEquivalentPoint);

  Standard_EXPORT void SetEquivalentPoint(
    const occ::handle<StepGeom_CartesianPoint>& aEquivalentPoint);

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> EquivalentPoint() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_EvaluatedDegeneratePcurve, StepGeom_DegeneratePcurve)

private:
  occ::handle<StepGeom_CartesianPoint> equivalentPoint;
};

