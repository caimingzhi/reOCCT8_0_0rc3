#pragma once

#include <StepTidy_EntityReducer.hpp>

#include <StepTidy_CartesianPointHasher.hpp>
#include <StepTidy_DirectionHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Axis2Placement2d.hpp>

struct StepTidy_Axis2Placement2dHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Axis2Placement2d>& thePlacement) const noexcept
  {

    const size_t aHashes[2]{StepTidy_CartesianPointHasher{}(thePlacement->Location()),
                            thePlacement->HasRefDirection()
                              ? StepTidy_DirectionHasher{}(thePlacement->RefDirection())
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

  bool operator()(const occ::handle<StepGeom_Axis2Placement2d>& thePlacement1,
                  const occ::handle<StepGeom_Axis2Placement2d>& thePlacement2) const noexcept
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

    const bool isSameRefDirectionFlag =
      thePlacement1->HasRefDirection() == thePlacement2->HasRefDirection();
    const bool isSameRefDirection =
      isSameRefDirectionFlag
      && (!thePlacement1->HasRefDirection()
          || StepTidy_DirectionHasher{}(thePlacement1->RefDirection(),
                                        thePlacement2->RefDirection()));

    return isSameLocation && isSameRefDirection;
  }
};

#include <StepTidy_Axis2Placement3dHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Circle.hpp>
#include <TCollection_HAsciiString.hpp>

struct StepTidy_CircleHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Circle>& theCircle) const noexcept
  {
    const size_t aPositionHash =
      !theCircle->Position().Axis2Placement2d().IsNull()
        ? StepTidy_Axis2Placement2dHasher{}(theCircle->Position().Axis2Placement2d())
      : !theCircle->Position().Axis2Placement3d().IsNull()
        ? StepTidy_Axis2Placement3dHasher{}(theCircle->Position().Axis2Placement3d())
        : opencascade::MurmurHash::optimalSeed();

    const size_t aRadiusHash = opencascade::hash(static_cast<int>(theCircle->Radius()));

    const size_t aHashes[2]{aPositionHash, aRadiusHash};
    const size_t aCombinedHash = opencascade::hashBytes(aHashes, sizeof(aHashes));
    if (theCircle->Name().IsNull())
    {

      return aCombinedHash;
    }

    const size_t aHashWithName[2]{
      aCombinedHash,
      std::hash<TCollection_AsciiString>{}(theCircle->Name()->String())};
    return opencascade::hashBytes(aHashWithName, sizeof(aHashWithName));
  }

  bool operator()(const occ::handle<StepGeom_Circle>& theCircle1,
                  const occ::handle<StepGeom_Circle>& theCircle2) const noexcept
  {

    if (theCircle1->Name().IsNull() != theCircle2->Name().IsNull())
    {
      return false;
    }
    if (!theCircle1->Name()->IsSameString(theCircle2->Name()))
    {
      return false;
    }

    if (theCircle1->Position().CaseNumber() != theCircle2->Position().CaseNumber())
    {
      return false;
    }

    if (theCircle1->Position().CaseNumber() == 1)
    {
      if (!StepTidy_Axis2Placement2dHasher{}(theCircle1->Position().Axis2Placement2d(),
                                             theCircle2->Position().Axis2Placement2d()))
      {
        return false;
      }
    }
    else if (theCircle1->Position().CaseNumber() == 2)
    {
      if (!StepTidy_Axis2Placement3dHasher{}(theCircle1->Position().Axis2Placement3d(),
                                             theCircle2->Position().Axis2Placement3d()))
      {
        return false;
      }
    }

    constexpr double aTolerance = 1e-12;
    if (std::abs(theCircle1->Radius() - theCircle2->Radius()) > aTolerance)
    {
      return false;
    }

    return true;
  }
};

#include <StepGeom_Circle.hpp>

class StepTidy_CircleReducer : public StepTidy_EntityReducer<StepGeom_Circle, StepTidy_CircleHasher>
{
public:
  Standard_EXPORT StepTidy_CircleReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replaceEdgeCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                               const occ::handle<StepGeom_Circle>&    theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);

  static bool replaceSurfaceCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                                  const occ::handle<StepGeom_Circle>&    theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  static bool replaceSeamCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                               const occ::handle<StepGeom_Circle>&    theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);
};
