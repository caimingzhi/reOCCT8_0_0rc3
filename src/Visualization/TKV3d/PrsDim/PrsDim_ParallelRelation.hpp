#pragma once

#include <PrsDim_Relation.hpp>
#include <DsgPrs_ArrowSide.hpp>

class PrsDim_ParallelRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_ParallelRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_ParallelRelation(const TopoDS_Shape&            aFShape,
                                          const TopoDS_Shape&            aSShape,
                                          const occ::handle<Geom_Plane>& aPlane);

  Standard_EXPORT PrsDim_ParallelRelation(const TopoDS_Shape&            aFShape,
                                          const TopoDS_Shape&            aSShape,
                                          const occ::handle<Geom_Plane>& aPlane,
                                          const gp_Pnt&                  aPosition,
                                          const DsgPrs_ArrowSide         aSymbolPrs,
                                          const double                   anArrowSize = 0.01);

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
