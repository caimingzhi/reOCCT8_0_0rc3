#pragma once

#include <PrsDim_Relation.hpp>

class Geom_Plane;

class PrsDim_EqualRadiusRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_EqualRadiusRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_EqualRadiusRelation(const TopoDS_Edge&             aFirstEdge,
                                             const TopoDS_Edge&             aSecondEdge,
                                             const occ::handle<Geom_Plane>& aPlane);

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeRadiusPosition();

private:
  gp_Pnt myFirstCenter;
  gp_Pnt mySecondCenter;
  gp_Pnt myFirstPoint;
  gp_Pnt mySecondPoint;
};
