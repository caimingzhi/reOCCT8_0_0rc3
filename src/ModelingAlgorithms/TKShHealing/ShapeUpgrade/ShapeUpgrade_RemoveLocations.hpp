#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>

//! Removes all locations sub-shapes of specified shape
class ShapeUpgrade_RemoveLocations : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT ShapeUpgrade_RemoveLocations();

  //! Removes all location correspondingly to RemoveLevel.
  Standard_EXPORT bool Remove(const TopoDS_Shape& theShape);

  //! Returns shape with removed locations.
  TopoDS_Shape GetResult() const;

  //! sets level starting with that location will be removed,
  //! by default TopAbs_SHAPE. In this case locations will be kept for specified shape
  //! and if specified shape is TopAbs_COMPOUND for sub-shapes of first level.
  void SetRemoveLevel(const TopAbs_ShapeEnum theLevel);

  //! sets level starting with that location will be removed.Value of level can be set to
  //! TopAbs_SHAPE,TopAbs_COMPOUND,TopAbs_SOLID,TopAbs_SHELL,TopAbs_FACE.By default TopAbs_SHAPE.
  //! In this case location will be removed for all shape types for exception of compound.
  TopAbs_ShapeEnum RemoveLevel() const;

  //! Returns modified shape obtained from initial shape.
  TopoDS_Shape ModifiedShape(const TopoDS_Shape& theInitShape) const;

  //! Returns map of modified shapes.
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
    GetModifiedShapesMap() const
  {
    return myMapNewShapes;
  }

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_RemoveLocations, Standard_Transient)

private:
  Standard_EXPORT bool MakeNewShape(const TopoDS_Shape& theShape,
                                    const TopoDS_Shape& theAncShape,
                                    TopoDS_Shape&       theNewShape,
                                    const bool          theRemoveLoc);

  TopAbs_ShapeEnum                                                         myLevelRemoving;
  TopoDS_Shape                                                             myShape;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapNewShapes;
};

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

//=================================================================================================

inline TopoDS_Shape ShapeUpgrade_RemoveLocations::GetResult() const
{
  return myShape;
}

//=================================================================================================

inline void ShapeUpgrade_RemoveLocations::SetRemoveLevel(const TopAbs_ShapeEnum theLevel)
{

  if ((int)theLevel > TopAbs_FACE)
    myLevelRemoving = TopAbs_FACE;
  else
    myLevelRemoving = theLevel;
}

//=================================================================================================

inline TopAbs_ShapeEnum ShapeUpgrade_RemoveLocations::RemoveLevel() const
{
  return myLevelRemoving;
}

//=================================================================================================

inline TopoDS_Shape ShapeUpgrade_RemoveLocations::ModifiedShape(
  const TopoDS_Shape& theInitShape) const
{
  TopoDS_Shape aShape = theInitShape;
  if (myMapNewShapes.IsBound(theInitShape))
    aShape = myMapNewShapes.Find(theInitShape);
  return aShape;
}
