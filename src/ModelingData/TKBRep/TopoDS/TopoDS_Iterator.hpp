#pragma once


#include <Standard_NoSuchObject.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopLoc_Location.hpp>
class TopoDS_Shape;

//! Iterates on the underlying shape underlying a given
//! TopoDS_Shape object, providing access to its
//! component sub-shapes. Each component shape is
//! returned as a TopoDS_Shape with an orientation,
//! and a compound of the original values and the relative values.
class TopoDS_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty Iterator.
  TopoDS_Iterator()
      : myOrientation(TopAbs_FORWARD)
  {
  }

  //! Creates an Iterator on <S> sub-shapes.
  //! Note:
  //! - If cumOri is true, the function composes all
  //! sub-shapes with the orientation of S.
  //! - If cumLoc is true, the function multiplies all
  //! sub-shapes by the location of S, i.e. it applies to
  //! each sub-shape the transformation that is associated with S.
  TopoDS_Iterator(const TopoDS_Shape& S, const bool cumOri = true, const bool cumLoc = true)
  {
    Initialize(S, cumOri, cumLoc);
  }

  //! Initializes this iterator with shape S.
  //! Note:
  //! - If cumOri is true, the function composes all
  //! sub-shapes with the orientation of S.
  //! - If cumLoc is true, the function multiplies all
  //! sub-shapes by the location of S, i.e. it applies to
  //! each sub-shape the transformation that is associated with S.
  Standard_EXPORT void Initialize(const TopoDS_Shape& S,
                                  const bool          cumOri = true,
                                  const bool          cumLoc = true);

  //! Returns true if there is another sub-shape in the
  //! shape which this iterator is scanning.
  bool More() const { return myShapes.More(); }

  //! Moves on to the next sub-shape in the shape which
  //! this iterator is scanning.
  //! Exceptions
  //! Standard_NoMoreObject if there are no more sub-shapes in the shape.
  Standard_EXPORT void Next();

  //! Returns the current sub-shape in the shape which
  //! this iterator is scanning.
  //! Exceptions
  //! Standard_NoSuchObject if there is no current sub-shape.
  const TopoDS_Shape& Value() const
  {
    Standard_NoSuchObject_Raise_if(!More(), "TopoDS_Iterator::Value");
    return myShape;
  }

private:
  TopoDS_Shape                             myShape;
  NCollection_List<TopoDS_Shape>::Iterator myShapes;
  TopAbs_Orientation                       myOrientation;
  TopLoc_Location                          myLocation;
};

