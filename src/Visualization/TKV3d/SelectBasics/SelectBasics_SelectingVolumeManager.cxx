

#include <SelectBasics_SelectingVolumeManager.hpp>

SelectBasics_SelectingVolumeManager::SelectBasics_SelectingVolumeManager() = default;

SelectBasics_SelectingVolumeManager::~SelectBasics_SelectingVolumeManager() = default;

bool SelectBasics_SelectingVolumeManager::Overlaps(
  const occ::handle<NCollection_HArray1<gp_Pnt>>& theArrayOfPts,
  int                                             theSensType,
  SelectBasics_PickResult&                        thePickResult) const
{
  return OverlapsPolygon(theArrayOfPts->Array1(), theSensType, thePickResult);
}
