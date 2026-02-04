#pragma once


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


#include <StepTidy_Axis2Placement3dHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Plane.hpp>

//! OCCT-style hasher for StepGeom_Plane entities.
struct StepTidy_PlaneHasher
{
  // Hashes the axis Planes.
  std::size_t operator()(const occ::handle<StepGeom_Plane>& thePlane) const noexcept
  {
    const size_t aHash = StepTidy_Axis2Placement3dHasher{}(thePlane->Position());
    if (thePlane->Name().IsNull())
    {
      // If the name is not present, return the hash.
      return aHash;
    }
    // Add the name to the hash if it is present.
    const size_t aCombinedHashWithName[2]{
      aHash,
      std::hash<TCollection_AsciiString>{}(thePlane->Name()->String())};
    return opencascade::hashBytes(aCombinedHashWithName, sizeof(aCombinedHashWithName));
  }

  // Compares two axis Planes.
  bool operator()(const occ::handle<StepGeom_Plane>& thePlane1,
                  const occ::handle<StepGeom_Plane>& thePlane2) const noexcept
  {
    // Compare names.
    if (thePlane1->Name().IsNull() != thePlane2->Name().IsNull())
    {
      return false;
    }
    if (!thePlane1->Name()->IsSameString(thePlane2->Name()))
    {
      return false;
    }

    // Compare axis Planes.
    return StepTidy_Axis2Placement3dHasher{}(thePlane1->Position(), thePlane2->Position());
  }
};



#include <StepGeom_Plane.hpp>

//! Processor for merging StepGeom_Plane entities.
//! This processor merges planes with the same names and placements.
class StepTidy_PlaneReducer : public StepTidy_EntityReducer<StepGeom_Plane, StepTidy_PlaneHasher>
{
public:
  //! Constructor. Stores the work session and registers replacer functions.
  //! @param theWS the work session.
  Standard_EXPORT StepTidy_PlaneReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  //! Replacer function for StepShape_AdvancedFace entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing StepShape_AdvancedFace in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceAdvancedFace(const occ::handle<StepGeom_Plane>&     theOldEntity,
                                  const occ::handle<StepGeom_Plane>&     theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepGeom_Pcurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing StepGeom_Pcurve in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replacePcurve(const occ::handle<StepGeom_Plane>&     theOldEntity,
                            const occ::handle<StepGeom_Plane>&     theNewEntity,
                            const occ::handle<Standard_Transient>& theSharing);
};

