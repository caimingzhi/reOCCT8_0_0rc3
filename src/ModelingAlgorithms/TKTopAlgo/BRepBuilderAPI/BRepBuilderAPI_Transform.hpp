#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
#include <BRepBuilderAPI_ModifyShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;

class BRepBuilderAPI_Transform : public BRepBuilderAPI_ModifyShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_Transform(const gp_Trsf& T);

  Standard_EXPORT BRepBuilderAPI_Transform(const TopoDS_Shape& theShape,
                                           const gp_Trsf&      theTrsf,
                                           const bool          theCopyGeom = false,
                                           const bool          theCopyMesh = false);

  Standard_EXPORT void Perform(const TopoDS_Shape& theShape,
                               const bool          theCopyGeom = false,
                               const bool          theCopyMesh = false);

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& S) const override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

private:
  gp_Trsf         myTrsf;
  TopLoc_Location myLocation;
  bool            myUseModif;
};
