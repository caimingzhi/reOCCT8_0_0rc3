#pragma once

#include <Standard_HashUtils.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <TCollection_HAsciiString.hpp>

struct StepTidy_CartesianPointHasher
{

  std::size_t operator()(
    const occ::handle<StepGeom_CartesianPoint>& theCartesianPoint) const noexcept
  {
    const std::array<double, 3>& aCoords = theCartesianPoint->Coordinates();

    if (theCartesianPoint->Name().IsNull())
    {
      return opencascade::hashBytes(aCoords.data(), static_cast<int>(aCoords.size()));
    }

    const size_t aHashes[2]{
      opencascade::hashBytes(aCoords.data(), static_cast<int>(aCoords.size())),
      std::hash<TCollection_AsciiString>{}(theCartesianPoint->Name()->String())};

    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  bool operator()(const occ::handle<StepGeom_CartesianPoint>& theCartesianPoint1,
                  const occ::handle<StepGeom_CartesianPoint>& theCartesianPoint2) const noexcept
  {

    if (theCartesianPoint1->Name().IsNull() != theCartesianPoint2->Name().IsNull())
    {
      return false;
    }
    if (!theCartesianPoint1->Name()->IsSameString(theCartesianPoint2->Name()))
    {
      return false;
    }

    constexpr double             aTolerance = 1e-12;
    const std::array<double, 3>& aCoords1   = theCartesianPoint1->Coordinates();
    const std::array<double, 3>& aCoords2   = theCartesianPoint2->Coordinates();
    if (theCartesianPoint1->NbCoordinates() != theCartesianPoint2->NbCoordinates())
    {
      return false;
    }
    for (int anIndex = 0; anIndex < theCartesianPoint1->NbCoordinates(); ++anIndex)
    {
      if (std::abs(aCoords1[anIndex] - aCoords2[anIndex]) > aTolerance)
      {
        return false;
      }
    }
    return true;
  }
};
