#pragma once

#include <Standard_NoSuchObject.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopLoc_Location.hpp>
class TopoDS_Shape;

class TopoDS_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  TopoDS_Iterator()
      : myOrientation(TopAbs_FORWARD)
  {
  }

  TopoDS_Iterator(const TopoDS_Shape& S, const bool cumOri = true, const bool cumLoc = true)
  {
    Initialize(S, cumOri, cumLoc);
  }

  Standard_EXPORT void Initialize(const TopoDS_Shape& S,
                                  const bool          cumOri = true,
                                  const bool          cumLoc = true);

  bool More() const { return myShapes.More(); }

  Standard_EXPORT void Next();

  const TopoDS_Shape& Value() const
  {
    Standard_NoSuchObject_Raise_if(!More(), "TopoDS_Iterator::Value");
    return myShape;
  }

private:
  TopoDS_Shape                             myShape;
  NCollection_List<TopoDS_Shape>::Iterator myShapes;
  TopAbs_Orientation                       myOrientation;
  TopLoc_Location                          myLocation;
};
