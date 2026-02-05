#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_SolidModel.hpp>
class StepShape_ConnectedFaceSet;
class TCollection_HAsciiString;
class StepShape_ClosedShell;

class StepShape_ManifoldSolidBrep : public StepShape_SolidModel
{

public:
  //! Returns a ManifoldSolidBrep
  Standard_EXPORT StepShape_ManifoldSolidBrep();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_ClosedShell>&    aOuter);

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&   aName,
                            const occ::handle<StepShape_ConnectedFaceSet>& aOuter);

  Standard_EXPORT void SetOuter(const occ::handle<StepShape_ConnectedFaceSet>& aOuter);

  Standard_EXPORT occ::handle<StepShape_ConnectedFaceSet> Outer() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_ManifoldSolidBrep, StepShape_SolidModel)

private:
  occ::handle<StepShape_ConnectedFaceSet> outer;
};
