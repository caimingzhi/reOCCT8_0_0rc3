#pragma once

#include <PrsDim_Relation.hpp>

enum PrsDim_TypeOfDist
{
  PrsDim_TypeOfDist_Unknown,
  PrsDim_TypeOfDist_Horizontal,
  PrsDim_TypeOfDist_Vertical
};

#include <DsgPrs_ArrowSide.hpp>

class Geom_Plane;

class PrsDim_EqualDistanceRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_EqualDistanceRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_EqualDistanceRelation(const TopoDS_Shape&            aShape1,
                                               const TopoDS_Shape&            aShape2,
                                               const TopoDS_Shape&            aShape3,
                                               const TopoDS_Shape&            aShape4,
                                               const occ::handle<Geom_Plane>& aPlane);

  void SetShape3(const TopoDS_Shape& aShape) { myShape3 = aShape; }

  const TopoDS_Shape& Shape3() const { return myShape3; }

  void SetShape4(const TopoDS_Shape& aShape) { myShape4 = aShape; }

  const TopoDS_Shape& Shape4() const { return myShape4; }

public:
  Standard_EXPORT static void ComputeTwoEdgesLength(
    const occ::handle<Prs3d_Presentation>& aPresentation,
    const occ::handle<Prs3d_Drawer>&       aDrawer,
    const double                           ArrowSize,
    const TopoDS_Edge&                     FirstEdge,
    const TopoDS_Edge&                     SecondEdge,
    const occ::handle<Geom_Plane>&         Plane,
    const bool                             AutomaticPos,
    const bool                             IsSetBndBox,
    const Bnd_Box&                         BndBox,
    gp_Pnt&                                Position,
    gp_Pnt&                                FirstAttach,
    gp_Pnt&                                SecondAttach,
    gp_Pnt&                                FirstExtreme,
    gp_Pnt&                                SecondExtreme,
    DsgPrs_ArrowSide&                      SymbolPrs);

  Standard_EXPORT static void ComputeTwoVerticesLength(
    const occ::handle<Prs3d_Presentation>& aPresentation,
    const occ::handle<Prs3d_Drawer>&       aDrawer,
    const double                           ArrowSize,
    const TopoDS_Vertex&                   FirstVertex,
    const TopoDS_Vertex&                   SecondVertex,
    const occ::handle<Geom_Plane>&         Plane,
    const bool                             AutomaticPos,
    const bool                             IsSetBndBox,
    const Bnd_Box&                         BndBox,
    const PrsDim_TypeOfDist                TypeDist,
    gp_Pnt&                                Position,
    gp_Pnt&                                FirstAttach,
    gp_Pnt&                                SecondAttach,
    gp_Pnt&                                FirstExtreme,
    gp_Pnt&                                SecondExtreme,
    DsgPrs_ArrowSide&                      SymbolPrs);

  Standard_EXPORT static void ComputeOneEdgeOneVertexLength(
    const occ::handle<Prs3d_Presentation>& aPresentation,
    const occ::handle<Prs3d_Drawer>&       aDrawer,
    const double                           ArrowSize,
    const TopoDS_Shape&                    FirstShape,
    const TopoDS_Shape&                    SecondShape,
    const occ::handle<Geom_Plane>&         Plane,
    const bool                             AutomaticPos,
    const bool                             IsSetBndBox,
    const Bnd_Box&                         BndBox,
    gp_Pnt&                                Position,
    gp_Pnt&                                FirstAttach,
    gp_Pnt&                                SecondAttach,
    gp_Pnt&                                FirstExtreme,
    gp_Pnt&                                SecondExtreme,
    DsgPrs_ArrowSide&                      SymbolPrs);

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

private:
  TopoDS_Shape myShape3;
  TopoDS_Shape myShape4;
  gp_Pnt       myAttachPoint1;
  gp_Pnt       myAttachPoint2;
  gp_Pnt       myAttachPoint3;
  gp_Pnt       myAttachPoint4;
  gp_Pnt       myPoint1;
  gp_Pnt       myPoint2;
  gp_Pnt       myPoint3;
  gp_Pnt       myPoint4;
};
