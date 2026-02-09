#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_FeaRepresentationItem.hpp>
class StepFEA_FeaAxis2Placement3d;
class TCollection_HAsciiString;

class StepFEA_AlignedCurve3dElementCoordinateSystem : public StepFEA_FeaRepresentationItem
{

public:
  Standard_EXPORT StepFEA_AlignedCurve3dElementCoordinateSystem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<StepFEA_FeaAxis2Placement3d>& aCoordinateSystem);

  Standard_EXPORT occ::handle<StepFEA_FeaAxis2Placement3d> CoordinateSystem() const;

  Standard_EXPORT void SetCoordinateSystem(
    const occ::handle<StepFEA_FeaAxis2Placement3d>& CoordinateSystem);

  DEFINE_STANDARD_RTTIEXT(StepFEA_AlignedCurve3dElementCoordinateSystem,
                          StepFEA_FeaRepresentationItem)

private:
  occ::handle<StepFEA_FeaAxis2Placement3d> theCoordinateSystem;
};
