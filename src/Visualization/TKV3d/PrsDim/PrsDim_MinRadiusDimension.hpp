#pragma once

#include <PrsDim_EllipseRadiusDimension.hpp>
#include <DsgPrs_ArrowSide.hpp>

class PrsDim_MinRadiusDimension : public PrsDim_EllipseRadiusDimension
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_MinRadiusDimension, PrsDim_EllipseRadiusDimension)
public:
  Standard_EXPORT PrsDim_MinRadiusDimension(const TopoDS_Shape&               aShape,
                                            const double                      aVal,
                                            const TCollection_ExtendedString& aText);

  Standard_EXPORT PrsDim_MinRadiusDimension(const TopoDS_Shape&               aShape,
                                            const double                      aVal,
                                            const TCollection_ExtendedString& aText,
                                            const gp_Pnt&                     aPosition,
                                            const DsgPrs_ArrowSide            aSymbolPrs,
                                            const double                      anArrowSize = 0.0);

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeEllipse(const occ::handle<Prs3d_Presentation>& aPresentation);

  Standard_EXPORT void ComputeArcOfEllipse(const occ::handle<Prs3d_Presentation>& aPresentation);

private:
  gp_Pnt myApexP;
  gp_Pnt myApexN;
  gp_Pnt myEndOfArrow;
};
