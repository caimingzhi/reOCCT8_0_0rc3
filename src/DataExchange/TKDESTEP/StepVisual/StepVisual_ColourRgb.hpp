#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <StepVisual_ColourSpecification.hpp>
class TCollection_HAsciiString;

class StepVisual_ColourRgb : public StepVisual_ColourSpecification
{

public:
  //! Returns a ColourRgb
  Standard_EXPORT StepVisual_ColourRgb();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const double                                 aRed,
                            const double                                 aGreen,
                            const double                                 aBlue);

  Standard_EXPORT void SetRed(const double aRed);

  Standard_EXPORT double Red() const;

  Standard_EXPORT void SetGreen(const double aGreen);

  Standard_EXPORT double Green() const;

  Standard_EXPORT void SetBlue(const double aBlue);

  Standard_EXPORT double Blue() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_ColourRgb, StepVisual_ColourSpecification)

private:
  double red;
  double green;
  double blue;
};
