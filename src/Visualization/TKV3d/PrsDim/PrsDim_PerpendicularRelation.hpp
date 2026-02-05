#pragma once

#include <PrsDim_Relation.hpp>

//! A framework to display constraints of perpendicularity
//! between two or more interactive datums. These
//! datums can be edges or faces.
class PrsDim_PerpendicularRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_PerpendicularRelation, PrsDim_Relation)
public:
  //! Constructs an object to display constraints of
  //! perpendicularity on shapes.
  //! This object is defined by a first shape aFShape, a
  //! second shape aSShape, and a plane aPlane.
  //! aPlane is the plane of reference to show and test the
  //! perpendicular relation between two shapes, at least
  //! one of which has a revolved surface.
  Standard_EXPORT PrsDim_PerpendicularRelation(const TopoDS_Shape&            aFShape,
                                               const TopoDS_Shape&            aSShape,
                                               const occ::handle<Geom_Plane>& aPlane);

  //! Constructs an object to display constraints of
  //! perpendicularity on shapes.
  //! This object is defined by a first shape aFShape and a
  //! second shape aSShape.
  Standard_EXPORT PrsDim_PerpendicularRelation(const TopoDS_Shape& aFShape,
                                               const TopoDS_Shape& aSShape);

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeTwoFacesPerpendicular(
    const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeTwoEdgesPerpendicular(
    const occ::handle<Prs3d_Presentation>& aPresentation);

private:
  gp_Pnt myFAttach;
  gp_Pnt mySAttach;
};
