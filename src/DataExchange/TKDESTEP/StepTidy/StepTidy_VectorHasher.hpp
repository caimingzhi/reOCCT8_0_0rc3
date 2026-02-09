#pragma once

#include <StepTidy_DirectionHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

struct StepTidy_VectorHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Vector>& theVector) const noexcept
  {
    const size_t aHashes[2]{StepTidy_DirectionHasher{}(theVector->Orientation()),
                            opencascade::hash(static_cast<int>(theVector->Magnitude()))};
    const size_t aCombinedHash = opencascade::hashBytes(aHashes, sizeof(aHashes));
    if (theVector->Name().IsNull())
    {

      return aCombinedHash;
    }

    const size_t aCombinedHashWithName[2]{
      aCombinedHash,
      std::hash<TCollection_AsciiString>{}(theVector->Name()->String())};
    return opencascade::hashBytes(aCombinedHashWithName, sizeof(aCombinedHashWithName));
  }

  bool operator()(const occ::handle<StepGeom_Vector>& theVector1,
                  const occ::handle<StepGeom_Vector>& theVector2) const noexcept
  {

    if (theVector1->Name().IsNull() != theVector2->Name().IsNull())
    {
      return false;
    }
    if (!theVector1->Name()->IsSameString(theVector2->Name()))
    {
      return false;
    }

    constexpr double aTolerance = 1e-12;
    if (fabs(theVector1->Magnitude() - theVector2->Magnitude()) > aTolerance)
    {
      return false;
    }

    return StepTidy_DirectionHasher{}(theVector1->Orientation(), theVector2->Orientation());
  }
};
