#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;
class TopoDS_Face;

//! This class builds faces from a set of wires SW and a face F.
//! The face must have and underlying surface, say S.
//! All of the edges of all of the wires must have a 2d representation
//! on surface S (except if S is planar)
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

