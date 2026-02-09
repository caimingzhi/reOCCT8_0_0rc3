

#include <StepGeom_DegeneratePcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_DegeneratePcurve, StepGeom_Point)

StepGeom_DegeneratePcurve::StepGeom_DegeneratePcurve() = default;

void StepGeom_DegeneratePcurve::Init(
  const occ::handle<TCollection_HAsciiString>&            aName,
  const occ::handle<StepGeom_Surface>&                    aBasisSurface,
  const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve)
{

  basisSurface     = aBasisSurface;
  referenceToCurve = aReferenceToCurve;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_DegeneratePcurve::SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface)
{
  basisSurface = aBasisSurface;
}

occ::handle<StepGeom_Surface> StepGeom_DegeneratePcurve::BasisSurface() const
{
  return basisSurface;
}

void StepGeom_DegeneratePcurve::SetReferenceToCurve(
  const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve)
{
  referenceToCurve = aReferenceToCurve;
}

occ::handle<StepRepr_DefinitionalRepresentation> StepGeom_DegeneratePcurve::ReferenceToCurve() const
{
  return referenceToCurve;
}
