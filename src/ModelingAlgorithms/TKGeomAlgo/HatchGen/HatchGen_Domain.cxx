#include <HatchGen_Domain.hpp>
#include <HatchGen_PointOnHatching.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>

//=================================================================================================

HatchGen_Domain::HatchGen_Domain()
    : myHasFirstPoint(false),
      myHasSecondPoint(false)
{
}

//=================================================================================================

HatchGen_Domain::HatchGen_Domain(const HatchGen_PointOnHatching& P1,
                                 const HatchGen_PointOnHatching& P2)
    : myHasFirstPoint(true),
      myFirstPoint(P1),
      myHasSecondPoint(true),
      mySecondPoint(P2)
{
}

//=================================================================================================

HatchGen_Domain::HatchGen_Domain(const HatchGen_PointOnHatching& P, const bool First)
{
  if (First)
  {
    myHasFirstPoint  = true;
    myHasSecondPoint = false;
    myFirstPoint     = P;
  }
  else
  {
    myHasFirstPoint  = false;
    myHasSecondPoint = true;
    mySecondPoint    = P;
  }
}

//=================================================================================================

void HatchGen_Domain::Dump(const int Index) const
{
  std::cout << "=== Domain ";
  if (Index > 0)
  {
    std::cout << "# " << std::setw(3) << Index << " ";
  }
  else
  {
    std::cout << "======";
  }
  std::cout << "=============================" << std::endl;

  if (myHasFirstPoint)
  {
    myFirstPoint.Dump(1);
  }
  else
  {
    std::cout << "    Has not a first point" << std::endl;
  }

  if (myHasSecondPoint)
  {
    mySecondPoint.Dump(2);
  }
  else
  {
    std::cout << "    Has not a second point" << std::endl;
  }

  std::cout << "==============================================" << std::endl;
}
