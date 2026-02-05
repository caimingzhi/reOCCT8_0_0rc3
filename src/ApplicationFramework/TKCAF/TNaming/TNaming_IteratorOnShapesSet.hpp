#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>

#include <TopTools_ShapeMapHasher.hpp>

#include <NCollection_Map.hpp>
#include <Standard_Boolean.hpp>
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class TNaming_ShapesSet;
class TopoDS_Shape;

class TNaming_IteratorOnShapesSet
{
public:
  DEFINE_STANDARD_ALLOC

  TNaming_IteratorOnShapesSet();

  TNaming_IteratorOnShapesSet(const TNaming_ShapesSet& S);

  //! Initialize the iteration
  void Init(const TNaming_ShapesSet& S);

  //! Returns True if there is a current Item in
  //! the iteration.
  bool More() const;

  //! Move to the next Item
  void Next();

  const TopoDS_Shape& Value() const;

private:
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator myIt;
};

#include <TNaming_ShapesSet.hpp>

//=================================================================================================

inline TNaming_IteratorOnShapesSet::TNaming_IteratorOnShapesSet() = default;

//=================================================================================================

inline TNaming_IteratorOnShapesSet::TNaming_IteratorOnShapesSet(const TNaming_ShapesSet& S)
{
  Init(S);
}

//=================================================================================================

inline void TNaming_IteratorOnShapesSet::Init(const TNaming_ShapesSet& S)
{
  myIt.Initialize(S.Map());
}

//=================================================================================================

inline bool TNaming_IteratorOnShapesSet::More() const
{
  return (myIt.More());
}

//=================================================================================================

inline void TNaming_IteratorOnShapesSet::Next()
{
  myIt.Next();
}

//=================================================================================================

inline const TopoDS_Shape& TNaming_IteratorOnShapesSet::Value() const
{
  return myIt.Key();
}
