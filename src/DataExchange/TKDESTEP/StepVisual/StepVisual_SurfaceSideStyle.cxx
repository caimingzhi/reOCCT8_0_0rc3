

#include <StepVisual_SurfaceSideStyle.hpp>
#include <StepVisual_SurfaceStyleElementSelect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_SurfaceSideStyle, Standard_Transient)

StepVisual_SurfaceSideStyle::StepVisual_SurfaceSideStyle() = default;

void StepVisual_SurfaceSideStyle::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>>& aStyles)
{

  name   = aName;
  styles = aStyles;
}

void StepVisual_SurfaceSideStyle::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_SurfaceSideStyle::Name() const
{
  return name;
}

void StepVisual_SurfaceSideStyle::SetStyles(
  const occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>>& aStyles)
{
  styles = aStyles;
}

occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>> StepVisual_SurfaceSideStyle::
  Styles() const
{
  return styles;
}

StepVisual_SurfaceStyleElementSelect StepVisual_SurfaceSideStyle::StylesValue(const int num) const
{
  return styles->Value(num);
}

int StepVisual_SurfaceSideStyle::NbStyles() const
{
  return (styles.IsNull()) ? 0 : styles->Length();
}
