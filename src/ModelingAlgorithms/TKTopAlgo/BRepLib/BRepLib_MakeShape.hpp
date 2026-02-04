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

//! This is the root class for all shape
//! constructions. It stores the result.
//!
//! It provides deferred methods to trace the history
//! of sub-shapes.
class BRepLib_MakeShape : public BRepLib_Command
{
public:
  DEFINE_STANDARD_ALLOC

  //! This is called by Shape(). It does nothing but
  //! may be redefined.
  Standard_EXPORT void Build();

  Standard_EXPORT const TopoDS_Shape& Shape();
  Standard_EXPORT                     operator TopoDS_Shape();

  //! returns the status of the Face after
  //! the shape creation.
  Standard_EXPORT virtual BRepLib_ShapeModification FaceStatus(const TopoDS_Face& F) const;

  //! Returns True if the Face generates new topology.
  Standard_EXPORT virtual bool HasDescendants(const TopoDS_Face& F) const;

  //! returns the list of generated Faces.
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& DescendantFaces(
    const TopoDS_Face& F);

  //! returns the number of surfaces
  //! after the shape creation.
  Standard_EXPORT virtual int NbSurfaces() const;

  //! Return the faces created for surface I.
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& NewFaces(const int I);

  //! returns a list of the created faces
  //! from the edge <E>.
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& FacesFromEdges(
    const TopoDS_Edge& E);

protected:
  Standard_EXPORT BRepLib_MakeShape();

  TopoDS_Shape                   myShape;
  NCollection_List<TopoDS_Shape> myGenFaces;
  NCollection_List<TopoDS_Shape> myNewFaces;
  NCollection_List<TopoDS_Shape> myEdgFaces;
};

