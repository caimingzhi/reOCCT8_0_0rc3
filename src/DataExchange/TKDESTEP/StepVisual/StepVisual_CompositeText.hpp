#pragma once


#include <Standard.hpp>

#include <StepVisual_TextOrCharacter.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_TextOrCharacter;

class StepVisual_CompositeText : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a CompositeText
  Standard_EXPORT StepVisual_CompositeText();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>>& aCollectedText);

  Standard_EXPORT void SetCollectedText(
    const occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>>& aCollectedText);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>> CollectedText()
    const;

  Standard_EXPORT StepVisual_TextOrCharacter CollectedTextValue(const int num) const;

  Standard_EXPORT int NbCollectedText() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CompositeText, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>> collectedText;
};

