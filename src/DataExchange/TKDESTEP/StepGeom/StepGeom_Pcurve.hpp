#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Curve.hpp>
class StepGeom_Surface;
class StepRepr_DefinitionalRepresentation;
class TCollection_HAsciiString;

class StepGeom_Pcurve : public StepGeom_Curve
{

public:
  //! Returns a Pcurve
  Standard_EXPORT StepGeom_Pcurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&            aName,
    const occ::handle<StepGeom_Surface>&                    aBasisSurface,
    const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve);

  Standard_EXPORT void SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface);

  Standard_EXPORT occ::handle<StepGeom_Surface> BasisSurface() const;

  Standard_EXPORT void SetReferenceToCurve(
    const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve);

  Standard_EXPORT occ::handle<StepRepr_DefinitionalRepresentation> ReferenceToCurve() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Pcurve, StepGeom_Curve)

private:
  occ::handle<StepGeom_Surface>                    basisSurface;
  occ::handle<StepRepr_DefinitionalRepresentation> referenceToCurve;
};

