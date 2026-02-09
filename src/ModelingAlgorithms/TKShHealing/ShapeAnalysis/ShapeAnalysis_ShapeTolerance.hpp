#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class TopoDS_Shape;

class ShapeAnalysis_ShapeTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_ShapeTolerance();

  Standard_EXPORT double Tolerance(const TopoDS_Shape&    shape,
                                   const int              mode,
                                   const TopAbs_ShapeEnum type = TopAbs_SHAPE);

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> OverTolerance(
    const TopoDS_Shape&    shape,
    const double           value,
    const TopAbs_ShapeEnum type = TopAbs_SHAPE) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> InTolerance(
    const TopoDS_Shape&    shape,
    const double           valmin,
    const double           valmax,
    const TopAbs_ShapeEnum type = TopAbs_SHAPE) const;

  Standard_EXPORT void InitTolerance();

  Standard_EXPORT void AddTolerance(const TopoDS_Shape&    shape,
                                    const TopAbs_ShapeEnum type = TopAbs_SHAPE);

  Standard_EXPORT double GlobalTolerance(const int mode) const;

private:
  double myTols[3];
  int    myNbTol;
};
