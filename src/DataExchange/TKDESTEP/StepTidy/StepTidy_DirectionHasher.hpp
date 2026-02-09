#pragma once

#include <Standard_HashUtils.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

struct StepTidy_DirectionHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Direction>& theDirection) const noexcept
  {
    const std::array<double, 3>& aCoords = theDirection->DirectionRatios();

    if (theDirection->Name().IsNull())
    {
      return opencascade::hashBytes(aCoords.data(), static_cast<int>(aCoords.size()));
    }

    const size_t aHashes[2]{
      opencascade::hashBytes(aCoords.data(), static_cast<int>(aCoords.size())),
      std::hash<TCollection_AsciiString>{}(theDirection->Name()->String())};

    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<StepGeom_Direction>& theDirection1,
                  const occ::handle<StepGeom_Direction>& theDirection2) const noexcept
  {

    if (theDirection1->Name().IsNull() != theDirection2->Name().IsNull())
    {
      return false;
    }
    if (!theDirection1->Name()->IsSameString(theDirection2->Name()))
    {
      return false;
    }

    constexpr double             aTolerance = 1e-12;
    const std::array<double, 3>& aCoords1   = theDirection1->DirectionRatios();
    const std::array<double, 3>& aCoords2   = theDirection2->DirectionRatios();
    if (theDirection1->NbDirectionRatios() != theDirection2->NbDirectionRatios())
    {
      return false;
    }
    for (int anIndex = 0; anIndex < theDirection1->NbDirectionRatios(); ++anIndex)
    {
      if (std::abs(aCoords1[anIndex] - aCoords2[anIndex]) > aTolerance)
      {
        return false;
      }
    }
    return true;
  }
};
