

#include <StepGeom_Pcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Pcurve, StepGeom_Curve)

StepGeom_Pcurve::StepGeom_Pcurve() = default;

void StepGeom_Pcurve::Init(
  const occ::handle<TCollection_HAsciiString>&            aName,
  const occ::handle<StepGeom_Surface>&                    aBasisSurface,
  const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve)
{

  basisSurface     = aBasisSurface;
  referenceToCurve = aReferenceToCurve;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_Pcurve::SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface)
{
  basisSurface = aBasisSurface;
}

occ::handle<StepGeom_Surface> StepGeom_Pcurve::BasisSurface() const
{
  return basisSurface;
}

void StepGeom_Pcurve::SetReferenceToCurve(
  const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve)
{
  referenceToCurve = aReferenceToCurve;
}

occ::handle<StepRepr_DefinitionalRepresentation> StepGeom_Pcurve::ReferenceToCurve() const
{
  return referenceToCurve;
}
