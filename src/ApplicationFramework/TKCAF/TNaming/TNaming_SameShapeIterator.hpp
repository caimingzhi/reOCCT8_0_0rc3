#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TNaming_PtrNode.hpp>
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class TNaming_Tool;
class TopoDS_Shape;
class TNaming_UsedShapes;
class TDF_Label;

//! To iterate on all the label which contained a
//! given shape.
class TNaming_SameShapeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_SameShapeIterator(const TopoDS_Shape& aShape, const TDF_Label& access);

  bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT TDF_Label Label() const;

  friend class TNaming_Tool;

private:
  Standard_EXPORT TNaming_SameShapeIterator(const TopoDS_Shape&                    aShape,
                                            const occ::handle<TNaming_UsedShapes>& Shapes);

  TNaming_PtrNode myNode;
  bool            myIsNew;
};

inline bool TNaming_SameShapeIterator::More() const
{
  return (myNode != nullptr);
}
