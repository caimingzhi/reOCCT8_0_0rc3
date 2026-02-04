#include <StdFail_NotDone.hpp>

inline bool IntStart_SearchOnBoundaries::IsDone() const
{

  return done;
}

inline bool IntStart_SearchOnBoundaries::AllArcSolution() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return all;
}

inline int IntStart_SearchOnBoundaries::NbPoints() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt.Length();
}

inline const IntStart_ThePathPoint& IntStart_SearchOnBoundaries::Point(const int Index) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt.Value(Index);
}

inline int IntStart_SearchOnBoundaries::NbSegments() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return sseg.Length();
}

inline const IntStart_TheSegment& IntStart_SearchOnBoundaries::Segment(const int Index) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return sseg.Value(Index);
}
