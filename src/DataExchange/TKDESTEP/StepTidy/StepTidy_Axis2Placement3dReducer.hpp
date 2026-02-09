#pragma once

#include <StepTidy_EntityReducer.hpp>
#include <StepTidy_Axis2Placement3dHasher.hpp>

#include <StepGeom_Axis2Placement3d.hpp>

class StepTidy_Axis2Placement3dReducer
    : public StepTidy_EntityReducer<StepGeom_Axis2Placement3d, StepTidy_Axis2Placement3dHasher>
{
public:
  Standard_EXPORT StepTidy_Axis2Placement3dReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replacePlane(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                           const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                           const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceItemDefinedTransformation(
    const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
    const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
    const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceCylindricalSurface(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                                        const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                                        const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceShapeRepresentation(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                                         const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                                         const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceConstructiveGeometryRepresentation(
    const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
    const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
    const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceCircle(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                            const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                            const occ::handle<Standard_Transient>&        theSharing);

  static bool replacePresentationLayerAssignment(
    const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
    const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
    const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceStyledItem(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                                const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                                const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceEllipse(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                             const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                             const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceConicalSurface(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                                    const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                                    const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceToroidalSurface(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                                     const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                                     const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceAdvancedBrepShapeRepresentation(
    const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
    const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
    const occ::handle<Standard_Transient>&        theSharing);

  static bool replaceSphericalSurface(const occ::handle<StepGeom_Axis2Placement3d>& theOldEntity,
                                      const occ::handle<StepGeom_Axis2Placement3d>& theNewEntity,
                                      const occ::handle<Standard_Transient>&        theSharing);
};
