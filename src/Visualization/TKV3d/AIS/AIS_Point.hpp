#pragma once

#include <AIS_InteractiveObject.hpp>

class Geom_Point;
class TopoDS_Vertex;

class AIS_Point : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Point, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Point(const occ::handle<Geom_Point>& aComponent);

  int Signature() const override { return 1; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  Standard_EXPORT occ::handle<Geom_Point> Component();

  Standard_EXPORT void SetComponent(const occ::handle<Geom_Point>& aComponent);

  Standard_EXPORT bool AcceptDisplayMode(const int aMode) const override;

  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void SetMarker(const Aspect_TypeOfMarker aType);

  Standard_EXPORT void UnsetMarker();

  bool HasMarker() const { return myHasTOM; }

  Standard_EXPORT TopoDS_Vertex Vertex() const;

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

private:
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                        const int                               aMode) override;

  Standard_EXPORT void UpdatePointValues();

  void replaceWithNewPointAspect(const occ::handle<Prs3d_PointAspect>& theAspect);

private:
  occ::handle<Geom_Point> myComponent;
  bool                    myHasTOM;
  Aspect_TypeOfMarker     myTOM;
};
