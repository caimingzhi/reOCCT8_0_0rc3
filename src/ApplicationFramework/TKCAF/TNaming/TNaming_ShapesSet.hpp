#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;

class TNaming_ShapesSet
{
public:
  DEFINE_STANDARD_ALLOC

  TNaming_ShapesSet();

  Standard_EXPORT TNaming_ShapesSet(const TopoDS_Shape&    S,
                                    const TopAbs_ShapeEnum Type = TopAbs_SHAPE);

  //! Removes all Shapes
  void Clear();

  //! Adds the Shape <S>
  bool Add(const TopoDS_Shape& S);

  //! Returns True if <S> is in <me>
  bool Contains(const TopoDS_Shape& S) const;

  //! Removes <S> in <me>.
  bool Remove(const TopoDS_Shape& S);

  //! Adds the shapes contained in <Shapes>.
  Standard_EXPORT void Add(const TNaming_ShapesSet& Shapes);

  //! Erases in <me> the shapes not
  //! contained in <Shapes>
  Standard_EXPORT void Filter(const TNaming_ShapesSet& Shapes);

  //! Removes in <me> the shapes contained in <Shapes>
  Standard_EXPORT void Remove(const TNaming_ShapesSet& Shapes);

  bool IsEmpty() const;

  int NbShapes() const;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& ChangeMap();

  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Map() const;

private:
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

//=================================================================================================

inline TNaming_ShapesSet::TNaming_ShapesSet() = default;

//=================================================================================================

inline void TNaming_ShapesSet::Clear()
{
  myMap.Clear();
}

//=================================================================================================

inline bool TNaming_ShapesSet::Add(const TopoDS_Shape& S)
{
  return myMap.Add(S);
}

//=================================================================================================

inline bool TNaming_ShapesSet::Contains(const TopoDS_Shape& S) const
{
  return myMap.Contains(S);
}

//=================================================================================================

inline bool TNaming_ShapesSet::Remove(const TopoDS_Shape& S)
{
  return myMap.Remove(S);
}

//=================================================================================================

inline bool TNaming_ShapesSet::IsEmpty() const
{
  return myMap.IsEmpty();
}

//=================================================================================================

inline int TNaming_ShapesSet::NbShapes() const
{
  return myMap.Extent();
}

//=================================================================================================

inline NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& TNaming_ShapesSet::ChangeMap()
{
  return myMap;
}

//=================================================================================================

inline const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& TNaming_ShapesSet::Map() const
{
  return myMap;
}
