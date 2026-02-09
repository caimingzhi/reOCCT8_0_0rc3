#pragma once

#include <StepTidy_EntityReducer.hpp>

#include <StepTidy_CartesianPointHasher.hpp>
#include <StepTidy_VectorHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Line.hpp>
#include <TCollection_HAsciiString.hpp>

struct StepTidy_LineHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Line>& theLine) const noexcept
  {
    const size_t aHashes[2]{StepTidy_CartesianPointHasher{}(theLine->Pnt()),
                            StepTidy_VectorHasher{}(theLine->Dir())};

    const size_t aCombinedHash = opencascade::hashBytes(aHashes, sizeof(aHashes));
    if (theLine->Name().IsNull())
    {

      return aCombinedHash;
    }

    const size_t aCombinedHashWithName[2]{
      aCombinedHash,
      std::hash<TCollection_AsciiString>{}(theLine->Name()->String())};
    return opencascade::hashBytes(aCombinedHashWithName, sizeof(aCombinedHashWithName));
  }

  bool operator()(const occ::handle<StepGeom_Line>& theLine1,
                  const occ::handle<StepGeom_Line>& theLine2) const noexcept

  {

    if (theLine1->Name().IsNull() != theLine2->Name().IsNull())
    {
      return false;
    }
    if (!theLine1->Name()->IsSameString(theLine2->Name()))
    {
      return false;
    }

    if (!StepTidy_CartesianPointHasher{}(theLine1->Pnt(), theLine2->Pnt()))
    {
      return false;
    }

    if (!StepTidy_VectorHasher{}(theLine1->Dir(), theLine2->Dir()))
    {
      return false;
    }

    return true;
  }
};

#include <StepGeom_Line.hpp>

class StepTidy_LineReducer : public StepTidy_EntityReducer<StepGeom_Line, StepTidy_LineHasher>
{
public:
  Standard_EXPORT StepTidy_LineReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replaceEdgeCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                               const occ::handle<StepGeom_Line>&      theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);

  static bool replaceTrimmedCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                  const occ::handle<StepGeom_Line>&      theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  static bool replaceSurfaceCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                  const occ::handle<StepGeom_Line>&      theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  static bool replaceDefinitionalRepresentation(const occ::handle<StepGeom_Line>&      theOldEntity,
                                                const occ::handle<StepGeom_Line>&      theNewEntity,
                                                const occ::handle<Standard_Transient>& theSharing);

  static bool replaceSeamCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                               const occ::handle<StepGeom_Line>&      theNewEntity,
                               const occ::handle<Standard_Transient>& theSharing);
};
