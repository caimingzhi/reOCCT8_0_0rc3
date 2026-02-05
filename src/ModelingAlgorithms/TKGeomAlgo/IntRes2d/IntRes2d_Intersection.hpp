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

//! Defines the root class of all the Intersections
//! between two 2D-Curves, and provides all the methods
//! about the results of the Intersections Algorithms.
class IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns TRUE when the computation was successful.
  bool IsDone() const;

  //! Returns TRUE if there is no intersection between the
  //! given arguments.
  //! The exception NotDone is raised if IsDone returns FALSE.
  bool IsEmpty() const;

  //! This function returns the number of intersection
  //! points between the 2 curves.
  //! The exception NotDone is raised if IsDone returns FALSE.
  int NbPoints() const;

  //! This function returns the intersection point
  //! of range N;
  //! The exception NotDone is raised if IsDone returns FALSE.
  //! The exception OutOfRange is raised if (N <= 0)
  //! or (N > NbPoints).
  const IntRes2d_IntersectionPoint& Point(const int N) const;

  //! This function returns the number of intersection
  //! segments between the two curves.
  //! The exception NotDone is raised if IsDone returns FALSE.
  int NbSegments() const;

  //! This function returns the intersection segment
  //! of range N;
  //! The exception NotDone is raised if IsDone returns FALSE.
  //! The exception OutOfRange is raised if (N <= 0)
  //! or (N > NbPoints).
  const IntRes2d_IntersectionSegment& Segment(const int N) const;

  void SetReversedParameters(const bool Reverseflag);

protected:
  //! Empty constructor.
  IntRes2d_Intersection();

  IntRes2d_Intersection(const IntRes2d_Intersection& Other);

  //! Assignment
  IntRes2d_Intersection& operator=(const IntRes2d_Intersection& theOther) = default;

  //! Destructor is protected, for safe inheritance
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

//----------------------------------------------------------------------
inline IntRes2d_Intersection::IntRes2d_Intersection()
{
  done = reverse = false;
}

//----------------------------------------------------------------------
inline IntRes2d_Intersection::IntRes2d_Intersection(const IntRes2d_Intersection& Other)
{
  done = reverse = false;
  lpnt           = Other.lpnt;
  lseg           = Other.lseg;
}

//----------------------------------------------------------------------
inline bool IntRes2d_Intersection::IsEmpty() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return ((lpnt.Length() == 0) && (lseg.Length() == 0));
}

//----------------------------------------------------------------------
inline int IntRes2d_Intersection::NbPoints() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lpnt.Length();
}

//----------------------------------------------------------------------
inline const IntRes2d_IntersectionPoint& IntRes2d_Intersection::Point(const int N) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lpnt(N);
}

//----------------------------------------------------------------------
inline int IntRes2d_Intersection::NbSegments() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lseg.Length();
}

//----------------------------------------------------------------------
inline const IntRes2d_IntersectionSegment& IntRes2d_Intersection::Segment(const int N) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return lseg(N);
}

//----------------------------------------------------------------------
inline void IntRes2d_Intersection::Append(const IntRes2d_IntersectionSegment& Seg)
{
  lseg.Append(Seg);
}

//----------------------------------------------------------------------
inline void IntRes2d_Intersection::Append(const IntRes2d_IntersectionPoint& Pnt)
{
  lpnt.Append(Pnt);
}

//----------------------------------------------------------------------
inline void IntRes2d_Intersection::ResetFields()
{
  if (done)
  {
    lseg.Clear();
    lpnt.Clear();
    done = false;
  }
}

//----------------------------------------------------------------------
inline void IntRes2d_Intersection::SetReversedParameters(const bool flag)
{
  reverse = flag;
}

//----------------------------------------------------------------------
inline bool IntRes2d_Intersection::ReversedParameters() const
{
  return (reverse);
}
