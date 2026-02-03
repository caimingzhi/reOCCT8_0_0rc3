// Copyright (c) 2025 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _StepTidy_CircleReducer_HeaderFile
#define _StepTidy_CircleReducer_HeaderFile

#include <StepTidy_EntityReducer.hpp>
// Copyright (c) 2025 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _StepTidy_CircleHasher_HeaderFile
#define _StepTidy_CircleHasher_HeaderFile
// Copyright (c) 2025 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _StepTidy_Axis2Placement2dHasher_HeaderFile
#define _StepTidy_Axis2Placement2dHasher_HeaderFile

#include <StepTidy_CartesianPointHasher.hpp>
#include <StepTidy_DirectionHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Axis2Placement2d.hpp>

//! OCCT-style hasher for StepGeom_Axis2Placement2d entities.
//! Currently only used for implementation of hasher for StepGeom_Circle.
struct StepTidy_Axis2Placement2dHasher
{
  // Hashes the axis placements.
  std::size_t operator()(const occ::handle<StepGeom_Axis2Placement2d>& thePlacement) const noexcept
  {
    // Prepare an array of hashes for the location, axis, and ref direction.
    // Optimal seed is used for the axis and ref direction if they are not present.
    const size_t aHashes[2]{StepTidy_CartesianPointHasher{}(thePlacement->Location()),
                            thePlacement->HasRefDirection()
                              ? StepTidy_DirectionHasher{}(thePlacement->RefDirection())
                              : opencascade::MurmurHash::optimalSeed()};
    const size_t aHash = opencascade::hashBytes(aHashes, sizeof(aHashes));
    if (thePlacement->Name().IsNull())
    {
      // If the name is not present, return the hash.
      return aHash;
    }
    // Add the name to the hash if it is present.
    const size_t aHashWithName[2]{
      aHash,
      std::hash<TCollection_AsciiString>{}(thePlacement->Name()->String())};
    return opencascade::hashBytes(aHashWithName, sizeof(aHashWithName));
  }

  // Compares two axis placements.
  bool operator()(const occ::handle<StepGeom_Axis2Placement2d>& thePlacement1,
                  const occ::handle<StepGeom_Axis2Placement2d>& thePlacement2) const noexcept
  {
    // Compare names.
    if (thePlacement1->Name().IsNull() != thePlacement2->Name().IsNull())
    {
      return false;
    }
    if (!thePlacement1->Name()->IsSameString(thePlacement2->Name()))
    {
      return false;
    }

    // Compare location, axis, and ref direction.
    const bool isSameLocation =
      StepTidy_CartesianPointHasher{}(thePlacement1->Location(), thePlacement2->Location());
    // Have to check if the axis is present and compare it.
    // Have to check if the ref direction is present and compare it.
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

#endif // _StepTidy_Axis2Placement2dHasher_HeaderFile

#include <StepTidy_Axis2Placement3dHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Circle.hpp>
#include <TCollection_HAsciiString.hpp>

//! OCCT-style hasher for StepGeom_Circle entities.
struct StepTidy_CircleHasher
{
  //! Returns hash for a Circle entity.
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
      // If the name is not present, return the hash.
      return aCombinedHash;
    }
    // Add the name to the hash if it is present.
    const size_t aHashWithName[2]{
      aCombinedHash,
      std::hash<TCollection_AsciiString>{}(theCircle->Name()->String())};
    return opencascade::hashBytes(aHashWithName, sizeof(aHashWithName));
  }

  //! Compares two Circle entities.
  bool operator()(const occ::handle<StepGeom_Circle>& theCircle1,
                  const occ::handle<StepGeom_Circle>& theCircle2) const noexcept
  {
    // Compare names.
    if (theCircle1->Name().IsNull() != theCircle2->Name().IsNull())
    {
      return false;
    }
    if (!theCircle1->Name()->IsSameString(theCircle2->Name()))
    {
      return false;
    }

    // Compare axis placements.
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

    // Compare radius.
    constexpr double aTolerance = 1e-12;
    if (std::abs(theCircle1->Radius() - theCircle2->Radius()) > aTolerance)
    {
      return false;
    }

    return true;
  }
};

#endif // _StepTidy_CircleHasher_HeaderFile


#include <StepGeom_Circle.hpp>

//! Processor for merging StepGeom_Circle entities.
//! This processor merges circles with the same position and radius and names.
class StepTidy_CircleReducer : public StepTidy_EntityReducer<StepGeom_Circle, StepTidy_CircleHasher>
{
public:
  //! Constructor. Stores the work session and registers replacer functions.
  //! @param theWS the work session.
  Standard_EXPORT StepTidy_CircleReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  //! Replacer function for StepShape_EdgeCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceEdgeCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                               const occ::handle<StepGeom_Circle>&    theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepGeom_SurfaceCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceSurfaceCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                                  const occ::handle<StepGeom_Circle>&    theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepGeom_SeamCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceSeamCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                               const occ::handle<StepGeom_Circle>&    theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);
};

#endif // _StepTidy_CircleReducer_HeaderFile
