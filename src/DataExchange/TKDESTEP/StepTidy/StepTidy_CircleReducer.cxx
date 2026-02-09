

#include <StepTidy_CircleReducer.hpp>

#include <Interface_Graph.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepGeom_SeamCurve.hpp>

StepTidy_CircleReducer::StepTidy_CircleReducer(const occ::handle<XSControl_WorkSession>& theWS)
    : StepTidy_EntityReducer<StepGeom_Circle, StepTidy_CircleHasher>(theWS)
{
  registerReplacer(STANDARD_TYPE(StepShape_EdgeCurve), replaceEdgeCurve);
  registerReplacer(STANDARD_TYPE(StepGeom_SurfaceCurve), replaceSurfaceCurve);
  registerReplacer(STANDARD_TYPE(StepGeom_SeamCurve), replaceSeamCurve);
}

bool StepTidy_CircleReducer::replaceEdgeCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                                              const occ::handle<StepGeom_Circle>&    theNewEntity,
                                              const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepShape_EdgeCurve> aSharing = occ::down_cast<StepShape_EdgeCurve>(theSharing);
  if (aSharing->EdgeGeometry() == theOldEntity)
  {
    aSharing->SetEdgeGeometry(theNewEntity);
    return true;
  }
  return false;
}

bool StepTidy_CircleReducer::replaceSurfaceCurve(const occ::handle<StepGeom_Circle>& theOldEntity,
                                                 const occ::handle<StepGeom_Circle>& theNewEntity,
                                                 const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_SurfaceCurve> aSharing = occ::down_cast<StepGeom_SurfaceCurve>(theSharing);
  if (aSharing->Curve3d() == theOldEntity)
  {
    aSharing->SetCurve3d(theNewEntity);
    return true;
  }
  return false;
}

bool StepTidy_CircleReducer::replaceSeamCurve(const occ::handle<StepGeom_Circle>&    theOldEntity,
                                              const occ::handle<StepGeom_Circle>&    theNewEntity,
                                              const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_SeamCurve> aSharing = occ::down_cast<StepGeom_SeamCurve>(theSharing);
  if (aSharing->Curve3d() == theOldEntity)
  {
    aSharing->SetCurve3d(theNewEntity);
    return true;
  }
  return false;
}
