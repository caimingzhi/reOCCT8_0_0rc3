#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SolidModel.hpp>
class StepShape_FaceSurface;
class TCollection_HAsciiString;

class StepShape_SweptFaceSolid : public StepShape_SolidModel
{

public:
  Standard_EXPORT StepShape_SweptFaceSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_FaceSurface>&    aSweptArea);

  Standard_EXPORT virtual void SetSweptFace(const occ::handle<StepShape_FaceSurface>& aSweptArea);

  Standard_EXPORT virtual occ::handle<StepShape_FaceSurface> SweptFace() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_SweptFaceSolid, StepShape_SolidModel)

private:
  occ::handle<StepShape_FaceSurface> sweptArea;
};
