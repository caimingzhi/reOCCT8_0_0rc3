#pragma once

#include <AIS_InteractiveObject.hpp>

class Graphic3d_ArrayOfSegments;
class Graphic3d_ArrayOfTriangles;

class AIS_CameraFrustum : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_CameraFrustum, AIS_InteractiveObject)
public:
  enum SelectionMode
  {
    SelectionMode_Edges  = 0,
    SelectionMode_Volume = 1,
  };

public:
  Standard_EXPORT AIS_CameraFrustum();

  Standard_EXPORT void SetCameraFrustum(const occ::handle<Graphic3d_Camera>& theCamera);

  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void UnsetTransparency() override;

  Standard_EXPORT bool AcceptDisplayMode(const int theMode) const override;

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

private:
  void fillTriangles();

  void fillBorders();

protected:
  NCollection_Array1<NCollection_Vec3<double>> myPoints;
  occ::handle<Graphic3d_ArrayOfTriangles>      myTriangles;
  occ::handle<Graphic3d_ArrayOfSegments>       myBorders;
};
