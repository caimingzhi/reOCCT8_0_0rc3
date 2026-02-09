#pragma once

#include <StepTidy_CartesianPointHasher.hpp>
#include <StepTidy_DirectionHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

struct StepTidy_Axis2Placement3dHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Axis2Placement3d>& thePlacement) const noexcept
  {

    const size_t aHashes[3]{
      StepTidy_CartesianPointHasher{}(thePlacement->Location()),
      thePlacement->HasAxis() ? StepTidy_DirectionHasher{}(thePlacement->Axis())
                              : opencascade::MurmurHash::optimalSeed(),
      thePlacement->HasRefDirection() ? StepTidy_DirectionHasher{}(thePlacement->RefDirection())
                                      : opencascade::MurmurHash::optimalSeed()};
    const size_t aHash = opencascade::hashBytes(aHashes, sizeof(aHashes));
    if (thePlacement->Name().IsNull())
    {

      return aHash;
    }

    const size_t aHashWithName[2]{
      aHash,
      std::hash<TCollection_AsciiString>{}(thePlacement->Name()->String())};
    return opencascade::hashBytes(aHashWithName, sizeof(aHashWithName));
  }

  bool operator()(const occ::handle<StepGeom_Axis2Placement3d>& thePlacement1,
                  const occ::handle<StepGeom_Axis2Placement3d>& thePlacement2) const noexcept
  {

    if (thePlacement1->Name().IsNull() != thePlacement2->Name().IsNull())
    {
      return false;
    }
    if (!thePlacement1->Name()->IsSameString(thePlacement2->Name()))
    {
      return false;
    }

    const bool isSameLocation =
      StepTidy_CartesianPointHasher{}(thePlacement1->Location(), thePlacement2->Location());

    const bool isSameAxisFlag = thePlacement1->HasAxis() == thePlacement2->HasAxis();
    const bool isSameAxis =
      isSameAxisFlag
      && (!thePlacement1->HasAxis()
          || StepTidy_DirectionHasher{}(thePlacement1->Axis(), thePlacement2->Axis()));

    const bool isSameRefDirectionFlag =
      thePlacement1->HasRefDirection() == thePlacement2->HasRefDirection();
    const bool isSameRefDirection =
      isSameRefDirectionFlag
      && (!thePlacement1->HasRefDirection()
          || StepTidy_DirectionHasher{}(thePlacement1->RefDirection(),
                                        thePlacement2->RefDirection()));

    return isSameLocation && isSameAxis && isSameRefDirection;
  }
};
