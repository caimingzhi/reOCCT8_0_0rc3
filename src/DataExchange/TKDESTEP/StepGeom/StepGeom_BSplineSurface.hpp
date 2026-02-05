#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepGeom_BSplineSurfaceForm.hpp>
#include <StepData_Logical.hpp>
#include <StepGeom_BoundedSurface.hpp>
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepGeom_BSplineSurface : public StepGeom_BoundedSurface
{

public:
  //! Returns a BSplineSurface
  Standard_EXPORT StepGeom_BSplineSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aUDegree,
    const int                                    aVDegree,
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>&
                                      aControlPointsList,
    const StepGeom_BSplineSurfaceForm aSurfaceForm,
    const StepData_Logical            aUClosed,
    const StepData_Logical            aVClosed,
    const StepData_Logical            aSelfIntersect);

  Standard_EXPORT void SetUDegree(const int aUDegree);

  Standard_EXPORT int UDegree() const;

  Standard_EXPORT void SetVDegree(const int aVDegree);

  Standard_EXPORT int VDegree() const;

  Standard_EXPORT void SetControlPointsList(
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>&
      aControlPointsList);

  Standard_EXPORT occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>
                  ControlPointsList() const;

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> ControlPointsListValue(const int num1,
                                                                              const int num2) const;

  Standard_EXPORT int NbControlPointsListI() const;

  Standard_EXPORT int NbControlPointsListJ() const;

  Standard_EXPORT void SetSurfaceForm(const StepGeom_BSplineSurfaceForm aSurfaceForm);

  Standard_EXPORT StepGeom_BSplineSurfaceForm SurfaceForm() const;

  Standard_EXPORT void SetUClosed(const StepData_Logical aUClosed);

  Standard_EXPORT StepData_Logical UClosed() const;

  Standard_EXPORT void SetVClosed(const StepData_Logical aVClosed);

  Standard_EXPORT StepData_Logical VClosed() const;

  Standard_EXPORT void SetSelfIntersect(const StepData_Logical aSelfIntersect);

  Standard_EXPORT StepData_Logical SelfIntersect() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_BSplineSurface, StepGeom_BoundedSurface)

private:
  int                                                                    uDegree;
  int                                                                    vDegree;
  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> controlPointsList;
  StepGeom_BSplineSurfaceForm                                            surfaceForm;
  StepData_Logical                                                       uClosed;
  StepData_Logical                                                       vClosed;
  StepData_Logical                                                       selfIntersect;
};
