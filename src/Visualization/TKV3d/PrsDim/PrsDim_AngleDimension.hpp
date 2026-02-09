#pragma once

#include <PrsDim_Dimension.hpp>

enum PrsDim_TypeOfAngle
{
  PrsDim_TypeOfAngle_Interior,
  PrsDim_TypeOfAngle_Exterior,
};

enum PrsDim_TypeOfAngleArrowVisibility
{
  PrsDim_TypeOfAngleArrowVisibility_Both,
  PrsDim_TypeOfAngleArrowVisibility_First,
  PrsDim_TypeOfAngleArrowVisibility_Second,
  PrsDim_TypeOfAngleArrowVisibility_None,
};

#include <Geom_Plane.hpp>
#include <Geom_Line.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Standard.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Type.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

class PrsDim_AngleDimension : public PrsDim_Dimension
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_AngleDimension, PrsDim_Dimension)
public:
  Standard_EXPORT PrsDim_AngleDimension(const TopoDS_Edge& theFirstEdge,
                                        const TopoDS_Edge& theSecondEdge);

  Standard_EXPORT PrsDim_AngleDimension(const gp_Pnt& theFirstPoint,
                                        const gp_Pnt& theSecondPoint,
                                        const gp_Pnt& theThirdPoint);

  Standard_EXPORT PrsDim_AngleDimension(const TopoDS_Vertex& theFirstVertex,
                                        const TopoDS_Vertex& theSecondVertex,
                                        const TopoDS_Vertex& theThirdVertex);

  Standard_EXPORT PrsDim_AngleDimension(const TopoDS_Face& theCone);

  Standard_EXPORT PrsDim_AngleDimension(const TopoDS_Face& theFirstFace,
                                        const TopoDS_Face& theSecondFace);

  Standard_EXPORT PrsDim_AngleDimension(const TopoDS_Face& theFirstFace,
                                        const TopoDS_Face& theSecondFace,
                                        const gp_Pnt&      thePoint);

public:
  const gp_Pnt& FirstPoint() const { return myFirstPoint; }

  const gp_Pnt& SecondPoint() const { return mySecondPoint; }

  const gp_Pnt& CenterPoint() const { return myCenterPoint; }

  const TopoDS_Shape& FirstShape() const { return myFirstShape; }

  const TopoDS_Shape& SecondShape() const { return mySecondShape; }

  const TopoDS_Shape& ThirdShape() const { return myThirdShape; }

public:
  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Edge& theFirstEdge,
                                           const TopoDS_Edge& theSecondEdge);

  Standard_EXPORT void SetMeasuredGeometry(const gp_Pnt& theFirstPoint,
                                           const gp_Pnt& theSecondPoint,
                                           const gp_Pnt& theThridPoint);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Vertex& theFirstVertex,
                                           const TopoDS_Vertex& theSecondVertex,
                                           const TopoDS_Vertex& theThirdVertex);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Face& theCone);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Face& theFirstFace,
                                           const TopoDS_Face& theSecondFace);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Face& theFirstFace,
                                           const TopoDS_Face& theSecondFace,
                                           const gp_Pnt&      thePoint);

  Standard_EXPORT const TCollection_AsciiString& GetDisplayUnits() const override;

  Standard_EXPORT const TCollection_AsciiString& GetModelUnits() const override;

  Standard_EXPORT void SetDisplayUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetModelUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetTextPosition(const gp_Pnt& theTextPos) override;

  Standard_EXPORT gp_Pnt GetTextPosition() const override;

  void SetType(const PrsDim_TypeOfAngle theType) { myType = theType; }

  PrsDim_TypeOfAngle GetType() const { return myType; }

  void SetArrowsVisibility(const PrsDim_TypeOfAngleArrowVisibility& theType)
  {
    myArrowsVisibility = theType;
  }

  PrsDim_TypeOfAngleArrowVisibility GetArrowsVisibility() const { return myArrowsVisibility; }

protected:
  Standard_EXPORT void Init();

  gp_Dir GetNormalForMinAngle() const;

  Standard_EXPORT gp_Pnt GetCenterOnArc(const gp_Pnt& theFirstAttach,
                                        const gp_Pnt& theSecondAttach,
                                        const gp_Pnt& theCenter) const;

  Standard_EXPORT void DrawArc(const occ::handle<Prs3d_Presentation>& thePresentation,
                               const gp_Pnt&                          theFirstAttach,
                               const gp_Pnt&                          theSecondAttach,
                               const gp_Pnt&                          theCenter,
                               const double                           theRadius,
                               const int                              theMode);

  Standard_EXPORT void DrawArcWithText(const occ::handle<Prs3d_Presentation>& thePresentation,
                                       const gp_Pnt&                          theFirstAttach,
                                       const gp_Pnt&                          theSecondAttach,
                                       const gp_Pnt&                          theCenter,
                                       const TCollection_ExtendedString&      theText,
                                       const double                           theTextWidth,
                                       const int                              theMode,
                                       const int                              theLabelPosition);

  Standard_EXPORT void FitTextAlignment(
    const Prs3d_DimensionTextHorizontalPosition& theHorizontalTextPos,
    int&                                         theLabelPosition,
    bool&                                        theIsArrowsExternal) const;

  Standard_EXPORT void AdjustParameters(const gp_Pnt&                          theTextPos,
                                        double&                                theExtensionSize,
                                        Prs3d_DimensionTextHorizontalPosition& theAlignment,
                                        double&                                theFlyout) const;

protected:
  Standard_EXPORT virtual void ComputePlane();

  Standard_EXPORT bool CheckPlane(const gp_Pln& thePlane) const override;

  Standard_EXPORT double ComputeValue() const override;

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePM,
                               const occ::handle<Prs3d_Presentation>&         thePresentation,
                               const int                                      theMode = 0) override;

  Standard_EXPORT void ComputeFlyoutSelection(
    const occ::handle<SelectMgr_Selection>&   theSelection,
    const occ::handle<SelectMgr_EntityOwner>& theOwner) override;

protected:
  Standard_EXPORT bool InitTwoEdgesAngle(gp_Pln& theComputedPlane);

  Standard_EXPORT bool InitTwoFacesAngle();

  Standard_EXPORT bool InitTwoFacesAngle(const gp_Pnt& thePointOnFirstFace);

  Standard_EXPORT bool InitConeAngle();

  Standard_EXPORT bool IsValidPoints(const gp_Pnt& theFirstPoint,
                                     const gp_Pnt& theCenterPoint,
                                     const gp_Pnt& theSecondPoint) const;

  Standard_EXPORT bool isArrowVisible(const PrsDim_TypeOfAngleArrowVisibility theArrowType) const;

private:
  PrsDim_TypeOfAngle                myType;
  PrsDim_TypeOfAngleArrowVisibility myArrowsVisibility;

  gp_Pnt       myFirstPoint;
  gp_Pnt       mySecondPoint;
  gp_Pnt       myCenterPoint;
  TopoDS_Shape myFirstShape;
  TopoDS_Shape mySecondShape;
  TopoDS_Shape myThirdShape;
};
