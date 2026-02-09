#pragma once

#include <Standard.hpp>

#include <StepElement_SurfaceSection.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Boolean.hpp>
#include <StepElement_SurfaceSectionField.hpp>

class StepElement_SurfaceSectionFieldVarying : public StepElement_SurfaceSectionField
{

public:
  Standard_EXPORT StepElement_SurfaceSectionFieldVarying();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>>& aDefinitions,
    const bool aAdditionalNodeValues);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>>
                  Definitions() const;

  Standard_EXPORT void SetDefinitions(
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>>& Definitions);

  Standard_EXPORT bool AdditionalNodeValues() const;

  Standard_EXPORT void SetAdditionalNodeValues(const bool AdditionalNodeValues);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceSectionFieldVarying, StepElement_SurfaceSectionField)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepElement_SurfaceSection>>> theDefinitions;
  bool                                                                      theAdditionalNodeValues;
};
