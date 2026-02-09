

#include <StepTidy_LineReducer.hpp>

#include <Interface_Graph.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepGeom_TrimmedCurve.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <StepGeom_SeamCurve.hpp>

StepTidy_LineReducer::StepTidy_LineReducer(const occ::handle<XSControl_WorkSession>& theWS)
    : StepTidy_EntityReducer<StepGeom_Line, StepTidy_LineHasher>(theWS)
{
  registerReplacer(STANDARD_TYPE(StepShape_EdgeCurve), replaceEdgeCurve);
  registerReplacer(STANDARD_TYPE(StepGeom_TrimmedCurve), replaceTrimmedCurve);
  registerReplacer(STANDARD_TYPE(StepGeom_SurfaceCurve), replaceSurfaceCurve);
  registerReplacer(STANDARD_TYPE(StepRepr_DefinitionalRepresentation),
                   replaceDefinitionalRepresentation);
  registerReplacer(STANDARD_TYPE(StepGeom_SeamCurve), replaceSeamCurve);
}

bool StepTidy_LineReducer::replaceEdgeCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                            const occ::handle<StepGeom_Line>&      theNewEntity,
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

bool StepTidy_LineReducer::replaceTrimmedCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                               const occ::handle<StepGeom_Line>&      theNewEntity,
                                               const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepGeom_TrimmedCurve> aSharing = occ::down_cast<StepGeom_TrimmedCurve>(theSharing);
  if (aSharing->BasisCurve() == theOldEntity)
  {
    aSharing->SetBasisCurve(theNewEntity);
    return true;
  }
  return false;
}

bool StepTidy_LineReducer::replaceSurfaceCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                               const occ::handle<StepGeom_Line>&      theNewEntity,
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

bool StepTidy_LineReducer::replaceDefinitionalRepresentation(
  const occ::handle<StepGeom_Line>&      theOldEntity,
  const occ::handle<StepGeom_Line>&      theNewEntity,
  const occ::handle<Standard_Transient>& theSharing)
{
  occ::handle<StepRepr_DefinitionalRepresentation> aSharing =
    occ::down_cast<StepRepr_DefinitionalRepresentation>(theSharing);
  bool                                                                       isReplaced = false;
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> anItems =
    aSharing->Items();
  for (int anIndex = 1; anIndex <= aSharing->NbItems(); ++anIndex)
  {
    const occ::handle<StepRepr_RepresentationItem> aRepItem = anItems->Value(anIndex);
    if (aRepItem == theOldEntity)
    {
      anItems->SetValue(anIndex, theNewEntity);
      isReplaced = true;
    }
  }
  return isReplaced;
}

bool StepTidy_LineReducer::replaceSeamCurve(const occ::handle<StepGeom_Line>&      theOldEntity,
                                            const occ::handle<StepGeom_Line>&      theNewEntity,
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
