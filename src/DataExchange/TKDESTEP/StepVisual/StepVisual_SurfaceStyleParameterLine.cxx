

#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleParameterLine.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceStyleParameterLine, Standard_Transient)

StepVisual_SurfaceStyleParameterLine::StepVisual_SurfaceStyleParameterLine() = default;

void StepVisual_SurfaceStyleParameterLine::Init(
  const occ::handle<StepVisual_CurveStyle>&                                aStyleOfParameterLines,
  const occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>>& aDirectionCounts)
{

  styleOfParameterLines = aStyleOfParameterLines;
  directionCounts       = aDirectionCounts;
}

void StepVisual_SurfaceStyleParameterLine::SetStyleOfParameterLines(
  const occ::handle<StepVisual_CurveStyle>& aStyleOfParameterLines)
{
  styleOfParameterLines = aStyleOfParameterLines;
}

occ::handle<StepVisual_CurveStyle> StepVisual_SurfaceStyleParameterLine::StyleOfParameterLines()
  const
{
  return styleOfParameterLines;
}

void StepVisual_SurfaceStyleParameterLine::SetDirectionCounts(
  const occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>>& aDirectionCounts)
{
  directionCounts = aDirectionCounts;
}

occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>>
  StepVisual_SurfaceStyleParameterLine::DirectionCounts() const
{
  return directionCounts;
}

StepVisual_DirectionCountSelect StepVisual_SurfaceStyleParameterLine::DirectionCountsValue(
  const int num) const
{
  return directionCounts->Value(num);
}

int StepVisual_SurfaceStyleParameterLine::NbDirectionCounts() const
{
  return directionCounts->Length();
}
