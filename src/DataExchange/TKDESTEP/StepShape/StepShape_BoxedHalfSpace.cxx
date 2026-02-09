

#include <StepGeom_Surface.hpp>
#include <StepShape_BoxDomain.hpp>
#include <StepShape_BoxedHalfSpace.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_BoxedHalfSpace, StepShape_HalfSpaceSolid)

StepShape_BoxedHalfSpace::StepShape_BoxedHalfSpace() = default;

void StepShape_BoxedHalfSpace::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                    const occ::handle<StepGeom_Surface>&         aBaseSurface,
                                    const bool                                   aAgreementFlag,
                                    const occ::handle<StepShape_BoxDomain>&      aEnclosure)
{

  enclosure = aEnclosure;

  StepShape_HalfSpaceSolid::Init(aName, aBaseSurface, aAgreementFlag);
}

void StepShape_BoxedHalfSpace::SetEnclosure(const occ::handle<StepShape_BoxDomain>& aEnclosure)
{
  enclosure = aEnclosure;
}

occ::handle<StepShape_BoxDomain> StepShape_BoxedHalfSpace::Enclosure() const
{
  return enclosure;
}
