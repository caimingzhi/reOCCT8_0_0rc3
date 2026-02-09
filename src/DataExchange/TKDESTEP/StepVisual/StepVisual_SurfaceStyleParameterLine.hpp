#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_DirectionCountSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class StepVisual_CurveStyle;
class StepVisual_DirectionCountSelect;

class StepVisual_SurfaceStyleParameterLine : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_SurfaceStyleParameterLine();

  Standard_EXPORT void Init(
    const occ::handle<StepVisual_CurveStyle>&                                aStyleOfParameterLines,
    const occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>>& aDirectionCounts);

  Standard_EXPORT void SetStyleOfParameterLines(
    const occ::handle<StepVisual_CurveStyle>& aStyleOfParameterLines);

  Standard_EXPORT occ::handle<StepVisual_CurveStyle> StyleOfParameterLines() const;

  Standard_EXPORT void SetDirectionCounts(
    const occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>>& aDirectionCounts);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>>
                  DirectionCounts() const;

  Standard_EXPORT StepVisual_DirectionCountSelect DirectionCountsValue(const int num) const;

  Standard_EXPORT int NbDirectionCounts() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleParameterLine, Standard_Transient)

private:
  occ::handle<StepVisual_CurveStyle>                                styleOfParameterLines;
  occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>> directionCounts;
};
