

#include <StepTidy_PlaneReducer.hpp>

#include <StepShape_AdvancedFace.hpp>
#include <StepGeom_Pcurve.hpp>

StepTidy_PlaneReducer::StepTidy_PlaneReducer(const occ::handle<XSControl_WorkSession>& theWS)
    : StepTidy_EntityReducer<StepGeom_Plane, StepTidy_PlaneHasher>(theWS)
{
  registerReplacer(STANDARD_TYPE(StepShape_AdvancedFace), replaceAdvancedFace);
  registerReplacer(STANDARD_TYPE(StepGeom_Pcurve), replacePcurve);
}

bool StepTidy_PlaneReducer::replaceAdvancedFace(const occ::handle<StepGeom_Plane>&     theOldEntity,
                                                const occ::handle<StepGeom_Plane>&     theNewEntity,
                                                const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepShape_AdvancedFace> aSharing = occ::down_cast<StepShape_AdvancedFace>(theSharing);
  if (aSharing->FaceGeometry() == theOldEntity)
  {
    aSharing->SetFaceGeometry(theNewEntity);
    return true;
  }
  return false;
}

bool StepTidy_PlaneReducer::replacePcurve(const occ::handle<StepGeom_Plane>&     theOldEntity,
                                          const occ::handle<StepGeom_Plane>&     theNewEntity,
                                          const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_Pcurve> aSharing = occ::down_cast<StepGeom_Pcurve>(theSharing);
  if (aSharing->BasisSurface() == theOldEntity)
  {
    aSharing->SetBasisSurface(theNewEntity);
    return true;
  }
  return false;
}
