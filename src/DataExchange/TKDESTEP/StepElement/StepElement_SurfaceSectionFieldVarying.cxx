#include <StepElement_SurfaceSectionFieldVarying.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_SurfaceSectionFieldVarying, StepElement_SurfaceSectionField)

//=================================================================================================

StepElement_SurfaceSectionFieldVarying::StepElement_SurfaceSectionFieldVarying() = default;

//=================================================================================================

void StepElement_SurfaceSectionFieldVarying::Init(
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>>& aDefinitions,
  const bool aAdditionalNodeValues)
{
  // StepElement_SurfaceSectionField::Init();

  theDefinitions = aDefinitions;

  theAdditionalNodeValues = aAdditionalNodeValues;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>>
  StepElement_SurfaceSectionFieldVarying::Definitions() const
{
  return theDefinitions;
}

//=================================================================================================

void StepElement_SurfaceSectionFieldVarying::SetDefinitions(
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>>& aDefinitions)
{
  theDefinitions = aDefinitions;
}

//=================================================================================================

bool StepElement_SurfaceSectionFieldVarying::AdditionalNodeValues() const
{
  return theAdditionalNodeValues;
}

//=================================================================================================

void StepElement_SurfaceSectionFieldVarying::SetAdditionalNodeValues(
  const bool aAdditionalNodeValues)
{
  theAdditionalNodeValues = aAdditionalNodeValues;
}
