#pragma once


#include <PrsDim_Relation.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <gp_Dir.hpp>

//! A framework to define display of 3D chamfers.
//! A chamfer is displayed with arrows and text. The text
//! gives the length of the chamfer if it is a symmetrical
//! chamfer, or the angle if it is not.
class PrsDim_Chamf3dDimension : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_Chamf3dDimension, PrsDim_Relation)
public:
  //! Constructs a display object for 3D chamfers.
  //! This object is defined by the shape aFShape, the
  //! dimension aVal and the text aText.
  Standard_EXPORT PrsDim_Chamf3dDimension(const TopoDS_Shape&               aFShape,
                                          const double                      aVal,
                                          const TCollection_ExtendedString& aText);

  //! Constructs a display object for 3D chamfers.
  //! This object is defined by the shape aFShape, the
  //! dimension aVal, the text aText, the point of origin of
  //! the chamfer aPosition, the type of arrow aSymbolPrs
  //! with the size anArrowSize.
  Standard_EXPORT PrsDim_Chamf3dDimension(const TopoDS_Shape&               aFShape,
                                          const double                      aVal,
                                          const TCollection_ExtendedString& aText,
                                          const gp_Pnt&                     aPosition,
                                          const DsgPrs_ArrowSide            aSymbolPrs,
                                          const double                      anArrowSize = 0.0);

  //! Indicates that we are concerned with a 3d length.
  PrsDim_KindOfDimension KindOfDimension() const override { return PrsDim_KOD_LENGTH; }

  //! Returns true if the 3d chamfer dimension is movable.
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

