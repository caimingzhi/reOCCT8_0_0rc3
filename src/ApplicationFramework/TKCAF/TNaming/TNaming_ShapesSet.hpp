// Created on: 1997-01-09
// Created by: Yves FRICAUD
// Copyright (c) 1997-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _TNaming_ShapesSet_HeaderFile
#define _TNaming_ShapesSet_HeaderFile

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
// Created on: 1997-01-09
// Created by: Yves FRICAUD
// Copyright (c) 1997-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

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


#endif // _TNaming_ShapesSet_HeaderFile
