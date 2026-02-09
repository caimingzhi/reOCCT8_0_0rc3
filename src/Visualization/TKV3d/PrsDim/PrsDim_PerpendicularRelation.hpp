#pragma once

#include <PrsDim_Relation.hpp>

class PrsDim_PerpendicularRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_PerpendicularRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_PerpendicularRelation(const TopoDS_Shape&            aFShape,
                                               const TopoDS_Shape&            aSShape,
                                               const occ::handle<Geom_Plane>& aPlane);

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
