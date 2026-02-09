#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_GTrsf.hpp>
#include <BRepBuilderAPI_Collect.hpp>
#include <BRepBuilderAPI_ModifyShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;

class BRepBuilderAPI_GTransform : public BRepBuilderAPI_ModifyShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_GTransform(const gp_GTrsf& T);

  Standard_EXPORT BRepBuilderAPI_GTransform(const TopoDS_Shape& S,
                                            const gp_GTrsf&     T,
                                            const bool          Copy = false);

  Standard_EXPORT void Perform(const TopoDS_Shape& S, const bool Copy = false);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& S) const override;

private:
  gp_GTrsf               myGTrsf;
  BRepBuilderAPI_Collect myHist;
};
