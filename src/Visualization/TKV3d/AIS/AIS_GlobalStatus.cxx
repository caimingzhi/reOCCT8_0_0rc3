#include <AIS_GlobalStatus.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_GlobalStatus, Standard_Transient)

//=================================================================================================

AIS_GlobalStatus::AIS_GlobalStatus()
    : myDispMode(0),
      myIsHilit(false),
      mySubInt(false)
{
}
