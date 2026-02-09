#pragma once

#include <StepTidy_EntityReducer.hpp>
#include <StepTidy_CartesianPointHasher.hpp>

#include <StepGeom_CartesianPoint.hpp>

class StepTidy_CartesianPointReducer
    : public StepTidy_EntityReducer<StepGeom_CartesianPoint, StepTidy_CartesianPointHasher>
{
public:
  Standard_EXPORT StepTidy_CartesianPointReducer(const occ::handle<XSControl_WorkSession>& theWS);

private:
  static bool replaceAxis2Placement3d(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                      const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                      const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceVertexPoint(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                 const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                 const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceGeometricCurveSet(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                       const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                       const occ::handle<Standard_Transient>&      theSharing);

  static bool replacePresentationLayerAssignment(
    const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
    const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
    const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceStyledItem(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceBSplineCurveWithKnots(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                           const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                           const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceLine(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                          const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                          const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceBSplineSurfaceWithKnots(
    const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
    const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
    const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceAxis1Placement(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                    const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                    const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceRepresentation(const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
                                    const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
                                    const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceBSplineCurveWithKnotsAndRationalBSplineCurve(
    const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
    const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
    const occ::handle<Standard_Transient>&      theSharing);

  static bool replaceBSplineSurfaceWithKnotsAndRationalBSplineSurface(
    const occ::handle<StepGeom_CartesianPoint>& theOldEntity,
    const occ::handle<StepGeom_CartesianPoint>& theNewEntity,
    const occ::handle<Standard_Transient>&      theSharing);
};
