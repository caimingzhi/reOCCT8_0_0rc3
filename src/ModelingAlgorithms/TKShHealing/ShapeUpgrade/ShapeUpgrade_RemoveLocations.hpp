#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>

class ShapeUpgrade_RemoveLocations : public Standard_Transient
{

public:
  Standard_EXPORT ShapeUpgrade_RemoveLocations();

  Standard_EXPORT bool Remove(const TopoDS_Shape& theShape);

  TopoDS_Shape GetResult() const;

  void SetRemoveLevel(const TopAbs_ShapeEnum theLevel);

  TopAbs_ShapeEnum RemoveLevel() const;

  TopoDS_Shape ModifiedShape(const TopoDS_Shape& theInitShape) const;

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

inline TopoDS_Shape ShapeUpgrade_RemoveLocations::GetResult() const
{
  return myShape;
}

inline void ShapeUpgrade_RemoveLocations::SetRemoveLevel(const TopAbs_ShapeEnum theLevel)
{

  if ((int)theLevel > TopAbs_FACE)
    myLevelRemoving = TopAbs_FACE;
  else
    myLevelRemoving = theLevel;
}

inline TopAbs_ShapeEnum ShapeUpgrade_RemoveLocations::RemoveLevel() const
{
  return myLevelRemoving;
}

inline TopoDS_Shape ShapeUpgrade_RemoveLocations::ModifiedShape(
  const TopoDS_Shape& theInitShape) const
{
  TopoDS_Shape aShape = theInitShape;
  if (myMapNewShapes.IsBound(theInitShape))
    aShape = myMapNewShapes.Find(theInitShape);
  return aShape;
}
