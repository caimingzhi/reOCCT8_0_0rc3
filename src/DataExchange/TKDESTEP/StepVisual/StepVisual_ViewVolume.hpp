#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_CentralOrParallel.hpp>
#include <Standard_Transient.hpp>
class StepGeom_CartesianPoint;
class StepVisual_PlanarBox;

class StepVisual_ViewVolume : public Standard_Transient
{

public:
  //! Returns a ViewVolume
  Standard_EXPORT StepVisual_ViewVolume();

  Standard_EXPORT void Init(const StepVisual_CentralOrParallel          aProjectionType,
                            const occ::handle<StepGeom_CartesianPoint>& aProjectionPoint,
                            const double                                aViewPlaneDistance,
                            const double                                aFrontPlaneDistance,
                            const bool                                  aFrontPlaneClipping,
                            const double                                aBackPlaneDistance,
                            const bool                                  aBackPlaneClipping,
                            const bool                                  aViewVolumeSidesClipping,
                            const occ::handle<StepVisual_PlanarBox>&    aViewWindow);

  Standard_EXPORT void SetProjectionType(const StepVisual_CentralOrParallel aProjectionType);

  Standard_EXPORT StepVisual_CentralOrParallel ProjectionType() const;

  Standard_EXPORT void SetProjectionPoint(
    const occ::handle<StepGeom_CartesianPoint>& aProjectionPoint);

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> ProjectionPoint() const;

  Standard_EXPORT void SetViewPlaneDistance(const double aViewPlaneDistance);

  Standard_EXPORT double ViewPlaneDistance() const;

  Standard_EXPORT void SetFrontPlaneDistance(const double aFrontPlaneDistance);

  Standard_EXPORT double FrontPlaneDistance() const;

  Standard_EXPORT void SetFrontPlaneClipping(const bool aFrontPlaneClipping);

  Standard_EXPORT bool FrontPlaneClipping() const;

  Standard_EXPORT void SetBackPlaneDistance(const double aBackPlaneDistance);

  Standard_EXPORT double BackPlaneDistance() const;

  Standard_EXPORT void SetBackPlaneClipping(const bool aBackPlaneClipping);

  Standard_EXPORT bool BackPlaneClipping() const;

  Standard_EXPORT void SetViewVolumeSidesClipping(const bool aViewVolumeSidesClipping);

  Standard_EXPORT bool ViewVolumeSidesClipping() const;

  Standard_EXPORT void SetViewWindow(const occ::handle<StepVisual_PlanarBox>& aViewWindow);

  Standard_EXPORT occ::handle<StepVisual_PlanarBox> ViewWindow() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_ViewVolume, Standard_Transient)

private:
  StepVisual_CentralOrParallel         projectionType;
  occ::handle<StepGeom_CartesianPoint> projectionPoint;
  double                               viewPlaneDistance;
  double                               frontPlaneDistance;
  bool                                 frontPlaneClipping;
  double                               backPlaneDistance;
  bool                                 backPlaneClipping;
  bool                                 viewVolumeSidesClipping;
  occ::handle<StepVisual_PlanarBox>    viewWindow;
};
