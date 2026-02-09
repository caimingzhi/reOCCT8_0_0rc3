

#include <StepVisual_Colour.hpp>
#include <StepVisual_PointStyle.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PointStyle, Standard_Transient)

StepVisual_PointStyle::StepVisual_PointStyle() = default;

void StepVisual_PointStyle::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                 const StepVisual_MarkerSelect&               aMarker,
                                 const StepBasic_SizeSelect&                  aMarkerSize,
                                 const occ::handle<StepVisual_Colour>&        aMarkerColour)
{

  name         = aName;
  marker       = aMarker;
  markerSize   = aMarkerSize;
  markerColour = aMarkerColour;
}

void StepVisual_PointStyle::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_PointStyle::Name() const
{
  return name;
}

void StepVisual_PointStyle::SetMarker(const StepVisual_MarkerSelect& aMarker)
{
  marker = aMarker;
}

StepVisual_MarkerSelect StepVisual_PointStyle::Marker() const
{
  return marker;
}

void StepVisual_PointStyle::SetMarkerSize(const StepBasic_SizeSelect& aMarkerSize)
{
  markerSize = aMarkerSize;
}

StepBasic_SizeSelect StepVisual_PointStyle::MarkerSize() const
{
  return markerSize;
}

void StepVisual_PointStyle::SetMarkerColour(const occ::handle<StepVisual_Colour>& aMarkerColour)
{
  markerColour = aMarkerColour;
}

occ::handle<StepVisual_Colour> StepVisual_PointStyle::MarkerColour() const
{
  return markerColour;
}
