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

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT const IntCurveSurface_IntersectionPoint& Point(const int Index) const;

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT const IntCurveSurface_IntersectionSegment& Segment(const int Index) const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT void Dump() const;

protected:
  Standard_EXPORT IntCurveSurface_Intersection();

  ~IntCurveSurface_Intersection() = default;

  Standard_EXPORT void SetValues(const IntCurveSurface_Intersection& Inter);

  Standard_EXPORT void Append(const IntCurveSurface_Intersection& Inter,
                              const double                        FirstParamOnCurve,
                              const double                        LastParamOnCurve);

  Standard_EXPORT void Append(const IntCurveSurface_IntersectionPoint& Pt);

  Standard_EXPORT void Append(const IntCurveSurface_IntersectionSegment& Seg);

  Standard_EXPORT void ResetFields();

  bool done;
  bool myIsParallel;

private:
  NCollection_Sequence<IntCurveSurface_IntersectionPoint>   lpnt;
  NCollection_Sequence<IntCurveSurface_IntersectionSegment> lseg;
};
