#pragma once

#include <Standard.hpp>

#include <StepVisual_SurfaceStyleElementSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_SurfaceStyleElementSelect;

class StepVisual_SurfaceSideStyle : public Standard_Transient
{

public:
  //! Returns a SurfaceSideStyle
  Standard_EXPORT StepVisual_SurfaceSideStyle();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                  aName,
    const occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>>& aStyles);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetStyles(
    const occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>>& aStyles);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>> Styles()
    const;

  Standard_EXPORT StepVisual_SurfaceStyleElementSelect StylesValue(const int num) const;

  Standard_EXPORT int NbStyles() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceSideStyle, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                  name;
  occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>> styles;
};
