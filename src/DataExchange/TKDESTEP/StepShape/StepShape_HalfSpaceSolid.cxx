

#include <StepGeom_Surface.hpp>
#include <StepShape_HalfSpaceSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_HalfSpaceSolid, StepGeom_GeometricRepresentationItem)

StepShape_HalfSpaceSolid::StepShape_HalfSpaceSolid() = default;

void StepShape_HalfSpaceSolid::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                    const occ::handle<StepGeom_Surface>&         aBaseSurface,
                                    const bool                                   aAgreementFlag)
{

  baseSurface   = aBaseSurface;
  agreementFlag = aAgreementFlag;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_HalfSpaceSolid::SetBaseSurface(const occ::handle<StepGeom_Surface>& aBaseSurface)
{
  baseSurface = aBaseSurface;
}

occ::handle<StepGeom_Surface> StepShape_HalfSpaceSolid::BaseSurface() const
{
  return baseSurface;
}

void StepShape_HalfSpaceSolid::SetAgreementFlag(const bool aAgreementFlag)
{
  agreementFlag = aAgreementFlag;
}

bool StepShape_HalfSpaceSolid::AgreementFlag() const
{
  return agreementFlag;
}
