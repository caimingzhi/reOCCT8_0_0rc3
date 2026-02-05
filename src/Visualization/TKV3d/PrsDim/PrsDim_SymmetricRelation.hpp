#pragma once

#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <PrsDim_Relation.hpp>

//! A framework to display constraints of symmetricity
//! between two or more datum Interactive Objects.
//! A plane serves as the axis of symmetry between the
//! shapes of which the datums are parts.
class PrsDim_SymmetricRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_SymmetricRelation, PrsDim_Relation)
public:
  //! Constructs an object to display constraints of symmetricity.
  //! This object is defined by a tool aSymmTool, a first
  //! shape FirstShape, a second shape SecondShape, and a plane aPlane.
  //! aPlane serves as the axis of symmetry.
  //! aSymmTool is the shape composed of FirstShape
  //! SecondShape and aPlane. It may be queried and
  //! edited using the functions GetTool and SetTool.
  //! The two shapes are typically two edges, two vertices or two points.
  Standard_EXPORT PrsDim_SymmetricRelation(const TopoDS_Shape&            aSymmTool,
                                           const TopoDS_Shape&            FirstShape,
                                           const TopoDS_Shape&            SecondShape,
                                           const occ::handle<Geom_Plane>& aPlane);

  //! Returns true if the symmetric constraint display is movable.
  bool IsMovable() const override { return true; }

  //! Sets the tool aSymmetricTool composed of a first
  //! shape, a second shape, and a plane.
  //! This tool is initially created at construction time.
  void SetTool(const TopoDS_Shape& aSymmetricTool) { myTool = aSymmetricTool; }

  //! Returns the tool composed of a first shape, a second
  //! shape, and a plane. This tool is created at construction time.
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
