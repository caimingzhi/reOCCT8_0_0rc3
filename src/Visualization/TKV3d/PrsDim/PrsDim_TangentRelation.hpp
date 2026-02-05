#pragma once

#include <PrsDim_Relation.hpp>

//! A framework to display tangency constraints between
//! two or more Interactive Objects of the datum type.
//! The datums are normally faces or edges.
class PrsDim_TangentRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_TangentRelation, PrsDim_Relation)
public:
  //! TwoFacesTangent or TwoEdgesTangent relation
  //! Constructs an object to display tangency constraints.
  //! This object is defined by the first shape aFShape, the
  //! second shape aSShape, the plane aPlane and the index anExternRef.
  //! aPlane serves as an optional axis.
  //! anExternRef set to 0 indicates that there is no relation.
  Standard_EXPORT PrsDim_TangentRelation(const TopoDS_Shape&            aFShape,
                                         const TopoDS_Shape&            aSShape,
                                         const occ::handle<Geom_Plane>& aPlane,
                                         const int                      anExternRef = 0);

  //! Returns the external reference for tangency.
  //! The values are as follows:
  //! -   0 - there is no connection;
  //! -   1 - there is a connection to the first shape;
  //! -   2 - there is a connection to the second shape.
  //! This reference is defined at construction time.
  int ExternRef() { return myExternRef; }

  //! Sets the external reference for tangency, aRef.
  //! The values are as follows:
  //! -   0 - there is no connection;
  //! -   1 - there is a connection to the first shape;
  //! -   2 - there is a connection to the second shape.
  //! This reference is initially defined at construction time.
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
