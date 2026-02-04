#pragma once


#include <Standard.hpp>

#include <StepGeom_Axis2Placement.hpp>
#include <StepGeom_Curve.hpp>
class TCollection_HAsciiString;

class StepGeom_Conic : public StepGeom_Curve
{

public:
  //! Returns a Conic
  Standard_EXPORT StepGeom_Conic();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepGeom_Axis2Placement&               aPosition);

  Standard_EXPORT void SetPosition(const StepGeom_Axis2Placement& aPosition);

  Standard_EXPORT StepGeom_Axis2Placement Position() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Conic, StepGeom_Curve)

private:
  StepGeom_Axis2Placement position;
};

