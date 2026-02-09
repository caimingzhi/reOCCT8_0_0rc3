#pragma once

#include <AIS_InteractiveObject.hpp>

enum AIS_TypeOfPlane
{
  AIS_TOPL_Unknown,
  AIS_TOPL_XYPlane,
  AIS_TOPL_XZPlane,
  AIS_TOPL_YZPlane
};

#include <gp_Pnt.hpp>
#include <Select3D_TypeOfSensitivity.hpp>

class Geom_Plane;
class Geom_Axis2Placement;

class AIS_Plane : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Plane, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Plane(const occ::handle<Geom_Plane>& aComponent,
                            const bool                     aCurrentMode = false);

  Standard_EXPORT AIS_Plane(const occ::handle<Geom_Plane>& aComponent,
                            const gp_Pnt&                  aCenter,
                            const bool                     aCurrentMode = false);

  Standard_EXPORT AIS_Plane(const occ::handle<Geom_Plane>& aComponent,
                            const gp_Pnt&                  aCenter,
                            const gp_Pnt&                  aPmin,
                            const gp_Pnt&                  aPmax,
                            const bool                     aCurrentMode = false);

  Standard_EXPORT AIS_Plane(const occ::handle<Geom_Axis2Placement>& aComponent,
                            const AIS_TypeOfPlane                   aPlaneType,
                            const bool                              aCurrentMode = false);

  Standard_EXPORT void SetSize(const double aValue);

  Standard_EXPORT void SetSize(const double Xval, const double YVal);

  Standard_EXPORT void UnsetSize();

  Standard_EXPORT bool Size(double& X, double& Y) const;

  bool HasOwnSize() const { return myHasOwnSize; }

  Standard_EXPORT void SetMinimumSize(const double theValue);

  Standard_EXPORT void UnsetMinimumSize();

  Standard_EXPORT bool HasMinimumSize() const;

  int Signature() const override { return 7; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  const occ::handle<Geom_Plane>& Component() { return myComponent; }

  Standard_EXPORT void SetComponent(const occ::handle<Geom_Plane>& aComponent);

  Standard_EXPORT bool PlaneAttributes(occ::handle<Geom_Plane>& aComponent,
                                       gp_Pnt&                  aCenter,
                                       gp_Pnt&                  aPmin,
                                       gp_Pnt&                  aPmax);

  Standard_EXPORT void SetPlaneAttributes(const occ::handle<Geom_Plane>& aComponent,
                                          const gp_Pnt&                  aCenter,
                                          const gp_Pnt&                  aPmin,
                                          const gp_Pnt&                  aPmax);

  const gp_Pnt& Center() const { return myCenter; }

  void SetCenter(const gp_Pnt& theCenter) { myCenter = theCenter; }

  Standard_EXPORT void SetAxis2Placement(const occ::handle<Geom_Axis2Placement>& aComponent,
                                         const AIS_TypeOfPlane                   aPlaneType);

  Standard_EXPORT occ::handle<Geom_Axis2Placement> Axis2Placement();

  AIS_TypeOfPlane TypeOfPlane() { return myTypeOfPlane; }

  bool IsXYZPlane() { return myIsXYZPlane; }

  bool CurrentMode() { return myCurrentMode; }

  void SetCurrentMode(const bool theCurrentMode) { myCurrentMode = theCurrentMode; }

  Standard_EXPORT bool AcceptDisplayMode(const int aMode) const override;

  Standard_EXPORT void SetContext(const occ::handle<AIS_InteractiveContext>& aCtx) override;

  Select3D_TypeOfSensitivity TypeOfSensitivity() const { return myTypeOfSensitivity; }

  void SetTypeOfSensitivity(Select3D_TypeOfSensitivity theTypeOfSensitivity)
  {
    myTypeOfSensitivity = theTypeOfSensitivity;
  }

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  Standard_EXPORT void SetColor(const Quantity_Color& aColor) override;

  Standard_EXPORT void UnsetColor() override;

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeFrame();

  Standard_EXPORT void ComputeFields();

  Standard_EXPORT void InitDrawerAttributes();

private:
  occ::handle<Geom_Plane>          myComponent;
  occ::handle<Geom_Axis2Placement> myAx2;
  gp_Pnt                           myCenter;
  gp_Pnt                           myPmin;
  gp_Pnt                           myPmax;
  bool                             myCurrentMode;
  bool                             myAutomaticPosition;
  AIS_TypeOfPlane                  myTypeOfPlane;
  bool                             myIsXYZPlane;
  bool                             myHasOwnSize;
  Select3D_TypeOfSensitivity       myTypeOfSensitivity;
};
