#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Sequence.hpp>

class AIS_RubberBand : public AIS_InteractiveObject
{
public:
  DEFINE_STANDARD_RTTIEXT(AIS_RubberBand, AIS_InteractiveObject)

  Standard_EXPORT AIS_RubberBand();

  Standard_EXPORT AIS_RubberBand(const Quantity_Color&   theLineColor,
                                 const Aspect_TypeOfLine theType,
                                 const double            theLineWidth       = 1.0,
                                 const bool              theIsPolygonClosed = true);

  Standard_EXPORT AIS_RubberBand(const Quantity_Color&   theLineColor,
                                 const Aspect_TypeOfLine theType,
                                 const Quantity_Color    theFillColor,
                                 const double            theTransparency    = 1.0,
                                 const double            theLineWidth       = 1.0,
                                 const bool              theIsPolygonClosed = true);

  Standard_EXPORT ~AIS_RubberBand() override;

  Standard_EXPORT void SetRectangle(const int theMinX,
                                    const int theMinY,
                                    const int theMaxX,
                                    const int theMaxY);

  Standard_EXPORT void AddPoint(const NCollection_Vec2<int>& thePoint);

  Standard_EXPORT void RemoveLastPoint();

  Standard_EXPORT const NCollection_Sequence<NCollection_Vec2<int>>& Points() const;

  void ClearPoints() { myPoints.Clear(); }

  Standard_EXPORT Quantity_Color LineColor() const;

  Standard_EXPORT void SetLineColor(const Quantity_Color& theColor);

  Standard_EXPORT Quantity_Color FillColor() const;

  Standard_EXPORT void SetFillColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetLineWidth(const double theWidth) const;

  Standard_EXPORT double LineWidth() const;

  Standard_EXPORT void SetLineType(const Aspect_TypeOfLine theType);

  Standard_EXPORT Aspect_TypeOfLine LineType() const;

  Standard_EXPORT void SetFillTransparency(const double theValue) const;

  Standard_EXPORT double FillTransparency() const;

  Standard_EXPORT void SetFilling(const bool theIsFilling);

  Standard_EXPORT void SetFilling(const Quantity_Color theColor, const double theTransparency);

  Standard_EXPORT bool IsFilling() const;

  Standard_EXPORT bool IsPolygonClosed() const;

  Standard_EXPORT void SetPolygonClosed(bool theIsPolygonClosed);

protected:
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  void ComputeSelection(const occ::handle<SelectMgr_Selection>&, const int) override {};

  Standard_EXPORT bool fillTriangles();

protected:
  NCollection_Sequence<NCollection_Vec2<int>> myPoints;

  occ::handle<Graphic3d_ArrayOfTriangles> myTriangles;
  occ::handle<Graphic3d_ArrayOfPolylines> myBorders;

  bool myIsPolygonClosed;
};
