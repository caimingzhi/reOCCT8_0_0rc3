#pragma once


#include <PrsDim_Relation.hpp>
#include <DsgPrs_ArrowSide.hpp>

//! A framework to display constraints of parallelism
//! between two or more Interactive Objects. These
//! entities can be faces or edges.
class PrsDim_ParallelRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_ParallelRelation, PrsDim_Relation)
public:
  //! Constructs an object to display parallel constraints.
  //! This object is defined by the first shape aFShape and
  //! the second shape aSShape and the plane aPlane.
  Standard_EXPORT PrsDim_ParallelRelation(const TopoDS_Shape&            aFShape,
                                          const TopoDS_Shape&            aSShape,
                                          const occ::handle<Geom_Plane>& aPlane);

  //! Constructs an object to display parallel constraints.
  //! This object is defined by the first shape aFShape and
  //! the second shape aSShape the plane aPlane, the
  //! position aPosition, the type of arrow, aSymbolPrs and
  //! its size anArrowSize.
  Standard_EXPORT PrsDim_ParallelRelation(const TopoDS_Shape&            aFShape,
                                          const TopoDS_Shape&            aSShape,
                                          const occ::handle<Geom_Plane>& aPlane,
                                          const gp_Pnt&                  aPosition,
                                          const DsgPrs_ArrowSide         aSymbolPrs,
                                          const double                   anArrowSize = 0.01);

  //! Returns true if the parallelism is movable.
  bool IsMovable() const override { return true; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeTwoFacesParallel(
    const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeTwoEdgesParallel(
    const occ::handle<Prs3d_Presentation>& aPresentation);

private:
  gp_Pnt myFAttach;
  gp_Pnt mySAttach;
  gp_Dir myDirAttach;
};

