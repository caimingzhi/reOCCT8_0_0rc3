#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepVisual_Colour;

class StepVisual_FillAreaStyleColour : public Standard_Transient
{

public:
  //! Returns a FillAreaStyleColour
  Standard_EXPORT StepVisual_FillAreaStyleColour();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepVisual_Colour>&        aFillColour);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetFillColour(const occ::handle<StepVisual_Colour>& aFillColour);

  Standard_EXPORT occ::handle<StepVisual_Colour> FillColour() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_FillAreaStyleColour, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<StepVisual_Colour>        fillColour;
};

