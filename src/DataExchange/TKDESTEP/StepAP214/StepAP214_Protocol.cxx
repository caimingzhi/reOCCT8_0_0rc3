// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

//: n5 abv 15 Feb 99: S4132: added complex type bounded_curve + surface_curve
//: j4 gka 11 Mar 99 S4134 :  added new types for DIS
//    gka 09.04.99: S4136: new name of parameter write.step.schema

#include <StepAP214_Protocol.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_Protocol, StepData_Protocol)

static const char* schemaAP214CD  = "AUTOMOTIVE_DESIGN_CC2 { 1 2 10303 214 -1 1 5 4 }";
static const char* schemaAP214DIS = "AUTOMOTIVE_DESIGN { 1 2 10303 214 0 1 1 1 }";
static const char* schemaAP214IS  = "AUTOMOTIVE_DESIGN { 1 0 10303 214 1 1 1 1 }";
static const char* schemaAP203    = "CONFIG_CONTROL_DESIGN";
static const char* schemaAP242DIS =
  "AP242_MANAGED_MODEL_BASED_3D_ENGINEERING_MIM_LF {1 0 10303 442 1 1 4 }";

#include <HeaderSection_Protocol.hpp>
#include <StepData_StepModel.hpp>

#include <StepShape_AdvancedBrepShapeRepresentation.hpp>
#include <StepShape_AdvancedFace.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_AnnotationCurveOccurrence.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_AnnotationFillArea.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_AnnotationFillAreaOccurrence.hpp>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
// Removed from CC1-Rev2 to Rev4 : <StepVisual_AnnotationSubfigureOccurrence.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_AnnotationSymbol.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_AnnotationSymbolOccurrence.hxx>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_AnnotationText.hpp>
#include <StepVisual_AnnotationTextOccurrence.hpp>

#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_ApprovalRelationship.hpp>
#include <StepBasic_ApprovalRole.hpp>
#include <StepBasic_ApprovalStatus.hpp>
#include <StepVisual_AreaInSet.hpp>
#include <StepAP214_AutoDesignActualDateAndTimeAssignment.hpp>
#include <StepAP214_AutoDesignActualDateAssignment.hpp>
#include <StepAP214_AutoDesignApprovalAssignment.hpp>
#include <StepAP214_AutoDesignDateAndPersonAssignment.hpp>
#include <StepAP214_AutoDesignGroupAssignment.hpp>
#include <StepAP214_AutoDesignNominalDateAndTimeAssignment.hpp>
#include <StepAP214_AutoDesignNominalDateAssignment.hpp>
#include <StepAP214_AutoDesignOrganizationAssignment.hpp>
#include <StepAP214_AutoDesignPersonAndOrganizationAssignment.hpp>
#include <StepAP214_AutoDesignPresentedItem.hpp>
#include <StepAP214_AutoDesignSecurityClassificationAssignment.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepAP214_AutoDesignViewArea.hxx>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepVisual_BackgroundColour.hpp>
#include <StepGeom_BezierCurve.hpp>
#include <StepGeom_BezierSurface.hpp>
#include <StepShape_Block.hpp>
#include <StepShape_BooleanResult.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <StepShape_BoxDomain.hpp>
#include <StepShape_BoxedHalfSpace.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepBasic_CalendarDate.hpp>
#include <StepVisual_CameraModelD2.hpp>
#include <StepVisual_CameraUsage.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_Circle.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_ColourRgb.hpp>
#include <StepVisual_ColourSpecification.hpp>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
// Removed from CC1-Rev2 to Rev4 : <StepVisual_CompositeTextWithAssociatedCurves.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_CompositeTextWithBlankingBox.hxx>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_CompositeTextWithExtent.hpp>

#include <StepGeom_Conic.hpp>
#include <StepGeom_ConicalSurface.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepVisual_ContextDependentInvisibility.hpp>
#include <StepVisual_ContextDependentOverRidingStyledItem.hpp>
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepShape_CsgRepresentation.hxx>
#include <StepShape_CsgShapeRepresentation.hpp>
#include <StepShape_CsgSolid.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepGeom_CurveReplica.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_CurveStyleFont.hpp>
#include <StepVisual_CurveStyleFontPattern.hpp>
#include <StepGeom_CylindricalSurface.hpp>
#include <StepBasic_Date.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateRole.hpp>
#include <StepBasic_DateTimeRole.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DefinedSymbol.hxx>
#include <StepGeom_DegenerateToroidalSurface.hpp>
#include <StepRepr_DescriptiveRepresentationItem.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DimensionCurve.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DimensionCurveTerminator.hxx>
#include <StepBasic_DimensionalExponents.hpp>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_DraughtingAnnotationOccurrence.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DraughtingCallout.hpp>
#include <StepVisual_DraughtingPreDefinedColour.hpp>
#include <StepVisual_DraughtingPreDefinedCurveFont.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DraughtingSubfigureRepresentation.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DraughtingSymbolRepresentation.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DraughtingTextLiteralWithDelineation.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DrawingDefinition.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_DrawingRevision.hxx>
#include <StepShape_EdgeCurve.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepGeom_ElementarySurface.hpp>
#include <StepGeom_Ellipse.hpp>
#include <StepGeom_EvaluatedDegeneratePcurve.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepVisual_ExternallyDefinedCurveFont.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_ExternallyDefinedHatchStyle.hxx>
#include <StepBasic_ExternallyDefinedItem.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_ExternallyDefinedSymbol.hxx>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_ExternallyDefinedTextFont.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_ExternallyDefinedTileStyle.hxx>
#include <StepShape_ExtrudedAreaSolid.hpp>
#include <StepShape_Face.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepShape_FaceBasedSurfaceModel.hpp>
#include <StepShape_FaceBound.hpp>
#include <StepShape_FaceOuterBound.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepShapeRepresentation.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_FillAreaStyleColour.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_FillAreaStyleHatching.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_FillAreaStyleTileSymbolWithStyle.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_FillAreaStyleTiles.hxx>
#include <StepRepr_FunctionallyDefinedTransformation.hpp>
#include <StepGeom_GeometricRepresentationContext.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepShape_GeometricallyBoundedSurfaceShapeRepresentation.hpp>
#include <StepShape_GeometricallyBoundedWireframeShapeRepresentation.hpp>
#include <StepRepr_GlobalUncertaintyAssignedContext.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <StepBasic_GeneralPropertyAssociation.hpp>
#include <StepBasic_GeneralPropertyRelationship.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <StepShape_HalfSpaceSolid.hpp>
#include <StepGeom_Hyperbola.hpp>
#include <StepGeom_IntersectionCurve.hpp>
#include <StepVisual_Invisibility.hpp>
#include <StepBasic_LengthUnit.hpp>
#include <StepGeom_Line.hpp>
#include <StepBasic_LocalTime.hpp>
#include <StepShape_Loop.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>
#include <StepShape_ManifoldSurfaceShapeRepresentation.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationArea.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_MechanicalDesignPresentationArea.hxx>
#include <StepBasic_NamedUnit.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepShape_NonManifoldSurfaceShapeRepresentation.hpp>
#include <StepGeom_OffsetCurve3d.hpp>
#include <StepGeom_OffsetSurface.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepAP214_OneDirectionRepeatFactor.hxx>
#include <StepBasic_OrdinalDate.hpp>
#include <StepBasic_OrganizationRole.hpp>
#include <StepBasic_OrganizationalAddress.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_OrientedFace.hpp>
#include <StepShape_OrientedOpenShell.hpp>
#include <StepShape_OrientedPath.hpp>
#include <StepGeom_OuterBoundaryCurve.hpp>
#include <StepVisual_OverRidingStyledItem.hpp>
#include <StepGeom_Parabola.hpp>
#include <StepRepr_ParametricRepresentationContext.hpp>
#include <StepShape_Path.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>
#include <StepBasic_PersonalAddress.hpp>
#include <StepGeom_Placement.hpp>
#include <StepVisual_PlanarBox.hpp>
#include <StepVisual_PlanarExtent.hpp>
#include <StepGeom_Plane.hpp>
#include <StepBasic_PlaneAngleUnit.hpp>
#include <StepGeom_Point.hpp>
#include <StepGeom_PointReplica.hpp>
#include <StepVisual_PointStyle.hpp>
#include <StepShape_PolyLoop.hpp>
#include <StepGeom_Polyline.hpp>
#include <StepVisual_PreDefinedColour.hpp>
#include <StepVisual_PreDefinedCurveFont.hpp>
#include <StepVisual_PreDefinedItem.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_PreDefinedSymbol.hxx>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_PreDefinedTextFont.hpp>

#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_PresentationRepresentation.hpp>
#include <StepVisual_PresentationSet.hpp>
#include <StepVisual_PresentationSize.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <StepVisual_PresentationStyleByContext.hpp>
#include <StepVisual_PresentationView.hpp>
#include <StepBasic_MechanicalContext.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_ProductDataRepresentationView.hxx>
#include <StepBasic_ProductDefinitionFormationWithSpecifiedSource.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepBasic_ProductType.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepGeom_QuasiUniformCurve.hpp>
#include <StepGeom_QuasiUniformSurface.hpp>
#include <StepBasic_RatioMeasureWithUnit.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <StepGeom_RectangularCompositeSurface.hpp>
#include <StepAP214_RepItemGroup.hpp>
#include <StepGeom_ReparametrisedCompositeCurveSegment.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationMap.hpp>
#include <StepShape_RevolvedAreaSolid.hpp>
#include <StepShape_RightAngularWedge.hpp>
#include <StepShape_RightCircularCone.hpp>
#include <StepShape_RightCircularCylinder.hpp>
#include <StepGeom_SeamCurve.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepBasic_SecurityClassificationLevel.hpp>
#include <StepRepr_FeatureForDatumTargetRelationship.hpp>
#include <StepRepr_ShapeAspectTransition.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>
#include <StepBasic_SolidAngleMeasureWithUnit.hpp>
#include <StepShape_SolidModel.hpp>
#include <StepShape_SolidReplica.hpp>
#include <StepShape_Sphere.hpp>
#include <StepGeom_SphericalSurface.hpp>
#include <StepVisual_StyledItem.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_SurfaceOfRevolution.hpp>
#include <StepGeom_SurfaceCurveAndBoundedCurve.hpp>
#include <StepGeom_SurfacePatch.hpp>
#include <StepGeom_SurfaceReplica.hpp>
#include <StepVisual_SurfaceSideStyle.hpp>
#include <StepVisual_SurfaceStyleBoundary.hpp>
#include <StepVisual_SurfaceStyleControlGrid.hpp>
#include <StepVisual_SurfaceStyleFillArea.hpp>
#include <StepVisual_SurfaceStyleParameterLine.hpp>
#include <StepVisual_SurfaceStyleSegmentationCurve.hpp>
#include <StepVisual_SurfaceStyleSilhouette.hpp>
#include <StepVisual_SurfaceStyleUsage.hpp>
#include <StepShape_SweptAreaSolid.hpp>
#include <StepGeom_SweptSurface.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_SymbolColour.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_SymbolRepresentation.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_SymbolRepresentationMap.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_SymbolStyle.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_SymbolTarget.hxx>
#include <StepVisual_Template.hpp>
#include <StepVisual_TemplateInstance.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_TerminatorSymbol.hxx>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_TextLiteral.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_TextLiteralWithAssociatedCurves.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_TextLiteralWithBlankingBox.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_TextLiteralWithDelineation.hxx>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_TextLiteralWithExtent.hxx>
// Removed from CC1-Rev2 to CC1-Rev4, re-added CC2-Rev4 :
#include <StepVisual_TextStyleForDefinedFont.hpp>
#include <StepVisual_TextStyleWithBoxCharacteristics.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepVisual_TextStyleWithMirror.hxx>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <StepShape_Torus.hpp>
#include <StepShape_TransitionalShapeRepresentation.hpp>
// Removed from CC1-Rev2 to Rev4 : <StepAP214_TwoDirectionRepeatFactor.hxx>
#include <StepBasic_UncertaintyMeasureWithUnit.hpp>
#include <StepGeom_UniformCurve.hpp>
#include <StepGeom_UniformSurface.hpp>
#include <StepGeom_Vector.hpp>
#include <StepShape_Vertex.hpp>
#include <StepShape_VertexLoop.hpp>
#include <StepShape_VertexPoint.hpp>
#include <StepVisual_ViewVolume.hpp>
#include <StepBasic_WeekOfYearAndDayDate.hpp>
#include <StepGeom_UniformCurveAndRationalBSplineCurve.hpp>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <StepGeom_QuasiUniformCurveAndRationalBSplineCurve.hpp>
#include <StepGeom_BezierCurveAndRationalBSplineCurve.hpp>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp>
#include <StepGeom_UniformSurfaceAndRationalBSplineSurface.hpp>
#include <StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface.hpp>
#include <StepGeom_BezierSurfaceAndRationalBSplineSurface.hpp>
#include <StepBasic_SiUnitAndLengthUnit.hpp>
#include <StepBasic_SiUnitAndPlaneAngleUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndLengthUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndPlaneAngleUnit.hpp>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hpp>
#include <StepShape_LoopAndPath.hpp>

// Added by FMA (for Rev4)
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp>
#include <StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.hpp>
#include <StepBasic_ConversionBasedUnitAndSolidAngleUnit.hpp>
#include <StepBasic_SolidAngleUnit.hpp>
#include <StepBasic_SiUnitAndSolidAngleUnit.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>

// Added by CKY (OCT-1996 for CC1-Rev4)
#include <StepBasic_DesignContext.hpp>

// Added from CC1-Rev2 to Rev4 (MAR-1997)
#include <StepBasic_TimeMeasureWithUnit.hpp>
#include <StepBasic_RatioUnit.hpp>
#include <StepBasic_TimeUnit.hpp>
#include <StepBasic_SiUnitAndRatioUnit.hpp>
#include <StepBasic_SiUnitAndTimeUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndRatioUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndTimeUnit.hpp>
#include <StepBasic_ApprovalDateTime.hpp>
#include <StepVisual_CameraImage2dWithScale.hpp>
#include <StepVisual_CameraImage3dWithScale.hpp>
#include <StepGeom_CartesianTransformationOperator2d.hpp>
#include <StepBasic_DerivedUnit.hpp>
#include <StepBasic_DerivedUnitElement.hpp>
#include <StepVisual_PresentedItemRepresentation.hpp>
#include <StepVisual_PresentationLayerUsage.hpp>

//  Added by CKY (JUL-1998) for AP214 CC1 -> CC2

#include <StepAP214_AutoDesignDocumentReference.hpp>
#include <StepBasic_DigitalDocument.hpp>
#include <StepBasic_DocumentRelationship.hpp>
#include <StepBasic_DocumentType.hpp>
#include <StepBasic_DocumentUsageConstraint.hpp>

#include <StepBasic_ProductDefinitionWithAssociatedDocuments.hpp>
#include <StepBasic_PhysicallyModeledProductDefinition.hpp>

#include <StepRepr_MakeFromUsageOption.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_PromissoryUsageOccurrence.hpp>
#include <StepRepr_QuantifiedAssemblyComponentUsage.hpp>
#include <StepRepr_SpecifiedHigherUsageOccurrence.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <StepRepr_SuppliedPartRelationship.hpp>
#include <StepRepr_ExternallyDefinedRepresentation.hpp>
#include <StepRepr_ShapeRepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_MaterialDesignation.hpp>

#include <StepShape_ContextDependentShapeRepresentation.hpp>

// Added by CKY (Resources)
#include <HeaderSection.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
// Added from CC2 to DIS March 1999 j4

#include <StepAP214_AppliedDateAndTimeAssignment.hpp>
#include <StepAP214_AppliedDateAssignment.hpp>
#include <StepAP214_AppliedApprovalAssignment.hpp>
#include <StepAP214_AppliedGroupAssignment.hpp>
#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_AppliedPersonAndOrganizationAssignment.hpp>
#include <StepAP214_AppliedPresentedItem.hpp>
#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepAP214_AppliedDocumentReference.hpp>

// Added by ABV 08.09.99 for CAX TRJ 2 (validation properties)
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepShape_ExtrudedFaceSolid.hpp>
#include <StepShape_RevolvedFaceSolid.hpp>
#include <StepShape_SweptFaceSolid.hpp>
#include <StepBasic_AreaUnit.hpp>
#include <StepBasic_VolumeUnit.hpp>
#include <StepBasic_SiUnitAndAreaUnit.hpp>
#include <StepBasic_SiUnitAndVolumeUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndAreaUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndVolumeUnit.hpp>

// Added by ABV 10.11.99 for AP203
#include <StepBasic_Action.hpp>
#include <StepBasic_ActionMethod.hpp>
#include <StepAP203_CcDesignApproval.hpp>
#include <StepAP203_CcDesignCertification.hpp>
#include <StepAP203_CcDesignContract.hpp>
#include <StepAP203_CcDesignDateAndTimeAssignment.hpp>
#include <StepAP203_CcDesignPersonAndOrganizationAssignment.hpp>
#include <StepAP203_CcDesignSecurityClassification.hpp>
#include <StepAP203_CcDesignSpecificationReference.hpp>
#include <StepBasic_Certification.hpp>
#include <StepBasic_CertificationAssignment.hpp>
#include <StepBasic_CertificationType.hpp>
#include <StepAP203_Change.hpp>
#include <StepAP203_ChangeRequest.hpp>
#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationEffectivity.hpp>
#include <StepBasic_Contract.hpp>
#include <StepBasic_ContractAssignment.hpp>
#include <StepBasic_ContractType.hpp>
#include <StepRepr_ProductConcept.hpp>
#include <StepBasic_ProductConceptContext.hpp>
#include <StepAP203_StartRequest.hpp>
#include <StepAP203_StartWork.hpp>
#include <StepBasic_VersionedActionRequest.hpp>
#include <StepBasic_ProductCategoryRelationship.hpp>
#include <StepBasic_ActionRequestSolution.hpp>

// Added by ABV 13.01.00 for CAX-IF TRJ3

// Added by ABV 18.04.00 for CAX-IF TRJ4 (dimensions)
#include <StepShape_AngularLocation.hpp>
#include <StepShape_AngularSize.hpp>
#include <StepShape_DimensionalCharacteristicRepresentation.hpp>
#include <StepShape_DimensionalLocation.hpp>
#include <StepShape_DimensionalLocationWithPath.hpp>
#include <StepShape_DimensionalSize.hpp>
#include <StepShape_DimensionalSizeWithPath.hpp>
#include <StepShape_ShapeDimensionRepresentation.hpp>

// Added by ABV 10.05.00 for CAX-IF TRJ4 (external references)
#include <StepBasic_DocumentRepresentationType.hpp>
#include <StepBasic_ObjectRole.hpp>
#include <StepBasic_RoleAssociation.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <StepBasic_EffectivityAssignment.hpp>
#include <StepBasic_NameAssignment.hpp>
#include <StepAP214_ExternallyDefinedClass.hpp>
#include <StepAP214_ExternallyDefinedGeneralProperty.hpp>
#include <StepAP214_AppliedExternalIdentificationAssignment.hpp>
#include <StepShape_DefinitionalRepresentationAndShapeRepresentation.hpp>

// Added by CKY , 25 APR 2001 for Dimensional Tolerances (CAX-IF TRJ7)
#include <StepRepr_Extension.hpp>
#include <StepShape_DirectedDimensionalLocation.hpp>
#include <StepShape_LimitsAndFits.hpp>
#include <StepShape_ToleranceValue.hpp>
#include <StepShape_MeasureQualification.hpp>
#include <StepShape_PlusMinusTolerance.hpp>
#include <StepShape_PrecisionQualifier.hpp>
#include <StepShape_TypeQualifier.hpp>
#include <StepShape_QualifiedRepresentationItem.hpp>
#include <StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem.hpp>
#include <StepRepr_ValueRange.hpp>
#include <StepRepr_ShapeAspectDerivingRelationship.hpp>

// Added by ABV 28.12.01 for CAX-IF TRJ9 (edge_based_wireframe_model)
#include <StepShape_CompoundShapeRepresentation.hpp>
#include <StepShape_ConnectedFaceShapeRepresentation.hpp>
#include <StepShape_EdgeBasedWireframeModel.hpp>
#include <StepShape_EdgeBasedWireframeShapeRepresentation.hpp>
#include <StepShape_FaceBasedSurfaceModel.hpp>
#include <StepShape_NonManifoldSurfaceShapeRepresentation.hpp>
#include <StepGeom_OrientedSurface.hpp>
#include <StepShape_Subface.hpp>
#include <StepShape_Subedge.hpp>
#include <StepShape_SeamEdge.hpp>
#include <StepShape_ConnectedFaceSubSet.hpp>

// AP209 types
#include <StepBasic_EulerAngles.hpp>
#include <StepBasic_MassUnit.hpp>
#include <StepBasic_ThermodynamicTemperatureUnit.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepElement_Curve3dElementDescriptor.hpp>
#include <StepElement_CurveElementSectionDerivedDefinitions.hpp>
#include <StepElement_ElementDescriptor.hpp>
#include <StepElement_ElementMaterial.hpp>
#include <StepElement_Surface3dElementDescriptor.hpp>
#include <StepElement_SurfaceElementProperty.hpp>
#include <StepElement_SurfaceSectionFieldConstant.hpp>
#include <StepElement_SurfaceSectionFieldVarying.hpp>
#include <StepElement_UniformSurfaceSection.hpp>
#include <StepElement_Volume3dElementDescriptor.hpp>
#include <StepFEA_AlignedCurve3dElementCoordinateSystem.hpp>
#include <StepFEA_ArbitraryVolume3dElementCoordinateSystem.hpp>
#include <StepFEA_Curve3dElementProperty.hpp>
#include <StepFEA_Curve3dElementRepresentation.hpp>
#include <StepFEA_CurveElementEndOffset.hpp>
#include <StepFEA_CurveElementEndRelease.hpp>
#include <StepFEA_CurveElementInterval.hpp>
#include <StepFEA_CurveElementIntervalConstant.hpp>
#include <StepFEA_DummyNode.hpp>
#include <StepFEA_CurveElementLocation.hpp>
#include <StepFEA_ElementGeometricRelationship.hpp>
#include <StepFEA_ElementGroup.hpp>
#include <StepFEA_ElementRepresentation.hpp>
#include <StepFEA_FeaAreaDensity.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>
#include <StepFEA_FeaGroup.hpp>
#include <StepFEA_FeaLinearElasticity.hpp>
#include <StepFEA_FeaMassDensity.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentation.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
#include <StepFEA_FeaModel3d.hpp>
#include <StepFEA_FeaMoistureAbsorption.hpp>
#include <StepFEA_FeaParametricPoint.hpp>
#include <StepFEA_FeaRepresentationItem.hpp>
#include <StepFEA_FeaSecantCoefficientOfLinearThermalExpansion.hpp>
#include <StepFEA_FeaShellBendingStiffness.hpp>
#include <StepFEA_FeaShellMembraneBendingCouplingStiffness.hpp>
#include <StepFEA_FeaShellMembraneStiffness.hpp>
#include <StepFEA_FeaShellShearStiffness.hpp>
#include <StepFEA_GeometricNode.hpp>
#include <StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.hpp>
#include <StepFEA_NodeGroup.hpp>
#include <StepFEA_NodeRepresentation.hpp>
#include <StepFEA_NodeSet.hpp>
#include <StepFEA_NodeWithSolutionCoordinateSystem.hpp>
#include <StepFEA_NodeWithVector.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateDirection.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateSystem.hpp>
#include <StepFEA_ParametricSurface3dElementCoordinateSystem.hpp>
#include <StepFEA_Surface3dElementRepresentation.hpp>
#include <StepFEA_Volume3dElementRepresentation.hpp>
#include <StepRepr_DataEnvironment.hpp>
#include <StepRepr_MaterialPropertyRepresentation.hpp>
#include <StepRepr_PropertyDefinitionRelationship.hpp>
#include <StepShape_PointRepresentation.hpp>
#include <StepRepr_MaterialProperty.hpp>
#include <StepFEA_FeaModelDefinition.hpp>
#include <StepFEA_FreedomAndCoefficient.hpp>
#include <StepFEA_FreedomsList.hpp>
#include <StepBasic_ProductDefinitionFormationRelationship.hpp>
#include <StepFEA_NodeDefinition.hpp>
#include <StepRepr_StructuralResponseProperty.hpp>
#include <StepRepr_StructuralResponsePropertyDefinitionRepresentation.hpp>

#include <StepBasic_SiUnitAndMassUnit.hpp>
#include <StepBasic_SiUnitAndThermodynamicTemperatureUnit.hpp>

#include <StepFEA_AlignedSurface3dElementCoordinateSystem.hpp>
#include <StepFEA_ConstantSurface3dElementCoordinateSystem.hpp>

// 23.01.2003
#include <StepFEA_CurveElementIntervalLinearlyVarying.hpp>
#include <StepFEA_FeaCurveSectionGeometricRelationship.hpp>
#include <StepFEA_FeaSurfaceSectionGeometricRelationship.hpp>

// added PTV TRJ11 8.02.2003
#include <StepBasic_DocumentProductEquivalence.hpp>

// TR12J 4.06.2003 G&DT entities
#include <StepShape_ShapeRepresentationWithParameters.hpp>
#include <StepDimTol_AngularityTolerance.hpp>
#include <StepDimTol_ConcentricityTolerance.hpp>
#include <StepDimTol_CircularRunoutTolerance.hpp>
#include <StepDimTol_CoaxialityTolerance.hpp>
#include <StepDimTol_CylindricityTolerance.hpp>
#include <StepDimTol_FlatnessTolerance.hpp>
#include <StepDimTol_LineProfileTolerance.hpp>
#include <StepDimTol_ParallelismTolerance.hpp>
#include <StepDimTol_PerpendicularityTolerance.hpp>
#include <StepDimTol_PositionTolerance.hpp>
#include <StepDimTol_RoundnessTolerance.hpp>
#include <StepDimTol_StraightnessTolerance.hpp>
#include <StepDimTol_SurfaceProfileTolerance.hpp>
#include <StepDimTol_SymmetryTolerance.hpp>
#include <StepDimTol_TotalRunoutTolerance.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceRelationship.hpp>
#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepDimTol_ModifiedGeometricTolerance.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepDimTol_DatumFeature.hpp>
#include <StepDimTol_DatumReference.hpp>
#include <StepDimTol_CommonDatum.hpp>
#include <StepDimTol_PlacedDatumTargetFeature.hpp>

#include <StepRepr_ReprItemAndLengthMeasureWithUnit.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.hpp>

// added by skl 10.02.2004 for TRJ13
#include <StepBasic_ConversionBasedUnitAndMassUnit.hpp>
#include <StepBasic_MassMeasureWithUnit.hpp>
#include <StepBasic_CharacterizedObject.hpp>

// Added by ika for GD&T AP242
#include <StepRepr_Apex.hpp>
#include <StepRepr_CentreOfSymmetry.hpp>
#include <StepRepr_GeometricAlignment.hpp>
#include <StepRepr_ParallelOffset.hpp>
#include <StepRepr_PerpendicularTo.hpp>
#include <StepRepr_Tangent.hpp>
#include <StepAP242_GeometricItemSpecificUsage.hpp>
#include <StepAP242_IdAttribute.hpp>
#include <StepAP242_ItemIdentifiedRepresentationUsage.hpp>
#include <StepRepr_AllAroundShapeAspect.hpp>
#include <StepRepr_BetweenShapeAspect.hpp>
#include <StepRepr_CompositeGroupShapeAspect.hpp>
#include <StepRepr_ContinuosShapeAspect.hpp>
#include <StepDimTol_GeometricToleranceWithDefinedAreaUnit.hpp>
#include <StepDimTol_GeometricToleranceWithDefinedUnit.hpp>
#include <StepDimTol_GeometricToleranceWithMaximumTolerance.hpp>
#include <StepDimTol_GeometricToleranceWithModifiers.hpp>
#include <StepDimTol_UnequallyDisposedGeometricTolerance.hpp>
#include <StepDimTol_NonUniformZoneDefinition.hpp>
#include <StepDimTol_ProjectedZoneDefinition.hpp>
#include <StepDimTol_RunoutZoneDefinition.hpp>
#include <StepDimTol_RunoutZoneOrientation.hpp>
#include <StepDimTol_ToleranceZone.hpp>
#include <StepDimTol_ToleranceZoneDefinition.hpp>
#include <StepDimTol_ToleranceZoneForm.hpp>
#include <StepShape_ValueFormatTypeQualifier.hpp>
#include <StepDimTol_DatumReferenceElement.hpp>
#include <StepDimTol_DatumReferenceModifierWithValue.hpp>
#include <StepDimTol_DatumSystem.hpp>
#include <StepDimTol_GeneralDatumReference.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol.hpp>
#include <StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp.hpp>
#include <StepRepr_CompShAspAndDatumFeatAndShAsp.hpp>
#include <StepRepr_BooleanRepresentationItem.hpp>
#include <StepRepr_IntegerRepresentationItem.hpp>
#include <StepRepr_RealRepresentationItem.hpp>
#include <StepRepr_ValueRepresentationItem.hpp>
#include <StepAP242_DraughtingModelItemAssociation.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthMaxTol.hpp>
#include <StepVisual_AnnotationPlane.hpp>
#include <StepVisual_DraughtingCallout.hpp>

#include <StepVisual_TessellatedAnnotationOccurrence.hpp>
#include <StepVisual_TessellatedGeometricSet.hpp>
#include <StepVisual_TessellatedCurveSet.hpp>
#include <StepVisual_RepositionedTessellatedGeometricSet.hpp>
#include <StepVisual_RepositionedTessellatedItem.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepRepr_CharacterizedRepresentation.hpp>
#include <StepRepr_ConstructiveGeometryRepresentation.hpp>
#include <StepRepr_ConstructiveGeometryRepresentationRelationship.hpp>
#include <StepRepr_MechanicalDesignAndDraughtingRelationship.hpp>
#include <StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel.hpp>
#include <StepVisual_AnnotationFillArea.hpp>
#include <StepVisual_AnnotationFillAreaOccurrence.hpp>
#include <StepVisual_CameraModelD3MultiClipping.hpp>
#include <StepVisual_CameraModelD3MultiClippingIntersection.hpp>
#include <StepVisual_CameraModelD3MultiClippingUnion.hpp>
#include <StepVisual_AnnotationCurveOccurrenceAndGeomReprItem.hpp>

// Added for kinematics implementation
#include <StepRepr_RepresentationReference.hpp>
#include <StepGeom_SuParameters.hpp>
#include <StepKinematics_RotationAboutDirection.hpp>
#include <StepKinematics_ActuatedKinematicPair.hpp>
#include <StepKinematics_ContextDependentKinematicLinkRepresentation.hpp>
#include <StepKinematics_CylindricalPairValue.hpp>
#include <StepKinematics_CylindricalPairWithRange.hpp>
#include <StepKinematics_FullyConstrainedPair.hpp>
#include <StepKinematics_GearPairValue.hpp>
#include <StepKinematics_GearPairWithRange.hpp>
#include <StepKinematics_HomokineticPair.hpp>
#include <StepKinematics_KinematicLinkRepresentationAssociation.hpp>
#include <StepKinematics_KinematicPropertyMechanismRepresentation.hpp>
#include <StepKinematics_KinematicTopologyDirectedStructure.hpp>
#include <StepKinematics_KinematicTopologyNetworkStructure.hpp>
#include <StepKinematics_KinematicTopologyStructure.hpp>
#include <StepKinematics_LinearFlexibleAndPinionPair.hpp>
#include <StepKinematics_LinearFlexibleAndPlanarCurvePair.hpp>
#include <StepKinematics_LinearFlexibleLinkRepresentation.hpp>
#include <StepKinematics_LowOrderKinematicPair.hpp>
#include <StepKinematics_LowOrderKinematicPairValue.hpp>
#include <StepKinematics_LowOrderKinematicPairWithRange.hpp>
#include <StepKinematics_MechanismRepresentation.hpp>
#include <StepKinematics_OrientedJoint.hpp>
#include <StepKinematics_PairRepresentationRelationship.hpp>
#include <StepKinematics_PlanarCurvePairRange.hpp>
#include <StepKinematics_PlanarPairValue.hpp>
#include <StepKinematics_PlanarPairWithRange.hpp>
#include <StepKinematics_PointOnPlanarCurvePairValue.hpp>
#include <StepKinematics_PointOnPlanarCurvePairWithRange.hpp>
#include <StepKinematics_PointOnSurfacePairValue.hpp>
#include <StepKinematics_PointOnSurfacePairWithRange.hpp>
#include <StepKinematics_PrismaticPairValue.hpp>
#include <StepKinematics_PrismaticPairWithRange.hpp>
#include <StepKinematics_ProductDefinitionKinematics.hpp>
#include <StepKinematics_ProductDefinitionRelationshipKinematics.hpp>
#include <StepKinematics_RackAndPinionPairValue.hpp>
#include <StepKinematics_RackAndPinionPairWithRange.hpp>
#include <StepKinematics_RevolutePairValue.hpp>
#include <StepKinematics_RevolutePairWithRange.hpp>
#include <StepKinematics_RigidLinkRepresentation.hpp>
#include <StepKinematics_RollingCurvePair.hpp>
#include <StepKinematics_RollingCurvePairValue.hpp>
#include <StepKinematics_RollingSurfacePair.hpp>
#include <StepKinematics_RollingSurfacePairValue.hpp>
#include <StepKinematics_ScrewPairValue.hpp>
#include <StepKinematics_ScrewPairWithRange.hpp>
#include <StepKinematics_SlidingCurvePair.hpp>
#include <StepKinematics_SlidingCurvePairValue.hpp>
#include <StepKinematics_SlidingSurfacePair.hpp>
#include <StepKinematics_SlidingSurfacePairValue.hpp>
#include <StepKinematics_SphericalPairValue.hpp>
#include <StepKinematics_SphericalPairWithPinAndRange.hpp>
#include <StepKinematics_SphericalPairWithRange.hpp>
#include <StepKinematics_SurfacePairWithRange.hpp>
#include <StepKinematics_UnconstrainedPair.hpp>
#include <StepKinematics_UnconstrainedPairValue.hpp>
#include <StepKinematics_UniversalPair.hpp>
#include <StepKinematics_UniversalPairValue.hpp>
#include <StepKinematics_UniversalPairWithRange.hpp>
#include <StepKinematics_ActuatedKinPairAndOrderKinPair.hpp>
#include <StepKinematics_MechanismStateRepresentation.hpp>

#include <StepVisual_SurfaceStyleTransparent.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuse.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular.hpp>
#include <StepVisual_SurfaceStyleRenderingWithProperties.hpp>

#include <StepVisual_TessellatedConnectingEdge.hpp>
#include <StepVisual_TessellatedEdge.hpp>
#include <StepVisual_TessellatedPointSet.hpp>
#include <StepVisual_TessellatedShapeRepresentation.hpp>
#include <StepVisual_TessellatedShapeRepresentationWithAccuracyParameters.hpp>
#include <StepVisual_TessellatedShell.hpp>
#include <StepVisual_TessellatedSolid.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>
#include <StepVisual_TessellatedVertex.hpp>
#include <StepVisual_TessellatedWire.hpp>
#include <StepVisual_TriangulatedFace.hpp>
#include <StepVisual_ComplexTriangulatedFace.hpp>
#include <StepVisual_ComplexTriangulatedSurfaceSet.hpp>
#include <StepVisual_CubicBezierTessellatedEdge.hpp>
#include <StepVisual_CubicBezierTriangulatedFace.hpp>
#include <StepVisual_TriangulatedSurfaceSet.hpp>

static int                                                       THE_StepAP214_Protocol_init = 0;
static NCollection_DataMap<occ::handle<Standard_Transient>, int> types(819);

//=================================================================================================

StepAP214_Protocol::StepAP214_Protocol()
{
  if (THE_StepAP214_Protocol_init)
  {
    return;
  }
  THE_StepAP214_Protocol_init = 1;

  types.Bind(STANDARD_TYPE(StepBasic_Address), 1);
  types.Bind(STANDARD_TYPE(StepShape_AdvancedBrepShapeRepresentation), 2);
  types.Bind(STANDARD_TYPE(StepShape_AdvancedFace), 3);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationCurveOccurrence), 4);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationFillArea), 5);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationFillAreaOccurrence), 6);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationOccurrence), 7);
  //  types.Bind (STANDARD_TYPE(StepVisual_AnnotationSubfigureOccurrence), 8);
  //  types.Bind (STANDARD_TYPE(StepVisual_AnnotationSymbol), 9);
  //  types.Bind (STANDARD_TYPE(StepVisual_AnnotationSymbolOccurrence), 10);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationText), 11);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationTextOccurrence), 12);
  types.Bind(STANDARD_TYPE(StepBasic_ApplicationContext), 13);
  types.Bind(STANDARD_TYPE(StepBasic_ApplicationContextElement), 14);
  types.Bind(STANDARD_TYPE(StepBasic_ApplicationProtocolDefinition), 15);
  types.Bind(STANDARD_TYPE(StepBasic_Approval), 16);
  types.Bind(STANDARD_TYPE(StepBasic_ApprovalPersonOrganization), 18);
  types.Bind(STANDARD_TYPE(StepBasic_ApprovalRelationship), 19);
  types.Bind(STANDARD_TYPE(StepBasic_ApprovalRole), 20);
  types.Bind(STANDARD_TYPE(StepBasic_ApprovalStatus), 21);
  types.Bind(STANDARD_TYPE(StepVisual_AreaInSet), 22);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignActualDateAndTimeAssignment), 23);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignActualDateAssignment), 24);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignApprovalAssignment), 25);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignDateAndPersonAssignment), 26);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignGroupAssignment), 27);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignNominalDateAndTimeAssignment), 28);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignNominalDateAssignment), 29);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignOrganizationAssignment), 30);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignPersonAndOrganizationAssignment), 31);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignPresentedItem), 32);
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignSecurityClassificationAssignment), 33);
  //  types.Bind (STANDARD_TYPE(StepAP214_AutoDesignViewArea), 34);
  types.Bind(STANDARD_TYPE(StepGeom_Axis1Placement), 35);
  types.Bind(STANDARD_TYPE(StepGeom_Axis2Placement2d), 36);
  types.Bind(STANDARD_TYPE(StepGeom_Axis2Placement3d), 37);
  types.Bind(STANDARD_TYPE(StepGeom_BSplineCurve), 38);
  types.Bind(STANDARD_TYPE(StepGeom_BSplineCurveWithKnots), 39);
  types.Bind(STANDARD_TYPE(StepGeom_BSplineSurface), 40);
  types.Bind(STANDARD_TYPE(StepGeom_BSplineSurfaceWithKnots), 41);
  types.Bind(STANDARD_TYPE(StepVisual_BackgroundColour), 42);
  types.Bind(STANDARD_TYPE(StepGeom_BezierCurve), 43);
  types.Bind(STANDARD_TYPE(StepGeom_BezierSurface), 44);
  types.Bind(STANDARD_TYPE(StepShape_Block), 45);
  types.Bind(STANDARD_TYPE(StepShape_BooleanResult), 46);
  types.Bind(STANDARD_TYPE(StepGeom_BoundaryCurve), 47);
  types.Bind(STANDARD_TYPE(StepGeom_BoundedCurve), 48);
  types.Bind(STANDARD_TYPE(StepGeom_BoundedSurface), 49);
  types.Bind(STANDARD_TYPE(StepShape_BoxDomain), 50);
  types.Bind(STANDARD_TYPE(StepShape_BoxedHalfSpace), 51);
  types.Bind(STANDARD_TYPE(StepShape_BrepWithVoids), 52);
  types.Bind(STANDARD_TYPE(StepBasic_CalendarDate), 53);
  types.Bind(STANDARD_TYPE(StepVisual_CameraImage), 54);
  types.Bind(STANDARD_TYPE(StepVisual_CameraModel), 55);
  types.Bind(STANDARD_TYPE(StepVisual_CameraModelD2), 56);
  types.Bind(STANDARD_TYPE(StepVisual_CameraModelD3), 57);
  types.Bind(STANDARD_TYPE(StepVisual_CameraUsage), 58);
  types.Bind(STANDARD_TYPE(StepGeom_CartesianPoint), 59);
  types.Bind(STANDARD_TYPE(StepGeom_CartesianTransformationOperator), 60);
  types.Bind(STANDARD_TYPE(StepGeom_CartesianTransformationOperator3d), 61);
  types.Bind(STANDARD_TYPE(StepGeom_Circle), 62);
  types.Bind(STANDARD_TYPE(StepShape_ClosedShell), 63);
  types.Bind(STANDARD_TYPE(StepVisual_Colour), 64);
  types.Bind(STANDARD_TYPE(StepVisual_ColourRgb), 65);
  types.Bind(STANDARD_TYPE(StepVisual_ColourSpecification), 66);
  types.Bind(STANDARD_TYPE(StepGeom_CompositeCurve), 67);
  types.Bind(STANDARD_TYPE(StepGeom_CompositeCurveOnSurface), 68);
  types.Bind(STANDARD_TYPE(StepGeom_CompositeCurveSegment), 69);
  types.Bind(STANDARD_TYPE(StepVisual_CompositeText), 70);
  //  types.Bind (STANDARD_TYPE(StepVisual_CompositeTextWithAssociatedCurves), 71);
  //  types.Bind (STANDARD_TYPE(StepVisual_CompositeTextWithBlankingBox), 72);
  types.Bind(STANDARD_TYPE(StepVisual_CompositeTextWithExtent), 73);
  types.Bind(STANDARD_TYPE(StepGeom_Conic), 74);
  types.Bind(STANDARD_TYPE(StepGeom_ConicalSurface), 75);
  types.Bind(STANDARD_TYPE(StepShape_ConnectedFaceSet), 76);
  types.Bind(STANDARD_TYPE(StepVisual_ContextDependentInvisibility), 77);
  types.Bind(STANDARD_TYPE(StepVisual_ContextDependentOverRidingStyledItem), 78);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnit), 79);
  types.Bind(STANDARD_TYPE(StepBasic_CoordinatedUniversalTimeOffset), 80);
  //  types.Bind (STANDARD_TYPE(StepShape_CsgRepresentation), 81);
  types.Bind(STANDARD_TYPE(StepShape_CsgShapeRepresentation), 82);
  types.Bind(STANDARD_TYPE(StepShape_CsgSolid), 83);
  types.Bind(STANDARD_TYPE(StepGeom_Curve), 84);
  types.Bind(STANDARD_TYPE(StepGeom_CurveBoundedSurface), 85);
  types.Bind(STANDARD_TYPE(StepGeom_CurveReplica), 86);
  types.Bind(STANDARD_TYPE(StepVisual_CurveStyle), 87);
  types.Bind(STANDARD_TYPE(StepVisual_CurveStyleFont), 88);
  types.Bind(STANDARD_TYPE(StepVisual_CurveStyleFontPattern), 89);
  types.Bind(STANDARD_TYPE(StepGeom_CylindricalSurface), 90);
  types.Bind(STANDARD_TYPE(StepBasic_Date), 91);
  types.Bind(STANDARD_TYPE(StepBasic_DateAndTime), 92);
  types.Bind(STANDARD_TYPE(StepBasic_DateRole), 95);
  types.Bind(STANDARD_TYPE(StepBasic_DateTimeRole), 96);
  //  types.Bind (STANDARD_TYPE(StepVisual_DefinedSymbol), 97);
  types.Bind(STANDARD_TYPE(StepRepr_DefinitionalRepresentation), 98);
  types.Bind(STANDARD_TYPE(StepGeom_DegeneratePcurve), 99);
  types.Bind(STANDARD_TYPE(StepGeom_DegenerateToroidalSurface), 100);
  types.Bind(STANDARD_TYPE(StepRepr_DescriptiveRepresentationItem), 101);
  //  types.Bind (STANDARD_TYPE(StepVisual_DimensionCurve), 102);
  //  types.Bind (STANDARD_TYPE(StepVisual_DimensionCurveTerminator), 103);
  types.Bind(STANDARD_TYPE(StepBasic_DimensionalExponents), 104);
  types.Bind(STANDARD_TYPE(StepGeom_Direction), 105);
  types.Bind(STANDARD_TYPE(StepVisual_DraughtingAnnotationOccurrence), 106);
  types.Bind(STANDARD_TYPE(StepVisual_DraughtingCallout), 107);
  types.Bind(STANDARD_TYPE(StepVisual_DraughtingPreDefinedColour), 108);
  types.Bind(STANDARD_TYPE(StepVisual_DraughtingPreDefinedCurveFont), 109);
  //  types.Bind (STANDARD_TYPE(StepVisual_DraughtingSubfigureRepresentation), 110);
  //  types.Bind (STANDARD_TYPE(StepVisual_DraughtingSymbolRepresentation), 111);
  //  types.Bind (STANDARD_TYPE(StepVisual_DraughtingTextLiteralWithDelineation), 112);
  //  types.Bind (STANDARD_TYPE(StepVisual_DrawingDefinition), 113);
  //  types.Bind (STANDARD_TYPE(StepVisual_DrawingRevision), 114);
  types.Bind(STANDARD_TYPE(StepShape_Edge), 115);
  types.Bind(STANDARD_TYPE(StepShape_EdgeCurve), 116);
  types.Bind(STANDARD_TYPE(StepShape_EdgeLoop), 117);
  types.Bind(STANDARD_TYPE(StepGeom_ElementarySurface), 118);
  types.Bind(STANDARD_TYPE(StepGeom_Ellipse), 119);
  types.Bind(STANDARD_TYPE(StepGeom_EvaluatedDegeneratePcurve), 120);
  types.Bind(STANDARD_TYPE(StepBasic_ExternalSource), 121);
  types.Bind(STANDARD_TYPE(StepVisual_ExternallyDefinedCurveFont), 122);
  //  types.Bind (STANDARD_TYPE(StepVisual_ExternallyDefinedHatchStyle), 123);
  types.Bind(STANDARD_TYPE(StepBasic_ExternallyDefinedItem), 124);
  //  types.Bind (STANDARD_TYPE(StepVisual_ExternallyDefinedSymbol), 125);
  types.Bind(STANDARD_TYPE(StepVisual_ExternallyDefinedTextFont), 126);
  //  types.Bind (STANDARD_TYPE(StepVisual_ExternallyDefinedTileStyle), 127);
  types.Bind(STANDARD_TYPE(StepShape_ExtrudedAreaSolid), 128);
  types.Bind(STANDARD_TYPE(StepShape_Face), 129);
  //  types.Bind (STANDARD_TYPE(StepShape_FaceBasedSurfaceModel), 130);
  types.Bind(STANDARD_TYPE(StepShape_FaceBound), 131);
  types.Bind(STANDARD_TYPE(StepShape_FaceOuterBound), 132);
  types.Bind(STANDARD_TYPE(StepShape_FaceSurface), 133);
  types.Bind(STANDARD_TYPE(StepShape_FacetedBrep), 134);
  types.Bind(STANDARD_TYPE(StepShape_FacetedBrepShapeRepresentation), 135);
  types.Bind(STANDARD_TYPE(StepVisual_FillAreaStyle), 136);
  types.Bind(STANDARD_TYPE(StepVisual_FillAreaStyleColour), 137);
  //  types.Bind (STANDARD_TYPE(StepVisual_FillAreaStyleHatching), 138);
  //  types.Bind (STANDARD_TYPE(StepVisual_FillAreaStyleTileSymbolWithStyle), 139);
  //  types.Bind (STANDARD_TYPE(StepVisual_FillAreaStyleTiles), 140);
  types.Bind(STANDARD_TYPE(StepRepr_FunctionallyDefinedTransformation), 141);
  types.Bind(STANDARD_TYPE(StepShape_GeometricCurveSet), 142);
  types.Bind(STANDARD_TYPE(StepGeom_GeometricRepresentationContext), 143);
  types.Bind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem), 144);
  types.Bind(STANDARD_TYPE(StepShape_GeometricSet), 145);
  types.Bind(STANDARD_TYPE(StepShape_GeometricallyBoundedSurfaceShapeRepresentation), 146);
  types.Bind(STANDARD_TYPE(StepShape_GeometricallyBoundedWireframeShapeRepresentation), 147);
  types.Bind(STANDARD_TYPE(StepRepr_GlobalUncertaintyAssignedContext), 148);
  types.Bind(STANDARD_TYPE(StepRepr_GlobalUnitAssignedContext), 149);
  types.Bind(STANDARD_TYPE(StepBasic_Group), 150);
  types.Bind(STANDARD_TYPE(StepBasic_GroupRelationship), 152);
  types.Bind(STANDARD_TYPE(StepShape_HalfSpaceSolid), 153);
  types.Bind(STANDARD_TYPE(StepGeom_Hyperbola), 154);
  types.Bind(STANDARD_TYPE(StepGeom_IntersectionCurve), 155);
  types.Bind(STANDARD_TYPE(StepVisual_Invisibility), 156);
  types.Bind(STANDARD_TYPE(StepBasic_LengthMeasureWithUnit), 157);
  types.Bind(STANDARD_TYPE(StepBasic_LengthUnit), 158);
  types.Bind(STANDARD_TYPE(StepGeom_Line), 159);
  types.Bind(STANDARD_TYPE(StepBasic_LocalTime), 160);
  types.Bind(STANDARD_TYPE(StepShape_Loop), 161);
  types.Bind(STANDARD_TYPE(StepShape_ManifoldSolidBrep), 162);
  types.Bind(STANDARD_TYPE(StepShape_ManifoldSurfaceShapeRepresentation), 163);
  types.Bind(STANDARD_TYPE(StepRepr_MappedItem), 164);
  types.Bind(STANDARD_TYPE(StepBasic_MeasureWithUnit), 165);
  types.Bind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationArea), 166);
  types.Bind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation), 167);
  //  types.Bind (STANDARD_TYPE(StepVisual_MechanicalDesignPresentationArea), 168);
  types.Bind(STANDARD_TYPE(StepBasic_NamedUnit), 169);
  //  types.Bind (STANDARD_TYPE(StepShape_NonManifoldSurfaceShapeRepresentation), 170);
  types.Bind(STANDARD_TYPE(StepGeom_OffsetCurve3d), 171);
  types.Bind(STANDARD_TYPE(StepGeom_OffsetSurface), 172);
  //  types.Bind (STANDARD_TYPE(StepAP214_OneDirectionRepeatFactor), 173);
  types.Bind(STANDARD_TYPE(StepShape_OpenShell), 174);
  types.Bind(STANDARD_TYPE(StepBasic_OrdinalDate), 175);
  types.Bind(STANDARD_TYPE(StepBasic_Organization), 176);
  types.Bind(STANDARD_TYPE(StepBasic_OrganizationRole), 178);
  types.Bind(STANDARD_TYPE(StepBasic_OrganizationalAddress), 179);
  types.Bind(STANDARD_TYPE(StepShape_OrientedClosedShell), 180);
  types.Bind(STANDARD_TYPE(StepShape_OrientedEdge), 181);
  types.Bind(STANDARD_TYPE(StepShape_OrientedFace), 182);
  types.Bind(STANDARD_TYPE(StepShape_OrientedOpenShell), 183);
  types.Bind(STANDARD_TYPE(StepShape_OrientedPath), 184);
  types.Bind(STANDARD_TYPE(StepGeom_OuterBoundaryCurve), 185);
  types.Bind(STANDARD_TYPE(StepVisual_OverRidingStyledItem), 186);
  types.Bind(STANDARD_TYPE(StepGeom_Parabola), 187);
  types.Bind(STANDARD_TYPE(StepRepr_ParametricRepresentationContext), 188);
  types.Bind(STANDARD_TYPE(StepShape_Path), 189);
  types.Bind(STANDARD_TYPE(StepGeom_Pcurve), 190);
  types.Bind(STANDARD_TYPE(StepBasic_Person), 191);
  types.Bind(STANDARD_TYPE(StepBasic_PersonAndOrganization), 192);
  types.Bind(STANDARD_TYPE(StepBasic_PersonAndOrganizationRole), 194);
  types.Bind(STANDARD_TYPE(StepBasic_PersonalAddress), 195);
  types.Bind(STANDARD_TYPE(StepGeom_Placement), 196);
  types.Bind(STANDARD_TYPE(StepVisual_PlanarBox), 197);
  types.Bind(STANDARD_TYPE(StepVisual_PlanarExtent), 198);
  types.Bind(STANDARD_TYPE(StepGeom_Plane), 199);
  types.Bind(STANDARD_TYPE(StepBasic_PlaneAngleMeasureWithUnit), 200);
  types.Bind(STANDARD_TYPE(StepBasic_PlaneAngleUnit), 201);
  types.Bind(STANDARD_TYPE(StepGeom_Point), 202);
  types.Bind(STANDARD_TYPE(StepGeom_PointOnCurve), 203);
  types.Bind(STANDARD_TYPE(StepGeom_PointOnSurface), 204);
  types.Bind(STANDARD_TYPE(StepGeom_PointReplica), 205);
  types.Bind(STANDARD_TYPE(StepVisual_PointStyle), 206);
  types.Bind(STANDARD_TYPE(StepShape_PolyLoop), 207);
  types.Bind(STANDARD_TYPE(StepGeom_Polyline), 208);
  types.Bind(STANDARD_TYPE(StepVisual_PreDefinedColour), 209);
  types.Bind(STANDARD_TYPE(StepVisual_PreDefinedCurveFont), 210);
  types.Bind(STANDARD_TYPE(StepVisual_PreDefinedItem), 211);
  //  types.Bind (STANDARD_TYPE(StepVisual_PreDefinedSymbol), 212);
  types.Bind(STANDARD_TYPE(StepVisual_PreDefinedTextFont), 213);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationArea), 214);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationLayerAssignment), 215);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationRepresentation), 216);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationSet), 217);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationSize), 218);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationStyleAssignment), 219);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationStyleByContext), 220);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationView), 221);
  types.Bind(STANDARD_TYPE(StepBasic_Product), 223);
  types.Bind(STANDARD_TYPE(StepBasic_ProductCategory), 224);
  types.Bind(STANDARD_TYPE(StepBasic_ProductContext), 225);
  //  types.Bind (STANDARD_TYPE(StepVisual_ProductDataRepresentationView), 226);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinition), 227);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionContext), 228);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation), 229);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionFormationWithSpecifiedSource), 230);
  types.Bind(STANDARD_TYPE(StepRepr_ProductDefinitionShape), 231);
  types.Bind(STANDARD_TYPE(StepBasic_ProductRelatedProductCategory), 232);
  types.Bind(STANDARD_TYPE(StepBasic_ProductType), 233);
  types.Bind(STANDARD_TYPE(StepRepr_PropertyDefinition), 234);
  types.Bind(STANDARD_TYPE(StepRepr_PropertyDefinitionRepresentation), 235);
  types.Bind(STANDARD_TYPE(StepGeom_QuasiUniformCurve), 236);
  types.Bind(STANDARD_TYPE(StepGeom_QuasiUniformSurface), 237);
  types.Bind(STANDARD_TYPE(StepBasic_RatioMeasureWithUnit), 238);
  types.Bind(STANDARD_TYPE(StepGeom_RationalBSplineCurve), 239);
  types.Bind(STANDARD_TYPE(StepGeom_RationalBSplineSurface), 240);
  types.Bind(STANDARD_TYPE(StepGeom_RectangularCompositeSurface), 241);
  types.Bind(STANDARD_TYPE(StepGeom_RectangularTrimmedSurface), 242);
  types.Bind(STANDARD_TYPE(StepAP214_RepItemGroup), 243);
  types.Bind(STANDARD_TYPE(StepGeom_ReparametrisedCompositeCurveSegment), 244);
  types.Bind(STANDARD_TYPE(StepRepr_Representation), 245);
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationContext), 246);
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationItem), 247);
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationMap), 248);
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationRelationship), 249);
  types.Bind(STANDARD_TYPE(StepShape_RevolvedAreaSolid), 250);
  types.Bind(STANDARD_TYPE(StepShape_RightAngularWedge), 251);
  types.Bind(STANDARD_TYPE(StepShape_RightCircularCone), 252);
  types.Bind(STANDARD_TYPE(StepShape_RightCircularCylinder), 253);
  types.Bind(STANDARD_TYPE(StepGeom_SeamCurve), 254);
  types.Bind(STANDARD_TYPE(StepBasic_SecurityClassification), 255);
  types.Bind(STANDARD_TYPE(StepBasic_SecurityClassificationLevel), 257);
  types.Bind(STANDARD_TYPE(StepRepr_ShapeAspect), 258);
  types.Bind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship), 259);
  types.Bind(STANDARD_TYPE(StepRepr_ShapeAspectTransition), 260);
  types.Bind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), 261);
  types.Bind(STANDARD_TYPE(StepShape_ShapeRepresentation), 262);
  types.Bind(STANDARD_TYPE(StepShape_ShellBasedSurfaceModel), 263);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnit), 264);
  types.Bind(STANDARD_TYPE(StepBasic_SolidAngleMeasureWithUnit), 265);
  types.Bind(STANDARD_TYPE(StepShape_SolidModel), 266);
  types.Bind(STANDARD_TYPE(StepShape_SolidReplica), 267);
  types.Bind(STANDARD_TYPE(StepShape_Sphere), 268);
  types.Bind(STANDARD_TYPE(StepGeom_SphericalSurface), 269);
  types.Bind(STANDARD_TYPE(StepVisual_StyledItem), 270);
  types.Bind(STANDARD_TYPE(StepGeom_Surface), 271);
  types.Bind(STANDARD_TYPE(StepGeom_SurfaceCurve), 272);
  types.Bind(STANDARD_TYPE(StepGeom_SurfaceOfLinearExtrusion), 273);
  types.Bind(STANDARD_TYPE(StepGeom_SurfaceOfRevolution), 274);
  types.Bind(STANDARD_TYPE(StepGeom_SurfacePatch), 275);
  types.Bind(STANDARD_TYPE(StepGeom_SurfaceReplica), 276);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceSideStyle), 277);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleBoundary), 278);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleControlGrid), 279);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleFillArea), 280);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleParameterLine), 281);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleSegmentationCurve), 282);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleSilhouette), 283);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleUsage), 284);
  types.Bind(STANDARD_TYPE(StepShape_SweptAreaSolid), 285);
  types.Bind(STANDARD_TYPE(StepGeom_SweptSurface), 286);
  //  types.Bind (STANDARD_TYPE(StepVisual_SymbolColour), 287);
  //  types.Bind (STANDARD_TYPE(StepVisual_SymbolRepresentation), 288);
  //  types.Bind (STANDARD_TYPE(StepVisual_SymbolRepresentationMap), 289);
  //  types.Bind (STANDARD_TYPE(StepVisual_SymbolStyle), 290);
  //  types.Bind (STANDARD_TYPE(StepVisual_SymbolTarget), 291);
  types.Bind(STANDARD_TYPE(StepVisual_Template), 292);
  types.Bind(STANDARD_TYPE(StepVisual_TemplateInstance), 293);
  //  types.Bind (STANDARD_TYPE(StepVisual_TerminatorSymbol), 294);
  types.Bind(STANDARD_TYPE(StepVisual_TextLiteral), 295);
  //  types.Bind (STANDARD_TYPE(StepVisual_TextLiteralWithAssociatedCurves), 296);
  //  types.Bind (STANDARD_TYPE(StepVisual_TextLiteralWithBlankingBox), 297);
  //  types.Bind (STANDARD_TYPE(StepVisual_TextLiteralWithDelineation), 298);
  //  types.Bind (STANDARD_TYPE(StepVisual_TextLiteralWithExtent), 299);
  types.Bind(STANDARD_TYPE(StepVisual_TextStyle), 300);
  types.Bind(STANDARD_TYPE(StepVisual_TextStyleForDefinedFont), 301);
  types.Bind(STANDARD_TYPE(StepVisual_TextStyleWithBoxCharacteristics), 302);
  //  types.Bind (STANDARD_TYPE(StepVisual_TextStyleWithMirror), 303);
  types.Bind(STANDARD_TYPE(StepShape_TopologicalRepresentationItem), 304);
  types.Bind(STANDARD_TYPE(StepGeom_ToroidalSurface), 305);
  types.Bind(STANDARD_TYPE(StepShape_Torus), 306);
  types.Bind(STANDARD_TYPE(StepShape_TransitionalShapeRepresentation), 307);
  types.Bind(STANDARD_TYPE(StepGeom_TrimmedCurve), 308);
  //  types.Bind (STANDARD_TYPE(StepAP214_TwoDirectionRepeatFactor), 309);
  types.Bind(STANDARD_TYPE(StepBasic_UncertaintyMeasureWithUnit), 310);
  types.Bind(STANDARD_TYPE(StepGeom_UniformCurve), 311);
  types.Bind(STANDARD_TYPE(StepGeom_UniformSurface), 312);
  types.Bind(STANDARD_TYPE(StepGeom_Vector), 313);
  types.Bind(STANDARD_TYPE(StepShape_Vertex), 314);
  types.Bind(STANDARD_TYPE(StepShape_VertexLoop), 315);
  types.Bind(STANDARD_TYPE(StepShape_VertexPoint), 316);
  types.Bind(STANDARD_TYPE(StepVisual_ViewVolume), 317);
  types.Bind(STANDARD_TYPE(StepBasic_WeekOfYearAndDayDate), 318);
  types.Bind(STANDARD_TYPE(StepGeom_UniformCurveAndRationalBSplineCurve), 319);
  types.Bind(STANDARD_TYPE(StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve), 320);
  types.Bind(STANDARD_TYPE(StepGeom_QuasiUniformCurveAndRationalBSplineCurve), 321);
  types.Bind(STANDARD_TYPE(StepGeom_BezierCurveAndRationalBSplineCurve), 322);
  types.Bind(STANDARD_TYPE(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface), 323);
  types.Bind(STANDARD_TYPE(StepGeom_UniformSurfaceAndRationalBSplineSurface), 324);
  types.Bind(STANDARD_TYPE(StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface), 325);
  types.Bind(STANDARD_TYPE(StepGeom_BezierSurfaceAndRationalBSplineSurface), 326);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndLengthUnit), 327);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndPlaneAngleUnit), 328);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndLengthUnit), 329);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndPlaneAngleUnit), 330);
  types.Bind(STANDARD_TYPE(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext),
             331);
  types.Bind(STANDARD_TYPE(StepShape_LoopAndPath), 332);
  // Added by FMA
  types.Bind(STANDARD_TYPE(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx), 333);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndSolidAngleUnit), 334);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndSolidAngleUnit), 335);
  types.Bind(STANDARD_TYPE(StepBasic_SolidAngleUnit), 336);
  types.Bind(STANDARD_TYPE(StepShape_FacetedBrepAndBrepWithVoids), 337);
  types.Bind(
    STANDARD_TYPE(StepGeom_GeometricRepresentationContextAndParametricRepresentationContext),
    338);
  types.Bind(STANDARD_TYPE(StepBasic_MechanicalContext), 339);
  types.Bind(STANDARD_TYPE(StepBasic_DesignContext), 340);

  // full Rev4
  types.Bind(STANDARD_TYPE(StepBasic_TimeMeasureWithUnit), 341);
  types.Bind(STANDARD_TYPE(StepBasic_RatioUnit), 342);
  types.Bind(STANDARD_TYPE(StepBasic_TimeUnit), 343);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndRatioUnit), 344);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndTimeUnit), 345);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndRatioUnit), 346);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndTimeUnit), 347);

  types.Bind(STANDARD_TYPE(StepBasic_ApprovalDateTime), 348);
  types.Bind(STANDARD_TYPE(StepVisual_CameraImage2dWithScale), 349);
  types.Bind(STANDARD_TYPE(StepVisual_CameraImage3dWithScale), 350);
  types.Bind(STANDARD_TYPE(StepGeom_CartesianTransformationOperator2d), 351);
  types.Bind(STANDARD_TYPE(StepBasic_DerivedUnit), 352);
  types.Bind(STANDARD_TYPE(StepBasic_DerivedUnitElement), 353);
  types.Bind(STANDARD_TYPE(StepRepr_ItemDefinedTransformation), 354);
  types.Bind(STANDARD_TYPE(StepVisual_PresentedItemRepresentation), 355);
  types.Bind(STANDARD_TYPE(StepVisual_PresentationLayerUsage), 356);
  types.Bind(STANDARD_TYPE(StepGeom_SurfaceCurveAndBoundedCurve), 358); //: n5

  //  AP214 : CC1 -> CC2
  types.Bind(STANDARD_TYPE(StepAP214_AutoDesignDocumentReference), 366);
  types.Bind(STANDARD_TYPE(StepBasic_Document), 367);
  types.Bind(STANDARD_TYPE(StepBasic_DigitalDocument), 368);
  types.Bind(STANDARD_TYPE(StepBasic_DocumentRelationship), 369);
  types.Bind(STANDARD_TYPE(StepBasic_DocumentType), 370);
  types.Bind(STANDARD_TYPE(StepBasic_DocumentUsageConstraint), 371);
  types.Bind(STANDARD_TYPE(StepBasic_Effectivity), 372);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionEffectivity), 373);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship), 374);

  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionWithAssociatedDocuments), 375);
  types.Bind(STANDARD_TYPE(StepBasic_PhysicallyModeledProductDefinition), 376);

  types.Bind(STANDARD_TYPE(StepRepr_ProductDefinitionUsage), 377);
  types.Bind(STANDARD_TYPE(StepRepr_MakeFromUsageOption), 378);
  types.Bind(STANDARD_TYPE(StepRepr_AssemblyComponentUsage), 379);
  types.Bind(STANDARD_TYPE(StepRepr_NextAssemblyUsageOccurrence), 380);
  types.Bind(STANDARD_TYPE(StepRepr_PromissoryUsageOccurrence), 381);
  types.Bind(STANDARD_TYPE(StepRepr_QuantifiedAssemblyComponentUsage), 382);
  types.Bind(STANDARD_TYPE(StepRepr_SpecifiedHigherUsageOccurrence), 383);
  types.Bind(STANDARD_TYPE(StepRepr_AssemblyComponentUsageSubstitute), 384);
  types.Bind(STANDARD_TYPE(StepRepr_SuppliedPartRelationship), 385);
  types.Bind(STANDARD_TYPE(StepRepr_ExternallyDefinedRepresentation), 386);
  types.Bind(STANDARD_TYPE(StepRepr_ShapeRepresentationRelationship), 387);
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationRelationshipWithTransformation), 388);
  types.Bind(STANDARD_TYPE(StepRepr_ShapeRepresentationRelationshipWithTransformation), 389);
  types.Bind(STANDARD_TYPE(StepRepr_MaterialDesignation), 390);
  types.Bind(STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation), 391);

  // Added from CD to DIS   :j4

  types.Bind(STANDARD_TYPE(StepAP214_AppliedDateAndTimeAssignment), 392);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedDateAssignment), 393);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedApprovalAssignment), 394);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedGroupAssignment), 395);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedOrganizationAssignment), 396);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedPersonAndOrganizationAssignment), 397);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedPresentedItem), 398);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedSecurityClassificationAssignment), 399);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedDocumentReference), 400);

  types.Bind(STANDARD_TYPE(StepBasic_DocumentFile), 401);
  types.Bind(STANDARD_TYPE(StepBasic_CharacterizedObject), 402);
  types.Bind(STANDARD_TYPE(StepShape_ExtrudedFaceSolid), 403);
  types.Bind(STANDARD_TYPE(StepShape_RevolvedFaceSolid), 404);
  types.Bind(STANDARD_TYPE(StepShape_SweptFaceSolid), 405);

  // Added by ABV 08.09.99 for CAX TRJ 2 (validation properties)
  types.Bind(STANDARD_TYPE(StepRepr_MeasureRepresentationItem), 406);
  types.Bind(STANDARD_TYPE(StepBasic_AreaUnit), 407);
  types.Bind(STANDARD_TYPE(StepBasic_VolumeUnit), 408);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndAreaUnit), 409);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndVolumeUnit), 410);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndAreaUnit), 411);
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndVolumeUnit), 412);

  // Added by ABV 10.11.99 for AP203
  types.Bind(STANDARD_TYPE(StepBasic_Action), 413);
  types.Bind(STANDARD_TYPE(StepBasic_ActionAssignment), 414);
  types.Bind(STANDARD_TYPE(StepBasic_ActionMethod), 415);
  types.Bind(STANDARD_TYPE(StepBasic_ActionRequestAssignment), 416);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignApproval), 417);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignCertification), 418);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignContract), 419);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignDateAndTimeAssignment), 420);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignPersonAndOrganizationAssignment), 421);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignSecurityClassification), 422);
  types.Bind(STANDARD_TYPE(StepAP203_CcDesignSpecificationReference), 423);
  types.Bind(STANDARD_TYPE(StepBasic_Certification), 424);
  types.Bind(STANDARD_TYPE(StepBasic_CertificationAssignment), 425);
  types.Bind(STANDARD_TYPE(StepBasic_CertificationType), 426);
  types.Bind(STANDARD_TYPE(StepAP203_Change), 427);
  types.Bind(STANDARD_TYPE(StepAP203_ChangeRequest), 428);
  types.Bind(STANDARD_TYPE(StepRepr_ConfigurationDesign), 429);
  types.Bind(STANDARD_TYPE(StepRepr_ConfigurationEffectivity), 430);
  types.Bind(STANDARD_TYPE(StepBasic_Contract), 431);
  types.Bind(STANDARD_TYPE(StepBasic_ContractAssignment), 432);
  types.Bind(STANDARD_TYPE(StepBasic_ContractType), 433);
  types.Bind(STANDARD_TYPE(StepRepr_ProductConcept), 434);
  types.Bind(STANDARD_TYPE(StepBasic_ProductConceptContext), 435);
  types.Bind(STANDARD_TYPE(StepAP203_StartRequest), 436);
  types.Bind(STANDARD_TYPE(StepAP203_StartWork), 437);
  types.Bind(STANDARD_TYPE(StepBasic_VersionedActionRequest), 438);
  types.Bind(STANDARD_TYPE(StepBasic_ProductCategoryRelationship), 439);
  types.Bind(STANDARD_TYPE(StepBasic_ActionRequestSolution), 440);
  types.Bind(STANDARD_TYPE(StepVisual_DraughtingModel), 441);

  // Added by ABV 18.04.00 for CAX-IF TRJ4 (dimensional tolerances)
  types.Bind(STANDARD_TYPE(StepShape_AngularLocation), 442);
  types.Bind(STANDARD_TYPE(StepShape_AngularSize), 443);
  types.Bind(STANDARD_TYPE(StepShape_DimensionalCharacteristicRepresentation), 444);
  types.Bind(STANDARD_TYPE(StepShape_DimensionalLocation), 445);
  types.Bind(STANDARD_TYPE(StepShape_DimensionalLocationWithPath), 446);
  types.Bind(STANDARD_TYPE(StepShape_DimensionalSize), 447);
  types.Bind(STANDARD_TYPE(StepShape_DimensionalSizeWithPath), 448);
  types.Bind(STANDARD_TYPE(StepShape_ShapeDimensionRepresentation), 449);

  // Added by ABV 10.05.00 for CAX-IF TRJ4 (external references)
  types.Bind(STANDARD_TYPE(StepBasic_DocumentRepresentationType), 450);
  types.Bind(STANDARD_TYPE(StepBasic_ObjectRole), 451);
  types.Bind(STANDARD_TYPE(StepBasic_RoleAssociation), 452);
  types.Bind(STANDARD_TYPE(StepBasic_IdentificationRole), 453);
  types.Bind(STANDARD_TYPE(StepBasic_IdentificationAssignment), 454);
  types.Bind(STANDARD_TYPE(StepBasic_ExternalIdentificationAssignment), 455);
  types.Bind(STANDARD_TYPE(StepBasic_EffectivityAssignment), 456);
  types.Bind(STANDARD_TYPE(StepBasic_NameAssignment), 457);
  types.Bind(STANDARD_TYPE(StepBasic_GeneralProperty), 458);
  types.Bind(STANDARD_TYPE(StepAP214_Class), 459);
  types.Bind(STANDARD_TYPE(StepAP214_ExternallyDefinedClass), 460);
  types.Bind(STANDARD_TYPE(StepAP214_ExternallyDefinedGeneralProperty), 461);
  types.Bind(STANDARD_TYPE(StepAP214_AppliedExternalIdentificationAssignment), 462);

  // abv 11.07.00: CAX-IF TRJ4: k1_geo-ac.stp
  types.Bind(STANDARD_TYPE(StepShape_DefinitionalRepresentationAndShapeRepresentation), 463);

  // CKY 25 APR 2001 : CAX-IF TR7J , dimensional tolerances (contd)
  types.Bind(STANDARD_TYPE(StepRepr_CompositeShapeAspect), 470);
  types.Bind(STANDARD_TYPE(StepRepr_DerivedShapeAspect), 471);
  types.Bind(STANDARD_TYPE(StepRepr_Extension), 472);
  types.Bind(STANDARD_TYPE(StepShape_DirectedDimensionalLocation), 473);
  types.Bind(STANDARD_TYPE(StepShape_LimitsAndFits), 474);
  types.Bind(STANDARD_TYPE(StepShape_ToleranceValue), 475);
  types.Bind(STANDARD_TYPE(StepShape_MeasureQualification), 476);
  types.Bind(STANDARD_TYPE(StepShape_PlusMinusTolerance), 477);
  types.Bind(STANDARD_TYPE(StepShape_PrecisionQualifier), 478);
  types.Bind(STANDARD_TYPE(StepShape_TypeQualifier), 479);
  types.Bind(STANDARD_TYPE(StepShape_QualifiedRepresentationItem), 480);
  types.Bind(STANDARD_TYPE(StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem), 481);
  types.Bind(STANDARD_TYPE(StepRepr_CompoundRepresentationItem), 482);
  types.Bind(STANDARD_TYPE(StepRepr_ValueRange), 483);
  types.Bind(STANDARD_TYPE(StepRepr_ShapeAspectDerivingRelationship), 484);

  // abv 11.07.00: CAX-IF TRJ8: edge_based_wireframe
  types.Bind(STANDARD_TYPE(StepShape_CompoundShapeRepresentation), 485);
  types.Bind(STANDARD_TYPE(StepShape_ConnectedEdgeSet), 486);
  types.Bind(STANDARD_TYPE(StepShape_ConnectedFaceShapeRepresentation), 487);
  types.Bind(STANDARD_TYPE(StepShape_EdgeBasedWireframeModel), 488);
  types.Bind(STANDARD_TYPE(StepShape_EdgeBasedWireframeShapeRepresentation), 489);
  types.Bind(STANDARD_TYPE(StepShape_FaceBasedSurfaceModel), 490);
  types.Bind(STANDARD_TYPE(StepShape_NonManifoldSurfaceShapeRepresentation), 491);

  // gka 08.01.02 TRJ9 IS->DIS
  types.Bind(STANDARD_TYPE(StepGeom_OrientedSurface), 492);
  types.Bind(STANDARD_TYPE(StepShape_Subface), 493);
  types.Bind(STANDARD_TYPE(StepShape_Subedge), 494);
  types.Bind(STANDARD_TYPE(StepShape_SeamEdge), 495);
  types.Bind(STANDARD_TYPE(StepShape_ConnectedFaceSubSet), 496);

  // AP209 types
  types.Bind(STANDARD_TYPE(StepBasic_EulerAngles), 500);
  types.Bind(STANDARD_TYPE(StepBasic_MassUnit), 501);
  types.Bind(STANDARD_TYPE(StepBasic_ThermodynamicTemperatureUnit), 502);
  types.Bind(STANDARD_TYPE(StepElement_AnalysisItemWithinRepresentation), 503);
  types.Bind(STANDARD_TYPE(StepElement_Curve3dElementDescriptor), 504);
  types.Bind(STANDARD_TYPE(StepElement_CurveElementEndReleasePacket), 505);
  types.Bind(STANDARD_TYPE(StepElement_CurveElementSectionDefinition), 506);
  types.Bind(STANDARD_TYPE(StepElement_CurveElementSectionDerivedDefinitions), 507);
  types.Bind(STANDARD_TYPE(StepElement_ElementDescriptor), 508);
  types.Bind(STANDARD_TYPE(StepElement_ElementMaterial), 509);
  types.Bind(STANDARD_TYPE(StepElement_Surface3dElementDescriptor), 510);
  types.Bind(STANDARD_TYPE(StepElement_SurfaceElementProperty), 511);
  types.Bind(STANDARD_TYPE(StepElement_SurfaceSection), 512);
  types.Bind(STANDARD_TYPE(StepElement_SurfaceSectionField), 513);
  types.Bind(STANDARD_TYPE(StepElement_SurfaceSectionFieldConstant), 514);
  types.Bind(STANDARD_TYPE(StepElement_SurfaceSectionFieldVarying), 515);
  types.Bind(STANDARD_TYPE(StepElement_UniformSurfaceSection), 516);
  types.Bind(STANDARD_TYPE(StepElement_Volume3dElementDescriptor), 517);
  types.Bind(STANDARD_TYPE(StepFEA_AlignedCurve3dElementCoordinateSystem), 518);
  types.Bind(STANDARD_TYPE(StepFEA_ArbitraryVolume3dElementCoordinateSystem), 519);
  types.Bind(STANDARD_TYPE(StepFEA_Curve3dElementProperty), 520);
  types.Bind(STANDARD_TYPE(StepFEA_Curve3dElementRepresentation), 521);
  types.Bind(STANDARD_TYPE(StepFEA_Node), 522);
  //  types.Bind (STANDARD_TYPE(StepFEA_CurveElementEndCoordinateSystem),523);
  types.Bind(STANDARD_TYPE(StepFEA_CurveElementEndOffset), 524);
  types.Bind(STANDARD_TYPE(StepFEA_CurveElementEndRelease), 525);
  types.Bind(STANDARD_TYPE(StepFEA_CurveElementInterval), 526);
  types.Bind(STANDARD_TYPE(StepFEA_CurveElementIntervalConstant), 527);
  types.Bind(STANDARD_TYPE(StepFEA_DummyNode), 528);
  types.Bind(STANDARD_TYPE(StepFEA_CurveElementLocation), 529);
  types.Bind(STANDARD_TYPE(StepFEA_ElementGeometricRelationship), 530);
  types.Bind(STANDARD_TYPE(StepFEA_ElementGroup), 531);
  types.Bind(STANDARD_TYPE(StepFEA_ElementRepresentation), 532);
  types.Bind(STANDARD_TYPE(StepFEA_FeaAreaDensity), 533);
  types.Bind(STANDARD_TYPE(StepFEA_FeaAxis2Placement3d), 534);
  types.Bind(STANDARD_TYPE(StepFEA_FeaGroup), 535);
  types.Bind(STANDARD_TYPE(StepFEA_FeaLinearElasticity), 536);
  types.Bind(STANDARD_TYPE(StepFEA_FeaMassDensity), 537);
  types.Bind(STANDARD_TYPE(StepFEA_FeaMaterialPropertyRepresentation), 538);
  types.Bind(STANDARD_TYPE(StepFEA_FeaMaterialPropertyRepresentationItem), 539);
  types.Bind(STANDARD_TYPE(StepFEA_FeaModel), 540);
  types.Bind(STANDARD_TYPE(StepFEA_FeaModel3d), 541);
  types.Bind(STANDARD_TYPE(StepFEA_FeaMoistureAbsorption), 542);
  types.Bind(STANDARD_TYPE(StepFEA_FeaParametricPoint), 543);
  types.Bind(STANDARD_TYPE(StepFEA_FeaRepresentationItem), 544);
  types.Bind(STANDARD_TYPE(StepFEA_FeaSecantCoefficientOfLinearThermalExpansion), 545);
  types.Bind(STANDARD_TYPE(StepFEA_FeaShellBendingStiffness), 546);
  types.Bind(STANDARD_TYPE(StepFEA_FeaShellMembraneBendingCouplingStiffness), 547);
  types.Bind(STANDARD_TYPE(StepFEA_FeaShellMembraneStiffness), 548);
  types.Bind(STANDARD_TYPE(StepFEA_FeaShellShearStiffness), 549);
  types.Bind(STANDARD_TYPE(StepFEA_GeometricNode), 550);
  types.Bind(STANDARD_TYPE(StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion), 551);
  types.Bind(STANDARD_TYPE(StepFEA_NodeGroup), 552);
  types.Bind(STANDARD_TYPE(StepFEA_NodeRepresentation), 553);
  types.Bind(STANDARD_TYPE(StepFEA_NodeSet), 554);
  types.Bind(STANDARD_TYPE(StepFEA_NodeWithSolutionCoordinateSystem), 555);
  types.Bind(STANDARD_TYPE(StepFEA_NodeWithVector), 556);
  types.Bind(STANDARD_TYPE(StepFEA_ParametricCurve3dElementCoordinateDirection), 557);
  types.Bind(STANDARD_TYPE(StepFEA_ParametricCurve3dElementCoordinateSystem), 558);
  types.Bind(STANDARD_TYPE(StepFEA_ParametricSurface3dElementCoordinateSystem), 559);
  types.Bind(STANDARD_TYPE(StepFEA_Surface3dElementRepresentation), 560);
  //  types.Bind (STANDARD_TYPE(StepFEA_SymmetricTensor22d),561);
  //  types.Bind (STANDARD_TYPE(StepFEA_SymmetricTensor42d),562);
  //  types.Bind (STANDARD_TYPE(StepFEA_SymmetricTensor43d),563);
  types.Bind(STANDARD_TYPE(StepFEA_Volume3dElementRepresentation), 564);
  types.Bind(STANDARD_TYPE(StepRepr_DataEnvironment), 565);
  types.Bind(STANDARD_TYPE(StepRepr_MaterialPropertyRepresentation), 566);
  types.Bind(STANDARD_TYPE(StepRepr_PropertyDefinitionRelationship), 567);
  types.Bind(STANDARD_TYPE(StepShape_PointRepresentation), 568);
  types.Bind(STANDARD_TYPE(StepRepr_MaterialProperty), 569);
  types.Bind(STANDARD_TYPE(StepFEA_FeaModelDefinition), 570);
  types.Bind(STANDARD_TYPE(StepFEA_FreedomAndCoefficient), 571);
  types.Bind(STANDARD_TYPE(StepFEA_FreedomsList), 572);
  types.Bind(STANDARD_TYPE(StepBasic_ProductDefinitionFormationRelationship), 573);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndMassUnit), 574);
  types.Bind(STANDARD_TYPE(StepFEA_NodeDefinition), 575);
  types.Bind(STANDARD_TYPE(StepRepr_StructuralResponseProperty), 576);
  types.Bind(STANDARD_TYPE(StepRepr_StructuralResponsePropertyDefinitionRepresentation), 577);
  types.Bind(STANDARD_TYPE(StepBasic_SiUnitAndThermodynamicTemperatureUnit), 578);
  types.Bind(STANDARD_TYPE(StepFEA_AlignedSurface3dElementCoordinateSystem), 579);
  types.Bind(STANDARD_TYPE(StepFEA_ConstantSurface3dElementCoordinateSystem), 580);
  types.Bind(STANDARD_TYPE(StepFEA_CurveElementIntervalLinearlyVarying), 581);
  types.Bind(STANDARD_TYPE(StepFEA_FeaCurveSectionGeometricRelationship), 582);
  types.Bind(STANDARD_TYPE(StepFEA_FeaSurfaceSectionGeometricRelationship), 583);

  // PTV 28.01.2003 TRJ11 AP214 external references
  types.Bind(STANDARD_TYPE(StepBasic_DocumentProductAssociation), 600);
  types.Bind(STANDARD_TYPE(StepBasic_DocumentProductEquivalence), 601);

  // TR12J 4.06.2003 G&DT entities
  types.Bind(STANDARD_TYPE(StepDimTol_CylindricityTolerance), 609);
  types.Bind(STANDARD_TYPE(StepShape_ShapeRepresentationWithParameters), 610);
  types.Bind(STANDARD_TYPE(StepDimTol_AngularityTolerance), 611);
  types.Bind(STANDARD_TYPE(StepDimTol_ConcentricityTolerance), 612);
  types.Bind(STANDARD_TYPE(StepDimTol_CircularRunoutTolerance), 613);
  types.Bind(STANDARD_TYPE(StepDimTol_CoaxialityTolerance), 614);
  types.Bind(STANDARD_TYPE(StepDimTol_FlatnessTolerance), 615);
  types.Bind(STANDARD_TYPE(StepDimTol_LineProfileTolerance), 616);
  types.Bind(STANDARD_TYPE(StepDimTol_ParallelismTolerance), 617);
  types.Bind(STANDARD_TYPE(StepDimTol_PerpendicularityTolerance), 618);
  types.Bind(STANDARD_TYPE(StepDimTol_PositionTolerance), 619);
  types.Bind(STANDARD_TYPE(StepDimTol_RoundnessTolerance), 620);
  types.Bind(STANDARD_TYPE(StepDimTol_StraightnessTolerance), 621);
  types.Bind(STANDARD_TYPE(StepDimTol_SurfaceProfileTolerance), 622);
  types.Bind(STANDARD_TYPE(StepDimTol_SymmetryTolerance), 623);
  types.Bind(STANDARD_TYPE(StepDimTol_TotalRunoutTolerance), 624);

  types.Bind(STANDARD_TYPE(StepDimTol_GeometricTolerance), 625);
  types.Bind(STANDARD_TYPE(StepDimTol_GeometricToleranceRelationship), 626);
  types.Bind(STANDARD_TYPE(StepDimTol_GeometricToleranceWithDatumReference), 627);
  types.Bind(STANDARD_TYPE(StepDimTol_ModifiedGeometricTolerance), 628);

  types.Bind(STANDARD_TYPE(StepDimTol_Datum), 629);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumFeature), 630);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumReference), 631);
  types.Bind(STANDARD_TYPE(StepDimTol_CommonDatum), 632);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumTarget), 633);
  types.Bind(STANDARD_TYPE(StepDimTol_PlacedDatumTargetFeature), 634);

  types.Bind(STANDARD_TYPE(StepRepr_ReprItemAndLengthMeasureWithUnit), 635);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol), 636);

  // added by skl 10.02.2004 for TRJ13
  types.Bind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndMassUnit), 650);
  types.Bind(STANDARD_TYPE(StepBasic_MassMeasureWithUnit), 651);

  // Added by ika for GD&T AP242
  types.Bind(STANDARD_TYPE(StepRepr_Apex), 660);
  types.Bind(STANDARD_TYPE(StepRepr_CentreOfSymmetry), 661);
  types.Bind(STANDARD_TYPE(StepRepr_GeometricAlignment), 662);
  types.Bind(STANDARD_TYPE(StepRepr_PerpendicularTo), 663);
  types.Bind(STANDARD_TYPE(StepRepr_Tangent), 664);
  types.Bind(STANDARD_TYPE(StepRepr_ParallelOffset), 665);
  types.Bind(STANDARD_TYPE(StepAP242_GeometricItemSpecificUsage), 666);
  types.Bind(STANDARD_TYPE(StepAP242_IdAttribute), 667);
  types.Bind(STANDARD_TYPE(StepAP242_ItemIdentifiedRepresentationUsage), 668);
  types.Bind(STANDARD_TYPE(StepRepr_AllAroundShapeAspect), 669);
  types.Bind(STANDARD_TYPE(StepRepr_BetweenShapeAspect), 670);
  types.Bind(STANDARD_TYPE(StepRepr_CompositeGroupShapeAspect), 671);
  types.Bind(STANDARD_TYPE(StepRepr_ContinuosShapeAspect), 672);
  types.Bind(STANDARD_TYPE(StepDimTol_GeometricToleranceWithDefinedAreaUnit), 673);
  types.Bind(STANDARD_TYPE(StepDimTol_GeometricToleranceWithDefinedUnit), 674);
  types.Bind(STANDARD_TYPE(StepDimTol_GeometricToleranceWithMaximumTolerance), 675);
  types.Bind(STANDARD_TYPE(StepDimTol_GeometricToleranceWithModifiers), 676);
  types.Bind(STANDARD_TYPE(StepDimTol_UnequallyDisposedGeometricTolerance), 677);
  types.Bind(STANDARD_TYPE(StepDimTol_NonUniformZoneDefinition), 678);
  types.Bind(STANDARD_TYPE(StepDimTol_ProjectedZoneDefinition), 679);
  types.Bind(STANDARD_TYPE(StepDimTol_RunoutZoneDefinition), 680);
  types.Bind(STANDARD_TYPE(StepDimTol_RunoutZoneOrientation), 681);
  types.Bind(STANDARD_TYPE(StepDimTol_ToleranceZone), 682);
  types.Bind(STANDARD_TYPE(StepDimTol_ToleranceZoneDefinition), 683);
  types.Bind(STANDARD_TYPE(StepDimTol_ToleranceZoneForm), 684);
  types.Bind(STANDARD_TYPE(StepShape_ValueFormatTypeQualifier), 685);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumReferenceCompartment), 686);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumReferenceElement), 687);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumReferenceModifierWithValue), 688);
  types.Bind(STANDARD_TYPE(StepDimTol_DatumSystem), 689);
  types.Bind(STANDARD_TYPE(StepDimTol_GeneralDatumReference), 690);
  types.Bind(STANDARD_TYPE(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit), 691);
  types.Bind(STANDARD_TYPE(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI), 692);
  types.Bind(STANDARD_TYPE(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI), 693);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthDatRef), 694);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod), 695);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthMod), 696);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol), 697);
  types.Bind(STANDARD_TYPE(StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp), 698);
  types.Bind(STANDARD_TYPE(StepRepr_CompShAspAndDatumFeatAndShAsp), 699);
  types.Bind(STANDARD_TYPE(StepRepr_IntegerRepresentationItem), 700);
  types.Bind(STANDARD_TYPE(StepRepr_ValueRepresentationItem), 701);
  types.Bind(STANDARD_TYPE(StepRepr_FeatureForDatumTargetRelationship), 702);
  types.Bind(STANDARD_TYPE(StepAP242_DraughtingModelItemAssociation), 703);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationPlane), 704);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol), 705);
  types.Bind(STANDARD_TYPE(StepDimTol_GeoTolAndGeoTolWthMaxTol), 706);
  // AP242 tesselated
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedAnnotationOccurrence), 707);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedItem), 708);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedGeometricSet), 709);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedCurveSet), 710);
  types.Bind(STANDARD_TYPE(StepVisual_CoordinatesList), 711);
  types.Bind(STANDARD_TYPE(StepRepr_ConstructiveGeometryRepresentation), 712);
  types.Bind(STANDARD_TYPE(StepRepr_ConstructiveGeometryRepresentationRelationship), 713);
  types.Bind(STANDARD_TYPE(StepRepr_CharacterizedRepresentation), 714);
  types.Bind(STANDARD_TYPE(StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel), 715);
  types.Bind(STANDARD_TYPE(StepVisual_CameraModelD3MultiClipping), 716);
  types.Bind(STANDARD_TYPE(StepVisual_CameraModelD3MultiClippingIntersection), 717);
  types.Bind(STANDARD_TYPE(StepVisual_CameraModelD3MultiClippingUnion), 718);
  types.Bind(STANDARD_TYPE(StepVisual_AnnotationCurveOccurrenceAndGeomReprItem), 719);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleTransparent), 720);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleReflectanceAmbient), 721);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleRendering), 722);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleRenderingWithProperties), 723);

  // Added for kinematics implementation
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationContextReference), 724);
  types.Bind(STANDARD_TYPE(StepRepr_RepresentationReference), 725);
  types.Bind(STANDARD_TYPE(StepGeom_SuParameters), 726);
  types.Bind(STANDARD_TYPE(StepKinematics_RotationAboutDirection), 727);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicJoint), 728);
  types.Bind(STANDARD_TYPE(StepKinematics_ActuatedKinematicPair), 729);
  types.Bind(STANDARD_TYPE(StepKinematics_ContextDependentKinematicLinkRepresentation), 730);
  types.Bind(STANDARD_TYPE(StepKinematics_CylindricalPair), 731);
  types.Bind(STANDARD_TYPE(StepKinematics_CylindricalPairValue), 732);
  types.Bind(STANDARD_TYPE(StepKinematics_CylindricalPairWithRange), 733);
  types.Bind(STANDARD_TYPE(StepKinematics_FullyConstrainedPair), 734);
  types.Bind(STANDARD_TYPE(StepKinematics_GearPair), 735);
  types.Bind(STANDARD_TYPE(StepKinematics_GearPairValue), 736);
  types.Bind(STANDARD_TYPE(StepKinematics_GearPairWithRange), 737);
  types.Bind(STANDARD_TYPE(StepKinematics_HomokineticPair), 738);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicLink), 739);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicLinkRepresentationAssociation), 740);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicPropertyMechanismRepresentation), 741);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicTopologyStructure), 742);
  types.Bind(STANDARD_TYPE(StepKinematics_LowOrderKinematicPair), 743);
  types.Bind(STANDARD_TYPE(StepKinematics_LowOrderKinematicPairValue), 744);
  types.Bind(STANDARD_TYPE(StepKinematics_LowOrderKinematicPairWithRange), 745);
  types.Bind(STANDARD_TYPE(StepKinematics_MechanismRepresentation), 746);
  types.Bind(STANDARD_TYPE(StepKinematics_OrientedJoint), 747);
  types.Bind(STANDARD_TYPE(StepKinematics_PlanarCurvePair), 748);
  types.Bind(STANDARD_TYPE(StepKinematics_PlanarCurvePairRange), 749);
  types.Bind(STANDARD_TYPE(StepKinematics_PlanarPair), 750);
  types.Bind(STANDARD_TYPE(StepKinematics_PlanarPairValue), 751);
  types.Bind(STANDARD_TYPE(StepKinematics_PlanarPairWithRange), 752);
  types.Bind(STANDARD_TYPE(StepKinematics_PointOnPlanarCurvePair), 753);
  types.Bind(STANDARD_TYPE(StepKinematics_PointOnPlanarCurvePairValue), 754);
  types.Bind(STANDARD_TYPE(StepKinematics_PointOnPlanarCurvePairWithRange), 755);
  types.Bind(STANDARD_TYPE(StepKinematics_PointOnSurfacePair), 756);
  types.Bind(STANDARD_TYPE(StepKinematics_PointOnSurfacePairValue), 757);
  types.Bind(STANDARD_TYPE(StepKinematics_PointOnSurfacePairWithRange), 758);
  types.Bind(STANDARD_TYPE(StepKinematics_PrismaticPair), 759);
  types.Bind(STANDARD_TYPE(StepKinematics_PrismaticPairValue), 760);
  types.Bind(STANDARD_TYPE(StepKinematics_PrismaticPairWithRange), 761);
  types.Bind(STANDARD_TYPE(StepKinematics_ProductDefinitionKinematics), 762);
  types.Bind(STANDARD_TYPE(StepKinematics_ProductDefinitionRelationshipKinematics), 763);
  types.Bind(STANDARD_TYPE(StepKinematics_RackAndPinionPair), 764);
  types.Bind(STANDARD_TYPE(StepKinematics_RackAndPinionPairValue), 765);
  types.Bind(STANDARD_TYPE(StepKinematics_RackAndPinionPairWithRange), 766);
  types.Bind(STANDARD_TYPE(StepKinematics_RevolutePair), 767);
  types.Bind(STANDARD_TYPE(StepKinematics_RevolutePairValue), 768);
  types.Bind(STANDARD_TYPE(StepKinematics_RevolutePairWithRange), 769);
  types.Bind(STANDARD_TYPE(StepKinematics_RollingCurvePair), 770);
  types.Bind(STANDARD_TYPE(StepKinematics_RollingCurvePairValue), 771);
  types.Bind(STANDARD_TYPE(StepKinematics_RollingSurfacePair), 772);
  types.Bind(STANDARD_TYPE(StepKinematics_RollingSurfacePairValue), 773);
  types.Bind(STANDARD_TYPE(StepKinematics_ScrewPair), 774);
  types.Bind(STANDARD_TYPE(StepKinematics_ScrewPairValue), 775);
  types.Bind(STANDARD_TYPE(StepKinematics_ScrewPairWithRange), 776);
  types.Bind(STANDARD_TYPE(StepKinematics_SlidingCurvePair), 777);
  types.Bind(STANDARD_TYPE(StepKinematics_SlidingCurvePairValue), 778);
  types.Bind(STANDARD_TYPE(StepKinematics_SlidingSurfacePair), 779);
  types.Bind(STANDARD_TYPE(StepKinematics_SlidingSurfacePairValue), 780);
  types.Bind(STANDARD_TYPE(StepKinematics_SphericalPair), 781);
  types.Bind(STANDARD_TYPE(StepKinematics_SphericalPairValue), 782);
  types.Bind(STANDARD_TYPE(StepKinematics_SphericalPairWithPin), 783);
  types.Bind(STANDARD_TYPE(StepKinematics_SphericalPairWithPinAndRange), 784);
  types.Bind(STANDARD_TYPE(StepKinematics_SphericalPairWithRange), 785);
  types.Bind(STANDARD_TYPE(StepKinematics_SurfacePairWithRange), 786);
  types.Bind(STANDARD_TYPE(StepKinematics_UnconstrainedPair), 787);
  types.Bind(STANDARD_TYPE(StepKinematics_UnconstrainedPairValue), 788);
  types.Bind(STANDARD_TYPE(StepKinematics_UniversalPair), 789);
  types.Bind(STANDARD_TYPE(StepKinematics_UniversalPairValue), 790);
  types.Bind(STANDARD_TYPE(StepKinematics_UniversalPairWithRange), 791);
  types.Bind(STANDARD_TYPE(StepKinematics_PairRepresentationRelationship), 792);
  types.Bind(STANDARD_TYPE(StepKinematics_RigidLinkRepresentation), 793);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicTopologyDirectedStructure), 794);
  types.Bind(STANDARD_TYPE(StepKinematics_KinematicTopologyNetworkStructure), 795);
  types.Bind(STANDARD_TYPE(StepKinematics_LinearFlexibleAndPinionPair), 796);
  types.Bind(STANDARD_TYPE(StepKinematics_LinearFlexibleAndPlanarCurvePair), 797);
  types.Bind(STANDARD_TYPE(StepKinematics_LinearFlexibleLinkRepresentation), 798);
  types.Bind(STANDARD_TYPE(StepKinematics_ActuatedKinPairAndOrderKinPair), 800);
  types.Bind(STANDARD_TYPE(StepKinematics_MechanismStateRepresentation), 801);
  types.Bind(STANDARD_TYPE(StepVisual_RepositionedTessellatedGeometricSet), 802);
  types.Bind(STANDARD_TYPE(StepVisual_RepositionedTessellatedItem), 803);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedConnectingEdge), 804);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedEdge), 805);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedPointSet), 806);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedShapeRepresentation), 807);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedShapeRepresentationWithAccuracyParameters), 808);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedShell), 809);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedSolid), 810);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedStructuredItem), 811);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedVertex), 812);
  types.Bind(STANDARD_TYPE(StepVisual_TessellatedWire), 813);
  types.Bind(STANDARD_TYPE(StepVisual_TriangulatedFace), 814);
  types.Bind(STANDARD_TYPE(StepVisual_ComplexTriangulatedFace), 815);
  types.Bind(STANDARD_TYPE(StepVisual_ComplexTriangulatedSurfaceSet), 816);
  types.Bind(STANDARD_TYPE(StepVisual_CubicBezierTessellatedEdge), 817);
  types.Bind(STANDARD_TYPE(StepVisual_CubicBezierTriangulatedFace), 818);
  types.Bind(STANDARD_TYPE(StepVisual_TriangulatedSurfaceSet), 819);
  types.Bind(STANDARD_TYPE(StepBasic_GeneralPropertyAssociation), 820);
  types.Bind(STANDARD_TYPE(StepBasic_GeneralPropertyRelationship), 821);
  types.Bind(STANDARD_TYPE(StepRepr_BooleanRepresentationItem), 822);
  types.Bind(STANDARD_TYPE(StepRepr_RealRepresentationItem), 823);
  types.Bind(STANDARD_TYPE(StepRepr_MechanicalDesignAndDraughtingRelationship), 824);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleReflectanceAmbientDiffuse), 825);
  types.Bind(STANDARD_TYPE(StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular), 826);
}

//=================================================================================================

int StepAP214_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (types.IsBound(atype))
    return types.Find(atype);
  else
    return 0;
}

//=================================================================================================

const char* StepAP214_Protocol::SchemaName(
  const occ::handle<Interface_InterfaceModel>& theModel) const
{
  occ::handle<StepData_StepModel> aModel1 = occ::down_cast<StepData_StepModel>(theModel);
  const DESTEP_Parameters::WriteMode_StepSchema aSchema =
    aModel1.IsNull() ? DESTEP_Parameters::WriteMode_StepSchema_AP214IS
                     : aModel1->InternalParameters.WriteSchema;
  switch (aSchema)
  {
    case DESTEP_Parameters::WriteMode_StepSchema_AP203:
      return schemaAP203;
    case DESTEP_Parameters::WriteMode_StepSchema_AP214IS:
      return schemaAP214IS;
    case DESTEP_Parameters::WriteMode_StepSchema_AP242DIS:
      return schemaAP242DIS;
    case DESTEP_Parameters::WriteMode_StepSchema_AP214CD:
      return schemaAP214CD;
    case DESTEP_Parameters::WriteMode_StepSchema_AP214DIS:
    default:
      return schemaAP214DIS;
  }
}

//=================================================================================================

int StepAP214_Protocol::NbResources() const
{
  return 1;
}

//=================================================================================================

occ::handle<Interface_Protocol> StepAP214_Protocol::Resource(const int /*num*/) const
{
  return HeaderSection::Protocol();
}
