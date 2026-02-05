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

#include <StepTidy_CartesianPointHasher.hpp>
#include <StepTidy_VectorHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Line.hpp>
#include <TCollection_HAsciiString.hpp>

//! OCCT-style hasher for StepGeom_Line entities.
struct StepTidy_LineHasher
{
  // Hashes the Line by its name and Line ratios.
  std::size_t operator()(const occ::handle<StepGeom_Line>& theLine) const noexcept
  {
    const size_t aHashes[2]{StepTidy_CartesianPointHasher{}(theLine->Pnt()),
                            StepTidy_VectorHasher{}(theLine->Dir())};

    const size_t aCombinedHash = opencascade::hashBytes(aHashes, sizeof(aHashes));
    if (theLine->Name().IsNull())
    {
      // If the name is not present, return the hash.
      return aCombinedHash;
    }
    // Add the name to the hash if it is present.
    const size_t aCombinedHashWithName[2]{
      aCombinedHash,
      std::hash<TCollection_AsciiString>{}(theLine->Name()->String())};
    return opencascade::hashBytes(aCombinedHashWithName, sizeof(aCombinedHashWithName));
  }

  // Compares two Lines by their names and Line ratios.
  bool operator()(const occ::handle<StepGeom_Line>& theLine1,
                  const occ::handle<StepGeom_Line>& theLine2) const noexcept

  {
    // Compare names.
    if (theLine1->Name().IsNull() != theLine2->Name().IsNull())
    {
      return false;
    }
    if (!theLine1->Name()->IsSameString(theLine2->Name()))
    {
      return false;
    }

    // Compare points.
    if (!StepTidy_CartesianPointHasher{}(theLine1->Pnt(), theLine2->Pnt()))
    {
      return false;
    }

    // Compare directions.
    if (!StepTidy_VectorHasher{}(theLine1->Dir(), theLine2->Dir()))
    {
      return false;
    }

    return true;
  }
};

#include <StepGeom_Line.hpp>

//! Processor for merging StepGeom_Line entities.
//! This processor merges lines with the same point and direction and names.
class StepTidy_LineReducer : public StepTidy_EntityReducer<StepGeom_Line, StepTidy_LineHasher>
{
public:
  //! Constructor. Stores the work session and registers replacer functions.
  //! @param theWS the work session.
  Standard_EXPORT StepTidy_LineReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  //! Replacer function for StepShape_EdgeCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceEdgeCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                               const occ::handle<StepGeom_Line>&      theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepGeom_TrimmedCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceTrimmedCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                  const occ::handle<StepGeom_Line>&      theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepGeom_SurfaceCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceSurfaceCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                  const occ::handle<StepGeom_Line>&      theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepRepr_DefinitionalRepresentation entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceDefinitionalRepresentation(const occ::handle<StepGeom_Line>&      theOldEntity,
                                                const occ::handle<StepGeom_Line>&      theNewEntity,
                                                const occ::handle<Standard_Transient>& theSharing);

  //! Replacer function for StepGeom_SeamCurve entities.
  //! Replaces the old entity with the new one in the sharing entity.
  //! @param theOldEntity the old entity to replace.
  //! @param theNewEntity the new entity to replace with.
  //! @param theSharing the sharing entity in which to replace the old entity.
  //! @return true if the entity was replaced, false otherwise.
  static bool replaceSeamCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                               const occ::handle<StepGeom_Line>&      theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);
};
