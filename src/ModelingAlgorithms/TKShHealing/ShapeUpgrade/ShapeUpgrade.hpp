#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Geom_BoundedCurve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Geom2d_BoundedCurve.hpp>
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;

class ShapeUpgrade
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool C0BSplineToSequenceOfC1BSplineCurve(
    const occ::handle<Geom_BSplineCurve>&                               BS,
    occ::handle<NCollection_HSequence<occ::handle<Geom_BoundedCurve>>>& seqBS);

  Standard_EXPORT static bool C0BSplineToSequenceOfC1BSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>&                               BS,
    occ::handle<NCollection_HSequence<occ::handle<Geom2d_BoundedCurve>>>& seqBS);
};
