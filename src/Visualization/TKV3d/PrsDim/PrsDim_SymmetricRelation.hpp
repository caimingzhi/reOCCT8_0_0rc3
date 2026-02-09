#pragma once

#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <PrsDim_Relation.hpp>

class PrsDim_SymmetricRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_SymmetricRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_SymmetricRelation(const TopoDS_Shape&            aSymmTool,
                                           const TopoDS_Shape&            FirstShape,
                                           const TopoDS_Shape&            SecondShape,
                                           const occ::handle<Geom_Plane>& aPlane);

  bool IsMovable() const override { return true; }

  void SetTool(const TopoDS_Shape& aSymmetricTool) { myTool = aSymmetricTool; }

  const TopoDS_Shape& GetTool() const { return myTool; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeTwoFacesSymmetric(const occ::handle<Prs3d_Presentation>& aprs);

  Standard_EXPORT void ComputeTwoEdgesSymmetric(const occ::handle<Prs3d_Presentation>& aprs);

  Standard_EXPORT void ComputeTwoVerticesSymmetric(const occ::handle<Prs3d_Presentation>& aprs);

private:
  TopoDS_Shape myTool;
  gp_Pnt       myFAttach;
  gp_Pnt       mySAttach;
  gp_Dir       myFDirAttach;
  gp_Dir       myAxisDirAttach;
};
