

#include <StepVisual_CompositeTextWithExtent.hpp>
#include <StepVisual_PlanarExtent.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CompositeTextWithExtent, StepVisual_CompositeText)

StepVisual_CompositeTextWithExtent::StepVisual_CompositeTextWithExtent() = default;

void StepVisual_CompositeTextWithExtent::Init(
  const occ::handle<TCollection_HAsciiString>&                        aName,
  const occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>>& aCollectedText,
  const occ::handle<StepVisual_PlanarExtent>&                         aExtent)
{

  extent = aExtent;

  StepVisual_CompositeText::Init(aName, aCollectedText);
}

void StepVisual_CompositeTextWithExtent::SetExtent(
  const occ::handle<StepVisual_PlanarExtent>& aExtent)
{
  extent = aExtent;
}

occ::handle<StepVisual_PlanarExtent> StepVisual_CompositeTextWithExtent::Extent() const
{
  return extent;
}
