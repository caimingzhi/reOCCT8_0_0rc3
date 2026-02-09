#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_MarkerSelect.hpp>
#include <StepBasic_SizeSelect.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepVisual_Colour;

class StepVisual_PointStyle : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_PointStyle();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepVisual_MarkerSelect&               aMarker,
                            const StepBasic_SizeSelect&                  aMarkerSize,
                            const occ::handle<StepVisual_Colour>&        aMarkerColour);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetMarker(const StepVisual_MarkerSelect& aMarker);

  Standard_EXPORT StepVisual_MarkerSelect Marker() const;

  Standard_EXPORT void SetMarkerSize(const StepBasic_SizeSelect& aMarkerSize);

  Standard_EXPORT StepBasic_SizeSelect MarkerSize() const;

  Standard_EXPORT void SetMarkerColour(const occ::handle<StepVisual_Colour>& aMarkerColour);

  Standard_EXPORT occ::handle<StepVisual_Colour> MarkerColour() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PointStyle, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  StepVisual_MarkerSelect               marker;
  StepBasic_SizeSelect                  markerSize;
  occ::handle<StepVisual_Colour>        markerColour;
};
