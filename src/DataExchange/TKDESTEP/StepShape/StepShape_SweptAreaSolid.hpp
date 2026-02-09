#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SolidModel.hpp>
class StepGeom_CurveBoundedSurface;
class TCollection_HAsciiString;

class StepShape_SweptAreaSolid : public StepShape_SolidModel
{

public:
  Standard_EXPORT StepShape_SweptAreaSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea);

  Standard_EXPORT void SetSweptArea(const occ::handle<StepGeom_CurveBoundedSurface>& aSweptArea);

  Standard_EXPORT occ::handle<StepGeom_CurveBoundedSurface> SweptArea() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_SweptAreaSolid, StepShape_SolidModel)

private:
  occ::handle<StepGeom_CurveBoundedSurface> sweptArea;
};
