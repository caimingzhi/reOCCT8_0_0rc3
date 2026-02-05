#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TNaming_PtrNode.hpp>
#include <Standard_Integer.hpp>
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class TNaming_Tool;
class TNaming_Name;
class TNaming_Naming;
class TopoDS_Shape;
class TNaming_UsedShapes;
class TDF_Label;
class TNaming_Iterator;
class TNaming_NamedShape;

//! Iterates on all the descendants of a shape
class TNaming_NewShapeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_NewShapeIterator(const TopoDS_Shape& aShape,
                                           const int           Transaction,
                                           const TDF_Label&    access);

  Standard_EXPORT TNaming_NewShapeIterator(const TopoDS_Shape& aShape, const TDF_Label& access);

  //! Iterates from the current Shape in <anIterator>
  Standard_EXPORT TNaming_NewShapeIterator(const TNaming_NewShapeIterator& anIterator);

  //! Iterates from the current Shape in <anIterator>
  Standard_EXPORT TNaming_NewShapeIterator(const TNaming_Iterator& anIterator);

  bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT TDF_Label Label() const;

  Standard_EXPORT occ::handle<TNaming_NamedShape> NamedShape() const;

  //! Warning! Can be a Null Shape if a descendant is deleted.
  Standard_EXPORT const TopoDS_Shape& Shape() const;

  //! True if the new shape is a modification (split,
  //! fuse,etc...) of the old shape.
  Standard_EXPORT bool IsModification() const;

  friend class TNaming_Tool;
  friend class TNaming_Name;
  friend class TNaming_Naming;

private:
  Standard_EXPORT TNaming_NewShapeIterator(const TopoDS_Shape&                    aShape,
                                           const int                              Transaction,
                                           const occ::handle<TNaming_UsedShapes>& Shapes);

  Standard_EXPORT TNaming_NewShapeIterator(const TopoDS_Shape&                    aShape,
                                           const occ::handle<TNaming_UsedShapes>& Shapes);

  TNaming_PtrNode myNode;
  int             myTrans;
};

inline bool TNaming_NewShapeIterator::More() const
{
  return (myNode != nullptr);
}
