#pragma once

#include <StepTidy_EntityReducer.hpp>

#include <StepTidy_Axis2Placement3dHasher.hpp>

#include <Standard_HashUtils.hpp>
#include <StepGeom_Plane.hpp>

struct StepTidy_PlaneHasher
{

  std::size_t operator()(const occ::handle<StepGeom_Plane>& thePlane) const noexcept
  {
    const size_t aHash = StepTidy_Axis2Placement3dHasher{}(thePlane->Position());
    if (thePlane->Name().IsNull())
    {

      return aHash;
    }

    const size_t aCombinedHashWithName[2]{
      aHash,
      std::hash<TCollection_AsciiString>{}(thePlane->Name()->String())};
    return opencascade::hashBytes(aCombinedHashWithName, sizeof(aCombinedHashWithName));
  }

  bool operator()(const occ::handle<StepGeom_Plane>& thePlane1,
                  const occ::handle<StepGeom_Plane>& thePlane2) const noexcept
  {

    if (thePlane1->Name().IsNull() != thePlane2->Name().IsNull())
    {
      return false;
    }
    if (!thePlane1->Name()->IsSameString(thePlane2->Name()))
    {
      return false;
    }

    return StepTidy_Axis2Placement3dHasher{}(thePlane1->Position(), thePlane2->Position());
  }
};

#include <StepGeom_Plane.hpp>

class StepTidy_PlaneReducer : public StepTidy_EntityReducer<StepGeom_Plane, StepTidy_PlaneHasher>
{
public:
  Standard_EXPORT StepTidy_PlaneReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replaceAdvancedFace(const occ::handle<StepGeom_Plane>&     theOldEntity,
                                  const occ::handle<StepGeom_Plane>&     theNewEntity,
                                  const occ::handle<Standard_Transient>& theSharing);

  static bool replacePcurve(const occ::handle<StepGeom_Plane>&     theOldEntity,
                            const occ::handle<StepGeom_Plane>&     theNewEntity,
                            const occ::handle<Standard_Transient>& theSharing);
};
