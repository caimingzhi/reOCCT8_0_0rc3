#pragma once

#include <PrsDim_Relation.hpp>
#include <gp_Dir.hpp>

class Geom_Plane;

class PrsDim_ConcentricRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_ConcentricRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_ConcentricRelation(const TopoDS_Shape&            aFShape,
                                            const TopoDS_Shape&            aSShape,
                                            const occ::handle<Geom_Plane>& aPlane);

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeTwoEdgesConcentric(const occ::handle<Prs3d_Presentation>& thePrsMgr);

  Standard_EXPORT void ComputeEdgeVertexConcentric(
    const occ::handle<Prs3d_Presentation>& thePrsMgr);

  Standard_EXPORT void ComputeTwoVerticesConcentric(
    const occ::handle<Prs3d_Presentation>& thePrsMgr);

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

private:
  gp_Pnt myCenter;
  double myRad;
  gp_Dir myDir;
  gp_Pnt myPnt;
};
