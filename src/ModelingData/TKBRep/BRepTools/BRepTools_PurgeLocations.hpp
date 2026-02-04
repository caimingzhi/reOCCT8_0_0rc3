#pragma once


#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <BRepTools_ReShape.hpp>
#include <TopTools_LocationSet.hpp>

//! Removes location datums, which satisfy conditions:
//! aTrsf.IsNegative() || (std::abs(std::abs(aTrsf.ScaleFactor()) - 1.) >
//! TopLoc_Location::ScalePrec()) from all locations of shape and its subshapes
class BRepTools_PurgeLocations
{

public:
  Standard_EXPORT BRepTools_PurgeLocations();

  //! Removes all locations correspondingly to criterium from theShape.
  Standard_EXPORT bool Perform(const TopoDS_Shape& theShape);

  //! Returns shape with removed locations.
  Standard_EXPORT const TopoDS_Shape& GetResult() const;

  Standard_EXPORT bool IsDone() const;

  //! Returns modified shape obtained from initial shape.
  TopoDS_Shape ModifiedShape(const TopoDS_Shape& theInitShape) const;

private:
  void AddShape(const TopoDS_Shape& theS);
  bool PurgeLocation(const TopoDS_Shape& theS, TopoDS_Shape& theRes);

  bool                                                                     myDone;
  TopoDS_Shape                                                             myShape;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>            myMapShapes;
  TopTools_LocationSet                                                     myLocations;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapNewShapes;
  occ::handle<BRepTools_ReShape>                                           myReShape;
};

