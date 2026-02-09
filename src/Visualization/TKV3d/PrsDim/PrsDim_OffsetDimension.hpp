#pragma once

#include <PrsDim_Relation.hpp>
#include <PrsDim_KindOfDimension.hpp>

class PrsDim_OffsetDimension : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_OffsetDimension, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_OffsetDimension(const TopoDS_Shape&               FistShape,
                                         const TopoDS_Shape&               SecondShape,
                                         const double                      aVal,
                                         const TCollection_ExtendedString& aText);

  PrsDim_KindOfDimension KindOfDimension() const override { return PrsDim_KOD_OFFSET; }

  bool IsMovable() const override { return true; }

  void SetRelativePos(const gp_Trsf& aTrsf) { myRelativePos = aTrsf; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeTwoFacesOffset(const occ::handle<Prs3d_Presentation>& aPresentation,
                                             const gp_Trsf&                         aTrsf);

  Standard_EXPORT void ComputeTwoAxesOffset(const occ::handle<Prs3d_Presentation>& aPresentation,
                                            const gp_Trsf&                         aTrsf);

  Standard_EXPORT void ComputeAxeFaceOffset(const occ::handle<Prs3d_Presentation>& aPresentation,
                                            const gp_Trsf&                         aTrsf);

private:
  gp_Pnt  myFAttach;
  gp_Pnt  mySAttach;
  gp_Dir  myDirAttach;
  gp_Dir  myDirAttach2;
  gp_Trsf myRelativePos;
};
