#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Iterator.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;

//! This class provides iteration services required by
//! the Generating Line (TopoDS Shape) of a BRepSweep.
//! This tool is used to iterate on the direct
//! sub-shapes of a Shape.
class BRepSweep_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Iterator();

  //! Reset the Iterator on sub-shapes of <aShape>.
  Standard_EXPORT void Init(const TopoDS_Shape& aShape);

  //! Returns True if there is a current sub-shape.
  bool More() const;

  //! Moves to the next sub-shape.
  Standard_EXPORT void Next();

  //! Returns the current sub-shape.
  const TopoDS_Shape& Value() const;

  //! Returns the orientation of the current sub-shape.
  TopAbs_Orientation Orientation() const;

private:
  TopoDS_Iterator myIterator;
};

inline bool BRepSweep_Iterator::More() const
{
  return myIterator.More();
}

//=================================================================================================

inline const TopoDS_Shape& BRepSweep_Iterator::Value() const
{
  return myIterator.Value();
}

//=================================================================================================

inline TopAbs_Orientation BRepSweep_Iterator::Orientation() const
{
  return Value().Orientation();
}
