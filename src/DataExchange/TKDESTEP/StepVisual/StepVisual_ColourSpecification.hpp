#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_Colour.hpp>
class TCollection_HAsciiString;

class StepVisual_ColourSpecification : public StepVisual_Colour
{

public:
  //! Returns a ColourSpecification
  Standard_EXPORT StepVisual_ColourSpecification();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_ColourSpecification, StepVisual_Colour)

private:
  occ::handle<TCollection_HAsciiString> name;
};

