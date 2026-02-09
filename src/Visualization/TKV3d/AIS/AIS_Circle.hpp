#pragma once

#include <AIS_InteractiveObject.hpp>

class Geom_Circle;

class AIS_Circle : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Circle, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Circle(const occ::handle<Geom_Circle>& aCircle);

  Standard_EXPORT AIS_Circle(const occ::handle<Geom_Circle>& theCircle,
                             const double                    theUStart,
                             const double                    theUEnd,
                             const bool                      theIsFilledCircleSens = false);

  int Signature() const override { return 6; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  const occ::handle<Geom_Circle>& Circle() const { return myComponent; }

  void Parameters(double& theU1, double& theU2) const
  {
    theU1 = myUStart;
    theU2 = myUEnd;
  }

  void SetCircle(const occ::handle<Geom_Circle>& theCircle) { myComponent = theCircle; }

  void SetFirstParam(const double theU)
  {
    myUStart      = theU;
    myCircleIsArc = true;
  }

  void SetLastParam(const double theU)
  {
    myUEnd        = theU;
    myCircleIsArc = true;
  }

  Standard_EXPORT void SetColor(const Quantity_Color& aColor) override;

  Standard_EXPORT void SetWidth(const double aValue) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void UnsetWidth() override;

  bool IsFilledCircleSens() const { return myIsFilledCircleSens; }

  void SetFilledCircleSens(const bool theIsFilledCircleSens)
  {
    myIsFilledCircleSens = theIsFilledCircleSens;
  }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         theprs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeCircle(const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeArc(const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeCircleSelection(const occ::handle<SelectMgr_Selection>& aSelection);

  Standard_EXPORT void ComputeArcSelection(const occ::handle<SelectMgr_Selection>& aSelection);

  void replaceWithNewLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect);

private:
  occ::handle<Geom_Circle> myComponent;
  double                   myUStart;
  double                   myUEnd;
  bool                     myCircleIsArc;
  bool                     myIsFilledCircleSens;
};
