#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

enum StepFEA_CoordinateSystemType
{
  StepFEA_Cartesian,
  StepFEA_Cylindrical,
  StepFEA_Spherical
};

#include <StepGeom_Axis2Placement3d.hpp>
#include <Standard_Boolean.hpp>
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;
class StepGeom_Direction;

class StepFEA_FeaAxis2Placement3d : public StepGeom_Axis2Placement3d
{

public:
  Standard_EXPORT StepFEA_FeaAxis2Placement3d();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<StepGeom_CartesianPoint>&  aPlacement_Location,
                            const bool                                   hasAxis2Placement3d_Axis,
                            const occ::handle<StepGeom_Direction>&       aAxis2Placement3d_Axis,
                            const bool                             hasAxis2Placement3d_RefDirection,
                            const occ::handle<StepGeom_Direction>& aAxis2Placement3d_RefDirection,
                            const StepFEA_CoordinateSystemType     aSystemType,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT StepFEA_CoordinateSystemType SystemType() const;

  Standard_EXPORT void SetSystemType(const StepFEA_CoordinateSystemType SystemType);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaAxis2Placement3d, StepGeom_Axis2Placement3d)

private:
  StepFEA_CoordinateSystemType          theSystemType;
  occ::handle<TCollection_HAsciiString> theDescription;
};
