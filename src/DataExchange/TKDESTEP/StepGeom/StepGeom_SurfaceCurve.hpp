#pragma once


#include <Standard.hpp>

#include <StepGeom_PcurveOrSurface.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_PreferredSurfaceCurveRepresentation.hpp>
#include <StepGeom_Curve.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepGeom_PcurveOrSurface;

class StepGeom_SurfaceCurve : public StepGeom_Curve
{

public:
  //! Returns a SurfaceCurve
  Standard_EXPORT StepGeom_SurfaceCurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                      aName,
    const occ::handle<StepGeom_Curve>&                                aCurve3d,
    const occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>>& aAssociatedGeometry,
    const StepGeom_PreferredSurfaceCurveRepresentation                aMasterRepresentation);

  Standard_EXPORT void SetCurve3d(const occ::handle<StepGeom_Curve>& aCurve3d);

  Standard_EXPORT occ::handle<StepGeom_Curve> Curve3d() const;

  Standard_EXPORT void SetAssociatedGeometry(
    const occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>>& aAssociatedGeometry);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>> AssociatedGeometry()
    const;

  Standard_EXPORT StepGeom_PcurveOrSurface AssociatedGeometryValue(const int num) const;

  Standard_EXPORT int NbAssociatedGeometry() const;

  Standard_EXPORT void SetMasterRepresentation(
    const StepGeom_PreferredSurfaceCurveRepresentation aMasterRepresentation);

  Standard_EXPORT StepGeom_PreferredSurfaceCurveRepresentation MasterRepresentation() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfaceCurve, StepGeom_Curve)

private:
  occ::handle<StepGeom_Curve>                                curve3d;
  occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>> associatedGeometry;
  StepGeom_PreferredSurfaceCurveRepresentation               masterRepresentation;
};

