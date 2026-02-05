#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_BoxCharacteristicSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_TextStyle.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_TextStyleForDefinedFont;
class StepVisual_BoxCharacteristicSelect;

class StepVisual_TextStyleWithBoxCharacteristics : public StepVisual_TextStyle
{

public:
  //! Returns a TextStyleWithBoxCharacteristics
  Standard_EXPORT StepVisual_TextStyleWithBoxCharacteristics();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&           aName,
    const occ::handle<StepVisual_TextStyleForDefinedFont>& aCharacterAppearance,
    const occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>>& aCharacteristics);

  Standard_EXPORT void SetCharacteristics(
    const occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>>& aCharacteristics);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>>
                  Characteristics() const;

  Standard_EXPORT StepVisual_BoxCharacteristicSelect CharacteristicsValue(const int num) const;

  Standard_EXPORT int NbCharacteristics() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TextStyleWithBoxCharacteristics, StepVisual_TextStyle)

private:
  occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>> characteristics;
};
