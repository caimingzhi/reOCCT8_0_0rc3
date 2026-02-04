#pragma once


#include <Standard.hpp>

#include <StepVisual_CompositeText.hpp>
#include <StepVisual_TextOrCharacter.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class StepVisual_PlanarExtent;
class TCollection_HAsciiString;

class StepVisual_CompositeTextWithExtent : public StepVisual_CompositeText
{

public:
  //! Returns a CompositeTextWithExtent
  Standard_EXPORT StepVisual_CompositeTextWithExtent();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>>& aCollectedText,
    const occ::handle<StepVisual_PlanarExtent>&                         aExtent);

  Standard_EXPORT void SetExtent(const occ::handle<StepVisual_PlanarExtent>& aExtent);

  Standard_EXPORT occ::handle<StepVisual_PlanarExtent> Extent() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CompositeTextWithExtent, StepVisual_CompositeText)

private:
  occ::handle<StepVisual_PlanarExtent> extent;
};

