#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_Curve.hpp>
class StepGeom_CartesianPoint;
class StepGeom_Vector;
class TCollection_HAsciiString;

class StepGeom_Line : public StepGeom_Curve
{

public:
  //! Returns a Line
  Standard_EXPORT StepGeom_Line();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_CartesianPoint>&  aPnt,
                            const occ::handle<StepGeom_Vector>&          aDir);

  Standard_EXPORT void SetPnt(const occ::handle<StepGeom_CartesianPoint>& aPnt);

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> Pnt() const;

  Standard_EXPORT void SetDir(const occ::handle<StepGeom_Vector>& aDir);

  Standard_EXPORT occ::handle<StepGeom_Vector> Dir() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Line, StepGeom_Curve)

private:
  occ::handle<StepGeom_CartesianPoint> pnt;
  occ::handle<StepGeom_Vector>         dir;
};
