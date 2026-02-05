#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TNaming_PtrNode.hpp>
#include <Standard_Integer.hpp>
#include <TNaming_Evolution.hpp>
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class TNaming_NewShapeIterator;
class TNaming_OldShapeIterator;
class TNaming_NamedShape;
class TDF_Label;
class TopoDS_Shape;

//! A tool to visit the contents of a named shape attribute.
//! Pairs of shapes in the attribute are iterated, one
//! being the pre-modification or the old shape, and
//! the other the post-modification or the new shape.
//! This allows you to have a full access to all
//! contents of an attribute. If, on the other hand, you
//! are only interested in topological entities stored
//! in the attribute, you can use the functions
//! GetShape and CurrentShape in TNaming_Tool.
class TNaming_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Iterates on all the history records in
  //! <anAtt>.
  Standard_EXPORT TNaming_Iterator(const occ::handle<TNaming_NamedShape>& anAtt);

  //! Iterates on all the history records in
  //! the current transaction
  Standard_EXPORT TNaming_Iterator(const TDF_Label& aLabel);

  //! Iterates on all the history records in
  //! the transaction <aTrans>
  Standard_EXPORT TNaming_Iterator(const TDF_Label& aLabel, const int aTrans);

  //! Returns True if there is a current Item in
  //! the iteration.
  bool More() const;

  //! Moves the iteration to the next Item
  Standard_EXPORT void Next();

  //! Returns the old shape in this iterator object.
  //! This shape can be a null one.
  Standard_EXPORT const TopoDS_Shape& OldShape() const;

  //! Returns the new shape in this iterator object.
  Standard_EXPORT const TopoDS_Shape& NewShape() const;

  //! Returns true if the new shape is a modification
  //! (split, fuse, etc...) of the old shape.
  Standard_EXPORT bool IsModification() const;

  Standard_EXPORT TNaming_Evolution Evolution() const;

  friend class TNaming_NewShapeIterator;
  friend class TNaming_OldShapeIterator;

private:
  TNaming_PtrNode myNode;
  int             myTrans;
};

inline bool TNaming_Iterator::More() const
{
  return (myNode != nullptr);
}
