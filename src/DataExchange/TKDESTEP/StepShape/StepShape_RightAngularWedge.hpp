#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Axis2Placement3d;
class TCollection_HAsciiString;

class StepShape_RightAngularWedge : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepShape_RightAngularWedge();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                            const double                                  aX,
                            const double                                  aY,
                            const double                                  aZ,
                            const double                                  aLtx);

  Standard_EXPORT void SetPosition(const occ::handle<StepGeom_Axis2Placement3d>& aPosition);

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> Position() const;

  Standard_EXPORT void SetX(const double aX);

  Standard_EXPORT double X() const;

  Standard_EXPORT void SetY(const double aY);

  Standard_EXPORT double Y() const;

  Standard_EXPORT void SetZ(const double aZ);

  Standard_EXPORT double Z() const;

  Standard_EXPORT void SetLtx(const double aLtx);

  Standard_EXPORT double Ltx() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_RightAngularWedge, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Axis2Placement3d> position;
  double                                 x;
  double                                 y;
  double                                 z;
  double                                 ltx;
};
