#pragma once

#include <gp_Circ.hpp>
#include <TopoDS_Wire.hpp>
#include <PrsDim_Relation.hpp>

class Geom_Plane;

class PrsDim_FixRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_FixRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane,
                                     const TopoDS_Wire&             aWire);

  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane,
                                     const TopoDS_Wire&             aWire,
                                     const gp_Pnt&                  aPosition,
                                     const double                   anArrowSize = 0.01);

  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane);

  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane,
                                     const gp_Pnt&                  aPosition,
                                     const double                   anArrowSize = 0.01);

  const TopoDS_Wire& Wire() { return myWire; }

  void SetWire(const TopoDS_Wire& aWire) { myWire = aWire; }

  bool IsMovable() const override { return true; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeVertex(const TopoDS_Vertex& FixVertex, gp_Pnt& curpos);

  Standard_EXPORT gp_Pnt ComputePosition(const occ::handle<Geom_Curve>& curv1,
                                         const occ::handle<Geom_Curve>& curv2,
                                         const gp_Pnt&                  firstp1,
                                         const gp_Pnt&                  lastp1,
                                         const gp_Pnt&                  firstp2,
                                         const gp_Pnt&                  lastp2) const;

  Standard_EXPORT gp_Pnt ComputePosition(const occ::handle<Geom_Curve>& curv,
                                         const gp_Pnt&                  firstp,
                                         const gp_Pnt&                  lastp) const;

  Standard_EXPORT void ComputeEdge(const TopoDS_Edge& FixEdge, gp_Pnt& curpos);

  Standard_EXPORT void ComputeLinePosition(const gp_Lin& glin,
                                           gp_Pnt&       pos,
                                           double&       pfirst,
                                           double&       plast);

  Standard_EXPORT void ComputeCirclePosition(const gp_Circ& gcirc,
                                             gp_Pnt&        pos,
                                             double&        pfirst,
                                             double&        plast);

  Standard_EXPORT static bool ConnectedEdges(const TopoDS_Wire&   aWire,
                                             const TopoDS_Vertex& aVertex,
                                             TopoDS_Edge&         Edge1,
                                             TopoDS_Edge&         Edge2);

private:
  TopoDS_Wire myWire;
  gp_Pnt      myPntAttach;
};
