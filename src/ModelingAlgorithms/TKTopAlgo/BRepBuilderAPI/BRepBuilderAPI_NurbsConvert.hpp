#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepBuilderAPI_ModifyShape.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepTools_ReShape.hpp>

class TopoDS_Shape;

class BRepBuilderAPI_NurbsConvert : public BRepBuilderAPI_ModifyShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_NurbsConvert();

  Standard_EXPORT BRepBuilderAPI_NurbsConvert(const TopoDS_Shape& S, const bool Copy = false);

  Standard_EXPORT void Perform(const TopoDS_Shape& S, const bool Copy = false);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& S) const override;

private:
  Standard_EXPORT void CorrectVertexTol();

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVtxToReplace;
  BRepTools_ReShape                                                        mySubs;
};
