#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <IntCurveSurface_IntersectionSegment.hpp>
class IntCurveSurface_IntersectionPoint;
class IntCurveSurface_IntersectionSegment;

class IntCurveSurface_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns the <done> field.
  Standard_EXPORT bool IsDone() const;

  //! returns the number of IntersectionPoint
  //! if IsDone returns True.
  //! else NotDone is raised.
  Standard_EXPORT int NbPoints() const;

  //! returns the IntersectionPoint of range <Index>
  //! raises NotDone if the computation has failed or if
  //! the computation has not been done
  //! raises OutOfRange if Index is not in the range <1..NbPoints>
  Standard_EXPORT const IntCurveSurface_IntersectionPoint& Point(const int Index) const;

  //! returns the number of IntersectionSegment
  //! if IsDone returns True.
  //! else NotDone is raised.
  Standard_EXPORT int NbSegments() const;

  //! returns the IntersectionSegment of range <Index>
  //! raises NotDone if the computation has failed or if
  //! the computation has not been done
  //! raises OutOfRange if Index is not in the range <1..NbSegment>
  Standard_EXPORT const IntCurveSurface_IntersectionSegment& Segment(const int Index) const;

  //! Returns true if curve is parallel or belongs surface
  //! This case is recognized only for some pairs
  //! of analytical curves and surfaces (plane - line, ...)
  Standard_EXPORT bool IsParallel() const;

  //! Dump all the fields.
  Standard_EXPORT void Dump() const;

protected:
  //! Empty Constructor;
  Standard_EXPORT IntCurveSurface_Intersection();

  //! Destructor is protected, for safe inheritance
  ~IntCurveSurface_Intersection() = default;

  //! Internal method
  //! copy the <Inter> fields to <me>
  Standard_EXPORT void SetValues(const IntCurveSurface_Intersection& Inter);

  //! Internal method
  //! Append the IntersectionPoints and
  //! IntersectionSegments of <Inter> to <me>.
  Standard_EXPORT void Append(const IntCurveSurface_Intersection& Inter,
                              const double                        FirstParamOnCurve,
                              const double                        LastParamOnCurve);

  //! Internal method
  //! Append the IntersectionPoints of <Inter> to <me>
  Standard_EXPORT void Append(const IntCurveSurface_IntersectionPoint& Pt);

  //! Internal method
  //! Append the IntersectionPoints of <Inter> to <me>
  Standard_EXPORT void Append(const IntCurveSurface_IntersectionSegment& Seg);

  //! Internal method
  //! Reset all the fields of <me>
  //! Clear the sequences of IntersectionPoints and Segments
  //! Set the field <done> to false.
  Standard_EXPORT void ResetFields();

  bool done;
  bool myIsParallel; // Curve is "parallel" surface
  // This case is recognized only for some pairs
  // of analytical curves and surfaces (plane - line, ...)

private:
  NCollection_Sequence<IntCurveSurface_IntersectionPoint>   lpnt;
  NCollection_Sequence<IntCurveSurface_IntersectionSegment> lseg;
};
