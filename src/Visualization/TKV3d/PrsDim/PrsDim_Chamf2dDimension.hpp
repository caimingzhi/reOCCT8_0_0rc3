#pragma once

#include <PrsDim_Relation.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <gp_Dir.hpp>

class Geom_Plane;

//! A framework to define display of 2D chamfers.
//! A chamfer is displayed with arrows and text. The text
//! gives the length of the chamfer if it is a symmetrical
//! chamfer, or the angle if it is not.
class PrsDim_Chamf2dDimension : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_Chamf2dDimension, PrsDim_Relation)
public:
  //! Constructs the display object for 2D chamfers.
  //! This object is defined by the face aFShape, the
  //! dimension aVal, the plane aPlane and the text aText.
  Standard_EXPORT PrsDim_Chamf2dDimension(const TopoDS_Shape&               aFShape,
                                          const occ::handle<Geom_Plane>&    aPlane,
                                          const double                      aVal,
                                          const TCollection_ExtendedString& aText);

  //! Constructs the display object for 2D chamfers.
  //! This object is defined by the face aFShape, the plane
  //! aPlane, the dimension aVal, the position aPosition,
  //! the type of arrow aSymbolPrs with the size
  //! anArrowSize, and the text aText.
  Standard_EXPORT PrsDim_Chamf2dDimension(const TopoDS_Shape&               aFShape,
                                          const occ::handle<Geom_Plane>&    aPlane,
                                          const double                      aVal,
                                          const TCollection_ExtendedString& aText,
                                          const gp_Pnt&                     aPosition,
                                          const DsgPrs_ArrowSide            aSymbolPrs,
                                          const double                      anArrowSize = 0.0);

  //! Indicates that we are concerned with a 2d length.
  PrsDim_KindOfDimension KindOfDimension() const override { return PrsDim_KOD_LENGTH; }

  //! Returns true if the 2d chamfer dimension is movable.
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
