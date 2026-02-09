#pragma once

#include <AIS_InteractiveObject.hpp>
#include <AIS_KindOfInteractive.hpp>

class Geom_Line;
class Geom_Point;

class AIS_Line : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Line, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Line(const occ::handle<Geom_Line>& aLine);

  Standard_EXPORT AIS_Line(const occ::handle<Geom_Point>& aStartPoint,
                           const occ::handle<Geom_Point>& aEndPoint);

  int Signature() const override { return 5; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  const occ::handle<Geom_Line>& Line() const { return myComponent; }

  void Points(occ::handle<Geom_Point>& thePStart, occ::handle<Geom_Point>& thePEnd) const
  {
    thePStart = myStartPoint;
    thePEnd   = myEndPoint;
  }

  void SetLine(const occ::handle<Geom_Line>& theLine)
  {
    myComponent     = theLine;
    myLineIsSegment = false;
  }

  void SetPoints(const occ::handle<Geom_Point>& thePStart, const occ::handle<Geom_Point>& thePEnd)
  {
    myStartPoint    = thePStart;
    myEndPoint      = thePEnd;
    myLineIsSegment = true;
  }

  Standard_EXPORT void SetColor(const Quantity_Color& aColor) override;

  Standard_EXPORT void SetWidth(const double aValue) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void UnsetWidth() override;

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeInfiniteLine(const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeSegmentLine(const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeInfiniteLineSelection(
    const occ::handle<SelectMgr_Selection>& aSelection);

  Standard_EXPORT void ComputeSegmentLineSelection(
    const occ::handle<SelectMgr_Selection>& aSelection);

  void replaceWithNewLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect);

private:
  occ::handle<Geom_Line>  myComponent;
  occ::handle<Geom_Point> myStartPoint;
  occ::handle<Geom_Point> myEndPoint;
  bool                    myLineIsSegment;
};
