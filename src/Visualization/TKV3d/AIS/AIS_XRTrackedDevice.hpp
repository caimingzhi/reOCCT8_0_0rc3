#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Aspect_XRTrackedDeviceRole.hpp>

class Graphic3d_ArrayOfTriangles;
class Image_Texture;

class AIS_XRTrackedDevice : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_XRTrackedDevice, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_XRTrackedDevice(const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
                                      const occ::handle<Image_Texture>&              theTexture);

  Standard_EXPORT AIS_XRTrackedDevice();

  Aspect_XRTrackedDeviceRole Role() const { return myRole; }

  void SetRole(Aspect_XRTrackedDeviceRole theRole) { myRole = theRole; }

  const Quantity_Color& LaserColor() const { return myLaserColor; }

  Standard_EXPORT void SetLaserColor(const Quantity_Color& theColor);

  float LaserLength() const { return myLaserLength; }

  Standard_EXPORT void SetLaserLength(float theLength);

  float UnitFactor() const { return myUnitFactor; }

  void SetUnitFactor(float theFactor) { myUnitFactor = theFactor; }

protected:
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void computeLaserRay();

private:
  class XRTexture;

private:
  occ::handle<Graphic3d_Group> myRayGroup;

  occ::handle<Graphic3d_ArrayOfTriangles> myTris;
  Quantity_Color                          myLaserColor;
  float                                   myLaserLength;
  float                                   myUnitFactor;
  Aspect_XRTrackedDeviceRole              myRole;
  bool                                    myToShowAxes;
};
