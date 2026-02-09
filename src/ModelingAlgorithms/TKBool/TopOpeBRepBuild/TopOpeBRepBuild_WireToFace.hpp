#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;
class TopoDS_Face;

class TopOpeBRepBuild_WireToFace
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_WireToFace();

  Standard_EXPORT void Init();

  Standard_EXPORT void AddWire(const TopoDS_Wire& W);

  Standard_EXPORT void MakeFaces(const TopoDS_Face& F, NCollection_List<TopoDS_Shape>& LF);

private:
  NCollection_List<TopoDS_Shape> myLW;
};
