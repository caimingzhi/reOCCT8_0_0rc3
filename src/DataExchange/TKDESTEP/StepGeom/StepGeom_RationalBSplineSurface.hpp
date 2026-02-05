#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepGeom_BSplineSurface.hpp>
#include <Standard_Integer.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_BSplineSurfaceForm.hpp>
#include <StepData_Logical.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class StepGeom_RationalBSplineSurface : public StepGeom_BSplineSurface
{

public:
  //! Returns a RationalBSplineSurface
  Standard_EXPORT StepGeom_RationalBSplineSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aUDegree,
    const int                                    aVDegree,
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>&
                                                    aControlPointsList,
    const StepGeom_BSplineSurfaceForm               aSurfaceForm,
    const StepData_Logical                          aUClosed,
    const StepData_Logical                          aVClosed,
    const StepData_Logical                          aSelfIntersect,
    const occ::handle<NCollection_HArray2<double>>& aWeightsData);

  Standard_EXPORT void SetWeightsData(const occ::handle<NCollection_HArray2<double>>& aWeightsData);

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> WeightsData() const;

  Standard_EXPORT double WeightsDataValue(const int num1, const int num2) const;

  Standard_EXPORT int NbWeightsDataI() const;

  Standard_EXPORT int NbWeightsDataJ() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_RationalBSplineSurface, StepGeom_BSplineSurface)

private:
  occ::handle<NCollection_HArray2<double>> weightsData;
};
