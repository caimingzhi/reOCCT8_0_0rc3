#include <HLRAlgo_Intersection.hpp>

//=================================================================================================

HLRAlgo_Intersection::HLRAlgo_Intersection()
    : mySegIndex(0),
      myIndex(0),
      myLevel(0),
      myParam(0.0),
      myToler(0.0)
{
}

//=================================================================================================

HLRAlgo_Intersection::HLRAlgo_Intersection(const TopAbs_Orientation Ori,
                                           const int                Lev,
                                           const int                SegInd,
                                           const int                Ind,
                                           const double             P,
                                           const float              Tol,
                                           const TopAbs_State       S)
    : myOrien(Ori),
      mySegIndex(SegInd),
      myIndex(Ind),
      myLevel(Lev),
      myParam(P),
      myToler(Tol),
      myState(S)
{
}
