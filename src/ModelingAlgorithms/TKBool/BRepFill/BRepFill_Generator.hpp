#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepFill_ThruSectionErrorStatus.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS_Shell.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepTools_ReShape.hpp>
class TopoDS_Wire;
class TopoDS_Shape;

class BRepFill_Generator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Generator();

  Standard_EXPORT void AddWire(const TopoDS_Wire& Wire);

  Standard_EXPORT void Perform();

  const TopoDS_Shell& Shell() const;

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape,
                                            NCollection_List<TopoDS_Shape>,
                                            TopTools_ShapeMapHasher>&
                        Generated() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GeneratedShapes(
    const TopoDS_Shape& SSection) const;

  Standard_EXPORT TopoDS_Shape ResultShape(const TopoDS_Shape& theShape) const;

  Standard_EXPORT void SetMutableInput(const bool theIsMutableInput);

  Standard_EXPORT bool IsMutableInput() const;

  BRepFill_ThruSectionErrorStatus GetStatus() const { return myStatus; }

private:
  NCollection_Sequence<TopoDS_Shape> myWires;
  TopoDS_Shell                       myShell;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myOldNewShapes;
  BRepTools_ReShape                                                        myReshaper;
  bool                                                                     myMutableInput;
  BRepFill_ThruSectionErrorStatus                                          myStatus;
};

inline const TopoDS_Shell& BRepFill_Generator::Shell() const
{
  return myShell;
}
