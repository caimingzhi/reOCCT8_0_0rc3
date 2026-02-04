#include <StdFail_NotDone.hpp>

#include IntWalk_TheIWLine_hxx

inline void IntWalk_IWalking::SetTolerance(const double Epsilon,
                                           const double Deflection,
                                           const double Increment)
{
  fleche  = Deflection;
  pas     = Increment;
  epsilon = Epsilon * Epsilon;
}

inline bool IntWalk_IWalking::IsDone() const
{
  return done;
}

inline int IntWalk_IWalking::NbLines() const
{
  if (!done)
    throw StdFail_NotDone();
  return lines.Length();
}

inline const occ::handle<IntWalk_TheIWLine>& IntWalk_IWalking::Value(const int Index) const
{
  if (!done)
    throw StdFail_NotDone();
  return lines.Value(Index);
}

inline int IntWalk_IWalking::NbSinglePnts() const
{
  if (!done)
    throw StdFail_NotDone();
  return seqSingle.Length();
}

inline const ThePointOfPath& IntWalk_IWalking::SinglePnt(const int Index) const
{
  if (!done)
    throw StdFail_NotDone();
  return seqSingle.Value(Index);
}
