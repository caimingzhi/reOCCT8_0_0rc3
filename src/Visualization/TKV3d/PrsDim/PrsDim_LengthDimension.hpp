#pragma once

#include <PrsDim_Dimension.hpp>
#include <Geom_Plane.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <TopoDS.hpp>

class PrsDim_LengthDimension : public PrsDim_Dimension
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_LengthDimension, PrsDim_Dimension)
public:
  Standard_EXPORT PrsDim_LengthDimension();

  Standard_EXPORT PrsDim_LengthDimension(const TopoDS_Face& theFace, const TopoDS_Edge& theEdge);

  Standard_EXPORT PrsDim_LengthDimension(const TopoDS_Face& theFirstFace,
                                         const TopoDS_Face& theSecondFace);

  Standard_EXPORT PrsDim_LengthDimension(const gp_Pnt& theFirstPoint,
                                         const gp_Pnt& theSecondPoint,
                                         const gp_Pln& thePlane);

  Standard_EXPORT PrsDim_LengthDimension(const TopoDS_Shape& theFirstShape,
                                         const TopoDS_Shape& theSecondShape,
                                         const gp_Pln&       thePlane);

  Standard_EXPORT PrsDim_LengthDimension(const TopoDS_Edge& theEdge, const gp_Pln& thePlane);

public:
  const gp_Pnt& FirstPoint() const { return myFirstPoint; }

  const gp_Pnt& SecondPoint() const { return mySecondPoint; }

  const TopoDS_Shape& FirstShape() const { return myFirstShape; }

  const TopoDS_Shape& SecondShape() const { return mySecondShape; }

public:
  Standard_EXPORT void SetMeasuredGeometry(const gp_Pnt& theFirstPoint,
                                           const gp_Pnt& theSecondPoint,
                                           const gp_Pln& thePlane);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Edge& theEdge, const gp_Pln& thePlane);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Face& theFirstFace,
                                           const TopoDS_Face& theSecondFace);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Face& theFace, const TopoDS_Edge& theEdge);

  Standard_EXPORT void SetMeasuredShapes(const TopoDS_Shape& theFirstShape,
                                         const TopoDS_Shape& theSecondShape);

  Standard_EXPORT const TCollection_AsciiString& GetDisplayUnits() const override;

  Standard_EXPORT const TCollection_AsciiString& GetModelUnits() const override;

  Standard_EXPORT void SetDisplayUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetModelUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetTextPosition(const gp_Pnt& theTextPos) override;

  Standard_EXPORT gp_Pnt GetTextPosition() const override;

  Standard_EXPORT void SetDirection(const gp_Dir& theDirection, const bool theUseDirection = true);

protected:
  Standard_EXPORT bool CheckPlane(const gp_Pln& thePlane) const override;

  Standard_EXPORT virtual gp_Pln ComputePlane(const gp_Dir& theAttachDir) const;

  Standard_EXPORT double ComputeValue() const override;

  Standard_EXPORT void Compute(
    const occ::handle<PrsMgr_PresentationManager>& thePresentationManager,
    const occ::handle<Prs3d_Presentation>&         thePresentation,
    const int                                      theMode = 0) override;

  Standard_EXPORT void ComputeFlyoutLinePoints(const gp_Pnt& theFirstPoint,
                                               const gp_Pnt& theSecondPoint,
                                               gp_Pnt&       theLineBegPoint,
                                               gp_Pnt&       theLineEndPoint) override;

  Standard_EXPORT void ComputeFlyoutSelection(
    const occ::handle<SelectMgr_Selection>&   theSelection,
    const occ::handle<SelectMgr_EntityOwner>& theEntityOwner) override;

protected:
  Standard_EXPORT bool IsValidPoints(const gp_Pnt& theFirstPoint,
                                     const gp_Pnt& theSecondPoint) const;

  Standard_EXPORT bool InitTwoEdgesLength(const TopoDS_Edge& theFirstEdge,
                                          const TopoDS_Edge& theSecondEdge,
                                          gp_Dir&            theEdgeDir);

  Standard_EXPORT bool InitEdgeVertexLength(const TopoDS_Edge&   theEdge,
                                            const TopoDS_Vertex& theVertex,
                                            gp_Dir&              theEdgeDir,
                                            bool                 isInfinite);

  Standard_EXPORT bool InitEdgeFaceLength(const TopoDS_Edge& theEdge,
                                          const TopoDS_Face& theFace,
                                          gp_Dir&            theEdgeDir);

  Standard_EXPORT bool InitTwoShapesPoints(const TopoDS_Shape& theFirstShape,
                                           const TopoDS_Shape& theSecondShape,
                                           gp_Pln&             theComputedPlane,
                                           bool&               theIsPlaneComputed);

  Standard_EXPORT bool InitOneShapePoints(const TopoDS_Shape& theShape);

protected:
  gp_Pnt       myFirstPoint;
  gp_Pnt       mySecondPoint;
  TopoDS_Shape myFirstShape;
  TopoDS_Shape mySecondShape;
  gp_Dir       myDirection;
  bool         myHasCustomDirection;
};
