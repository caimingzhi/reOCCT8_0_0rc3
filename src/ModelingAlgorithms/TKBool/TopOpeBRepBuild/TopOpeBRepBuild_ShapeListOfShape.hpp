#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class TopOpeBRepBuild_ShapeListOfShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_ShapeListOfShape();

  Standard_EXPORT TopOpeBRepBuild_ShapeListOfShape(const TopoDS_Shape& S);

  Standard_EXPORT TopOpeBRepBuild_ShapeListOfShape(const TopoDS_Shape&                   S,
                                                   const NCollection_List<TopoDS_Shape>& L);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& List() const;

  Standard_EXPORT NCollection_List<TopoDS_Shape>& ChangeList();

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT TopoDS_Shape& ChangeShape();

private:
  NCollection_List<TopoDS_Shape> myList;
  TopoDS_Shape                   myShape;
};
