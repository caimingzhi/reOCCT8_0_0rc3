#pragma once


#include <PrsDim_EllipseRadiusDimension.hpp>
#include <DsgPrs_ArrowSide.hpp>

//! Ellipse Max radius dimension of a Shape which can be Edge
//! or Face (planar or cylindrical(surface of extrusion or
//! surface of offset))
class PrsDim_MaxRadiusDimension : public PrsDim_EllipseRadiusDimension
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_MaxRadiusDimension, PrsDim_EllipseRadiusDimension)
public:
  //! Max Ellipse radius dimension
  //! Shape can be edge, planar face or cylindrical face
  Standard_EXPORT PrsDim_MaxRadiusDimension(const TopoDS_Shape&               aShape,
                                            const double                      aVal,
                                            const TCollection_ExtendedString& aText);

  //! Max Ellipse radius dimension with position
  //! Shape can be edge, planar face or cylindrical face
  Standard_EXPORT PrsDim_MaxRadiusDimension(const TopoDS_Shape&               aShape,
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

