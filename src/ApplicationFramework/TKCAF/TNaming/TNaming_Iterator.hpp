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

class TNaming_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_Iterator(const occ::handle<TNaming_NamedShape>& anAtt);

  Standard_EXPORT TNaming_Iterator(const TDF_Label& aLabel);

  Standard_EXPORT TNaming_Iterator(const TDF_Label& aLabel, const int aTrans);

  bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopoDS_Shape& OldShape() const;

  Standard_EXPORT const TopoDS_Shape& NewShape() const;

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
