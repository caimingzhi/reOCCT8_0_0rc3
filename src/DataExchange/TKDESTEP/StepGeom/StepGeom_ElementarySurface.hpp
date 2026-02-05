#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Surface.hpp>
class StepGeom_Axis2Placement3d;
class TCollection_HAsciiString;

class StepGeom_ElementarySurface : public StepGeom_Surface
{

public:
  //! Returns a ElementarySurface
  Standard_EXPORT StepGeom_ElementarySurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aPosition);

  Standard_EXPORT void SetPosition(const occ::handle<StepGeom_Axis2Placement3d>& aPosition);

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> Position() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_ElementarySurface, StepGeom_Surface)

private:
  occ::handle<StepGeom_Axis2Placement3d> position;
};
