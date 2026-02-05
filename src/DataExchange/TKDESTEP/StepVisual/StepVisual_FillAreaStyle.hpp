#pragma once

#include <Standard.hpp>

#include <StepVisual_FillStyleSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_FillStyleSelect;

class StepVisual_FillAreaStyle : public Standard_Transient
{

public:
  //! Returns a FillAreaStyle
  Standard_EXPORT StepVisual_FillAreaStyle();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                        aName,
    const occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>>& aFillStyles);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetFillStyles(
    const occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>>& aFillStyles);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>> FillStyles() const;

  Standard_EXPORT StepVisual_FillStyleSelect FillStylesValue(const int num) const;

  Standard_EXPORT int NbFillStyles() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_FillAreaStyle, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                        name;
  occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>> fillStyles;
};
