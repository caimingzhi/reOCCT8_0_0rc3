#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Surface.hpp>
class StepGeom_Curve;
class TCollection_HAsciiString;

class StepGeom_SweptSurface : public StepGeom_Surface
{

public:
  //! Returns a SweptSurface
  Standard_EXPORT StepGeom_SweptSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Curve>&           aSweptCurve);

  Standard_EXPORT void SetSweptCurve(const occ::handle<StepGeom_Curve>& aSweptCurve);

  Standard_EXPORT occ::handle<StepGeom_Curve> SweptCurve() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_SweptSurface, StepGeom_Surface)

private:
  occ::handle<StepGeom_Curve> sweptCurve;
};

