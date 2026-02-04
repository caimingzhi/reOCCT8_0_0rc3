#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_HalfSpaceSolid.hpp>
class StepShape_BoxDomain;
class TCollection_HAsciiString;
class StepGeom_Surface;

class StepShape_BoxedHalfSpace : public StepShape_HalfSpaceSolid
{

public:
  //! Returns a BoxedHalfSpace
  Standard_EXPORT StepShape_BoxedHalfSpace();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Surface>&         aBaseSurface,
                            const bool                                   aAgreementFlag,
                            const occ::handle<StepShape_BoxDomain>&      aEnclosure);

  Standard_EXPORT void SetEnclosure(const occ::handle<StepShape_BoxDomain>& aEnclosure);

  Standard_EXPORT occ::handle<StepShape_BoxDomain> Enclosure() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_BoxedHalfSpace, StepShape_HalfSpaceSolid)

private:
  occ::handle<StepShape_BoxDomain> enclosure;
};

