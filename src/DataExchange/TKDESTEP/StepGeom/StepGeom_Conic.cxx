

#include <StepGeom_Conic.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Conic, StepGeom_Curve)

StepGeom_Conic::StepGeom_Conic() = default;

void StepGeom_Conic::Init(const occ::handle<TCollection_HAsciiString>& aName,
                          const StepGeom_Axis2Placement&               aPosition)
{

  position = aPosition;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_Conic::SetPosition(const StepGeom_Axis2Placement& aPosition)
{
  position = aPosition;
}

StepGeom_Axis2Placement StepGeom_Conic::Position() const
{
  return position;
}
