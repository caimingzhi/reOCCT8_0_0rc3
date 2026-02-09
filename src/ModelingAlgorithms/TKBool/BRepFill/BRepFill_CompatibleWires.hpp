#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepFill_ThruSectionErrorStatus.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Edge;

class BRepFill_CompatibleWires
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_CompatibleWires();

  Standard_EXPORT BRepFill_CompatibleWires(const NCollection_Sequence<TopoDS_Shape>& Sections);

  Standard_EXPORT void Init(const NCollection_Sequence<TopoDS_Shape>& Sections);

  Standard_EXPORT void SetPercent(const double percent = 0.01);

  Standard_EXPORT void Perform(const bool WithRotation = true);

  Standard_EXPORT bool IsDone() const;

  BRepFill_ThruSectionErrorStatus GetStatus() const { return myStatus; }

  Standard_EXPORT const NCollection_Sequence<TopoDS_Shape>& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GeneratedShapes(
    const TopoDS_Edge& SubSection) const;

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape,
                                            NCollection_List<TopoDS_Shape>,
                                            TopTools_ShapeMapHasher>&
                        Generated() const;

  Standard_EXPORT bool IsDegeneratedFirstSection() const;

  Standard_EXPORT bool IsDegeneratedLastSection() const;

private:
  Standard_EXPORT void SameNumberByPolarMethod(const bool WithRotation = true);

  Standard_EXPORT void SameNumberByACR(const bool report);

  Standard_EXPORT void ComputeOrigin(const bool polar);

  Standard_EXPORT void SearchOrigin();

  NCollection_Sequence<TopoDS_Shape> myInit;
  NCollection_Sequence<TopoDS_Shape> myWork;
  double                             myPercent;
  bool                               myDegen1;
  bool                               myDegen2;
  BRepFill_ThruSectionErrorStatus    myStatus;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};
