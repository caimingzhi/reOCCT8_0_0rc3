#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepLib_Command.hpp>
#include <BRepLib_ShapeModification.hpp>
class TopoDS_Face;
class TopoDS_Edge;

class BRepLib_MakeShape : public BRepLib_Command
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void Build();

  Standard_EXPORT const TopoDS_Shape& Shape();
  Standard_EXPORT                     operator TopoDS_Shape();

  Standard_EXPORT virtual BRepLib_ShapeModification FaceStatus(const TopoDS_Face& F) const;

  Standard_EXPORT virtual bool HasDescendants(const TopoDS_Face& F) const;

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& DescendantFaces(
    const TopoDS_Face& F);

  Standard_EXPORT virtual int NbSurfaces() const;

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& NewFaces(const int I);

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& FacesFromEdges(
    const TopoDS_Edge& E);

protected:
  Standard_EXPORT BRepLib_MakeShape();

  TopoDS_Shape                   myShape;
  NCollection_List<TopoDS_Shape> myGenFaces;
  NCollection_List<TopoDS_Shape> myNewFaces;
  NCollection_List<TopoDS_Shape> myEdgFaces;
};
