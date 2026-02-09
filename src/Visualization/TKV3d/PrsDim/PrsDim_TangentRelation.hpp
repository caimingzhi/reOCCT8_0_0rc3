#pragma once

#include <PrsDim_Relation.hpp>

class PrsDim_TangentRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_TangentRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_TangentRelation(const TopoDS_Shape&            aFShape,
                                         const TopoDS_Shape&            aSShape,
                                         const occ::handle<Geom_Plane>& aPlane,
                                         const int                      anExternRef = 0);

  int ExternRef() { return myExternRef; }

  void SetExternRef(const int aRef) { myExternRef = aRef; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeTwoFacesTangent(const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeTwoEdgesTangent(const occ::handle<Prs3d_Presentation>& aPresentation);

private:
  gp_Pnt myAttach;
  gp_Dir myDir;
  double myLength;
  int    myExternRef;
};
