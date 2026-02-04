#pragma once


#include <gp_Circ.hpp>
#include <TopoDS_Wire.hpp>
#include <PrsDim_Relation.hpp>

class Geom_Plane;

//! Constructs and manages a constraint by a fixed
//! relation between two or more interactive datums. This
//! constraint is represented by a wire from a shape -
//! point, vertex, or edge - in the first datum and a
//! corresponding shape in the second.
//! Warning: This relation is not bound with any kind of parametric
//! constraint : it represents the "status" of an parametric
//! object.
class PrsDim_FixRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_FixRelation, PrsDim_Relation)
public:
  //! initializes the vertex aShape, the
  //! plane aPlane and the wire aWire, which connects
  //! the two vertices in a fixed relation.
  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane,
                                     const TopoDS_Wire&             aWire);

  //! initializes the vertex aShape, the
  //! plane aPlane and the wire aWire, the position
  //! aPosition, the arrow size anArrowSize and the
  //! wire aWire, which connects the two vertices in a fixed relation.
  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane,
                                     const TopoDS_Wire&             aWire,
                                     const gp_Pnt&                  aPosition,
                                     const double                   anArrowSize = 0.01);

  //! initializes the edge aShape and the plane aPlane.
  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane);

  //! initializes the edge aShape, the
  //! plane aPlane, the position aPosition and the arrow
  //! size anArrowSize.
  Standard_EXPORT PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                     const occ::handle<Geom_Plane>& aPlane,
                                     const gp_Pnt&                  aPosition,
                                     const double                   anArrowSize = 0.01);

  //! Returns the wire which connects vertices in a fixed relation.
  const TopoDS_Wire& Wire() { return myWire; }

  //! Constructs the wire aWire. This connects vertices
  //! which are in a fixed relation.
  void SetWire(const TopoDS_Wire& aWire) { myWire = aWire; }

  //! Returns true if the Interactive Objects in the relation
  //! are movable.
  bool IsMovable() const override { return true; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  //! computes the presentation for <myFixShape> if it's a vertex.
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

  //! computes the presentation for <myFixShape> if it's a
  //! edge.
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

