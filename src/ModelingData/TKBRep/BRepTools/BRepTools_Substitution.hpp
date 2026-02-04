#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;

//! A tool to substitute subshapes by other shapes.
//!
//! The user use the method Substitute to define the
//! modifications.
//! A set of shapes is designated to replace a initial
//! shape.
//!
//! The method Build reconstructs a new Shape with the
//! modifications.The Shape and the new shape are
//! registered.
class BRepTools_Substitution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTools_Substitution();

  //! Reset all the fields.
  Standard_EXPORT void Clear();

  //! <Oldshape> will be replaced by <NewShapes>.
  //!
  //! <NewShapes> can be empty, in this case <OldShape>
  //! will disparate from its ancestors.
  //!
  //! if an item of <NewShapes> is oriented FORWARD.
  //! it will be oriented as <OldShape> in its ancestors.
  //! else it will be reversed.
  Standard_EXPORT void Substitute(const TopoDS_Shape&                   OldShape,
                                  const NCollection_List<TopoDS_Shape>& NewShapes);

  //! Build NewShape from <S> if its subshapes has modified.
  //!
  //! The methods <IsCopied> and <Copy> allows you to keep
  //! the resul of <Build>
  Standard_EXPORT void Build(const TopoDS_Shape& S);

  //! Returns True if <S> has been replaced.
  Standard_EXPORT bool IsCopied(const TopoDS_Shape& S) const;

  //! Returns the set of shapes substituted to <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Copy(const TopoDS_Shape& S) const;

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};

