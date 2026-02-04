#include <StdFail_NotDone.hpp>

inline bool IntStart_SearchInside::IsDone() const
{

  return done;
}

inline int IntStart_SearchInside::NbPoints() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return list.Length();
}

inline const IntSurf_InteriorPoint& IntStart_SearchInside::Value(const int Index) const

{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return list.Value(Index);
}
