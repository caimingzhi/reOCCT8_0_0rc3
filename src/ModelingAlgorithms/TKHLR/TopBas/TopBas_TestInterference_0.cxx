#include <TopBas_TestInterference.hpp>

//=================================================================================================

TopBas_TestInterference::TopBas_TestInterference() = default;

//=================================================================================================

TopBas_TestInterference::TopBas_TestInterference(const double&            Inters,
                                                 const int&               Bound,
                                                 const TopAbs_Orientation Orient,
                                                 const TopAbs_Orientation Trans,
                                                 const TopAbs_Orientation BTrans)
    : myIntersection(Inters),
      myBoundary(Bound),
      myOrientation(Orient),
      myTransition(Trans),
      myBTransition(BTrans)
{
}
