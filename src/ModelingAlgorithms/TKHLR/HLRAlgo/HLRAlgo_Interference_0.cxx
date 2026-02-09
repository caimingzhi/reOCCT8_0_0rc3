#include <HLRAlgo_Interference.hpp>

#include <HLRAlgo_Intersection.hpp>
#include <HLRAlgo_Coincidence.hpp>

HLRAlgo_Interference::HLRAlgo_Interference() = default;

HLRAlgo_Interference::HLRAlgo_Interference(const HLRAlgo_Intersection& Inters,
                                           const HLRAlgo_Coincidence&  Bound,
                                           const TopAbs_Orientation    Orient,
                                           const TopAbs_Orientation    Trans,
                                           const TopAbs_Orientation    BTrans)
    : myIntersection(Inters),
      myBoundary(Bound),
      myOrientation(Orient),
      myTransition(Trans),
      myBTransition(BTrans)
{
}
