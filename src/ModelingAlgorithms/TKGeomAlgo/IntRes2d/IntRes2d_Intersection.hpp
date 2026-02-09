#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <IntRes2d_IntersectionSegment.hpp>
class IntRes2d_IntersectionPoint;
class IntRes2d_IntersectionSegment;

class IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  bool IsDone() const;

  bool IsEmpty() const;

  int NbPoints() const;

  const IntRes2d_IntersectionPoint& Point(const int N) const;

  int NbSegments() const;

  const IntRes2d_IntersectionSegment& Segment(const int N) const;

  void SetReversedParameters(const bool Reverseflag);

protected:
  IntRes2d_Intersection();

  IntRes2d_Intersection(const IntRes2d_Intersection& Other);

  IntRes2d_Intersection& operator=(const IntRes2d_Intersection& theOther) = default;

  ~IntRes2d_Intersection() = default;

  Standard_EXPORT void SetValues(const IntRes2d_Intersection& Inter);

  Standard_EXPORT void Append(const IntRes2d_Intersection& Inter,
                              const double                 FirstParam1,
                              const double                 LastParam1,
                              const double                 FirstParam2,
                              const double                 LastParam2);

  void Append(const IntRes2d_IntersectionSegment& Seg);

  void Append(const IntRes2d_IntersectionPoint& Pnt);

  Standard_EXPORT void Insert(const IntRes2d_IntersectionPoint& Pnt);

  void ResetFields();

  bool ReversedParameters() const;

protected:
  NCollection_Sequence<IntRes2d_IntersectionPoint>   lpnt;
  NCollection_Sequence<IntRes2d_IntersectionSegment> lseg;
  bool                                               done;
  bool                                               reverse;
};

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

inline bool IntRes2d_Intersection::IsDone() const
{
  return done;
}

inline IntRes2d_Intersection::IntRes2d_Intersection()
{
  done = reverse = false;
}

inline IntRes2d_Intersection::IntRes2d_Intersection(const IntRes2d_Intersection& Other)
{
  done = reverse = false;
  lpnt           = Other.lpnt;
  lseg           = Other.lseg;
}

inline bool IntRes2d_Intersection::IsEmpty() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return ((lpnt.Length() == 0) && (lseg.Length() == 0));
}

inline int IntRes2d_Intersection::NbPoints() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lpnt.Length();
}

inline const IntRes2d_IntersectionPoint& IntRes2d_Intersection::Point(const int N) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lpnt(N);
}

inline int IntRes2d_Intersection::NbSegments() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lseg.Length();
}

inline const IntRes2d_IntersectionSegment& IntRes2d_Intersection::Segment(const int N) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lseg(N);
}

inline void IntRes2d_Intersection::Append(const IntRes2d_IntersectionSegment& Seg)
{
  lseg.Append(Seg);
}

inline void IntRes2d_Intersection::Append(const IntRes2d_IntersectionPoint& Pnt)
{
  lpnt.Append(Pnt);
}

inline void IntRes2d_Intersection::ResetFields()
{
  if (done)
  {
    lseg.Clear();
    lpnt.Clear();
    done = false;
  }
}

inline void IntRes2d_Intersection::SetReversedParameters(const bool flag)
{
  reverse = flag;
}

inline bool IntRes2d_Intersection::ReversedParameters() const
{
  return (reverse);
}
