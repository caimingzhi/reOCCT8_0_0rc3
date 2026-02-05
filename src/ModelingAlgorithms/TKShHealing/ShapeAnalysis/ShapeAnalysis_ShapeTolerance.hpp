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

//! Tool for computing shape tolerances (minimal, maximal, average),
//! finding shape with tolerance matching given criteria,
//! setting or limitating tolerances.
class ShapeAnalysis_ShapeTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT ShapeAnalysis_ShapeTolerance();

  //! Determines a tolerance from the ones stored in a shape
  //! Remark : calls InitTolerance and AddTolerance,
  //! hence, can be used to start a series for cumulating tolerance
  //! <mode> = 0 : returns the average value between sub-shapes,
  //! <mode> > 0 : returns the maximal found,
  //! <mode> < 0 : returns the minimal found.
  //! <type> defines what kinds of sub-shapes to consider:
  //! SHAPE (default) : all : VERTEX, EDGE, FACE,
  //! VERTEX : only vertices,
  //! EDGE   : only edges,
  //! FACE   : only faces,
  //! SHELL  : combined SHELL + FACE, for each face (and containing
  //! shell), also checks EDGE and VERTEX
  Standard_EXPORT double Tolerance(const TopoDS_Shape&    shape,
                                   const int              mode,
                                   const TopAbs_ShapeEnum type = TopAbs_SHAPE);

  //! Determines which shapes have a tolerance over the given value
  //! <type> is interpreted as in the method Tolerance
  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> OverTolerance(
    const TopoDS_Shape&    shape,
    const double           value,
    const TopAbs_ShapeEnum type = TopAbs_SHAPE) const;

  //! Determines which shapes have a tolerance within a given interval
  //! <type> is interpreted as in the method Tolerance
  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> InTolerance(
    const TopoDS_Shape&    shape,
    const double           valmin,
    const double           valmax,
    const TopAbs_ShapeEnum type = TopAbs_SHAPE) const;

  //! Initializes computation of cumulated tolerance
  Standard_EXPORT void InitTolerance();

  //! Adds data on new Shape to compute Cumulated Tolerance
  //! (prepares three computations : maximal, average, minimal)
  Standard_EXPORT void AddTolerance(const TopoDS_Shape&    shape,
                                    const TopAbs_ShapeEnum type = TopAbs_SHAPE);

  //! Returns the computed tolerance according to the <mode>
  //! <mode> = 0 : average
  //! <mode> > 0 : maximal
  //! <mode> < 0 : minimal
  Standard_EXPORT double GlobalTolerance(const int mode) const;

private:
  double myTols[3];
  int    myNbTol;
};
