#pragma once

#include <PrsDim_Relation.hpp>
#include <PrsDim_KindOfDimension.hpp>

//! A framework to display dimensions of offsets.
//! The relation between the offset and the basis shape
//! is indicated. This relation is displayed with arrows and
//! text. The text gives the dsitance between the offset
//! and the basis shape.
class PrsDim_OffsetDimension : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_OffsetDimension, PrsDim_Relation)
public:
  //! Constructs the offset display object defined by the
  //! first shape aFShape, the second shape aSShape, the
  //! dimension aVal, and the text aText.
  Standard_EXPORT PrsDim_OffsetDimension(const TopoDS_Shape&               FistShape,
                                         const TopoDS_Shape&               SecondShape,
                                         const double                      aVal,
                                         const TCollection_ExtendedString& aText);

  //! Indicates that the dimension we are concerned with is an offset.
  PrsDim_KindOfDimension KindOfDimension() const override { return PrsDim_KOD_OFFSET; }

  //! Returns true if the offset datum is movable.
  bool IsMovable() const override { return true; }

  //! Sets a transformation aTrsf for presentation and
  //! selection to a relative position.
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
