#pragma once

#include <PrsDim_Relation.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <gp_Dir.hpp>

class PrsDim_Chamf3dDimension : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_Chamf3dDimension, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_Chamf3dDimension(const TopoDS_Shape&               aFShape,
                                          const double                      aVal,
                                          const TCollection_ExtendedString& aText);

  Standard_EXPORT PrsDim_Chamf3dDimension(const TopoDS_Shape&               aFShape,
                                          const double                      aVal,
                                          const TCollection_ExtendedString& aText,
                                          const gp_Pnt&                     aPosition,
                                          const DsgPrs_ArrowSide            aSymbolPrs,
                                          const double                      anArrowSize = 0.0);

  PrsDim_KindOfDimension KindOfDimension() const override { return PrsDim_KOD_LENGTH; }

  bool IsMovable() const override { return true; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

private:
  gp_Pnt myPntAttach;
  gp_Dir myDir;
};
