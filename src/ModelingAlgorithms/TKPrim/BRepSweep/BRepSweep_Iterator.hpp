#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Iterator.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;

class BRepSweep_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Iterator();

  Standard_EXPORT void Init(const TopoDS_Shape& aShape);

  bool More() const;

  Standard_EXPORT void Next();

  const TopoDS_Shape& Value() const;

  TopAbs_Orientation Orientation() const;

private:
  TopoDS_Iterator myIterator;
};

inline bool BRepSweep_Iterator::More() const
{
  return myIterator.More();
}

inline const TopoDS_Shape& BRepSweep_Iterator::Value() const
{
  return myIterator.Value();
}

inline TopAbs_Orientation BRepSweep_Iterator::Orientation() const
{
  return Value().Orientation();
}
