

#include <Interface_Check.hpp>
#include <Interface_ParamType.hpp>
#include <Interface_ReaderLib.hpp>
#include "RWStepAP214_ReadWriteModule.hpp"
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepData_WriterLib.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWStepAP214_ReadWriteModule, StepData_ReadWriteModule)

#include <MoniTool_Macros.hpp>

#include <StepBasic_Address.hpp>
#include <StepShape_AdvancedBrepShapeRepresentation.hpp>
#include <StepShape_AdvancedFace.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>

#include <StepVisual_AnnotationText.hpp>
#include <StepVisual_AnnotationTextOccurrence.hpp>

#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationContextElement.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_ApprovalRelationship.hpp>
#include <StepBasic_ApprovalRole.hpp>
#include <StepBasic_ApprovalStatus.hpp>
#include <StepBasic_AreaUnit.hpp>
#include <StepVisual_AreaInSet.hpp>
#include <StepBasic_VolumeUnit.hpp>
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

#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_BSplineCurve.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_BSplineSurface.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepVisual_BackgroundColour.hpp>
#include <StepGeom_BezierCurve.hpp>
#include <StepGeom_BezierSurface.hpp>
#include <StepShape_Block.hpp>
#include <StepShape_BooleanResult.hpp>
#include <StepGeom_BoundaryCurve.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <StepShape_BoxDomain.hpp>
#include <StepShape_BoxedHalfSpace.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepBasic_CalendarDate.hpp>
#include <StepVisual_CameraImage.hpp>
#include <StepVisual_CameraModel.hpp>
#include <StepVisual_CameraModelD2.hpp>
#include <StepVisual_CameraModelD3.hpp>
#include <StepVisual_CameraUsage.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_CartesianTransformationOperator.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_Circle.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_ColourRgb.hpp>
#include <StepVisual_ColourSpecification.hpp>
#include <StepGeom_CompositeCurve.hpp>
#include <StepGeom_CompositeCurveOnSurface.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>

#include <StepVisual_CompositeText.hpp>

#include <StepVisual_CompositeTextWithExtent.hpp>

#include <StepGeom_Conic.hpp>
#include <StepGeom_ConicalSurface.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepVisual_ContextDependentInvisibility.hpp>
#include <StepVisual_ContextDependentOverRidingStyledItem.hpp>
#include <StepBasic_ConversionBasedUnit.hpp>
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>

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

#include <StepRepr_DefinitionalRepresentation.hpp>
#include <StepGeom_DegeneratePcurve.hpp>
#include <StepGeom_DegenerateToroidalSurface.hpp>
#include <StepRepr_DescriptiveRepresentationItem.hpp>

#include <StepBasic_DimensionalExponents.hpp>
#include <StepGeom_Direction.hpp>

#include <StepVisual_DraughtingAnnotationOccurrence.hpp>

#include <StepVisual_DraughtingPreDefinedColour.hpp>
#include <StepVisual_DraughtingPreDefinedCurveFont.hpp>

#include <StepShape_Edge.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepGeom_ElementarySurface.hpp>
#include <StepGeom_Ellipse.hpp>
#include <StepGeom_EvaluatedDegeneratePcurve.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepVisual_ExternallyDefinedCurveFont.hpp>

#include <StepBasic_ExternallyDefinedItem.hpp>

#include <StepVisual_ExternallyDefinedTextFont.hpp>

#include <StepShape_ExtrudedAreaSolid.hpp>
#include <StepShape_Face.hpp>

#include <StepShape_FaceBound.hpp>
#include <StepShape_FaceOuterBound.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepShapeRepresentation.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_FillAreaStyleColour.hpp>

#include <StepRepr_FunctionallyDefinedTransformation.hpp>
#include <StepShape_GeometricCurveSet.hpp>
#include <StepGeom_GeometricRepresentationContext.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepShape_GeometricSet.hpp>
#include <StepShape_GeometricallyBoundedSurfaceShapeRepresentation.hpp>
#include <StepShape_GeometricallyBoundedWireframeShapeRepresentation.hpp>
#include <StepRepr_GlobalUncertaintyAssignedContext.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <StepBasic_GeneralPropertyAssociation.hpp>
#include <StepBasic_GeneralPropertyRelationship.hpp>
#include <StepBasic_Group.hpp>
#include <StepBasic_GroupRelationship.hpp>
#include <StepShape_HalfSpaceSolid.hpp>
#include <StepGeom_Hyperbola.hpp>
#include <StepGeom_IntersectionCurve.hpp>
#include <StepVisual_Invisibility.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
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

#include <StepBasic_NamedUnit.hpp>
#include <StepGeom_OffsetCurve3d.hpp>
#include <StepGeom_OffsetSurface.hpp>

#include <StepShape_OpenShell.hpp>
#include <StepBasic_OrdinalDate.hpp>
#include <StepBasic_Organization.hpp>
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
#include <StepBasic_Person.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>
#include <StepBasic_PersonalAddress.hpp>
#include <StepGeom_Placement.hpp>
#include <StepVisual_PlanarBox.hpp>
#include <StepVisual_PlanarExtent.hpp>
#include <StepGeom_Plane.hpp>
#include <StepBasic_PlaneAngleMeasureWithUnit.hpp>
#include <StepBasic_PlaneAngleUnit.hpp>
#include <StepGeom_Point.hpp>
#include <StepGeom_PointOnCurve.hpp>
#include <StepGeom_PointOnSurface.hpp>
#include <StepGeom_PointReplica.hpp>
#include <StepVisual_PointStyle.hpp>
#include <StepShape_PolyLoop.hpp>
#include <StepGeom_Polyline.hpp>
#include <StepVisual_PreDefinedColour.hpp>
#include <StepVisual_PreDefinedCurveFont.hpp>
#include <StepVisual_PreDefinedItem.hpp>

#include <StepVisual_PreDefinedTextFont.hpp>

#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_PresentationRepresentation.hpp>
#include <StepVisual_PresentationSet.hpp>
#include <StepVisual_PresentationSize.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <StepVisual_PresentationStyleByContext.hpp>
#include <StepVisual_PresentationView.hpp>
#include <StepVisual_RepositionedTessellatedGeometricSet.hpp>
#include <StepVisual_RepositionedTessellatedItem.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductCategory.hpp>
#include <StepBasic_ProductContext.hpp>

#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionFormationWithSpecifiedSource.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepBasic_ProductRelatedProductCategory.hpp>
#include <StepBasic_ProductType.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <StepGeom_QuasiUniformCurve.hpp>
#include <StepGeom_QuasiUniformSurface.hpp>
#include <StepBasic_RatioMeasureWithUnit.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <StepGeom_RectangularCompositeSurface.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>
#include <StepAP214_RepItemGroup.hpp>
#include <StepGeom_ReparametrisedCompositeCurveSegment.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationMap.hpp>
#include <StepRepr_RepresentationRelationship.hpp>
#include <StepShape_RevolvedAreaSolid.hpp>
#include <StepShape_RightAngularWedge.hpp>
#include <StepShape_RightCircularCone.hpp>
#include <StepShape_RightCircularCylinder.hpp>
#include <StepGeom_SeamCurve.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepBasic_SecurityClassificationLevel.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <StepRepr_FeatureForDatumTargetRelationship.hpp>
#include <StepRepr_ShapeAspectTransition.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>
#include <StepBasic_SiUnit.hpp>
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

#include <StepVisual_Template.hpp>
#include <StepVisual_TemplateInstance.hpp>

#include <StepVisual_TextLiteral.hpp>

#include <StepVisual_TextStyle.hpp>
#include <StepVisual_TextStyleForDefinedFont.hpp>
#include <StepVisual_TextStyleWithBoxCharacteristics.hpp>

#include <StepShape_TopologicalRepresentationItem.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <StepShape_Torus.hpp>
#include <StepShape_TransitionalShapeRepresentation.hpp>
#include <StepGeom_TrimmedCurve.hpp>

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

#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp>
#include <StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.hpp>
#include <StepBasic_ConversionBasedUnitAndSolidAngleUnit.hpp>
#include <StepBasic_SiUnitAndSolidAngleUnit.hpp>
#include <StepBasic_SolidAngleUnit.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepBasic_MechanicalContext.hpp>

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
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepVisual_PresentedItemRepresentation.hpp>
#include <StepVisual_PresentationLayerUsage.hpp>

#include <StepAP214_AutoDesignDocumentReference.hpp>
#include <StepBasic_Document.hpp>
#include <StepBasic_DigitalDocument.hpp>
#include <StepBasic_DocumentRelationship.hpp>
#include <StepBasic_DocumentType.hpp>
#include <StepBasic_DocumentUsageConstraint.hpp>
#include <StepBasic_Effectivity.hpp>
#include <StepBasic_ProductDefinitionEffectivity.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>

#include <StepBasic_ProductDefinitionWithAssociatedDocuments.hpp>
#include <StepBasic_PhysicallyModeledProductDefinition.hpp>

#include <StepRepr_ProductDefinitionUsage.hpp>
#include <StepRepr_MakeFromUsageOption.hpp>
#include <StepRepr_AssemblyComponentUsage.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_PromissoryUsageOccurrence.hpp>
#include <StepRepr_QuantifiedAssemblyComponentUsage.hpp>
#include <StepRepr_SpecifiedHigherUsageOccurrence.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <StepRepr_SuppliedPartRelationship.hpp>
#include <StepRepr_ExternallyDefinedRepresentation.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_ShapeRepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_MaterialDesignation.hpp>

#include <StepShape_ContextDependentShapeRepresentation.hpp>

#include <StepVisual_SurfaceStyleTransparent.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuse.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular.hpp>
#include <StepVisual_SurfaceStyleRendering.hpp>
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

#include "../RWStepVisual/RWStepVisual_RWTessellatedConnectingEdge.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedEdge.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedPointSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedShapeRepresentation.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedShell.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedSolid.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedStructuredItem.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedVertex.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedWire.hpp"
#include "../RWStepVisual/RWStepVisual_RWTriangulatedFace.hpp"
#include "../RWStepVisual/RWStepVisual_RWComplexTriangulatedFace.hpp"
#include "../RWStepVisual/RWStepVisual_RWComplexTriangulatedSurfaceSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWCubicBezierTessellatedEdge.hpp"
#include "../RWStepVisual/RWStepVisual_RWCubicBezierTriangulatedFace.hpp"
#include "../RWStepVisual/RWStepVisual_RWTriangulatedSurfaceSet.hpp"

#include "../RWStepBasic/RWStepBasic_RWAddress.hpp"
#include "../RWStepShape/RWStepShape_RWAdvancedBrepShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWAdvancedFace.hpp"

#include "../RWStepBasic/RWStepBasic_RWApplicationContext.hpp"
#include "../RWStepBasic/RWStepBasic_RWApplicationContextElement.hpp"
#include "../RWStepBasic/RWStepBasic_RWApplicationProtocolDefinition.hpp"
#include "../RWStepBasic/RWStepBasic_RWApproval.hpp"
#include "../RWStepBasic/RWStepBasic_RWApprovalPersonOrganization.hpp"
#include "../RWStepBasic/RWStepBasic_RWApprovalRelationship.hpp"
#include "../RWStepBasic/RWStepBasic_RWApprovalRole.hpp"
#include "../RWStepBasic/RWStepBasic_RWApprovalStatus.hpp"
#include "../RWStepVisual/RWStepVisual_RWAreaInSet.hpp"
#include "RWStepAP214_RWAutoDesignActualDateAndTimeAssignment.hpp"
#include "RWStepAP214_RWAutoDesignActualDateAssignment.hpp"
#include "RWStepAP214_RWAutoDesignApprovalAssignment.hpp"
#include "RWStepAP214_RWAutoDesignDateAndPersonAssignment.hpp"
#include "RWStepAP214_RWAutoDesignGroupAssignment.hpp"
#include "RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment.hpp"
#include "RWStepAP214_RWAutoDesignNominalDateAssignment.hpp"
#include "RWStepAP214_RWAutoDesignOrganizationAssignment.hpp"
#include "RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment.hpp"
#include "RWStepAP214_RWAutoDesignPresentedItem.hpp"
#include "RWStepAP214_RWAutoDesignSecurityClassificationAssignment.hpp"

#include "../RWStepGeom/RWStepGeom_RWAxis1Placement.hpp"
#include "../RWStepGeom/RWStepGeom_RWAxis2Placement2d.hpp"
#include "../RWStepGeom/RWStepGeom_RWAxis2Placement3d.hpp"
#include "../RWStepGeom/RWStepGeom_RWBSplineCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBSplineCurveWithKnots.hpp"
#include "../RWStepGeom/RWStepGeom_RWBSplineSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWBSplineSurfaceWithKnots.hpp"
#include "../RWStepVisual/RWStepVisual_RWBackgroundColour.hpp"
#include "../RWStepGeom/RWStepGeom_RWBezierCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBezierSurface.hpp"
#include "../RWStepShape/RWStepShape_RWBlock.hpp"
#include "../RWStepShape/RWStepShape_RWBooleanResult.hpp"
#include "../RWStepGeom/RWStepGeom_RWBoundaryCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBoundedCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBoundedSurface.hpp"
#include "../RWStepShape/RWStepShape_RWBoxDomain.hpp"
#include "../RWStepShape/RWStepShape_RWBoxedHalfSpace.hpp"
#include "../RWStepShape/RWStepShape_RWBrepWithVoids.hpp"
#include "../RWStepBasic/RWStepBasic_RWCalendarDate.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraImage.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraModel.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraModelD2.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraModelD3.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraUsage.hpp"
#include "../RWStepGeom/RWStepGeom_RWCartesianPoint.hpp"
#include "../RWStepGeom/RWStepGeom_RWCartesianTransformationOperator.hpp"
#include "../RWStepGeom/RWStepGeom_RWCartesianTransformationOperator3d.hpp"
#include "../RWStepGeom/RWStepGeom_RWCircle.hpp"
#include "../RWStepShape/RWStepShape_RWClosedShell.hpp"
#include "../RWStepVisual/RWStepVisual_RWColour.hpp"
#include "../RWStepVisual/RWStepVisual_RWColourRgb.hpp"
#include "../RWStepVisual/RWStepVisual_RWColourSpecification.hpp"
#include "../RWStepGeom/RWStepGeom_RWCompositeCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWCompositeCurveOnSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWCompositeCurveSegment.hpp"
#include "../RWStepVisual/RWStepVisual_RWCompositeText.hpp"

#include "../RWStepVisual/RWStepVisual_RWCompositeTextWithExtent.hpp"

#include "../RWStepGeom/RWStepGeom_RWConic.hpp"
#include "../RWStepGeom/RWStepGeom_RWConicalSurface.hpp"
#include "../RWStepShape/RWStepShape_RWConnectedFaceSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWContextDependentInvisibility.hpp"
#include "../RWStepVisual/RWStepVisual_RWContextDependentOverRidingStyledItem.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWCoordinatedUniversalTimeOffset.hpp"

#include "../RWStepShape/RWStepShape_RWCsgShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWCsgSolid.hpp"
#include "../RWStepGeom/RWStepGeom_RWCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWCurveBoundedSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWCurveReplica.hpp"
#include "../RWStepVisual/RWStepVisual_RWCurveStyle.hpp"
#include "../RWStepVisual/RWStepVisual_RWCurveStyleFont.hpp"
#include "../RWStepVisual/RWStepVisual_RWCurveStyleFontPattern.hpp"
#include "../RWStepGeom/RWStepGeom_RWCylindricalSurface.hpp"
#include "../RWStepBasic/RWStepBasic_RWDate.hpp"
#include "../RWStepBasic/RWStepBasic_RWDateAndTime.hpp"
#include "../RWStepBasic/RWStepBasic_RWDateRole.hpp"
#include "../RWStepBasic/RWStepBasic_RWDateTimeRole.hpp"

#include "../RWStepRepr/RWStepRepr_RWDefinitionalRepresentation.hpp"
#include "../RWStepGeom/RWStepGeom_RWDegeneratePcurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWDegenerateToroidalSurface.hpp"
#include "../RWStepRepr/RWStepRepr_RWDescriptiveRepresentationItem.hpp"

#include "../RWStepBasic/RWStepBasic_RWDimensionalExponents.hpp"
#include "../RWStepGeom/RWStepGeom_RWDirection.hpp"

#include "../RWStepVisual/RWStepVisual_RWDraughtingPreDefinedColour.hpp"
#include "../RWStepVisual/RWStepVisual_RWDraughtingPreDefinedCurveFont.hpp"

#include "../RWStepShape/RWStepShape_RWEdge.hpp"
#include "../RWStepShape/RWStepShape_RWEdgeCurve.hpp"
#include "../RWStepShape/RWStepShape_RWEdgeLoop.hpp"
#include "../RWStepGeom/RWStepGeom_RWElementarySurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWEllipse.hpp"
#include "../RWStepGeom/RWStepGeom_RWEvaluatedDegeneratePcurve.hpp"
#include "../RWStepBasic/RWStepBasic_RWExternalSource.hpp"
#include "../RWStepVisual/RWStepVisual_RWExternallyDefinedCurveFont.hpp"

#include "../RWStepBasic/RWStepBasic_RWExternallyDefinedItem.hpp"

#include "../RWStepShape/RWStepShape_RWExtrudedAreaSolid.hpp"
#include "../RWStepShape/RWStepShape_RWFace.hpp"

#include "../RWStepShape/RWStepShape_RWFaceBound.hpp"
#include "../RWStepShape/RWStepShape_RWFaceOuterBound.hpp"
#include "../RWStepShape/RWStepShape_RWFaceSurface.hpp"
#include "../RWStepShape/RWStepShape_RWFacetedBrep.hpp"
#include "../RWStepShape/RWStepShape_RWFacetedBrepShapeRepresentation.hpp"
#include "../RWStepVisual/RWStepVisual_RWFillAreaStyle.hpp"
#include "../RWStepVisual/RWStepVisual_RWFillAreaStyleColour.hpp"

#include "../RWStepRepr/RWStepRepr_RWFunctionallyDefinedTransformation.hpp"
#include "../RWStepShape/RWStepShape_RWGeometricCurveSet.hpp"
#include "../RWStepGeom/RWStepGeom_RWGeometricRepresentationContext.hpp"
#include "../RWStepGeom/RWStepGeom_RWGeometricRepresentationItem.hpp"
#include "../RWStepShape/RWStepShape_RWGeometricSet.hpp"
#include "../RWStepShape/RWStepShape_RWGeometricallyBoundedSurfaceShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWGeometricallyBoundedWireframeShapeRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWGlobalUncertaintyAssignedContext.hpp"
#include "../RWStepRepr/RWStepRepr_RWGlobalUnitAssignedContext.hpp"
#include "../RWStepBasic/RWStepBasic_RWGeneralPropertyAssociation.hpp"
#include "../RWStepBasic/RWStepBasic_RWGeneralPropertyRelationship.hpp"
#include "../RWStepBasic/RWStepBasic_RWGroup.hpp"
#include "../RWStepBasic/RWStepBasic_RWGroupRelationship.hpp"
#include "../RWStepShape/RWStepShape_RWHalfSpaceSolid.hpp"
#include "../RWStepGeom/RWStepGeom_RWHyperbola.hpp"
#include "../RWStepGeom/RWStepGeom_RWIntersectionCurve.hpp"
#include "../RWStepVisual/RWStepVisual_RWInvisibility.hpp"
#include "../RWStepBasic/RWStepBasic_RWLengthMeasureWithUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWLengthUnit.hpp"
#include "../RWStepGeom/RWStepGeom_RWLine.hpp"
#include "../RWStepBasic/RWStepBasic_RWLocalTime.hpp"
#include "../RWStepShape/RWStepShape_RWLoop.hpp"
#include "../RWStepShape/RWStepShape_RWManifoldSolidBrep.hpp"
#include "../RWStepShape/RWStepShape_RWManifoldSurfaceShapeRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWMappedItem.hpp"
#include "../RWStepBasic/RWStepBasic_RWMeasureWithUnit.hpp"
#include "../RWStepRepr/RWStepRepr_RWMechanicalDesignAndDraughtingRelationship.hpp"
#include "../RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationArea.hpp"
#include "../RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationRepresentation.hpp"

#include "../RWStepBasic/RWStepBasic_RWNamedUnit.hpp"
#include "../RWStepGeom/RWStepGeom_RWOffsetCurve3d.hpp"
#include "../RWStepGeom/RWStepGeom_RWOffsetSurface.hpp"

#include "../RWStepShape/RWStepShape_RWOpenShell.hpp"
#include "../RWStepBasic/RWStepBasic_RWOrdinalDate.hpp"
#include "../RWStepBasic/RWStepBasic_RWOrganization.hpp"
#include "../RWStepBasic/RWStepBasic_RWOrganizationRole.hpp"
#include "../RWStepBasic/RWStepBasic_RWOrganizationalAddress.hpp"
#include "../RWStepShape/RWStepShape_RWOrientedClosedShell.hpp"
#include "../RWStepShape/RWStepShape_RWOrientedEdge.hpp"
#include "../RWStepShape/RWStepShape_RWOrientedFace.hpp"
#include "../RWStepShape/RWStepShape_RWOrientedOpenShell.hpp"
#include "../RWStepShape/RWStepShape_RWOrientedPath.hpp"
#include "../RWStepGeom/RWStepGeom_RWOuterBoundaryCurve.hpp"
#include "../RWStepVisual/RWStepVisual_RWOverRidingStyledItem.hpp"
#include "../RWStepGeom/RWStepGeom_RWParabola.hpp"
#include "../RWStepRepr/RWStepRepr_RWParametricRepresentationContext.hpp"
#include "../RWStepShape/RWStepShape_RWPath.hpp"
#include "../RWStepGeom/RWStepGeom_RWPcurve.hpp"
#include "../RWStepBasic/RWStepBasic_RWPerson.hpp"
#include "../RWStepBasic/RWStepBasic_RWPersonAndOrganization.hpp"
#include "../RWStepBasic/RWStepBasic_RWPersonAndOrganizationRole.hpp"
#include "../RWStepBasic/RWStepBasic_RWPersonalAddress.hpp"
#include "../RWStepGeom/RWStepGeom_RWPlacement.hpp"
#include "../RWStepVisual/RWStepVisual_RWPlanarBox.hpp"
#include "../RWStepVisual/RWStepVisual_RWPlanarExtent.hpp"
#include "../RWStepGeom/RWStepGeom_RWPlane.hpp"
#include "../RWStepBasic/RWStepBasic_RWPlaneAngleMeasureWithUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWPlaneAngleUnit.hpp"
#include "../RWStepGeom/RWStepGeom_RWPoint.hpp"
#include "../RWStepGeom/RWStepGeom_RWPointOnCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWPointOnSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWPointReplica.hpp"
#include "../RWStepVisual/RWStepVisual_RWPointStyle.hpp"
#include "../RWStepShape/RWStepShape_RWPolyLoop.hpp"
#include "../RWStepGeom/RWStepGeom_RWPolyline.hpp"
#include "../RWStepVisual/RWStepVisual_RWPreDefinedColour.hpp"
#include "../RWStepVisual/RWStepVisual_RWPreDefinedCurveFont.hpp"
#include "../RWStepVisual/RWStepVisual_RWPreDefinedItem.hpp"

#include "../RWStepVisual/RWStepVisual_RWPresentationArea.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationLayerAssignment.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationRepresentation.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationSize.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationStyleAssignment.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationStyleByContext.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationView.hpp"
#include "../RWStepVisual/RWStepVisual_RWRepositionedTessellatedGeometricSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWRepositionedTessellatedItem.hpp"
#include "../RWStepBasic/RWStepBasic_RWProduct.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductCategory.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductContext.hpp"

#include "../RWStepBasic/RWStepBasic_RWProductDefinition.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductDefinitionContext.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductDefinitionFormation.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource.hpp"
#include "../RWStepRepr/RWStepRepr_RWProductDefinitionShape.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductRelatedProductCategory.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductType.hpp"
#include "../RWStepRepr/RWStepRepr_RWPropertyDefinition.hpp"
#include "../RWStepRepr/RWStepRepr_RWPropertyDefinitionRepresentation.hpp"
#include "../RWStepGeom/RWStepGeom_RWQuasiUniformCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWQuasiUniformSurface.hpp"
#include "../RWStepBasic/RWStepBasic_RWRatioMeasureWithUnit.hpp"
#include "../RWStepGeom/RWStepGeom_RWRationalBSplineCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWRationalBSplineSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWRectangularCompositeSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWRectangularTrimmedSurface.hpp"
#include "RWStepAP214_RWRepItemGroup.hpp"
#include "../RWStepGeom/RWStepGeom_RWReparametrisedCompositeCurveSegment.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationContext.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationItem.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationMap.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationRelationship.hpp"
#include "../RWStepShape/RWStepShape_RWRevolvedAreaSolid.hpp"
#include "../RWStepShape/RWStepShape_RWRightAngularWedge.hpp"
#include "../RWStepShape/RWStepShape_RWRightCircularCone.hpp"
#include "../RWStepShape/RWStepShape_RWRightCircularCylinder.hpp"
#include "../RWStepGeom/RWStepGeom_RWSeamCurve.hpp"
#include "../RWStepBasic/RWStepBasic_RWSecurityClassification.hpp"
#include "../RWStepBasic/RWStepBasic_RWSecurityClassificationLevel.hpp"
#include "../RWStepRepr/RWStepRepr_RWShapeAspect.hpp"
#include "../RWStepRepr/RWStepRepr_RWShapeAspectRelationship.hpp"
#include "../RWStepRepr/RWStepRepr_RWFeatureForDatumTargetRelationship.hpp"
#include "../RWStepRepr/RWStepRepr_RWShapeAspectTransition.hpp"
#include "../RWStepShape/RWStepShape_RWShapeDefinitionRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWShellBasedSurfaceModel.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSolidAngleMeasureWithUnit.hpp"
#include "../RWStepShape/RWStepShape_RWSolidModel.hpp"
#include "../RWStepShape/RWStepShape_RWSolidReplica.hpp"
#include "../RWStepShape/RWStepShape_RWSphere.hpp"
#include "../RWStepGeom/RWStepGeom_RWSphericalSurface.hpp"
#include "../RWStepVisual/RWStepVisual_RWStyledItem.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurfaceCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurfaceOfLinearExtrusion.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurfaceOfRevolution.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurfaceCurveAndBoundedCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurfacePatch.hpp"
#include "../RWStepGeom/RWStepGeom_RWSurfaceReplica.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceSideStyle.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleBoundary.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleControlGrid.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleFillArea.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleParameterLine.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleSegmentationCurve.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleSilhouette.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleUsage.hpp"
#include "../RWStepShape/RWStepShape_RWSweptAreaSolid.hpp"
#include "../RWStepGeom/RWStepGeom_RWSweptSurface.hpp"

#include "../RWStepVisual/RWStepVisual_RWTemplate.hpp"
#include "../RWStepVisual/RWStepVisual_RWTemplateInstance.hpp"

#include "../RWStepVisual/RWStepVisual_RWTextLiteral.hpp"

#include "../RWStepVisual/RWStepVisual_RWTextStyle.hpp"
#include "../RWStepVisual/RWStepVisual_RWTextStyleForDefinedFont.hpp"
#include "../RWStepVisual/RWStepVisual_RWTextStyleWithBoxCharacteristics.hpp"

#include "../RWStepShape/RWStepShape_RWTopologicalRepresentationItem.hpp"
#include "../RWStepGeom/RWStepGeom_RWToroidalSurface.hpp"
#include "../RWStepShape/RWStepShape_RWTorus.hpp"
#include "../RWStepShape/RWStepShape_RWTransitionalShapeRepresentation.hpp"
#include "../RWStepGeom/RWStepGeom_RWTrimmedCurve.hpp"

#include "../RWStepBasic/RWStepBasic_RWUncertaintyMeasureWithUnit.hpp"
#include "../RWStepGeom/RWStepGeom_RWUniformCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWUniformSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWVector.hpp"
#include "../RWStepShape/RWStepShape_RWVertex.hpp"
#include "../RWStepShape/RWStepShape_RWVertexLoop.hpp"
#include "../RWStepShape/RWStepShape_RWVertexPoint.hpp"
#include "../RWStepVisual/RWStepVisual_RWViewVolume.hpp"
#include "../RWStepBasic/RWStepBasic_RWWeekOfYearAndDayDate.hpp"
#include "../RWStepGeom/RWStepGeom_RWUniformCurveAndRationalBSplineCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBezierCurveAndRationalBSplineCurve.hpp"
#include "../RWStepGeom/RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.hpp"
#include "../RWStepGeom/RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndLengthUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndPlaneAngleUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndLengthUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit.hpp"
#include "../RWStepGeom/RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.hpp"
#include "../RWStepShape/RWStepShape_RWLoopAndPath.hpp"

#include "../RWStepGeom/RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp"
#include "../RWStepGeom/RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndSolidAngleUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndSolidAngleUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSolidAngleUnit.hpp"
#include "../RWStepShape/RWStepShape_RWFacetedBrepAndBrepWithVoids.hpp"
#include "../RWStepBasic/RWStepBasic_RWMechanicalContext.hpp"

#include "../RWStepBasic/RWStepBasic_RWSiUnitAndRatioUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndTimeUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndRatioUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndTimeUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWApprovalDateTime.hpp"

#include "../RWStepBasic/RWStepBasic_RWDerivedUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWDerivedUnitElement.hpp"
#include "../RWStepRepr/RWStepRepr_RWItemDefinedTransformation.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentedItemRepresentation.hpp"
#include "../RWStepVisual/RWStepVisual_RWPresentationLayerUsage.hpp"

#include "RWStepAP214_RWAutoDesignDocumentReference.hpp"
#include "../RWStepBasic/RWStepBasic_RWDocument.hpp"
#include "../RWStepBasic/RWStepBasic_RWDocumentRelationship.hpp"
#include "../RWStepBasic/RWStepBasic_RWDocumentType.hpp"
#include "../RWStepBasic/RWStepBasic_RWDocumentUsageConstraint.hpp"
#include "../RWStepBasic/RWStepBasic_RWEffectivity.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductDefinitionEffectivity.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductDefinitionRelationship.hpp"

#include "../RWStepBasic/RWStepBasic_RWProductDefinitionWithAssociatedDocuments.hpp"

#include "../RWStepRepr/RWStepRepr_RWMakeFromUsageOption.hpp"
#include "../RWStepRepr/RWStepRepr_RWAssemblyComponentUsage.hpp"
#include "../RWStepRepr/RWStepRepr_RWQuantifiedAssemblyComponentUsage.hpp"
#include "../RWStepRepr/RWStepRepr_RWSpecifiedHigherUsageOccurrence.hpp"
#include "../RWStepRepr/RWStepRepr_RWAssemblyComponentUsageSubstitute.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationRelationshipWithTransformation.hpp"
#include "../RWStepRepr/RWStepRepr_RWShapeRepresentationRelationshipWithTransformation.hpp"
#include "../RWStepRepr/RWStepRepr_RWMaterialDesignation.hpp"

#include "../RWStepShape/RWStepShape_RWContextDependentShapeRepresentation.hpp"

#include <StepAP214_AppliedDateAndTimeAssignment.hpp>
#include <StepAP214_AppliedDateAssignment.hpp>
#include <StepAP214_AppliedApprovalAssignment.hpp>
#include <StepAP214_AppliedDocumentReference.hpp>
#include <StepAP214_AppliedGroupAssignment.hpp>
#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_AppliedPersonAndOrganizationAssignment.hpp>
#include <StepAP214_AppliedPresentedItem.hpp>
#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_CharacterizedObject.hpp>
#include <StepShape_ExtrudedFaceSolid.hpp>
#include <StepShape_RevolvedFaceSolid.hpp>
#include <StepShape_SweptFaceSolid.hpp>

#include "RWStepAP214_RWAppliedDateAndTimeAssignment.hpp"
#include "RWStepAP214_RWAppliedDateAssignment.hpp"
#include "RWStepAP214_RWAppliedApprovalAssignment.hpp"
#include "RWStepAP214_RWAppliedDocumentReference.hpp"
#include "RWStepAP214_RWAppliedGroupAssignment.hpp"
#include "RWStepAP214_RWAppliedOrganizationAssignment.hpp"
#include "RWStepAP214_RWAppliedPersonAndOrganizationAssignment.hpp"
#include "RWStepAP214_RWAppliedPresentedItem.hpp"
#include "RWStepAP214_RWAppliedSecurityClassificationAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWDocumentFile.hpp"
#include "../RWStepBasic/RWStepBasic_RWCharacterizedObject.hpp"
#include "../RWStepShape/RWStepShape_RWExtrudedFaceSolid.hpp"
#include "../RWStepShape/RWStepShape_RWRevolvedFaceSolid.hpp"
#include "../RWStepShape/RWStepShape_RWSweptFaceSolid.hpp"

#include <StepRepr_MeasureRepresentationItem.hpp>
#include "../RWStepRepr/RWStepRepr_RWMeasureRepresentationItem.hpp"
#include <StepBasic_SiUnitAndAreaUnit.hpp>
#include <StepBasic_SiUnitAndVolumeUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndAreaUnit.hpp>
#include <StepBasic_ConversionBasedUnitAndVolumeUnit.hpp>
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndAreaUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndVolumeUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndAreaUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndVolumeUnit.hpp"

#include <StepBasic_Action.hpp>
#include <StepBasic_ActionAssignment.hpp>
#include <StepBasic_ActionMethod.hpp>
#include <StepBasic_ActionRequestAssignment.hpp>
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
#include "../RWStepBasic/RWStepBasic_RWAction.hpp"
#include "../RWStepBasic/RWStepBasic_RWActionAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWActionMethod.hpp"
#include "../RWStepBasic/RWStepBasic_RWActionRequestAssignment.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignApproval.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignCertification.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignContract.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignDateAndTimeAssignment.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignPersonAndOrganizationAssignment.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignSecurityClassification.hpp"
#include "../RWStepAP203/RWStepAP203_RWCcDesignSpecificationReference.hpp"
#include "../RWStepBasic/RWStepBasic_RWCertification.hpp"
#include "../RWStepBasic/RWStepBasic_RWCertificationAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWCertificationType.hpp"
#include "../RWStepAP203/RWStepAP203_RWChange.hpp"
#include "../RWStepAP203/RWStepAP203_RWChangeRequest.hpp"
#include "../RWStepRepr/RWStepRepr_RWConfigurationDesign.hpp"
#include "../RWStepRepr/RWStepRepr_RWConfigurationEffectivity.hpp"
#include "../RWStepBasic/RWStepBasic_RWContract.hpp"
#include "../RWStepBasic/RWStepBasic_RWContractAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWContractType.hpp"
#include "../RWStepRepr/RWStepRepr_RWProductConcept.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductConceptContext.hpp"
#include "../RWStepAP203/RWStepAP203_RWStartRequest.hpp"
#include "../RWStepAP203/RWStepAP203_RWStartWork.hpp"
#include "../RWStepBasic/RWStepBasic_RWVersionedActionRequest.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductCategoryRelationship.hpp"
#include "../RWStepBasic/RWStepBasic_RWActionRequestSolution.hpp"

#include <StepVisual_DraughtingModel.hpp>
#include "../RWStepVisual/RWStepVisual_RWDraughtingModel.hpp"

#include <StepShape_AngularLocation.hpp>
#include <StepShape_AngularSize.hpp>
#include <StepShape_DimensionalCharacteristicRepresentation.hpp>
#include <StepShape_DimensionalLocation.hpp>
#include <StepShape_DimensionalLocationWithPath.hpp>
#include <StepShape_DimensionalSize.hpp>
#include <StepShape_DimensionalSizeWithPath.hpp>
#include <StepShape_ShapeDimensionRepresentation.hpp>
#include "../RWStepShape/RWStepShape_RWAngularLocation.hpp"
#include "../RWStepShape/RWStepShape_RWAngularSize.hpp"
#include "../RWStepShape/RWStepShape_RWDimensionalCharacteristicRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWDimensionalLocation.hpp"
#include "../RWStepShape/RWStepShape_RWDimensionalLocationWithPath.hpp"
#include "../RWStepShape/RWStepShape_RWDimensionalSize.hpp"
#include "../RWStepShape/RWStepShape_RWDimensionalSizeWithPath.hpp"
#include "../RWStepShape/RWStepShape_RWShapeDimensionRepresentation.hpp"

#include <StepBasic_DocumentRepresentationType.hpp>
#include <StepBasic_ObjectRole.hpp>
#include <StepBasic_RoleAssociation.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <StepBasic_IdentificationAssignment.hpp>
#include <StepBasic_ExternalIdentificationAssignment.hpp>
#include <StepBasic_EffectivityAssignment.hpp>
#include <StepBasic_NameAssignment.hpp>
#include <StepBasic_GeneralProperty.hpp>
#include <StepAP214_Class.hpp>
#include <StepAP214_ExternallyDefinedClass.hpp>
#include <StepAP214_ExternallyDefinedGeneralProperty.hpp>
#include <StepAP214_AppliedExternalIdentificationAssignment.hpp>
#include "../RWStepBasic/RWStepBasic_RWDocumentRepresentationType.hpp"
#include "../RWStepBasic/RWStepBasic_RWObjectRole.hpp"
#include "../RWStepBasic/RWStepBasic_RWRoleAssociation.hpp"
#include "../RWStepBasic/RWStepBasic_RWIdentificationRole.hpp"
#include "../RWStepBasic/RWStepBasic_RWIdentificationAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWExternalIdentificationAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWEffectivityAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWNameAssignment.hpp"
#include "../RWStepBasic/RWStepBasic_RWGeneralProperty.hpp"
#include "RWStepAP214_RWClass.hpp"
#include "RWStepAP214_RWExternallyDefinedClass.hpp"
#include "RWStepAP214_RWExternallyDefinedGeneralProperty.hpp"
#include "RWStepAP214_RWAppliedExternalIdentificationAssignment.hpp"

#include <StepShape_DefinitionalRepresentationAndShapeRepresentation.hpp>
#include "../RWStepShape/RWStepShape_RWDefinitionalRepresentationAndShapeRepresentation.hpp"

#include <StepRepr_CompositeShapeAspect.hpp>
#include <StepRepr_DerivedShapeAspect.hpp>
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
#include <StepRepr_CompoundRepresentationItem.hpp>
#include <StepRepr_ValueRange.hpp>
#include <StepRepr_ShapeAspectDerivingRelationship.hpp>
#include "../RWStepShape/RWStepShape_RWLimitsAndFits.hpp"
#include "../RWStepShape/RWStepShape_RWToleranceValue.hpp"
#include "../RWStepShape/RWStepShape_RWMeasureQualification.hpp"
#include "../RWStepShape/RWStepShape_RWPlusMinusTolerance.hpp"
#include "../RWStepShape/RWStepShape_RWPrecisionQualifier.hpp"
#include "../RWStepShape/RWStepShape_RWTypeQualifier.hpp"
#include "../RWStepShape/RWStepShape_RWQualifiedRepresentationItem.hpp"
#include "../RWStepShape/RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem.hpp"
#include "../RWStepRepr/RWStepRepr_RWCompoundRepresentationItem.hpp"

#include <StepShape_CompoundShapeRepresentation.hpp>
#include <StepShape_ConnectedEdgeSet.hpp>
#include <StepShape_ConnectedFaceShapeRepresentation.hpp>
#include <StepShape_EdgeBasedWireframeModel.hpp>
#include <StepShape_EdgeBasedWireframeShapeRepresentation.hpp>
#include <StepShape_FaceBasedSurfaceModel.hpp>
#include <StepShape_NonManifoldSurfaceShapeRepresentation.hpp>
#include "../RWStepShape/RWStepShape_RWCompoundShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWConnectedEdgeSet.hpp"
#include "../RWStepShape/RWStepShape_RWConnectedFaceShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWEdgeBasedWireframeModel.hpp"
#include "../RWStepShape/RWStepShape_RWEdgeBasedWireframeShapeRepresentation.hpp"
#include "../RWStepShape/RWStepShape_RWFaceBasedSurfaceModel.hpp"
#include "../RWStepShape/RWStepShape_RWNonManifoldSurfaceShapeRepresentation.hpp"

#include <StepGeom_OrientedSurface.hpp>
#include <StepShape_Subface.hpp>
#include <StepShape_Subedge.hpp>
#include <StepShape_SeamEdge.hpp>
#include <StepShape_ConnectedFaceSubSet.hpp>

#include "../RWStepGeom/RWStepGeom_RWOrientedSurface.hpp"
#include "../RWStepShape/RWStepShape_RWSubface.hpp"
#include "../RWStepShape/RWStepShape_RWSubedge.hpp"
#include "../RWStepShape/RWStepShape_RWSeamEdge.hpp"
#include "../RWStepShape/RWStepShape_RWConnectedFaceSubSet.hpp"

#include <StepBasic_EulerAngles.hpp>
#include <StepBasic_MassUnit.hpp>
#include <StepBasic_ThermodynamicTemperatureUnit.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepElement_Curve3dElementDescriptor.hpp>
#include <StepElement_CurveElementEndReleasePacket.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>
#include <StepElement_CurveElementSectionDerivedDefinitions.hpp>
#include <StepElement_ElementDescriptor.hpp>
#include <StepElement_ElementMaterial.hpp>
#include <StepElement_Surface3dElementDescriptor.hpp>
#include <StepElement_SurfaceElementProperty.hpp>
#include <StepElement_SurfaceSection.hpp>
#include <StepElement_SurfaceSectionField.hpp>
#include <StepElement_SurfaceSectionFieldConstant.hpp>
#include <StepElement_SurfaceSectionFieldVarying.hpp>
#include <StepElement_UniformSurfaceSection.hpp>
#include <StepElement_Volume3dElementDescriptor.hpp>
#include <StepFEA_AlignedCurve3dElementCoordinateSystem.hpp>
#include <StepFEA_ArbitraryVolume3dElementCoordinateSystem.hpp>
#include <StepFEA_Curve3dElementProperty.hpp>
#include <StepFEA_Curve3dElementRepresentation.hpp>
#include <StepFEA_Node.hpp>
#include <StepFEA_CurveElementEndCoordinateSystem.hpp>
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
#include <StepFEA_FeaModel.hpp>
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
#include <StepFEA_SymmetricTensor22d.hpp>
#include <StepFEA_SymmetricTensor42d.hpp>
#include <StepFEA_SymmetricTensor43d.hpp>
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

#include "../RWStepBasic/RWStepBasic_RWEulerAngles.hpp"
#include "../RWStepBasic/RWStepBasic_RWMassUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWThermodynamicTemperatureUnit.hpp"
#include "../RWStepElement/RWStepElement_RWAnalysisItemWithinRepresentation.hpp"
#include "../RWStepElement/RWStepElement_RWCurve3dElementDescriptor.hpp"
#include "../RWStepElement/RWStepElement_RWCurveElementEndReleasePacket.hpp"
#include "../RWStepElement/RWStepElement_RWCurveElementSectionDefinition.hpp"
#include "../RWStepElement/RWStepElement_RWCurveElementSectionDerivedDefinitions.hpp"
#include "../RWStepElement/RWStepElement_RWElementDescriptor.hpp"
#include "../RWStepElement/RWStepElement_RWElementMaterial.hpp"
#include "../RWStepElement/RWStepElement_RWSurface3dElementDescriptor.hpp"
#include "../RWStepElement/RWStepElement_RWSurfaceElementProperty.hpp"
#include "../RWStepElement/RWStepElement_RWSurfaceSection.hpp"
#include "../RWStepElement/RWStepElement_RWSurfaceSectionField.hpp"
#include "../RWStepElement/RWStepElement_RWSurfaceSectionFieldConstant.hpp"
#include "../RWStepElement/RWStepElement_RWSurfaceSectionFieldVarying.hpp"
#include "../RWStepElement/RWStepElement_RWUniformSurfaceSection.hpp"
#include "../RWStepElement/RWStepElement_RWVolume3dElementDescriptor.hpp"
#include "../RWStepFEA/RWStepFEA_RWAlignedCurve3dElementCoordinateSystem.hpp"
#include "../RWStepFEA/RWStepFEA_RWArbitraryVolume3dElementCoordinateSystem.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurve3dElementProperty.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurve3dElementRepresentation.hpp"
#include "../RWStepFEA/RWStepFEA_RWNode.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurveElementEndOffset.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurveElementEndRelease.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurveElementInterval.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurveElementIntervalConstant.hpp"
#include "../RWStepFEA/RWStepFEA_RWDummyNode.hpp"
#include "../RWStepFEA/RWStepFEA_RWCurveElementLocation.hpp"
#include "../RWStepFEA/RWStepFEA_RWElementGeometricRelationship.hpp"
#include "../RWStepFEA/RWStepFEA_RWElementGroup.hpp"
#include "../RWStepFEA/RWStepFEA_RWElementRepresentation.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaAreaDensity.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaAxis2Placement3d.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaGroup.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaLinearElasticity.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaMassDensity.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentation.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentationItem.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaModel.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaModel3d.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaMoistureAbsorption.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaParametricPoint.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaRepresentationItem.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaShellBendingStiffness.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaShellMembraneStiffness.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaShellShearStiffness.hpp"
#include "../RWStepFEA/RWStepFEA_RWGeometricNode.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion.hpp"
#include "../RWStepFEA/RWStepFEA_RWNodeGroup.hpp"
#include "../RWStepFEA/RWStepFEA_RWNodeRepresentation.hpp"
#include "../RWStepFEA/RWStepFEA_RWNodeSet.hpp"
#include "../RWStepFEA/RWStepFEA_RWNodeWithSolutionCoordinateSystem.hpp"
#include "../RWStepFEA/RWStepFEA_RWNodeWithVector.hpp"
#include "../RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateDirection.hpp"
#include "../RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateSystem.hpp"
#include "../RWStepFEA/RWStepFEA_RWParametricSurface3dElementCoordinateSystem.hpp"
#include "../RWStepFEA/RWStepFEA_RWSurface3dElementRepresentation.hpp"
#include "../RWStepFEA/RWStepFEA_RWVolume3dElementRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWDataEnvironment.hpp"
#include "../RWStepRepr/RWStepRepr_RWMaterialPropertyRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWPropertyDefinitionRelationship.hpp"
#include "../RWStepShape/RWStepShape_RWPointRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWMaterialProperty.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaModelDefinition.hpp"
#include "../RWStepFEA/RWStepFEA_RWFreedomAndCoefficient.hpp"
#include "../RWStepFEA/RWStepFEA_RWFreedomsList.hpp"
#include "../RWStepBasic/RWStepBasic_RWProductDefinitionFormationRelationship.hpp"
#include "../RWStepFEA/RWStepFEA_RWNodeDefinition.hpp"
#include "../RWStepRepr/RWStepRepr_RWStructuralResponseProperty.hpp"
#include "../RWStepRepr/RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation.hpp"

#include <StepBasic_SiUnitAndMassUnit.hpp>
#include <StepBasic_SiUnitAndThermodynamicTemperatureUnit.hpp>
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndMassUnit.hpp"
#include "../RWStepBasic/RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit.hpp"
#include <StepFEA_AlignedSurface3dElementCoordinateSystem.hpp>
#include <StepFEA_ConstantSurface3dElementCoordinateSystem.hpp>
#include "../RWStepFEA/RWStepFEA_RWAlignedSurface3dElementCoordinateSystem.hpp"
#include "../RWStepFEA/RWStepFEA_RWConstantSurface3dElementCoordinateSystem.hpp"

#include <StepFEA_CurveElementIntervalLinearlyVarying.hpp>
#include <StepFEA_FeaCurveSectionGeometricRelationship.hpp>
#include <StepFEA_FeaSurfaceSectionGeometricRelationship.hpp>
#include "../RWStepFEA/RWStepFEA_RWCurveElementIntervalLinearlyVarying.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaCurveSectionGeometricRelationship.hpp"
#include "../RWStepFEA/RWStepFEA_RWFeaSurfaceSectionGeometricRelationship.hpp"

#include <StepBasic_DocumentProductAssociation.hpp>
#include <StepBasic_DocumentProductEquivalence.hpp>
#include "../RWStepBasic/RWStepBasic_RWDocumentProductAssociation.hpp"
#include "../RWStepBasic/RWStepBasic_RWDocumentProductEquivalence.hpp"

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
#include <StepDimTol_GeometricToleranceWithDatumReference.hpp>
#include <StepDimTol_ModifiedGeometricTolerance.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepDimTol_DatumFeature.hpp>
#include <StepDimTol_DatumReference.hpp>
#include <StepDimTol_CommonDatum.hpp>
#include <StepDimTol_DatumTarget.hpp>
#include <StepDimTol_PlacedDatumTargetFeature.hpp>
#include "../RWStepRepr/RWStepRepr_RWCompositeShapeAspect.hpp"
#include "../RWStepRepr/RWStepRepr_RWDerivedShapeAspect.hpp"
#include "../RWStepRepr/RWStepRepr_RWExtension.hpp"
#include "../RWStepShape/RWStepShape_RWShapeRepresentationWithParameters.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWAngularityTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWConcentricityTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWCircularRunoutTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWCoaxialityTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWCylindricityTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWFlatnessTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWLineProfileTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWParallelismTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWPerpendicularityTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWPositionTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWRoundnessTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWStraightnessTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWSurfaceProfileTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWSymmetryTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWTotalRunoutTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeometricTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithDatumReference.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWModifiedGeometricTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatum.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumFeature.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumReference.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWCommonDatum.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumTarget.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWPlacedDatumTargetFeature.hpp"
#include <StepDimTol_GeometricToleranceRelationship.hpp>
#include "../RWStepDimTol/RWStepDimTol_RWGeometricToleranceRelationship.hpp"

#include <StepRepr_ReprItemAndLengthMeasureWithUnit.hpp>
#include "../RWStepRepr/RWStepRepr_RWReprItemAndLengthMeasureWithUnit.hpp"
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.hpp>
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.hpp"

#include <StepBasic_ConversionBasedUnitAndMassUnit.hpp>
#include "../RWStepBasic/RWStepBasic_RWConversionBasedUnitAndMassUnit.hpp"
#include <StepBasic_MassMeasureWithUnit.hpp>
#include "../RWStepBasic/RWStepBasic_RWMassMeasureWithUnit.hpp"

#include "../RWStepRepr/RWStepRepr_RWApex.hpp"
#include "../RWStepRepr/RWStepRepr_RWCentreOfSymmetry.hpp"
#include "../RWStepRepr/RWStepRepr_RWGeometricAlignment.hpp"
#include "../RWStepRepr/RWStepRepr_RWParallelOffset.hpp"
#include "../RWStepRepr/RWStepRepr_RWPerpendicularTo.hpp"
#include "../RWStepRepr/RWStepRepr_RWTangent.hpp"
#include "../RWStepAP242/RWStepAP242_RWGeometricItemSpecificUsage.hpp"
#include "../RWStepAP242/RWStepAP242_RWIdAttribute.hpp"
#include "../RWStepAP242/RWStepAP242_RWItemIdentifiedRepresentationUsage.hpp"
#include "../RWStepRepr/RWStepRepr_RWAllAroundShapeAspect.hpp"
#include "../RWStepRepr/RWStepRepr_RWBetweenShapeAspect.hpp"
#include "../RWStepRepr/RWStepRepr_RWCompositeGroupShapeAspect.hpp"
#include "../RWStepRepr/RWStepRepr_RWContinuosShapeAspect.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithDefinedUnit.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithMaximumTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithModifiers.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWUnequallyDisposedGeometricTolerance.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWNonUniformZoneDefinition.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWProjectedZoneDefinition.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWRunoutZoneDefinition.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWRunoutZoneOrientation.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWToleranceZone.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWToleranceZoneDefinition.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWToleranceZoneForm.hpp"
#include "../RWStepShape/RWStepShape_RWValueFormatTypeQualifier.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumReferenceCompartment.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumReferenceElement.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumReferenceModifierWithValue.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWDatumSystem.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeneralDatumReference.hpp"
#include "../RWStepRepr/RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnit.hpp"
#include "../RWStepRepr/RWStepRepr_RWReprItemAndLengthMeasureWithUnitAndQRI.hpp"
#include "../RWStepRepr/RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRef.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndGeoTolWthMod.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthMod.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndUneqDisGeoTol.hpp"
#include "../RWStepRepr/RWStepRepr_RWCompGroupShAspAndCompShAspAndDatumFeatAndShAsp.hpp"
#include "../RWStepRepr/RWStepRepr_RWCompShAspAndDatumFeatAndShAsp.hpp"
#include "../RWStepRepr/RWStepRepr_RWBooleanRepresentationItem.hpp"
#include "../RWStepRepr/RWStepRepr_RWIntegerRepresentationItem.hpp"
#include "../RWStepRepr/RWStepRepr_RWRealRepresentationItem.hpp"
#include "../RWStepRepr/RWStepRepr_RWValueRepresentationItem.hpp"
#include "../RWStepRepr/RWStepRepr_RWValueRepresentationItem.hpp"
#include "../RWStepAP242/RWStepAP242_RWDraughtingModelItemAssociation.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol.hpp"
#include "../RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthMaxTol.hpp"
#include "../RWStepVisual/RWStepVisual_RWAnnotationCurveOccurrence.hpp"
#include "../RWStepVisual/RWStepVisual_RWAnnotationOccurrence.hpp"
#include "../RWStepVisual/RWStepVisual_RWAnnotationPlane.hpp"
#include "../RWStepVisual/RWStepVisual_RWDraughtingCallout.hpp"

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
#include <StepDimTol_DatumReferenceCompartment.hpp>
#include <StepDimTol_DatumReferenceElement.hpp>
#include <StepDimTol_DatumReferenceModifierWithValue.hpp>
#include <StepDimTol_DatumSystem.hpp>
#include <StepDimTol_GeneralDatumReference.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI.hpp>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRef.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod.hpp>
#include <StepDimTol_GeoTolAndGeoTolWthMod.hpp>
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
#include <StepVisual_AnnotationCurveOccurrence.hpp>
#include <StepVisual_AnnotationPlane.hpp>
#include <StepVisual_DraughtingCallout.hpp>

#include <StepVisual_TessellatedAnnotationOccurrence.hpp>
#include <StepVisual_TessellatedItem.hpp>
#include <StepVisual_TessellatedGeometricSet.hpp>
#include <StepVisual_TessellatedCurveSet.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepRepr_CharacterizedRepresentation.hpp>
#include <StepRepr_ConstructiveGeometryRepresentation.hpp>
#include <StepRepr_ConstructiveGeometryRepresentationRelationship.hpp>
#include <StepRepr_MechanicalDesignAndDraughtingRelationship.hpp>

#include "../RWStepVisual/RWStepVisual_RWTessellatedAnnotationOccurrence.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedItem.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedGeometricSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWTessellatedCurveSet.hpp"
#include "../RWStepVisual/RWStepVisual_RWCoordinatesList.hpp"
#include "../RWStepRepr/RWStepRepr_RWCharacterizedRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWConstructiveGeometryRepresentation.hpp"
#include "../RWStepRepr/RWStepRepr_RWConstructiveGeometryRepresentationRelationship.hpp"
#include <StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel.hpp>
#include "../RWStepVisual/RWStepVisual_RWCharacterizedObjAndRepresentationAndDraughtingModel.hpp"
#include <StepVisual_AnnotationFillArea.hpp>
#include <StepVisual_AnnotationFillAreaOccurrence.hpp>
#include "../RWStepVisual/RWStepVisual_RWAnnotationFillArea.hpp"
#include "../RWStepVisual/RWStepVisual_RWAnnotationFillAreaOccurrence.hpp"
#include <StepVisual_CameraModelD3MultiClipping.hpp>
#include <StepVisual_CameraModelD3MultiClippingIntersection.hpp>
#include <StepVisual_CameraModelD3MultiClippingUnion.hpp>
#include "../RWStepVisual/RWStepVisual_RWCameraModelD3MultiClipping.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraModelD3MultiClippingIntersection.hpp"
#include "../RWStepVisual/RWStepVisual_RWCameraModelD3MultiClippingUnion.hpp"
#include <StepVisual_AnnotationCurveOccurrenceAndGeomReprItem.hpp>
#include "../RWStepVisual/RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem.hpp"

#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleTransparent.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleReflectanceAmbient.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleRendering.hpp"
#include "../RWStepVisual/RWStepVisual_RWSurfaceStyleRenderingWithProperties.hpp"

#include "../RWStepGeom/RWStepGeom_RWSuParameters.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWActuatedKinPairAndOrderKinPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWActuatedKinematicPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWContextDependentKinematicLinkRepresentation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWCylindricalPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWCylindricalPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWCylindricalPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWFullyConstrainedPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWGearPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWGearPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWGearPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWHomokineticPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicJoint.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicLink.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicLinkRepresentationAssociation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicPropertyMechanismRepresentation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicTopologyDirectedStructure.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicTopologyNetworkStructure.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWKinematicTopologyStructure.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWLinearFlexibleAndPinionPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWLinearFlexibleAndPlanarCurvePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWLinearFlexibleLinkRepresentation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWLowOrderKinematicPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWLowOrderKinematicPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWLowOrderKinematicPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWMechanismRepresentation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWMechanismStateRepresentation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWOrientedJoint.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPairRepresentationRelationship.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPlanarCurvePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPlanarCurvePairRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPlanarPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPlanarPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPlanarPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPointOnPlanarCurvePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPointOnPlanarCurvePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPointOnPlanarCurvePairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPointOnSurfacePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPointOnSurfacePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPointOnSurfacePairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPrismaticPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPrismaticPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWPrismaticPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWProductDefinitionKinematics.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWProductDefinitionRelationshipKinematics.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRackAndPinionPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRackAndPinionPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRackAndPinionPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRevolutePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRevolutePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRevolutePairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRigidLinkRepresentation.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRollingCurvePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRollingCurvePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRollingSurfacePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRollingSurfacePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWRotationAboutDirection.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWScrewPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWScrewPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWScrewPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSlidingCurvePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSlidingCurvePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSlidingSurfacePair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSlidingSurfacePairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSphericalPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSphericalPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSphericalPairWithPin.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSphericalPairWithPinAndRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSphericalPairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWSurfacePairWithRange.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWUnconstrainedPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWUnconstrainedPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWUniversalPair.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWUniversalPairValue.hpp"
#include "../RWStepKinematics/RWStepKinematics_RWUniversalPairWithRange.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationContextReference.hpp"
#include "../RWStepRepr/RWStepRepr_RWRepresentationReference.hpp"

#include <StepGeom_SuParameters.hpp>
#include <StepKinematics_ActuatedKinPairAndOrderKinPair.hpp>
#include <StepKinematics_ActuatedKinematicPair.hpp>
#include <StepKinematics_ContextDependentKinematicLinkRepresentation.hpp>
#include <StepKinematics_CylindricalPair.hpp>
#include <StepKinematics_CylindricalPairValue.hpp>
#include <StepKinematics_CylindricalPairWithRange.hpp>
#include <StepKinematics_FullyConstrainedPair.hpp>
#include <StepKinematics_GearPair.hpp>
#include <StepKinematics_GearPairValue.hpp>
#include <StepKinematics_GearPairWithRange.hpp>
#include <StepKinematics_HomokineticPair.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepKinematics_KinematicLink.hpp>
#include <StepKinematics_KinematicLinkRepresentationAssociation.hpp>
#include <StepKinematics_KinematicPair.hpp>
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
#include <StepKinematics_MechanismStateRepresentation.hpp>
#include <StepKinematics_OrientedJoint.hpp>
#include <StepKinematics_PairRepresentationRelationship.hpp>
#include <StepKinematics_PlanarCurvePair.hpp>
#include <StepKinematics_PlanarCurvePairRange.hpp>
#include <StepKinematics_PlanarPair.hpp>
#include <StepKinematics_PlanarPairValue.hpp>
#include <StepKinematics_PlanarPairWithRange.hpp>
#include <StepKinematics_PointOnPlanarCurvePair.hpp>
#include <StepKinematics_PointOnPlanarCurvePairValue.hpp>
#include <StepKinematics_PointOnPlanarCurvePairWithRange.hpp>
#include <StepKinematics_PointOnSurfacePair.hpp>
#include <StepKinematics_PointOnSurfacePairValue.hpp>
#include <StepKinematics_PointOnSurfacePairWithRange.hpp>
#include <StepKinematics_PrismaticPair.hpp>
#include <StepKinematics_PrismaticPairValue.hpp>
#include <StepKinematics_PrismaticPairWithRange.hpp>
#include <StepKinematics_ProductDefinitionKinematics.hpp>
#include <StepKinematics_ProductDefinitionRelationshipKinematics.hpp>
#include <StepKinematics_RackAndPinionPair.hpp>
#include <StepKinematics_RackAndPinionPairValue.hpp>
#include <StepKinematics_RackAndPinionPairWithRange.hpp>
#include <StepKinematics_RevolutePair.hpp>
#include <StepKinematics_RevolutePairValue.hpp>
#include <StepKinematics_RevolutePairWithRange.hpp>
#include <StepKinematics_RigidLinkRepresentation.hpp>
#include <StepKinematics_RollingCurvePair.hpp>
#include <StepKinematics_RollingCurvePairValue.hpp>
#include <StepKinematics_RollingSurfacePair.hpp>
#include <StepKinematics_RollingSurfacePairValue.hpp>
#include <StepKinematics_RotationAboutDirection.hpp>
#include <StepKinematics_ScrewPair.hpp>
#include <StepKinematics_ScrewPairValue.hpp>
#include <StepKinematics_ScrewPairWithRange.hpp>
#include <StepKinematics_SlidingCurvePair.hpp>
#include <StepKinematics_SlidingCurvePairValue.hpp>
#include <StepKinematics_SlidingSurfacePair.hpp>
#include <StepKinematics_SlidingSurfacePairValue.hpp>
#include <StepKinematics_SphericalPair.hpp>
#include <StepKinematics_SphericalPairValue.hpp>
#include <StepKinematics_SphericalPairWithPin.hpp>
#include <StepKinematics_SphericalPairWithPinAndRange.hpp>
#include <StepKinematics_SphericalPairWithRange.hpp>
#include <StepKinematics_SurfacePairWithRange.hpp>
#include <StepKinematics_UnconstrainedPair.hpp>
#include <StepKinematics_UnconstrainedPairValue.hpp>
#include <StepKinematics_UniversalPair.hpp>
#include <StepKinematics_UniversalPairValue.hpp>
#include <StepKinematics_UniversalPairWithRange.hpp>
#include <StepRepr_RepresentationContextReference.hpp>
#include <StepRepr_RepresentationReference.hpp>

#include <NCollection_IncAllocator.hpp>

#include <string_view>
#include <mutex>

namespace
{

  static constexpr std::string_view PasReco("?");
  static constexpr std::string_view Reco_Address("ADDRESS");
  static constexpr std::string_view Reco_AdvancedBrepShapeRepresentation(
    "ADVANCED_BREP_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_AdvancedFace("ADVANCED_FACE");
  static constexpr std::string_view Reco_AnnotationCurveOccurrence("ANNOTATION_CURVE_OCCURRENCE");
  static constexpr std::string_view Reco_AnnotationFillArea("ANNOTATION_FILL_AREA");
  static constexpr std::string_view Reco_AnnotationFillAreaOccurrence(
    "ANNOTATION_FILL_AREA_OCCURRENCE");
  static constexpr std::string_view Reco_AnnotationOccurrence("ANNOTATION_OCCURRENCE");
  static constexpr std::string_view Reco_AnnotationSubfigureOccurrence(
    "ANNOTATION_SUBFIGURE_OCCURRENCE");
  static constexpr std::string_view Reco_AnnotationSymbol("ANNOTATION_SYMBOL");
  static constexpr std::string_view Reco_AnnotationSymbolOccurrence("ANNOTATION_SYMBOL_OCCURRENCE");
  static constexpr std::string_view Reco_AnnotationText("ANNOTATION_TEXT");
  static constexpr std::string_view Reco_AnnotationTextOccurrence("ANNOTATION_TEXT_OCCURRENCE");
  static constexpr std::string_view Reco_ApplicationContext("APPLICATION_CONTEXT");
  static constexpr std::string_view Reco_ApplicationContextElement("APPLICATION_CONTEXT_ELEMENT");
  static constexpr std::string_view Reco_ApplicationProtocolDefinition(
    "APPLICATION_PROTOCOL_DEFINITION");
  static constexpr std::string_view Reco_Approval("APPROVAL");
  static constexpr std::string_view Reco_ApprovalAssignment("APPROVAL_ASSIGNMENT");
  static constexpr std::string_view Reco_ApprovalPersonOrganization("APPROVAL_PERSON_ORGANIZATION");
  static constexpr std::string_view Reco_ApprovalRelationship("APPROVAL_RELATIONSHIP");
  static constexpr std::string_view Reco_ApprovalRole("APPROVAL_ROLE");
  static constexpr std::string_view Reco_ApprovalStatus("APPROVAL_STATUS");
  static constexpr std::string_view Reco_AreaInSet("AREA_IN_SET");
  static constexpr std::string_view Reco_AutoDesignActualDateAndTimeAssignment(
    "AUTO_DESIGN_ACTUAL_DATE_AND_TIME_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignActualDateAssignment(
    "AUTO_DESIGN_ACTUAL_DATE_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignApprovalAssignment(
    "AUTO_DESIGN_APPROVAL_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignDateAndPersonAssignment(
    "AUTO_DESIGN_DATE_AND_PERSON_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignGroupAssignment("AUTO_DESIGN_GROUP_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignNominalDateAndTimeAssignment(
    "AUTO_DESIGN_NOMINAL_DATE_AND_TIME_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignNominalDateAssignment(
    "AUTO_DESIGN_NOMINAL_DATE_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignOrganizationAssignment(
    "AUTO_DESIGN_ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignPersonAndOrganizationAssignment(
    "AUTO_DESIGN_PERSON_AND_ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignPresentedItem("AUTO_DESIGN_PRESENTED_ITEM");
  static constexpr std::string_view Reco_AutoDesignSecurityClassificationAssignment(
    "AUTO_DESIGN_SECURITY_CLASSIFICATION_ASSIGNMENT");
  static constexpr std::string_view Reco_AutoDesignViewArea("AUTO_DESIGN_VIEW_AREA");
  static constexpr std::string_view Reco_Axis1Placement("AXIS1_PLACEMENT");
  static constexpr std::string_view Reco_Axis2Placement2d("AXIS2_PLACEMENT_2D");
  static constexpr std::string_view Reco_Axis2Placement3d("AXIS2_PLACEMENT_3D");
  static constexpr std::string_view Reco_BSplineCurve("B_SPLINE_CURVE");
  static constexpr std::string_view Reco_BSplineCurveWithKnots("B_SPLINE_CURVE_WITH_KNOTS");
  static constexpr std::string_view Reco_BSplineSurface("B_SPLINE_SURFACE");
  static constexpr std::string_view Reco_BSplineSurfaceWithKnots("B_SPLINE_SURFACE_WITH_KNOTS");
  static constexpr std::string_view Reco_BackgroundColour("BACKGROUND_COLOUR");
  static constexpr std::string_view Reco_BezierCurve("BEZIER_CURVE");
  static constexpr std::string_view Reco_BezierSurface("BEZIER_SURFACE");
  static constexpr std::string_view Reco_Block("BLOCK");
  static constexpr std::string_view Reco_BooleanResult("BOOLEAN_RESULT");
  static constexpr std::string_view Reco_BoundaryCurve("BOUNDARY_CURVE");
  static constexpr std::string_view Reco_BoundedCurve("BOUNDED_CURVE");
  static constexpr std::string_view Reco_BoundedSurface("BOUNDED_SURFACE");
  static constexpr std::string_view Reco_BoxDomain("BOX_DOMAIN");
  static constexpr std::string_view Reco_BoxedHalfSpace("BOXED_HALF_SPACE");
  static constexpr std::string_view Reco_BrepWithVoids("BREP_WITH_VOIDS");
  static constexpr std::string_view Reco_CalendarDate("CALENDAR_DATE");
  static constexpr std::string_view Reco_CameraImage("CAMERA_IMAGE");
  static constexpr std::string_view Reco_CameraModel("CAMERA_MODEL");
  static constexpr std::string_view Reco_CameraModelD2("CAMERA_MODEL_D2");
  static constexpr std::string_view Reco_CameraModelD3("CAMERA_MODEL_D3");
  static constexpr std::string_view Reco_CameraUsage("CAMERA_USAGE");
  static constexpr std::string_view Reco_CartesianPoint("CARTESIAN_POINT");
  static constexpr std::string_view Reco_CartesianTransformationOperator(
    "CARTESIAN_TRANSFORMATION_OPERATOR");
  static constexpr std::string_view Reco_CartesianTransformationOperator3d(
    "CARTESIAN_TRANSFORMATION_OPERATOR_3D");
  static constexpr std::string_view Reco_Circle("CIRCLE");
  static constexpr std::string_view Reco_ClosedShell("CLOSED_SHELL");
  static constexpr std::string_view Reco_Colour("COLOUR");
  static constexpr std::string_view Reco_ColourRgb("COLOUR_RGB");
  static constexpr std::string_view Reco_ColourSpecification("COLOUR_SPECIFICATION");
  static constexpr std::string_view Reco_CompositeCurve("COMPOSITE_CURVE");
  static constexpr std::string_view Reco_CompositeCurveOnSurface("COMPOSITE_CURVE_ON_SURFACE");
  static constexpr std::string_view Reco_CompositeCurveSegment("COMPOSITE_CURVE_SEGMENT");
  static constexpr std::string_view Reco_CompositeText("COMPOSITE_TEXT");
  static constexpr std::string_view Reco_CompositeTextWithAssociatedCurves(
    "COMPOSITE_TEXT_WITH_ASSOCIATED_CURVES");
  static constexpr std::string_view Reco_CompositeTextWithBlankingBox(
    "COMPOSITE_TEXT_WITH_BLANKING_BOX");
  static constexpr std::string_view Reco_CompositeTextWithExtent("COMPOSITE_TEXT_WITH_EXTENT");
  static constexpr std::string_view Reco_Conic("CONIC");
  static constexpr std::string_view Reco_ConicalSurface("CONICAL_SURFACE");
  static constexpr std::string_view Reco_ConnectedFaceSet("CONNECTED_FACE_SET");
  static constexpr std::string_view Reco_ContextDependentInvisibility(
    "CONTEXT_DEPENDENT_INVISIBILITY");
  static constexpr std::string_view Reco_ContextDependentOverRidingStyledItem(
    "CONTEXT_DEPENDENT_OVER_RIDING_STYLED_ITEM");
  static constexpr std::string_view Reco_ConversionBasedUnit("CONVERSION_BASED_UNIT");
  static constexpr std::string_view Reco_CoordinatedUniversalTimeOffset(
    "COORDINATED_UNIVERSAL_TIME_OFFSET");
  static constexpr std::string_view Reco_CsgRepresentation("CSG_REPRESENTATION");
  static constexpr std::string_view Reco_CsgShapeRepresentation("CSG_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_CsgSolid("CSG_SOLID");
  static constexpr std::string_view Reco_Curve("CURVE");
  static constexpr std::string_view Reco_CurveBoundedSurface("CURVE_BOUNDED_SURFACE");
  static constexpr std::string_view Reco_CurveReplica("CURVE_REPLICA");
  static constexpr std::string_view Reco_CurveStyle("CURVE_STYLE");
  static constexpr std::string_view Reco_CurveStyleFont("CURVE_STYLE_FONT");
  static constexpr std::string_view Reco_CurveStyleFontPattern("CURVE_STYLE_FONT_PATTERN");
  static constexpr std::string_view Reco_CylindricalSurface("CYLINDRICAL_SURFACE");
  static constexpr std::string_view Reco_Date("DATE");
  static constexpr std::string_view Reco_DateAndTime("DATE_AND_TIME");
  static constexpr std::string_view Reco_DateAndTimeAssignment("DATE_AND_TIME_ASSIGNMENT");
  static constexpr std::string_view Reco_DateAssignment("DATE_ASSIGNMENT");
  static constexpr std::string_view Reco_DateRole("DATE_ROLE");
  static constexpr std::string_view Reco_DateTimeRole("DATE_TIME_ROLE");
  static constexpr std::string_view Reco_DefinedSymbol("DEFINED_SYMBOL");
  static constexpr std::string_view Reco_DefinitionalRepresentation("DEFINITIONAL_REPRESENTATION");
  static constexpr std::string_view Reco_DegeneratePcurve("DEGENERATE_PCURVE");
  static constexpr std::string_view Reco_DegenerateToroidalSurface("DEGENERATE_TOROIDAL_SURFACE");
  static constexpr std::string_view Reco_DescriptiveRepresentationItem(
    "DESCRIPTIVE_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_DimensionCurve("DIMENSION_CURVE");
  static constexpr std::string_view Reco_DimensionCurveTerminator("DIMENSION_CURVE_TERMINATOR");
  static constexpr std::string_view Reco_DimensionalExponents("DIMENSIONAL_EXPONENTS");
  static constexpr std::string_view Reco_Direction("DIRECTION");
  static constexpr std::string_view Reco_DraughtingAnnotationOccurrence(
    "DRAUGHTING_ANNOTATION_OCCURRENCE");
  static constexpr std::string_view Reco_DraughtingCallout("DRAUGHTING_CALLOUT");
  static constexpr std::string_view Reco_DraughtingPreDefinedColour(
    "DRAUGHTING_PRE_DEFINED_COLOUR");
  static constexpr std::string_view Reco_DraughtingPreDefinedCurveFont(
    "DRAUGHTING_PRE_DEFINED_CURVE_FONT");
  static constexpr std::string_view Reco_DraughtingSubfigureRepresentation(
    "DRAUGHTING_SUBFIGURE_REPRESENTATION");
  static constexpr std::string_view Reco_DraughtingSymbolRepresentation(
    "DRAUGHTING_SYMBOL_REPRESENTATION");
  static constexpr std::string_view Reco_DraughtingTextLiteralWithDelineation(
    "DRAUGHTING_TEXT_LITERAL_WITH_DELINEATION");
  static constexpr std::string_view Reco_DrawingDefinition("DRAWING_DEFINITION");
  static constexpr std::string_view Reco_DrawingRevision("DRAWING_REVISION");
  static constexpr std::string_view Reco_Edge("EDGE");
  static constexpr std::string_view Reco_EdgeCurve("EDGE_CURVE");
  static constexpr std::string_view Reco_EdgeLoop("EDGE_LOOP");
  static constexpr std::string_view Reco_ElementarySurface("ELEMENTARY_SURFACE");
  static constexpr std::string_view Reco_Ellipse("ELLIPSE");
  static constexpr std::string_view Reco_EvaluatedDegeneratePcurve("EVALUATED_DEGENERATE_PCURVE");
  static constexpr std::string_view Reco_ExternalSource("EXTERNAL_SOURCE");
  static constexpr std::string_view Reco_ExternallyDefinedCurveFont(
    "EXTERNALLY_DEFINED_CURVE_FONT");
  static constexpr std::string_view Reco_ExternallyDefinedHatchStyle(
    "EXTERNALLY_DEFINED_HATCH_STYLE");
  static constexpr std::string_view Reco_ExternallyDefinedItem("EXTERNALLY_DEFINED_ITEM");
  static constexpr std::string_view Reco_ExternallyDefinedSymbol("EXTERNALLY_DEFINED_SYMBOL");
  static constexpr std::string_view Reco_ExternallyDefinedTextFont("EXTERNALLY_DEFINED_TEXT_FONT");
  static constexpr std::string_view Reco_ExternallyDefinedTileStyle(
    "EXTERNALLY_DEFINED_TILE_STYLE");
  static constexpr std::string_view Reco_ExtrudedAreaSolid("EXTRUDED_AREA_SOLID");
  static constexpr std::string_view Reco_Face("FACE");
  static constexpr std::string_view Reco_FaceBound("FACE_BOUND");
  static constexpr std::string_view Reco_FaceOuterBound("FACE_OUTER_BOUND");
  static constexpr std::string_view Reco_FaceSurface("FACE_SURFACE");
  static constexpr std::string_view Reco_FacetedBrep("FACETED_BREP");
  static constexpr std::string_view Reco_FacetedBrepShapeRepresentation(
    "FACETED_BREP_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_FillAreaStyle("FILL_AREA_STYLE");
  static constexpr std::string_view Reco_FillAreaStyleColour("FILL_AREA_STYLE_COLOUR");
  static constexpr std::string_view Reco_FillAreaStyleHatching("FILL_AREA_STYLE_HATCHING");
  static constexpr std::string_view Reco_FillAreaStyleTileSymbolWithStyle(
    "FILL_AREA_STYLE_TILE_SYMBOL_WITH_STYLE");
  static constexpr std::string_view Reco_FillAreaStyleTiles("FILL_AREA_STYLE_TILES");
  static constexpr std::string_view Reco_FunctionallyDefinedTransformation(
    "FUNCTIONALLY_DEFINED_TRANSFORMATION");
  static constexpr std::string_view Reco_GeometricCurveSet("GEOMETRIC_CURVE_SET");
  static constexpr std::string_view Reco_GeometricRepresentationContext(
    "GEOMETRIC_REPRESENTATION_CONTEXT");
  static constexpr std::string_view Reco_GeometricRepresentationItem(
    "GEOMETRIC_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_GeometricSet("GEOMETRIC_SET");
  static constexpr std::string_view Reco_GeometricallyBoundedSurfaceShapeRepresentation(
    "GEOMETRICALLY_BOUNDED_SURFACE_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_GeometricallyBoundedWireframeShapeRepresentation(
    "GEOMETRICALLY_BOUNDED_WIREFRAME_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_GlobalUncertaintyAssignedContext(
    "GLOBAL_UNCERTAINTY_ASSIGNED_CONTEXT");
  static constexpr std::string_view Reco_GlobalUnitAssignedContext("GLOBAL_UNIT_ASSIGNED_CONTEXT");
  static constexpr std::string_view Reco_Group("GROUP");
  static constexpr std::string_view Reco_GroupAssignment("GROUP_ASSIGNMENT");
  static constexpr std::string_view Reco_GroupRelationship("GROUP_RELATIONSHIP");
  static constexpr std::string_view Reco_HalfSpaceSolid("HALF_SPACE_SOLID");
  static constexpr std::string_view Reco_Hyperbola("HYPERBOLA");
  static constexpr std::string_view Reco_IntersectionCurve("INTERSECTION_CURVE");
  static constexpr std::string_view Reco_Invisibility("INVISIBILITY");
  static constexpr std::string_view Reco_LengthMeasureWithUnit("LENGTH_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_LengthUnit("LENGTH_UNIT");
  static constexpr std::string_view Reco_Line("LINE");
  static constexpr std::string_view Reco_LocalTime("LOCAL_TIME");
  static constexpr std::string_view Reco_Loop("LOOP");
  static constexpr std::string_view Reco_ManifoldSolidBrep("MANIFOLD_SOLID_BREP");
  static constexpr std::string_view Reco_ManifoldSurfaceShapeRepresentation(
    "MANIFOLD_SURFACE_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_MappedItem("MAPPED_ITEM");
  static constexpr std::string_view Reco_MeasureWithUnit("MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_MechanicalDesignGeometricPresentationArea(
    "MECHANICAL_DESIGN_GEOMETRIC_PRESENTATION_AREA");
  static constexpr std::string_view Reco_MechanicalDesignGeometricPresentationRepresentation(
    "MECHANICAL_DESIGN_GEOMETRIC_PRESENTATION_REPRESENTATION");
  static constexpr std::string_view Reco_MechanicalDesignPresentationArea(
    "MECHANICAL_DESIGN_PRESENTATION_AREA");
  static constexpr std::string_view Reco_NamedUnit("NAMED_UNIT");
  static constexpr std::string_view Reco_OffsetCurve3d("OFFSET_CURVE_3D");
  static constexpr std::string_view Reco_OffsetSurface("OFFSET_SURFACE");
  static constexpr std::string_view Reco_OneDirectionRepeatFactor("ONE_DIRECTION_REPEAT_FACTOR");
  static constexpr std::string_view Reco_OpenShell("OPEN_SHELL");
  static constexpr std::string_view Reco_OrdinalDate("ORDINAL_DATE");
  static constexpr std::string_view Reco_Organization("ORGANIZATION");
  static constexpr std::string_view Reco_OrganizationAssignment("ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_OrganizationRole("ORGANIZATION_ROLE");
  static constexpr std::string_view Reco_OrganizationalAddress("ORGANIZATIONAL_ADDRESS");
  static constexpr std::string_view Reco_OrientedClosedShell("ORIENTED_CLOSED_SHELL");
  static constexpr std::string_view Reco_OrientedEdge("ORIENTED_EDGE");
  static constexpr std::string_view Reco_OrientedFace("ORIENTED_FACE");
  static constexpr std::string_view Reco_OrientedOpenShell("ORIENTED_OPEN_SHELL");
  static constexpr std::string_view Reco_OrientedPath("ORIENTED_PATH");
  static constexpr std::string_view Reco_OuterBoundaryCurve("OUTER_BOUNDARY_CURVE");
  static constexpr std::string_view Reco_OverRidingStyledItem("OVER_RIDING_STYLED_ITEM");
  static constexpr std::string_view Reco_Parabola("PARABOLA");
  static constexpr std::string_view Reco_ParametricRepresentationContext(
    "PARAMETRIC_REPRESENTATION_CONTEXT");
  static constexpr std::string_view Reco_Path("PATH");
  static constexpr std::string_view Reco_Pcurve("PCURVE");
  static constexpr std::string_view Reco_Person("PERSON");
  static constexpr std::string_view Reco_PersonAndOrganization("PERSON_AND_ORGANIZATION");
  static constexpr std::string_view Reco_PersonAndOrganizationAssignment(
    "PERSON_AND_ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_PersonAndOrganizationRole("PERSON_AND_ORGANIZATION_ROLE");
  static constexpr std::string_view Reco_PersonalAddress("PERSONAL_ADDRESS");
  static constexpr std::string_view Reco_Placement("PLACEMENT");
  static constexpr std::string_view Reco_PlanarBox("PLANAR_BOX");
  static constexpr std::string_view Reco_PlanarExtent("PLANAR_EXTENT");
  static constexpr std::string_view Reco_Plane("PLANE");
  static constexpr std::string_view Reco_PlaneAngleMeasureWithUnit("PLANE_ANGLE_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_PlaneAngleUnit("PLANE_ANGLE_UNIT");
  static constexpr std::string_view Reco_Point("POINT");
  static constexpr std::string_view Reco_PointOnCurve("POINT_ON_CURVE");
  static constexpr std::string_view Reco_PointOnSurface("POINT_ON_SURFACE");
  static constexpr std::string_view Reco_PointReplica("POINT_REPLICA");
  static constexpr std::string_view Reco_PointStyle("POINT_STYLE");
  static constexpr std::string_view Reco_PolyLoop("POLY_LOOP");
  static constexpr std::string_view Reco_Polyline("POLYLINE");
  static constexpr std::string_view Reco_PreDefinedColour("PRE_DEFINED_COLOUR");
  static constexpr std::string_view Reco_PreDefinedCurveFont("PRE_DEFINED_CURVE_FONT");
  static constexpr std::string_view Reco_PreDefinedItem("PRE_DEFINED_ITEM");
  static constexpr std::string_view Reco_PreDefinedSymbol("PRE_DEFINED_SYMBOL");
  static constexpr std::string_view Reco_PreDefinedTextFont("PRE_DEFINED_TEXT_FONT");
  static constexpr std::string_view Reco_PresentationArea("PRESENTATION_AREA");
  static constexpr std::string_view Reco_PresentationLayerAssignment(
    "PRESENTATION_LAYER_ASSIGNMENT");
  static constexpr std::string_view Reco_PresentationRepresentation("PRESENTATION_REPRESENTATION");
  static constexpr std::string_view Reco_PresentationSet("PRESENTATION_SET");
  static constexpr std::string_view Reco_PresentationSize("PRESENTATION_SIZE");
  static constexpr std::string_view Reco_PresentationStyleAssignment(
    "PRESENTATION_STYLE_ASSIGNMENT");
  static constexpr std::string_view Reco_PresentationStyleByContext(
    "PRESENTATION_STYLE_BY_CONTEXT");
  static constexpr std::string_view Reco_PresentationView("PRESENTATION_VIEW");
  static constexpr std::string_view Reco_PresentedItem("PRESENTED_ITEM");
  static constexpr std::string_view Reco_Product("PRODUCT");
  static constexpr std::string_view Reco_ProductCategory("PRODUCT_CATEGORY");
  static constexpr std::string_view Reco_ProductContext("PRODUCT_CONTEXT");
  static constexpr std::string_view Reco_ProductDataRepresentationView(
    "PRODUCT_DATA_REPRESENTATION_VIEW");
  static constexpr std::string_view Reco_ProductDefinition("PRODUCT_DEFINITION");
  static constexpr std::string_view Reco_ProductDefinitionContext("PRODUCT_DEFINITION_CONTEXT");
  static constexpr std::string_view Reco_ProductDefinitionFormation("PRODUCT_DEFINITION_FORMATION");
  static constexpr std::string_view Reco_ProductDefinitionFormationWithSpecifiedSource(
    "PRODUCT_DEFINITION_FORMATION_WITH_SPECIFIED_SOURCE");
  static constexpr std::string_view Reco_ProductDefinitionShape("PRODUCT_DEFINITION_SHAPE");
  static constexpr std::string_view Reco_ProductRelatedProductCategory(
    "PRODUCT_RELATED_PRODUCT_CATEGORY");
  static constexpr std::string_view Reco_ProductType("PRODUCT_TYPE");
  static constexpr std::string_view Reco_PropertyDefinition("PROPERTY_DEFINITION");
  static constexpr std::string_view Reco_PropertyDefinitionRepresentation(
    "PROPERTY_DEFINITION_REPRESENTATION");
  static constexpr std::string_view Reco_QuasiUniformCurve("QUASI_UNIFORM_CURVE");
  static constexpr std::string_view Reco_QuasiUniformSurface("QUASI_UNIFORM_SURFACE");
  static constexpr std::string_view Reco_RatioMeasureWithUnit("RATIO_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_RationalBSplineCurve("RATIONAL_B_SPLINE_CURVE");
  static constexpr std::string_view Reco_RationalBSplineSurface("RATIONAL_B_SPLINE_SURFACE");
  static constexpr std::string_view Reco_RectangularCompositeSurface(
    "RECTANGULAR_COMPOSITE_SURFACE");
  static constexpr std::string_view Reco_RectangularTrimmedSurface("RECTANGULAR_TRIMMED_SURFACE");
  static constexpr std::string_view Reco_RepItemGroup("REP_ITEM_GROUP");
  static constexpr std::string_view Reco_ReparametrisedCompositeCurveSegment(
    "REPARAMETRISED_COMPOSITE_CURVE_SEGMENT");
  static constexpr std::string_view Reco_Representation("REPRESENTATION");
  static constexpr std::string_view Reco_RepresentationContext("REPRESENTATION_CONTEXT");
  static constexpr std::string_view Reco_RepresentationItem("REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_RepresentationMap("REPRESENTATION_MAP");
  static constexpr std::string_view Reco_RepresentationRelationship("REPRESENTATION_RELATIONSHIP");
  static constexpr std::string_view Reco_RevolvedAreaSolid("REVOLVED_AREA_SOLID");
  static constexpr std::string_view Reco_RightAngularWedge("RIGHT_ANGULAR_WEDGE");
  static constexpr std::string_view Reco_RightCircularCone("RIGHT_CIRCULAR_CONE");
  static constexpr std::string_view Reco_RightCircularCylinder("RIGHT_CIRCULAR_CYLINDER");
  static constexpr std::string_view Reco_SeamCurve("SEAM_CURVE");
  static constexpr std::string_view Reco_SecurityClassification("SECURITY_CLASSIFICATION");
  static constexpr std::string_view Reco_SecurityClassificationAssignment(
    "SECURITY_CLASSIFICATION_ASSIGNMENT");
  static constexpr std::string_view Reco_SecurityClassificationLevel(
    "SECURITY_CLASSIFICATION_LEVEL");
  static constexpr std::string_view Reco_ShapeAspect("SHAPE_ASPECT");
  static constexpr std::string_view Reco_ShapeAspectRelationship("SHAPE_ASPECT_RELATIONSHIP");
  static constexpr std::string_view Reco_ShapeAspectTransition("SHAPE_ASPECT_TRANSITION");
  static constexpr std::string_view Reco_ShapeDefinitionRepresentation(
    "SHAPE_DEFINITION_REPRESENTATION");
  static constexpr std::string_view Reco_ShapeRepresentation("SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_ShellBasedSurfaceModel("SHELL_BASED_SURFACE_MODEL");
  static constexpr std::string_view Reco_SiUnit("SI_UNIT");
  static constexpr std::string_view Reco_SolidAngleMeasureWithUnit("SOLID_ANGLE_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_SolidModel("SOLID_MODEL");
  static constexpr std::string_view Reco_SolidReplica("SOLID_REPLICA");
  static constexpr std::string_view Reco_Sphere("SPHERE");
  static constexpr std::string_view Reco_SphericalSurface("SPHERICAL_SURFACE");
  static constexpr std::string_view Reco_StyledItem("STYLED_ITEM");
  static constexpr std::string_view Reco_Surface("SURFACE");
  static constexpr std::string_view Reco_SurfaceCurve("SURFACE_CURVE");
  static constexpr std::string_view Reco_SurfaceOfLinearExtrusion("SURFACE_OF_LINEAR_EXTRUSION");
  static constexpr std::string_view Reco_SurfaceOfRevolution("SURFACE_OF_REVOLUTION");
  static constexpr std::string_view Reco_SurfacePatch("SURFACE_PATCH");
  static constexpr std::string_view Reco_SurfaceReplica("SURFACE_REPLICA");
  static constexpr std::string_view Reco_SurfaceSideStyle("SURFACE_SIDE_STYLE");
  static constexpr std::string_view Reco_SurfaceStyleBoundary("SURFACE_STYLE_BOUNDARY");
  static constexpr std::string_view Reco_SurfaceStyleControlGrid("SURFACE_STYLE_CONTROL_GRID");
  static constexpr std::string_view Reco_SurfaceStyleFillArea("SURFACE_STYLE_FILL_AREA");
  static constexpr std::string_view Reco_SurfaceStyleParameterLine("SURFACE_STYLE_PARAMETER_LINE");
  static constexpr std::string_view Reco_SurfaceStyleSegmentationCurve(
    "SURFACE_STYLE_SEGMENTATION_CURVE");
  static constexpr std::string_view Reco_SurfaceStyleSilhouette("SURFACE_STYLE_SILHOUETTE");
  static constexpr std::string_view Reco_SurfaceStyleUsage("SURFACE_STYLE_USAGE");
  static constexpr std::string_view Reco_SweptAreaSolid("SWEPT_AREA_SOLID");
  static constexpr std::string_view Reco_SweptSurface("SWEPT_SURFACE");
  static constexpr std::string_view Reco_SymbolColour("SYMBOL_COLOUR");
  static constexpr std::string_view Reco_SymbolRepresentation("SYMBOL_REPRESENTATION");
  static constexpr std::string_view Reco_SymbolRepresentationMap("SYMBOL_REPRESENTATION_MAP");
  static constexpr std::string_view Reco_SymbolStyle("SYMBOL_STYLE");
  static constexpr std::string_view Reco_SymbolTarget("SYMBOL_TARGET");
  static constexpr std::string_view Reco_Template("TEMPLATE");
  static constexpr std::string_view Reco_TemplateInstance("TEMPLATE_INSTANCE");
  static constexpr std::string_view Reco_TerminatorSymbol("TERMINATOR_SYMBOL");
  static constexpr std::string_view Reco_TextLiteral("TEXT_LITERAL");
  static constexpr std::string_view Reco_TextLiteralWithAssociatedCurves(
    "TEXT_LITERAL_WITH_ASSOCIATED_CURVES");
  static constexpr std::string_view Reco_TextLiteralWithBlankingBox(
    "TEXT_LITERAL_WITH_BLANKING_BOX");
  static constexpr std::string_view Reco_TextLiteralWithDelineation(
    "TEXT_LITERAL_WITH_DELINEATION");
  static constexpr std::string_view Reco_TextLiteralWithExtent("TEXT_LITERAL_WITH_EXTENT");
  static constexpr std::string_view Reco_TextStyle("TEXT_STYLE");
  static constexpr std::string_view Reco_TextStyleForDefinedFont("TEXT_STYLE_FOR_DEFINED_FONT");
  static constexpr std::string_view Reco_TextStyleWithBoxCharacteristics(
    "TEXT_STYLE_WITH_BOX_CHARACTERISTICS");
  static constexpr std::string_view Reco_TextStyleWithMirror("TEXT_STYLE_WITH_MIRROR");
  static constexpr std::string_view Reco_TopologicalRepresentationItem(
    "TOPOLOGICAL_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_ToroidalSurface("TOROIDAL_SURFACE");
  static constexpr std::string_view Reco_Torus("TORUS");
  static constexpr std::string_view Reco_TransitionalShapeRepresentation(
    "TRANSITIONAL_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_TrimmedCurve("TRIMMED_CURVE");
  static constexpr std::string_view Reco_TwoDirectionRepeatFactor("TWO_DIRECTION_REPEAT_FACTOR");
  static constexpr std::string_view Reco_UncertaintyMeasureWithUnit(
    "UNCERTAINTY_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_UniformCurve("UNIFORM_CURVE");
  static constexpr std::string_view Reco_UniformSurface("UNIFORM_SURFACE");
  static constexpr std::string_view Reco_Vector("VECTOR");
  static constexpr std::string_view Reco_Vertex("VERTEX");
  static constexpr std::string_view Reco_VertexLoop("VERTEX_LOOP");
  static constexpr std::string_view Reco_VertexPoint("VERTEX_POINT");
  static constexpr std::string_view Reco_ViewVolume("VIEW_VOLUME");
  static constexpr std::string_view Reco_WeekOfYearAndDayDate("WEEK_OF_YEAR_AND_DAY_DATE");

  static constexpr std::string_view Reco_SolidAngleUnit("SOLID_ANGLE_UNIT");
  static constexpr std::string_view Reco_MechanicalContext("MECHANICAL_CONTEXT");
  static constexpr std::string_view Reco_DesignContext("DESIGN_CONTEXT");

  static constexpr std::string_view Reco_TimeMeasureWithUnit("TIME_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_RatioUnit("RATIO_UNIT");
  static constexpr std::string_view Reco_TimeUnit("TIME_UNIT");
  static constexpr std::string_view Reco_ApprovalDateTime("APPROVAL_DATE_TIME");
  static constexpr std::string_view Reco_CameraImage2dWithScale("CAMERA_IMAGE_2D_WITH_SCALE");
  static constexpr std::string_view Reco_CameraImage3dWithScale("CAMERA_IMAGE_3D_WITH_SCALE");
  static constexpr std::string_view Reco_CartesianTransformationOperator2d(
    "CARTESIAN_TRANSFORMATION_OPERATOR_2D");
  static constexpr std::string_view Reco_DerivedUnit("DERIVED_UNIT");
  static constexpr std::string_view Reco_DerivedUnitElement("DERIVED_UNIT_ELEMENT");
  static constexpr std::string_view Reco_ItemDefinedTransformation("ITEM_DEFINED_TRANSFORMATION");
  static constexpr std::string_view Reco_PresentedItemRepresentation(
    "PRESENTED_ITEM_REPRESENTATION");
  static constexpr std::string_view Reco_PresentationLayerUsage("PRESENTATION_LAYER_USAGE");

  static constexpr std::string_view Reco_AutoDesignDocumentReference(
    "AUTO_DESIGN_DOCUMENT_REFERENCE");
  static constexpr std::string_view Reco_Document("DOCUMENT");
  static constexpr std::string_view Reco_DigitalDocument("DIGITAL_DOCUMENT");
  static constexpr std::string_view Reco_DocumentRelationship("DOCUMENT_RELATIONSHIP");
  static constexpr std::string_view Reco_DocumentType("DOCUMENT_TYPE");
  static constexpr std::string_view Reco_DocumentUsageConstraint("DOCUMENT_USAGE_CONSTRAINT");
  static constexpr std::string_view Reco_Effectivity("EFFECTIVITY");
  static constexpr std::string_view Reco_ProductDefinitionEffectivity(
    "PRODUCT_DEFINITION_EFFECTIVITY");
  static constexpr std::string_view Reco_ProductDefinitionRelationship(
    "PRODUCT_DEFINITION_RELATIONSHIP");
  static constexpr std::string_view Reco_ProductDefinitionWithAssociatedDocuments(
    "PRODUCT_DEFINITION_WITH_ASSOCIATED_DOCUMENTS");
  static constexpr std::string_view Reco_PhysicallyModeledProductDefinition(
    "PHYSICALLY_MODELED_PRODUCT_DEFINITION");

  static constexpr std::string_view Reco_ProductDefinitionUsage("PRODUCT_DEFINITION_USAGE");
  static constexpr std::string_view Reco_MakeFromUsageOption("MAKE_FROM_USAGE_OPTION");
  static constexpr std::string_view Reco_AssemblyComponentUsage("ASSEMBLY_COMPONENT_USAGE");
  static constexpr std::string_view Reco_NextAssemblyUsageOccurrence(
    "NEXT_ASSEMBLY_USAGE_OCCURRENCE");
  static constexpr std::string_view Reco_PromissoryUsageOccurrence("PROMISSORY_USAGE_OCCURRENCE");
  static constexpr std::string_view Reco_QuantifiedAssemblyComponentUsage(
    "QUANTIFIED_ASSEMBLY_COMPONENT_USAGE");
  static constexpr std::string_view Reco_SpecifiedHigherUsageOccurrence(
    "SPECIFIED_HIGHER_USAGE_OCCURRENCE");
  static constexpr std::string_view Reco_AssemblyComponentUsageSubstitute(
    "ASSEMBLY_COMPONENT_USAGE_SUBSTITUTE");
  static constexpr std::string_view Reco_SuppliedPartRelationship("SUPPLIED_PART_RELATIONSHIP");
  static constexpr std::string_view Reco_ExternallyDefinedRepresentation(
    "EXTERNALLY_DEFINED_REPRESENTATION");
  static constexpr std::string_view Reco_ShapeRepresentationRelationship(
    "SHAPE_REPRESENTATION_RELATIONSHIP");
  static constexpr std::string_view Reco_RepresentationRelationshipWithTransformation(
    "REPRESENTATION_RELATIONSHIP_WITH_TRANSFORMATION");
  static constexpr std::string_view Reco_MaterialDesignation("MATERIAL_DESIGNATION");
  static constexpr std::string_view Reco_ContextDependentShapeRepresentation(
    "CONTEXT_DEPENDENT_SHAPE_REPRESENTATION");

  static constexpr std::string_view Reco_AppliedDateAndTimeAssignment(
    "APPLIED_DATE_AND_TIME_ASSIGNMENT");
  static constexpr std::string_view Reco_AppliedDateAssignment("APPLIED_DATE_ASSIGNMENT");
  static constexpr std::string_view Reco_AppliedApprovalAssignment("APPLIED_APPROVAL_ASSIGNMENT");
  static constexpr std::string_view Reco_AppliedDocumentReference("APPLIED_DOCUMENT_REFERENCE");
  static constexpr std::string_view Reco_AppliedGroupAssignment("APPLIED_GROUP_ASSIGNMENT");
  static constexpr std::string_view Reco_AppliedOrganizationAssignment(
    "APPLIED_ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_AppliedPersonAndOrganizationAssignment(
    "APPLIED_PERSON_AND_ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_AppliedPresentedItem("APPLIED_PRESENTED_ITEM");
  static constexpr std::string_view Reco_AppliedSecurityClassificationAssignment(
    "APPLIED_SECURITY_CLASSIFICATION_ASSIGNMENT");
  static constexpr std::string_view Reco_DocumentFile("DOCUMENT_FILE");
  static constexpr std::string_view Reco_CharacterizedObject("CHARACTERIZED_OBJECT");
  static constexpr std::string_view Reco_ExtrudedFaceSolid("EXTRUDED_FACE_SOLID");
  static constexpr std::string_view Reco_RevolvedFaceSolid("REVOLVED_FACE_SOLID");
  static constexpr std::string_view Reco_SweptFaceSolid("SWEPT_FACE_SOLID");

  static constexpr std::string_view Reco_MeasureRepresentationItem("MEASURE_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_AreaUnit("AREA_UNIT");
  static constexpr std::string_view Reco_VolumeUnit("VOLUME_UNIT");

  static constexpr std::string_view Reco_Action("ACTION");
  static constexpr std::string_view Reco_ActionAssignment("ACTION_ASSIGNMENT");
  static constexpr std::string_view Reco_ActionMethod("ACTION_METHOD");
  static constexpr std::string_view Reco_ActionRequestAssignment("ACTION_REQUEST_ASSIGNMENT");
  static constexpr std::string_view Reco_CcDesignApproval("CC_DESIGN_APPROVAL");
  static constexpr std::string_view Reco_CcDesignCertification("CC_DESIGN_CERTIFICATION");
  static constexpr std::string_view Reco_CcDesignContract("CC_DESIGN_CONTRACT");
  static constexpr std::string_view Reco_CcDesignDateAndTimeAssignment(
    "CC_DESIGN_DATE_AND_TIME_ASSIGNMENT");
  static constexpr std::string_view Reco_CcDesignPersonAndOrganizationAssignment(
    "CC_DESIGN_PERSON_AND_ORGANIZATION_ASSIGNMENT");
  static constexpr std::string_view Reco_CcDesignSecurityClassification(
    "CC_DESIGN_SECURITY_CLASSIFICATION");
  static constexpr std::string_view Reco_CcDesignSpecificationReference(
    "CC_DESIGN_SPECIFICATION_REFERENCE");
  static constexpr std::string_view Reco_Certification("CERTIFICATION");
  static constexpr std::string_view Reco_CertificationAssignment("CERTIFICATION_ASSIGNMENT");
  static constexpr std::string_view Reco_CertificationType("CERTIFICATION_TYPE");
  static constexpr std::string_view Reco_Change("CHANGE");
  static constexpr std::string_view Reco_ChangeRequest("CHANGE_REQUEST");
  static constexpr std::string_view Reco_ConfigurationDesign("CONFIGURATION_DESIGN");
  static constexpr std::string_view Reco_ConfigurationEffectivity("CONFIGURATION_EFFECTIVITY");
  static constexpr std::string_view Reco_Contract("CONTRACT");
  static constexpr std::string_view Reco_ContractAssignment("CONTRACT_ASSIGNMENT");
  static constexpr std::string_view Reco_ContractType("CONTRACT_TYPE");
  static constexpr std::string_view Reco_ProductConcept("PRODUCT_CONCEPT");
  static constexpr std::string_view Reco_ProductConceptContext("PRODUCT_CONCEPT_CONTEXT");
  static constexpr std::string_view Reco_StartRequest("START_REQUEST");
  static constexpr std::string_view Reco_StartWork("START_WORK");
  static constexpr std::string_view Reco_VersionedActionRequest("VERSIONED_ACTION_REQUEST");
  static constexpr std::string_view Reco_ProductCategoryRelationship(
    "PRODUCT_CATEGORY_RELATIONSHIP");
  static constexpr std::string_view Reco_ActionRequestSolution("ACTION_REQUEST_SOLUTION");
  static constexpr std::string_view Reco_DraughtingModel("DRAUGHTING_MODEL");

  static constexpr std::string_view Reco_AngularLocation("ANGULAR_LOCATION");
  static constexpr std::string_view Reco_AngularSize("ANGULAR_SIZE");
  static constexpr std::string_view Reco_DimensionalCharacteristicRepresentation(
    "DIMENSIONAL_CHARACTERISTIC_REPRESENTATION");
  static constexpr std::string_view Reco_DimensionalLocation("DIMENSIONAL_LOCATION");
  static constexpr std::string_view Reco_DimensionalLocationWithPath(
    "DIMENSIONAL_LOCATION_WITH_PATH");
  static constexpr std::string_view Reco_DimensionalSize("DIMENSIONAL_SIZE");
  static constexpr std::string_view Reco_DimensionalSizeWithPath("DIMENSIONAL_SIZE_WITH_PATH");
  static constexpr std::string_view Reco_ShapeDimensionRepresentation(
    "SHAPE_DIMENSION_REPRESENTATION");

  static constexpr std::string_view Reco_DocumentRepresentationType("DOCUMENT_REPRESENTATION_TYPE");
  static constexpr std::string_view Reco_ObjectRole("OBJECT_ROLE");
  static constexpr std::string_view Reco_RoleAssociation("ROLE_ASSOCIATION");
  static constexpr std::string_view Reco_IdentificationRole("IDENTIFICATION_ROLE");
  static constexpr std::string_view Reco_IdentificationAssignment("IDENTIFICATION_ASSIGNMENT");
  static constexpr std::string_view Reco_ExternalIdentificationAssignment(
    "EXTERNAL_IDENTIFICATION_ASSIGNMENT");
  static constexpr std::string_view Reco_EffectivityAssignment("EFFECTIVITY_ASSIGNMENT");
  static constexpr std::string_view Reco_NameAssignment("NAME_ASSIGNMENT");
  static constexpr std::string_view Reco_GeneralProperty("GENERAL_PROPERTY");
  static constexpr std::string_view Reco_Class("CLASS");
  static constexpr std::string_view Reco_ExternallyDefinedClass("EXTERNALLY_DEFINED_Class");
  static constexpr std::string_view Reco_ExternallyDefinedGeneralProperty(
    "EXTERNALLY_DEFINED_GENERAL_PROPERTY");
  static constexpr std::string_view Reco_AppliedExternalIdentificationAssignment(
    "APPLIED_EXTERNAL_IDENTIFICATION_ASSIGNMENT");

  static constexpr std::string_view Reco_CompositeShapeAspect("COMPOSITE_SHAPE_ASPECT");
  static constexpr std::string_view Reco_DerivedShapeAspect("DERIVED_SHAPE_ASPECT");
  static constexpr std::string_view Reco_Extension("EXTENSION");
  static constexpr std::string_view Reco_DirectedDimensionalLocation(
    "DIRECTED_DIMENSIONAL_LOCATION");
  static constexpr std::string_view Reco_LimitsAndFits("LIMITS_AND_FITS");
  static constexpr std::string_view Reco_ToleranceValue("TOLERANCE_VALUE");
  static constexpr std::string_view Reco_MeasureQualification("MEASURE_QUALIFICATION");
  static constexpr std::string_view Reco_PlusMinusTolerance("PLUS_MINUS_TOLERANCE");
  static constexpr std::string_view Reco_PrecisionQualifier("PRECISION_QUALIFIER");
  static constexpr std::string_view Reco_TypeQualifier("TYPE_QUALIFIER");
  static constexpr std::string_view Reco_QualifiedRepresentationItem(
    "QUALIFIED_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_CompoundRepresentationItem("COMPOUND_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_ValueRange("VALUE_RANGE");
  static constexpr std::string_view Reco_ShapeAspectDerivingRelationship(
    "SHAPE_ASPECT_DERIVING_RELATIONSHIP");

  static constexpr std::string_view Reco_CompoundShapeRepresentation(
    "COMPOUND_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_ConnectedEdgeSet("CONNECTED_EDGE_SET");
  static constexpr std::string_view Reco_ConnectedFaceShapeRepresentation(
    "CONNECTED_FACE_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_EdgeBasedWireframeModel("EDGE_BASED_WIREFRAME_MODEL");
  static constexpr std::string_view Reco_EdgeBasedWireframeShapeRepresentation(
    "EDGE_BASED_WIREFRAME_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_FaceBasedSurfaceModel("FACE_BASED_SURFACE_MODEL");
  static constexpr std::string_view Reco_NonManifoldSurfaceShapeRepresentation(
    "NON_MANIFOLD_SURFACE_SHAPE_REPRESENTATION");

  static constexpr std::string_view Reco_OrientedSurface("ORIENTED_SURFACE");
  static constexpr std::string_view Reco_Subface("SUBFACE");
  static constexpr std::string_view Reco_Subedge("SUBEDGE");
  static constexpr std::string_view Reco_SeamEdge("SEAM_EDGE");
  static constexpr std::string_view Reco_ConnectedFaceSubSet("CONNECTED_FACE_SUB_SET");

  static constexpr std::string_view Reco_EulerAngles("EULER_ANGLES");
  static constexpr std::string_view Reco_MassUnit("MASS_UNIT");
  static constexpr std::string_view Reco_MassMeasureWithUnit("MASS_MEASURE_WITH_UNIT");
  static constexpr std::string_view Reco_ThermodynamicTemperatureUnit(
    "THERMODYNAMIC_TEMPERATURE_UNIT");
  static constexpr std::string_view Reco_AnalysisItemWithinRepresentation(
    "ANALYSIS_ITEM_WITHIN_REPRESENTATION");
  static constexpr std::string_view Reco_Curve3dElementDescriptor("CURVE_3D_ELEMENT_DESCRIPTOR");
  static constexpr std::string_view Reco_CurveElementEndReleasePacket(
    "CURVE_ELEMENT_END_RELEASE_PACKET");
  static constexpr std::string_view Reco_CurveElementSectionDefinition(
    "CURVE_ELEMENT_SECTION_DEFINITION");
  static constexpr std::string_view Reco_CurveElementSectionDerivedDefinitions(
    "CURVE_ELEMENT_SECTION_DERIVED_DEFINITIONS");
  static constexpr std::string_view Reco_ElementDescriptor("ELEMENT_DESCRIPTOR");
  static constexpr std::string_view Reco_ElementMaterial("ELEMENT_MATERIAL");
  static constexpr std::string_view Reco_Surface3dElementDescriptor(
    "SURFACE_3D_ELEMENT_DESCRIPTOR");
  static constexpr std::string_view Reco_SurfaceElementProperty("SURFACE_ELEMENT_PROPERTY");
  static constexpr std::string_view Reco_SurfaceSection("SURFACE_SECTION");
  static constexpr std::string_view Reco_SurfaceSectionField("SURFACE_SECTION_FIELD");
  static constexpr std::string_view Reco_SurfaceSectionFieldConstant(
    "SURFACE_SECTION_FIELD_CONSTANT");
  static constexpr std::string_view Reco_SurfaceSectionFieldVarying(
    "SURFACE_SECTION_FIELD_VARYING");
  static constexpr std::string_view Reco_UniformSurfaceSection("UNIFORM_SURFACE_SECTION");
  static constexpr std::string_view Reco_Volume3dElementDescriptor("VOLUME_3D_ELEMENT_DESCRIPTOR");
  static constexpr std::string_view Reco_AlignedCurve3dElementCoordinateSystem(
    "ALIGNED_CURVE_3D_ELEMENT_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_ArbitraryVolume3dElementCoordinateSystem(
    "ARBITRARY_VOLUME_3D_ELEMENT_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_Curve3dElementProperty("CURVE_3D_ELEMENT_PROPERTY");
  static constexpr std::string_view Reco_Curve3dElementRepresentation(
    "CURVE_3D_ELEMENT_REPRESENTATION");
  static constexpr std::string_view Reco_Node("NODE");

  static constexpr std::string_view Reco_CurveElementEndOffset("CURVE_ELEMENT_END_OFFSET");
  static constexpr std::string_view Reco_CurveElementEndRelease("CURVE_ELEMENT_END_RELEASE");
  static constexpr std::string_view Reco_CurveElementInterval("CURVE_ELEMENT_INTERVAL");
  static constexpr std::string_view Reco_CurveElementIntervalConstant(
    "CURVE_ELEMENT_INTERVAL_CONSTANT");
  static constexpr std::string_view Reco_DummyNode("DUMMY_NODE");
  static constexpr std::string_view Reco_CurveElementLocation("CURVE_ELEMENT_LOCATION");
  static constexpr std::string_view Reco_ElementGeometricRelationship(
    "ELEMENT_GEOMETRIC_RELATIONSHIP");
  static constexpr std::string_view Reco_ElementGroup("ELEMENT_GROUP");
  static constexpr std::string_view Reco_ElementRepresentation("ELEMENT_REPRESENTATION");
  static constexpr std::string_view Reco_FeaAreaDensity("FEA_AREA_DENSITY");
  static constexpr std::string_view Reco_FeaAxis2Placement3d("FEA_AXIS2_PLACEMENT_3D");
  static constexpr std::string_view Reco_FeaGroup("FEA_GROUP");
  static constexpr std::string_view Reco_FeaLinearElasticity("FEA_LINEAR_ELASTICITY");
  static constexpr std::string_view Reco_FeaMassDensity("FEA_MASS_DENSITY");
  static constexpr std::string_view Reco_FeaMaterialPropertyRepresentation(
    "FEA_MATERIAL_PROPERTY_REPRESENTATION");
  static constexpr std::string_view Reco_FeaMaterialPropertyRepresentationItem(
    "FEA_MATERIAL_PROPERTY_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_FeaModel("FEA_MODEL");
  static constexpr std::string_view Reco_FeaModel3d("FEA_MODEL_3D");
  static constexpr std::string_view Reco_FeaMoistureAbsorption("FEA_MOISTURE_ABSORPTION");
  static constexpr std::string_view Reco_FeaParametricPoint("FEA_PARAMETRIC_POINT");
  static constexpr std::string_view Reco_FeaRepresentationItem("FEA_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_FeaSecantCoefficientOfLinearThermalExpansion(
    "FEA_SECANT_COEFFICIENT_OF_LINEAR_THERMAL_EXPANSION");
  static constexpr std::string_view Reco_FeaShellBendingStiffness("FEA_SHELL_BENDING_STIFFNESS");
  static constexpr std::string_view Reco_FeaShellMembraneBendingCouplingStiffness(
    "FEA_SHELL_MEMBRANE_BENDING_COUPLING_STIFFNESS");
  static constexpr std::string_view Reco_FeaShellMembraneStiffness("FEA_SHELL_MEMBRANE_STIFFNESS");
  static constexpr std::string_view Reco_FeaShellShearStiffness("FEA_SHELL_SHEAR_STIFFNESS");
  static constexpr std::string_view Reco_GeometricNode("GEOMETRIC_NODE");
  static constexpr std::string_view Reco_FeaTangentialCoefficientOfLinearThermalExpansion(
    "FEA_TANGENTIAL_COEFFICIENT_OF_LINEAR_THERMAL_EXPANSION");
  static constexpr std::string_view Reco_NodeGroup("NODE_GROUP");
  static constexpr std::string_view Reco_NodeRepresentation("NODE_REPRESENTATION");
  static constexpr std::string_view Reco_NodeSet("NODE_SET");
  static constexpr std::string_view Reco_NodeWithSolutionCoordinateSystem(
    "NODE_WITH_SOLUTION_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_NodeWithVector("NODE_WITH_VECTOR");
  static constexpr std::string_view Reco_ParametricCurve3dElementCoordinateDirection(
    "PARAMETRIC_CURVE_3D_ELEMENT_COORDINATE_DIRECTION");
  static constexpr std::string_view Reco_ParametricCurve3dElementCoordinateSystem(
    "PARAMETRIC_CURVE_3D_ELEMENT_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_ParametricSurface3dElementCoordinateSystem(
    "PARAMETRIC_SURFACE_3D_ELEMENT_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_Surface3dElementRepresentation(
    "SURFACE_3D_ELEMENT_REPRESENTATION");

  static constexpr std::string_view Reco_Volume3dElementRepresentation(
    "VOLUME_3D_ELEMENT_REPRESENTATION");
  static constexpr std::string_view Reco_DataEnvironment("DATA_ENVIRONMENT");
  static constexpr std::string_view Reco_MaterialPropertyRepresentation(
    "MATERIAL_PROPERTY_REPRESENTATION");
  static constexpr std::string_view Reco_PropertyDefinitionRelationship(
    "PROPERTY_DEFINITION_RELATIONSHIP");
  static constexpr std::string_view Reco_PointRepresentation("POINT_REPRESENTATION");
  static constexpr std::string_view Reco_MaterialProperty("MATERIAL_PROPERTY");
  static constexpr std::string_view Reco_FeaModelDefinition("FEA_MODEL_DEFINITION");
  static constexpr std::string_view Reco_FreedomAndCoefficient("FREEDOM_AND_COEFFICIENT");
  static constexpr std::string_view Reco_FreedomsList("FREEDOMS_LIST");
  static constexpr std::string_view Reco_ProductDefinitionFormationRelationship(
    "PRODUCT_DEFINITION_FORMATION_RELATIONSHIP");

  static constexpr std::string_view Reco_NodeDefinition("NODE_DEFINITION");
  static constexpr std::string_view Reco_StructuralResponseProperty("STRUCTURAL_RESPONSE_PROPERTY");
  static constexpr std::string_view Reco_StructuralResponsePropertyDefinitionRepresentation(
    "STRUCTURAL_RESPONSE_PROPERTY_DEFINITION_REPRESENTATION");
  static constexpr std::string_view Reco_AlignedSurface3dElementCoordinateSystem(
    "ALIGNED_SURFACE_3D_ELEMENT_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_ConstantSurface3dElementCoordinateSystem(
    "CONSTANT_SURFACE_3D_ELEMENT_COORDINATE_SYSTEM");
  static constexpr std::string_view Reco_CurveElementIntervalLinearlyVarying(
    "CURVE_ELEMENT_INTERVAL_LINEARLY_VARYING");
  static constexpr std::string_view Reco_FeaCurveSectionGeometricRelationship(
    "FEA_CURVE_SECTION_GEOMETRIC_RELATIONSHIP");
  static constexpr std::string_view Reco_FeaSurfaceSectionGeometricRelationship(
    "FEA_SURFACE_SECTION_GEOMETRIC_RELATIONSHIP");

  static constexpr std::string_view Reco_DocumentProductAssociation("DOCUMENT_PRODUCT_ASSOCIATION");
  static constexpr std::string_view Reco_DocumentProductEquivalence("DOCUMENT_PRODUCT_EQUIVALENCE");

  static constexpr std::string_view Reco_ShapeRepresentationWithParameters(
    "SHAPE_REPRESENTATION_WITH_PARAMETERS");
  static constexpr std::string_view Reco_AngularityTolerance("ANGULARITY_TOLERANCE");
  static constexpr std::string_view Reco_ConcentricityTolerance("CONCENTRICITY_TOLERANCE");
  static constexpr std::string_view Reco_CircularRunoutTolerance("CIRCULAR_RUNOUT_TOLERANCE");
  static constexpr std::string_view Reco_CoaxialityTolerance("COAXIALITY_TOLERANCE");
  static constexpr std::string_view Reco_CylindricityTolerance("CYLINDRICITY_TOLERANCE");
  static constexpr std::string_view Reco_FlatnessTolerance("FLATNESS_TOLERANCE");
  static constexpr std::string_view Reco_LineProfileTolerance("LINE_PROFILE_TOLERANCE");
  static constexpr std::string_view Reco_ParallelismTolerance("PARALLELISM_TOLERANCE");
  static constexpr std::string_view Reco_PerpendicularityTolerance("PERPENDICULARITY_TOLERANCE");
  static constexpr std::string_view Reco_PositionTolerance("POSITION_TOLERANCE");
  static constexpr std::string_view Reco_RoundnessTolerance("ROUNDNESS_TOLERANCE");
  static constexpr std::string_view Reco_StraightnessTolerance("STRAIGHTNESS_TOLERANCE");
  static constexpr std::string_view Reco_SurfaceProfileTolerance("SURFACE_PROFILE_TOLERANCE");
  static constexpr std::string_view Reco_SymmetryTolerance("SYMMETRY_TOLERANCE");
  static constexpr std::string_view Reco_TotalRunoutTolerance("TOTAL_RUNOUT_TOLERANCE");
  static constexpr std::string_view Reco_GeometricTolerance("GEOMETRIC_TOLERANCE");
  static constexpr std::string_view Reco_GeometricToleranceRelationship(
    "GEOMETRIC_TOLERANCE_RELATIONSHIP");
  static constexpr std::string_view Reco_GeometricToleranceWithDatumReference(
    "GEOMETRIC_TOLERANCE_WITH_DATUM_REFERENCE");
  static constexpr std::string_view Reco_ModifiedGeometricTolerance("MODIFIED_GEOMETRIC_TOLERANCE");
  static constexpr std::string_view Reco_Datum("DATUM");
  static constexpr std::string_view Reco_DatumFeature("DATUM_FEATURE");
  static constexpr std::string_view Reco_DatumReference("DATUM_REFERENCE");
  static constexpr std::string_view Reco_CommonDatum("COMMON_DATUM");
  static constexpr std::string_view Reco_DatumTarget("DATUM_TARGET");
  static constexpr std::string_view Reco_PlacedDatumTargetFeature("PLACED_DATUM_TARGET_FEATURE");

  static constexpr std::string_view Reco_Apex("APEX");
  static constexpr std::string_view Reco_CentreOfSymmetry("CENTRE_OF_SYMMETRY");
  static constexpr std::string_view Reco_GeometricAlignment("GEOMETRIC_ALIGNMENT");
  static constexpr std::string_view Reco_PerpendicularTo("PERPENDICULAR_TO");
  static constexpr std::string_view Reco_Tangent("TANGENT");
  static constexpr std::string_view Reco_ParallelOffset("PARALLEL_OFFSET");
  static constexpr std::string_view Reco_GeometricItemSpecificUsage(
    "GEOMETRIC_ITEM_SPECIFIC_USAGE");
  static constexpr std::string_view Reco_IdAttribute("ID_ATTRIBUTE");
  static constexpr std::string_view Reco_ItemIdentifiedRepresentationUsage(
    "ITEM_IDENTIFIED_REPRESENTATION_USAGE");
  static constexpr std::string_view Reco_AllAroundShapeAspect("ALL_AROUND_SHAPE_ASPECT");
  static constexpr std::string_view Reco_BetweenShapeAspect("BETWEEN_SHAPE_ASPECT");
  static constexpr std::string_view Reco_CompositeGroupShapeAspect("COMPOSITE_GROUP_SHAPE_ASPECT");
  static constexpr std::string_view Reco_ContinuosShapeAspect("CONTINUOUS_SHAPE_ASPECT");
  static constexpr std::string_view Reco_GeometricToleranceWithDefinedAreaUnit(
    "GEOMETRIC_TOLERANCE_WITH_DEFINED_AREA_UNIT");
  static constexpr std::string_view Reco_GeometricToleranceWithDefinedUnit(
    "GEOMETRIC_TOLERANCE_WITH_DEFINED_UNIT");
  static constexpr std::string_view Reco_GeometricToleranceWithMaximumTolerance(
    "GEOMETRIC_TOLERANCE_WITH_MAXIMUM_TOLERANCE");
  static constexpr std::string_view Reco_GeometricToleranceWithModifiers(
    "GEOMETRIC_TOLERANCE_WITH_MODIFIERS");
  static constexpr std::string_view Reco_UnequallyDisposedGeometricTolerance(
    "UNEQUALLY_DISPOSED_GEOMETRIC_TOLERANCE");
  static constexpr std::string_view Reco_NonUniformZoneDefinition("NON_UNIFORM_ZONE_DEFINITION");
  static constexpr std::string_view Reco_ProjectedZoneDefinition("PROJECTED_ZONE_DEFINITION");
  static constexpr std::string_view Reco_RunoutZoneDefinition("RUNOUT_ZONE_DEFINITION");
  static constexpr std::string_view Reco_RunoutZoneOrientation("RUNOUT_ZONE_ORIENTATION");
  static constexpr std::string_view Reco_ToleranceZone("TOLERANCE_ZONE");
  static constexpr std::string_view Reco_ToleranceZoneDefinition("TOLERANCE_ZONE_DEFINITION");
  static constexpr std::string_view Reco_ToleranceZoneForm("TOLERANCE_ZONE_FORM");
  static constexpr std::string_view Reco_ValueFormatTypeQualifier("VALUE_FORMAT_TYPE_QUALIFIER");
  static constexpr std::string_view Reco_DatumReferenceCompartment("DATUM_REFERENCE_COMPARTMENT");
  static constexpr std::string_view Reco_DatumReferenceElement("DATUM_REFERENCE_ELEMENT");
  static constexpr std::string_view Reco_DatumReferenceModifierWithValue(
    "DATUM_REFERENCE_MODIFIER_WITH_VALUE");
  static constexpr std::string_view Reco_DatumSystem("DATUM_SYSTEM");
  static constexpr std::string_view Reco_GeneralDatumReference("GENERAL_DATUM_REFERENCE");
  static constexpr std::string_view Reco_IntegerRepresentationItem("INTEGER_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_ValueRepresentationItem("VALUE_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_FeatureForDatumTargetRelationship(
    "FEATURE_FOR_DATUM_TARGET_RELATIONSHIP");
  static constexpr std::string_view Reco_DraughtingModelItemAssociation(
    "DRAUGHTING_MODEL_ITEM_ASSOCIATION");
  static constexpr std::string_view Reco_AnnotationPlane("ANNOTATION_PLANE");

  static constexpr std::string_view Reco_TessellatedAnnotationOccurrence(
    "TESSELLATED_ANNOTATION_OCCURRENCE");
  static constexpr std::string_view Reco_TessellatedGeometricSet("TESSELLATED_GEOMETRIC_SET");
  static constexpr std::string_view Reco_TessellatedCurveSet("TESSELLATED_CURVE_SET");
  static constexpr std::string_view Reco_TessellatedItem("TESSELLATED_ITEM");
  static constexpr std::string_view Reco_RepositionedTessellatedItem(
    "REPOSITIONED_TESSELLATED_ITEM");
  static constexpr std::string_view Reco_CoordinatesList("COORDINATES_LIST");
  static constexpr std::string_view Reco_ConstructiveGeometryRepresentation(
    "CONSTRUCTIVE_GEOMETRY_REPRESENTATION");
  static constexpr std::string_view Reco_ConstructiveGeometryRepresentationRelationship(
    "CONSTRUCTIVE_GEOMETRY_REPRESENTATION_RELATIONSHIP");
  static constexpr std::string_view Reco_CharacterizedRepresentation(
    "CHARACTERIZED_REPRESENTATION");
  static constexpr std::string_view Reco_CameraModelD3MultiClipping(
    "CAMERA_MODEL_D3_MULTI_CLIPPING");
  static constexpr std::string_view Reco_CameraModelD3MultiClippingIntersection(
    "CAMERA_MODEL_D3_MULTI_CLIPPING_INTERSECTION");
  static constexpr std::string_view Reco_CameraModelD3MultiClippingUnion(
    "CAMERA_MODEL_D3_MULTI_CLIPPING_UNION");

  static constexpr std::string_view Reco_SurfaceStyleTransparent("SURFACE_STYLE_TRANSPARENT");
  static constexpr std::string_view Reco_SurfaceStyleReflectanceAmbient(
    "SURFACE_STYLE_REFLECTANCE_AMBIENT");
  static constexpr std::string_view Reco_SurfaceStyleRendering("SURFACE_STYLE_RENDERING");
  static constexpr std::string_view Reco_SurfaceStyleRenderingWithProperties(
    "SURFACE_STYLE_RENDERING_WITH_PROPERTIES");

  static constexpr std::string_view Reco_RepresentationContextReference(
    "REPRESENTATION_CONTEXT_REFERENCE");
  static constexpr std::string_view Reco_RepresentationReference("REPRESENTATION_REFERENCE");
  static constexpr std::string_view Reco_SuParameters("SU_PARAMETERS");
  static constexpr std::string_view Reco_RotationAboutDirection("ROTATION_ABOUT_DIRECTION");
  static constexpr std::string_view Reco_KinematicJoint("KINEMATIC_JOINT");
  static constexpr std::string_view Reco_ActuatedKinematicPair("ACTUATED_KINEMATIC_PAIR");
  static constexpr std::string_view Reco_ContextDependentKinematicLinkRepresentation(
    "CONTEXT_DEPENDENT_KINEMATIC_LINK_REPRESENTATION");
  static constexpr std::string_view Reco_CylindricalPair("CYLINDRICAL_PAIR");
  static constexpr std::string_view Reco_CylindricalPairValue("CYLINDRICAL_PAIR_VALUE");
  static constexpr std::string_view Reco_CylindricalPairWithRange("CYLINDRICAL_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_FullyConstrainedPair("FULLY_CONSTRAINED_PAIR");
  static constexpr std::string_view Reco_GearPair("GEAR_PAIR");
  static constexpr std::string_view Reco_GearPairValue("GEAR_PAIR_VALUE");
  static constexpr std::string_view Reco_GearPairWithRange("GEAR_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_HomokineticPair("HOMOKINETIC_PAIR");
  static constexpr std::string_view Reco_KinematicLink("KINEMATIC_LINK");
  static constexpr std::string_view Reco_KinematicLinkRepresentationAssociation(
    "KINEMATIC_LINK_REPRESENTATION_ASSOCIATION");
  static constexpr std::string_view Reco_KinematicPropertyMechanismRepresentation(
    "KINEMATIC_PROPERTY_MECHANISM_REPRESENTATION");
  static constexpr std::string_view Reco_KinematicTopologyDirectedStructure(
    "KINEMATIC_TOPOLOGY_DIRECTED_STRUCTURE");
  static constexpr std::string_view Reco_KinematicTopologyNetworkStructure(
    "KINEMATIC_TOPOLOGY_NETWORK_STRUCTURE");
  static constexpr std::string_view Reco_KinematicTopologyStructure("KINEMATIC_TOPOLOGY_STRUCTURE");
  static constexpr std::string_view Reco_LinearFlexibleAndPinionPair(
    "LINEAR_FLEXIBLE_AND_PINION_PAIR");
  static constexpr std::string_view Reco_LinearFlexibleAndPlanarCurvePair(
    "LINEAR_FLEXIBLE_AND_PLANAR_CURVE_PAIR");
  static constexpr std::string_view Reco_LinearFlexibleLinkRepresentation(
    "LINEAR_FLEXIBLE_LINK_REPRESENTATION");
  static constexpr std::string_view Reco_LowOrderKinematicPair("LOW_ORDER_KINEMATIC_PAIR");
  static constexpr std::string_view Reco_LowOrderKinematicPairValue(
    "LOW_ORDER_KINEMATIC_PAIR_VALUE");
  static constexpr std::string_view Reco_LowOrderKinematicPairWithRange(
    "LOW_ORDER_KINEMATIC_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_MechanismRepresentation("MECHANISM_REPRESENTATION");
  static constexpr std::string_view Reco_OrientedJoint("ORIENTED_JOINT");
  static constexpr std::string_view Reco_PairRepresentationRelationship(
    "PAIR_REPRESENTATION_RELATIONSHIP");
  static constexpr std::string_view Reco_PlanarCurvePair("PLANAR_CURVE_PAIR");
  static constexpr std::string_view Reco_PlanarCurvePairRange("PLANAR_CURVE_PAIR_RANGE");
  static constexpr std::string_view Reco_PlanarPair("PLANAR_PAIR");
  static constexpr std::string_view Reco_PlanarPairValue("PLANAR_PAIR_VALUE");
  static constexpr std::string_view Reco_PlanarPairWithRange("PLANAR_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_PointOnPlanarCurvePair("POINT_ON_PLANAR_CURVE_PAIR");
  static constexpr std::string_view Reco_PointOnPlanarCurvePairValue(
    "POINT_ON_PLANAR_CURVE_PAIR_VALUE");
  static constexpr std::string_view Reco_PointOnPlanarCurvePairWithRange(
    "POINT_ON_PLANAR_CURVE_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_PointOnSurfacePair("POINT_ON_SURFACE_PAIR");
  static constexpr std::string_view Reco_PointOnSurfacePairValue("POINT_ON_SURFACE_PAIR_VALUE");
  static constexpr std::string_view Reco_PointOnSurfacePairWithRange(
    "POINT_ON_SURFACE_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_PrismaticPair("PRISMATIC_PAIR");
  static constexpr std::string_view Reco_PrismaticPairValue("PRISMATIC_PAIR_VALUE");
  static constexpr std::string_view Reco_PrismaticPairWithRange("PRISMATIC_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_ProductDefinitionKinematics(
    "PRODUCT_DEFINITION_KINEMATICS");
  static constexpr std::string_view Reco_ProductDefinitionRelationshipKinematics(
    "PRODUCT_DEFINITION_RELATIONSHIP_KINEMATICS");
  static constexpr std::string_view Reco_RackAndPinionPair("RACK_AND_PINION_PAIR");
  static constexpr std::string_view Reco_RackAndPinionPairValue("RACK_AND_PINION_PAIR_VALUE");
  static constexpr std::string_view Reco_RackAndPinionPairWithRange(
    "RACK_AND_PINION_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_RevolutePair("REVOLUTE_PAIR");
  static constexpr std::string_view Reco_RevolutePairValue("REVOLUTE_PAIR_VALUE");
  static constexpr std::string_view Reco_RevolutePairWithRange("REVOLUTE_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_RigidLinkRepresentation("RIGID_LINK_REPRESENTATION");
  static constexpr std::string_view Reco_RollingCurvePair("ROLLING_CURVE_PAIR");
  static constexpr std::string_view Reco_RollingCurvePairValue("ROLLING_CURVE_PAIR_VALUE");
  static constexpr std::string_view Reco_RollingSurfacePair("ROLLING_SURFACE_PAIR");
  static constexpr std::string_view Reco_RollingSurfacePairValue("ROLLING_SURFACE_PAIR_VALUE");
  static constexpr std::string_view Reco_ScrewPair("SCREW_PAIR");
  static constexpr std::string_view Reco_ScrewPairValue("SCREW_PAIR_VALUE");
  static constexpr std::string_view Reco_ScrewPairWithRange("SCREW_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_SlidingCurvePair("SLIDING_CURVE_PAIR");
  static constexpr std::string_view Reco_SlidingCurvePairValue("SLIDING_CURVE_PAIR_VALUE");
  static constexpr std::string_view Reco_SlidingSurfacePair("SLIDING_SURFACE_PAIR");
  static constexpr std::string_view Reco_SlidingSurfacePairValue("SLIDING_SURFACE_PAIR_VALUE");
  static constexpr std::string_view Reco_SphericalPair("SPHERICAL_PAIR");
  static constexpr std::string_view Reco_SphericalPairValue("SPHERICAL_PAIR_VALUE");
  static constexpr std::string_view Reco_SphericalPairWithPin("SPHERICAL_PAIR_WITH_PIN");
  static constexpr std::string_view Reco_SphericalPairWithPinAndRange(
    "SPHERICAL_PAIR_WITH_PIN_AND_RANGE");
  static constexpr std::string_view Reco_SphericalPairWithRange("SPHERICAL_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_SurfacePairWithRange("SURFACE_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_UnconstrainedPair("UNCONSTRAINED_PAIR");
  static constexpr std::string_view Reco_UnconstrainedPairValue("UNCONSTRAINED_PAIR_VALUE");
  static constexpr std::string_view Reco_UniversalPair("UNIVERSAL_PAIR");
  static constexpr std::string_view Reco_UniversalPairValue("UNIVERSAL_PAIR_VALUE");
  static constexpr std::string_view Reco_UniversalPairWithRange("UNIVERSAL_PAIR_WITH_RANGE");
  static constexpr std::string_view Reco_KinematicPair("KINEMATIC_PAIR");
  static constexpr std::string_view Reco_MechanismStateRepresentation(
    "MECHANISM_STATE_REPRESENTATION");

  static constexpr std::string_view Reco_TessellatedConnectingEdge("TESSELLATED_CONNECTING_EDGE");
  static constexpr std::string_view Reco_TessellatedEdge("TESSELLATED_EDGE");
  static constexpr std::string_view Reco_TessellatedPointSet("TESSELLATED_POINT_SET");
  static constexpr std::string_view Reco_TessellatedShapeRepresentation(
    "TESSELLATED_SHAPE_REPRESENTATION");
  static constexpr std::string_view Reco_TessellatedShapeRepresentationWithAccuracyParameters(
    "TESSELLATED_SHAPE_REPRESENTATION_WITH_ACCURACY_PARAMETERS");
  static constexpr std::string_view Reco_TessellatedShell("TESSELLATED_SHELL");
  static constexpr std::string_view Reco_TessellatedSolid("TESSELLATED_SOLID");
  static constexpr std::string_view Reco_TessellatedStructuredItem("TESSELLATED_STRUCTURED_ITEM");
  static constexpr std::string_view Reco_TessellatedVertex("TESSELLATED_VERTEX");
  static constexpr std::string_view Reco_TessellatedWire("TESSELLATED_WIRE");
  static constexpr std::string_view Reco_TriangulatedFace("TRIANGULATED_FACE");
  static constexpr std::string_view Reco_ComplexTriangulatedFace("COMPLEX_TRIANGULATED_FACE");
  static constexpr std::string_view Reco_ComplexTriangulatedSurfaceSet(
    "COMPLEX_TRIANGULATED_SURFACE_SET");
  static constexpr std::string_view Reco_CubicBezierTessellatedEdge(
    "CUBIC_BEZIER_TESSELLATED_EDGE");
  static constexpr std::string_view Reco_CubicBezierTriangulatedFace(
    "CUBIC_BEZIER_TRIANGULATED_FACE");
  static constexpr std::string_view Reco_TriangulatedSurfaceSet("TRIANGULATED_SURFACE_SET");
  static constexpr std::string_view Reco_GeneralPropertyAssociation("GENERAL_PROPERTY_ASSOCIATION");
  static constexpr std::string_view Reco_GeneralPropertyRelationship(
    "GENERAL_PROPERTY_RELATIONSHIP");
  static constexpr std::string_view Reco_BooleanRepresentationItem("BOOLEAN_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_RealRepresentationItem("REAL_REPRESENTATION_ITEM");
  static constexpr std::string_view Reco_MechanicalDesignAndDraughtingRelationship(
    "MECHANICAL_DESIGN_AND_DRAUGHTING_RELATIONSHIP");

  static constexpr std::string_view s_ADDRSS("ADDRSS");
  static constexpr std::string_view s_ABSR("ABSR");
  static constexpr std::string_view s_ADVFC("ADVFC");
  static constexpr std::string_view s_ANCROC("ANCROC");
  static constexpr std::string_view s_ANFLAR("ANFLAR");
  static constexpr std::string_view s_AFAO("AFAO");
  static constexpr std::string_view s_ANNOCC("ANNOCC");
  static constexpr std::string_view s_ANSBOC("ANSBOC");
  static constexpr std::string_view s_ANNSYM("ANNSYM");
  static constexpr std::string_view s_ANSYOC("ANSYOC");
  static constexpr std::string_view s_ANNTXT("ANNTXT");
  static constexpr std::string_view s_ANTXOC("ANTXOC");
  static constexpr std::string_view s_APPCNT("APPCNT");
  static constexpr std::string_view s_APCNEL("APCNEL");
  static constexpr std::string_view s_APPRDF("APPRDF");
  static constexpr std::string_view s_APPRVL("APPRVL");
  static constexpr std::string_view s_APPASS("APPASS");
  static constexpr std::string_view s_APDTTM("APDTTM");
  static constexpr std::string_view s_APPROR("APPROR");
  static constexpr std::string_view s_APPRLT("APPRLT");
  static constexpr std::string_view s_APPRL("APPRL");
  static constexpr std::string_view s_APPSTT("APPSTT");
  static constexpr std::string_view s_ARINST("ARINST");
  static constexpr std::string_view s_ASCMUS("ASCMUS");
  static constexpr std::string_view s_ACUS("ACUS");
  static constexpr std::string_view s_AX1PLC("AX1PLC");
  static constexpr std::string_view s_A2PL2D("A2PL2D");
  static constexpr std::string_view s_A2PL3D("A2PL3D");
  static constexpr std::string_view s_BZRCRV("BZRCRV");
  static constexpr std::string_view s_BZRSRF("BZRSRF");
  static constexpr std::string_view s_BLNRSL("BLNRSL");
  static constexpr std::string_view s_BNDCR("BNDCR");
  static constexpr std::string_view s_BNDCRV("BNDCRV");
  static constexpr std::string_view s_BNDSRF("BNDSRF");
  static constexpr std::string_view s_BRWTVD("BRWTVD");
  static constexpr std::string_view s_BSPCR("BSPCR");
  static constexpr std::string_view s_BSCWK("BSCWK");
  static constexpr std::string_view s_BSPSR("BSPSR");
  static constexpr std::string_view s_BSSWK("BSSWK");
  static constexpr std::string_view s_BXDMN("BXDMN");
  static constexpr std::string_view s_BXHLSP("BXHLSP");
  static constexpr std::string_view s_CLNDT("CLNDT");
  static constexpr std::string_view s_CMRIMG("CMRIMG");
  static constexpr std::string_view s_CMRMDL("CMRMDL");
  static constexpr std::string_view s_CMMDD3("CMMDD3");
  static constexpr std::string_view s_CMRUSG("CMRUSG");
  static constexpr std::string_view s_CRTPNT("CRTPNT");
  static constexpr std::string_view s_CRTROP("CRTROP");
  static constexpr std::string_view s_CTO3("CTO3");
  static constexpr std::string_view s_CLSSHL("CLSSHL");
  static constexpr std::string_view s_CLRRGB("CLRRGB");
  static constexpr std::string_view s_CLRSPC("CLRSPC");
  static constexpr std::string_view s_CMPCRV("CMPCRV");
  static constexpr std::string_view s_CCOS("CCOS");
  static constexpr std::string_view s_CMCRSG("CMCRSG");
  static constexpr std::string_view s_CMPTXT("CMPTXT");
  static constexpr std::string_view s_CTWAC("CTWAC");
  static constexpr std::string_view s_CTWBB("CTWBB");
  static constexpr std::string_view s_CTWE("CTWE");
  static constexpr std::string_view s_CNCSRF("CNCSRF");
  static constexpr std::string_view s_CNFCST("CNFCST");
  static constexpr std::string_view s_CNDPIN("CNDPIN");
  static constexpr std::string_view s_CDORSI("CDORSI");
  static constexpr std::string_view s_CDSR("CDSR");
  static constexpr std::string_view s_CNBSUN("CNBSUN");
  static constexpr std::string_view s_CUTO("CUTO");
  static constexpr std::string_view s_CSSHRP("CSSHRP");
  static constexpr std::string_view s_CSGSLD("CSGSLD");
  static constexpr std::string_view s_CRBNSR("CRBNSR");
  static constexpr std::string_view s_CRVRPL("CRVRPL");
  static constexpr std::string_view s_CRVSTY("CRVSTY");
  static constexpr std::string_view s_CRSTFN("CRSTFN");
  static constexpr std::string_view s_CSFP("CSFP");
  static constexpr std::string_view s_CYLSRF("CYLSRF");
  static constexpr std::string_view s_DTANTM("DTANTM");
  static constexpr std::string_view s_DATA("DATA");
  static constexpr std::string_view s_DTASS("DTASS");
  static constexpr std::string_view s_DTRL("DTRL");
  static constexpr std::string_view s_DTTMRL("DTTMRL");
  static constexpr std::string_view s_DFNSYM("DFNSYM");
  static constexpr std::string_view s_DFNRPR("DFNRPR");
  static constexpr std::string_view s_DGNPCR("DGNPCR");
  static constexpr std::string_view s_DGTRSR("DGTRSR");
  static constexpr std::string_view s_DSRPIT("DSRPIT");
  static constexpr std::string_view s_DMNCRV("DMNCRV");
  static constexpr std::string_view s_DMCRTR("DMCRTR");
  static constexpr std::string_view s_DSGCNT("DSGCNT");
  static constexpr std::string_view s_DMNEXP("DMNEXP");
  static constexpr std::string_view s_DRCTN("DRCTN");
  static constexpr std::string_view s_DRANOC("DRANOC");
  static constexpr std::string_view s_DRGCLL("DRGCLL");
  static constexpr std::string_view s_DPDC("DPDC");
  static constexpr std::string_view s_DPDCF("DPDCF");
  static constexpr std::string_view s_DRSBRP("DRSBRP");
  static constexpr std::string_view s_DRSYRP("DRSYRP");
  static constexpr std::string_view s_DTLWD("DTLWD");
  static constexpr std::string_view s_DRWDFN("DRWDFN");
  static constexpr std::string_view s_DRWRVS("DRWRVS");
  static constexpr std::string_view s_DCMNT("DCMNT");
  static constexpr std::string_view s_DCMRLT("DCMRLT");
  static constexpr std::string_view s_DCMTYP("DCMTYP");
  static constexpr std::string_view s_DCUSCN("DCUSCN");
  static constexpr std::string_view s_EDGCRV("EDGCRV");
  static constexpr std::string_view s_EDGLP("EDGLP");
  static constexpr std::string_view s_EFFCTV("EFFCTV");
  static constexpr std::string_view s_ELMSRF("ELMSRF");
  static constexpr std::string_view s_ELLPS("ELLPS");
  static constexpr std::string_view s_EVDGPC("EVDGPC");
  static constexpr std::string_view s_EXTSRC("EXTSRC");
  static constexpr std::string_view s_EDCF("EDCF");
  static constexpr std::string_view s_EDHS("EDHS");
  static constexpr std::string_view s_EXDFIT("EXDFIT");
  static constexpr std::string_view s_EXDFSY("EXDFSY");
  static constexpr std::string_view s_EDTF("EDTF");
  static constexpr std::string_view s_EDTS("EDTS");
  static constexpr std::string_view s_EXARSL("EXARSL");
  static constexpr std::string_view s_FCBND("FCBND");
  static constexpr std::string_view s_FCOTBN("FCOTBN");
  static constexpr std::string_view s_FCSRF("FCSRF");
  static constexpr std::string_view s_FCTBR("FCTBR");
  static constexpr std::string_view s_FBSR("FBSR");
  static constexpr std::string_view s_FLARST("FLARST");
  static constexpr std::string_view s_FASC("FASC");
  static constexpr std::string_view s_FASH("FASH");
  static constexpr std::string_view s_FASTSW("FASTSW");
  static constexpr std::string_view s_FAST("FAST");
  static constexpr std::string_view s_FNDFTR("FNDFTR");
  static constexpr std::string_view s_GBSSR("GBSSR");
  static constexpr std::string_view s_GBWSR("GBWSR");
  static constexpr std::string_view s_GMCRST("GMCRST");
  static constexpr std::string_view s_GMRPCN("GMRPCN");
  static constexpr std::string_view s_GMRPIT("GMRPIT");
  static constexpr std::string_view s_GMTST("GMTST");
  static constexpr std::string_view s_GC("GC");
  static constexpr std::string_view s_GUAC("GUAC");
  static constexpr std::string_view s_GRPASS("GRPASS");
  static constexpr std::string_view s_GRPRLT("GRPRLT");
  static constexpr std::string_view s_HLSPSL("HLSPSL");
  static constexpr std::string_view s_HYPRBL("HYPRBL");
  static constexpr std::string_view s_INTCRV("INTCRV");
  static constexpr std::string_view s_INVSBL("INVSBL");
  static constexpr std::string_view s_ITDFTR("ITDFTR");
  static constexpr std::string_view s_LMWU("LMWU");
  static constexpr std::string_view s_LNGUNT("LNGUNT");
  static constexpr std::string_view s_LCLTM("LCLTM");
  static constexpr std::string_view s_MNSLBR("MNSLBR");
  static constexpr std::string_view s_MSSR("MSSR");
  static constexpr std::string_view s_MPPITM("MPPITM");
  static constexpr std::string_view s_MDGPA("MDGPA");
  static constexpr std::string_view s_MDGPR("MDGPR");
  static constexpr std::string_view s_MSWTUN("MSWTUN");
  static constexpr std::string_view s_MCHCNT("MCHCNT");
  static constexpr std::string_view s_NMDUNT("NMDUNT");
  static constexpr std::string_view s_NAUO("NAUO");
  static constexpr std::string_view s_OFCR3D("OFCR3D");
  static constexpr std::string_view s_OFFSRF("OFFSRF");
  static constexpr std::string_view s_ODRF("ODRF");
  static constexpr std::string_view s_OPNSHL("OPNSHL");
  static constexpr std::string_view s_ORDDT("ORDDT");
  static constexpr std::string_view s_ORGNZT("ORGNZT");
  static constexpr std::string_view s_ORGASS("ORGASS");
  static constexpr std::string_view s_ORGRL("ORGRL");
  static constexpr std::string_view s_ORGADD("ORGADD");
  static constexpr std::string_view s_ORCLSH("ORCLSH");
  static constexpr std::string_view s_ORNEDG("ORNEDG");
  static constexpr std::string_view s_ORNFC("ORNFC");
  static constexpr std::string_view s_OROPSH("OROPSH");
  static constexpr std::string_view s_ORNPTH("ORNPTH");
  static constexpr std::string_view s_OTBNCR("OTBNCR");
  static constexpr std::string_view s_ORSI("ORSI");
  static constexpr std::string_view s_PRBL("PRBL");
  static constexpr std::string_view s_PRRPCN("PRRPCN");
  static constexpr std::string_view s_PRANOR("PRANOR");
  static constexpr std::string_view s_PAOA("PAOA");
  static constexpr std::string_view s_PAOR("PAOR");
  static constexpr std::string_view s_PRSADD("PRSADD");
  static constexpr std::string_view s_PLCMNT("PLCMNT");
  static constexpr std::string_view s_PLNBX("PLNBX");
  static constexpr std::string_view s_PLNEXT("PLNEXT");
  static constexpr std::string_view s_PAMWU("PAMWU");
  static constexpr std::string_view s_PLANUN("PLANUN");
  static constexpr std::string_view s_PNONCR("PNONCR");
  static constexpr std::string_view s_PNONSR("PNONSR");
  static constexpr std::string_view s_PNTRPL("PNTRPL");
  static constexpr std::string_view s_PNTSTY("PNTSTY");
  static constexpr std::string_view s_PLYLP("PLYLP");
  static constexpr std::string_view s_PLYLN("PLYLN");
  static constexpr std::string_view s_PRDFCL("PRDFCL");
  static constexpr std::string_view s_PDCF("PDCF");
  static constexpr std::string_view s_PRDFIT("PRDFIT");
  static constexpr std::string_view s_PRDFSY("PRDFSY");
  static constexpr std::string_view s_PDTF("PDTF");
  static constexpr std::string_view s_PRSAR("PRSAR");
  static constexpr std::string_view s_PRLYAS("PRLYAS");
  static constexpr std::string_view s_PRSRPR("PRSRPR");
  static constexpr std::string_view s_PRSST("PRSST");
  static constexpr std::string_view s_PRSSZ("PRSSZ");
  static constexpr std::string_view s_PRSTAS("PRSTAS");
  static constexpr std::string_view s_PSBC("PSBC");
  static constexpr std::string_view s_PRSVW("PRSVW");
  static constexpr std::string_view s_PRSITM("PRSITM");
  static constexpr std::string_view s_PRDCT("PRDCT");
  static constexpr std::string_view s_PRDCTG("PRDCTG");
  static constexpr std::string_view s_PRDCNT("PRDCNT");
  static constexpr std::string_view s_PRDDFN("PRDDFN");
  static constexpr std::string_view s_PRDFCN("PRDFCN");
  static constexpr std::string_view s_PRDFEF("PRDFEF");
  static constexpr std::string_view s_PRDFFR("PRDFFR");
  static constexpr std::string_view s_PDFWSS("PDFWSS");
  static constexpr std::string_view s_PRDFRL("PRDFRL");
  static constexpr std::string_view s_PRDFSH("PRDFSH");
  static constexpr std::string_view s_PRDFUS("PRDFUS");
  static constexpr std::string_view s_PDWAD("PDWAD");
  static constexpr std::string_view s_PRPC("PRPC");
  static constexpr std::string_view s_PRUSOC("PRUSOC");
  static constexpr std::string_view s_PRPDFN("PRPDFN");
  static constexpr std::string_view s_PRDFRP("PRDFRP");
  static constexpr std::string_view s_QACU("QACU");
  static constexpr std::string_view s_QSUNCR("QSUNCR");
  static constexpr std::string_view s_QSUNSR("QSUNSR");
  static constexpr std::string_view s_RMWU("RMWU");
  static constexpr std::string_view s_RBSC("RBSC");
  static constexpr std::string_view s_RBSS("RBSS");
  static constexpr std::string_view s_RCCMSR("RCCMSR");
  static constexpr std::string_view s_RCTRSR("RCTRSR");
  static constexpr std::string_view s_RPITGR("RPITGR");
  static constexpr std::string_view s_RCCS("RCCS");
  static constexpr std::string_view s_RPRSNT("RPRSNT");
  static constexpr std::string_view s_RPRCNT("RPRCNT");
  static constexpr std::string_view s_RPRITM("RPRITM");
  static constexpr std::string_view s_RPRMP("RPRMP");
  static constexpr std::string_view s_RPRRLT("RPRRLT");
  static constexpr std::string_view s_RVARSL("RVARSL");
  static constexpr std::string_view s_RGANWD("RGANWD");
  static constexpr std::string_view s_RGCRCN("RGCRCN");
  static constexpr std::string_view s_RGCRCY("RGCRCY");
  static constexpr std::string_view s_RRWT("RRWT");
  static constexpr std::string_view s_SMCRV("SMCRV");
  static constexpr std::string_view s_SCRCLS("SCRCLS");
  static constexpr std::string_view s_SCCLAS("SCCLAS");
  static constexpr std::string_view s_SCCLLV("SCCLLV");
  static constexpr std::string_view s_SHPASP("SHPASP");
  static constexpr std::string_view s_SHASRL("SHASRL");
  static constexpr std::string_view s_SHDFRP("SHDFRP");
  static constexpr std::string_view s_SHPRPR("SHPRPR");
  static constexpr std::string_view s_SHRPRL("SHRPRL");
  static constexpr std::string_view s_SBSM("SBSM");
  static constexpr std::string_view s_SUNT("SUNT");
  static constexpr std::string_view s_SAMWU("SAMWU");
  static constexpr std::string_view s_SLANUN("SLANUN");
  static constexpr std::string_view s_SLDMDL("SLDMDL");
  static constexpr std::string_view s_SLDRPL("SLDRPL");
  static constexpr std::string_view s_SHUO("SHUO");
  static constexpr std::string_view s_SPHSRF("SPHSRF");
  static constexpr std::string_view s_STYITM("STYITM");
  static constexpr std::string_view s_SPPRRL("SPPRRL");
  static constexpr std::string_view s_SRFC("SRFC");
  static constexpr std::string_view s_SRFCRV("SRFCRV");
  static constexpr std::string_view s_SL("SL");
  static constexpr std::string_view s_SROFRV("SROFRV");
  static constexpr std::string_view s_SRFPTC("SRFPTC");
  static constexpr std::string_view s_SRFRPL("SRFRPL");
  static constexpr std::string_view s_SRSDST("SRSDST");
  static constexpr std::string_view s_SRSTBN("SRSTBN");
  static constexpr std::string_view s_SSCG("SSCG");
  static constexpr std::string_view s_SSFA("SSFA");
  static constexpr std::string_view s_SSPL("SSPL");
  static constexpr std::string_view s_SSSC("SSSC");
  static constexpr std::string_view s_SRSTSL("SRSTSL");
  static constexpr std::string_view s_SRSTUS("SRSTUS");
  static constexpr std::string_view s_SWARSL("SWARSL");
  static constexpr std::string_view s_SWPSRF("SWPSRF");
  static constexpr std::string_view s_SYMCLR("SYMCLR");
  static constexpr std::string_view s_SYMRPR("SYMRPR");
  static constexpr std::string_view s_SYRPMP("SYRPMP");
  static constexpr std::string_view s_SYMSTY("SYMSTY");
  static constexpr std::string_view s_SYMTRG("SYMTRG");
  static constexpr std::string_view s_TRMSYM("TRMSYM");
  static constexpr std::string_view s_TXTLTR("TXTLTR");
  static constexpr std::string_view s_TLWAC("TLWAC");
  static constexpr std::string_view s_TLWBB("TLWBB");
  static constexpr std::string_view s_TLWD("TLWD");
  static constexpr std::string_view s_TLWE("TLWE");
  static constexpr std::string_view s_TXTSTY("TXTSTY");
  static constexpr std::string_view s_TSFDF("TSFDF");
  static constexpr std::string_view s_TSWBC("TSWBC");
  static constexpr std::string_view s_TSWM("TSWM");
  static constexpr std::string_view s_TPRPIT("TPRPIT");
  static constexpr std::string_view s_TRDSRF("TRDSRF");
  static constexpr std::string_view s_TRMCRV("TRMCRV");
  static constexpr std::string_view s_TDRF("TDRF");
  static constexpr std::string_view s_UMWU("UMWU");
  static constexpr std::string_view s_UNFCRV("UNFCRV");
  static constexpr std::string_view s_UNFSRF("UNFSRF");
  static constexpr std::string_view s_VRTLP("VRTLP");
  static constexpr std::string_view s_VRTPNT("VRTPNT");
  static constexpr std::string_view s_VWVLM("VWVLM");
  static constexpr std::string_view s_WOYADD("WOYADD");
  static constexpr std::string_view s_TMWU("TMWU");
  static constexpr std::string_view s_RTUNT("RTUNT");
  static constexpr std::string_view s_TMUNT("TMUNT");
  static constexpr std::string_view s_CI3WS("CI3WS");
  static constexpr std::string_view s_CTO2("CTO2");
  static constexpr std::string_view s_DRVUNT("DRVUNT");
  static constexpr std::string_view s_DRUNEL("DRUNEL");
  static constexpr std::string_view s_PRITRP("PRITRP");
  static constexpr std::string_view s_MFUO("MFUO");
  static constexpr std::string_view s_MTRDSG("MTRDSG");
  static constexpr std::string_view s_ADATA("ADATA");
  static constexpr std::string_view s_APDTAS("APDTAS");
  static constexpr std::string_view s_APGRAS("APGRAS");
  static constexpr std::string_view s_APORAS("APORAS");
  static constexpr std::string_view s_APAOA("APAOA");
  static constexpr std::string_view s_APPRIT("APPRIT");
  static constexpr std::string_view s_ASCA("ASCA");
  static constexpr std::string_view s_APDCRF("APDCRF");
  static constexpr std::string_view s_DCMFL("DCMFL");
  static constexpr std::string_view s_CHROBJ("CHROBJ");
  static constexpr std::string_view s_EXFCSL("EXFCSL");
  static constexpr std::string_view s_RVFCSL("RVFCSL");
  static constexpr std::string_view s_SWFCSL("SWFCSL");
  static constexpr std::string_view s_MSRPIT("MSRPIT");
  static constexpr std::string_view s_ARUNT("ARUNT");
  static constexpr std::string_view s_VLMUNT("VLMUNT");
  static constexpr std::string_view s_ACTION("ACTION");
  static constexpr std::string_view s_ACTASS("ACTASS");
  static constexpr std::string_view s_ACTMTH("ACTMTH");
  static constexpr std::string_view s_ACRQAS("ACRQAS");
  static constexpr std::string_view s_CCDSAP("CCDSAP");
  static constexpr std::string_view s_CCDSCR("CCDSCR");
  static constexpr std::string_view s_CCDSCN("CCDSCN");
  static constexpr std::string_view s_CDDATA("CDDATA");
  static constexpr std::string_view s_CDPAOA("CDPAOA");
  static constexpr std::string_view s_CDSC("CDSC");
  static constexpr std::string_view s_CDS("CDS");
  static constexpr std::string_view s_CRTFCT("CRTFCT");
  static constexpr std::string_view s_CRTASS("CRTASS");
  static constexpr std::string_view s_CRTTYP("CRTTYP");
  static constexpr std::string_view s_CHANGE("CHANGE");
  static constexpr std::string_view s_CHNRQS("CHNRQS");
  static constexpr std::string_view s_CNFDSG("CNFDSG");
  static constexpr std::string_view s_CNFEFF("CNFEFF");
  static constexpr std::string_view s_CNTRCT("CNTRCT");
  static constexpr std::string_view s_CNTASS("CNTASS");
  static constexpr std::string_view s_CNTTYP("CNTTYP");
  static constexpr std::string_view s_PRDCNC("PRDCNC");
  static constexpr std::string_view s_PRCNCN("PRCNCN");
  static constexpr std::string_view s_STRRQS("STRRQS");
  static constexpr std::string_view s_STRWRK("STRWRK");
  static constexpr std::string_view s_VRACRQ("VRACRQ");
  static constexpr std::string_view s_PRCTRL("PRCTRL");
  static constexpr std::string_view s_ACRQSL("ACRQSL");
  static constexpr std::string_view s_DRGMDL("DRGMDL");
  static constexpr std::string_view s_ANGLCT("ANGLCT");
  static constexpr std::string_view s_ANGSZ("ANGSZ");
  static constexpr std::string_view s_DMCHRP("DMCHRP");
  static constexpr std::string_view s_DMNLCT("DMNLCT");
  static constexpr std::string_view s_DLWP("DLWP");
  static constexpr std::string_view s_DMNSZ("DMNSZ");
  static constexpr std::string_view s_DSWP("DSWP");
  static constexpr std::string_view s_SHDMRP("SHDMRP");
  static constexpr std::string_view s_DCRPTY("DCRPTY");
  static constexpr std::string_view s_OBJRL("OBJRL");
  static constexpr std::string_view s_RLASS("RLASS");
  static constexpr std::string_view s_IDNRL("IDNRL");
  static constexpr std::string_view s_IDNASS("IDNASS");
  static constexpr std::string_view s_EXIDAS("EXIDAS");
  static constexpr std::string_view s_EFFASS("EFFASS");
  static constexpr std::string_view s_NMASS("NMASS");
  static constexpr std::string_view s_GNRPRP("GNRPRP");
  static constexpr std::string_view s_EDGP("EDGP");
  static constexpr std::string_view s_AEIA("AEIA");
  static constexpr std::string_view s_CMSHAS("CMSHAS");
  static constexpr std::string_view s_DRSHAS("DRSHAS");
  static constexpr std::string_view s_EXTNSN("EXTNSN");
  static constexpr std::string_view s_DRDMLC("DRDMLC");
  static constexpr std::string_view s_LMANFT("LMANFT");
  static constexpr std::string_view s_TLRVL("TLRVL");
  static constexpr std::string_view s_MSRQLF("MSRQLF");
  static constexpr std::string_view s_PLMNTL("PLMNTL");
  static constexpr std::string_view s_PRCQLF("PRCQLF");
  static constexpr std::string_view s_TYPQLF("TYPQLF");
  static constexpr std::string_view s_QLRPIT("QLRPIT");
  static constexpr std::string_view s_CMRPIT("CMRPIT");
  static constexpr std::string_view s_CMS0("CMS0");
  static constexpr std::string_view s_CNEDST("CNEDST");
  static constexpr std::string_view s_EBWM("EBWM");
  static constexpr std::string_view s_EBWSR("EBWSR");
  static constexpr std::string_view s_NMSSR("NMSSR");
  static constexpr std::string_view s_ORNSRF("ORNSRF");
  static constexpr std::string_view s_SBFC("SBFC");
  static constexpr std::string_view s_SBDG("SBDG");
  static constexpr std::string_view s_CFSS("CFSS");
  static constexpr std::string_view s_MSSUNT("MSSUNT");
  static constexpr std::string_view s_THTMUN("THTMUN");
  static constexpr std::string_view s_DTENV("DTENV");
  static constexpr std::string_view s_MTPRRP("MTPRRP");
  static constexpr std::string_view s_PRDFR("PRDFR");
  static constexpr std::string_view s_MTRPRP("MTRPRP");
  static constexpr std::string_view s_PDFR("PDFR");
  static constexpr std::string_view s_DCP1("DCP1");
  static constexpr std::string_view s_DCPREQ("DCPREQ");
  static constexpr std::string_view s_CYLTLR("CYLTLR");
  static constexpr std::string_view s_SRWP("SRWP");
  static constexpr std::string_view s_ANGTLR("ANGTLR");
  static constexpr std::string_view s_CNCTLR("CNCTLR");
  static constexpr std::string_view s_CRRNTL("CRRNTL");
  static constexpr std::string_view s_CXLTLR("CXLTLR");
  static constexpr std::string_view s_FLTTLR("FLTTLR");
  static constexpr std::string_view s_LNP0("LNP0");
  static constexpr std::string_view s_PRLTLR("PRLTLR");
  static constexpr std::string_view s_PRPTLR("PRPTLR");
  static constexpr std::string_view s_PSTTLR("PSTTLR");
  static constexpr std::string_view s_RNDTLR("RNDTLR");
  static constexpr std::string_view s_STRTLR("STRTLR");
  static constexpr std::string_view s_SRPRTL("SRPRTL");
  static constexpr std::string_view s_SYMTLR("SYMTLR");
  static constexpr std::string_view s_TTRNTL("TTRNTL");
  static constexpr std::string_view s_GMTTLR("GMTTLR");
  static constexpr std::string_view s_GMTLRL("GMTLRL");
  static constexpr std::string_view s_GTWDR("GTWDR");
  static constexpr std::string_view s_MDGMTL("MDGMTL");
  static constexpr std::string_view s_DTMFTR("DTMFTR");
  static constexpr std::string_view s_DTMRFR("DTMRFR");
  static constexpr std::string_view s_CMMDTM("CMMDTM");
  static constexpr std::string_view s_DTMTRG("DTMTRG");
  static constexpr std::string_view s_PDT0("PDT0");
  static constexpr std::string_view s_MMWU("MMWU");
  static constexpr std::string_view s_CNOFSY("CNOFSY");
  static constexpr std::string_view s_GMTALG("GMTALG");
  static constexpr std::string_view s_PRPT("PRPT");
  static constexpr std::string_view s_TNGNT("TNGNT");
  static constexpr std::string_view s_PRLOFF("PRLOFF");
  static constexpr std::string_view s_GISU("GISU");
  static constexpr std::string_view s_IDATT("IDATT");
  static constexpr std::string_view s_IIRU("IIRU");
  static constexpr std::string_view s_GTWDU("GTWDU");
  static constexpr std::string_view s_PRZNDF("PRZNDF");
  static constexpr std::string_view s_RNZNDF("RNZNDF");
  static constexpr std::string_view s_RNZNOR("RNZNOR");
  static constexpr std::string_view s_TLRZN("TLRZN");
  static constexpr std::string_view s_TLZNDF("TLZNDF");
  static constexpr std::string_view s_TLZNFR("TLZNFR");
  static constexpr std::string_view s_INRPIT("INRPIT");
  static constexpr std::string_view s_VLRPIT("VLRPIT");
  static constexpr std::string_view s_DMIA("DMIA");
  static constexpr std::string_view s_ANNPLN("ANNPLN");
  static constexpr std::string_view s_CNGMRP("CNGMRP");
  static constexpr std::string_view s_CGRR("CGRR");

  struct StringViewHasher
  {
    size_t operator()(const std::string_view& theKey) const noexcept
    {
      const int aLen = static_cast<int>(theKey.size());
      return opencascade::hashBytes(theKey.data(), aLen);
    }

    bool operator()(const std::string_view& theK1, const std::string_view& theK2) const noexcept
    {
      return theK1 == theK2;
    }
  };

  using StringViewDataMap = NCollection_DataMap<std::string_view, int, StringViewHasher>;

  static StringViewDataMap THE_TYPENUMS;

  static StringViewDataMap THE_TYPESHOR;

  static occ::handle<NCollection_IncAllocator> THE_INC_ALLOCATOR;

  static void initializeTypenums(StringViewDataMap& theTypenums)
  {
    theTypenums.Clear(THE_INC_ALLOCATOR);
    theTypenums.ReSize(1024);
    theTypenums.Bind(Reco_CartesianPoint, 59);
    theTypenums.Bind(Reco_VertexPoint, 316);
    theTypenums.Bind(Reco_OrientedEdge, 181);
    theTypenums.Bind(Reco_EdgeCurve, 116);
    theTypenums.Bind(Reco_SurfaceCurve, 272);
    theTypenums.Bind(Reco_EdgeLoop, 117);
    theTypenums.Bind(Reco_AdvancedFace, 3);
    theTypenums.Bind(Reco_FaceBound, 131);
    theTypenums.Bind(Reco_FaceOuterBound, 132);
    theTypenums.Bind(Reco_Direction, 105);
    theTypenums.Bind(Reco_Vector, 313);
    theTypenums.Bind(Reco_BSplineCurve, 38);
    theTypenums.Bind(Reco_BSplineCurveWithKnots, 39);
    theTypenums.Bind(Reco_BezierCurve, 43);
    theTypenums.Bind(Reco_Pcurve, 190);
    theTypenums.Bind(Reco_QuasiUniformCurve, 236);
    theTypenums.Bind(Reco_RationalBSplineCurve, 239);
    theTypenums.Bind(Reco_TrimmedCurve, 308);
    theTypenums.Bind(Reco_UniformCurve, 311);

    theTypenums.Bind(Reco_BSplineSurface, 40);
    theTypenums.Bind(Reco_BSplineSurfaceWithKnots, 41);
    theTypenums.Bind(Reco_QuasiUniformSurface, 237);
    theTypenums.Bind(Reco_RationalBSplineSurface, 240);
    theTypenums.Bind(Reco_UniformSurface, 312);
    theTypenums.Bind(Reco_BezierSurface, 44);
    theTypenums.Bind(Reco_ConicalSurface, 75);
    theTypenums.Bind(Reco_CylindricalSurface, 90);
    theTypenums.Bind(Reco_SphericalSurface, 269);
    theTypenums.Bind(Reco_ToroidalSurface, 305);
    theTypenums.Bind(Reco_SurfaceOfLinearExtrusion, 273);
    theTypenums.Bind(Reco_SurfaceOfRevolution, 274);

    theTypenums.Bind(Reco_Address, 1);
    theTypenums.Bind(Reco_AdvancedBrepShapeRepresentation, 2);
    theTypenums.Bind(Reco_AnnotationCurveOccurrence, 4);
    theTypenums.Bind(Reco_AnnotationFillArea, 5);
    theTypenums.Bind(Reco_AnnotationFillAreaOccurrence, 6);
    theTypenums.Bind(Reco_AnnotationOccurrence, 7);
    theTypenums.Bind(Reco_AnnotationSubfigureOccurrence, 8);
    theTypenums.Bind(Reco_AnnotationSymbol, 9);
    theTypenums.Bind(Reco_AnnotationSymbolOccurrence, 10);
    theTypenums.Bind(Reco_AnnotationText, 11);
    theTypenums.Bind(Reco_AnnotationTextOccurrence, 12);
    theTypenums.Bind(Reco_ApplicationContext, 13);
    theTypenums.Bind(Reco_ApplicationContextElement, 14);
    theTypenums.Bind(Reco_ApplicationProtocolDefinition, 15);
    theTypenums.Bind(Reco_Approval, 16);
    theTypenums.Bind(Reco_ApprovalAssignment, 17);
    theTypenums.Bind(Reco_ApprovalPersonOrganization, 18);
    theTypenums.Bind(Reco_ApprovalRelationship, 19);
    theTypenums.Bind(Reco_ApprovalRole, 20);
    theTypenums.Bind(Reco_ApprovalStatus, 21);
    theTypenums.Bind(Reco_AreaInSet, 22);
    theTypenums.Bind(Reco_AutoDesignActualDateAndTimeAssignment, 23);
    theTypenums.Bind(Reco_AutoDesignActualDateAssignment, 24);
    theTypenums.Bind(Reco_AutoDesignApprovalAssignment, 25);
    theTypenums.Bind(Reco_AutoDesignDateAndPersonAssignment, 26);
    theTypenums.Bind(Reco_AutoDesignGroupAssignment, 27);
    theTypenums.Bind(Reco_AutoDesignNominalDateAndTimeAssignment, 28);
    theTypenums.Bind(Reco_AutoDesignNominalDateAssignment, 29);
    theTypenums.Bind(Reco_AutoDesignOrganizationAssignment, 30);
    theTypenums.Bind(Reco_AutoDesignPersonAndOrganizationAssignment, 31);
    theTypenums.Bind(Reco_AutoDesignPresentedItem, 32);
    theTypenums.Bind(Reco_AutoDesignSecurityClassificationAssignment, 33);
    theTypenums.Bind(Reco_AutoDesignViewArea, 34);
    theTypenums.Bind(Reco_Axis1Placement, 35);
    theTypenums.Bind(Reco_Axis2Placement2d, 36);
    theTypenums.Bind(Reco_Axis2Placement3d, 37);
    theTypenums.Bind(Reco_BackgroundColour, 42);
    theTypenums.Bind(Reco_Block, 45);
    theTypenums.Bind(Reco_BooleanResult, 46);
    theTypenums.Bind(Reco_BoundaryCurve, 47);
    theTypenums.Bind(Reco_BoundedCurve, 48);
    theTypenums.Bind(Reco_BoundedSurface, 49);
    theTypenums.Bind(Reco_BoxDomain, 50);
    theTypenums.Bind(Reco_BoxedHalfSpace, 51);
    theTypenums.Bind(Reco_BrepWithVoids, 52);
    theTypenums.Bind(Reco_CalendarDate, 53);
    theTypenums.Bind(Reco_CameraImage, 54);
    theTypenums.Bind(Reco_CameraModel, 55);
    theTypenums.Bind(Reco_CameraModelD2, 56);
    theTypenums.Bind(Reco_CameraModelD3, 57);
    theTypenums.Bind(Reco_CameraUsage, 58);
    theTypenums.Bind(Reco_CartesianTransformationOperator, 60);
    theTypenums.Bind(Reco_CartesianTransformationOperator3d, 61);
    theTypenums.Bind(Reco_Circle, 62);
    theTypenums.Bind(Reco_ClosedShell, 63);
    theTypenums.Bind(Reco_Colour, 64);
    theTypenums.Bind(Reco_ColourRgb, 65);
    theTypenums.Bind(Reco_ColourSpecification, 66);
    theTypenums.Bind(Reco_CompositeCurve, 67);
    theTypenums.Bind(Reco_CompositeCurveOnSurface, 68);
    theTypenums.Bind(Reco_CompositeCurveSegment, 69);
    theTypenums.Bind(Reco_CompositeText, 70);
    theTypenums.Bind(Reco_CompositeTextWithAssociatedCurves, 71);
    theTypenums.Bind(Reco_CompositeTextWithBlankingBox, 72);
    theTypenums.Bind(Reco_CompositeTextWithExtent, 73);
    theTypenums.Bind(Reco_Conic, 74);
    theTypenums.Bind(Reco_ConnectedFaceSet, 76);
    theTypenums.Bind(Reco_ContextDependentInvisibility, 77);
    theTypenums.Bind(Reco_ContextDependentOverRidingStyledItem, 78);
    theTypenums.Bind(Reco_ConversionBasedUnit, 79);
    theTypenums.Bind(Reco_CoordinatedUniversalTimeOffset, 80);
    theTypenums.Bind(Reco_CsgRepresentation, 81);
    theTypenums.Bind(Reco_CsgShapeRepresentation, 82);
    theTypenums.Bind(Reco_CsgSolid, 83);
    theTypenums.Bind(Reco_Curve, 84);
    theTypenums.Bind(Reco_CurveBoundedSurface, 85);
    theTypenums.Bind(Reco_CurveReplica, 86);
    theTypenums.Bind(Reco_CurveStyle, 87);
    theTypenums.Bind(Reco_CurveStyleFont, 88);
    theTypenums.Bind(Reco_CurveStyleFontPattern, 89);
    theTypenums.Bind(Reco_Date, 91);
    theTypenums.Bind(Reco_DateAndTime, 92);
    theTypenums.Bind(Reco_DateAndTimeAssignment, 93);
    theTypenums.Bind(Reco_DateAssignment, 94);
    theTypenums.Bind(Reco_DateRole, 95);
    theTypenums.Bind(Reco_DateTimeRole, 96);
    theTypenums.Bind(Reco_DefinedSymbol, 97);
    theTypenums.Bind(Reco_DefinitionalRepresentation, 98);
    theTypenums.Bind(Reco_DegeneratePcurve, 99);
    theTypenums.Bind(Reco_DegenerateToroidalSurface, 100);
    theTypenums.Bind(Reco_DescriptiveRepresentationItem, 101);
    theTypenums.Bind(Reco_DimensionCurve, 102);
    theTypenums.Bind(Reco_DimensionCurveTerminator, 103);
    theTypenums.Bind(Reco_DimensionalExponents, 104);
    theTypenums.Bind(Reco_DraughtingAnnotationOccurrence, 106);
    theTypenums.Bind(Reco_DraughtingCallout, 107);
    theTypenums.Bind(Reco_DraughtingPreDefinedColour, 108);
    theTypenums.Bind(Reco_DraughtingPreDefinedCurveFont, 109);
    theTypenums.Bind(Reco_DraughtingSubfigureRepresentation, 110);
    theTypenums.Bind(Reco_DraughtingSymbolRepresentation, 111);
    theTypenums.Bind(Reco_DraughtingTextLiteralWithDelineation, 112);
    theTypenums.Bind(Reco_DrawingDefinition, 113);
    theTypenums.Bind(Reco_DrawingRevision, 114);
    theTypenums.Bind(Reco_Edge, 115);
    theTypenums.Bind(Reco_ElementarySurface, 118);
    theTypenums.Bind(Reco_Ellipse, 119);
    theTypenums.Bind(Reco_EvaluatedDegeneratePcurve, 120);
    theTypenums.Bind(Reco_ExternalSource, 121);
    theTypenums.Bind(Reco_ExternallyDefinedCurveFont, 122);
    theTypenums.Bind(Reco_ExternallyDefinedHatchStyle, 123);
    theTypenums.Bind(Reco_ExternallyDefinedItem, 124);
    theTypenums.Bind(Reco_ExternallyDefinedSymbol, 125);
    theTypenums.Bind(Reco_ExternallyDefinedTextFont, 126);
    theTypenums.Bind(Reco_ExternallyDefinedTileStyle, 127);
    theTypenums.Bind(Reco_ExtrudedAreaSolid, 128);
    theTypenums.Bind(Reco_Face, 129);
    theTypenums.Bind(Reco_FaceSurface, 133);
    theTypenums.Bind(Reco_FacetedBrep, 134);
    theTypenums.Bind(Reco_FacetedBrepShapeRepresentation, 135);
    theTypenums.Bind(Reco_FillAreaStyle, 136);
    theTypenums.Bind(Reco_FillAreaStyleColour, 137);
    theTypenums.Bind(Reco_FillAreaStyleHatching, 138);
    theTypenums.Bind(Reco_FillAreaStyleTileSymbolWithStyle, 139);
    theTypenums.Bind(Reco_FillAreaStyleTiles, 140);
    theTypenums.Bind(Reco_FunctionallyDefinedTransformation, 141);
    theTypenums.Bind(Reco_GeometricCurveSet, 142);
    theTypenums.Bind(Reco_GeometricRepresentationContext, 143);
    theTypenums.Bind(Reco_GeometricRepresentationItem, 144);
    theTypenums.Bind(Reco_GeometricSet, 145);
    theTypenums.Bind(Reco_GeometricallyBoundedSurfaceShapeRepresentation, 146);
    theTypenums.Bind(Reco_GeometricallyBoundedWireframeShapeRepresentation, 147);
    theTypenums.Bind(Reco_GlobalUncertaintyAssignedContext, 148);
    theTypenums.Bind(Reco_GlobalUnitAssignedContext, 149);
    theTypenums.Bind(Reco_Group, 150);
    theTypenums.Bind(Reco_GroupAssignment, 151);
    theTypenums.Bind(Reco_GroupRelationship, 152);
    theTypenums.Bind(Reco_HalfSpaceSolid, 153);
    theTypenums.Bind(Reco_Hyperbola, 154);
    theTypenums.Bind(Reco_IntersectionCurve, 155);
    theTypenums.Bind(Reco_Invisibility, 156);
    theTypenums.Bind(Reco_LengthMeasureWithUnit, 157);
    theTypenums.Bind(Reco_LengthUnit, 158);
    theTypenums.Bind(Reco_Line, 159);
    theTypenums.Bind(Reco_LocalTime, 160);
    theTypenums.Bind(Reco_Loop, 161);
    theTypenums.Bind(Reco_ManifoldSolidBrep, 162);
    theTypenums.Bind(Reco_ManifoldSurfaceShapeRepresentation, 163);
    theTypenums.Bind(Reco_MappedItem, 164);
    theTypenums.Bind(Reco_MeasureWithUnit, 165);
    theTypenums.Bind(Reco_MechanicalDesignGeometricPresentationArea, 166);
    theTypenums.Bind(Reco_MechanicalDesignGeometricPresentationRepresentation, 167);
    theTypenums.Bind(Reco_MechanicalDesignPresentationArea, 168);
    theTypenums.Bind(Reco_NamedUnit, 169);
    theTypenums.Bind(Reco_OffsetCurve3d, 171);
    theTypenums.Bind(Reco_OffsetSurface, 172);
    theTypenums.Bind(Reco_OneDirectionRepeatFactor, 173);
    theTypenums.Bind(Reco_OpenShell, 174);
    theTypenums.Bind(Reco_OrdinalDate, 175);
    theTypenums.Bind(Reco_Organization, 176);
    theTypenums.Bind(Reco_OrganizationAssignment, 177);
    theTypenums.Bind(Reco_OrganizationRole, 178);
    theTypenums.Bind(Reco_OrganizationalAddress, 179);
    theTypenums.Bind(Reco_OrientedClosedShell, 180);
    theTypenums.Bind(Reco_OrientedFace, 182);
    theTypenums.Bind(Reco_OrientedOpenShell, 183);
    theTypenums.Bind(Reco_OrientedPath, 184);
    theTypenums.Bind(Reco_OuterBoundaryCurve, 185);
    theTypenums.Bind(Reco_OverRidingStyledItem, 186);
    theTypenums.Bind(Reco_Parabola, 187);
    theTypenums.Bind(Reco_ParametricRepresentationContext, 188);
    theTypenums.Bind(Reco_Path, 189);
    theTypenums.Bind(Reco_Person, 191);
    theTypenums.Bind(Reco_PersonAndOrganization, 192);
    theTypenums.Bind(Reco_PersonAndOrganizationAssignment, 193);
    theTypenums.Bind(Reco_PersonAndOrganizationRole, 194);
    theTypenums.Bind(Reco_PersonalAddress, 195);
    theTypenums.Bind(Reco_Placement, 196);
    theTypenums.Bind(Reco_PlanarBox, 197);
    theTypenums.Bind(Reco_PlanarExtent, 198);
    theTypenums.Bind(Reco_Plane, 199);
    theTypenums.Bind(Reco_PlaneAngleMeasureWithUnit, 200);
    theTypenums.Bind(Reco_PlaneAngleUnit, 201);
    theTypenums.Bind(Reco_Point, 202);
    theTypenums.Bind(Reco_PointOnCurve, 203);
    theTypenums.Bind(Reco_PointOnSurface, 204);
    theTypenums.Bind(Reco_PointReplica, 205);
    theTypenums.Bind(Reco_PointStyle, 206);
    theTypenums.Bind(Reco_PolyLoop, 207);
    theTypenums.Bind(Reco_Polyline, 208);
    theTypenums.Bind(Reco_PreDefinedColour, 209);
    theTypenums.Bind(Reco_PreDefinedCurveFont, 210);
    theTypenums.Bind(Reco_PreDefinedItem, 211);
    theTypenums.Bind(Reco_PreDefinedSymbol, 212);
    theTypenums.Bind(Reco_PreDefinedTextFont, 213);
    theTypenums.Bind(Reco_PresentationArea, 214);
    theTypenums.Bind(Reco_PresentationLayerAssignment, 215);
    theTypenums.Bind(Reco_PresentationRepresentation, 216);
    theTypenums.Bind(Reco_PresentationSet, 217);
    theTypenums.Bind(Reco_PresentationSize, 218);
    theTypenums.Bind(Reco_PresentationStyleAssignment, 219);
    theTypenums.Bind(Reco_PresentationStyleByContext, 220);
    theTypenums.Bind(Reco_PresentationView, 221);
    theTypenums.Bind(Reco_PresentedItem, 222);
    theTypenums.Bind(Reco_Product, 223);
    theTypenums.Bind(Reco_ProductCategory, 224);
    theTypenums.Bind(Reco_ProductContext, 225);
    theTypenums.Bind(Reco_ProductDataRepresentationView, 226);
    theTypenums.Bind(Reco_ProductDefinition, 227);
    theTypenums.Bind(Reco_ProductDefinitionContext, 228);
    theTypenums.Bind(Reco_ProductDefinitionFormation, 229);
    theTypenums.Bind(Reco_ProductDefinitionFormationWithSpecifiedSource, 230);
    theTypenums.Bind(Reco_ProductDefinitionShape, 231);
    theTypenums.Bind(Reco_ProductRelatedProductCategory, 232);
    theTypenums.Bind(Reco_ProductType, 233);
    theTypenums.Bind(Reco_PropertyDefinition, 234);
    theTypenums.Bind(Reco_PropertyDefinitionRepresentation, 235);
    theTypenums.Bind(Reco_RatioMeasureWithUnit, 238);
    theTypenums.Bind(Reco_RectangularCompositeSurface, 241);
    theTypenums.Bind(Reco_RectangularTrimmedSurface, 242);
    theTypenums.Bind(Reco_RepItemGroup, 243);
    theTypenums.Bind(Reco_ReparametrisedCompositeCurveSegment, 244);
    theTypenums.Bind(Reco_Representation, 245);
    theTypenums.Bind(Reco_RepresentationContext, 246);
    theTypenums.Bind(Reco_RepresentationItem, 247);
    theTypenums.Bind(Reco_RepresentationMap, 248);
    theTypenums.Bind(Reco_RepresentationRelationship, 249);
    theTypenums.Bind(Reco_RevolvedAreaSolid, 250);
    theTypenums.Bind(Reco_RightAngularWedge, 251);
    theTypenums.Bind(Reco_RightCircularCone, 252);
    theTypenums.Bind(Reco_RightCircularCylinder, 253);
    theTypenums.Bind(Reco_SeamCurve, 254);
    theTypenums.Bind(Reco_SecurityClassification, 255);
    theTypenums.Bind(Reco_SecurityClassificationAssignment, 256);
    theTypenums.Bind(Reco_SecurityClassificationLevel, 257);
    theTypenums.Bind(Reco_ShapeAspect, 258);
    theTypenums.Bind(Reco_ShapeAspectRelationship, 259);
    theTypenums.Bind(Reco_ShapeAspectTransition, 260);
    theTypenums.Bind(Reco_ShapeDefinitionRepresentation, 261);
    theTypenums.Bind(Reco_ShapeRepresentation, 262);
    theTypenums.Bind(Reco_ShellBasedSurfaceModel, 263);
    theTypenums.Bind(Reco_SiUnit, 264);
    theTypenums.Bind(Reco_SolidAngleMeasureWithUnit, 265);
    theTypenums.Bind(Reco_SolidModel, 266);
    theTypenums.Bind(Reco_SolidReplica, 267);
    theTypenums.Bind(Reco_Sphere, 268);
    theTypenums.Bind(Reco_StyledItem, 270);
    theTypenums.Bind(Reco_Surface, 271);
    theTypenums.Bind(Reco_SurfacePatch, 275);
    theTypenums.Bind(Reco_SurfaceReplica, 276);
    theTypenums.Bind(Reco_SurfaceSideStyle, 277);
    theTypenums.Bind(Reco_SurfaceStyleBoundary, 278);
    theTypenums.Bind(Reco_SurfaceStyleControlGrid, 279);
    theTypenums.Bind(Reco_SurfaceStyleFillArea, 280);
    theTypenums.Bind(Reco_SurfaceStyleParameterLine, 281);
    theTypenums.Bind(Reco_SurfaceStyleSegmentationCurve, 282);
    theTypenums.Bind(Reco_SurfaceStyleSilhouette, 283);
    theTypenums.Bind(Reco_SurfaceStyleUsage, 284);
    theTypenums.Bind(Reco_SweptAreaSolid, 285);
    theTypenums.Bind(Reco_SweptSurface, 286);
    theTypenums.Bind(Reco_SymbolColour, 287);
    theTypenums.Bind(Reco_SymbolRepresentation, 288);
    theTypenums.Bind(Reco_SymbolRepresentationMap, 289);
    theTypenums.Bind(Reco_SymbolStyle, 290);
    theTypenums.Bind(Reco_SymbolTarget, 291);
    theTypenums.Bind(Reco_Template, 292);
    theTypenums.Bind(Reco_TemplateInstance, 293);
    theTypenums.Bind(Reco_TerminatorSymbol, 294);
    theTypenums.Bind(Reco_TextLiteral, 295);
    theTypenums.Bind(Reco_TextLiteralWithAssociatedCurves, 296);
    theTypenums.Bind(Reco_TextLiteralWithBlankingBox, 297);
    theTypenums.Bind(Reco_TextLiteralWithDelineation, 298);
    theTypenums.Bind(Reco_TextLiteralWithExtent, 299);
    theTypenums.Bind(Reco_TextStyle, 300);
    theTypenums.Bind(Reco_TextStyleForDefinedFont, 301);
    theTypenums.Bind(Reco_TextStyleWithBoxCharacteristics, 302);
    theTypenums.Bind(Reco_TextStyleWithMirror, 303);
    theTypenums.Bind(Reco_TopologicalRepresentationItem, 304);
    theTypenums.Bind(Reco_Torus, 306);
    theTypenums.Bind(Reco_TransitionalShapeRepresentation, 307);
    theTypenums.Bind(Reco_TwoDirectionRepeatFactor, 309);
    theTypenums.Bind(Reco_UncertaintyMeasureWithUnit, 310);
    theTypenums.Bind(Reco_Vertex, 314);
    theTypenums.Bind(Reco_VertexLoop, 315);
    theTypenums.Bind(Reco_ViewVolume, 317);
    theTypenums.Bind(Reco_WeekOfYearAndDayDate, 318);

    theTypenums.Bind(Reco_SolidAngleUnit, 336);
    theTypenums.Bind(Reco_MechanicalContext, 339);
    theTypenums.Bind(Reco_DesignContext, 340);

    theTypenums.Bind(Reco_TimeMeasureWithUnit, 341);
    theTypenums.Bind(Reco_RatioUnit, 342);
    theTypenums.Bind(Reco_TimeUnit, 343);
    theTypenums.Bind(Reco_ApprovalDateTime, 348);
    theTypenums.Bind(Reco_CameraImage2dWithScale, 349);
    theTypenums.Bind(Reco_CameraImage3dWithScale, 350);
    theTypenums.Bind(Reco_CartesianTransformationOperator2d, 351);
    theTypenums.Bind(Reco_DerivedUnit, 352);
    theTypenums.Bind(Reco_DerivedUnitElement, 353);
    theTypenums.Bind(Reco_ItemDefinedTransformation, 354);
    theTypenums.Bind(Reco_PresentedItemRepresentation, 355);
    theTypenums.Bind(Reco_PresentationLayerUsage, 356);

    theTypenums.Bind(Reco_AutoDesignDocumentReference, 366);

    theTypenums.Bind(Reco_Document, 367);
    theTypenums.Bind(Reco_DigitalDocument, 368);
    theTypenums.Bind(Reco_DocumentRelationship, 369);
    theTypenums.Bind(Reco_DocumentType, 370);
    theTypenums.Bind(Reco_DocumentUsageConstraint, 371);
    theTypenums.Bind(Reco_Effectivity, 372);
    theTypenums.Bind(Reco_ProductDefinitionEffectivity, 373);
    theTypenums.Bind(Reco_ProductDefinitionRelationship, 374);

    theTypenums.Bind(Reco_ProductDefinitionWithAssociatedDocuments, 375);
    theTypenums.Bind(Reco_PhysicallyModeledProductDefinition, 376);

    theTypenums.Bind(Reco_ProductDefinitionUsage, 377);
    theTypenums.Bind(Reco_MakeFromUsageOption, 378);
    theTypenums.Bind(Reco_AssemblyComponentUsage, 379);
    theTypenums.Bind(Reco_NextAssemblyUsageOccurrence, 380);
    theTypenums.Bind(Reco_PromissoryUsageOccurrence, 381);
    theTypenums.Bind(Reco_QuantifiedAssemblyComponentUsage, 382);
    theTypenums.Bind(Reco_SpecifiedHigherUsageOccurrence, 383);
    theTypenums.Bind(Reco_AssemblyComponentUsageSubstitute, 384);
    theTypenums.Bind(Reco_SuppliedPartRelationship, 385);
    theTypenums.Bind(Reco_ExternallyDefinedRepresentation, 386);
    theTypenums.Bind(Reco_ShapeRepresentationRelationship, 387);
    theTypenums.Bind(Reco_RepresentationRelationshipWithTransformation, 388);
    theTypenums.Bind(Reco_MaterialDesignation, 390);

    theTypenums.Bind(Reco_ContextDependentShapeRepresentation, 391);

    theTypenums.Bind(Reco_AppliedDateAndTimeAssignment, 392);
    theTypenums.Bind(Reco_AppliedDateAssignment, 393);
    theTypenums.Bind(Reco_AppliedApprovalAssignment, 394);
    theTypenums.Bind(Reco_AppliedGroupAssignment, 395);
    theTypenums.Bind(Reco_AppliedOrganizationAssignment, 396);
    theTypenums.Bind(Reco_AppliedPersonAndOrganizationAssignment, 397);
    theTypenums.Bind(Reco_AppliedPresentedItem, 398);
    theTypenums.Bind(Reco_AppliedSecurityClassificationAssignment, 399);
    theTypenums.Bind(Reco_AppliedDocumentReference, 400);
    theTypenums.Bind(Reco_DocumentFile, 401);
    theTypenums.Bind(Reco_CharacterizedObject, 402);
    theTypenums.Bind(Reco_ExtrudedFaceSolid, 403);
    theTypenums.Bind(Reco_RevolvedFaceSolid, 404);
    theTypenums.Bind(Reco_SweptFaceSolid, 405);

    theTypenums.Bind(Reco_MeasureRepresentationItem, 406);
    theTypenums.Bind(Reco_AreaUnit, 407);
    theTypenums.Bind(Reco_VolumeUnit, 408);

    theTypenums.Bind(Reco_Action, 413);
    theTypenums.Bind(Reco_ActionAssignment, 414);
    theTypenums.Bind(Reco_ActionMethod, 415);
    theTypenums.Bind(Reco_ActionRequestAssignment, 416);
    theTypenums.Bind(Reco_CcDesignApproval, 417);
    theTypenums.Bind(Reco_CcDesignCertification, 418);
    theTypenums.Bind(Reco_CcDesignContract, 419);
    theTypenums.Bind(Reco_CcDesignDateAndTimeAssignment, 420);
    theTypenums.Bind(Reco_CcDesignPersonAndOrganizationAssignment, 421);
    theTypenums.Bind(Reco_CcDesignSecurityClassification, 422);
    theTypenums.Bind(Reco_CcDesignSpecificationReference, 423);
    theTypenums.Bind(Reco_Certification, 424);
    theTypenums.Bind(Reco_CertificationAssignment, 425);
    theTypenums.Bind(Reco_CertificationType, 426);
    theTypenums.Bind(Reco_Change, 427);
    theTypenums.Bind(Reco_ChangeRequest, 428);
    theTypenums.Bind(Reco_ConfigurationDesign, 429);
    theTypenums.Bind(Reco_ConfigurationEffectivity, 430);
    theTypenums.Bind(Reco_Contract, 431);
    theTypenums.Bind(Reco_ContractAssignment, 432);
    theTypenums.Bind(Reco_ContractType, 433);
    theTypenums.Bind(Reco_ProductConcept, 434);
    theTypenums.Bind(Reco_ProductConceptContext, 435);
    theTypenums.Bind(Reco_StartRequest, 436);
    theTypenums.Bind(Reco_StartWork, 437);
    theTypenums.Bind(Reco_VersionedActionRequest, 438);
    theTypenums.Bind(Reco_ProductCategoryRelationship, 439);
    theTypenums.Bind(Reco_ActionRequestSolution, 440);
    theTypenums.Bind(Reco_DraughtingModel, 441);

    theTypenums.Bind(Reco_AngularLocation, 442);
    theTypenums.Bind(Reco_AngularSize, 443);
    theTypenums.Bind(Reco_DimensionalCharacteristicRepresentation, 444);
    theTypenums.Bind(Reco_DimensionalLocation, 445);
    theTypenums.Bind(Reco_DimensionalLocationWithPath, 446);
    theTypenums.Bind(Reco_DimensionalSize, 447);
    theTypenums.Bind(Reco_DimensionalSizeWithPath, 448);
    theTypenums.Bind(Reco_ShapeDimensionRepresentation, 449);

    theTypenums.Bind(Reco_DocumentRepresentationType, 450);
    theTypenums.Bind(Reco_ObjectRole, 451);
    theTypenums.Bind(Reco_RoleAssociation, 452);
    theTypenums.Bind(Reco_IdentificationRole, 453);
    theTypenums.Bind(Reco_IdentificationAssignment, 454);
    theTypenums.Bind(Reco_ExternalIdentificationAssignment, 455);
    theTypenums.Bind(Reco_EffectivityAssignment, 456);
    theTypenums.Bind(Reco_NameAssignment, 457);
    theTypenums.Bind(Reco_GeneralProperty, 458);
    theTypenums.Bind(Reco_Class, 459);
    theTypenums.Bind(Reco_ExternallyDefinedClass, 460);
    theTypenums.Bind(Reco_ExternallyDefinedGeneralProperty, 461);
    theTypenums.Bind(Reco_AppliedExternalIdentificationAssignment, 462);

    theTypenums.Bind(Reco_CompositeShapeAspect, 470);
    theTypenums.Bind(Reco_DerivedShapeAspect, 471);
    theTypenums.Bind(Reco_Extension, 472);
    theTypenums.Bind(Reco_DirectedDimensionalLocation, 473);
    theTypenums.Bind(Reco_LimitsAndFits, 474);
    theTypenums.Bind(Reco_ToleranceValue, 475);
    theTypenums.Bind(Reco_MeasureQualification, 476);
    theTypenums.Bind(Reco_PlusMinusTolerance, 477);
    theTypenums.Bind(Reco_PrecisionQualifier, 478);
    theTypenums.Bind(Reco_TypeQualifier, 479);
    theTypenums.Bind(Reco_QualifiedRepresentationItem, 480);

    theTypenums.Bind(Reco_CompoundRepresentationItem, 482);
    theTypenums.Bind(Reco_ValueRange, 483);
    theTypenums.Bind(Reco_ShapeAspectDerivingRelationship, 484);

    theTypenums.Bind(Reco_CompoundShapeRepresentation, 485);
    theTypenums.Bind(Reco_ConnectedEdgeSet, 486);
    theTypenums.Bind(Reco_ConnectedFaceShapeRepresentation, 487);
    theTypenums.Bind(Reco_EdgeBasedWireframeModel, 488);
    theTypenums.Bind(Reco_EdgeBasedWireframeShapeRepresentation, 489);
    theTypenums.Bind(Reco_FaceBasedSurfaceModel, 490);
    theTypenums.Bind(Reco_NonManifoldSurfaceShapeRepresentation, 491);

    theTypenums.Bind(Reco_OrientedSurface, 492);
    theTypenums.Bind(Reco_Subface, 493);
    theTypenums.Bind(Reco_Subedge, 494);
    theTypenums.Bind(Reco_SeamEdge, 495);
    theTypenums.Bind(Reco_ConnectedFaceSubSet, 496);

    theTypenums.Bind(Reco_EulerAngles, 500);
    theTypenums.Bind(Reco_MassUnit, 501);
    theTypenums.Bind(Reco_ThermodynamicTemperatureUnit, 502);
    theTypenums.Bind(Reco_AnalysisItemWithinRepresentation, 503);
    theTypenums.Bind(Reco_Curve3dElementDescriptor, 504);
    theTypenums.Bind(Reco_CurveElementEndReleasePacket, 505);
    theTypenums.Bind(Reco_CurveElementSectionDefinition, 506);
    theTypenums.Bind(Reco_CurveElementSectionDerivedDefinitions, 507);
    theTypenums.Bind(Reco_ElementDescriptor, 508);
    theTypenums.Bind(Reco_ElementMaterial, 509);
    theTypenums.Bind(Reco_Surface3dElementDescriptor, 510);
    theTypenums.Bind(Reco_SurfaceElementProperty, 511);
    theTypenums.Bind(Reco_SurfaceSection, 512);
    theTypenums.Bind(Reco_SurfaceSectionField, 513);
    theTypenums.Bind(Reco_SurfaceSectionFieldConstant, 514);
    theTypenums.Bind(Reco_SurfaceSectionFieldVarying, 515);
    theTypenums.Bind(Reco_UniformSurfaceSection, 516);
    theTypenums.Bind(Reco_Volume3dElementDescriptor, 517);
    theTypenums.Bind(Reco_AlignedCurve3dElementCoordinateSystem, 518);
    theTypenums.Bind(Reco_ArbitraryVolume3dElementCoordinateSystem, 519);
    theTypenums.Bind(Reco_Curve3dElementProperty, 520);
    theTypenums.Bind(Reco_Curve3dElementRepresentation, 521);
    theTypenums.Bind(Reco_Node, 522);

    theTypenums.Bind(Reco_CurveElementEndOffset, 524);
    theTypenums.Bind(Reco_CurveElementEndRelease, 525);
    theTypenums.Bind(Reco_CurveElementInterval, 526);
    theTypenums.Bind(Reco_CurveElementIntervalConstant, 527);
    theTypenums.Bind(Reco_DummyNode, 528);
    theTypenums.Bind(Reco_CurveElementLocation, 529);
    theTypenums.Bind(Reco_ElementGeometricRelationship, 530);
    theTypenums.Bind(Reco_ElementGroup, 531);
    theTypenums.Bind(Reco_ElementRepresentation, 532);
    theTypenums.Bind(Reco_FeaAreaDensity, 533);
    theTypenums.Bind(Reco_FeaAxis2Placement3d, 534);
    theTypenums.Bind(Reco_FeaGroup, 535);
    theTypenums.Bind(Reco_FeaLinearElasticity, 536);
    theTypenums.Bind(Reco_FeaMassDensity, 537);
    theTypenums.Bind(Reco_FeaMaterialPropertyRepresentation, 538);
    theTypenums.Bind(Reco_FeaMaterialPropertyRepresentationItem, 539);
    theTypenums.Bind(Reco_FeaModel, 540);
    theTypenums.Bind(Reco_FeaModel3d, 541);
    theTypenums.Bind(Reco_FeaMoistureAbsorption, 542);
    theTypenums.Bind(Reco_FeaParametricPoint, 543);
    theTypenums.Bind(Reco_FeaRepresentationItem, 544);
    theTypenums.Bind(Reco_FeaSecantCoefficientOfLinearThermalExpansion, 545);
    theTypenums.Bind(Reco_FeaShellBendingStiffness, 546);
    theTypenums.Bind(Reco_FeaShellMembraneBendingCouplingStiffness, 547);
    theTypenums.Bind(Reco_FeaShellMembraneStiffness, 548);
    theTypenums.Bind(Reco_FeaShellShearStiffness, 549);
    theTypenums.Bind(Reco_GeometricNode, 550);
    theTypenums.Bind(Reco_FeaTangentialCoefficientOfLinearThermalExpansion, 551);
    theTypenums.Bind(Reco_NodeGroup, 552);
    theTypenums.Bind(Reco_NodeRepresentation, 553);
    theTypenums.Bind(Reco_NodeSet, 554);
    theTypenums.Bind(Reco_NodeWithSolutionCoordinateSystem, 555);
    theTypenums.Bind(Reco_NodeWithVector, 556);
    theTypenums.Bind(Reco_ParametricCurve3dElementCoordinateDirection, 557);
    theTypenums.Bind(Reco_ParametricCurve3dElementCoordinateSystem, 558);
    theTypenums.Bind(Reco_ParametricSurface3dElementCoordinateSystem, 559);
    theTypenums.Bind(Reco_Surface3dElementRepresentation, 560);

    theTypenums.Bind(Reco_Volume3dElementRepresentation, 564);
    theTypenums.Bind(Reco_DataEnvironment, 565);
    theTypenums.Bind(Reco_MaterialPropertyRepresentation, 566);
    theTypenums.Bind(Reco_PropertyDefinitionRelationship, 567);
    theTypenums.Bind(Reco_PointRepresentation, 568);
    theTypenums.Bind(Reco_MaterialProperty, 569);
    theTypenums.Bind(Reco_FeaModelDefinition, 570);
    theTypenums.Bind(Reco_FreedomAndCoefficient, 571);
    theTypenums.Bind(Reco_FreedomsList, 572);
    theTypenums.Bind(Reco_ProductDefinitionFormationRelationship, 573);

    theTypenums.Bind(Reco_NodeDefinition, 575);
    theTypenums.Bind(Reco_StructuralResponseProperty, 576);
    theTypenums.Bind(Reco_StructuralResponsePropertyDefinitionRepresentation, 577);
    theTypenums.Bind(Reco_AlignedSurface3dElementCoordinateSystem, 579);
    theTypenums.Bind(Reco_ConstantSurface3dElementCoordinateSystem, 580);
    theTypenums.Bind(Reco_CurveElementIntervalLinearlyVarying, 581);
    theTypenums.Bind(Reco_FeaCurveSectionGeometricRelationship, 582);
    theTypenums.Bind(Reco_FeaSurfaceSectionGeometricRelationship, 583);

    theTypenums.Bind(Reco_DocumentProductAssociation, 600);
    theTypenums.Bind(Reco_DocumentProductEquivalence, 601);

    theTypenums.Bind(Reco_CylindricityTolerance, 609);
    theTypenums.Bind(Reco_ShapeRepresentationWithParameters, 610);
    theTypenums.Bind(Reco_AngularityTolerance, 611);
    theTypenums.Bind(Reco_ConcentricityTolerance, 612);
    theTypenums.Bind(Reco_CircularRunoutTolerance, 613);
    theTypenums.Bind(Reco_CoaxialityTolerance, 614);
    theTypenums.Bind(Reco_FlatnessTolerance, 615);
    theTypenums.Bind(Reco_LineProfileTolerance, 616);
    theTypenums.Bind(Reco_ParallelismTolerance, 617);
    theTypenums.Bind(Reco_PerpendicularityTolerance, 618);
    theTypenums.Bind(Reco_PositionTolerance, 619);
    theTypenums.Bind(Reco_RoundnessTolerance, 620);
    theTypenums.Bind(Reco_StraightnessTolerance, 621);
    theTypenums.Bind(Reco_SurfaceProfileTolerance, 622);
    theTypenums.Bind(Reco_SymmetryTolerance, 623);
    theTypenums.Bind(Reco_TotalRunoutTolerance, 624);
    theTypenums.Bind(Reco_GeometricTolerance, 625);
    theTypenums.Bind(Reco_GeometricToleranceRelationship, 626);
    theTypenums.Bind(Reco_GeometricToleranceWithDatumReference, 627);
    theTypenums.Bind(Reco_ModifiedGeometricTolerance, 628);
    theTypenums.Bind(Reco_Datum, 629);
    theTypenums.Bind(Reco_DatumFeature, 630);
    theTypenums.Bind(Reco_DatumReference, 631);
    theTypenums.Bind(Reco_CommonDatum, 632);
    theTypenums.Bind(Reco_DatumTarget, 633);
    theTypenums.Bind(Reco_PlacedDatumTargetFeature, 634);

    theTypenums.Bind(Reco_MassMeasureWithUnit, 651);

    theTypenums.Bind(Reco_Apex, 660);
    theTypenums.Bind(Reco_CentreOfSymmetry, 661);
    theTypenums.Bind(Reco_GeometricAlignment, 662);
    theTypenums.Bind(Reco_PerpendicularTo, 663);
    theTypenums.Bind(Reco_Tangent, 664);
    theTypenums.Bind(Reco_ParallelOffset, 665);
    theTypenums.Bind(Reco_GeometricItemSpecificUsage, 666);
    theTypenums.Bind(Reco_IdAttribute, 667);
    theTypenums.Bind(Reco_ItemIdentifiedRepresentationUsage, 668);
    theTypenums.Bind(Reco_AllAroundShapeAspect, 669);
    theTypenums.Bind(Reco_BetweenShapeAspect, 670);
    theTypenums.Bind(Reco_CompositeGroupShapeAspect, 671);
    theTypenums.Bind(Reco_ContinuosShapeAspect, 672);
    theTypenums.Bind(Reco_GeometricToleranceWithDefinedAreaUnit, 673);
    theTypenums.Bind(Reco_GeometricToleranceWithDefinedUnit, 674);
    theTypenums.Bind(Reco_GeometricToleranceWithMaximumTolerance, 675);
    theTypenums.Bind(Reco_GeometricToleranceWithModifiers, 676);
    theTypenums.Bind(Reco_UnequallyDisposedGeometricTolerance, 677);
    theTypenums.Bind(Reco_NonUniformZoneDefinition, 678);
    theTypenums.Bind(Reco_ProjectedZoneDefinition, 679);
    theTypenums.Bind(Reco_RunoutZoneDefinition, 680);
    theTypenums.Bind(Reco_RunoutZoneOrientation, 681);
    theTypenums.Bind(Reco_ToleranceZone, 682);
    theTypenums.Bind(Reco_ToleranceZoneDefinition, 683);
    theTypenums.Bind(Reco_ToleranceZoneForm, 684);
    theTypenums.Bind(Reco_ValueFormatTypeQualifier, 685);
    theTypenums.Bind(Reco_DatumReferenceCompartment, 686);
    theTypenums.Bind(Reco_DatumReferenceElement, 687);
    theTypenums.Bind(Reco_DatumReferenceModifierWithValue, 688);
    theTypenums.Bind(Reco_DatumSystem, 689);
    theTypenums.Bind(Reco_GeneralDatumReference, 690);
    theTypenums.Bind(Reco_IntegerRepresentationItem, 700);
    theTypenums.Bind(Reco_ValueRepresentationItem, 701);
    theTypenums.Bind(Reco_FeatureForDatumTargetRelationship, 702);
    theTypenums.Bind(Reco_DraughtingModelItemAssociation, 703);
    theTypenums.Bind(Reco_AnnotationPlane, 704);

    theTypenums.Bind(Reco_TessellatedAnnotationOccurrence, 707);
    theTypenums.Bind(Reco_TessellatedGeometricSet, 709);

    theTypenums.Bind(Reco_TessellatedCurveSet, 710);
    theTypenums.Bind(Reco_CoordinatesList, 711);
    theTypenums.Bind(Reco_ConstructiveGeometryRepresentation, 712);
    theTypenums.Bind(Reco_ConstructiveGeometryRepresentationRelationship, 713);
    theTypenums.Bind(Reco_CharacterizedRepresentation, 714);
    theTypenums.Bind(Reco_CameraModelD3MultiClipping, 716);
    theTypenums.Bind(Reco_CameraModelD3MultiClippingIntersection, 717);
    theTypenums.Bind(Reco_CameraModelD3MultiClippingUnion, 718);

    theTypenums.Bind(Reco_SurfaceStyleTransparent, 720);
    theTypenums.Bind(Reco_SurfaceStyleReflectanceAmbient, 721);
    theTypenums.Bind(Reco_SurfaceStyleRendering, 722);
    theTypenums.Bind(Reco_SurfaceStyleRenderingWithProperties, 723);

    theTypenums.Bind(Reco_RepresentationContextReference, 724);
    theTypenums.Bind(Reco_RepresentationReference, 725);
    theTypenums.Bind(Reco_SuParameters, 726);
    theTypenums.Bind(Reco_RotationAboutDirection, 727);
    theTypenums.Bind(Reco_KinematicJoint, 728);
    theTypenums.Bind(Reco_ActuatedKinematicPair, 729);
    theTypenums.Bind(Reco_ContextDependentKinematicLinkRepresentation, 730);
    theTypenums.Bind(Reco_CylindricalPair, 731);
    theTypenums.Bind(Reco_CylindricalPairValue, 732);
    theTypenums.Bind(Reco_CylindricalPairWithRange, 733);
    theTypenums.Bind(Reco_FullyConstrainedPair, 734);
    theTypenums.Bind(Reco_GearPair, 735);
    theTypenums.Bind(Reco_GearPairValue, 736);
    theTypenums.Bind(Reco_GearPairWithRange, 737);
    theTypenums.Bind(Reco_HomokineticPair, 738);
    theTypenums.Bind(Reco_KinematicLink, 739);
    theTypenums.Bind(Reco_KinematicLinkRepresentationAssociation, 740);
    theTypenums.Bind(Reco_KinematicPropertyMechanismRepresentation, 741);
    theTypenums.Bind(Reco_KinematicTopologyStructure, 742);
    theTypenums.Bind(Reco_LowOrderKinematicPair, 743);
    theTypenums.Bind(Reco_LowOrderKinematicPairValue, 744);
    theTypenums.Bind(Reco_LowOrderKinematicPairWithRange, 745);
    theTypenums.Bind(Reco_MechanismRepresentation, 746);
    theTypenums.Bind(Reco_OrientedJoint, 747);
    theTypenums.Bind(Reco_PlanarCurvePair, 748);
    theTypenums.Bind(Reco_PlanarCurvePairRange, 749);
    theTypenums.Bind(Reco_PlanarPair, 750);
    theTypenums.Bind(Reco_PlanarPairValue, 751);
    theTypenums.Bind(Reco_PlanarPairWithRange, 752);
    theTypenums.Bind(Reco_PointOnPlanarCurvePair, 753);
    theTypenums.Bind(Reco_PointOnPlanarCurvePairValue, 754);
    theTypenums.Bind(Reco_PointOnPlanarCurvePairWithRange, 755);
    theTypenums.Bind(Reco_PointOnSurfacePair, 756);
    theTypenums.Bind(Reco_PointOnSurfacePairValue, 757);
    theTypenums.Bind(Reco_PointOnSurfacePairWithRange, 758);
    theTypenums.Bind(Reco_PrismaticPair, 759);
    theTypenums.Bind(Reco_PrismaticPairValue, 760);
    theTypenums.Bind(Reco_PrismaticPairWithRange, 761);
    theTypenums.Bind(Reco_ProductDefinitionKinematics, 762);
    theTypenums.Bind(Reco_ProductDefinitionRelationshipKinematics, 763);
    theTypenums.Bind(Reco_RackAndPinionPair, 764);
    theTypenums.Bind(Reco_RackAndPinionPairValue, 765);
    theTypenums.Bind(Reco_RackAndPinionPairWithRange, 766);
    theTypenums.Bind(Reco_RevolutePair, 767);
    theTypenums.Bind(Reco_RevolutePairValue, 768);
    theTypenums.Bind(Reco_RevolutePairWithRange, 769);
    theTypenums.Bind(Reco_RollingCurvePair, 770);
    theTypenums.Bind(Reco_RollingCurvePairValue, 771);
    theTypenums.Bind(Reco_RollingSurfacePair, 772);
    theTypenums.Bind(Reco_RollingSurfacePairValue, 773);
    theTypenums.Bind(Reco_ScrewPair, 774);
    theTypenums.Bind(Reco_ScrewPairValue, 775);
    theTypenums.Bind(Reco_ScrewPairWithRange, 776);
    theTypenums.Bind(Reco_SlidingCurvePair, 777);
    theTypenums.Bind(Reco_SlidingCurvePairValue, 778);
    theTypenums.Bind(Reco_SlidingSurfacePair, 779);
    theTypenums.Bind(Reco_SlidingSurfacePairValue, 780);
    theTypenums.Bind(Reco_SphericalPair, 781);
    theTypenums.Bind(Reco_SphericalPairValue, 782);
    theTypenums.Bind(Reco_SphericalPairWithPin, 783);
    theTypenums.Bind(Reco_SphericalPairWithPinAndRange, 784);
    theTypenums.Bind(Reco_SphericalPairWithRange, 785);
    theTypenums.Bind(Reco_SurfacePairWithRange, 786);
    theTypenums.Bind(Reco_UnconstrainedPair, 787);
    theTypenums.Bind(Reco_UnconstrainedPairValue, 788);
    theTypenums.Bind(Reco_UniversalPair, 789);
    theTypenums.Bind(Reco_UniversalPairValue, 790);
    theTypenums.Bind(Reco_UniversalPairWithRange, 791);
    theTypenums.Bind(Reco_PairRepresentationRelationship, 792);
    theTypenums.Bind(Reco_RigidLinkRepresentation, 793);
    theTypenums.Bind(Reco_KinematicTopologyDirectedStructure, 794);
    theTypenums.Bind(Reco_KinematicTopologyNetworkStructure, 795);
    theTypenums.Bind(Reco_LinearFlexibleAndPinionPair, 796);
    theTypenums.Bind(Reco_LinearFlexibleAndPlanarCurvePair, 797);
    theTypenums.Bind(Reco_LinearFlexibleLinkRepresentation, 798);
    theTypenums.Bind(Reco_KinematicPair, 799);
    theTypenums.Bind(Reco_MechanismStateRepresentation, 801);
    theTypenums.Bind(Reco_RepositionedTessellatedItem, 803);
    theTypenums.Bind(Reco_TessellatedConnectingEdge, 804);
    theTypenums.Bind(Reco_TessellatedEdge, 805);
    theTypenums.Bind(Reco_TessellatedPointSet, 806);
    theTypenums.Bind(Reco_TessellatedShapeRepresentation, 807);
    theTypenums.Bind(Reco_TessellatedShapeRepresentationWithAccuracyParameters, 808);
    theTypenums.Bind(Reco_TessellatedShell, 809);
    theTypenums.Bind(Reco_TessellatedSolid, 810);
    theTypenums.Bind(Reco_TessellatedStructuredItem, 811);
    theTypenums.Bind(Reco_TessellatedVertex, 812);
    theTypenums.Bind(Reco_TessellatedWire, 813);
    theTypenums.Bind(Reco_TriangulatedFace, 814);
    theTypenums.Bind(Reco_ComplexTriangulatedFace, 815);
    theTypenums.Bind(Reco_ComplexTriangulatedSurfaceSet, 816);
    theTypenums.Bind(Reco_CubicBezierTessellatedEdge, 817);
    theTypenums.Bind(Reco_CubicBezierTriangulatedFace, 818);
    theTypenums.Bind(Reco_TriangulatedSurfaceSet, 819);
    theTypenums.Bind(Reco_GeneralPropertyAssociation, 820);
    theTypenums.Bind(Reco_GeneralPropertyRelationship, 821);
    theTypenums.Bind(Reco_BooleanRepresentationItem, 822);
    theTypenums.Bind(Reco_RealRepresentationItem, 823);
    theTypenums.Bind(Reco_MechanicalDesignAndDraughtingRelationship, 824);
  }

  static void initializeTypeshor(StringViewDataMap& theTypeshor)
  {
    theTypeshor.Clear(THE_INC_ALLOCATOR);
    theTypeshor.ReSize(528);

    theTypeshor.Bind(s_ADDRSS, 1);
    theTypeshor.Bind(s_ABSR, 2);
    theTypeshor.Bind(s_ADVFC, 3);
    theTypeshor.Bind(s_ANCROC, 4);
    theTypeshor.Bind(s_ANFLAR, 5);
    theTypeshor.Bind(s_AFAO, 6);
    theTypeshor.Bind(s_ANNOCC, 7);
    theTypeshor.Bind(s_ANSBOC, 8);
    theTypeshor.Bind(s_ANNSYM, 9);
    theTypeshor.Bind(s_ANSYOC, 10);
    theTypeshor.Bind(s_ANNTXT, 11);
    theTypeshor.Bind(s_ANTXOC, 12);

    theTypeshor.Bind(s_APPCNT, 13);
    theTypeshor.Bind(s_APCNEL, 14);
    theTypeshor.Bind(s_APPRDF, 15);
    theTypeshor.Bind(s_APPRVL, 16);
    theTypeshor.Bind(s_APPASS, 17);
    theTypeshor.Bind(s_APDTTM, 348);
    theTypeshor.Bind(s_APPROR, 18);
    theTypeshor.Bind(s_APPRLT, 19);
    theTypeshor.Bind(s_APPRL, 20);
    theTypeshor.Bind(s_APPSTT, 21);
    theTypeshor.Bind(s_ARINST, 22);

    theTypeshor.Bind(s_ASCMUS, 379);
    theTypeshor.Bind(s_ACUS, 384);
    theTypeshor.Bind(s_AX1PLC, 35);
    theTypeshor.Bind(s_A2PL2D, 36);
    theTypeshor.Bind(s_A2PL3D, 37);
    theTypeshor.Bind(s_BZRCRV, 43);
    theTypeshor.Bind(s_BZRSRF, 44);
    theTypeshor.Bind(s_BLNRSL, 46);
    theTypeshor.Bind(s_BNDCR, 47);
    theTypeshor.Bind(s_BNDCRV, 48);
    theTypeshor.Bind(s_BNDSRF, 49);
    theTypeshor.Bind(s_BRWTVD, 52);
    theTypeshor.Bind(s_BSPCR, 38);
    theTypeshor.Bind(s_BSCWK, 39);
    theTypeshor.Bind(s_BSPSR, 40);
    theTypeshor.Bind(s_BSSWK, 41);
    theTypeshor.Bind(s_BXDMN, 50);
    theTypeshor.Bind(s_BXHLSP, 51);
    theTypeshor.Bind(s_CLNDT, 53);
    theTypeshor.Bind(s_CMRIMG, 54);
    theTypeshor.Bind(s_CMRMDL, 55);
    theTypeshor.Bind(s_CMMDD3, 57);
    theTypeshor.Bind(s_CMRUSG, 58);
    theTypeshor.Bind(s_CRTPNT, 59);
    theTypeshor.Bind(s_CRTROP, 60);

    theTypeshor.Bind(s_CTO3, 61);

    theTypeshor.Bind(s_CLSSHL, 63);
    theTypeshor.Bind(s_CLRRGB, 65);
    theTypeshor.Bind(s_CLRSPC, 66);
    theTypeshor.Bind(s_CMPCRV, 67);
    theTypeshor.Bind(s_CCOS, 68);
    theTypeshor.Bind(s_CMCRSG, 69);

    theTypeshor.Bind(s_CMPTXT, 70);
    theTypeshor.Bind(s_CTWAC, 71);
    theTypeshor.Bind(s_CTWBB, 72);
    theTypeshor.Bind(s_CTWE, 73);
    theTypeshor.Bind(s_CNCSRF, 75);

    theTypeshor.Bind(s_CNFCST, 76);
    theTypeshor.Bind(s_CNDPIN, 77);
    theTypeshor.Bind(s_CDORSI, 78);
    theTypeshor.Bind(s_CDSR, 391);

    theTypeshor.Bind(s_CNBSUN, 79);
    theTypeshor.Bind(s_CUTO, 80);
    theTypeshor.Bind(s_CSSHRP, 82);
    theTypeshor.Bind(s_CSGSLD, 83);

    theTypeshor.Bind(s_CRBNSR, 85);
    theTypeshor.Bind(s_CRVRPL, 86);
    theTypeshor.Bind(s_CRVSTY, 87);
    theTypeshor.Bind(s_CRSTFN, 88);
    theTypeshor.Bind(s_CSFP, 89);
    theTypeshor.Bind(s_CYLSRF, 90);

    theTypeshor.Bind(s_DTANTM, 92);
    theTypeshor.Bind(s_DATA, 93);
    theTypeshor.Bind(s_DTASS, 94);
    theTypeshor.Bind(s_DTRL, 95);
    theTypeshor.Bind(s_DTTMRL, 96);
    theTypeshor.Bind(s_DFNSYM, 97);
    theTypeshor.Bind(s_DFNRPR, 98);
    theTypeshor.Bind(s_DGNPCR, 99);
    theTypeshor.Bind(s_DGTRSR, 100);
    theTypeshor.Bind(s_DSRPIT, 101);
    theTypeshor.Bind(s_DMNCRV, 102);
    theTypeshor.Bind(s_DMCRTR, 103);
    theTypeshor.Bind(s_DSGCNT, 340);

    theTypeshor.Bind(s_DMNEXP, 104);

    theTypeshor.Bind(s_DRCTN, 105);
    theTypeshor.Bind(s_DRANOC, 106);
    theTypeshor.Bind(s_DRGCLL, 107);
    theTypeshor.Bind(s_DPDC, 108);
    theTypeshor.Bind(s_DPDCF, 109);
    theTypeshor.Bind(s_DRSBRP, 110);
    theTypeshor.Bind(s_DRSYRP, 111);
    theTypeshor.Bind(s_DTLWD, 112);
    theTypeshor.Bind(s_DRWDFN, 113);
    theTypeshor.Bind(s_DRWRVS, 114);
    theTypeshor.Bind(s_DCMNT, 367);

    theTypeshor.Bind(s_DCMRLT, 369);
    theTypeshor.Bind(s_DCMTYP, 370);
    theTypeshor.Bind(s_DCUSCN, 371);

    theTypeshor.Bind(s_EDGCRV, 116);
    theTypeshor.Bind(s_EDGLP, 117);
    theTypeshor.Bind(s_EFFCTV, 372);
    theTypeshor.Bind(s_ELMSRF, 118);
    theTypeshor.Bind(s_ELLPS, 119);
    theTypeshor.Bind(s_EVDGPC, 120);
    theTypeshor.Bind(s_EXTSRC, 121);
    theTypeshor.Bind(s_EDCF, 122);
    theTypeshor.Bind(s_EDHS, 123);
    theTypeshor.Bind(s_EXDFIT, 124);
    theTypeshor.Bind(s_EXDFSY, 125);
    theTypeshor.Bind(s_EDTF, 126);
    theTypeshor.Bind(s_EDTS, 127);
    theTypeshor.Bind(s_EXARSL, 128);

    theTypeshor.Bind(s_FCBND, 131);
    theTypeshor.Bind(s_FCOTBN, 132);
    theTypeshor.Bind(s_FCSRF, 133);
    theTypeshor.Bind(s_FCTBR, 134);
    theTypeshor.Bind(s_FBSR, 135);
    theTypeshor.Bind(s_FLARST, 136);
    theTypeshor.Bind(s_FASC, 137);
    theTypeshor.Bind(s_FASH, 138);
    theTypeshor.Bind(s_FASTSW, 139);
    theTypeshor.Bind(s_FAST, 140);
    theTypeshor.Bind(s_FNDFTR, 141);
    theTypeshor.Bind(s_GBSSR, 146);
    theTypeshor.Bind(s_GBWSR, 147);
    theTypeshor.Bind(s_GMCRST, 142);
    theTypeshor.Bind(s_GMRPCN, 143);
    theTypeshor.Bind(s_GMRPIT, 144);
    theTypeshor.Bind(s_GMTST, 145);
    theTypeshor.Bind(s_GC, 148);
    theTypeshor.Bind(s_GUAC, 149);
    theTypeshor.Bind(s_GRPASS, 151);
    theTypeshor.Bind(s_GRPRLT, 152);
    theTypeshor.Bind(s_HLSPSL, 153);
    theTypeshor.Bind(s_HYPRBL, 154);
    theTypeshor.Bind(s_INTCRV, 155);
    theTypeshor.Bind(s_INVSBL, 156);
    theTypeshor.Bind(s_ITDFTR, 354);
    theTypeshor.Bind(s_LMWU, 157);
    theTypeshor.Bind(s_LNGUNT, 158);

    theTypeshor.Bind(s_LCLTM, 160);

    theTypeshor.Bind(s_MNSLBR, 162);
    theTypeshor.Bind(s_MSSR, 163);
    theTypeshor.Bind(s_MPPITM, 164);
    theTypeshor.Bind(s_MDGPA, 166);
    theTypeshor.Bind(s_MDGPR, 167);

    theTypeshor.Bind(s_MSWTUN, 165);
    theTypeshor.Bind(s_MCHCNT, 339);
    theTypeshor.Bind(s_NMDUNT, 169);
    theTypeshor.Bind(s_NAUO, 380);

    theTypeshor.Bind(s_OFCR3D, 171);
    theTypeshor.Bind(s_OFFSRF, 172);
    theTypeshor.Bind(s_ODRF, 173);
    theTypeshor.Bind(s_OPNSHL, 174);
    theTypeshor.Bind(s_ORDDT, 175);
    theTypeshor.Bind(s_ORGNZT, 176);
    theTypeshor.Bind(s_ORGASS, 177);
    theTypeshor.Bind(s_ORGRL, 178);
    theTypeshor.Bind(s_ORGADD, 179);

    theTypeshor.Bind(s_ORCLSH, 180);
    theTypeshor.Bind(s_ORNEDG, 181);
    theTypeshor.Bind(s_ORNFC, 182);
    theTypeshor.Bind(s_OROPSH, 183);
    theTypeshor.Bind(s_ORNPTH, 184);
    theTypeshor.Bind(s_OTBNCR, 185);
    theTypeshor.Bind(s_ORSI, 186);
    theTypeshor.Bind(s_PRBL, 187);
    theTypeshor.Bind(s_PRRPCN, 188);

    theTypeshor.Bind(s_PRANOR, 192);
    theTypeshor.Bind(s_PAOA, 193);
    theTypeshor.Bind(s_PAOR, 194);
    theTypeshor.Bind(s_PRSADD, 195);
    theTypeshor.Bind(s_PLCMNT, 196);
    theTypeshor.Bind(s_PLNBX, 197);
    theTypeshor.Bind(s_PLNEXT, 198);

    theTypeshor.Bind(s_PAMWU, 200);
    theTypeshor.Bind(s_PLANUN, 201);

    theTypeshor.Bind(s_PNONCR, 203);
    theTypeshor.Bind(s_PNONSR, 204);
    theTypeshor.Bind(s_PNTRPL, 205);
    theTypeshor.Bind(s_PNTSTY, 206);
    theTypeshor.Bind(s_PLYLP, 207);
    theTypeshor.Bind(s_PLYLN, 208);
    theTypeshor.Bind(s_PRDFCL, 209);
    theTypeshor.Bind(s_PDCF, 210);
    theTypeshor.Bind(s_PRDFIT, 211);
    theTypeshor.Bind(s_PRDFSY, 212);
    theTypeshor.Bind(s_PDTF, 213);
    theTypeshor.Bind(s_PRSAR, 214);
    theTypeshor.Bind(s_PRLYAS, 215);
    theTypeshor.Bind(s_PRSRPR, 216);
    theTypeshor.Bind(s_PRSST, 217);
    theTypeshor.Bind(s_PRSSZ, 218);
    theTypeshor.Bind(s_PRSTAS, 219);
    theTypeshor.Bind(s_PSBC, 220);
    theTypeshor.Bind(s_PRSVW, 221);
    theTypeshor.Bind(s_PRSITM, 222);
    theTypeshor.Bind(s_PRDCT, 223);
    theTypeshor.Bind(s_PRDCTG, 224);

    theTypeshor.Bind(s_PRDCNT, 225);
    theTypeshor.Bind(s_PRDDFN, 227);
    theTypeshor.Bind(s_PRDFCN, 228);
    theTypeshor.Bind(s_PRDFEF, 373);
    theTypeshor.Bind(s_PRDFFR, 229);
    theTypeshor.Bind(s_PDFWSS, 230);
    theTypeshor.Bind(s_PRDFRL, 374);
    theTypeshor.Bind(s_PRDFSH, 231);
    theTypeshor.Bind(s_PRDFUS, 377);
    theTypeshor.Bind(s_PDWAD, 375);
    theTypeshor.Bind(s_PRPC, 232);
    theTypeshor.Bind(s_PRUSOC, 381);
    theTypeshor.Bind(s_PRPDFN, 234);
    theTypeshor.Bind(s_PRDFRP, 235);
    theTypeshor.Bind(s_QACU, 382);
    theTypeshor.Bind(s_QSUNCR, 236);
    theTypeshor.Bind(s_QSUNSR, 237);
    theTypeshor.Bind(s_RMWU, 238);
    theTypeshor.Bind(s_RBSC, 239);
    theTypeshor.Bind(s_RBSS, 240);
    theTypeshor.Bind(s_RCCMSR, 241);
    theTypeshor.Bind(s_RCTRSR, 242);
    theTypeshor.Bind(s_RPITGR, 243);
    theTypeshor.Bind(s_RCCS, 244);
    theTypeshor.Bind(s_RPRSNT, 245);
    theTypeshor.Bind(s_RPRCNT, 246);
    theTypeshor.Bind(s_RPRITM, 247);
    theTypeshor.Bind(s_RPRMP, 248);
    theTypeshor.Bind(s_RPRRLT, 249);
    theTypeshor.Bind(s_RVARSL, 250);
    theTypeshor.Bind(s_RGANWD, 251);
    theTypeshor.Bind(s_RGCRCN, 252);
    theTypeshor.Bind(s_RGCRCY, 253);
    theTypeshor.Bind(s_RRWT, 388);
    theTypeshor.Bind(s_SMCRV, 254);
    theTypeshor.Bind(s_SCRCLS, 255);
    theTypeshor.Bind(s_SCCLAS, 256);
    theTypeshor.Bind(s_SCCLLV, 257);

    theTypeshor.Bind(s_SHPASP, 258);
    theTypeshor.Bind(s_SHASRL, 259);
    theTypeshor.Bind(s_SHDFRP, 261);
    theTypeshor.Bind(s_SHPRPR, 262);
    theTypeshor.Bind(s_SHRPRL, 387);
    theTypeshor.Bind(s_SBSM, 263);

    theTypeshor.Bind(s_SUNT, 264);
    theTypeshor.Bind(s_SAMWU, 265);
    theTypeshor.Bind(s_SLANUN, 336);
    theTypeshor.Bind(s_SLDMDL, 266);
    theTypeshor.Bind(s_SLDRPL, 267);
    theTypeshor.Bind(s_SHUO, 383);
    theTypeshor.Bind(s_SPHSRF, 269);
    theTypeshor.Bind(s_STYITM, 270);

    theTypeshor.Bind(s_SPPRRL, 385);
    theTypeshor.Bind(s_SRFC, 271);
    theTypeshor.Bind(s_SRFCRV, 272);
    theTypeshor.Bind(s_SL, 273);
    theTypeshor.Bind(s_SROFRV, 274);
    theTypeshor.Bind(s_SRFPTC, 275);
    theTypeshor.Bind(s_SRFRPL, 276);
    theTypeshor.Bind(s_SRSDST, 277);
    theTypeshor.Bind(s_SRSTBN, 278);
    theTypeshor.Bind(s_SSCG, 279);
    theTypeshor.Bind(s_SSFA, 280);
    theTypeshor.Bind(s_SSPL, 281);
    theTypeshor.Bind(s_SSSC, 282);
    theTypeshor.Bind(s_SRSTSL, 283);
    theTypeshor.Bind(s_SRSTUS, 284);
    theTypeshor.Bind(s_SWARSL, 285);
    theTypeshor.Bind(s_SWPSRF, 286);
    theTypeshor.Bind(s_SYMCLR, 287);
    theTypeshor.Bind(s_SYMRPR, 288);
    theTypeshor.Bind(s_SYRPMP, 289);
    theTypeshor.Bind(s_SYMSTY, 290);
    theTypeshor.Bind(s_SYMTRG, 291);
    theTypeshor.Bind(s_TRMSYM, 294);
    theTypeshor.Bind(s_TXTLTR, 295);
    theTypeshor.Bind(s_TLWAC, 296);
    theTypeshor.Bind(s_TLWBB, 297);
    theTypeshor.Bind(s_TLWD, 298);
    theTypeshor.Bind(s_TLWE, 299);
    theTypeshor.Bind(s_TXTSTY, 300);
    theTypeshor.Bind(s_TSFDF, 301);
    theTypeshor.Bind(s_TSWBC, 302);
    theTypeshor.Bind(s_TSWM, 303);
    theTypeshor.Bind(s_TPRPIT, 304);
    theTypeshor.Bind(s_TRDSRF, 305);
    theTypeshor.Bind(s_TRMCRV, 308);
    theTypeshor.Bind(s_TDRF, 309);
    theTypeshor.Bind(s_UMWU, 310);
    theTypeshor.Bind(s_UNFCRV, 311);
    theTypeshor.Bind(s_UNFSRF, 312);

    theTypeshor.Bind(s_VRTLP, 315);
    theTypeshor.Bind(s_VRTPNT, 316);

    theTypeshor.Bind(s_VWVLM, 317);
    theTypeshor.Bind(s_WOYADD, 318);
    theTypeshor.Bind(s_TMWU, 341);
    theTypeshor.Bind(s_RTUNT, 342);
    theTypeshor.Bind(s_TMUNT, 343);
    theTypeshor.Bind(s_CI3WS, 350);
    theTypeshor.Bind(s_CTO2, 351);
    theTypeshor.Bind(s_DRVUNT, 352);
    theTypeshor.Bind(s_DRUNEL, 353);
    theTypeshor.Bind(s_PRITRP, 355);
    theTypeshor.Bind(s_MFUO, 378);

    theTypeshor.Bind(s_MTRDSG, 390);
    theTypeshor.Bind(s_ADATA, 392);
    theTypeshor.Bind(s_APDTAS, 393);
    theTypeshor.Bind(s_APGRAS, 395);
    theTypeshor.Bind(s_APORAS, 396);
    theTypeshor.Bind(s_APAOA, 397);
    theTypeshor.Bind(s_APPRIT, 398);
    theTypeshor.Bind(s_ASCA, 399);
    theTypeshor.Bind(s_APDCRF, 400);
    theTypeshor.Bind(s_DCMFL, 401);
    theTypeshor.Bind(s_CHROBJ, 402);
    theTypeshor.Bind(s_EXFCSL, 403);
    theTypeshor.Bind(s_RVFCSL, 404);
    theTypeshor.Bind(s_SWFCSL, 405);

    theTypeshor.Bind(s_MSRPIT, 406);
    theTypeshor.Bind(s_ARUNT, 407);
    theTypeshor.Bind(s_VLMUNT, 408);

    theTypeshor.Bind(s_ACTION, 413);
    theTypeshor.Bind(s_ACTASS, 414);
    theTypeshor.Bind(s_ACTMTH, 415);
    theTypeshor.Bind(s_ACRQAS, 416);
    theTypeshor.Bind(s_CCDSAP, 417);
    theTypeshor.Bind(s_CCDSCR, 418);
    theTypeshor.Bind(s_CCDSCN, 419);
    theTypeshor.Bind(s_CDDATA, 420);
    theTypeshor.Bind(s_CDPAOA, 421);
    theTypeshor.Bind(s_CDSC, 422);
    theTypeshor.Bind(s_CDS, 423);
    theTypeshor.Bind(s_CRTFCT, 424);
    theTypeshor.Bind(s_CRTASS, 425);
    theTypeshor.Bind(s_CRTTYP, 426);
    theTypeshor.Bind(s_CHANGE, 427);
    theTypeshor.Bind(s_CHNRQS, 428);
    theTypeshor.Bind(s_CNFDSG, 429);
    theTypeshor.Bind(s_CNFEFF, 430);
    theTypeshor.Bind(s_CNTRCT, 431);
    theTypeshor.Bind(s_CNTASS, 432);
    theTypeshor.Bind(s_CNTTYP, 433);
    theTypeshor.Bind(s_PRDCNC, 434);
    theTypeshor.Bind(s_PRCNCN, 435);
    theTypeshor.Bind(s_STRRQS, 436);
    theTypeshor.Bind(s_STRWRK, 437);
    theTypeshor.Bind(s_VRACRQ, 438);
    theTypeshor.Bind(s_PRCTRL, 439);
    theTypeshor.Bind(s_ACRQSL, 440);
    theTypeshor.Bind(s_DRGMDL, 441);
    theTypeshor.Bind(s_ANGLCT, 442);
    theTypeshor.Bind(s_ANGSZ, 443);
    theTypeshor.Bind(s_DMCHRP, 444);
    theTypeshor.Bind(s_DMNLCT, 445);
    theTypeshor.Bind(s_DLWP, 446);
    theTypeshor.Bind(s_DMNSZ, 447);
    theTypeshor.Bind(s_DSWP, 448);
    theTypeshor.Bind(s_SHDMRP, 449);
    theTypeshor.Bind(s_DCRPTY, 450);
    theTypeshor.Bind(s_OBJRL, 451);
    theTypeshor.Bind(s_RLASS, 452);
    theTypeshor.Bind(s_IDNRL, 453);
    theTypeshor.Bind(s_IDNASS, 454);
    theTypeshor.Bind(s_EXIDAS, 455);
    theTypeshor.Bind(s_EFFASS, 456);
    theTypeshor.Bind(s_NMASS, 457);
    theTypeshor.Bind(s_GNRPRP, 458);
    theTypeshor.Bind(s_EDGP, 461);
    theTypeshor.Bind(s_AEIA, 462);
    theTypeshor.Bind(s_CMSHAS, 470);
    theTypeshor.Bind(s_DRSHAS, 471);
    theTypeshor.Bind(s_EXTNSN, 472);
    theTypeshor.Bind(s_DRDMLC, 473);
    theTypeshor.Bind(s_LMANFT, 474);
    theTypeshor.Bind(s_TLRVL, 475);
    theTypeshor.Bind(s_MSRQLF, 476);
    theTypeshor.Bind(s_PLMNTL, 477);
    theTypeshor.Bind(s_PRCQLF, 478);
    theTypeshor.Bind(s_TYPQLF, 479);
    theTypeshor.Bind(s_QLRPIT, 480);
    theTypeshor.Bind(s_CMRPIT, 482);
    theTypeshor.Bind(s_CMRPIT, 483);
    theTypeshor.Bind(s_CMS0, 485);
    theTypeshor.Bind(s_CNEDST, 486);
    theTypeshor.Bind(s_EBWM, 488);
    theTypeshor.Bind(s_EBWSR, 489);
    theTypeshor.Bind(s_NMSSR, 491);
    theTypeshor.Bind(s_ORNSRF, 492);
    theTypeshor.Bind(s_SBFC, 493);
    theTypeshor.Bind(s_SBDG, 494);
    theTypeshor.Bind(s_CFSS, 496);
    theTypeshor.Bind(s_MSSUNT, 501);
    theTypeshor.Bind(s_THTMUN, 502);
    theTypeshor.Bind(s_DTENV, 565);
    theTypeshor.Bind(s_MTPRRP, 566);
    theTypeshor.Bind(s_PRDFR, 567);
    theTypeshor.Bind(s_MTRPRP, 569);
    theTypeshor.Bind(s_PDFR, 573);
    theTypeshor.Bind(s_DCP1, 600);
    theTypeshor.Bind(s_DCPREQ, 601);

    theTypeshor.Bind(s_CYLTLR, 609);
    theTypeshor.Bind(s_SRWP, 610);
    theTypeshor.Bind(s_ANGTLR, 611);
    theTypeshor.Bind(s_CNCTLR, 612);
    theTypeshor.Bind(s_CRRNTL, 613);
    theTypeshor.Bind(s_CXLTLR, 614);
    theTypeshor.Bind(s_FLTTLR, 615);
    theTypeshor.Bind(s_LNP0, 616);
    theTypeshor.Bind(s_PRLTLR, 617);
    theTypeshor.Bind(s_PRPTLR, 618);
    theTypeshor.Bind(s_PSTTLR, 619);
    theTypeshor.Bind(s_RNDTLR, 620);
    theTypeshor.Bind(s_STRTLR, 621);
    theTypeshor.Bind(s_SRPRTL, 622);
    theTypeshor.Bind(s_SYMTLR, 623);
    theTypeshor.Bind(s_TTRNTL, 624);
    theTypeshor.Bind(s_GMTTLR, 625);
    theTypeshor.Bind(s_GMTLRL, 626);
    theTypeshor.Bind(s_GTWDR, 627);
    theTypeshor.Bind(s_MDGMTL, 628);
    theTypeshor.Bind(s_DTMFTR, 630);
    theTypeshor.Bind(s_DTMRFR, 631);
    theTypeshor.Bind(s_CMMDTM, 632);
    theTypeshor.Bind(s_DTMTRG, 633);
    theTypeshor.Bind(s_PDT0, 634);
    theTypeshor.Bind(s_MMWU, 651);
    theTypeshor.Bind(s_CNOFSY, 661);
    theTypeshor.Bind(s_GMTALG, 662);
    theTypeshor.Bind(s_PRPT, 663);
    theTypeshor.Bind(s_TNGNT, 664);
    theTypeshor.Bind(s_PRLOFF, 665);
    theTypeshor.Bind(s_GISU, 666);
    theTypeshor.Bind(s_IDATT, 667);
    theTypeshor.Bind(s_IIRU, 668);
    theTypeshor.Bind(s_GTWDU, 674);
    theTypeshor.Bind(s_PRZNDF, 679);
    theTypeshor.Bind(s_RNZNDF, 680);
    theTypeshor.Bind(s_RNZNOR, 681);
    theTypeshor.Bind(s_TLRZN, 682);
    theTypeshor.Bind(s_TLZNDF, 683);
    theTypeshor.Bind(s_TLZNFR, 684);
    theTypeshor.Bind(s_INRPIT, 700);
    theTypeshor.Bind(s_VLRPIT, 701);
    theTypeshor.Bind(s_DMIA, 703);
    theTypeshor.Bind(s_ANNPLN, 704);
    theTypeshor.Bind(s_CNGMRP, 712);
    theTypeshor.Bind(s_CGRR, 713);
  }
} // namespace

RWStepAP214_ReadWriteModule::RWStepAP214_ReadWriteModule()
{
  static std::mutex           THE_MUTEX;
  std::lock_guard<std::mutex> aLock(THE_MUTEX);
  static bool                 anInitialized = false;
  if (!anInitialized)
  {
    THE_INC_ALLOCATOR =
      new NCollection_IncAllocator(NCollection_IncAllocator::THE_MINIMUM_BLOCK_SIZE);
    initializeTypenums(THE_TYPENUMS);
    initializeTypeshor(THE_TYPESHOR);
    anInitialized = true;
  }
}

int RWStepAP214_ReadWriteModule::CaseStep(const TCollection_AsciiString& key) const
{

  int num;
  if (key.IsEqual(Reco_CartesianPoint))
    return 59;
  if (THE_TYPENUMS.Find(static_cast<std::string_view>(key), num))
    return num;
  if (THE_TYPESHOR.Find(static_cast<std::string_view>(key), num))
    return num;
  return 0;
}

int RWStepAP214_ReadWriteModule::CaseStep(
  const NCollection_Sequence<TCollection_AsciiString>& theTypes) const
{

  int NbComp = theTypes.Length();
  if (NbComp < 2)
  {
#ifdef OCCT_DEBUG
    std::cout << "Not a Plex" << std::endl;
#endif
  }
  else
  {

    int i, num = 0;
    for (i = 1; i <= NbComp; i++)
    {
      if (THE_TYPESHOR.IsBound(static_cast<std::string_view>(theTypes(i))))
      {
        num = 1;
        break;
      }
    }
    if (num > 0)
    {
      NCollection_Sequence<TCollection_AsciiString> longs;
      for (i = 1; i <= NbComp; i++)
      {
        if (THE_TYPESHOR.Find(static_cast<std::string_view>(theTypes(i)), num))
          longs.Append(TCollection_AsciiString(StepType(num)));
        else
          longs.Append(theTypes(i));
      }
      return CaseStep(longs);
    }

    NCollection_Sequence<TCollection_AsciiString> types;
    for (i = 1; i <= theTypes.Length(); i++)
      types.Append(theTypes(i));

    bool                    isOK = false;
    TCollection_AsciiString tmpStr;
    int                     aLen = types.Length() - 1;
    while (!isOK)
    {
      isOK = true;
      for (i = 1; i <= aLen; i++)
        if (types(i) > types(i + 1))
        {
          tmpStr       = types(i);
          types(i)     = types(i + 1);
          types(i + 1) = tmpStr;
          isOK         = false;
        }
    }

    if (NbComp == 8)
    {
      if ((types(1).IsEqual(StepType(729))) && (types(2).IsEqual(StepType(144)))
          && (types(3).IsEqual(StepType(354))) && (types(4).IsEqual(StepType(799)))
          && (types(5).IsEqual(StepType(743)))
          && (((types(6).IsEqual(StepType(759))) && (types(7).IsEqual(StepType(761))))
              || ((types(6).IsEqual(StepType(731))) && (types(7).IsEqual(StepType(733))))
              || ((types(6).IsEqual(StepType(767))) && (types(7).IsEqual(StepType(769))))
              || ((types(6).IsEqual(StepType(789))) && (types(7).IsEqual(StepType(791))))
              || ((types(6).IsEqual(StepType(781))) && (types(7).IsEqual(StepType(785))))
              || ((types(6).IsEqual(StepType(783))) && (types(7).IsEqual(StepType(784)))))
          && (types(8).IsEqual(StepType(247))))
      {
        return 800;
      }
    }
    else if (NbComp == 7)
    {
      if ((types(1).IsEqual(StepType(48))) && (types(2).IsEqual(StepType(38)))
          && (types(3).IsEqual(StepType(84))) && (types(4).IsEqual(StepType(144)))
          && (types(5).IsEqual(StepType(239))) && (types(6).IsEqual(StepType(247)))
          && (types(7).IsEqual(StepType(311))))
      {
        return 319;
      }
      else if ((types(1).IsEqual(StepType(48))) && (types(2).IsEqual(StepType(38)))
               && (types(3).IsEqual(StepType(39))) && (types(4).IsEqual(StepType(84)))
               && (types(5).IsEqual(StepType(144))) && (types(6).IsEqual(StepType(239)))
               && (types(7).IsEqual(StepType(247))))
      {
        return 320;
      }
      else if ((types(1).IsEqual(StepType(48))) && (types(2).IsEqual(StepType(38)))
               && (types(3).IsEqual(StepType(84))) && (types(4).IsEqual(StepType(144)))
               && (types(5).IsEqual(StepType(236))) && (types(6).IsEqual(StepType(239)))
               && (types(7).IsEqual(StepType(247))))
      {
        return 321;
      }
      else if ((types(1).IsEqual(StepType(43))) && (types(2).IsEqual(StepType(48)))
               && (types(3).IsEqual(StepType(38))) && (types(4).IsEqual(StepType(84)))
               && (types(5).IsEqual(StepType(144))) && (types(6).IsEqual(StepType(239)))
               && (types(7).IsEqual(StepType(247))))
      {
        return 322;
      }
      else if ((types(1).IsEqual(StepType(49))) && (types(2).IsEqual(StepType(40)))
               && (types(3).IsEqual(StepType(41))) && (types(4).IsEqual(StepType(144)))
               && (types(5).IsEqual(StepType(240))) && (types(6).IsEqual(StepType(247)))
               && (types(7).IsEqual(StepType(271))))
      {
        return 323;
      }
      else if ((types(1).IsEqual(StepType(49))) && (types(2).IsEqual(StepType(40)))
               && (types(3).IsEqual(StepType(144))) && (types(4).IsEqual(StepType(240)))
               && (types(5).IsEqual(StepType(247))) && (types(6).IsEqual(StepType(271)))
               && (types(7).IsEqual(StepType(312))))
      {
        return 324;
      }
      else if ((types(1).IsEqual(StepType(49))) && (types(2).IsEqual(StepType(40)))
               && (types(3).IsEqual(StepType(144))) && (types(4).IsEqual(StepType(237)))
               && (types(5).IsEqual(StepType(240))) && (types(6).IsEqual(StepType(247)))
               && (types(7).IsEqual(StepType(271))))
      {
        return 325;
      }
      else if ((types(1).IsEqual(StepType(44))) && (types(2).IsEqual(StepType(49)))
               && (types(3).IsEqual(StepType(40))) && (types(4).IsEqual(StepType(144)))
               && (types(5).IsEqual(StepType(240))) && (types(6).IsEqual(StepType(247)))
               && (types(7).IsEqual(StepType(271))))
      {
        return 326;
      }
      else if ((types(1).IsEqual(StepType(40))) && (types(2).IsEqual(StepType(41)))
               && (types(3).IsEqual(StepType(49))) && (types(4).IsEqual(StepType(144)))
               && (types(5).IsEqual(StepType(240))) && (types(6).IsEqual(StepType(247)))
               && (types(7).IsEqual(StepType(271))))
      {
        return 323;
      }
      else if ((types(1).IsEqual(StepType(40))) && (types(2).IsEqual(StepType(41)))
               && (types(3).IsEqual(StepType(240))) && (types(4).IsEqual(StepType(49)))
               && (types(5).IsEqual(StepType(247))) && (types(6).IsEqual(StepType(144)))
               && (types(7).IsEqual(StepType(271))))
      {
        return 323;
      }
    }

    else if (NbComp == 6)
    {
      if (types(1).IsEqual(StepType(52)) && types(2).IsEqual(StepType(134))
          && types(3).IsEqual(StepType(144)) && types(4).IsEqual(StepType(162))
          && types(5).IsEqual(StepType(247)) && types(6).IsEqual(StepType(266)))
      {
        return 337;
      }
    }
    else if (NbComp == 5)
    {

      if ((types(1).IsEqual(StepType(48))) && (types(2).IsEqual(StepType(84)))
          && (types(3).IsEqual(StepType(144))) && (types(4).IsEqual(StepType(247)))
          && (types(5).IsEqual(StepType(272))))
      {
        return 358;
      }
      else if ((types(1).IsEqual(StepType(157))) && (types(2).IsEqual(StepType(406)))
               && (types(3).IsEqual(StepType(165))) && (types(4).IsEqual(StepType(480)))
               && (types(5).IsEqual(StepType(247))))
      {
        return 692;
      }
      else if ((types(1).IsEqual(StepType(406))) && (types(2).IsEqual(StepType(165)))
               && (types(3).IsEqual(StepType(200))) && (types(4).IsEqual(StepType(480)))
               && (types(5).IsEqual(StepType(247))))
      {
        return 693;
      }
      else if (((types(1).IsEqual(StepType(609)) || types(1).IsEqual(StepType(611))
                 || types(1).IsEqual(StepType(612)) || types(1).IsEqual(StepType(613))
                 || types(1).IsEqual(StepType(614)) || types(1).IsEqual(StepType(615)))
                && types(2).IsEqual(StepType(625)) && types(3).IsEqual(StepType(627))
                && types(4).IsEqual(StepType(675)) && types(5).IsEqual(StepType(676)))
               || (types(1).IsEqual(StepType(625)) && types(2).IsEqual(StepType(627))
                   && types(3).IsEqual(StepType(675)) && types(4).IsEqual(StepType(676))
                   && (types(5).IsEqual(StepType(616)) || types(5).IsEqual(StepType(617))
                       || types(5).IsEqual(StepType(618)) || types(5).IsEqual(StepType(619))
                       || types(5).IsEqual(StepType(620)) || types(5).IsEqual(StepType(621))
                       || types(5).IsEqual(StepType(622)) || types(5).IsEqual(StepType(623))
                       || types(5).IsEqual(StepType(624)))))
      {
        return 705;
      }
      else if ((types(1).IsEqual(StepType(4))) && (types(2).IsEqual(StepType(7)))
               && (types(3).IsEqual(StepType(144))) && (types(4).IsEqual(StepType(247)))
               && (types(5).IsEqual(StepType(270))))
      {
        return 719;
      }
      else if ((types(1).IsEqual(StepType(144))) && (types(2).IsEqual(StepType(803)))
               && (types(3).IsEqual(StepType(247))) && (types(4).IsEqual(StepType(709)))
               && (types(5).IsEqual(StepType(708))))
      {
        return 802;
      }
    }
    else if (NbComp == 4)
    {
      if ((types(1).IsEqual(StepType(161))) && (types(2).IsEqual(StepType(189)))
          && (types(3).IsEqual(StepType(247))) && (types(4).IsEqual(StepType(304))))
      {
        return 332;
      }

      else if ((types(1).IsEqual(StepType(143)) && types(2).IsEqual(StepType(148))
                && types(3).IsEqual(StepType(149)) && types(4).IsEqual(StepType(246))))
      {
        return 333;
      }

      else if ((types(1).IsEqual(StepType(157))) && (types(2).IsEqual(StepType(406)))
               && (types(3).IsEqual(StepType(165))) && (types(4).IsEqual(StepType(247))))
      {
        return 635;
      }
      else if ((types(1).IsEqual(StepType(625))) && (types(2).IsEqual(StepType(627)))
               && (types(3).IsEqual(StepType(628))) && (types(4).IsEqual(StepType(619))))
      {
        return 636;
      }
      else if ((types(1).IsEqual(StepType(406))) && (types(2).IsEqual(StepType(165)))
               && (types(3).IsEqual(StepType(200))) && (types(4).IsEqual(StepType(247))))
      {
        return 691;
      }
      else if (((types(1).IsEqual(StepType(609)) || types(1).IsEqual(StepType(611))
                 || types(1).IsEqual(StepType(612)) || types(1).IsEqual(StepType(613))
                 || types(1).IsEqual(StepType(614)) || types(1).IsEqual(StepType(615)))
                && types(2).IsEqual(StepType(625)) && types(3).IsEqual(StepType(627))
                && types(4).IsEqual(StepType(676)))
               || (types(1).IsEqual(StepType(625)) && types(2).IsEqual(StepType(627))
                   && types(3).IsEqual(StepType(676))
                   && (types(4).IsEqual(StepType(616)) || types(4).IsEqual(StepType(617))
                       || types(4).IsEqual(StepType(618)) || types(4).IsEqual(StepType(619))
                       || types(4).IsEqual(StepType(620)) || types(4).IsEqual(StepType(621))
                       || types(4).IsEqual(StepType(622)) || types(4).IsEqual(StepType(623))
                       || types(4).IsEqual(StepType(624)))))
      {
        return 695;
      }
      else if (((types(1).IsEqual(StepType(609)) || types(1).IsEqual(StepType(611))
                 || types(1).IsEqual(StepType(612)) || types(1).IsEqual(StepType(613))
                 || types(1).IsEqual(StepType(614)) || types(1).IsEqual(StepType(615)))
                && types(2).IsEqual(StepType(625)) && types(3).IsEqual(StepType(627))
                && types(4).IsEqual(StepType(677)))
               || (types(1).IsEqual(StepType(625)) && types(2).IsEqual(StepType(627))
                   && types(4).IsEqual(StepType(677))
                   && (types(3).IsEqual(StepType(616)) || types(3).IsEqual(StepType(617))
                       || types(3).IsEqual(StepType(618)) || types(3).IsEqual(StepType(619))
                       || types(3).IsEqual(StepType(620)) || types(3).IsEqual(StepType(621))
                       || types(3).IsEqual(StepType(622)) || types(3).IsEqual(StepType(623))
                       || types(3).IsEqual(StepType(624)))))
      {
        return 697;
      }
      else if (types(1).IsEqual(StepType(671)) && types(2).IsEqual(StepType(470))
               && types(3).IsEqual(StepType(630)) && types(4).IsEqual(StepType(258)))
      {
        return 698;
      }
      else if (((types(1).IsEqual(StepType(609)) || types(1).IsEqual(StepType(611))
                 || types(1).IsEqual(StepType(612)) || types(1).IsEqual(StepType(613))
                 || types(1).IsEqual(StepType(614)) || types(1).IsEqual(StepType(615)))
                && types(2).IsEqual(StepType(625)) && types(3).IsEqual(StepType(675))
                && types(4).IsEqual(StepType(676)))
               || (types(1).IsEqual(StepType(625)) && types(2).IsEqual(StepType(675))
                   && types(3).IsEqual(StepType(676))
                   && (types(4).IsEqual(StepType(616)) || types(4).IsEqual(StepType(617))
                       || types(4).IsEqual(StepType(618)) || types(4).IsEqual(StepType(619))
                       || types(4).IsEqual(StepType(620)) || types(4).IsEqual(StepType(621))
                       || types(4).IsEqual(StepType(622)) || types(4).IsEqual(StepType(623))
                       || types(4).IsEqual(StepType(624)))))
      {
        return 706;
      }
      else if (types(1).IsEqual(StepType(402)) && types(2).IsEqual(StepType(714))
               && types(3).IsEqual(StepType(441)) && types(4).IsEqual(StepType(245)))
      {
        return 715;
      }
    }
    else if (NbComp == 3)
    {
      if ((types(1).IsEqual(StepType(158))) && (types(2).IsEqual(StepType(169)))
          && (types(3).IsEqual(StepType(264))))
      {
        return 327;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(264)))
               && (types(3).IsEqual(StepType(158))))
      {
        return 327;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(201)))
               && (types(3).IsEqual(StepType(264))))
      {
        return 328;
      }
      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(158)))
               && (types(3).IsEqual(StepType(169))))
      {
        return 329;
      }
      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(201))))
      {
        return 330;
      }
      else if ((types(1).IsEqual(StepType(143))) && (types(2).IsEqual(StepType(149)))
               && (types(3).IsEqual(StepType(246))))
      {
        return 331;
      }

      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(336))))
      {
        return 334;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(264)))
               && (types(3).IsEqual(StepType(336))))
      {
        return 335;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(336)))
               && (types(3).IsEqual(StepType(264))))
      {
        return 335;
      }
      else if ((types(1).IsEqual(StepType(143))) && (types(2).IsEqual(StepType(188)))
               && (types(3).IsEqual(StepType(246))))
      {
        return 338;
      }

      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(342)))
               && (types(3).IsEqual(StepType(264))))
      {
        return 344;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(264)))
               && (types(3).IsEqual(StepType(343))))
      {
        return 345;
      }
      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(342))))
      {
        return 346;
      }
      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(343))))
      {
        return 347;
      }
      else if ((types(1).IsEqual(StepType(157))) && (types(2).IsEqual(StepType(165)))
               && (types(3).IsEqual(StepType(310))))
      {
        return 357;
      }

      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(158)))
               && (types(3).IsEqual(StepType(264))))
      {
        return 327;
      }

      else if ((types(1).IsEqual(StepType(249))) && (types(2).IsEqual(StepType(388)))
               && (types(3).IsEqual(StepType(387))))
      {
        return 389;
      }
      else if ((types(1).IsEqual(StepType(407))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(264))))
      {
        return 409;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(264)))
               && (types(3).IsEqual(StepType(408))))
      {
        return 410;
      }
      else if ((types(1).IsEqual(StepType(407))) && (types(2).IsEqual(StepType(79)))
               && (types(3).IsEqual(StepType(169))))
      {
        return 411;
      }
      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(408))))
      {
        return 412;
      }

      else if ((types(1).IsEqual(StepType(98))) && (types(2).IsEqual(StepType(245)))
               && (types(3).IsEqual(StepType(262))))
      {
        return 463;
      }

      else if ((types(1).IsEqual(StepType(406))) && (types(2).IsEqual(StepType(480)))
               && (types(3).IsEqual(StepType(247))))
      {
        return 481;
      }
      else if ((types(1).IsEqual(StepType(501))) && (types(2).IsEqual(StepType(169)))
               && (types(3).IsEqual(StepType(264))))
      {
        return 574;
      }
      else if ((types(1).IsEqual(StepType(169))) && (types(2).IsEqual(StepType(264)))
               && (types(3).IsEqual(StepType(502))))
      {
        return 578;
      }
      else if ((types(1).IsEqual(StepType(79))) && (types(2).IsEqual(StepType(501)))
               && (types(3).IsEqual(StepType(169))))
      {
        return 650;
      }
      else if (((types(1).IsEqual(StepType(609)) || types(1).IsEqual(StepType(611))
                 || types(1).IsEqual(StepType(612)) || types(1).IsEqual(StepType(613))
                 || types(1).IsEqual(StepType(614)) || types(1).IsEqual(StepType(615)))
                && types(2).IsEqual(StepType(625)) && types(3).IsEqual(StepType(627)))
               || (types(1).IsEqual(StepType(625)) && types(2).IsEqual(StepType(627))
                   && (types(3).IsEqual(StepType(616)) || types(3).IsEqual(StepType(617))
                       || types(3).IsEqual(StepType(618)) || types(3).IsEqual(StepType(619))
                       || types(3).IsEqual(StepType(620)) || types(3).IsEqual(StepType(621))
                       || types(3).IsEqual(StepType(622)) || types(3).IsEqual(StepType(623))
                       || types(3).IsEqual(StepType(624)))))
      {
        return 694;
      }
      else if (((types(1).IsEqual(StepType(609)) || types(1).IsEqual(StepType(611))
                 || types(1).IsEqual(StepType(612)) || types(1).IsEqual(StepType(613))
                 || types(1).IsEqual(StepType(614)) || types(1).IsEqual(StepType(615)))
                && types(2).IsEqual(StepType(625)) && types(3).IsEqual(StepType(676)))
               || (types(1).IsEqual(StepType(625)) && types(2).IsEqual(StepType(676))
                   && (types(3).IsEqual(StepType(616)) || types(3).IsEqual(StepType(617))
                       || types(3).IsEqual(StepType(618)) || types(3).IsEqual(StepType(619))
                       || types(3).IsEqual(StepType(620)) || types(3).IsEqual(StepType(621))
                       || types(3).IsEqual(StepType(622)) || types(3).IsEqual(StepType(623))
                       || types(3).IsEqual(StepType(624)))))
      {
        return 696;
      }
      else if (types(1).IsEqual(StepType(470)) && types(2).IsEqual(StepType(630))
               && types(3).IsEqual(StepType(258)))
      {
        return 699;
      }
    }
    return 0;
  }
  return 0;
}

bool RWStepAP214_ReadWriteModule::IsComplex(const int CN) const
{
  switch (CN)
  {
    case 319:
      return true;
    case 320:
      return true;
    case 321:
      return true;
    case 322:
      return true;
    case 323:
      return true;
    case 324:
      return true;
    case 325:
      return true;
    case 326:
      return true;
    case 327:
      return true;
    case 328:
      return true;
    case 329:
      return true;
    case 330:
      return true;
    case 331:
      return true;
    case 332:
      return true;

    case 333:
      return true;
    case 334:
      return true;
    case 335:
      return true;
    case 337:
      return true;
    case 338:
      return true;
    case 344:
      return true;
    case 345:
      return true;
    case 346:
      return true;
    case 347:
      return true;
    case 357:
      return true;
    case 358:
      return true;

    case 389:
      return true;
    case 409:
    case 410:
    case 411:
    case 412:
      return true;
    case 463:
      return true;
    case 481:
      return true;
    case 574:
      return true;
    case 578:
      return true;
    case 635:
      return true;
    case 636:
      return true;
    case 650:
      return true;
    case 691:
      return true;
    case 692:
      return true;
    case 693:
      return true;
    case 694:
      return true;
    case 695:
      return true;
    case 696:
      return true;
    case 697:
      return true;
    case 698:
      return true;
    case 699:
      return true;
    case 705:
      return true;
    case 706:
      return true;
    case 715:
      return true;
    case 719:
      return true;
    default:
      return false;
  }
}

const std::string_view& RWStepAP214_ReadWriteModule::StepType(const int CN) const
{
  switch (CN)
  {
    case 1:
      return Reco_Address;
    case 2:
      return Reco_AdvancedBrepShapeRepresentation;
    case 3:
      return Reco_AdvancedFace;
    case 4:
      return Reco_AnnotationCurveOccurrence;
    case 5:
      return Reco_AnnotationFillArea;
    case 6:
      return Reco_AnnotationFillAreaOccurrence;
    case 7:
      return Reco_AnnotationOccurrence;
    case 8:
      return Reco_AnnotationSubfigureOccurrence;
    case 9:
      return Reco_AnnotationSymbol;
    case 10:
      return Reco_AnnotationSymbolOccurrence;
    case 11:
      return Reco_AnnotationText;
    case 12:
      return Reco_AnnotationTextOccurrence;
    case 13:
      return Reco_ApplicationContext;
    case 14:
      return Reco_ApplicationContextElement;
    case 15:
      return Reco_ApplicationProtocolDefinition;
    case 16:
      return Reco_Approval;
    case 17:
      return Reco_ApprovalAssignment;
    case 18:
      return Reco_ApprovalPersonOrganization;
    case 19:
      return Reco_ApprovalRelationship;
    case 20:
      return Reco_ApprovalRole;
    case 21:
      return Reco_ApprovalStatus;
    case 22:
      return Reco_AreaInSet;
    case 23:
      return Reco_AutoDesignActualDateAndTimeAssignment;
    case 24:
      return Reco_AutoDesignActualDateAssignment;
    case 25:
      return Reco_AutoDesignApprovalAssignment;
    case 26:
      return Reco_AutoDesignDateAndPersonAssignment;
    case 27:
      return Reco_AutoDesignGroupAssignment;
    case 28:
      return Reco_AutoDesignNominalDateAndTimeAssignment;
    case 29:
      return Reco_AutoDesignNominalDateAssignment;
    case 30:
      return Reco_AutoDesignOrganizationAssignment;
    case 31:
      return Reco_AutoDesignPersonAndOrganizationAssignment;
    case 32:
      return Reco_AutoDesignPresentedItem;
    case 33:
      return Reco_AutoDesignSecurityClassificationAssignment;
    case 34:
      return Reco_AutoDesignViewArea;
    case 35:
      return Reco_Axis1Placement;
    case 36:
      return Reco_Axis2Placement2d;
    case 37:
      return Reco_Axis2Placement3d;
    case 38:
      return Reco_BSplineCurve;
    case 39:
      return Reco_BSplineCurveWithKnots;
    case 40:
      return Reco_BSplineSurface;
    case 41:
      return Reco_BSplineSurfaceWithKnots;
    case 42:
      return Reco_BackgroundColour;
    case 43:
      return Reco_BezierCurve;
    case 44:
      return Reco_BezierSurface;
    case 45:
      return Reco_Block;
    case 46:
      return Reco_BooleanResult;
    case 47:
      return Reco_BoundaryCurve;
    case 48:
      return Reco_BoundedCurve;
    case 49:
      return Reco_BoundedSurface;
    case 50:
      return Reco_BoxDomain;
    case 51:
      return Reco_BoxedHalfSpace;
    case 52:
      return Reco_BrepWithVoids;
    case 53:
      return Reco_CalendarDate;
    case 54:
      return Reco_CameraImage;
    case 55:
      return Reco_CameraModel;
    case 56:
      return Reco_CameraModelD2;
    case 57:
      return Reco_CameraModelD3;
    case 58:
      return Reco_CameraUsage;
    case 59:
      return Reco_CartesianPoint;
    case 60:
      return Reco_CartesianTransformationOperator;
    case 61:
      return Reco_CartesianTransformationOperator3d;
    case 62:
      return Reco_Circle;
    case 63:
      return Reco_ClosedShell;
    case 64:
      return Reco_Colour;
    case 65:
      return Reco_ColourRgb;
    case 66:
      return Reco_ColourSpecification;
    case 67:
      return Reco_CompositeCurve;
    case 68:
      return Reco_CompositeCurveOnSurface;
    case 69:
      return Reco_CompositeCurveSegment;
    case 70:
      return Reco_CompositeText;
    case 71:
      return Reco_CompositeTextWithAssociatedCurves;
    case 72:
      return Reco_CompositeTextWithBlankingBox;
    case 73:
      return Reco_CompositeTextWithExtent;
    case 74:
      return Reco_Conic;
    case 75:
      return Reco_ConicalSurface;
    case 76:
      return Reco_ConnectedFaceSet;
    case 77:
      return Reco_ContextDependentInvisibility;
    case 78:
      return Reco_ContextDependentOverRidingStyledItem;
    case 79:
      return Reco_ConversionBasedUnit;
    case 80:
      return Reco_CoordinatedUniversalTimeOffset;
    case 81:
      return Reco_CsgRepresentation;
    case 82:
      return Reco_CsgShapeRepresentation;
    case 83:
      return Reco_CsgSolid;
    case 84:
      return Reco_Curve;
    case 85:
      return Reco_CurveBoundedSurface;
    case 86:
      return Reco_CurveReplica;
    case 87:
      return Reco_CurveStyle;
    case 88:
      return Reco_CurveStyleFont;
    case 89:
      return Reco_CurveStyleFontPattern;
    case 90:
      return Reco_CylindricalSurface;
    case 91:
      return Reco_Date;
    case 92:
      return Reco_DateAndTime;
    case 93:
      return Reco_DateAndTimeAssignment;
    case 94:
      return Reco_DateAssignment;
    case 95:
      return Reco_DateRole;
    case 96:
      return Reco_DateTimeRole;
    case 97:
      return Reco_DefinedSymbol;
    case 98:
      return Reco_DefinitionalRepresentation;
    case 99:
      return Reco_DegeneratePcurve;
    case 100:
      return Reco_DegenerateToroidalSurface;
    case 101:
      return Reco_DescriptiveRepresentationItem;
    case 102:
      return Reco_DimensionCurve;
    case 103:
      return Reco_DimensionCurveTerminator;
    case 104:
      return Reco_DimensionalExponents;
    case 105:
      return Reco_Direction;
    case 106:
      return Reco_DraughtingAnnotationOccurrence;
    case 107:
      return Reco_DraughtingCallout;
    case 108:
      return Reco_DraughtingPreDefinedColour;
    case 109:
      return Reco_DraughtingPreDefinedCurveFont;
    case 110:
      return Reco_DraughtingSubfigureRepresentation;
    case 111:
      return Reco_DraughtingSymbolRepresentation;
    case 112:
      return Reco_DraughtingTextLiteralWithDelineation;
    case 113:
      return Reco_DrawingDefinition;
    case 114:
      return Reco_DrawingRevision;
    case 115:
      return Reco_Edge;
    case 116:
      return Reco_EdgeCurve;
    case 117:
      return Reco_EdgeLoop;
    case 118:
      return Reco_ElementarySurface;
    case 119:
      return Reco_Ellipse;
    case 120:
      return Reco_EvaluatedDegeneratePcurve;
    case 121:
      return Reco_ExternalSource;
    case 122:
      return Reco_ExternallyDefinedCurveFont;
    case 123:
      return Reco_ExternallyDefinedHatchStyle;
    case 124:
      return Reco_ExternallyDefinedItem;
    case 125:
      return Reco_ExternallyDefinedSymbol;
    case 126:
      return Reco_ExternallyDefinedTextFont;
    case 127:
      return Reco_ExternallyDefinedTileStyle;
    case 128:
      return Reco_ExtrudedAreaSolid;
    case 129:
      return Reco_Face;
    case 131:
      return Reco_FaceBound;
    case 132:
      return Reco_FaceOuterBound;
    case 133:
      return Reco_FaceSurface;
    case 134:
      return Reco_FacetedBrep;
    case 135:
      return Reco_FacetedBrepShapeRepresentation;
    case 136:
      return Reco_FillAreaStyle;
    case 137:
      return Reco_FillAreaStyleColour;
    case 138:
      return Reco_FillAreaStyleHatching;
    case 139:
      return Reco_FillAreaStyleTileSymbolWithStyle;
    case 140:
      return Reco_FillAreaStyleTiles;
    case 141:
      return Reco_FunctionallyDefinedTransformation;
    case 142:
      return Reco_GeometricCurveSet;
    case 143:
      return Reco_GeometricRepresentationContext;
    case 144:
      return Reco_GeometricRepresentationItem;
    case 145:
      return Reco_GeometricSet;
    case 146:
      return Reco_GeometricallyBoundedSurfaceShapeRepresentation;
    case 147:
      return Reco_GeometricallyBoundedWireframeShapeRepresentation;
    case 148:
      return Reco_GlobalUncertaintyAssignedContext;
    case 149:
      return Reco_GlobalUnitAssignedContext;
    case 150:
      return Reco_Group;
    case 151:
      return Reco_GroupAssignment;
    case 152:
      return Reco_GroupRelationship;
    case 153:
      return Reco_HalfSpaceSolid;
    case 154:
      return Reco_Hyperbola;
    case 155:
      return Reco_IntersectionCurve;
    case 156:
      return Reco_Invisibility;
    case 157:
      return Reco_LengthMeasureWithUnit;
    case 158:
      return Reco_LengthUnit;
    case 159:
      return Reco_Line;
    case 160:
      return Reco_LocalTime;
    case 161:
      return Reco_Loop;
    case 162:
      return Reco_ManifoldSolidBrep;
    case 163:
      return Reco_ManifoldSurfaceShapeRepresentation;
    case 164:
      return Reco_MappedItem;
    case 165:
      return Reco_MeasureWithUnit;
    case 166:
      return Reco_MechanicalDesignGeometricPresentationArea;
    case 167:
      return Reco_MechanicalDesignGeometricPresentationRepresentation;
    case 168:
      return Reco_MechanicalDesignPresentationArea;
    case 169:
      return Reco_NamedUnit;
    case 171:
      return Reco_OffsetCurve3d;
    case 172:
      return Reco_OffsetSurface;
    case 173:
      return Reco_OneDirectionRepeatFactor;
    case 174:
      return Reco_OpenShell;
    case 175:
      return Reco_OrdinalDate;
    case 176:
      return Reco_Organization;
    case 177:
      return Reco_OrganizationAssignment;
    case 178:
      return Reco_OrganizationRole;
    case 179:
      return Reco_OrganizationalAddress;
    case 180:
      return Reco_OrientedClosedShell;
    case 181:
      return Reco_OrientedEdge;
    case 182:
      return Reco_OrientedFace;
    case 183:
      return Reco_OrientedOpenShell;
    case 184:
      return Reco_OrientedPath;
    case 185:
      return Reco_OuterBoundaryCurve;
    case 186:
      return Reco_OverRidingStyledItem;
    case 187:
      return Reco_Parabola;
    case 188:
      return Reco_ParametricRepresentationContext;
    case 189:
      return Reco_Path;
    case 190:
      return Reco_Pcurve;
    case 191:
      return Reco_Person;
    case 192:
      return Reco_PersonAndOrganization;
    case 193:
      return Reco_PersonAndOrganizationAssignment;
    case 194:
      return Reco_PersonAndOrganizationRole;
    case 195:
      return Reco_PersonalAddress;
    case 196:
      return Reco_Placement;
    case 197:
      return Reco_PlanarBox;
    case 198:
      return Reco_PlanarExtent;
    case 199:
      return Reco_Plane;
    case 200:
      return Reco_PlaneAngleMeasureWithUnit;
    case 201:
      return Reco_PlaneAngleUnit;
    case 202:
      return Reco_Point;
    case 203:
      return Reco_PointOnCurve;
    case 204:
      return Reco_PointOnSurface;
    case 205:
      return Reco_PointReplica;
    case 206:
      return Reco_PointStyle;
    case 207:
      return Reco_PolyLoop;
    case 208:
      return Reco_Polyline;
    case 209:
      return Reco_PreDefinedColour;
    case 210:
      return Reco_PreDefinedCurveFont;
    case 211:
      return Reco_PreDefinedItem;
    case 212:
      return Reco_PreDefinedSymbol;
    case 213:
      return Reco_PreDefinedTextFont;
    case 214:
      return Reco_PresentationArea;
    case 215:
      return Reco_PresentationLayerAssignment;
    case 216:
      return Reco_PresentationRepresentation;
    case 217:
      return Reco_PresentationSet;
    case 218:
      return Reco_PresentationSize;
    case 219:
      return Reco_PresentationStyleAssignment;
    case 220:
      return Reco_PresentationStyleByContext;
    case 221:
      return Reco_PresentationView;
    case 222:
      return Reco_PresentedItem;
    case 223:
      return Reco_Product;
    case 224:
      return Reco_ProductCategory;
    case 225:
      return Reco_ProductContext;
    case 226:
      return Reco_ProductDataRepresentationView;
    case 227:
      return Reco_ProductDefinition;
    case 228:
      return Reco_ProductDefinitionContext;
    case 229:
      return Reco_ProductDefinitionFormation;
    case 230:
      return Reco_ProductDefinitionFormationWithSpecifiedSource;
    case 231:
      return Reco_ProductDefinitionShape;
    case 232:
      return Reco_ProductRelatedProductCategory;
    case 233:
      return Reco_ProductType;
    case 234:
      return Reco_PropertyDefinition;
    case 235:
      return Reco_PropertyDefinitionRepresentation;
    case 236:
      return Reco_QuasiUniformCurve;
    case 237:
      return Reco_QuasiUniformSurface;
    case 238:
      return Reco_RatioMeasureWithUnit;
    case 239:
      return Reco_RationalBSplineCurve;
    case 240:
      return Reco_RationalBSplineSurface;
    case 241:
      return Reco_RectangularCompositeSurface;
    case 242:
      return Reco_RectangularTrimmedSurface;
    case 243:
      return Reco_RepItemGroup;
    case 244:
      return Reco_ReparametrisedCompositeCurveSegment;
    case 245:
      return Reco_Representation;
    case 246:
      return Reco_RepresentationContext;
    case 247:
      return Reco_RepresentationItem;
    case 248:
      return Reco_RepresentationMap;
    case 249:
      return Reco_RepresentationRelationship;
    case 250:
      return Reco_RevolvedAreaSolid;
    case 251:
      return Reco_RightAngularWedge;
    case 252:
      return Reco_RightCircularCone;
    case 253:
      return Reco_RightCircularCylinder;
    case 254:
      return Reco_SeamCurve;
    case 255:
      return Reco_SecurityClassification;
    case 256:
      return Reco_SecurityClassificationAssignment;
    case 257:
      return Reco_SecurityClassificationLevel;
    case 258:
      return Reco_ShapeAspect;
    case 259:
      return Reco_ShapeAspectRelationship;
    case 260:
      return Reco_ShapeAspectTransition;
    case 261:
      return Reco_ShapeDefinitionRepresentation;
    case 262:
      return Reco_ShapeRepresentation;
    case 263:
      return Reco_ShellBasedSurfaceModel;
    case 264:
      return Reco_SiUnit;
    case 265:
      return Reco_SolidAngleMeasureWithUnit;
    case 266:
      return Reco_SolidModel;
    case 267:
      return Reco_SolidReplica;
    case 268:
      return Reco_Sphere;
    case 269:
      return Reco_SphericalSurface;
    case 270:
      return Reco_StyledItem;
    case 271:
      return Reco_Surface;
    case 272:
      return Reco_SurfaceCurve;
    case 273:
      return Reco_SurfaceOfLinearExtrusion;
    case 274:
      return Reco_SurfaceOfRevolution;
    case 275:
      return Reco_SurfacePatch;
    case 276:
      return Reco_SurfaceReplica;
    case 277:
      return Reco_SurfaceSideStyle;
    case 278:
      return Reco_SurfaceStyleBoundary;
    case 279:
      return Reco_SurfaceStyleControlGrid;
    case 280:
      return Reco_SurfaceStyleFillArea;
    case 281:
      return Reco_SurfaceStyleParameterLine;
    case 282:
      return Reco_SurfaceStyleSegmentationCurve;
    case 283:
      return Reco_SurfaceStyleSilhouette;
    case 284:
      return Reco_SurfaceStyleUsage;
    case 285:
      return Reco_SweptAreaSolid;
    case 286:
      return Reco_SweptSurface;
    case 287:
      return Reco_SymbolColour;
    case 288:
      return Reco_SymbolRepresentation;
    case 289:
      return Reco_SymbolRepresentationMap;
    case 290:
      return Reco_SymbolStyle;
    case 291:
      return Reco_SymbolTarget;
    case 292:
      return Reco_Template;
    case 293:
      return Reco_TemplateInstance;
    case 294:
      return Reco_TerminatorSymbol;
    case 295:
      return Reco_TextLiteral;
    case 296:
      return Reco_TextLiteralWithAssociatedCurves;
    case 297:
      return Reco_TextLiteralWithBlankingBox;
    case 298:
      return Reco_TextLiteralWithDelineation;
    case 299:
      return Reco_TextLiteralWithExtent;
    case 300:
      return Reco_TextStyle;
    case 301:
      return Reco_TextStyleForDefinedFont;
    case 302:
      return Reco_TextStyleWithBoxCharacteristics;
    case 303:
      return Reco_TextStyleWithMirror;
    case 304:
      return Reco_TopologicalRepresentationItem;
    case 305:
      return Reco_ToroidalSurface;
    case 306:
      return Reco_Torus;
    case 307:
      return Reco_TransitionalShapeRepresentation;
    case 308:
      return Reco_TrimmedCurve;
    case 309:
      return Reco_TwoDirectionRepeatFactor;
    case 310:
      return Reco_UncertaintyMeasureWithUnit;
    case 311:
      return Reco_UniformCurve;
    case 312:
      return Reco_UniformSurface;
    case 313:
      return Reco_Vector;
    case 314:
      return Reco_Vertex;
    case 315:
      return Reco_VertexLoop;
    case 316:
      return Reco_VertexPoint;
    case 317:
      return Reco_ViewVolume;
    case 318:
      return Reco_WeekOfYearAndDayDate;

    case 336:
      return Reco_SolidAngleUnit;
    case 339:
      return Reco_MechanicalContext;
    case 340:
      return Reco_DesignContext;

    case 341:
      return Reco_TimeMeasureWithUnit;
    case 342:
      return Reco_RatioUnit;
    case 343:
      return Reco_TimeUnit;
    case 348:
      return Reco_ApprovalDateTime;
    case 349:
      return Reco_CameraImage2dWithScale;
    case 350:
      return Reco_CameraImage3dWithScale;
    case 351:
      return Reco_CartesianTransformationOperator2d;
    case 352:
      return Reco_DerivedUnit;
    case 353:
      return Reco_DerivedUnitElement;
    case 354:
      return Reco_ItemDefinedTransformation;
    case 355:
      return Reco_PresentedItemRepresentation;
    case 356:
      return Reco_PresentationLayerUsage;

    case 366:
      return Reco_AutoDesignDocumentReference;
    case 367:
      return Reco_Document;
    case 368:
      return Reco_DigitalDocument;
    case 369:
      return Reco_DocumentRelationship;
    case 370:
      return Reco_DocumentType;
    case 371:
      return Reco_DocumentUsageConstraint;
    case 372:
      return Reco_Effectivity;
    case 373:
      return Reco_ProductDefinitionEffectivity;
    case 374:
      return Reco_ProductDefinitionRelationship;

    case 375:
      return Reco_ProductDefinitionWithAssociatedDocuments;
    case 376:
      return Reco_PhysicallyModeledProductDefinition;

    case 377:
      return Reco_ProductDefinitionUsage;
    case 378:
      return Reco_MakeFromUsageOption;
    case 379:
      return Reco_AssemblyComponentUsage;
    case 380:
      return Reco_NextAssemblyUsageOccurrence;
    case 381:
      return Reco_PromissoryUsageOccurrence;
    case 382:
      return Reco_QuantifiedAssemblyComponentUsage;
    case 383:
      return Reco_SpecifiedHigherUsageOccurrence;
    case 384:
      return Reco_AssemblyComponentUsageSubstitute;
    case 385:
      return Reco_SuppliedPartRelationship;
    case 386:
      return Reco_ExternallyDefinedRepresentation;
    case 387:
      return Reco_ShapeRepresentationRelationship;
    case 388:
      return Reco_RepresentationRelationshipWithTransformation;

    case 390:
      return Reco_MaterialDesignation;
    case 391:
      return Reco_ContextDependentShapeRepresentation;

    case 392:
      return Reco_AppliedDateAndTimeAssignment;
    case 393:
      return Reco_AppliedDateAssignment;
    case 394:
      return Reco_AppliedApprovalAssignment;
    case 395:
      return Reco_AppliedGroupAssignment;
    case 396:
      return Reco_AppliedOrganizationAssignment;
    case 397:
      return Reco_AppliedPersonAndOrganizationAssignment;
    case 398:
      return Reco_AppliedPresentedItem;
    case 399:
      return Reco_AppliedSecurityClassificationAssignment;
    case 400:
      return Reco_AppliedDocumentReference;
    case 401:
      return Reco_DocumentFile;
    case 402:
      return Reco_CharacterizedObject;
    case 403:
      return Reco_ExtrudedFaceSolid;
    case 404:
      return Reco_RevolvedFaceSolid;
    case 405:
      return Reco_SweptFaceSolid;

    case 406:
      return Reco_MeasureRepresentationItem;
    case 407:
      return Reco_AreaUnit;
    case 408:
      return Reco_VolumeUnit;

    case 413:
      return Reco_Action;
    case 414:
      return Reco_ActionAssignment;
    case 415:
      return Reco_ActionMethod;
    case 416:
      return Reco_ActionRequestAssignment;
    case 417:
      return Reco_CcDesignApproval;
    case 418:
      return Reco_CcDesignCertification;
    case 419:
      return Reco_CcDesignContract;
    case 420:
      return Reco_CcDesignDateAndTimeAssignment;
    case 421:
      return Reco_CcDesignPersonAndOrganizationAssignment;
    case 422:
      return Reco_CcDesignSecurityClassification;
    case 423:
      return Reco_CcDesignSpecificationReference;
    case 424:
      return Reco_Certification;
    case 425:
      return Reco_CertificationAssignment;
    case 426:
      return Reco_CertificationType;
    case 427:
      return Reco_Change;
    case 428:
      return Reco_ChangeRequest;
    case 429:
      return Reco_ConfigurationDesign;
    case 430:
      return Reco_ConfigurationEffectivity;
    case 431:
      return Reco_Contract;
    case 432:
      return Reco_ContractAssignment;
    case 433:
      return Reco_ContractType;
    case 434:
      return Reco_ProductConcept;
    case 435:
      return Reco_ProductConceptContext;
    case 436:
      return Reco_StartRequest;
    case 437:
      return Reco_StartWork;
    case 438:
      return Reco_VersionedActionRequest;
    case 439:
      return Reco_ProductCategoryRelationship;
    case 440:
      return Reco_ActionRequestSolution;
    case 441:
      return Reco_DraughtingModel;

    case 442:
      return Reco_AngularLocation;
    case 443:
      return Reco_AngularSize;
    case 444:
      return Reco_DimensionalCharacteristicRepresentation;
    case 445:
      return Reco_DimensionalLocation;
    case 446:
      return Reco_DimensionalLocationWithPath;
    case 447:
      return Reco_DimensionalSize;
    case 448:
      return Reco_DimensionalSizeWithPath;
    case 449:
      return Reco_ShapeDimensionRepresentation;

    case 450:
      return Reco_DocumentRepresentationType;
    case 451:
      return Reco_ObjectRole;
    case 452:
      return Reco_RoleAssociation;
    case 453:
      return Reco_IdentificationRole;
    case 454:
      return Reco_IdentificationAssignment;
    case 455:
      return Reco_ExternalIdentificationAssignment;
    case 456:
      return Reco_EffectivityAssignment;
    case 457:
      return Reco_NameAssignment;
    case 458:
      return Reco_GeneralProperty;
    case 459:
      return Reco_Class;
    case 460:
      return Reco_ExternallyDefinedClass;
    case 461:
      return Reco_ExternallyDefinedGeneralProperty;
    case 462:
      return Reco_AppliedExternalIdentificationAssignment;

    case 470:
      return Reco_CompositeShapeAspect;
    case 471:
      return Reco_DerivedShapeAspect;
    case 472:
      return Reco_Extension;
    case 473:
      return Reco_DirectedDimensionalLocation;
    case 474:
      return Reco_LimitsAndFits;
    case 475:
      return Reco_ToleranceValue;
    case 476:
      return Reco_MeasureQualification;
    case 477:
      return Reco_PlusMinusTolerance;
    case 478:
      return Reco_PrecisionQualifier;
    case 479:
      return Reco_TypeQualifier;
    case 480:
      return Reco_QualifiedRepresentationItem;

    case 482:
      return Reco_CompoundRepresentationItem;
    case 483:
      return Reco_ValueRange;
    case 484:
      return Reco_ShapeAspectDerivingRelationship;

    case 485:
      return Reco_CompoundShapeRepresentation;
    case 486:
      return Reco_ConnectedEdgeSet;
    case 487:
      return Reco_ConnectedFaceShapeRepresentation;
    case 488:
      return Reco_EdgeBasedWireframeModel;
    case 489:
      return Reco_EdgeBasedWireframeShapeRepresentation;
    case 490:
      return Reco_FaceBasedSurfaceModel;
    case 491:
      return Reco_NonManifoldSurfaceShapeRepresentation;

    case 492:
      return Reco_OrientedSurface;
    case 493:
      return Reco_Subface;
    case 494:
      return Reco_Subedge;
    case 495:
      return Reco_SeamEdge;
    case 496:
      return Reco_ConnectedFaceSubSet;

    case 500:
      return Reco_EulerAngles;
    case 501:
      return Reco_MassUnit;
    case 502:
      return Reco_ThermodynamicTemperatureUnit;
    case 503:
      return Reco_AnalysisItemWithinRepresentation;
    case 504:
      return Reco_Curve3dElementDescriptor;
    case 505:
      return Reco_CurveElementEndReleasePacket;
    case 506:
      return Reco_CurveElementSectionDefinition;
    case 507:
      return Reco_CurveElementSectionDerivedDefinitions;
    case 508:
      return Reco_ElementDescriptor;
    case 509:
      return Reco_ElementMaterial;
    case 510:
      return Reco_Surface3dElementDescriptor;
    case 511:
      return Reco_SurfaceElementProperty;
    case 512:
      return Reco_SurfaceSection;
    case 513:
      return Reco_SurfaceSectionField;
    case 514:
      return Reco_SurfaceSectionFieldConstant;
    case 515:
      return Reco_SurfaceSectionFieldVarying;
    case 516:
      return Reco_UniformSurfaceSection;
    case 517:
      return Reco_Volume3dElementDescriptor;
    case 518:
      return Reco_AlignedCurve3dElementCoordinateSystem;
    case 519:
      return Reco_ArbitraryVolume3dElementCoordinateSystem;
    case 520:
      return Reco_Curve3dElementProperty;
    case 521:
      return Reco_Curve3dElementRepresentation;
    case 522:
      return Reco_Node;

    case 524:
      return Reco_CurveElementEndOffset;
    case 525:
      return Reco_CurveElementEndRelease;
    case 526:
      return Reco_CurveElementInterval;
    case 527:
      return Reco_CurveElementIntervalConstant;
    case 528:
      return Reco_DummyNode;
    case 529:
      return Reco_CurveElementLocation;
    case 530:
      return Reco_ElementGeometricRelationship;
    case 531:
      return Reco_ElementGroup;
    case 532:
      return Reco_ElementRepresentation;
    case 533:
      return Reco_FeaAreaDensity;
    case 534:
      return Reco_FeaAxis2Placement3d;
    case 535:
      return Reco_FeaGroup;
    case 536:
      return Reco_FeaLinearElasticity;
    case 537:
      return Reco_FeaMassDensity;
    case 538:
      return Reco_FeaMaterialPropertyRepresentation;
    case 539:
      return Reco_FeaMaterialPropertyRepresentationItem;
    case 540:
      return Reco_FeaModel;
    case 541:
      return Reco_FeaModel3d;
    case 542:
      return Reco_FeaMoistureAbsorption;
    case 543:
      return Reco_FeaParametricPoint;
    case 544:
      return Reco_FeaRepresentationItem;
    case 545:
      return Reco_FeaSecantCoefficientOfLinearThermalExpansion;
    case 546:
      return Reco_FeaShellBendingStiffness;
    case 547:
      return Reco_FeaShellMembraneBendingCouplingStiffness;
    case 548:
      return Reco_FeaShellMembraneStiffness;
    case 549:
      return Reco_FeaShellShearStiffness;
    case 550:
      return Reco_GeometricNode;
    case 551:
      return Reco_FeaTangentialCoefficientOfLinearThermalExpansion;
    case 552:
      return Reco_NodeGroup;
    case 553:
      return Reco_NodeRepresentation;
    case 554:
      return Reco_NodeSet;
    case 555:
      return Reco_NodeWithSolutionCoordinateSystem;
    case 556:
      return Reco_NodeWithVector;
    case 557:
      return Reco_ParametricCurve3dElementCoordinateDirection;
    case 558:
      return Reco_ParametricCurve3dElementCoordinateSystem;
    case 559:
      return Reco_ParametricSurface3dElementCoordinateSystem;
    case 560:
      return Reco_Surface3dElementRepresentation;

    case 564:
      return Reco_Volume3dElementRepresentation;
    case 565:
      return Reco_DataEnvironment;
    case 566:
      return Reco_MaterialPropertyRepresentation;
    case 567:
      return Reco_PropertyDefinitionRelationship;
    case 568:
      return Reco_PointRepresentation;
    case 569:
      return Reco_MaterialProperty;
    case 570:
      return Reco_FeaModelDefinition;
    case 571:
      return Reco_FreedomAndCoefficient;
    case 572:
      return Reco_FreedomsList;
    case 573:
      return Reco_ProductDefinitionFormationRelationship;

    case 575:
      return Reco_NodeDefinition;
    case 576:
      return Reco_StructuralResponseProperty;
    case 577:
      return Reco_StructuralResponsePropertyDefinitionRepresentation;
    case 579:
      return Reco_AlignedSurface3dElementCoordinateSystem;
    case 580:
      return Reco_ConstantSurface3dElementCoordinateSystem;
    case 581:
      return Reco_CurveElementIntervalLinearlyVarying;
    case 582:
      return Reco_FeaCurveSectionGeometricRelationship;
    case 583:
      return Reco_FeaSurfaceSectionGeometricRelationship;

    case 600:
      return Reco_DocumentProductAssociation;
    case 601:
      return Reco_DocumentProductEquivalence;

    case 609:
      return Reco_CylindricityTolerance;
    case 610:
      return Reco_ShapeRepresentationWithParameters;
    case 611:
      return Reco_AngularityTolerance;
    case 612:
      return Reco_ConcentricityTolerance;
    case 613:
      return Reco_CircularRunoutTolerance;
    case 614:
      return Reco_CoaxialityTolerance;
    case 615:
      return Reco_FlatnessTolerance;
    case 616:
      return Reco_LineProfileTolerance;
    case 617:
      return Reco_ParallelismTolerance;
    case 618:
      return Reco_PerpendicularityTolerance;
    case 619:
      return Reco_PositionTolerance;
    case 620:
      return Reco_RoundnessTolerance;
    case 621:
      return Reco_StraightnessTolerance;
    case 622:
      return Reco_SurfaceProfileTolerance;
    case 623:
      return Reco_SymmetryTolerance;
    case 624:
      return Reco_TotalRunoutTolerance;
    case 625:
      return Reco_GeometricTolerance;
    case 626:
      return Reco_GeometricToleranceRelationship;
    case 627:
      return Reco_GeometricToleranceWithDatumReference;
    case 628:
      return Reco_ModifiedGeometricTolerance;
    case 629:
      return Reco_Datum;
    case 630:
      return Reco_DatumFeature;
    case 631:
      return Reco_DatumReference;
    case 632:
      return Reco_CommonDatum;
    case 633:
      return Reco_DatumTarget;
    case 634:
      return Reco_PlacedDatumTargetFeature;

    case 651:
      return Reco_MassMeasureWithUnit;

    case 660:
      return Reco_Apex;
    case 661:
      return Reco_CentreOfSymmetry;
    case 662:
      return Reco_GeometricAlignment;
    case 663:
      return Reco_PerpendicularTo;
    case 664:
      return Reco_Tangent;
    case 665:
      return Reco_ParallelOffset;
    case 666:
      return Reco_GeometricItemSpecificUsage;
    case 667:
      return Reco_IdAttribute;
    case 668:
      return Reco_ItemIdentifiedRepresentationUsage;
    case 669:
      return Reco_AllAroundShapeAspect;
    case 670:
      return Reco_BetweenShapeAspect;
    case 671:
      return Reco_CompositeGroupShapeAspect;
    case 672:
      return Reco_ContinuosShapeAspect;
    case 673:
      return Reco_GeometricToleranceWithDefinedAreaUnit;
    case 674:
      return Reco_GeometricToleranceWithDefinedUnit;
    case 675:
      return Reco_GeometricToleranceWithMaximumTolerance;
    case 676:
      return Reco_GeometricToleranceWithModifiers;
    case 677:
      return Reco_UnequallyDisposedGeometricTolerance;
    case 678:
      return Reco_NonUniformZoneDefinition;
    case 679:
      return Reco_ProjectedZoneDefinition;
    case 680:
      return Reco_RunoutZoneDefinition;
    case 681:
      return Reco_RunoutZoneOrientation;
    case 682:
      return Reco_ToleranceZone;
    case 683:
      return Reco_ToleranceZoneDefinition;
    case 684:
      return Reco_ToleranceZoneForm;
    case 685:
      return Reco_ValueFormatTypeQualifier;
    case 686:
      return Reco_DatumReferenceCompartment;
    case 687:
      return Reco_DatumReferenceElement;
    case 688:
      return Reco_DatumReferenceModifierWithValue;
    case 689:
      return Reco_DatumSystem;
    case 690:
      return Reco_GeneralDatumReference;
    case 700:
      return Reco_IntegerRepresentationItem;
    case 701:
      return Reco_ValueRepresentationItem;
    case 702:
      return Reco_FeatureForDatumTargetRelationship;
    case 703:
      return Reco_DraughtingModelItemAssociation;
    case 704:
      return Reco_AnnotationPlane;

    case 707:
      return Reco_TessellatedAnnotationOccurrence;
    case 708:
      return Reco_TessellatedItem;
    case 709:
      return Reco_TessellatedGeometricSet;

    case 710:
      return Reco_TessellatedCurveSet;
    case 711:
      return Reco_CoordinatesList;
    case 712:
      return Reco_ConstructiveGeometryRepresentation;
    case 713:
      return Reco_ConstructiveGeometryRepresentationRelationship;
    case 714:
      return Reco_CharacterizedRepresentation;
    case 716:
      return Reco_CameraModelD3MultiClipping;
    case 717:
      return Reco_CameraModelD3MultiClippingIntersection;
    case 718:
      return Reco_CameraModelD3MultiClippingUnion;

    case 720:
      return Reco_SurfaceStyleTransparent;
    case 721:
      return Reco_SurfaceStyleReflectanceAmbient;
    case 722:
      return Reco_SurfaceStyleRendering;
    case 723:
      return Reco_SurfaceStyleRenderingWithProperties;

    case 724:
      return Reco_RepresentationContextReference;
    case 725:
      return Reco_RepresentationReference;
    case 726:
      return Reco_SuParameters;
    case 727:
      return Reco_RotationAboutDirection;
    case 728:
      return Reco_KinematicJoint;
    case 729:
      return Reco_ActuatedKinematicPair;
    case 730:
      return Reco_ContextDependentKinematicLinkRepresentation;
    case 731:
      return Reco_CylindricalPair;
    case 732:
      return Reco_CylindricalPairValue;
    case 733:
      return Reco_CylindricalPairWithRange;
    case 734:
      return Reco_FullyConstrainedPair;
    case 735:
      return Reco_GearPair;
    case 736:
      return Reco_GearPairValue;
    case 737:
      return Reco_GearPairWithRange;
    case 738:
      return Reco_HomokineticPair;
    case 739:
      return Reco_KinematicLink;
    case 740:
      return Reco_KinematicLinkRepresentationAssociation;
    case 741:
      return Reco_KinematicPropertyMechanismRepresentation;
    case 742:
      return Reco_KinematicTopologyStructure;
    case 743:
      return Reco_LowOrderKinematicPair;
    case 744:
      return Reco_LowOrderKinematicPairValue;
    case 745:
      return Reco_LowOrderKinematicPairWithRange;
    case 746:
      return Reco_MechanismRepresentation;
    case 747:
      return Reco_OrientedJoint;
    case 748:
      return Reco_PlanarCurvePair;
    case 749:
      return Reco_PlanarCurvePairRange;
    case 750:
      return Reco_PlanarPair;
    case 751:
      return Reco_PlanarPairValue;
    case 752:
      return Reco_PlanarPairWithRange;
    case 753:
      return Reco_PointOnPlanarCurvePair;
    case 754:
      return Reco_PointOnPlanarCurvePairValue;
    case 755:
      return Reco_PointOnPlanarCurvePairWithRange;
    case 756:
      return Reco_PointOnSurfacePair;
    case 757:
      return Reco_PointOnSurfacePairValue;
    case 758:
      return Reco_PointOnSurfacePairWithRange;
    case 759:
      return Reco_PrismaticPair;
    case 760:
      return Reco_PrismaticPairValue;
    case 761:
      return Reco_PrismaticPairWithRange;
    case 762:
      return Reco_ProductDefinitionKinematics;
    case 763:
      return Reco_ProductDefinitionRelationshipKinematics;
    case 764:
      return Reco_RackAndPinionPair;
    case 765:
      return Reco_RackAndPinionPairValue;
    case 766:
      return Reco_RackAndPinionPairWithRange;
    case 767:
      return Reco_RevolutePair;
    case 768:
      return Reco_RevolutePairValue;
    case 769:
      return Reco_RevolutePairWithRange;
    case 770:
      return Reco_RollingCurvePair;
    case 771:
      return Reco_RollingCurvePairValue;
    case 772:
      return Reco_RollingSurfacePair;
    case 773:
      return Reco_RollingSurfacePairValue;
    case 774:
      return Reco_ScrewPair;
    case 775:
      return Reco_ScrewPairValue;
    case 776:
      return Reco_ScrewPairWithRange;
    case 777:
      return Reco_SlidingCurvePair;
    case 778:
      return Reco_SlidingCurvePairValue;
    case 779:
      return Reco_SlidingSurfacePair;
    case 780:
      return Reco_SlidingSurfacePairValue;
    case 781:
      return Reco_SphericalPair;
    case 782:
      return Reco_SphericalPairValue;
    case 783:
      return Reco_SphericalPairWithPin;
    case 784:
      return Reco_SphericalPairWithPinAndRange;
    case 785:
      return Reco_SphericalPairWithRange;
    case 786:
      return Reco_SurfacePairWithRange;
    case 787:
      return Reco_UnconstrainedPair;
    case 788:
      return Reco_UnconstrainedPairValue;
    case 789:
      return Reco_UniversalPair;
    case 790:
      return Reco_UniversalPairValue;
    case 791:
      return Reco_UniversalPairWithRange;
    case 792:
      return Reco_PairRepresentationRelationship;
    case 793:
      return Reco_RigidLinkRepresentation;
    case 794:
      return Reco_KinematicTopologyDirectedStructure;
    case 795:
      return Reco_KinematicTopologyNetworkStructure;
    case 796:
      return Reco_LinearFlexibleAndPinionPair;
    case 797:
      return Reco_LinearFlexibleAndPlanarCurvePair;
    case 798:
      return Reco_LinearFlexibleLinkRepresentation;
    case 799:
      return Reco_KinematicPair;
    case 801:
      return Reco_MechanismStateRepresentation;
    case 803:
      return Reco_RepositionedTessellatedItem;
    case 804:
      return Reco_TessellatedConnectingEdge;
    case 805:
      return Reco_TessellatedEdge;
    case 806:
      return Reco_TessellatedPointSet;
    case 807:
      return Reco_TessellatedShapeRepresentation;
    case 808:
      return Reco_TessellatedShapeRepresentationWithAccuracyParameters;
    case 809:
      return Reco_TessellatedShell;
    case 810:
      return Reco_TessellatedSolid;
    case 811:
      return Reco_TessellatedStructuredItem;
    case 812:
      return Reco_TessellatedVertex;
    case 813:
      return Reco_TessellatedWire;
    case 814:
      return Reco_TriangulatedFace;
    case 815:
      return Reco_ComplexTriangulatedFace;
    case 816:
      return Reco_ComplexTriangulatedSurfaceSet;
    case 817:
      return Reco_CubicBezierTessellatedEdge;
    case 818:
      return Reco_CubicBezierTriangulatedFace;
    case 819:
      return Reco_TriangulatedSurfaceSet;
    case 820:
      return Reco_GeneralPropertyAssociation;
    case 821:
      return Reco_GeneralPropertyRelationship;
    case 822:
      return Reco_BooleanRepresentationItem;
    case 823:
      return Reco_RealRepresentationItem;
    case 824:
      return Reco_MechanicalDesignAndDraughtingRelationship;
    default:
      return PasReco;
  }
}

bool RWStepAP214_ReadWriteModule::ComplexType(
  const int                                      CN,
  NCollection_Sequence<TCollection_AsciiString>& types) const
{
  switch (CN)
  {
    case 319:
      types.Append(TCollection_AsciiString(StepType(48)));
      types.Append(TCollection_AsciiString(StepType(38)));
      types.Append(TCollection_AsciiString(StepType(84)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(239)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(311)));
      break;
    case 320:
      types.Append(TCollection_AsciiString(StepType(48)));
      types.Append(TCollection_AsciiString(StepType(38)));
      types.Append(TCollection_AsciiString(StepType(39)));
      types.Append(TCollection_AsciiString(StepType(84)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(239)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 321:
      types.Append(TCollection_AsciiString(StepType(48)));
      types.Append(TCollection_AsciiString(StepType(38)));
      types.Append(TCollection_AsciiString(StepType(84)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(236)));
      types.Append(TCollection_AsciiString(StepType(239)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 322:
      types.Append(TCollection_AsciiString(StepType(43)));
      types.Append(TCollection_AsciiString(StepType(48)));
      types.Append(TCollection_AsciiString(StepType(38)));
      types.Append(TCollection_AsciiString(StepType(84)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(239)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 323:
      types.Append(TCollection_AsciiString(StepType(49)));
      types.Append(TCollection_AsciiString(StepType(40)));
      types.Append(TCollection_AsciiString(StepType(41)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(240)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(271)));
      break;
    case 324:
      types.Append(TCollection_AsciiString(StepType(49)));
      types.Append(TCollection_AsciiString(StepType(40)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(240)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(271)));
      types.Append(TCollection_AsciiString(StepType(312)));
      break;
    case 325:
      types.Append(TCollection_AsciiString(StepType(49)));
      types.Append(TCollection_AsciiString(StepType(40)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(237)));
      types.Append(TCollection_AsciiString(StepType(240)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(271)));
      break;
    case 326:
      types.Append(TCollection_AsciiString(StepType(44)));
      types.Append(TCollection_AsciiString(StepType(49)));
      types.Append(TCollection_AsciiString(StepType(40)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(240)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(271)));
      break;
    case 327:
      types.Append(TCollection_AsciiString(StepType(158)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      break;
    case 328:
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(201)));
      types.Append(TCollection_AsciiString(StepType(264)));
      break;
    case 329:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(158)));
      types.Append(TCollection_AsciiString(StepType(169)));
      break;
    case 330:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(201)));
      break;
    case 331:
      types.Append(TCollection_AsciiString(StepType(143)));
      types.Append(TCollection_AsciiString(StepType(149)));
      types.Append(TCollection_AsciiString(StepType(246)));
      break;
    case 332:
      types.Append(TCollection_AsciiString(StepType(161)));
      types.Append(TCollection_AsciiString(StepType(189)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(304)));
      break;
    case 333:
      types.Append(TCollection_AsciiString(StepType(143)));
      types.Append(TCollection_AsciiString(StepType(148)));
      types.Append(TCollection_AsciiString(StepType(149)));
      types.Append(TCollection_AsciiString(StepType(246)));
      break;
    case 334:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(336)));
      break;
    case 335:
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      types.Append(TCollection_AsciiString(StepType(336)));
      break;
    case 337:
      types.Append(TCollection_AsciiString(StepType(52)));
      types.Append(TCollection_AsciiString(StepType(134)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(162)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(266)));
      break;
    case 338:
      types.Append(TCollection_AsciiString(StepType(143)));
      types.Append(TCollection_AsciiString(StepType(188)));
      types.Append(TCollection_AsciiString(StepType(246)));
      break;
    case 344:
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(342)));
      types.Append(TCollection_AsciiString(StepType(264)));
      break;
    case 345:
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      types.Append(TCollection_AsciiString(StepType(343)));
      break;
    case 346:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(342)));
      break;
    case 347:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(343)));
      break;
    case 357:
      types.Append(TCollection_AsciiString(StepType(157)));
      types.Append(TCollection_AsciiString(StepType(165)));
      types.Append(TCollection_AsciiString(StepType(310)));
      break;
    case 358:
      types.Append(TCollection_AsciiString(StepType(48)));
      types.Append(TCollection_AsciiString(StepType(84)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(272)));
      break;
    case 389:
      types.Append(TCollection_AsciiString(StepType(249)));
      types.Append(TCollection_AsciiString(StepType(388)));
      types.Append(TCollection_AsciiString(StepType(387)));
      break;
    case 409:
      types.Append(TCollection_AsciiString(StepType(407)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      break;
    case 410:
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      types.Append(TCollection_AsciiString(StepType(408)));
      break;
    case 411:
      types.Append(TCollection_AsciiString(StepType(407)));
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(169)));
      break;
    case 412:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(408)));
      break;
    case 463:
      types.Append(TCollection_AsciiString(StepType(98)));
      types.Append(TCollection_AsciiString(StepType(245)));
      types.Append(TCollection_AsciiString(StepType(262)));
      break;
    case 481:
      types.Append(TCollection_AsciiString(StepType(406)));
      types.Append(TCollection_AsciiString(StepType(480)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 574:
      types.Append(TCollection_AsciiString(StepType(501)));
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      break;
    case 578:
      types.Append(TCollection_AsciiString(StepType(169)));
      types.Append(TCollection_AsciiString(StepType(264)));
      types.Append(TCollection_AsciiString(StepType(502)));
      break;
    case 635:
      types.Append(TCollection_AsciiString(StepType(157)));
      types.Append(TCollection_AsciiString(StepType(406)));
      types.Append(TCollection_AsciiString(StepType(165)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 636:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(627)));
      types.Append(TCollection_AsciiString(StepType(628)));
      types.Append(TCollection_AsciiString(StepType(619)));
      break;
    case 650:
      types.Append(TCollection_AsciiString(StepType(79)));
      types.Append(TCollection_AsciiString(StepType(501)));
      types.Append(TCollection_AsciiString(StepType(169)));
      break;
    case 691:
      types.Append(TCollection_AsciiString(StepType(406)));
      types.Append(TCollection_AsciiString(StepType(165)));
      types.Append(TCollection_AsciiString(StepType(200)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 692:
      types.Append(TCollection_AsciiString(StepType(157)));
      types.Append(TCollection_AsciiString(StepType(406)));
      types.Append(TCollection_AsciiString(StepType(165)));
      types.Append(TCollection_AsciiString(StepType(480)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 693:
      types.Append(TCollection_AsciiString(StepType(406)));
      types.Append(TCollection_AsciiString(StepType(165)));
      types.Append(TCollection_AsciiString(StepType(200)));
      types.Append(TCollection_AsciiString(StepType(480)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 694:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(627)));
      types.Append(TCollection_AsciiString(StepType(625)));
      break;
    case 695:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(627)));
      types.Append(TCollection_AsciiString(StepType(676)));
      types.Append(TCollection_AsciiString(StepType(625)));
      break;
    case 696:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(676)));
      types.Append(TCollection_AsciiString(StepType(625)));
      break;
    case 697:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(627)));
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(677)));
      break;
    case 698:
      types.Append(TCollection_AsciiString(StepType(671)));
      types.Append(TCollection_AsciiString(StepType(470)));
      types.Append(TCollection_AsciiString(StepType(630)));
      types.Append(TCollection_AsciiString(StepType(258)));
      break;
    case 699:
      types.Append(TCollection_AsciiString(StepType(470)));
      types.Append(TCollection_AsciiString(StepType(630)));
      types.Append(TCollection_AsciiString(StepType(258)));
      break;
    case 705:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(627)));
      types.Append(TCollection_AsciiString(StepType(675)));
      types.Append(TCollection_AsciiString(StepType(676)));
      types.Append(TCollection_AsciiString(StepType(625)));
      break;
    case 706:
      types.Append(TCollection_AsciiString(StepType(625)));
      types.Append(TCollection_AsciiString(StepType(675)));
      types.Append(TCollection_AsciiString(StepType(676)));
      types.Append(TCollection_AsciiString(StepType(625)));
      break;
    case 715:
      types.Append(TCollection_AsciiString(StepType(402)));
      types.Append(TCollection_AsciiString(StepType(714)));
      types.Append(TCollection_AsciiString(StepType(441)));
      types.Append(TCollection_AsciiString(StepType(245)));
      break;
    case 719:
      types.Append(TCollection_AsciiString(StepType(4)));
      types.Append(TCollection_AsciiString(StepType(7)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(270)));
      break;
    case 800:
      types.Append(TCollection_AsciiString(StepType(729)));
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(354)));
      types.Append(TCollection_AsciiString(StepType(799)));
      types.Append(TCollection_AsciiString(StepType(743)));
      types.Append(TCollection_AsciiString(StepType(757)));
      types.Append(TCollection_AsciiString(StepType(759)));
      types.Append(TCollection_AsciiString(StepType(247)));
      break;
    case 802:
      types.Append(TCollection_AsciiString(StepType(144)));
      types.Append(TCollection_AsciiString(StepType(803)));
      types.Append(TCollection_AsciiString(StepType(247)));
      types.Append(TCollection_AsciiString(StepType(709)));
      types.Append(TCollection_AsciiString(StepType(708)));
      break;
    default:
      return false;
  }
  return true;
}

void RWStepAP214_ReadWriteModule::ReadStep(const int                                   CN,
                                           const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<Standard_Transient>&      ent) const
{
  if (CN == 0)
  {
#ifdef OCCT_DEBUG
    std::cout << "CN = 0 for num = " << num << std::endl;
#endif
    return;
  }
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(StepBasic_Address, anent, ent);
      RWStepBasic_RWAddress tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 2:
    {
      DeclareAndCast(StepShape_AdvancedBrepShapeRepresentation, anent, ent);
      RWStepShape_RWAdvancedBrepShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 3:
    {
      DeclareAndCast(StepShape_AdvancedFace, anent, ent);
      RWStepShape_RWAdvancedFace tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 4:
    {
      DeclareAndCast(StepVisual_AnnotationCurveOccurrence, anent, ent);
      RWStepVisual_RWAnnotationCurveOccurrence tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 5:
    {
      DeclareAndCast(StepVisual_AnnotationFillArea, anent, ent);
      RWStepVisual_RWAnnotationFillArea tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 6:
    {
      DeclareAndCast(StepVisual_AnnotationFillAreaOccurrence, anent, ent);
      RWStepVisual_RWAnnotationFillAreaOccurrence tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 7:
    {
      DeclareAndCast(StepVisual_AnnotationOccurrence, anent, ent);
      RWStepVisual_RWAnnotationOccurrence tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 11:
    {
      DeclareAndCast(StepRepr_MappedItem, anent, ent);
      RWStepRepr_RWMappedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 12:
    {
      DeclareAndCast(StepVisual_StyledItem, anent, ent);
      RWStepVisual_RWStyledItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 13:
    {
      DeclareAndCast(StepBasic_ApplicationContext, anent, ent);
      RWStepBasic_RWApplicationContext tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 14:
    {
      DeclareAndCast(StepBasic_ApplicationContextElement, anent, ent);
      RWStepBasic_RWApplicationContextElement tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 15:
    {
      DeclareAndCast(StepBasic_ApplicationProtocolDefinition, anent, ent);
      RWStepBasic_RWApplicationProtocolDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 16:
    {
      DeclareAndCast(StepBasic_Approval, anent, ent);
      RWStepBasic_RWApproval tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 18:
    {
      DeclareAndCast(StepBasic_ApprovalPersonOrganization, anent, ent);
      RWStepBasic_RWApprovalPersonOrganization tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 19:
    {
      DeclareAndCast(StepBasic_ApprovalRelationship, anent, ent);
      RWStepBasic_RWApprovalRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 20:
    {
      DeclareAndCast(StepBasic_ApprovalRole, anent, ent);
      RWStepBasic_RWApprovalRole tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 21:
    {
      DeclareAndCast(StepBasic_ApprovalStatus, anent, ent);
      RWStepBasic_RWApprovalStatus tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 22:
    {
      DeclareAndCast(StepVisual_AreaInSet, anent, ent);
      RWStepVisual_RWAreaInSet tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 23:
    {
      DeclareAndCast(StepAP214_AutoDesignActualDateAndTimeAssignment, anent, ent);
      RWStepAP214_RWAutoDesignActualDateAndTimeAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 24:
    {
      DeclareAndCast(StepAP214_AutoDesignActualDateAssignment, anent, ent);
      RWStepAP214_RWAutoDesignActualDateAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 25:
    {
      DeclareAndCast(StepAP214_AutoDesignApprovalAssignment, anent, ent);
      RWStepAP214_RWAutoDesignApprovalAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 26:
    {
      DeclareAndCast(StepAP214_AutoDesignDateAndPersonAssignment, anent, ent);
      RWStepAP214_RWAutoDesignDateAndPersonAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 27:
    {
      DeclareAndCast(StepAP214_AutoDesignGroupAssignment, anent, ent);
      RWStepAP214_RWAutoDesignGroupAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 28:
    {
      DeclareAndCast(StepAP214_AutoDesignNominalDateAndTimeAssignment, anent, ent);
      RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 29:
    {
      DeclareAndCast(StepAP214_AutoDesignNominalDateAssignment, anent, ent);
      RWStepAP214_RWAutoDesignNominalDateAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 30:
    {
      DeclareAndCast(StepAP214_AutoDesignOrganizationAssignment, anent, ent);
      RWStepAP214_RWAutoDesignOrganizationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 31:
    {
      DeclareAndCast(StepAP214_AutoDesignPersonAndOrganizationAssignment, anent, ent);
      RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 32:
    {
      DeclareAndCast(StepAP214_AutoDesignPresentedItem, anent, ent);
      RWStepAP214_RWAutoDesignPresentedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 33:
    {
      DeclareAndCast(StepAP214_AutoDesignSecurityClassificationAssignment, anent, ent);
      RWStepAP214_RWAutoDesignSecurityClassificationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 35:
    {
      DeclareAndCast(StepGeom_Axis1Placement, anent, ent);
      RWStepGeom_RWAxis1Placement tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 36:
    {
      DeclareAndCast(StepGeom_Axis2Placement2d, anent, ent);
      RWStepGeom_RWAxis2Placement2d tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 37:
    {
      DeclareAndCast(StepGeom_Axis2Placement3d, anent, ent);
      RWStepGeom_RWAxis2Placement3d tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 38:
    {
      DeclareAndCast(StepGeom_BSplineCurve, anent, ent);
      RWStepGeom_RWBSplineCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 39:
    {
      DeclareAndCast(StepGeom_BSplineCurveWithKnots, anent, ent);
      RWStepGeom_RWBSplineCurveWithKnots tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 40:
    {
      DeclareAndCast(StepGeom_BSplineSurface, anent, ent);
      RWStepGeom_RWBSplineSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 41:
    {
      DeclareAndCast(StepGeom_BSplineSurfaceWithKnots, anent, ent);
      RWStepGeom_RWBSplineSurfaceWithKnots tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 42:
    {
      DeclareAndCast(StepVisual_BackgroundColour, anent, ent);
      RWStepVisual_RWBackgroundColour tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 43:
    {
      DeclareAndCast(StepGeom_BezierCurve, anent, ent);
      RWStepGeom_RWBezierCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 44:
    {
      DeclareAndCast(StepGeom_BezierSurface, anent, ent);
      RWStepGeom_RWBezierSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 45:
    {
      DeclareAndCast(StepShape_Block, anent, ent);
      RWStepShape_RWBlock tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 46:
    {
      DeclareAndCast(StepShape_BooleanResult, anent, ent);
      RWStepShape_RWBooleanResult tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 47:
    {
      DeclareAndCast(StepGeom_BoundaryCurve, anent, ent);
      RWStepGeom_RWBoundaryCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 48:
    {
      DeclareAndCast(StepGeom_BoundedCurve, anent, ent);
      RWStepGeom_RWBoundedCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 49:
    {
      DeclareAndCast(StepGeom_BoundedSurface, anent, ent);
      RWStepGeom_RWBoundedSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 50:
    {
      DeclareAndCast(StepShape_BoxDomain, anent, ent);
      RWStepShape_RWBoxDomain tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 51:
    {
      DeclareAndCast(StepShape_BoxedHalfSpace, anent, ent);
      RWStepShape_RWBoxedHalfSpace tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 52:
    {
      DeclareAndCast(StepShape_BrepWithVoids, anent, ent);
      RWStepShape_RWBrepWithVoids tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 53:
    {
      DeclareAndCast(StepBasic_CalendarDate, anent, ent);
      RWStepBasic_RWCalendarDate tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 54:
    {
      DeclareAndCast(StepVisual_CameraImage, anent, ent);
      RWStepVisual_RWCameraImage tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 55:
    {
      DeclareAndCast(StepVisual_CameraModel, anent, ent);
      RWStepVisual_RWCameraModel tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 56:
    {
      DeclareAndCast(StepVisual_CameraModelD2, anent, ent);
      RWStepVisual_RWCameraModelD2 tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 57:
    {
      DeclareAndCast(StepVisual_CameraModelD3, anent, ent);
      RWStepVisual_RWCameraModelD3 tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 58:
    {
      DeclareAndCast(StepVisual_CameraUsage, anent, ent);
      RWStepVisual_RWCameraUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 59:
    {
      DeclareAndCast(StepGeom_CartesianPoint, anent, ent);
      RWStepGeom_RWCartesianPoint tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 60:
    {
      DeclareAndCast(StepGeom_CartesianTransformationOperator, anent, ent);
      RWStepGeom_RWCartesianTransformationOperator tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 61:
    {
      DeclareAndCast(StepGeom_CartesianTransformationOperator3d, anent, ent);
      RWStepGeom_RWCartesianTransformationOperator3d tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 62:
    {
      DeclareAndCast(StepGeom_Circle, anent, ent);
      RWStepGeom_RWCircle tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 63:
    {
      DeclareAndCast(StepShape_ClosedShell, anent, ent);
      RWStepShape_RWClosedShell tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 64:
    {
      DeclareAndCast(StepVisual_Colour, anent, ent);
      RWStepVisual_RWColour tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 65:
    {
      DeclareAndCast(StepVisual_ColourRgb, anent, ent);
      RWStepVisual_RWColourRgb tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 66:
    {
      DeclareAndCast(StepVisual_ColourSpecification, anent, ent);
      RWStepVisual_RWColourSpecification tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 67:
    {
      DeclareAndCast(StepGeom_CompositeCurve, anent, ent);
      RWStepGeom_RWCompositeCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 68:
    {
      DeclareAndCast(StepGeom_CompositeCurveOnSurface, anent, ent);
      RWStepGeom_RWCompositeCurveOnSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 69:
    {
      DeclareAndCast(StepGeom_CompositeCurveSegment, anent, ent);
      RWStepGeom_RWCompositeCurveSegment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 70:
    {
      DeclareAndCast(StepVisual_CompositeText, anent, ent);
      RWStepVisual_RWCompositeText tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 73:
    {
      DeclareAndCast(StepVisual_CompositeTextWithExtent, anent, ent);
      RWStepVisual_RWCompositeTextWithExtent tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 74:
    {
      DeclareAndCast(StepGeom_Conic, anent, ent);
      RWStepGeom_RWConic tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 75:
    {
      DeclareAndCast(StepGeom_ConicalSurface, anent, ent);
      RWStepGeom_RWConicalSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 76:
    {
      DeclareAndCast(StepShape_ConnectedFaceSet, anent, ent);
      RWStepShape_RWConnectedFaceSet tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 77:
    {
      DeclareAndCast(StepVisual_ContextDependentInvisibility, anent, ent);
      RWStepVisual_RWContextDependentInvisibility tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 78:
    {
      DeclareAndCast(StepVisual_ContextDependentOverRidingStyledItem, anent, ent);
      RWStepVisual_RWContextDependentOverRidingStyledItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 79:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 80:
    {
      DeclareAndCast(StepBasic_CoordinatedUniversalTimeOffset, anent, ent);
      RWStepBasic_RWCoordinatedUniversalTimeOffset tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 82:
    {
      DeclareAndCast(StepShape_CsgShapeRepresentation, anent, ent);
      RWStepShape_RWCsgShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 83:
    {
      DeclareAndCast(StepShape_CsgSolid, anent, ent);
      RWStepShape_RWCsgSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 84:
    {
      DeclareAndCast(StepGeom_Curve, anent, ent);
      RWStepGeom_RWCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 85:
    {
      DeclareAndCast(StepGeom_CurveBoundedSurface, anent, ent);
      RWStepGeom_RWCurveBoundedSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 86:
    {
      DeclareAndCast(StepGeom_CurveReplica, anent, ent);
      RWStepGeom_RWCurveReplica tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 87:
    {
      DeclareAndCast(StepVisual_CurveStyle, anent, ent);
      RWStepVisual_RWCurveStyle tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 88:
    {
      DeclareAndCast(StepVisual_CurveStyleFont, anent, ent);
      RWStepVisual_RWCurveStyleFont tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 89:
    {
      DeclareAndCast(StepVisual_CurveStyleFontPattern, anent, ent);
      RWStepVisual_RWCurveStyleFontPattern tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 90:
    {
      DeclareAndCast(StepGeom_CylindricalSurface, anent, ent);
      RWStepGeom_RWCylindricalSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 91:
    {
      DeclareAndCast(StepBasic_Date, anent, ent);
      RWStepBasic_RWDate tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 92:
    {
      DeclareAndCast(StepBasic_DateAndTime, anent, ent);
      RWStepBasic_RWDateAndTime tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 95:
    {
      DeclareAndCast(StepBasic_DateRole, anent, ent);
      RWStepBasic_RWDateRole tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 96:
    {
      DeclareAndCast(StepBasic_DateTimeRole, anent, ent);
      RWStepBasic_RWDateTimeRole tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 98:
    {
      DeclareAndCast(StepRepr_DefinitionalRepresentation, anent, ent);
      RWStepRepr_RWDefinitionalRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 99:
    {
      DeclareAndCast(StepGeom_DegeneratePcurve, anent, ent);
      RWStepGeom_RWDegeneratePcurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 100:
    {
      DeclareAndCast(StepGeom_DegenerateToroidalSurface, anent, ent);
      RWStepGeom_RWDegenerateToroidalSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 101:
    {
      DeclareAndCast(StepRepr_DescriptiveRepresentationItem, anent, ent);
      RWStepRepr_RWDescriptiveRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 104:
    {
      DeclareAndCast(StepBasic_DimensionalExponents, anent, ent);
      RWStepBasic_RWDimensionalExponents tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 105:
    {
      DeclareAndCast(StepGeom_Direction, anent, ent);
      RWStepGeom_RWDirection tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 106:
    {
      DeclareAndCast(StepVisual_StyledItem, anent, ent);
      RWStepVisual_RWStyledItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 107:
    {
      DeclareAndCast(StepVisual_DraughtingCallout, anent, ent);
      RWStepVisual_RWDraughtingCallout tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 108:
    {
      DeclareAndCast(StepVisual_DraughtingPreDefinedColour, anent, ent);
      RWStepVisual_RWDraughtingPreDefinedColour tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 109:
    {
      DeclareAndCast(StepVisual_DraughtingPreDefinedCurveFont, anent, ent);
      RWStepVisual_RWDraughtingPreDefinedCurveFont tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 115:
    {
      DeclareAndCast(StepShape_Edge, anent, ent);
      RWStepShape_RWEdge tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 116:
    {
      DeclareAndCast(StepShape_EdgeCurve, anent, ent);
      RWStepShape_RWEdgeCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 117:
    {
      DeclareAndCast(StepShape_EdgeLoop, anent, ent);
      RWStepShape_RWEdgeLoop tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 118:
    {
      DeclareAndCast(StepGeom_ElementarySurface, anent, ent);
      RWStepGeom_RWElementarySurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 119:
    {
      DeclareAndCast(StepGeom_Ellipse, anent, ent);
      RWStepGeom_RWEllipse tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 120:
    {
      DeclareAndCast(StepGeom_EvaluatedDegeneratePcurve, anent, ent);
      RWStepGeom_RWEvaluatedDegeneratePcurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 121:
    {
      DeclareAndCast(StepBasic_ExternalSource, anent, ent);
      RWStepBasic_RWExternalSource tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 122:
    {
      DeclareAndCast(StepVisual_ExternallyDefinedCurveFont, anent, ent);
      RWStepVisual_RWExternallyDefinedCurveFont tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 124:
    case 126:
    {
      DeclareAndCast(StepBasic_ExternallyDefinedItem, anent, ent);
      RWStepBasic_RWExternallyDefinedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 128:
    {
      DeclareAndCast(StepShape_ExtrudedAreaSolid, anent, ent);
      RWStepShape_RWExtrudedAreaSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 129:
    {
      DeclareAndCast(StepShape_Face, anent, ent);
      RWStepShape_RWFace tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 131:
    {
      DeclareAndCast(StepShape_FaceBound, anent, ent);
      RWStepShape_RWFaceBound tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 132:
    {
      DeclareAndCast(StepShape_FaceOuterBound, anent, ent);
      RWStepShape_RWFaceOuterBound tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 133:
    {
      DeclareAndCast(StepShape_FaceSurface, anent, ent);
      RWStepShape_RWFaceSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 134:
    {
      DeclareAndCast(StepShape_FacetedBrep, anent, ent);
      RWStepShape_RWFacetedBrep tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 135:
    {
      DeclareAndCast(StepShape_FacetedBrepShapeRepresentation, anent, ent);
      RWStepShape_RWFacetedBrepShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 136:
    {
      DeclareAndCast(StepVisual_FillAreaStyle, anent, ent);
      RWStepVisual_RWFillAreaStyle tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 137:
    {
      DeclareAndCast(StepVisual_FillAreaStyleColour, anent, ent);
      RWStepVisual_RWFillAreaStyleColour tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 141:
    {
      DeclareAndCast(StepRepr_FunctionallyDefinedTransformation, anent, ent);
      RWStepRepr_RWFunctionallyDefinedTransformation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 142:
    {
      DeclareAndCast(StepShape_GeometricCurveSet, anent, ent);
      RWStepShape_RWGeometricCurveSet tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 143:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContext, anent, ent);
      RWStepGeom_RWGeometricRepresentationContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 144:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationItem, anent, ent);
      RWStepGeom_RWGeometricRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 145:
    {
      DeclareAndCast(StepShape_GeometricSet, anent, ent);
      RWStepShape_RWGeometricSet tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 146:
    {
      DeclareAndCast(StepShape_GeometricallyBoundedSurfaceShapeRepresentation, anent, ent);
      RWStepShape_RWGeometricallyBoundedSurfaceShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 147:
    {
      DeclareAndCast(StepShape_GeometricallyBoundedWireframeShapeRepresentation, anent, ent);
      RWStepShape_RWGeometricallyBoundedWireframeShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 148:
    {
      DeclareAndCast(StepRepr_GlobalUncertaintyAssignedContext, anent, ent);
      RWStepRepr_RWGlobalUncertaintyAssignedContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 149:
    {
      DeclareAndCast(StepRepr_GlobalUnitAssignedContext, anent, ent);
      RWStepRepr_RWGlobalUnitAssignedContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 150:
    {
      DeclareAndCast(StepBasic_Group, anent, ent);
      RWStepBasic_RWGroup tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 152:
    {
      DeclareAndCast(StepBasic_GroupRelationship, anent, ent);
      RWStepBasic_RWGroupRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 153:
    {
      DeclareAndCast(StepShape_HalfSpaceSolid, anent, ent);
      RWStepShape_RWHalfSpaceSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 154:
    {
      DeclareAndCast(StepGeom_Hyperbola, anent, ent);
      RWStepGeom_RWHyperbola tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 155:
    {
      DeclareAndCast(StepGeom_IntersectionCurve, anent, ent);
      RWStepGeom_RWIntersectionCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 156:
    {
      DeclareAndCast(StepVisual_Invisibility, anent, ent);
      RWStepVisual_RWInvisibility tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 157:
    {
      DeclareAndCast(StepBasic_LengthMeasureWithUnit, anent, ent);
      RWStepBasic_RWLengthMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 158:
    {
      DeclareAndCast(StepBasic_LengthUnit, anent, ent);
      RWStepBasic_RWLengthUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 159:
    {
      DeclareAndCast(StepGeom_Line, anent, ent);
      RWStepGeom_RWLine tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 160:
    {
      DeclareAndCast(StepBasic_LocalTime, anent, ent);
      RWStepBasic_RWLocalTime tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 161:
    {
      DeclareAndCast(StepShape_Loop, anent, ent);
      RWStepShape_RWLoop tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 162:
    {
      DeclareAndCast(StepShape_ManifoldSolidBrep, anent, ent);
      RWStepShape_RWManifoldSolidBrep tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 163:
    {
      DeclareAndCast(StepShape_ManifoldSurfaceShapeRepresentation, anent, ent);
      RWStepShape_RWManifoldSurfaceShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 164:
    {
      DeclareAndCast(StepRepr_MappedItem, anent, ent);
      RWStepRepr_RWMappedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 165:
    {
      DeclareAndCast(StepBasic_MeasureWithUnit, anent, ent);
      RWStepBasic_RWMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 166:
    {
      DeclareAndCast(StepVisual_MechanicalDesignGeometricPresentationArea, anent, ent);
      RWStepVisual_RWMechanicalDesignGeometricPresentationArea tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 167:
    {
      DeclareAndCast(StepVisual_MechanicalDesignGeometricPresentationRepresentation, anent, ent);
      RWStepVisual_RWMechanicalDesignGeometricPresentationRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 169:
    {
      DeclareAndCast(StepBasic_NamedUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 171:
    {
      DeclareAndCast(StepGeom_OffsetCurve3d, anent, ent);
      RWStepGeom_RWOffsetCurve3d tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 172:
    {
      DeclareAndCast(StepGeom_OffsetSurface, anent, ent);
      RWStepGeom_RWOffsetSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 174:
    {
      DeclareAndCast(StepShape_OpenShell, anent, ent);
      RWStepShape_RWOpenShell tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 175:
    {
      DeclareAndCast(StepBasic_OrdinalDate, anent, ent);
      RWStepBasic_RWOrdinalDate tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 176:
    {
      DeclareAndCast(StepBasic_Organization, anent, ent);
      RWStepBasic_RWOrganization tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 178:
    {
      DeclareAndCast(StepBasic_OrganizationRole, anent, ent);
      RWStepBasic_RWOrganizationRole tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 179:
    {
      DeclareAndCast(StepBasic_OrganizationalAddress, anent, ent);
      RWStepBasic_RWOrganizationalAddress tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 180:
    {
      DeclareAndCast(StepShape_OrientedClosedShell, anent, ent);
      RWStepShape_RWOrientedClosedShell tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 181:
    {
      DeclareAndCast(StepShape_OrientedEdge, anent, ent);
      RWStepShape_RWOrientedEdge tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 182:
    {
      DeclareAndCast(StepShape_OrientedFace, anent, ent);
      RWStepShape_RWOrientedFace tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 183:
    {
      DeclareAndCast(StepShape_OrientedOpenShell, anent, ent);
      RWStepShape_RWOrientedOpenShell tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 184:
    {
      DeclareAndCast(StepShape_OrientedPath, anent, ent);
      RWStepShape_RWOrientedPath tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 185:
    {
      DeclareAndCast(StepGeom_OuterBoundaryCurve, anent, ent);
      RWStepGeom_RWOuterBoundaryCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 186:
    {
      DeclareAndCast(StepVisual_OverRidingStyledItem, anent, ent);
      RWStepVisual_RWOverRidingStyledItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 187:
    {
      DeclareAndCast(StepGeom_Parabola, anent, ent);
      RWStepGeom_RWParabola tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 188:
    {
      DeclareAndCast(StepRepr_ParametricRepresentationContext, anent, ent);
      RWStepRepr_RWParametricRepresentationContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 189:
    {
      DeclareAndCast(StepShape_Path, anent, ent);
      RWStepShape_RWPath tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 190:
    {
      DeclareAndCast(StepGeom_Pcurve, anent, ent);
      RWStepGeom_RWPcurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 191:
    {
      DeclareAndCast(StepBasic_Person, anent, ent);
      RWStepBasic_RWPerson tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 192:
    {
      DeclareAndCast(StepBasic_PersonAndOrganization, anent, ent);
      RWStepBasic_RWPersonAndOrganization tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 194:
    {
      DeclareAndCast(StepBasic_PersonAndOrganizationRole, anent, ent);
      RWStepBasic_RWPersonAndOrganizationRole tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 195:
    {
      DeclareAndCast(StepBasic_PersonalAddress, anent, ent);
      RWStepBasic_RWPersonalAddress tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 196:
    {
      DeclareAndCast(StepGeom_Placement, anent, ent);
      RWStepGeom_RWPlacement tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 197:
    {
      DeclareAndCast(StepVisual_PlanarBox, anent, ent);
      RWStepVisual_RWPlanarBox tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 198:
    {
      DeclareAndCast(StepVisual_PlanarExtent, anent, ent);
      RWStepVisual_RWPlanarExtent tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 199:
    {
      DeclareAndCast(StepGeom_Plane, anent, ent);
      RWStepGeom_RWPlane tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 200:
    {
      DeclareAndCast(StepBasic_PlaneAngleMeasureWithUnit, anent, ent);
      RWStepBasic_RWPlaneAngleMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 201:
    {
      DeclareAndCast(StepBasic_PlaneAngleUnit, anent, ent);
      RWStepBasic_RWPlaneAngleUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 202:
    {
      DeclareAndCast(StepGeom_Point, anent, ent);
      RWStepGeom_RWPoint tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 203:
    {
      DeclareAndCast(StepGeom_PointOnCurve, anent, ent);
      RWStepGeom_RWPointOnCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 204:
    {
      DeclareAndCast(StepGeom_PointOnSurface, anent, ent);
      RWStepGeom_RWPointOnSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 205:
    {
      DeclareAndCast(StepGeom_PointReplica, anent, ent);
      RWStepGeom_RWPointReplica tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 206:
    {
      DeclareAndCast(StepVisual_PointStyle, anent, ent);
      RWStepVisual_RWPointStyle tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 207:
    {
      DeclareAndCast(StepShape_PolyLoop, anent, ent);
      RWStepShape_RWPolyLoop tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 208:
    {
      DeclareAndCast(StepGeom_Polyline, anent, ent);
      RWStepGeom_RWPolyline tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 209:
    {
      DeclareAndCast(StepVisual_PreDefinedColour, anent, ent);
      RWStepVisual_RWPreDefinedColour tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 210:
    {
      DeclareAndCast(StepVisual_PreDefinedCurveFont, anent, ent);
      RWStepVisual_RWPreDefinedCurveFont tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 211:
    case 213:
    {
      DeclareAndCast(StepVisual_PreDefinedItem, anent, ent);
      RWStepVisual_RWPreDefinedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 214:
    {
      DeclareAndCast(StepVisual_PresentationArea, anent, ent);
      RWStepVisual_RWPresentationArea tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 215:
    {
      DeclareAndCast(StepVisual_PresentationLayerAssignment, anent, ent);
      RWStepVisual_RWPresentationLayerAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 216:
    {
      DeclareAndCast(StepVisual_PresentationRepresentation, anent, ent);
      RWStepVisual_RWPresentationRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 217:
    {
      DeclareAndCast(StepVisual_PresentationSet, anent, ent);
      RWStepVisual_RWPresentationSet tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 218:
    {
      DeclareAndCast(StepVisual_PresentationSize, anent, ent);
      RWStepVisual_RWPresentationSize tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 219:
    {
      DeclareAndCast(StepVisual_PresentationStyleAssignment, anent, ent);
      RWStepVisual_RWPresentationStyleAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 220:
    {
      DeclareAndCast(StepVisual_PresentationStyleByContext, anent, ent);
      RWStepVisual_RWPresentationStyleByContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 221:
    {
      DeclareAndCast(StepVisual_PresentationView, anent, ent);
      RWStepVisual_RWPresentationView tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 223:
    {
      DeclareAndCast(StepBasic_Product, anent, ent);
      RWStepBasic_RWProduct tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 224:
    {
      DeclareAndCast(StepBasic_ProductCategory, anent, ent);
      RWStepBasic_RWProductCategory tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 225:
    {
      DeclareAndCast(StepBasic_ProductContext, anent, ent);
      RWStepBasic_RWProductContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 227:
    {
      DeclareAndCast(StepBasic_ProductDefinition, anent, ent);
      RWStepBasic_RWProductDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 228:
    {
      DeclareAndCast(StepBasic_ProductDefinitionContext, anent, ent);
      RWStepBasic_RWProductDefinitionContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 229:
    {
      DeclareAndCast(StepBasic_ProductDefinitionFormation, anent, ent);
      RWStepBasic_RWProductDefinitionFormation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 230:
    {
      DeclareAndCast(StepBasic_ProductDefinitionFormationWithSpecifiedSource, anent, ent);
      RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 231:
    {
      DeclareAndCast(StepRepr_ProductDefinitionShape, anent, ent);
      RWStepRepr_RWProductDefinitionShape tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 232:
    {
      DeclareAndCast(StepBasic_ProductRelatedProductCategory, anent, ent);
      RWStepBasic_RWProductRelatedProductCategory tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 233:
    {
      DeclareAndCast(StepBasic_ProductType, anent, ent);
      RWStepBasic_RWProductType tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 234:
    {
      DeclareAndCast(StepRepr_PropertyDefinition, anent, ent);
      RWStepRepr_RWPropertyDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 235:
    {
      DeclareAndCast(StepRepr_PropertyDefinitionRepresentation, anent, ent);
      RWStepRepr_RWPropertyDefinitionRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 236:
    {
      DeclareAndCast(StepGeom_QuasiUniformCurve, anent, ent);
      RWStepGeom_RWQuasiUniformCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 237:
    {
      DeclareAndCast(StepGeom_QuasiUniformSurface, anent, ent);
      RWStepGeom_RWQuasiUniformSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 238:
    {
      DeclareAndCast(StepBasic_RatioMeasureWithUnit, anent, ent);
      RWStepBasic_RWRatioMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 239:
    {
      DeclareAndCast(StepGeom_RationalBSplineCurve, anent, ent);
      RWStepGeom_RWRationalBSplineCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 240:
    {
      DeclareAndCast(StepGeom_RationalBSplineSurface, anent, ent);
      RWStepGeom_RWRationalBSplineSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 241:
    {
      DeclareAndCast(StepGeom_RectangularCompositeSurface, anent, ent);
      RWStepGeom_RWRectangularCompositeSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 242:
    {
      DeclareAndCast(StepGeom_RectangularTrimmedSurface, anent, ent);
      RWStepGeom_RWRectangularTrimmedSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 243:
    {
      DeclareAndCast(StepAP214_RepItemGroup, anent, ent);
      RWStepAP214_RWRepItemGroup tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 244:
    {
      DeclareAndCast(StepGeom_ReparametrisedCompositeCurveSegment, anent, ent);
      RWStepGeom_RWReparametrisedCompositeCurveSegment tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 245:
    {
      DeclareAndCast(StepRepr_Representation, anent, ent);
      RWStepRepr_RWRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 246:
    {
      DeclareAndCast(StepRepr_RepresentationContext, anent, ent);
      RWStepRepr_RWRepresentationContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 247:
    {
      DeclareAndCast(StepRepr_RepresentationItem, anent, ent);
      RWStepRepr_RWRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 248:
    {
      DeclareAndCast(StepRepr_RepresentationMap, anent, ent);
      RWStepRepr_RWRepresentationMap tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 249:
    {
      DeclareAndCast(StepRepr_RepresentationRelationship, anent, ent);
      RWStepRepr_RWRepresentationRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 250:
    {
      DeclareAndCast(StepShape_RevolvedAreaSolid, anent, ent);
      RWStepShape_RWRevolvedAreaSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 251:
    {
      DeclareAndCast(StepShape_RightAngularWedge, anent, ent);
      RWStepShape_RWRightAngularWedge tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 252:
    {
      DeclareAndCast(StepShape_RightCircularCone, anent, ent);
      RWStepShape_RWRightCircularCone tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 253:
    {
      DeclareAndCast(StepShape_RightCircularCylinder, anent, ent);
      RWStepShape_RWRightCircularCylinder tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 254:
    {
      DeclareAndCast(StepGeom_SeamCurve, anent, ent);
      RWStepGeom_RWSeamCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 255:
    {
      DeclareAndCast(StepBasic_SecurityClassification, anent, ent);
      RWStepBasic_RWSecurityClassification tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 257:
    {
      DeclareAndCast(StepBasic_SecurityClassificationLevel, anent, ent);
      RWStepBasic_RWSecurityClassificationLevel tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 258:
    {
      DeclareAndCast(StepRepr_ShapeAspect, anent, ent);
      RWStepRepr_RWShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 259:
    {
      DeclareAndCast(StepRepr_ShapeAspectRelationship, anent, ent);
      RWStepRepr_RWShapeAspectRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 260:
    {
      DeclareAndCast(StepRepr_ShapeAspectTransition, anent, ent);
      RWStepRepr_RWShapeAspectTransition tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 261:
    {
      DeclareAndCast(StepShape_ShapeDefinitionRepresentation, anent, ent);
      RWStepShape_RWShapeDefinitionRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 262:
    {
      DeclareAndCast(StepShape_ShapeRepresentation, anent, ent);
      RWStepShape_RWShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 263:
    {
      DeclareAndCast(StepShape_ShellBasedSurfaceModel, anent, ent);
      RWStepShape_RWShellBasedSurfaceModel tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 264:
    {
      DeclareAndCast(StepBasic_SiUnit, anent, ent);
      RWStepBasic_RWSiUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 265:
    {
      DeclareAndCast(StepBasic_SolidAngleMeasureWithUnit, anent, ent);
      RWStepBasic_RWSolidAngleMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 266:
    {
      DeclareAndCast(StepShape_SolidModel, anent, ent);
      RWStepShape_RWSolidModel tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 267:
    {
      DeclareAndCast(StepShape_SolidReplica, anent, ent);
      RWStepShape_RWSolidReplica tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 268:
    {
      DeclareAndCast(StepShape_Sphere, anent, ent);
      RWStepShape_RWSphere tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 269:
    {
      DeclareAndCast(StepGeom_SphericalSurface, anent, ent);
      RWStepGeom_RWSphericalSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 270:
    {
      DeclareAndCast(StepVisual_StyledItem, anent, ent);
      RWStepVisual_RWStyledItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 271:
    {
      DeclareAndCast(StepGeom_Surface, anent, ent);
      RWStepGeom_RWSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 272:
    {
      DeclareAndCast(StepGeom_SurfaceCurve, anent, ent);
      RWStepGeom_RWSurfaceCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 273:
    {
      DeclareAndCast(StepGeom_SurfaceOfLinearExtrusion, anent, ent);
      RWStepGeom_RWSurfaceOfLinearExtrusion tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 274:
    {
      DeclareAndCast(StepGeom_SurfaceOfRevolution, anent, ent);
      RWStepGeom_RWSurfaceOfRevolution tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 275:
    {
      DeclareAndCast(StepGeom_SurfacePatch, anent, ent);
      RWStepGeom_RWSurfacePatch tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 276:
    {
      DeclareAndCast(StepGeom_SurfaceReplica, anent, ent);
      RWStepGeom_RWSurfaceReplica tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 277:
    {
      DeclareAndCast(StepVisual_SurfaceSideStyle, anent, ent);
      RWStepVisual_RWSurfaceSideStyle tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 278:
    {
      DeclareAndCast(StepVisual_SurfaceStyleBoundary, anent, ent);
      RWStepVisual_RWSurfaceStyleBoundary tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 279:
    {
      DeclareAndCast(StepVisual_SurfaceStyleControlGrid, anent, ent);
      RWStepVisual_RWSurfaceStyleControlGrid tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 280:
    {
      DeclareAndCast(StepVisual_SurfaceStyleFillArea, anent, ent);
      RWStepVisual_RWSurfaceStyleFillArea tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 281:
    {
      DeclareAndCast(StepVisual_SurfaceStyleParameterLine, anent, ent);
      RWStepVisual_RWSurfaceStyleParameterLine tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 282:
    {
      DeclareAndCast(StepVisual_SurfaceStyleSegmentationCurve, anent, ent);
      RWStepVisual_RWSurfaceStyleSegmentationCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 283:
    {
      DeclareAndCast(StepVisual_SurfaceStyleSilhouette, anent, ent);
      RWStepVisual_RWSurfaceStyleSilhouette tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 284:
    {
      DeclareAndCast(StepVisual_SurfaceStyleUsage, anent, ent);
      RWStepVisual_RWSurfaceStyleUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 285:
    {
      DeclareAndCast(StepShape_SweptAreaSolid, anent, ent);
      RWStepShape_RWSweptAreaSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 286:
    {
      DeclareAndCast(StepGeom_SweptSurface, anent, ent);
      RWStepGeom_RWSweptSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 292:
    {
      DeclareAndCast(StepVisual_Template, anent, ent);
      RWStepVisual_RWTemplate tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 293:
    {
      DeclareAndCast(StepVisual_TemplateInstance, anent, ent);
      RWStepVisual_RWTemplateInstance tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 295:
    {
      DeclareAndCast(StepVisual_TextLiteral, anent, ent);
      RWStepVisual_RWTextLiteral tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 300:
    {
      DeclareAndCast(StepVisual_TextStyle, anent, ent);
      RWStepVisual_RWTextStyle tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 301:
    {
      DeclareAndCast(StepVisual_TextStyleForDefinedFont, anent, ent);
      RWStepVisual_RWTextStyleForDefinedFont tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 302:
    {
      DeclareAndCast(StepVisual_TextStyleWithBoxCharacteristics, anent, ent);
      RWStepVisual_RWTextStyleWithBoxCharacteristics tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 304:
    {
      DeclareAndCast(StepShape_TopologicalRepresentationItem, anent, ent);
      RWStepShape_RWTopologicalRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 305:
    {
      DeclareAndCast(StepGeom_ToroidalSurface, anent, ent);
      RWStepGeom_RWToroidalSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 306:
    {
      DeclareAndCast(StepShape_Torus, anent, ent);
      RWStepShape_RWTorus tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 307:
    {
      DeclareAndCast(StepShape_TransitionalShapeRepresentation, anent, ent);
      RWStepShape_RWTransitionalShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 308:
    {
      DeclareAndCast(StepGeom_TrimmedCurve, anent, ent);
      RWStepGeom_RWTrimmedCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 310:
    {
      DeclareAndCast(StepBasic_UncertaintyMeasureWithUnit, anent, ent);
      RWStepBasic_RWUncertaintyMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 311:
    {
      DeclareAndCast(StepGeom_UniformCurve, anent, ent);
      RWStepGeom_RWUniformCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 312:
    {
      DeclareAndCast(StepGeom_UniformSurface, anent, ent);
      RWStepGeom_RWUniformSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 313:
    {
      DeclareAndCast(StepGeom_Vector, anent, ent);
      RWStepGeom_RWVector tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 314:
    {
      DeclareAndCast(StepShape_Vertex, anent, ent);
      RWStepShape_RWVertex tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 315:
    {
      DeclareAndCast(StepShape_VertexLoop, anent, ent);
      RWStepShape_RWVertexLoop tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 316:
    {
      DeclareAndCast(StepShape_VertexPoint, anent, ent);
      RWStepShape_RWVertexPoint tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 317:
    {
      DeclareAndCast(StepVisual_ViewVolume, anent, ent);
      RWStepVisual_RWViewVolume tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 318:
    {
      DeclareAndCast(StepBasic_WeekOfYearAndDayDate, anent, ent);
      RWStepBasic_RWWeekOfYearAndDayDate tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 319:
    {
      DeclareAndCast(StepGeom_UniformCurveAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWUniformCurveAndRationalBSplineCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 320:
    {
      DeclareAndCast(StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 321:
    {
      DeclareAndCast(StepGeom_QuasiUniformCurveAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 322:
    {
      DeclareAndCast(StepGeom_BezierCurveAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWBezierCurveAndRationalBSplineCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 323:
    {
      DeclareAndCast(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 324:
    {
      DeclareAndCast(StepGeom_UniformSurfaceAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 325:
    {
      DeclareAndCast(StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 326:
    {
      DeclareAndCast(StepGeom_BezierSurfaceAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 327:
    {
      DeclareAndCast(StepBasic_SiUnitAndLengthUnit, anent, ent);
      RWStepBasic_RWSiUnitAndLengthUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 328:
    {
      DeclareAndCast(StepBasic_SiUnitAndPlaneAngleUnit, anent, ent);
      RWStepBasic_RWSiUnitAndPlaneAngleUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 329:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndLengthUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndLengthUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 330:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndPlaneAngleUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 331:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext,
                     anent,
                     ent);
      RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 332:
    {
      DeclareAndCast(StepShape_LoopAndPath, anent, ent);
      RWStepShape_RWLoopAndPath tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 333:
    {
      DeclareAndCast(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx, anent, ent);
      RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 334:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndSolidAngleUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndSolidAngleUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 335:
    {
      DeclareAndCast(StepBasic_SiUnitAndSolidAngleUnit, anent, ent);
      RWStepBasic_RWSiUnitAndSolidAngleUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 336:
    {
      DeclareAndCast(StepBasic_SolidAngleUnit, anent, ent);
      RWStepBasic_RWSolidAngleUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 337:
    {
      DeclareAndCast(StepShape_FacetedBrepAndBrepWithVoids, anent, ent);
      RWStepShape_RWFacetedBrepAndBrepWithVoids tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 338:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContextAndParametricRepresentationContext,
                     anent,
                     ent);
      RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 339:
    {
      DeclareAndCast(StepBasic_MechanicalContext, anent, ent);
      RWStepBasic_RWMechanicalContext tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 340:
    {
      DeclareAndCast(StepBasic_ProductDefinitionContext, anent, ent);
      RWStepBasic_RWProductDefinitionContext tool;
      tool.ReadStep(data, num, ach, anent);
      break;
    }

    case 341:
    {
      DeclareAndCast(StepBasic_MeasureWithUnit, anent, ent);
      RWStepBasic_RWMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 342:
    case 343:
    {
      DeclareAndCast(StepBasic_NamedUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 344:
    {
      DeclareAndCast(StepBasic_SiUnitAndRatioUnit, anent, ent);
      RWStepBasic_RWSiUnitAndRatioUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 345:
    {
      DeclareAndCast(StepBasic_SiUnitAndTimeUnit, anent, ent);
      RWStepBasic_RWSiUnitAndTimeUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 346:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndRatioUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndRatioUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 347:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndTimeUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndTimeUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 348:
    {
      DeclareAndCast(StepBasic_ApprovalDateTime, anent, ent);
      RWStepBasic_RWApprovalDateTime tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 349:
    case 350:
    {
      DeclareAndCast(StepVisual_CameraImage, anent, ent);
      RWStepVisual_RWCameraImage tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 351:
    {
      DeclareAndCast(StepGeom_CartesianTransformationOperator, anent, ent);
      RWStepGeom_RWCartesianTransformationOperator tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 352:
    {
      DeclareAndCast(StepBasic_DerivedUnit, anent, ent);
      RWStepBasic_RWDerivedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 353:
    {
      DeclareAndCast(StepBasic_DerivedUnitElement, anent, ent);
      RWStepBasic_RWDerivedUnitElement tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 354:
    {
      DeclareAndCast(StepRepr_ItemDefinedTransformation, anent, ent);
      RWStepRepr_RWItemDefinedTransformation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 355:
    {
      DeclareAndCast(StepVisual_PresentedItemRepresentation, anent, ent);
      RWStepVisual_RWPresentedItemRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 356:
    {
      DeclareAndCast(StepVisual_PresentationLayerUsage, anent, ent);
      RWStepVisual_RWPresentationLayerUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 357:
    {
      DeclareAndCast(StepBasic_UncertaintyMeasureWithUnit, anent, ent);
      RWStepBasic_RWUncertaintyMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 358:
    {
      DeclareAndCast(StepGeom_SurfaceCurveAndBoundedCurve, anent, ent);
      RWStepGeom_RWSurfaceCurveAndBoundedCurve tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 366:
    {
      DeclareAndCast(StepAP214_AutoDesignDocumentReference, anent, ent);
      RWStepAP214_RWAutoDesignDocumentReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 367:
    case 368:
    {
      DeclareAndCast(StepBasic_Document, anent, ent);
      RWStepBasic_RWDocument tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 369:
    {
      DeclareAndCast(StepBasic_DocumentRelationship, anent, ent);
      RWStepBasic_RWDocumentRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 370:
    {
      DeclareAndCast(StepBasic_DocumentType, anent, ent);
      RWStepBasic_RWDocumentType tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 371:
    {
      DeclareAndCast(StepBasic_DocumentUsageConstraint, anent, ent);
      RWStepBasic_RWDocumentUsageConstraint tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 372:
    {
      DeclareAndCast(StepBasic_Effectivity, anent, ent);
      RWStepBasic_RWEffectivity tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 373:
    {
      DeclareAndCast(StepBasic_ProductDefinitionEffectivity, anent, ent);
      RWStepBasic_RWProductDefinitionEffectivity tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 374:
    {
      DeclareAndCast(StepBasic_ProductDefinitionRelationship, anent, ent);
      RWStepBasic_RWProductDefinitionRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 375:
    {
      DeclareAndCast(StepBasic_ProductDefinitionWithAssociatedDocuments, anent, ent);
      RWStepBasic_RWProductDefinitionWithAssociatedDocuments tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 376:
    {
      DeclareAndCast(StepBasic_PhysicallyModeledProductDefinition, anent, ent);
      RWStepBasic_RWProductDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 377:
    {
      DeclareAndCast(StepRepr_ProductDefinitionUsage, anent, ent);
      RWStepBasic_RWProductDefinitionRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 378:
    {
      DeclareAndCast(StepRepr_MakeFromUsageOption, anent, ent);
      RWStepRepr_RWMakeFromUsageOption tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 379:
    case 380:
    case 381:
    {
      DeclareAndCast(StepRepr_AssemblyComponentUsage, anent, ent);
      RWStepRepr_RWAssemblyComponentUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 382:
    {
      DeclareAndCast(StepRepr_QuantifiedAssemblyComponentUsage, anent, ent);
      RWStepRepr_RWQuantifiedAssemblyComponentUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 383:
    {
      DeclareAndCast(StepRepr_SpecifiedHigherUsageOccurrence, anent, ent);
      RWStepRepr_RWSpecifiedHigherUsageOccurrence tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 384:
    {
      DeclareAndCast(StepRepr_AssemblyComponentUsageSubstitute, anent, ent);
      RWStepRepr_RWAssemblyComponentUsageSubstitute tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 385:
    {
      DeclareAndCast(StepRepr_SuppliedPartRelationship, anent, ent);
      RWStepBasic_RWProductDefinitionRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 386:
    {
      DeclareAndCast(StepRepr_ExternallyDefinedRepresentation, anent, ent);
      RWStepRepr_RWRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 387:
    {
      DeclareAndCast(StepRepr_ShapeRepresentationRelationship, anent, ent);
      RWStepRepr_RWRepresentationRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 388:
    {
      DeclareAndCast(StepRepr_RepresentationRelationshipWithTransformation, anent, ent);
      RWStepRepr_RWRepresentationRelationshipWithTransformation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 389:
    {
      DeclareAndCast(StepRepr_ShapeRepresentationRelationshipWithTransformation, anent, ent);
      RWStepRepr_RWShapeRepresentationRelationshipWithTransformation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 390:
    {
      DeclareAndCast(StepRepr_MaterialDesignation, anent, ent);
      RWStepRepr_RWMaterialDesignation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 391:
    {
      DeclareAndCast(StepShape_ContextDependentShapeRepresentation, anent, ent);
      RWStepShape_RWContextDependentShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 392:
    {
      DeclareAndCast(StepAP214_AppliedDateAndTimeAssignment, anent, ent);
      RWStepAP214_RWAppliedDateAndTimeAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 393:
    {
      DeclareAndCast(StepAP214_AppliedDateAssignment, anent, ent);
      RWStepAP214_RWAppliedDateAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 394:
    {
      DeclareAndCast(StepAP214_AppliedApprovalAssignment, anent, ent);
      RWStepAP214_RWAppliedApprovalAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 395:
    {
      DeclareAndCast(StepAP214_AppliedGroupAssignment, anent, ent);
      RWStepAP214_RWAppliedGroupAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 396:
    {
      DeclareAndCast(StepAP214_AppliedOrganizationAssignment, anent, ent);
      RWStepAP214_RWAppliedOrganizationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 397:
    {
      DeclareAndCast(StepAP214_AppliedPersonAndOrganizationAssignment, anent, ent);
      RWStepAP214_RWAppliedPersonAndOrganizationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 398:
    {
      DeclareAndCast(StepAP214_AppliedPresentedItem, anent, ent);
      RWStepAP214_RWAppliedPresentedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 399:
    {
      DeclareAndCast(StepAP214_AppliedSecurityClassificationAssignment, anent, ent);
      RWStepAP214_RWAppliedSecurityClassificationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 400:
    {
      DeclareAndCast(StepAP214_AppliedDocumentReference, anent, ent);
      RWStepAP214_RWAppliedDocumentReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 401:
    {
      DeclareAndCast(StepBasic_DocumentFile, anent, ent);
      RWStepBasic_RWDocumentFile tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 402:
    {
      DeclareAndCast(StepBasic_CharacterizedObject, anent, ent);
      RWStepBasic_RWCharacterizedObject tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 403:
    {
      DeclareAndCast(StepShape_ExtrudedFaceSolid, anent, ent);
      RWStepShape_RWExtrudedFaceSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 404:
    {
      DeclareAndCast(StepShape_RevolvedFaceSolid, anent, ent);
      RWStepShape_RWRevolvedFaceSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 405:
    {
      DeclareAndCast(StepShape_SweptFaceSolid, anent, ent);
      RWStepShape_RWSweptFaceSolid tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 406:
    {
      DeclareAndCast(StepRepr_MeasureRepresentationItem, anent, ent);
      RWStepRepr_RWMeasureRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 407:
    {
      DeclareAndCast(StepBasic_AreaUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 408:
    {
      DeclareAndCast(StepBasic_VolumeUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 409:
    {
      DeclareAndCast(StepBasic_SiUnitAndAreaUnit, anent, ent);
      RWStepBasic_RWSiUnitAndAreaUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 410:
    {
      DeclareAndCast(StepBasic_SiUnitAndVolumeUnit, anent, ent);
      RWStepBasic_RWSiUnitAndVolumeUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 411:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndAreaUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndAreaUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 412:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndVolumeUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndVolumeUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 413:
    {
      DeclareAndCast(StepBasic_Action, anent, ent);
      RWStepBasic_RWAction tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 414:
    {
      DeclareAndCast(StepBasic_ActionAssignment, anent, ent);
      RWStepBasic_RWActionAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 415:
    {
      DeclareAndCast(StepBasic_ActionMethod, anent, ent);
      RWStepBasic_RWActionMethod tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 416:
    {
      DeclareAndCast(StepBasic_ActionRequestAssignment, anent, ent);
      RWStepBasic_RWActionRequestAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 417:
    {
      DeclareAndCast(StepAP203_CcDesignApproval, anent, ent);
      RWStepAP203_RWCcDesignApproval tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 418:
    {
      DeclareAndCast(StepAP203_CcDesignCertification, anent, ent);
      RWStepAP203_RWCcDesignCertification tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 419:
    {
      DeclareAndCast(StepAP203_CcDesignContract, anent, ent);
      RWStepAP203_RWCcDesignContract tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 420:
    {
      DeclareAndCast(StepAP203_CcDesignDateAndTimeAssignment, anent, ent);
      RWStepAP203_RWCcDesignDateAndTimeAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 421:
    {
      DeclareAndCast(StepAP203_CcDesignPersonAndOrganizationAssignment, anent, ent);
      RWStepAP203_RWCcDesignPersonAndOrganizationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 422:
    {
      DeclareAndCast(StepAP203_CcDesignSecurityClassification, anent, ent);
      RWStepAP203_RWCcDesignSecurityClassification tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 423:
    {
      DeclareAndCast(StepAP203_CcDesignSpecificationReference, anent, ent);
      RWStepAP203_RWCcDesignSpecificationReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 424:
    {
      DeclareAndCast(StepBasic_Certification, anent, ent);
      RWStepBasic_RWCertification tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 425:
    {
      DeclareAndCast(StepBasic_CertificationAssignment, anent, ent);
      RWStepBasic_RWCertificationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 426:
    {
      DeclareAndCast(StepBasic_CertificationType, anent, ent);
      RWStepBasic_RWCertificationType tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 427:
    {
      DeclareAndCast(StepAP203_Change, anent, ent);
      RWStepAP203_RWChange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 428:
    {
      DeclareAndCast(StepAP203_ChangeRequest, anent, ent);
      RWStepAP203_RWChangeRequest tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 429:
    {
      DeclareAndCast(StepRepr_ConfigurationDesign, anent, ent);
      RWStepRepr_RWConfigurationDesign tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 430:
    {
      DeclareAndCast(StepRepr_ConfigurationEffectivity, anent, ent);
      RWStepRepr_RWConfigurationEffectivity tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 431:
    {
      DeclareAndCast(StepBasic_Contract, anent, ent);
      RWStepBasic_RWContract tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 432:
    {
      DeclareAndCast(StepBasic_ContractAssignment, anent, ent);
      RWStepBasic_RWContractAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 433:
    {
      DeclareAndCast(StepBasic_ContractType, anent, ent);
      RWStepBasic_RWContractType tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 434:
    {
      DeclareAndCast(StepRepr_ProductConcept, anent, ent);
      RWStepRepr_RWProductConcept tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 435:
    {
      DeclareAndCast(StepBasic_ProductConceptContext, anent, ent);
      RWStepBasic_RWProductConceptContext tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 436:
    {
      DeclareAndCast(StepAP203_StartRequest, anent, ent);
      RWStepAP203_RWStartRequest tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 437:
    {
      DeclareAndCast(StepAP203_StartWork, anent, ent);
      RWStepAP203_RWStartWork tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 438:
    {
      DeclareAndCast(StepBasic_VersionedActionRequest, anent, ent);
      RWStepBasic_RWVersionedActionRequest tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 439:
    {
      DeclareAndCast(StepBasic_ProductCategoryRelationship, anent, ent);
      RWStepBasic_RWProductCategoryRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 440:
    {
      DeclareAndCast(StepBasic_ActionRequestSolution, anent, ent);
      RWStepBasic_RWActionRequestSolution tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 441:
    {
      DeclareAndCast(StepVisual_DraughtingModel, anent, ent);
      RWStepVisual_RWDraughtingModel tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 442:
    {
      DeclareAndCast(StepShape_AngularLocation, anent, ent);
      RWStepShape_RWAngularLocation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 443:
    {
      DeclareAndCast(StepShape_AngularSize, anent, ent);
      RWStepShape_RWAngularSize tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 444:
    {
      DeclareAndCast(StepShape_DimensionalCharacteristicRepresentation, anent, ent);
      RWStepShape_RWDimensionalCharacteristicRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 445:
    {
      DeclareAndCast(StepShape_DimensionalLocation, anent, ent);
      RWStepShape_RWDimensionalLocation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 446:
    {
      DeclareAndCast(StepShape_DimensionalLocationWithPath, anent, ent);
      RWStepShape_RWDimensionalLocationWithPath tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 447:
    {
      DeclareAndCast(StepShape_DimensionalSize, anent, ent);
      RWStepShape_RWDimensionalSize tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 448:
    {
      DeclareAndCast(StepShape_DimensionalSizeWithPath, anent, ent);
      RWStepShape_RWDimensionalSizeWithPath tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 449:
    {
      DeclareAndCast(StepShape_ShapeDimensionRepresentation, anent, ent);
      RWStepShape_RWShapeDimensionRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 450:
    {
      DeclareAndCast(StepBasic_DocumentRepresentationType, anent, ent);
      RWStepBasic_RWDocumentRepresentationType tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 451:
    {
      DeclareAndCast(StepBasic_ObjectRole, anent, ent);
      RWStepBasic_RWObjectRole tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 452:
    {
      DeclareAndCast(StepBasic_RoleAssociation, anent, ent);
      RWStepBasic_RWRoleAssociation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 453:
    {
      DeclareAndCast(StepBasic_IdentificationRole, anent, ent);
      RWStepBasic_RWIdentificationRole tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 454:
    {
      DeclareAndCast(StepBasic_IdentificationAssignment, anent, ent);
      RWStepBasic_RWIdentificationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 455:
    {
      DeclareAndCast(StepBasic_ExternalIdentificationAssignment, anent, ent);
      RWStepBasic_RWExternalIdentificationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 456:
    {
      DeclareAndCast(StepBasic_EffectivityAssignment, anent, ent);
      RWStepBasic_RWEffectivityAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 457:
    {
      DeclareAndCast(StepBasic_NameAssignment, anent, ent);
      RWStepBasic_RWNameAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 458:
    {
      DeclareAndCast(StepBasic_GeneralProperty, anent, ent);
      RWStepBasic_RWGeneralProperty tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 459:
    {
      DeclareAndCast(StepAP214_Class, anent, ent);
      RWStepAP214_RWClass tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 460:
    {
      DeclareAndCast(StepAP214_ExternallyDefinedClass, anent, ent);
      RWStepAP214_RWExternallyDefinedClass tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 461:
    {
      DeclareAndCast(StepAP214_ExternallyDefinedGeneralProperty, anent, ent);
      RWStepAP214_RWExternallyDefinedGeneralProperty tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 462:
    {
      DeclareAndCast(StepAP214_AppliedExternalIdentificationAssignment, anent, ent);
      RWStepAP214_RWAppliedExternalIdentificationAssignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 463:
    {
      DeclareAndCast(StepShape_DefinitionalRepresentationAndShapeRepresentation, anent, ent);
      RWStepShape_RWDefinitionalRepresentationAndShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 470:
    {
      DeclareAndCast(StepRepr_CompositeShapeAspect, anent, ent);
      RWStepRepr_RWCompositeShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 471:
    {
      DeclareAndCast(StepRepr_DerivedShapeAspect, anent, ent);
      RWStepRepr_RWDerivedShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 472:
    {
      DeclareAndCast(StepRepr_Extension, anent, ent);
      RWStepRepr_RWExtension tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 473:
    {
      DeclareAndCast(StepShape_DirectedDimensionalLocation, anent, ent);
      RWStepShape_RWDimensionalLocation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 474:
    {
      DeclareAndCast(StepShape_LimitsAndFits, anent, ent);
      RWStepShape_RWLimitsAndFits tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 475:
    {
      DeclareAndCast(StepShape_ToleranceValue, anent, ent);
      RWStepShape_RWToleranceValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 476:
    {
      DeclareAndCast(StepShape_MeasureQualification, anent, ent);
      RWStepShape_RWMeasureQualification tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 477:
    {
      DeclareAndCast(StepShape_PlusMinusTolerance, anent, ent);
      RWStepShape_RWPlusMinusTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 478:
    {
      DeclareAndCast(StepShape_PrecisionQualifier, anent, ent);
      RWStepShape_RWPrecisionQualifier tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 479:
    {
      DeclareAndCast(StepShape_TypeQualifier, anent, ent);
      RWStepShape_RWTypeQualifier tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 480:
    {
      DeclareAndCast(StepShape_QualifiedRepresentationItem, anent, ent);
      RWStepShape_RWQualifiedRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 481:
    {
      DeclareAndCast(StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem, anent, ent);
      RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 482:
    case 483:
    {
      DeclareAndCast(StepRepr_CompoundRepresentationItem, anent, ent);
      RWStepRepr_RWCompoundRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 484:
    {
      DeclareAndCast(StepRepr_ShapeAspectRelationship, anent, ent);
      RWStepRepr_RWShapeAspectRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 485:
    {
      DeclareAndCast(StepShape_CompoundShapeRepresentation, anent, ent);
      RWStepShape_RWCompoundShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 486:
    {
      DeclareAndCast(StepShape_ConnectedEdgeSet, anent, ent);
      RWStepShape_RWConnectedEdgeSet tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 487:
    {
      DeclareAndCast(StepShape_ConnectedFaceShapeRepresentation, anent, ent);
      RWStepShape_RWConnectedFaceShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 488:
    {
      DeclareAndCast(StepShape_EdgeBasedWireframeModel, anent, ent);
      RWStepShape_RWEdgeBasedWireframeModel tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 489:
    {
      DeclareAndCast(StepShape_EdgeBasedWireframeShapeRepresentation, anent, ent);
      RWStepShape_RWEdgeBasedWireframeShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 490:
    {
      DeclareAndCast(StepShape_FaceBasedSurfaceModel, anent, ent);
      RWStepShape_RWFaceBasedSurfaceModel tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 491:
    {
      DeclareAndCast(StepShape_NonManifoldSurfaceShapeRepresentation, anent, ent);
      RWStepShape_RWNonManifoldSurfaceShapeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 492:
    {
      DeclareAndCast(StepGeom_OrientedSurface, anent, ent);
      RWStepGeom_RWOrientedSurface tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 493:
    {
      DeclareAndCast(StepShape_Subface, anent, ent);
      RWStepShape_RWSubface tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 494:
    {
      DeclareAndCast(StepShape_Subedge, anent, ent);
      RWStepShape_RWSubedge tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 495:
    {
      DeclareAndCast(StepShape_SeamEdge, anent, ent);
      RWStepShape_RWSeamEdge tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 496:
    {
      DeclareAndCast(StepShape_ConnectedFaceSubSet, anent, ent);
      RWStepShape_RWConnectedFaceSubSet tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 500:
    {
      DeclareAndCast(StepBasic_EulerAngles, anent, ent);
      RWStepBasic_RWEulerAngles tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 501:
    {
      DeclareAndCast(StepBasic_MassUnit, anent, ent);
      RWStepBasic_RWMassUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 502:
    {
      DeclareAndCast(StepBasic_ThermodynamicTemperatureUnit, anent, ent);
      RWStepBasic_RWThermodynamicTemperatureUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 503:
    {
      DeclareAndCast(StepElement_AnalysisItemWithinRepresentation, anent, ent);
      RWStepElement_RWAnalysisItemWithinRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 504:
    {
      DeclareAndCast(StepElement_Curve3dElementDescriptor, anent, ent);
      RWStepElement_RWCurve3dElementDescriptor tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 505:
    {
      DeclareAndCast(StepElement_CurveElementEndReleasePacket, anent, ent);
      RWStepElement_RWCurveElementEndReleasePacket tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 506:
    {
      DeclareAndCast(StepElement_CurveElementSectionDefinition, anent, ent);
      RWStepElement_RWCurveElementSectionDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 507:
    {
      DeclareAndCast(StepElement_CurveElementSectionDerivedDefinitions, anent, ent);
      RWStepElement_RWCurveElementSectionDerivedDefinitions tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 508:
    {
      DeclareAndCast(StepElement_ElementDescriptor, anent, ent);
      RWStepElement_RWElementDescriptor tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 509:
    {
      DeclareAndCast(StepElement_ElementMaterial, anent, ent);
      RWStepElement_RWElementMaterial tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 510:
    {
      DeclareAndCast(StepElement_Surface3dElementDescriptor, anent, ent);
      RWStepElement_RWSurface3dElementDescriptor tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 511:
    {
      DeclareAndCast(StepElement_SurfaceElementProperty, anent, ent);
      RWStepElement_RWSurfaceElementProperty tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 512:
    {
      DeclareAndCast(StepElement_SurfaceSection, anent, ent);
      RWStepElement_RWSurfaceSection tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 513:
    {
      DeclareAndCast(StepElement_SurfaceSectionField, anent, ent);
      RWStepElement_RWSurfaceSectionField tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 514:
    {
      DeclareAndCast(StepElement_SurfaceSectionFieldConstant, anent, ent);
      RWStepElement_RWSurfaceSectionFieldConstant tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 515:
    {
      DeclareAndCast(StepElement_SurfaceSectionFieldVarying, anent, ent);
      RWStepElement_RWSurfaceSectionFieldVarying tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 516:
    {
      DeclareAndCast(StepElement_UniformSurfaceSection, anent, ent);
      RWStepElement_RWUniformSurfaceSection tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 517:
    {
      DeclareAndCast(StepElement_Volume3dElementDescriptor, anent, ent);
      RWStepElement_RWVolume3dElementDescriptor tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 518:
    {
      DeclareAndCast(StepFEA_AlignedCurve3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWAlignedCurve3dElementCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 519:
    {
      DeclareAndCast(StepFEA_ArbitraryVolume3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWArbitraryVolume3dElementCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 520:
    {
      DeclareAndCast(StepFEA_Curve3dElementProperty, anent, ent);
      RWStepFEA_RWCurve3dElementProperty tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 521:
    {
      DeclareAndCast(StepFEA_Curve3dElementRepresentation, anent, ent);
      RWStepFEA_RWCurve3dElementRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 522:
    {
      DeclareAndCast(StepFEA_Node, anent, ent);
      RWStepFEA_RWNode tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 524:
    {
      DeclareAndCast(StepFEA_CurveElementEndOffset, anent, ent);
      RWStepFEA_RWCurveElementEndOffset tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 525:
    {
      DeclareAndCast(StepFEA_CurveElementEndRelease, anent, ent);
      RWStepFEA_RWCurveElementEndRelease tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 526:
    {
      DeclareAndCast(StepFEA_CurveElementInterval, anent, ent);
      RWStepFEA_RWCurveElementInterval tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 527:
    {
      DeclareAndCast(StepFEA_CurveElementIntervalConstant, anent, ent);
      RWStepFEA_RWCurveElementIntervalConstant tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 528:
    {
      DeclareAndCast(StepFEA_DummyNode, anent, ent);
      RWStepFEA_RWDummyNode tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 529:
    {
      DeclareAndCast(StepFEA_CurveElementLocation, anent, ent);
      RWStepFEA_RWCurveElementLocation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 530:
    {
      DeclareAndCast(StepFEA_ElementGeometricRelationship, anent, ent);
      RWStepFEA_RWElementGeometricRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 531:
    {
      DeclareAndCast(StepFEA_ElementGroup, anent, ent);
      RWStepFEA_RWElementGroup tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 532:
    {
      DeclareAndCast(StepFEA_ElementRepresentation, anent, ent);
      RWStepFEA_RWElementRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 533:
    {
      DeclareAndCast(StepFEA_FeaAreaDensity, anent, ent);
      RWStepFEA_RWFeaAreaDensity tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 534:
    {
      DeclareAndCast(StepFEA_FeaAxis2Placement3d, anent, ent);
      RWStepFEA_RWFeaAxis2Placement3d tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 535:
    {
      DeclareAndCast(StepFEA_FeaGroup, anent, ent);
      RWStepFEA_RWFeaGroup tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 536:
    {
      DeclareAndCast(StepFEA_FeaLinearElasticity, anent, ent);
      RWStepFEA_RWFeaLinearElasticity tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 537:
    {
      DeclareAndCast(StepFEA_FeaMassDensity, anent, ent);
      RWStepFEA_RWFeaMassDensity tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 538:
    {
      DeclareAndCast(StepFEA_FeaMaterialPropertyRepresentation, anent, ent);
      RWStepFEA_RWFeaMaterialPropertyRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 539:
    {
      DeclareAndCast(StepFEA_FeaMaterialPropertyRepresentationItem, anent, ent);
      RWStepFEA_RWFeaMaterialPropertyRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 540:
    {
      DeclareAndCast(StepFEA_FeaModel, anent, ent);
      RWStepFEA_RWFeaModel tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 541:
    {
      DeclareAndCast(StepFEA_FeaModel3d, anent, ent);
      RWStepFEA_RWFeaModel3d tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 542:
    {
      DeclareAndCast(StepFEA_FeaMoistureAbsorption, anent, ent);
      RWStepFEA_RWFeaMoistureAbsorption tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 543:
    {
      DeclareAndCast(StepFEA_FeaParametricPoint, anent, ent);
      RWStepFEA_RWFeaParametricPoint tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 544:
    {
      DeclareAndCast(StepFEA_FeaRepresentationItem, anent, ent);
      RWStepFEA_RWFeaRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 545:
    {
      DeclareAndCast(StepFEA_FeaSecantCoefficientOfLinearThermalExpansion, anent, ent);
      RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 546:
    {
      DeclareAndCast(StepFEA_FeaShellBendingStiffness, anent, ent);
      RWStepFEA_RWFeaShellBendingStiffness tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 547:
    {
      DeclareAndCast(StepFEA_FeaShellMembraneBendingCouplingStiffness, anent, ent);
      RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 548:
    {
      DeclareAndCast(StepFEA_FeaShellMembraneStiffness, anent, ent);
      RWStepFEA_RWFeaShellMembraneStiffness tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 549:
    {
      DeclareAndCast(StepFEA_FeaShellShearStiffness, anent, ent);
      RWStepFEA_RWFeaShellShearStiffness tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 550:
    {
      DeclareAndCast(StepFEA_GeometricNode, anent, ent);
      RWStepFEA_RWGeometricNode tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 551:
    {
      DeclareAndCast(StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion, anent, ent);
      RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 552:
    {
      DeclareAndCast(StepFEA_NodeGroup, anent, ent);
      RWStepFEA_RWNodeGroup tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 553:
    {
      DeclareAndCast(StepFEA_NodeRepresentation, anent, ent);
      RWStepFEA_RWNodeRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 554:
    {
      DeclareAndCast(StepFEA_NodeSet, anent, ent);
      RWStepFEA_RWNodeSet tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 555:
    {
      DeclareAndCast(StepFEA_NodeWithSolutionCoordinateSystem, anent, ent);
      RWStepFEA_RWNodeWithSolutionCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 556:
    {
      DeclareAndCast(StepFEA_NodeWithVector, anent, ent);
      RWStepFEA_RWNodeWithVector tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 557:
    {
      DeclareAndCast(StepFEA_ParametricCurve3dElementCoordinateDirection, anent, ent);
      RWStepFEA_RWParametricCurve3dElementCoordinateDirection tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 558:
    {
      DeclareAndCast(StepFEA_ParametricCurve3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWParametricCurve3dElementCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 559:
    {
      DeclareAndCast(StepFEA_ParametricSurface3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWParametricSurface3dElementCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 560:
    {
      DeclareAndCast(StepFEA_Surface3dElementRepresentation, anent, ent);
      RWStepFEA_RWSurface3dElementRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 564:
    {
      DeclareAndCast(StepFEA_Volume3dElementRepresentation, anent, ent);
      RWStepFEA_RWVolume3dElementRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 565:
    {
      DeclareAndCast(StepRepr_DataEnvironment, anent, ent);
      RWStepRepr_RWDataEnvironment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 566:
    {
      DeclareAndCast(StepRepr_MaterialPropertyRepresentation, anent, ent);
      RWStepRepr_RWMaterialPropertyRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 567:
    {
      DeclareAndCast(StepRepr_PropertyDefinitionRelationship, anent, ent);
      RWStepRepr_RWPropertyDefinitionRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 568:
    {
      DeclareAndCast(StepShape_PointRepresentation, anent, ent);
      RWStepShape_RWPointRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 569:
    {
      DeclareAndCast(StepRepr_MaterialProperty, anent, ent);
      RWStepRepr_RWMaterialProperty tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 570:
    {
      DeclareAndCast(StepFEA_FeaModelDefinition, anent, ent);
      RWStepFEA_RWFeaModelDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 571:
    {
      DeclareAndCast(StepFEA_FreedomAndCoefficient, anent, ent);
      RWStepFEA_RWFreedomAndCoefficient tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 572:
    {
      DeclareAndCast(StepFEA_FreedomsList, anent, ent);
      RWStepFEA_RWFreedomsList tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 573:
    {
      DeclareAndCast(StepBasic_ProductDefinitionFormationRelationship, anent, ent);
      RWStepBasic_RWProductDefinitionFormationRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 574:
    {
      DeclareAndCast(StepBasic_SiUnitAndMassUnit, anent, ent);
      RWStepBasic_RWSiUnitAndMassUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 575:
    {
      DeclareAndCast(StepFEA_NodeDefinition, anent, ent);
      RWStepFEA_RWNodeDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 576:
    {
      DeclareAndCast(StepRepr_StructuralResponseProperty, anent, ent);
      RWStepRepr_RWStructuralResponseProperty tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 577:
    {
      DeclareAndCast(StepRepr_StructuralResponsePropertyDefinitionRepresentation, anent, ent);
      RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 578:
    {
      DeclareAndCast(StepBasic_SiUnitAndThermodynamicTemperatureUnit, anent, ent);
      RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }

    break;
    case 579:
    {
      DeclareAndCast(StepFEA_AlignedSurface3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWAlignedSurface3dElementCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 580:
    {
      DeclareAndCast(StepFEA_ConstantSurface3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWConstantSurface3dElementCoordinateSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 581:
    {
      DeclareAndCast(StepFEA_CurveElementIntervalLinearlyVarying, anent, ent);
      RWStepFEA_RWCurveElementIntervalLinearlyVarying tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 582:
    {
      DeclareAndCast(StepFEA_FeaCurveSectionGeometricRelationship, anent, ent);
      RWStepFEA_RWFeaCurveSectionGeometricRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 583:
    {
      DeclareAndCast(StepFEA_FeaSurfaceSectionGeometricRelationship, anent, ent);
      RWStepFEA_RWFeaSurfaceSectionGeometricRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 600:
    {
      DeclareAndCast(StepBasic_DocumentProductAssociation, anent, ent);
      RWStepBasic_RWDocumentProductAssociation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 601:
    {
      DeclareAndCast(StepBasic_DocumentProductEquivalence, anent, ent);
      RWStepBasic_RWDocumentProductEquivalence tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 609:
    {
      DeclareAndCast(StepDimTol_CylindricityTolerance, anent, ent);
      RWStepDimTol_RWCylindricityTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 610:
    {
      DeclareAndCast(StepShape_ShapeRepresentationWithParameters, anent, ent);
      RWStepShape_RWShapeRepresentationWithParameters tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 611:
    {
      DeclareAndCast(StepDimTol_AngularityTolerance, anent, ent);
      RWStepDimTol_RWAngularityTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 612:
    {
      DeclareAndCast(StepDimTol_ConcentricityTolerance, anent, ent);
      RWStepDimTol_RWConcentricityTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 613:
    {
      DeclareAndCast(StepDimTol_CircularRunoutTolerance, anent, ent);
      RWStepDimTol_RWCircularRunoutTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 614:
    {
      DeclareAndCast(StepDimTol_CoaxialityTolerance, anent, ent);
      RWStepDimTol_RWCoaxialityTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 615:
    {
      DeclareAndCast(StepDimTol_FlatnessTolerance, anent, ent);
      RWStepDimTol_RWFlatnessTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 616:
    {
      DeclareAndCast(StepDimTol_LineProfileTolerance, anent, ent);
      RWStepDimTol_RWLineProfileTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 617:
    {
      DeclareAndCast(StepDimTol_ParallelismTolerance, anent, ent);
      RWStepDimTol_RWParallelismTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 618:
    {
      DeclareAndCast(StepDimTol_PerpendicularityTolerance, anent, ent);
      RWStepDimTol_RWPerpendicularityTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 619:
    {
      DeclareAndCast(StepDimTol_PositionTolerance, anent, ent);
      RWStepDimTol_RWPositionTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 620:
    {
      DeclareAndCast(StepDimTol_RoundnessTolerance, anent, ent);
      RWStepDimTol_RWRoundnessTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 621:
    {
      DeclareAndCast(StepDimTol_StraightnessTolerance, anent, ent);
      RWStepDimTol_RWStraightnessTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 622:
    {
      DeclareAndCast(StepDimTol_SurfaceProfileTolerance, anent, ent);
      RWStepDimTol_RWSurfaceProfileTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 623:
    {
      DeclareAndCast(StepDimTol_SymmetryTolerance, anent, ent);
      RWStepDimTol_RWSymmetryTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 624:
    {
      DeclareAndCast(StepDimTol_TotalRunoutTolerance, anent, ent);
      RWStepDimTol_RWTotalRunoutTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 625:
    {
      DeclareAndCast(StepDimTol_GeometricTolerance, anent, ent);
      RWStepDimTol_RWGeometricTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 626:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceRelationship, anent, ent);
      RWStepDimTol_RWGeometricToleranceRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 627:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithDatumReference, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithDatumReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 628:
    {
      DeclareAndCast(StepDimTol_ModifiedGeometricTolerance, anent, ent);
      RWStepDimTol_RWModifiedGeometricTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 629:
    {
      DeclareAndCast(StepDimTol_Datum, anent, ent);
      RWStepDimTol_RWDatum tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 630:
    {
      DeclareAndCast(StepDimTol_DatumFeature, anent, ent);
      RWStepDimTol_RWDatumFeature tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 631:
    {
      DeclareAndCast(StepDimTol_DatumReference, anent, ent);
      RWStepDimTol_RWDatumReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 632:
    {
      DeclareAndCast(StepDimTol_CommonDatum, anent, ent);
      RWStepDimTol_RWCommonDatum tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 633:
    {
      DeclareAndCast(StepDimTol_DatumTarget, anent, ent);
      RWStepDimTol_RWDatumTarget tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 634:
    {
      DeclareAndCast(StepDimTol_PlacedDatumTargetFeature, anent, ent);
      RWStepDimTol_RWPlacedDatumTargetFeature tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 635:
    {
      DeclareAndCast(StepRepr_ReprItemAndLengthMeasureWithUnit, anent, ent);
      RWStepRepr_RWReprItemAndLengthMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 636:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 650:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndMassUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndMassUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 651:
    {
      DeclareAndCast(StepBasic_MassMeasureWithUnit, anent, ent);
      RWStepBasic_RWMassMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 660:
    {
      DeclareAndCast(StepRepr_Apex, anent, ent);
      RWStepRepr_RWApex tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 661:
    {
      DeclareAndCast(StepRepr_CentreOfSymmetry, anent, ent);
      RWStepRepr_RWCentreOfSymmetry tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 662:
    {
      DeclareAndCast(StepRepr_GeometricAlignment, anent, ent);
      RWStepRepr_RWGeometricAlignment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 663:
    {
      DeclareAndCast(StepRepr_PerpendicularTo, anent, ent);
      RWStepRepr_RWPerpendicularTo tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 664:
    {
      DeclareAndCast(StepRepr_Tangent, anent, ent);
      RWStepRepr_RWTangent tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 665:
    {
      DeclareAndCast(StepRepr_ParallelOffset, anent, ent);
      RWStepRepr_RWParallelOffset tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 666:
    {
      DeclareAndCast(StepAP242_GeometricItemSpecificUsage, anent, ent);
      RWStepAP242_RWGeometricItemSpecificUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 667:
    {
      DeclareAndCast(StepAP242_IdAttribute, anent, ent);
      RWStepAP242_RWIdAttribute tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 668:
    {
      DeclareAndCast(StepAP242_ItemIdentifiedRepresentationUsage, anent, ent);
      RWStepAP242_RWItemIdentifiedRepresentationUsage tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 669:
    {
      DeclareAndCast(StepRepr_AllAroundShapeAspect, anent, ent);
      RWStepRepr_RWAllAroundShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 670:
    {
      DeclareAndCast(StepRepr_BetweenShapeAspect, anent, ent);
      RWStepRepr_RWBetweenShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 671:
    {
      DeclareAndCast(StepRepr_CompositeGroupShapeAspect, anent, ent);
      RWStepRepr_RWCompositeGroupShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 672:
    {
      DeclareAndCast(StepRepr_ContinuosShapeAspect, anent, ent);
      RWStepRepr_RWContinuosShapeAspect tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 673:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithDefinedAreaUnit, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 674:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithDefinedUnit, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithDefinedUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 675:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithMaximumTolerance, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithMaximumTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 676:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithModifiers, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithModifiers tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 677:
    {
      DeclareAndCast(StepDimTol_UnequallyDisposedGeometricTolerance, anent, ent);
      RWStepDimTol_RWUnequallyDisposedGeometricTolerance tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 678:
    {
      DeclareAndCast(StepDimTol_NonUniformZoneDefinition, anent, ent);
      RWStepDimTol_RWNonUniformZoneDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 679:
    {
      DeclareAndCast(StepDimTol_ProjectedZoneDefinition, anent, ent);
      RWStepDimTol_RWProjectedZoneDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 680:
    {
      DeclareAndCast(StepDimTol_RunoutZoneDefinition, anent, ent);
      RWStepDimTol_RWRunoutZoneDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 681:
    {
      DeclareAndCast(StepDimTol_RunoutZoneOrientation, anent, ent);
      RWStepDimTol_RWRunoutZoneOrientation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 682:
    {
      DeclareAndCast(StepDimTol_ToleranceZone, anent, ent);
      RWStepDimTol_RWToleranceZone tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 683:
    {
      DeclareAndCast(StepDimTol_ToleranceZoneDefinition, anent, ent);
      RWStepDimTol_RWToleranceZoneDefinition tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 684:
    {
      DeclareAndCast(StepDimTol_ToleranceZoneForm, anent, ent);
      RWStepDimTol_RWToleranceZoneForm tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 685:
    {
      DeclareAndCast(StepShape_ValueFormatTypeQualifier, anent, ent);
      RWStepShape_RWValueFormatTypeQualifier tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 686:
    {
      DeclareAndCast(StepDimTol_DatumReferenceCompartment, anent, ent);
      RWStepDimTol_RWDatumReferenceCompartment tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 687:
    {
      DeclareAndCast(StepDimTol_DatumReferenceElement, anent, ent);
      RWStepDimTol_RWDatumReferenceElement tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 688:
    {
      DeclareAndCast(StepDimTol_DatumReferenceModifierWithValue, anent, ent);
      RWStepDimTol_RWDatumReferenceModifierWithValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 689:
    {
      DeclareAndCast(StepDimTol_DatumSystem, anent, ent);
      RWStepDimTol_RWDatumSystem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 690:
    {
      DeclareAndCast(StepDimTol_GeneralDatumReference, anent, ent);
      RWStepDimTol_RWGeneralDatumReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 691:
    {
      DeclareAndCast(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit, anent, ent);
      RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnit tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 692:
    {
      DeclareAndCast(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI, anent, ent);
      RWStepRepr_RWReprItemAndLengthMeasureWithUnitAndQRI tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 693:
    {
      DeclareAndCast(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI, anent, ent);
      RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 694:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRef, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRef tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 695:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndGeoTolWthMod tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 696:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthMod, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthMod tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 697:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndUneqDisGeoTol tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 698:
    {
      DeclareAndCast(StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp, anent, ent);
      RWStepRepr_RWCompGroupShAspAndCompShAspAndDatumFeatAndShAsp tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 699:
    {
      DeclareAndCast(StepRepr_CompShAspAndDatumFeatAndShAsp, anent, ent);
      RWStepRepr_RWCompShAspAndDatumFeatAndShAsp tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 700:
    {
      DeclareAndCast(StepRepr_IntegerRepresentationItem, anent, ent);
      RWStepRepr_RWIntegerRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 701:
    {
      DeclareAndCast(StepRepr_ValueRepresentationItem, anent, ent);
      RWStepRepr_RWValueRepresentationItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 702:
    {
      DeclareAndCast(StepRepr_FeatureForDatumTargetRelationship, anent, ent);
      RWStepRepr_RWFeatureForDatumTargetRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 703:
    {
      DeclareAndCast(StepAP242_DraughtingModelItemAssociation, anent, ent);
      RWStepAP242_RWDraughtingModelItemAssociation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 704:
    {
      DeclareAndCast(StepVisual_AnnotationPlane, anent, ent);
      RWStepVisual_RWAnnotationPlane tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 705:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 706:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthMaxTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthMaxTol tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 707:
    {
      DeclareAndCast(StepVisual_TessellatedAnnotationOccurrence, anent, ent);
      RWStepVisual_RWTessellatedAnnotationOccurrence tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 708:
    {
      DeclareAndCast(StepVisual_TessellatedItem, anent, ent);
      RWStepVisual_RWTessellatedItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;

    case 709:
    {
      DeclareAndCast(StepVisual_TessellatedGeometricSet, anent, ent);
      RWStepVisual_RWTessellatedGeometricSet tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 710:
    {
      DeclareAndCast(StepVisual_TessellatedCurveSet, anent, ent);
      RWStepVisual_RWTessellatedCurveSet tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 711:
    {
      DeclareAndCast(StepVisual_CoordinatesList, anent, ent);
      RWStepVisual_RWCoordinatesList tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 712:
    {
      DeclareAndCast(StepRepr_ConstructiveGeometryRepresentation, anent, ent);
      RWStepRepr_RWConstructiveGeometryRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 713:
    {
      DeclareAndCast(StepRepr_ConstructiveGeometryRepresentationRelationship, anent, ent);
      RWStepRepr_RWConstructiveGeometryRepresentationRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 714:
    {
      DeclareAndCast(StepRepr_CharacterizedRepresentation, anent, ent);
      RWStepRepr_RWCharacterizedRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 715:
    {
      DeclareAndCast(StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel, anent, ent);
      RWStepVisual_RWCharacterizedObjAndRepresentationAndDraughtingModel tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 716:
    {
      DeclareAndCast(StepVisual_CameraModelD3MultiClipping, anent, ent);
      RWStepVisual_RWCameraModelD3MultiClipping tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 717:
    {
      DeclareAndCast(StepVisual_CameraModelD3MultiClippingIntersection, anent, ent);
      RWStepVisual_RWCameraModelD3MultiClippingIntersection tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 718:
    {
      DeclareAndCast(StepVisual_CameraModelD3MultiClippingUnion, anent, ent);
      RWStepVisual_RWCameraModelD3MultiClippingUnion tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 719:
    {
      DeclareAndCast(StepVisual_AnnotationCurveOccurrenceAndGeomReprItem, anent, ent);
      RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 720:
    {
      DeclareAndCast(StepVisual_SurfaceStyleTransparent, anent, ent);
      RWStepVisual_RWSurfaceStyleTransparent tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 721:
    {
      DeclareAndCast(StepVisual_SurfaceStyleReflectanceAmbient, anent, ent);
      RWStepVisual_RWSurfaceStyleReflectanceAmbient tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 722:
    {
      DeclareAndCast(StepVisual_SurfaceStyleRendering, anent, ent);
      RWStepVisual_RWSurfaceStyleRendering tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 723:
    {
      DeclareAndCast(StepVisual_SurfaceStyleRenderingWithProperties, anent, ent);
      RWStepVisual_RWSurfaceStyleRenderingWithProperties tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 724:
    {
      DeclareAndCast(StepRepr_RepresentationContextReference, anent, ent);
      RWStepRepr_RWRepresentationContextReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 725:
    {
      DeclareAndCast(StepRepr_RepresentationReference, anent, ent);
      RWStepRepr_RWRepresentationReference tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 726:
    {
      DeclareAndCast(StepGeom_SuParameters, anent, ent);
      RWStepGeom_RWSuParameters tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 727:
    {
      DeclareAndCast(StepKinematics_RotationAboutDirection, anent, ent);
      RWStepKinematics_RWRotationAboutDirection tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 728:
    {
      DeclareAndCast(StepKinematics_KinematicJoint, anent, ent);
      RWStepKinematics_RWKinematicJoint tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 729:
    {
      DeclareAndCast(StepKinematics_ActuatedKinematicPair, anent, ent);
      RWStepKinematics_RWActuatedKinematicPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 730:
    {
      DeclareAndCast(StepKinematics_ContextDependentKinematicLinkRepresentation, anent, ent);
      RWStepKinematics_RWContextDependentKinematicLinkRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 731:
    {
      DeclareAndCast(StepKinematics_CylindricalPair, anent, ent);
      RWStepKinematics_RWCylindricalPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 732:
    {
      DeclareAndCast(StepKinematics_CylindricalPairValue, anent, ent);
      RWStepKinematics_RWCylindricalPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 733:
    {
      DeclareAndCast(StepKinematics_CylindricalPairWithRange, anent, ent);
      RWStepKinematics_RWCylindricalPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 734:
    {
      DeclareAndCast(StepKinematics_FullyConstrainedPair, anent, ent);
      RWStepKinematics_RWFullyConstrainedPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 735:
    {
      DeclareAndCast(StepKinematics_GearPair, anent, ent);
      RWStepKinematics_RWGearPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 736:
    {
      DeclareAndCast(StepKinematics_GearPairValue, anent, ent);
      RWStepKinematics_RWGearPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 737:
    {
      DeclareAndCast(StepKinematics_GearPairWithRange, anent, ent);
      RWStepKinematics_RWGearPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 738:
    {
      DeclareAndCast(StepKinematics_HomokineticPair, anent, ent);
      RWStepKinematics_RWHomokineticPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 739:
    {
      DeclareAndCast(StepKinematics_KinematicLink, anent, ent);
      RWStepKinematics_RWKinematicLink tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 740:
    {
      DeclareAndCast(StepKinematics_KinematicLinkRepresentationAssociation, anent, ent);
      RWStepKinematics_RWKinematicLinkRepresentationAssociation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 741:
    {
      DeclareAndCast(StepKinematics_KinematicPropertyMechanismRepresentation, anent, ent);
      RWStepKinematics_RWKinematicPropertyMechanismRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 742:
    {
      DeclareAndCast(StepKinematics_KinematicTopologyStructure, anent, ent);
      RWStepKinematics_RWKinematicTopologyStructure tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 743:
    {
      DeclareAndCast(StepKinematics_LowOrderKinematicPair, anent, ent);
      RWStepKinematics_RWLowOrderKinematicPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 744:
    {
      DeclareAndCast(StepKinematics_LowOrderKinematicPairValue, anent, ent);
      RWStepKinematics_RWLowOrderKinematicPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 745:
    {
      DeclareAndCast(StepKinematics_LowOrderKinematicPairWithRange, anent, ent);
      RWStepKinematics_RWLowOrderKinematicPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 746:
    {
      DeclareAndCast(StepKinematics_MechanismRepresentation, anent, ent);
      RWStepKinematics_RWMechanismRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 747:
    {
      DeclareAndCast(StepKinematics_OrientedJoint, anent, ent);
      RWStepKinematics_RWOrientedJoint tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 748:
    {
      DeclareAndCast(StepKinematics_PlanarCurvePair, anent, ent);
      RWStepKinematics_RWPlanarCurvePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 749:
    {
      DeclareAndCast(StepKinematics_PlanarCurvePairRange, anent, ent);
      RWStepKinematics_RWPlanarCurvePairRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 750:
    {
      DeclareAndCast(StepKinematics_PlanarPair, anent, ent);
      RWStepKinematics_RWPlanarPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 751:
    {
      DeclareAndCast(StepKinematics_PlanarPairValue, anent, ent);
      RWStepKinematics_RWPlanarPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 752:
    {
      DeclareAndCast(StepKinematics_PlanarPairWithRange, anent, ent);
      RWStepKinematics_RWPlanarPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 753:
    {
      DeclareAndCast(StepKinematics_PointOnPlanarCurvePair, anent, ent);
      RWStepKinematics_RWPointOnPlanarCurvePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 754:
    {
      DeclareAndCast(StepKinematics_PointOnPlanarCurvePairValue, anent, ent);
      RWStepKinematics_RWPointOnPlanarCurvePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 755:
    {
      DeclareAndCast(StepKinematics_PointOnPlanarCurvePairWithRange, anent, ent);
      RWStepKinematics_RWPointOnPlanarCurvePairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 756:
    {
      DeclareAndCast(StepKinematics_PointOnSurfacePair, anent, ent);
      RWStepKinematics_RWPointOnSurfacePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 757:
    {
      DeclareAndCast(StepKinematics_PointOnSurfacePairValue, anent, ent);
      RWStepKinematics_RWPointOnSurfacePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 758:
    {
      DeclareAndCast(StepKinematics_PointOnSurfacePairWithRange, anent, ent);
      RWStepKinematics_RWPointOnSurfacePairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 759:
    {
      DeclareAndCast(StepKinematics_PrismaticPair, anent, ent);
      RWStepKinematics_RWPrismaticPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 760:
    {
      DeclareAndCast(StepKinematics_PrismaticPairValue, anent, ent);
      RWStepKinematics_RWPrismaticPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 761:
    {
      DeclareAndCast(StepKinematics_PrismaticPairWithRange, anent, ent);
      RWStepKinematics_RWPrismaticPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 762:
    {
      DeclareAndCast(StepKinematics_ProductDefinitionKinematics, anent, ent);
      RWStepKinematics_RWProductDefinitionKinematics tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 763:
    {
      DeclareAndCast(StepKinematics_ProductDefinitionRelationshipKinematics, anent, ent);
      RWStepKinematics_RWProductDefinitionRelationshipKinematics tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 764:
    {
      DeclareAndCast(StepKinematics_RackAndPinionPair, anent, ent);
      RWStepKinematics_RWRackAndPinionPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 765:
    {
      DeclareAndCast(StepKinematics_RackAndPinionPairValue, anent, ent);
      RWStepKinematics_RWRackAndPinionPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 766:
    {
      DeclareAndCast(StepKinematics_RackAndPinionPairWithRange, anent, ent);
      RWStepKinematics_RWRackAndPinionPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 767:
    {
      DeclareAndCast(StepKinematics_RevolutePair, anent, ent);
      RWStepKinematics_RWRevolutePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 768:
    {
      DeclareAndCast(StepKinematics_RevolutePairValue, anent, ent);
      RWStepKinematics_RWRevolutePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 769:
    {
      DeclareAndCast(StepKinematics_RevolutePairWithRange, anent, ent);
      RWStepKinematics_RWRevolutePairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 770:
    {
      DeclareAndCast(StepKinematics_RollingCurvePair, anent, ent);
      RWStepKinematics_RWRollingCurvePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 771:
    {
      DeclareAndCast(StepKinematics_RollingCurvePairValue, anent, ent);
      RWStepKinematics_RWRollingCurvePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 772:
    {
      DeclareAndCast(StepKinematics_RollingSurfacePair, anent, ent);
      RWStepKinematics_RWRollingSurfacePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 773:
    {
      DeclareAndCast(StepKinematics_RollingSurfacePairValue, anent, ent);
      RWStepKinematics_RWRollingSurfacePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 774:
    {
      DeclareAndCast(StepKinematics_ScrewPair, anent, ent);
      RWStepKinematics_RWScrewPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 775:
    {
      DeclareAndCast(StepKinematics_ScrewPairValue, anent, ent);
      RWStepKinematics_RWScrewPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 776:
    {
      DeclareAndCast(StepKinematics_ScrewPairWithRange, anent, ent);
      RWStepKinematics_RWScrewPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 777:
    {
      DeclareAndCast(StepKinematics_SlidingCurvePair, anent, ent);
      RWStepKinematics_RWSlidingCurvePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 778:
    {
      DeclareAndCast(StepKinematics_SlidingCurvePairValue, anent, ent);
      RWStepKinematics_RWSlidingCurvePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 779:
    {
      DeclareAndCast(StepKinematics_SlidingSurfacePair, anent, ent);
      RWStepKinematics_RWSlidingSurfacePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 780:
    {
      DeclareAndCast(StepKinematics_SlidingSurfacePairValue, anent, ent);
      RWStepKinematics_RWSlidingSurfacePairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 781:
    {
      DeclareAndCast(StepKinematics_SphericalPair, anent, ent);
      RWStepKinematics_RWSphericalPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 782:
    {
      DeclareAndCast(StepKinematics_SphericalPairValue, anent, ent);
      RWStepKinematics_RWSphericalPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 783:
    {
      DeclareAndCast(StepKinematics_SphericalPairWithPin, anent, ent);
      RWStepKinematics_RWSphericalPairWithPin tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 784:
    {
      DeclareAndCast(StepKinematics_SphericalPairWithPinAndRange, anent, ent);
      RWStepKinematics_RWSphericalPairWithPinAndRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 785:
    {
      DeclareAndCast(StepKinematics_SphericalPairWithRange, anent, ent);
      RWStepKinematics_RWSphericalPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 786:
    {
      DeclareAndCast(StepKinematics_SurfacePairWithRange, anent, ent);
      RWStepKinematics_RWSurfacePairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 787:
    {
      DeclareAndCast(StepKinematics_UnconstrainedPair, anent, ent);
      RWStepKinematics_RWUnconstrainedPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 788:
    {
      DeclareAndCast(StepKinematics_UnconstrainedPairValue, anent, ent);
      RWStepKinematics_RWUnconstrainedPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 789:
    {
      DeclareAndCast(StepKinematics_UniversalPair, anent, ent);
      RWStepKinematics_RWUniversalPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 790:
    {
      DeclareAndCast(StepKinematics_UniversalPairValue, anent, ent);
      RWStepKinematics_RWUniversalPairValue tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 791:
    {
      DeclareAndCast(StepKinematics_UniversalPairWithRange, anent, ent);
      RWStepKinematics_RWUniversalPairWithRange tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 792:
    {
      DeclareAndCast(StepKinematics_PairRepresentationRelationship, anent, ent);
      RWStepKinematics_RWPairRepresentationRelationship tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 793:
    {
      DeclareAndCast(StepKinematics_RigidLinkRepresentation, anent, ent);
      RWStepKinematics_RWRigidLinkRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 794:
    {
      DeclareAndCast(StepKinematics_KinematicTopologyDirectedStructure, anent, ent);
      RWStepKinematics_RWKinematicTopologyDirectedStructure tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 795:
    {
      DeclareAndCast(StepKinematics_KinematicTopologyNetworkStructure, anent, ent);
      RWStepKinematics_RWKinematicTopologyNetworkStructure tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 796:
    {
      DeclareAndCast(StepKinematics_LinearFlexibleAndPinionPair, anent, ent);
      RWStepKinematics_RWLinearFlexibleAndPinionPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 797:
    {
      DeclareAndCast(StepKinematics_LinearFlexibleAndPlanarCurvePair, anent, ent);
      RWStepKinematics_RWLinearFlexibleAndPlanarCurvePair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 798:
    {
      DeclareAndCast(StepKinematics_LinearFlexibleLinkRepresentation, anent, ent);
      RWStepKinematics_RWLinearFlexibleLinkRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 800:
    {
      DeclareAndCast(StepKinematics_ActuatedKinPairAndOrderKinPair, anent, ent);
      RWStepKinematics_RWActuatedKinPairAndOrderKinPair tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 801:
    {
      DeclareAndCast(StepKinematics_MechanismStateRepresentation, anent, ent);
      RWStepKinematics_RWMechanismStateRepresentation tool;
      tool.ReadStep(data, num, ach, anent);
    }
    break;
    case 802:
    {
      DeclareAndCast(StepVisual_RepositionedTessellatedGeometricSet, anEnt, ent);
      RWStepVisual_RWRepositionedTessellatedGeometricSet aTool;
      aTool.ReadStep(data, num, ach, anEnt);
      break;
    }
    case 803:
    {
      DeclareAndCast(StepVisual_RepositionedTessellatedItem, anEnt, ent);
      RWStepVisual_RWRepositionedTessellatedItem aTool;
      aTool.ReadStep(data, num, ach, anEnt);
      break;
    }
    case 804:
    {
      DeclareAndCast(StepVisual_TessellatedConnectingEdge, anEnt, ent);
      RWStepVisual_RWTessellatedConnectingEdge aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 805:
    {
      DeclareAndCast(StepVisual_TessellatedEdge, anEnt, ent);
      RWStepVisual_RWTessellatedEdge aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 806:
    {
      DeclareAndCast(StepVisual_TessellatedPointSet, anEnt, ent);
      RWStepVisual_RWTessellatedPointSet aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 807:
    {
      DeclareAndCast(StepVisual_TessellatedShapeRepresentation, anEnt, ent);
      RWStepVisual_RWTessellatedShapeRepresentation aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 808:
    {
      DeclareAndCast(StepVisual_TessellatedShapeRepresentationWithAccuracyParameters, anEnt, ent);
      RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 809:
    {
      DeclareAndCast(StepVisual_TessellatedShell, anEnt, ent);
      RWStepVisual_RWTessellatedShell aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 810:
    {
      DeclareAndCast(StepVisual_TessellatedSolid, anEnt, ent);
      RWStepVisual_RWTessellatedSolid aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 811:
    {
      DeclareAndCast(StepVisual_TessellatedStructuredItem, anEnt, ent);
      RWStepVisual_RWTessellatedStructuredItem aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 812:
    {
      DeclareAndCast(StepVisual_TessellatedVertex, anEnt, ent);
      RWStepVisual_RWTessellatedVertex aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 813:
    {
      DeclareAndCast(StepVisual_TessellatedWire, anEnt, ent);
      RWStepVisual_RWTessellatedWire aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 814:
    {
      DeclareAndCast(StepVisual_TriangulatedFace, anEnt, ent);
      RWStepVisual_RWTriangulatedFace aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 815:
    {
      DeclareAndCast(StepVisual_ComplexTriangulatedFace, anEnt, ent);
      RWStepVisual_RWComplexTriangulatedFace aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 816:
    {
      DeclareAndCast(StepVisual_ComplexTriangulatedSurfaceSet, anEnt, ent);
      RWStepVisual_RWComplexTriangulatedSurfaceSet aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 817:
    {
      DeclareAndCast(StepVisual_CubicBezierTessellatedEdge, anEnt, ent);
      RWStepVisual_RWCubicBezierTessellatedEdge aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 818:
    {
      DeclareAndCast(StepVisual_CubicBezierTriangulatedFace, anEnt, ent);
      RWStepVisual_RWCubicBezierTriangulatedFace aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 819:
    {
      DeclareAndCast(StepVisual_TriangulatedSurfaceSet, anEnt, ent);
      RWStepVisual_RWTriangulatedSurfaceSet aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 820:
    {
      DeclareAndCast(StepBasic_GeneralPropertyAssociation, anEnt, ent);
      RWStepBasic_RWGeneralPropertyAssociation aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 821:
    {
      DeclareAndCast(StepBasic_GeneralPropertyRelationship, anEnt, ent);
      RWStepBasic_RWGeneralPropertyRelationship aTool;
      aTool.ReadStep(data, num, ach, anEnt);
    }
    break;
    case 822:
    {
      DeclareAndCast(StepRepr_BooleanRepresentationItem, anent, ent);
      RWStepRepr_RWBooleanRepresentationItem aTool;
      aTool.ReadStep(data, num, ach, anent);
    }
    break;
    case 823:
    {
      DeclareAndCast(StepRepr_RealRepresentationItem, anent, ent);
      RWStepRepr_RWRealRepresentationItem aTool;
      aTool.ReadStep(data, num, ach, anent);
    }
    break;
    case 824:
    {
      DeclareAndCast(StepRepr_MechanicalDesignAndDraughtingRelationship, anent, ent);
      RWStepRepr_RWMechanicalDesignAndDraughtingRelationship aTool;
      aTool.ReadStep(data, num, ach, anent);
    }
    break;
    case 825:
    {
      DeclareAndCast(StepVisual_SurfaceStyleReflectanceAmbientDiffuse, anent, ent);
      RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuse aTool;
      aTool.ReadStep(data, num, ach, anent);
    }
    break;
    case 826:
    {
      DeclareAndCast(StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular, anent, ent);
      RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular aTool;
      aTool.ReadStep(data, num, ach, anent);
    }
    break;
    default:
      ach->AddFail("Type Mismatch when reading - Entity");
  }
  return;
}

void RWStepAP214_ReadWriteModule::WriteStep(const int                              CN,
                                            StepData_StepWriter&                   SW,
                                            const occ::handle<Standard_Transient>& ent) const
{
  if (CN == 0)
    return;
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(StepBasic_Address, anent, ent);
      RWStepBasic_RWAddress tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 2:
    {
      DeclareAndCast(StepShape_AdvancedBrepShapeRepresentation, anent, ent);
      RWStepShape_RWAdvancedBrepShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 3:
    {
      DeclareAndCast(StepShape_AdvancedFace, anent, ent);
      RWStepShape_RWAdvancedFace tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 4:
    {
      DeclareAndCast(StepVisual_AnnotationCurveOccurrence, anent, ent);
      RWStepVisual_RWAnnotationCurveOccurrence tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 5:
    {
      DeclareAndCast(StepVisual_AnnotationFillArea, anent, ent);
      RWStepVisual_RWAnnotationFillArea tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 6:
    {
      DeclareAndCast(StepVisual_AnnotationFillAreaOccurrence, anent, ent);
      RWStepVisual_RWAnnotationFillAreaOccurrence tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 7:
    {
      DeclareAndCast(StepVisual_AnnotationOccurrence, anent, ent);
      RWStepVisual_RWAnnotationOccurrence tool;
      tool.WriteStep(SW, anent);
    }

    break;
    case 11:
    {
      DeclareAndCast(StepRepr_MappedItem, anent, ent);
      RWStepRepr_RWMappedItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 12:
    {
      DeclareAndCast(StepVisual_StyledItem, anent, ent);
      RWStepVisual_RWStyledItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 13:
    {
      DeclareAndCast(StepBasic_ApplicationContext, anent, ent);
      RWStepBasic_RWApplicationContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 14:
    {
      DeclareAndCast(StepBasic_ApplicationContextElement, anent, ent);
      RWStepBasic_RWApplicationContextElement tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 15:
    {
      DeclareAndCast(StepBasic_ApplicationProtocolDefinition, anent, ent);
      RWStepBasic_RWApplicationProtocolDefinition tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 16:
    {
      DeclareAndCast(StepBasic_Approval, anent, ent);
      RWStepBasic_RWApproval tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 18:
    {
      DeclareAndCast(StepBasic_ApprovalPersonOrganization, anent, ent);
      RWStepBasic_RWApprovalPersonOrganization tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 19:
    {
      DeclareAndCast(StepBasic_ApprovalRelationship, anent, ent);
      RWStepBasic_RWApprovalRelationship tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 20:
    {
      DeclareAndCast(StepBasic_ApprovalRole, anent, ent);
      RWStepBasic_RWApprovalRole tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 21:
    {
      DeclareAndCast(StepBasic_ApprovalStatus, anent, ent);
      RWStepBasic_RWApprovalStatus tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 22:
    {
      DeclareAndCast(StepVisual_AreaInSet, anent, ent);
      RWStepVisual_RWAreaInSet tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 23:
    {
      DeclareAndCast(StepAP214_AutoDesignActualDateAndTimeAssignment, anent, ent);
      RWStepAP214_RWAutoDesignActualDateAndTimeAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 24:
    {
      DeclareAndCast(StepAP214_AutoDesignActualDateAssignment, anent, ent);
      RWStepAP214_RWAutoDesignActualDateAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 25:
    {
      DeclareAndCast(StepAP214_AutoDesignApprovalAssignment, anent, ent);
      RWStepAP214_RWAutoDesignApprovalAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 26:
    {
      DeclareAndCast(StepAP214_AutoDesignDateAndPersonAssignment, anent, ent);
      RWStepAP214_RWAutoDesignDateAndPersonAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 27:
    {
      DeclareAndCast(StepAP214_AutoDesignGroupAssignment, anent, ent);
      RWStepAP214_RWAutoDesignGroupAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 28:
    {
      DeclareAndCast(StepAP214_AutoDesignNominalDateAndTimeAssignment, anent, ent);
      RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 29:
    {
      DeclareAndCast(StepAP214_AutoDesignNominalDateAssignment, anent, ent);
      RWStepAP214_RWAutoDesignNominalDateAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 30:
    {
      DeclareAndCast(StepAP214_AutoDesignOrganizationAssignment, anent, ent);
      RWStepAP214_RWAutoDesignOrganizationAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 31:
    {
      DeclareAndCast(StepAP214_AutoDesignPersonAndOrganizationAssignment, anent, ent);
      RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 32:
    {
      DeclareAndCast(StepAP214_AutoDesignPresentedItem, anent, ent);
      RWStepAP214_RWAutoDesignPresentedItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 33:
    {
      DeclareAndCast(StepAP214_AutoDesignSecurityClassificationAssignment, anent, ent);
      RWStepAP214_RWAutoDesignSecurityClassificationAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 35:
    {
      DeclareAndCast(StepGeom_Axis1Placement, anent, ent);
      RWStepGeom_RWAxis1Placement tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 36:
    {
      DeclareAndCast(StepGeom_Axis2Placement2d, anent, ent);
      RWStepGeom_RWAxis2Placement2d tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 37:
    {
      DeclareAndCast(StepGeom_Axis2Placement3d, anent, ent);
      RWStepGeom_RWAxis2Placement3d tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 38:
    {
      DeclareAndCast(StepGeom_BSplineCurve, anent, ent);
      RWStepGeom_RWBSplineCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 39:
    {
      DeclareAndCast(StepGeom_BSplineCurveWithKnots, anent, ent);
      RWStepGeom_RWBSplineCurveWithKnots tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 40:
    {
      DeclareAndCast(StepGeom_BSplineSurface, anent, ent);
      RWStepGeom_RWBSplineSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 41:
    {
      DeclareAndCast(StepGeom_BSplineSurfaceWithKnots, anent, ent);
      RWStepGeom_RWBSplineSurfaceWithKnots tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 42:
    {
      DeclareAndCast(StepVisual_BackgroundColour, anent, ent);
      RWStepVisual_RWBackgroundColour tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 43:
    {
      DeclareAndCast(StepGeom_BezierCurve, anent, ent);
      RWStepGeom_RWBezierCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 44:
    {
      DeclareAndCast(StepGeom_BezierSurface, anent, ent);
      RWStepGeom_RWBezierSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 45:
    {
      DeclareAndCast(StepShape_Block, anent, ent);
      RWStepShape_RWBlock tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 46:
    {
      DeclareAndCast(StepShape_BooleanResult, anent, ent);
      RWStepShape_RWBooleanResult tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 47:
    {
      DeclareAndCast(StepGeom_BoundaryCurve, anent, ent);
      RWStepGeom_RWBoundaryCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 48:
    {
      DeclareAndCast(StepGeom_BoundedCurve, anent, ent);
      RWStepGeom_RWBoundedCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 49:
    {
      DeclareAndCast(StepGeom_BoundedSurface, anent, ent);
      RWStepGeom_RWBoundedSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 50:
    {
      DeclareAndCast(StepShape_BoxDomain, anent, ent);
      RWStepShape_RWBoxDomain tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 51:
    {
      DeclareAndCast(StepShape_BoxedHalfSpace, anent, ent);
      RWStepShape_RWBoxedHalfSpace tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 52:
    {
      DeclareAndCast(StepShape_BrepWithVoids, anent, ent);
      RWStepShape_RWBrepWithVoids tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 53:
    {
      DeclareAndCast(StepBasic_CalendarDate, anent, ent);
      RWStepBasic_RWCalendarDate tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 54:
    {
      DeclareAndCast(StepVisual_CameraImage, anent, ent);
      RWStepVisual_RWCameraImage tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 55:
    {
      DeclareAndCast(StepVisual_CameraModel, anent, ent);
      RWStepVisual_RWCameraModel tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 56:
    {
      DeclareAndCast(StepVisual_CameraModelD2, anent, ent);
      RWStepVisual_RWCameraModelD2 tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 57:
    {
      DeclareAndCast(StepVisual_CameraModelD3, anent, ent);
      RWStepVisual_RWCameraModelD3 tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 58:
    {
      DeclareAndCast(StepVisual_CameraUsage, anent, ent);
      RWStepVisual_RWCameraUsage tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 59:
    {
      DeclareAndCast(StepGeom_CartesianPoint, anent, ent);
      RWStepGeom_RWCartesianPoint tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 60:
    {
      DeclareAndCast(StepGeom_CartesianTransformationOperator, anent, ent);
      RWStepGeom_RWCartesianTransformationOperator tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 61:
    {
      DeclareAndCast(StepGeom_CartesianTransformationOperator3d, anent, ent);
      RWStepGeom_RWCartesianTransformationOperator3d tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 62:
    {
      DeclareAndCast(StepGeom_Circle, anent, ent);
      RWStepGeom_RWCircle tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 63:
    {
      DeclareAndCast(StepShape_ClosedShell, anent, ent);
      RWStepShape_RWClosedShell tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 64:
    {
      DeclareAndCast(StepVisual_Colour, anent, ent);
      RWStepVisual_RWColour tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 65:
    {
      DeclareAndCast(StepVisual_ColourRgb, anent, ent);
      RWStepVisual_RWColourRgb tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 66:
    {
      DeclareAndCast(StepVisual_ColourSpecification, anent, ent);
      RWStepVisual_RWColourSpecification tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 67:
    {
      DeclareAndCast(StepGeom_CompositeCurve, anent, ent);
      RWStepGeom_RWCompositeCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 68:
    {
      DeclareAndCast(StepGeom_CompositeCurveOnSurface, anent, ent);
      RWStepGeom_RWCompositeCurveOnSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 69:
    {
      DeclareAndCast(StepGeom_CompositeCurveSegment, anent, ent);
      RWStepGeom_RWCompositeCurveSegment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 70:
    {
      DeclareAndCast(StepVisual_CompositeText, anent, ent);
      RWStepVisual_RWCompositeText tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 73:
    {
      DeclareAndCast(StepVisual_CompositeTextWithExtent, anent, ent);
      RWStepVisual_RWCompositeTextWithExtent tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 74:
    {
      DeclareAndCast(StepGeom_Conic, anent, ent);
      RWStepGeom_RWConic tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 75:
    {
      DeclareAndCast(StepGeom_ConicalSurface, anent, ent);
      RWStepGeom_RWConicalSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 76:
    {
      DeclareAndCast(StepShape_ConnectedFaceSet, anent, ent);
      RWStepShape_RWConnectedFaceSet tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 77:
    {
      DeclareAndCast(StepVisual_ContextDependentInvisibility, anent, ent);
      RWStepVisual_RWContextDependentInvisibility tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 78:
    {
      DeclareAndCast(StepVisual_ContextDependentOverRidingStyledItem, anent, ent);
      RWStepVisual_RWContextDependentOverRidingStyledItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 79:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 80:
    {
      DeclareAndCast(StepBasic_CoordinatedUniversalTimeOffset, anent, ent);
      RWStepBasic_RWCoordinatedUniversalTimeOffset tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 82:
    {
      DeclareAndCast(StepShape_CsgShapeRepresentation, anent, ent);
      RWStepShape_RWCsgShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 83:
    {
      DeclareAndCast(StepShape_CsgSolid, anent, ent);
      RWStepShape_RWCsgSolid tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 84:
    {
      DeclareAndCast(StepGeom_Curve, anent, ent);
      RWStepGeom_RWCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 85:
    {
      DeclareAndCast(StepGeom_CurveBoundedSurface, anent, ent);
      RWStepGeom_RWCurveBoundedSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 86:
    {
      DeclareAndCast(StepGeom_CurveReplica, anent, ent);
      RWStepGeom_RWCurveReplica tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 87:
    {
      DeclareAndCast(StepVisual_CurveStyle, anent, ent);
      RWStepVisual_RWCurveStyle tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 88:
    {
      DeclareAndCast(StepVisual_CurveStyleFont, anent, ent);
      RWStepVisual_RWCurveStyleFont tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 89:
    {
      DeclareAndCast(StepVisual_CurveStyleFontPattern, anent, ent);
      RWStepVisual_RWCurveStyleFontPattern tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 90:
    {
      DeclareAndCast(StepGeom_CylindricalSurface, anent, ent);
      RWStepGeom_RWCylindricalSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 91:
    {
      DeclareAndCast(StepBasic_Date, anent, ent);
      RWStepBasic_RWDate tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 92:
    {
      DeclareAndCast(StepBasic_DateAndTime, anent, ent);
      RWStepBasic_RWDateAndTime tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 95:
    {
      DeclareAndCast(StepBasic_DateRole, anent, ent);
      RWStepBasic_RWDateRole tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 96:
    {
      DeclareAndCast(StepBasic_DateTimeRole, anent, ent);
      RWStepBasic_RWDateTimeRole tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 98:
    {
      DeclareAndCast(StepRepr_DefinitionalRepresentation, anent, ent);
      RWStepRepr_RWDefinitionalRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 99:
    {
      DeclareAndCast(StepGeom_DegeneratePcurve, anent, ent);
      RWStepGeom_RWDegeneratePcurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 100:
    {
      DeclareAndCast(StepGeom_DegenerateToroidalSurface, anent, ent);
      RWStepGeom_RWDegenerateToroidalSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 101:
    {
      DeclareAndCast(StepRepr_DescriptiveRepresentationItem, anent, ent);
      RWStepRepr_RWDescriptiveRepresentationItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 104:
    {
      DeclareAndCast(StepBasic_DimensionalExponents, anent, ent);
      RWStepBasic_RWDimensionalExponents tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 105:
    {
      DeclareAndCast(StepGeom_Direction, anent, ent);
      RWStepGeom_RWDirection tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 106:
    {
      DeclareAndCast(StepVisual_StyledItem, anent, ent);
      RWStepVisual_RWStyledItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 107:
    {
      DeclareAndCast(StepVisual_DraughtingCallout, anent, ent);
      RWStepVisual_RWDraughtingCallout tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 108:
    {
      DeclareAndCast(StepVisual_DraughtingPreDefinedColour, anent, ent);
      RWStepVisual_RWDraughtingPreDefinedColour tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 109:
    {
      DeclareAndCast(StepVisual_DraughtingPreDefinedCurveFont, anent, ent);
      RWStepVisual_RWDraughtingPreDefinedCurveFont tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 115:
    {
      DeclareAndCast(StepShape_Edge, anent, ent);
      RWStepShape_RWEdge tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 116:
    {
      DeclareAndCast(StepShape_EdgeCurve, anent, ent);
      RWStepShape_RWEdgeCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 117:
    {
      DeclareAndCast(StepShape_EdgeLoop, anent, ent);
      RWStepShape_RWEdgeLoop tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 118:
    {
      DeclareAndCast(StepGeom_ElementarySurface, anent, ent);
      RWStepGeom_RWElementarySurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 119:
    {
      DeclareAndCast(StepGeom_Ellipse, anent, ent);
      RWStepGeom_RWEllipse tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 120:
    {
      DeclareAndCast(StepGeom_EvaluatedDegeneratePcurve, anent, ent);
      RWStepGeom_RWEvaluatedDegeneratePcurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 121:
    {
      DeclareAndCast(StepBasic_ExternalSource, anent, ent);
      RWStepBasic_RWExternalSource tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 122:
    {
      DeclareAndCast(StepVisual_ExternallyDefinedCurveFont, anent, ent);
      RWStepVisual_RWExternallyDefinedCurveFont tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 124:
    case 126:
    {
      DeclareAndCast(StepBasic_ExternallyDefinedItem, anent, ent);
      RWStepBasic_RWExternallyDefinedItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 128:
    {
      DeclareAndCast(StepShape_ExtrudedAreaSolid, anent, ent);
      RWStepShape_RWExtrudedAreaSolid tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 129:
    {
      DeclareAndCast(StepShape_Face, anent, ent);
      RWStepShape_RWFace tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 131:
    {
      DeclareAndCast(StepShape_FaceBound, anent, ent);
      RWStepShape_RWFaceBound tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 132:
    {
      DeclareAndCast(StepShape_FaceOuterBound, anent, ent);
      RWStepShape_RWFaceOuterBound tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 133:
    {
      DeclareAndCast(StepShape_FaceSurface, anent, ent);
      RWStepShape_RWFaceSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 134:
    {
      DeclareAndCast(StepShape_FacetedBrep, anent, ent);
      RWStepShape_RWFacetedBrep tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 135:
    {
      DeclareAndCast(StepShape_FacetedBrepShapeRepresentation, anent, ent);
      RWStepShape_RWFacetedBrepShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 136:
    {
      DeclareAndCast(StepVisual_FillAreaStyle, anent, ent);
      RWStepVisual_RWFillAreaStyle tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 137:
    {
      DeclareAndCast(StepVisual_FillAreaStyleColour, anent, ent);
      RWStepVisual_RWFillAreaStyleColour tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 141:
    {
      DeclareAndCast(StepRepr_FunctionallyDefinedTransformation, anent, ent);
      RWStepRepr_RWFunctionallyDefinedTransformation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 142:
    {
      DeclareAndCast(StepShape_GeometricCurveSet, anent, ent);
      RWStepShape_RWGeometricCurveSet tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 143:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContext, anent, ent);
      RWStepGeom_RWGeometricRepresentationContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 144:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationItem, anent, ent);
      RWStepGeom_RWGeometricRepresentationItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 145:
    {
      DeclareAndCast(StepShape_GeometricSet, anent, ent);
      RWStepShape_RWGeometricSet tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 146:
    {
      DeclareAndCast(StepShape_GeometricallyBoundedSurfaceShapeRepresentation, anent, ent);
      RWStepShape_RWGeometricallyBoundedSurfaceShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 147:
    {
      DeclareAndCast(StepShape_GeometricallyBoundedWireframeShapeRepresentation, anent, ent);
      RWStepShape_RWGeometricallyBoundedWireframeShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 148:
    {
      DeclareAndCast(StepRepr_GlobalUncertaintyAssignedContext, anent, ent);
      RWStepRepr_RWGlobalUncertaintyAssignedContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 149:
    {
      DeclareAndCast(StepRepr_GlobalUnitAssignedContext, anent, ent);
      RWStepRepr_RWGlobalUnitAssignedContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 150:
    {
      DeclareAndCast(StepBasic_Group, anent, ent);
      RWStepBasic_RWGroup tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 152:
    {
      DeclareAndCast(StepBasic_GroupRelationship, anent, ent);
      RWStepBasic_RWGroupRelationship tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 153:
    {
      DeclareAndCast(StepShape_HalfSpaceSolid, anent, ent);
      RWStepShape_RWHalfSpaceSolid tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 154:
    {
      DeclareAndCast(StepGeom_Hyperbola, anent, ent);
      RWStepGeom_RWHyperbola tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 155:
    {
      DeclareAndCast(StepGeom_IntersectionCurve, anent, ent);
      RWStepGeom_RWIntersectionCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 156:
    {
      DeclareAndCast(StepVisual_Invisibility, anent, ent);
      RWStepVisual_RWInvisibility tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 157:
    {
      DeclareAndCast(StepBasic_LengthMeasureWithUnit, anent, ent);
      RWStepBasic_RWLengthMeasureWithUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 158:
    {
      DeclareAndCast(StepBasic_LengthUnit, anent, ent);
      RWStepBasic_RWLengthUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 159:
    {
      DeclareAndCast(StepGeom_Line, anent, ent);
      RWStepGeom_RWLine tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 160:
    {
      DeclareAndCast(StepBasic_LocalTime, anent, ent);
      RWStepBasic_RWLocalTime tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 161:
    {
      DeclareAndCast(StepShape_Loop, anent, ent);
      RWStepShape_RWLoop tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 162:
    {
      DeclareAndCast(StepShape_ManifoldSolidBrep, anent, ent);
      RWStepShape_RWManifoldSolidBrep tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 163:
    {
      DeclareAndCast(StepShape_ManifoldSurfaceShapeRepresentation, anent, ent);
      RWStepShape_RWManifoldSurfaceShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 164:
    {
      DeclareAndCast(StepRepr_MappedItem, anent, ent);
      RWStepRepr_RWMappedItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 165:
    {
      DeclareAndCast(StepBasic_MeasureWithUnit, anent, ent);
      RWStepBasic_RWMeasureWithUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 166:
    {
      DeclareAndCast(StepVisual_MechanicalDesignGeometricPresentationArea, anent, ent);
      RWStepVisual_RWMechanicalDesignGeometricPresentationArea tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 167:
    {
      DeclareAndCast(StepVisual_MechanicalDesignGeometricPresentationRepresentation, anent, ent);
      RWStepVisual_RWMechanicalDesignGeometricPresentationRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 169:
    {
      DeclareAndCast(StepBasic_NamedUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 171:
    {
      DeclareAndCast(StepGeom_OffsetCurve3d, anent, ent);
      RWStepGeom_RWOffsetCurve3d tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 172:
    {
      DeclareAndCast(StepGeom_OffsetSurface, anent, ent);
      RWStepGeom_RWOffsetSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 174:
    {
      DeclareAndCast(StepShape_OpenShell, anent, ent);
      RWStepShape_RWOpenShell tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 175:
    {
      DeclareAndCast(StepBasic_OrdinalDate, anent, ent);
      RWStepBasic_RWOrdinalDate tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 176:
    {
      DeclareAndCast(StepBasic_Organization, anent, ent);
      RWStepBasic_RWOrganization tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 178:
    {
      DeclareAndCast(StepBasic_OrganizationRole, anent, ent);
      RWStepBasic_RWOrganizationRole tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 179:
    {
      DeclareAndCast(StepBasic_OrganizationalAddress, anent, ent);
      RWStepBasic_RWOrganizationalAddress tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 180:
    {
      DeclareAndCast(StepShape_OrientedClosedShell, anent, ent);
      RWStepShape_RWOrientedClosedShell tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 181:
    {
      DeclareAndCast(StepShape_OrientedEdge, anent, ent);
      RWStepShape_RWOrientedEdge tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 182:
    {
      DeclareAndCast(StepShape_OrientedFace, anent, ent);
      RWStepShape_RWOrientedFace tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 183:
    {
      DeclareAndCast(StepShape_OrientedOpenShell, anent, ent);
      RWStepShape_RWOrientedOpenShell tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 184:
    {
      DeclareAndCast(StepShape_OrientedPath, anent, ent);
      RWStepShape_RWOrientedPath tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 185:
    {
      DeclareAndCast(StepGeom_OuterBoundaryCurve, anent, ent);
      RWStepGeom_RWOuterBoundaryCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 186:
    {
      DeclareAndCast(StepVisual_OverRidingStyledItem, anent, ent);
      RWStepVisual_RWOverRidingStyledItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 187:
    {
      DeclareAndCast(StepGeom_Parabola, anent, ent);
      RWStepGeom_RWParabola tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 188:
    {
      DeclareAndCast(StepRepr_ParametricRepresentationContext, anent, ent);
      RWStepRepr_RWParametricRepresentationContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 189:
    {
      DeclareAndCast(StepShape_Path, anent, ent);
      RWStepShape_RWPath tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 190:
    {
      DeclareAndCast(StepGeom_Pcurve, anent, ent);
      RWStepGeom_RWPcurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 191:
    {
      DeclareAndCast(StepBasic_Person, anent, ent);
      RWStepBasic_RWPerson tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 192:
    {
      DeclareAndCast(StepBasic_PersonAndOrganization, anent, ent);
      RWStepBasic_RWPersonAndOrganization tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 194:
    {
      DeclareAndCast(StepBasic_PersonAndOrganizationRole, anent, ent);
      RWStepBasic_RWPersonAndOrganizationRole tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 195:
    {
      DeclareAndCast(StepBasic_PersonalAddress, anent, ent);
      RWStepBasic_RWPersonalAddress tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 196:
    {
      DeclareAndCast(StepGeom_Placement, anent, ent);
      RWStepGeom_RWPlacement tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 197:
    {
      DeclareAndCast(StepVisual_PlanarBox, anent, ent);
      RWStepVisual_RWPlanarBox tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 198:
    {
      DeclareAndCast(StepVisual_PlanarExtent, anent, ent);
      RWStepVisual_RWPlanarExtent tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 199:
    {
      DeclareAndCast(StepGeom_Plane, anent, ent);
      RWStepGeom_RWPlane tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 200:
    {
      DeclareAndCast(StepBasic_PlaneAngleMeasureWithUnit, anent, ent);
      RWStepBasic_RWPlaneAngleMeasureWithUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 201:
    {
      DeclareAndCast(StepBasic_PlaneAngleUnit, anent, ent);
      RWStepBasic_RWPlaneAngleUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 202:
    {
      DeclareAndCast(StepGeom_Point, anent, ent);
      RWStepGeom_RWPoint tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 203:
    {
      DeclareAndCast(StepGeom_PointOnCurve, anent, ent);
      RWStepGeom_RWPointOnCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 204:
    {
      DeclareAndCast(StepGeom_PointOnSurface, anent, ent);
      RWStepGeom_RWPointOnSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 205:
    {
      DeclareAndCast(StepGeom_PointReplica, anent, ent);
      RWStepGeom_RWPointReplica tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 206:
    {
      DeclareAndCast(StepVisual_PointStyle, anent, ent);
      RWStepVisual_RWPointStyle tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 207:
    {
      DeclareAndCast(StepShape_PolyLoop, anent, ent);
      RWStepShape_RWPolyLoop tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 208:
    {
      DeclareAndCast(StepGeom_Polyline, anent, ent);
      RWStepGeom_RWPolyline tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 209:
    {
      DeclareAndCast(StepVisual_PreDefinedColour, anent, ent);
      RWStepVisual_RWPreDefinedColour tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 210:
    {
      DeclareAndCast(StepVisual_PreDefinedCurveFont, anent, ent);
      RWStepVisual_RWPreDefinedCurveFont tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 211:
    case 213:
    {
      DeclareAndCast(StepVisual_PreDefinedItem, anent, ent);
      RWStepVisual_RWPreDefinedItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 214:
    {
      DeclareAndCast(StepVisual_PresentationArea, anent, ent);
      RWStepVisual_RWPresentationArea tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 215:
    {
      DeclareAndCast(StepVisual_PresentationLayerAssignment, anent, ent);
      RWStepVisual_RWPresentationLayerAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 216:
    {
      DeclareAndCast(StepVisual_PresentationRepresentation, anent, ent);
      RWStepVisual_RWPresentationRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 217:
    {
      DeclareAndCast(StepVisual_PresentationSet, anent, ent);
      RWStepVisual_RWPresentationSet tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 218:
    {
      DeclareAndCast(StepVisual_PresentationSize, anent, ent);
      RWStepVisual_RWPresentationSize tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 219:
    {
      DeclareAndCast(StepVisual_PresentationStyleAssignment, anent, ent);
      RWStepVisual_RWPresentationStyleAssignment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 220:
    {
      DeclareAndCast(StepVisual_PresentationStyleByContext, anent, ent);
      RWStepVisual_RWPresentationStyleByContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 221:
    {
      DeclareAndCast(StepVisual_PresentationView, anent, ent);
      RWStepVisual_RWPresentationView tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 223:
    {
      DeclareAndCast(StepBasic_Product, anent, ent);
      RWStepBasic_RWProduct tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 224:
    {
      DeclareAndCast(StepBasic_ProductCategory, anent, ent);
      RWStepBasic_RWProductCategory tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 225:
    {
      DeclareAndCast(StepBasic_ProductContext, anent, ent);
      RWStepBasic_RWProductContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 227:
    {
      DeclareAndCast(StepBasic_ProductDefinition, anent, ent);
      RWStepBasic_RWProductDefinition tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 228:
    {
      DeclareAndCast(StepBasic_ProductDefinitionContext, anent, ent);
      RWStepBasic_RWProductDefinitionContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 229:
    {
      DeclareAndCast(StepBasic_ProductDefinitionFormation, anent, ent);
      RWStepBasic_RWProductDefinitionFormation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 230:
    {
      DeclareAndCast(StepBasic_ProductDefinitionFormationWithSpecifiedSource, anent, ent);
      RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 231:
    {
      DeclareAndCast(StepRepr_ProductDefinitionShape, anent, ent);
      RWStepRepr_RWProductDefinitionShape tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 232:
    {
      DeclareAndCast(StepBasic_ProductRelatedProductCategory, anent, ent);
      RWStepBasic_RWProductRelatedProductCategory tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 233:
    {
      DeclareAndCast(StepBasic_ProductType, anent, ent);
      RWStepBasic_RWProductType tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 234:
    {
      DeclareAndCast(StepRepr_PropertyDefinition, anent, ent);
      RWStepRepr_RWPropertyDefinition tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 235:
    {
      DeclareAndCast(StepRepr_PropertyDefinitionRepresentation, anent, ent);
      RWStepRepr_RWPropertyDefinitionRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 236:
    {
      DeclareAndCast(StepGeom_QuasiUniformCurve, anent, ent);
      RWStepGeom_RWQuasiUniformCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 237:
    {
      DeclareAndCast(StepGeom_QuasiUniformSurface, anent, ent);
      RWStepGeom_RWQuasiUniformSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 238:
    {
      DeclareAndCast(StepBasic_RatioMeasureWithUnit, anent, ent);
      RWStepBasic_RWRatioMeasureWithUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 239:
    {
      DeclareAndCast(StepGeom_RationalBSplineCurve, anent, ent);
      RWStepGeom_RWRationalBSplineCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 240:
    {
      DeclareAndCast(StepGeom_RationalBSplineSurface, anent, ent);
      RWStepGeom_RWRationalBSplineSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 241:
    {
      DeclareAndCast(StepGeom_RectangularCompositeSurface, anent, ent);
      RWStepGeom_RWRectangularCompositeSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 242:
    {
      DeclareAndCast(StepGeom_RectangularTrimmedSurface, anent, ent);
      RWStepGeom_RWRectangularTrimmedSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 243:
    {
      DeclareAndCast(StepAP214_RepItemGroup, anent, ent);
      RWStepAP214_RWRepItemGroup tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 244:
    {
      DeclareAndCast(StepGeom_ReparametrisedCompositeCurveSegment, anent, ent);
      RWStepGeom_RWReparametrisedCompositeCurveSegment tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 245:
    {
      DeclareAndCast(StepRepr_Representation, anent, ent);
      RWStepRepr_RWRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 246:
    {
      DeclareAndCast(StepRepr_RepresentationContext, anent, ent);
      RWStepRepr_RWRepresentationContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 247:
    {
      DeclareAndCast(StepRepr_RepresentationItem, anent, ent);
      RWStepRepr_RWRepresentationItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 248:
    {
      DeclareAndCast(StepRepr_RepresentationMap, anent, ent);
      RWStepRepr_RWRepresentationMap tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 249:
    {
      DeclareAndCast(StepRepr_RepresentationRelationship, anent, ent);
      RWStepRepr_RWRepresentationRelationship tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 250:
    {
      DeclareAndCast(StepShape_RevolvedAreaSolid, anent, ent);
      RWStepShape_RWRevolvedAreaSolid tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 251:
    {
      DeclareAndCast(StepShape_RightAngularWedge, anent, ent);
      RWStepShape_RWRightAngularWedge tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 252:
    {
      DeclareAndCast(StepShape_RightCircularCone, anent, ent);
      RWStepShape_RWRightCircularCone tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 253:
    {
      DeclareAndCast(StepShape_RightCircularCylinder, anent, ent);
      RWStepShape_RWRightCircularCylinder tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 254:
    {
      DeclareAndCast(StepGeom_SeamCurve, anent, ent);
      RWStepGeom_RWSeamCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 255:
    {
      DeclareAndCast(StepBasic_SecurityClassification, anent, ent);
      RWStepBasic_RWSecurityClassification tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 257:
    {
      DeclareAndCast(StepBasic_SecurityClassificationLevel, anent, ent);
      RWStepBasic_RWSecurityClassificationLevel tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 258:
    {
      DeclareAndCast(StepRepr_ShapeAspect, anent, ent);
      RWStepRepr_RWShapeAspect tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 259:
    {
      DeclareAndCast(StepRepr_ShapeAspectRelationship, anent, ent);
      RWStepRepr_RWShapeAspectRelationship tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 260:
    {
      DeclareAndCast(StepRepr_ShapeAspectTransition, anent, ent);
      RWStepRepr_RWShapeAspectTransition tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 261:
    {
      DeclareAndCast(StepShape_ShapeDefinitionRepresentation, anent, ent);
      RWStepShape_RWShapeDefinitionRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 262:
    {
      DeclareAndCast(StepShape_ShapeRepresentation, anent, ent);
      RWStepShape_RWShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 263:
    {
      DeclareAndCast(StepShape_ShellBasedSurfaceModel, anent, ent);
      RWStepShape_RWShellBasedSurfaceModel tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 264:
    {
      DeclareAndCast(StepBasic_SiUnit, anent, ent);
      RWStepBasic_RWSiUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 265:
    {
      DeclareAndCast(StepBasic_SolidAngleMeasureWithUnit, anent, ent);
      RWStepBasic_RWSolidAngleMeasureWithUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 266:
    {
      DeclareAndCast(StepShape_SolidModel, anent, ent);
      RWStepShape_RWSolidModel tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 267:
    {
      DeclareAndCast(StepShape_SolidReplica, anent, ent);
      RWStepShape_RWSolidReplica tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 268:
    {
      DeclareAndCast(StepShape_Sphere, anent, ent);
      RWStepShape_RWSphere tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 269:
    {
      DeclareAndCast(StepGeom_SphericalSurface, anent, ent);
      RWStepGeom_RWSphericalSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 270:
    {
      DeclareAndCast(StepVisual_StyledItem, anent, ent);
      RWStepVisual_RWStyledItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 271:
    {
      DeclareAndCast(StepGeom_Surface, anent, ent);
      RWStepGeom_RWSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 272:
    {
      DeclareAndCast(StepGeom_SurfaceCurve, anent, ent);
      RWStepGeom_RWSurfaceCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 273:
    {
      DeclareAndCast(StepGeom_SurfaceOfLinearExtrusion, anent, ent);
      RWStepGeom_RWSurfaceOfLinearExtrusion tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 274:
    {
      DeclareAndCast(StepGeom_SurfaceOfRevolution, anent, ent);
      RWStepGeom_RWSurfaceOfRevolution tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 275:
    {
      DeclareAndCast(StepGeom_SurfacePatch, anent, ent);
      RWStepGeom_RWSurfacePatch tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 276:
    {
      DeclareAndCast(StepGeom_SurfaceReplica, anent, ent);
      RWStepGeom_RWSurfaceReplica tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 277:
    {
      DeclareAndCast(StepVisual_SurfaceSideStyle, anent, ent);
      RWStepVisual_RWSurfaceSideStyle tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 278:
    {
      DeclareAndCast(StepVisual_SurfaceStyleBoundary, anent, ent);
      RWStepVisual_RWSurfaceStyleBoundary tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 279:
    {
      DeclareAndCast(StepVisual_SurfaceStyleControlGrid, anent, ent);
      RWStepVisual_RWSurfaceStyleControlGrid tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 280:
    {
      DeclareAndCast(StepVisual_SurfaceStyleFillArea, anent, ent);
      RWStepVisual_RWSurfaceStyleFillArea tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 281:
    {
      DeclareAndCast(StepVisual_SurfaceStyleParameterLine, anent, ent);
      RWStepVisual_RWSurfaceStyleParameterLine tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 282:
    {
      DeclareAndCast(StepVisual_SurfaceStyleSegmentationCurve, anent, ent);
      RWStepVisual_RWSurfaceStyleSegmentationCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 283:
    {
      DeclareAndCast(StepVisual_SurfaceStyleSilhouette, anent, ent);
      RWStepVisual_RWSurfaceStyleSilhouette tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 284:
    {
      DeclareAndCast(StepVisual_SurfaceStyleUsage, anent, ent);
      RWStepVisual_RWSurfaceStyleUsage tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 285:
    {
      DeclareAndCast(StepShape_SweptAreaSolid, anent, ent);
      RWStepShape_RWSweptAreaSolid tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 286:
    {
      DeclareAndCast(StepGeom_SweptSurface, anent, ent);
      RWStepGeom_RWSweptSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 292:
    {
      DeclareAndCast(StepVisual_Template, anent, ent);
      RWStepVisual_RWTemplate tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 293:
    {
      DeclareAndCast(StepVisual_TemplateInstance, anent, ent);
      RWStepVisual_RWTemplateInstance tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 295:
    {
      DeclareAndCast(StepVisual_TextLiteral, anent, ent);
      RWStepVisual_RWTextLiteral tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 300:
    {
      DeclareAndCast(StepVisual_TextStyle, anent, ent);
      RWStepVisual_RWTextStyle tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 301:
    {
      DeclareAndCast(StepVisual_TextStyleForDefinedFont, anent, ent);
      RWStepVisual_RWTextStyleForDefinedFont tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 302:
    {
      DeclareAndCast(StepVisual_TextStyleWithBoxCharacteristics, anent, ent);
      RWStepVisual_RWTextStyleWithBoxCharacteristics tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 304:
    {
      DeclareAndCast(StepShape_TopologicalRepresentationItem, anent, ent);
      RWStepShape_RWTopologicalRepresentationItem tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 305:
    {
      DeclareAndCast(StepGeom_ToroidalSurface, anent, ent);
      RWStepGeom_RWToroidalSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 306:
    {
      DeclareAndCast(StepShape_Torus, anent, ent);
      RWStepShape_RWTorus tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 307:
    {
      DeclareAndCast(StepShape_TransitionalShapeRepresentation, anent, ent);
      RWStepShape_RWTransitionalShapeRepresentation tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 308:
    {
      DeclareAndCast(StepGeom_TrimmedCurve, anent, ent);
      RWStepGeom_RWTrimmedCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 310:
    {
      DeclareAndCast(StepBasic_UncertaintyMeasureWithUnit, anent, ent);
      RWStepBasic_RWUncertaintyMeasureWithUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 311:
    {
      DeclareAndCast(StepGeom_UniformCurve, anent, ent);
      RWStepGeom_RWUniformCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 312:
    {
      DeclareAndCast(StepGeom_UniformSurface, anent, ent);
      RWStepGeom_RWUniformSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 313:
    {
      DeclareAndCast(StepGeom_Vector, anent, ent);
      RWStepGeom_RWVector tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 314:
    {
      DeclareAndCast(StepShape_Vertex, anent, ent);
      RWStepShape_RWVertex tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 315:
    {
      DeclareAndCast(StepShape_VertexLoop, anent, ent);
      RWStepShape_RWVertexLoop tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 316:
    {
      DeclareAndCast(StepShape_VertexPoint, anent, ent);
      RWStepShape_RWVertexPoint tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 317:
    {
      DeclareAndCast(StepVisual_ViewVolume, anent, ent);
      RWStepVisual_RWViewVolume tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 318:
    {
      DeclareAndCast(StepBasic_WeekOfYearAndDayDate, anent, ent);
      RWStepBasic_RWWeekOfYearAndDayDate tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 319:
    {
      DeclareAndCast(StepGeom_UniformCurveAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWUniformCurveAndRationalBSplineCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 320:
    {
      DeclareAndCast(StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 321:
    {
      DeclareAndCast(StepGeom_QuasiUniformCurveAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 322:
    {
      DeclareAndCast(StepGeom_BezierCurveAndRationalBSplineCurve, anent, ent);
      RWStepGeom_RWBezierCurveAndRationalBSplineCurve tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 323:
    {
      DeclareAndCast(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 324:
    {
      DeclareAndCast(StepGeom_UniformSurfaceAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 325:
    {
      DeclareAndCast(StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 326:
    {
      DeclareAndCast(StepGeom_BezierSurfaceAndRationalBSplineSurface, anent, ent);
      RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 327:
    {
      DeclareAndCast(StepBasic_SiUnitAndLengthUnit, anent, ent);
      RWStepBasic_RWSiUnitAndLengthUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 328:
    {
      DeclareAndCast(StepBasic_SiUnitAndPlaneAngleUnit, anent, ent);
      RWStepBasic_RWSiUnitAndPlaneAngleUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 329:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndLengthUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndLengthUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 330:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndPlaneAngleUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 331:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext,
                     anent,
                     ent);
      RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext tool;

      tool.WriteStep(SW, anent);
    }

    break;
    case 332:
    {
      DeclareAndCast(StepShape_LoopAndPath, anent, ent);
      RWStepShape_RWLoopAndPath tool;

      tool.WriteStep(SW, anent);
    }

    break;

    case 333:
    {
      DeclareAndCast(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx, anent, ent);
      RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx tool;

      tool.WriteStep(SW, anent);
    }
    break;

    case 334:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndSolidAngleUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndSolidAngleUnit tool;

      tool.WriteStep(SW, anent);
    }
    break;

    case 335:
    {
      DeclareAndCast(StepBasic_SiUnitAndSolidAngleUnit, anent, ent);
      RWStepBasic_RWSiUnitAndSolidAngleUnit tool;

      tool.WriteStep(SW, anent);
    }
    break;
    case 336:
    {
      DeclareAndCast(StepBasic_SolidAngleUnit, anent, ent);
      RWStepBasic_RWSolidAngleUnit tool;

      tool.WriteStep(SW, anent);
    }
    break;
    case 337:
    {
      DeclareAndCast(StepShape_FacetedBrepAndBrepWithVoids, anent, ent);
      RWStepShape_RWFacetedBrepAndBrepWithVoids tool;

      tool.WriteStep(SW, anent);
    }
    break;
    case 338:
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContextAndParametricRepresentationContext,
                     anent,
                     ent);
      RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext tool;

      tool.WriteStep(SW, anent);
    }
    break;
    case 339:
    {
      DeclareAndCast(StepBasic_MechanicalContext, anent, ent);
      RWStepBasic_RWMechanicalContext tool;

      tool.WriteStep(SW, anent);
    }
    break;

    case 340:
    {
      DeclareAndCast(StepBasic_ProductDefinitionContext, anent, ent);
      RWStepBasic_RWProductDefinitionContext tool;

      tool.WriteStep(SW, anent);
      break;
    }

    case 341:
    {
      DeclareAndCast(StepBasic_MeasureWithUnit, anent, ent);
      RWStepBasic_RWMeasureWithUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 342:
    case 343:
    {
      DeclareAndCast(StepBasic_NamedUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 344:
    {
      DeclareAndCast(StepBasic_SiUnitAndRatioUnit, anent, ent);
      RWStepBasic_RWSiUnitAndRatioUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 345:
    {
      DeclareAndCast(StepBasic_SiUnitAndTimeUnit, anent, ent);
      RWStepBasic_RWSiUnitAndTimeUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 346:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndRatioUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndRatioUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 347:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndTimeUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndTimeUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 348:
    {
      DeclareAndCast(StepBasic_ApprovalDateTime, anent, ent);
      RWStepBasic_RWApprovalDateTime tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 349:
    case 350:
    {
      DeclareAndCast(StepVisual_CameraImage, anent, ent);
      RWStepVisual_RWCameraImage tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 351:
    {
      DeclareAndCast(StepGeom_CartesianTransformationOperator, anent, ent);
      RWStepGeom_RWCartesianTransformationOperator tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 352:
    {
      DeclareAndCast(StepBasic_DerivedUnit, anent, ent);
      RWStepBasic_RWDerivedUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 353:
    {
      DeclareAndCast(StepBasic_DerivedUnitElement, anent, ent);
      RWStepBasic_RWDerivedUnitElement tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 354:
    {
      DeclareAndCast(StepRepr_ItemDefinedTransformation, anent, ent);
      RWStepRepr_RWItemDefinedTransformation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 355:
    {
      DeclareAndCast(StepVisual_PresentedItemRepresentation, anent, ent);
      RWStepVisual_RWPresentedItemRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 356:
    {
      DeclareAndCast(StepVisual_PresentationLayerUsage, anent, ent);
      RWStepVisual_RWPresentationLayerUsage tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 358:
    {
      DeclareAndCast(StepGeom_SurfaceCurveAndBoundedCurve, anent, ent);
      RWStepGeom_RWSurfaceCurveAndBoundedCurve tool;
      tool.WriteStep(SW, anent);
      break;
    }

    case 366:
    {
      DeclareAndCast(StepAP214_AutoDesignDocumentReference, anent, ent);
      RWStepAP214_RWAutoDesignDocumentReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 367:
    case 368:
    {
      DeclareAndCast(StepBasic_Document, anent, ent);
      RWStepBasic_RWDocument tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 369:
    {
      DeclareAndCast(StepBasic_DocumentRelationship, anent, ent);
      RWStepBasic_RWDocumentRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 370:
    {
      DeclareAndCast(StepBasic_DocumentType, anent, ent);
      RWStepBasic_RWDocumentType tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 371:
    {
      DeclareAndCast(StepBasic_DocumentUsageConstraint, anent, ent);
      RWStepBasic_RWDocumentUsageConstraint tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 372:
    {
      DeclareAndCast(StepBasic_Effectivity, anent, ent);
      RWStepBasic_RWEffectivity tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 373:
    {
      DeclareAndCast(StepBasic_ProductDefinitionEffectivity, anent, ent);
      RWStepBasic_RWProductDefinitionEffectivity tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 374:
    {
      DeclareAndCast(StepBasic_ProductDefinitionRelationship, anent, ent);
      RWStepBasic_RWProductDefinitionRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 375:
    {
      DeclareAndCast(StepBasic_ProductDefinitionWithAssociatedDocuments, anent, ent);
      RWStepBasic_RWProductDefinitionWithAssociatedDocuments tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 376:
    {
      DeclareAndCast(StepBasic_PhysicallyModeledProductDefinition, anent, ent);
      RWStepBasic_RWProductDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 377:
    {
      DeclareAndCast(StepRepr_ProductDefinitionUsage, anent, ent);
      RWStepBasic_RWProductDefinitionRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 378:
    {
      DeclareAndCast(StepRepr_MakeFromUsageOption, anent, ent);
      RWStepRepr_RWMakeFromUsageOption tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 379:
    case 380:
    case 381:
    {
      DeclareAndCast(StepRepr_AssemblyComponentUsage, anent, ent);
      RWStepRepr_RWAssemblyComponentUsage tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 382:
    {
      DeclareAndCast(StepRepr_QuantifiedAssemblyComponentUsage, anent, ent);
      RWStepRepr_RWQuantifiedAssemblyComponentUsage tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 383:
    {
      DeclareAndCast(StepRepr_SpecifiedHigherUsageOccurrence, anent, ent);
      RWStepRepr_RWSpecifiedHigherUsageOccurrence tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 384:
    {
      DeclareAndCast(StepRepr_AssemblyComponentUsageSubstitute, anent, ent);
      RWStepRepr_RWAssemblyComponentUsageSubstitute tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 385:
    {
      DeclareAndCast(StepRepr_SuppliedPartRelationship, anent, ent);
      RWStepBasic_RWProductDefinitionRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 386:
    {
      DeclareAndCast(StepRepr_ExternallyDefinedRepresentation, anent, ent);
      RWStepRepr_RWRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 387:
    {
      DeclareAndCast(StepRepr_ShapeRepresentationRelationship, anent, ent);
      RWStepRepr_RWRepresentationRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 388:
    {
      DeclareAndCast(StepRepr_RepresentationRelationshipWithTransformation, anent, ent);
      RWStepRepr_RWRepresentationRelationshipWithTransformation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 389:
    {
      DeclareAndCast(StepRepr_ShapeRepresentationRelationshipWithTransformation, anent, ent);
      RWStepRepr_RWShapeRepresentationRelationshipWithTransformation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 390:
    {
      DeclareAndCast(StepRepr_MaterialDesignation, anent, ent);
      RWStepRepr_RWMaterialDesignation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 391:
    {
      DeclareAndCast(StepShape_ContextDependentShapeRepresentation, anent, ent);
      RWStepShape_RWContextDependentShapeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 392:
    {
      DeclareAndCast(StepAP214_AppliedDateAndTimeAssignment, anent, ent);
      RWStepAP214_RWAppliedDateAndTimeAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 393:
    {
      DeclareAndCast(StepAP214_AppliedDateAssignment, anent, ent);
      RWStepAP214_RWAppliedDateAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 394:
    {
      DeclareAndCast(StepAP214_AppliedApprovalAssignment, anent, ent);
      RWStepAP214_RWAppliedApprovalAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 395:
    {
      DeclareAndCast(StepAP214_AppliedGroupAssignment, anent, ent);
      RWStepAP214_RWAppliedGroupAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 396:
    {
      DeclareAndCast(StepAP214_AppliedOrganizationAssignment, anent, ent);
      RWStepAP214_RWAppliedOrganizationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 397:
    {
      DeclareAndCast(StepAP214_AppliedPersonAndOrganizationAssignment, anent, ent);
      RWStepAP214_RWAppliedPersonAndOrganizationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 398:
    {
      DeclareAndCast(StepAP214_AppliedPresentedItem, anent, ent);
      RWStepAP214_RWAppliedPresentedItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 399:
    {
      DeclareAndCast(StepAP214_AppliedSecurityClassificationAssignment, anent, ent);
      RWStepAP214_RWAppliedSecurityClassificationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 400:
    {
      DeclareAndCast(StepAP214_AppliedDocumentReference, anent, ent);
      RWStepAP214_RWAppliedDocumentReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 401:
    {
      DeclareAndCast(StepBasic_DocumentFile, anent, ent);
      RWStepBasic_RWDocumentFile tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 402:
    {
      DeclareAndCast(StepBasic_CharacterizedObject, anent, ent);
      RWStepBasic_RWCharacterizedObject tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 403:
    {
      DeclareAndCast(StepShape_ExtrudedFaceSolid, anent, ent);
      RWStepShape_RWExtrudedFaceSolid tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 404:
    {
      DeclareAndCast(StepShape_RevolvedFaceSolid, anent, ent);
      RWStepShape_RWRevolvedFaceSolid tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 405:
    {
      DeclareAndCast(StepShape_SweptFaceSolid, anent, ent);
      RWStepShape_RWSweptFaceSolid tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 406:
    {
      DeclareAndCast(StepRepr_MeasureRepresentationItem, anent, ent);
      RWStepRepr_RWMeasureRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 407:
    {
      DeclareAndCast(StepBasic_AreaUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 408:
    {
      DeclareAndCast(StepBasic_VolumeUnit, anent, ent);
      RWStepBasic_RWNamedUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 409:
    {
      DeclareAndCast(StepBasic_SiUnitAndAreaUnit, anent, ent);
      RWStepBasic_RWSiUnitAndAreaUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 410:
    {
      DeclareAndCast(StepBasic_SiUnitAndVolumeUnit, anent, ent);
      RWStepBasic_RWSiUnitAndVolumeUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 411:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndAreaUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndAreaUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 412:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndVolumeUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndVolumeUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 413:
    {
      DeclareAndCast(StepBasic_Action, anent, ent);
      RWStepBasic_RWAction tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 414:
    {
      DeclareAndCast(StepBasic_ActionAssignment, anent, ent);
      RWStepBasic_RWActionAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 415:
    {
      DeclareAndCast(StepBasic_ActionMethod, anent, ent);
      RWStepBasic_RWActionMethod tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 416:
    {
      DeclareAndCast(StepBasic_ActionRequestAssignment, anent, ent);
      RWStepBasic_RWActionRequestAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 417:
    {
      DeclareAndCast(StepAP203_CcDesignApproval, anent, ent);
      RWStepAP203_RWCcDesignApproval tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 418:
    {
      DeclareAndCast(StepAP203_CcDesignCertification, anent, ent);
      RWStepAP203_RWCcDesignCertification tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 419:
    {
      DeclareAndCast(StepAP203_CcDesignContract, anent, ent);
      RWStepAP203_RWCcDesignContract tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 420:
    {
      DeclareAndCast(StepAP203_CcDesignDateAndTimeAssignment, anent, ent);
      RWStepAP203_RWCcDesignDateAndTimeAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 421:
    {
      DeclareAndCast(StepAP203_CcDesignPersonAndOrganizationAssignment, anent, ent);
      RWStepAP203_RWCcDesignPersonAndOrganizationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 422:
    {
      DeclareAndCast(StepAP203_CcDesignSecurityClassification, anent, ent);
      RWStepAP203_RWCcDesignSecurityClassification tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 423:
    {
      DeclareAndCast(StepAP203_CcDesignSpecificationReference, anent, ent);
      RWStepAP203_RWCcDesignSpecificationReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 424:
    {
      DeclareAndCast(StepBasic_Certification, anent, ent);
      RWStepBasic_RWCertification tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 425:
    {
      DeclareAndCast(StepBasic_CertificationAssignment, anent, ent);
      RWStepBasic_RWCertificationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 426:
    {
      DeclareAndCast(StepBasic_CertificationType, anent, ent);
      RWStepBasic_RWCertificationType tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 427:
    {
      DeclareAndCast(StepAP203_Change, anent, ent);
      RWStepAP203_RWChange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 428:
    {
      DeclareAndCast(StepAP203_ChangeRequest, anent, ent);
      RWStepAP203_RWChangeRequest tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 429:
    {
      DeclareAndCast(StepRepr_ConfigurationDesign, anent, ent);
      RWStepRepr_RWConfigurationDesign tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 430:
    {
      DeclareAndCast(StepRepr_ConfigurationEffectivity, anent, ent);
      RWStepRepr_RWConfigurationEffectivity tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 431:
    {
      DeclareAndCast(StepBasic_Contract, anent, ent);
      RWStepBasic_RWContract tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 432:
    {
      DeclareAndCast(StepBasic_ContractAssignment, anent, ent);
      RWStepBasic_RWContractAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 433:
    {
      DeclareAndCast(StepBasic_ContractType, anent, ent);
      RWStepBasic_RWContractType tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 434:
    {
      DeclareAndCast(StepRepr_ProductConcept, anent, ent);
      RWStepRepr_RWProductConcept tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 435:
    {
      DeclareAndCast(StepBasic_ProductConceptContext, anent, ent);
      RWStepBasic_RWProductConceptContext tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 436:
    {
      DeclareAndCast(StepAP203_StartRequest, anent, ent);
      RWStepAP203_RWStartRequest tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 437:
    {
      DeclareAndCast(StepAP203_StartWork, anent, ent);
      RWStepAP203_RWStartWork tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 438:
    {
      DeclareAndCast(StepBasic_VersionedActionRequest, anent, ent);
      RWStepBasic_RWVersionedActionRequest tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 439:
    {
      DeclareAndCast(StepBasic_ProductCategoryRelationship, anent, ent);
      RWStepBasic_RWProductCategoryRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 440:
    {
      DeclareAndCast(StepBasic_ActionRequestSolution, anent, ent);
      RWStepBasic_RWActionRequestSolution tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 441:
    {
      DeclareAndCast(StepVisual_DraughtingModel, anent, ent);
      RWStepVisual_RWDraughtingModel tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 442:
    {
      DeclareAndCast(StepShape_AngularLocation, anent, ent);
      RWStepShape_RWAngularLocation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 443:
    {
      DeclareAndCast(StepShape_AngularSize, anent, ent);
      RWStepShape_RWAngularSize tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 444:
    {
      DeclareAndCast(StepShape_DimensionalCharacteristicRepresentation, anent, ent);
      RWStepShape_RWDimensionalCharacteristicRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 445:
    {
      DeclareAndCast(StepShape_DimensionalLocation, anent, ent);
      RWStepShape_RWDimensionalLocation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 446:
    {
      DeclareAndCast(StepShape_DimensionalLocationWithPath, anent, ent);
      RWStepShape_RWDimensionalLocationWithPath tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 447:
    {
      DeclareAndCast(StepShape_DimensionalSize, anent, ent);
      RWStepShape_RWDimensionalSize tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 448:
    {
      DeclareAndCast(StepShape_DimensionalSizeWithPath, anent, ent);
      RWStepShape_RWDimensionalSizeWithPath tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 449:
    {
      DeclareAndCast(StepShape_ShapeDimensionRepresentation, anent, ent);
      RWStepShape_RWShapeDimensionRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 450:
    {
      DeclareAndCast(StepBasic_DocumentRepresentationType, anent, ent);
      RWStepBasic_RWDocumentRepresentationType tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 451:
    {
      DeclareAndCast(StepBasic_ObjectRole, anent, ent);
      RWStepBasic_RWObjectRole tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 452:
    {
      DeclareAndCast(StepBasic_RoleAssociation, anent, ent);
      RWStepBasic_RWRoleAssociation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 453:
    {
      DeclareAndCast(StepBasic_IdentificationRole, anent, ent);
      RWStepBasic_RWIdentificationRole tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 454:
    {
      DeclareAndCast(StepBasic_IdentificationAssignment, anent, ent);
      RWStepBasic_RWIdentificationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 455:
    {
      DeclareAndCast(StepBasic_ExternalIdentificationAssignment, anent, ent);
      RWStepBasic_RWExternalIdentificationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 456:
    {
      DeclareAndCast(StepBasic_EffectivityAssignment, anent, ent);
      RWStepBasic_RWEffectivityAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 457:
    {
      DeclareAndCast(StepBasic_NameAssignment, anent, ent);
      RWStepBasic_RWNameAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 458:
    {
      DeclareAndCast(StepBasic_GeneralProperty, anent, ent);
      RWStepBasic_RWGeneralProperty tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 459:
    {
      DeclareAndCast(StepAP214_Class, anent, ent);
      RWStepAP214_RWClass tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 460:
    {
      DeclareAndCast(StepAP214_ExternallyDefinedClass, anent, ent);
      RWStepAP214_RWExternallyDefinedClass tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 461:
    {
      DeclareAndCast(StepAP214_ExternallyDefinedGeneralProperty, anent, ent);
      RWStepAP214_RWExternallyDefinedGeneralProperty tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 462:
    {
      DeclareAndCast(StepAP214_AppliedExternalIdentificationAssignment, anent, ent);
      RWStepAP214_RWAppliedExternalIdentificationAssignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 463:
    {
      DeclareAndCast(StepShape_DefinitionalRepresentationAndShapeRepresentation, anent, ent);
      RWStepShape_RWDefinitionalRepresentationAndShapeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 470:
    {
      DeclareAndCast(StepRepr_CompositeShapeAspect, anent, ent);
      RWStepRepr_RWCompositeShapeAspect tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 471:
    {
      DeclareAndCast(StepRepr_DerivedShapeAspect, anent, ent);
      RWStepRepr_RWDerivedShapeAspect tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 472:
    {
      DeclareAndCast(StepRepr_Extension, anent, ent);
      RWStepRepr_RWExtension tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 473:
    {
      DeclareAndCast(StepShape_DirectedDimensionalLocation, anent, ent);
      RWStepShape_RWDimensionalLocation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 474:
    {
      DeclareAndCast(StepShape_LimitsAndFits, anent, ent);
      RWStepShape_RWLimitsAndFits tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 475:
    {
      DeclareAndCast(StepShape_ToleranceValue, anent, ent);
      RWStepShape_RWToleranceValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 476:
    {
      DeclareAndCast(StepShape_MeasureQualification, anent, ent);
      RWStepShape_RWMeasureQualification tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 477:
    {
      DeclareAndCast(StepShape_PlusMinusTolerance, anent, ent);
      RWStepShape_RWPlusMinusTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 478:
    {
      DeclareAndCast(StepShape_PrecisionQualifier, anent, ent);
      RWStepShape_RWPrecisionQualifier tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 479:
    {
      DeclareAndCast(StepShape_TypeQualifier, anent, ent);
      RWStepShape_RWTypeQualifier tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 480:
    {
      DeclareAndCast(StepShape_QualifiedRepresentationItem, anent, ent);
      RWStepShape_RWQualifiedRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 481:
    {
      DeclareAndCast(StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem, anent, ent);
      RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 482:
    case 483:
    {
      DeclareAndCast(StepRepr_CompoundRepresentationItem, anent, ent);
      RWStepRepr_RWCompoundRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 484:
    {
      DeclareAndCast(StepRepr_ShapeAspectRelationship, anent, ent);
      RWStepRepr_RWShapeAspectRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 485:
    {
      DeclareAndCast(StepShape_CompoundShapeRepresentation, anent, ent);
      RWStepShape_RWCompoundShapeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 486:
    {
      DeclareAndCast(StepShape_ConnectedEdgeSet, anent, ent);
      RWStepShape_RWConnectedEdgeSet tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 487:
    {
      DeclareAndCast(StepShape_ConnectedFaceShapeRepresentation, anent, ent);
      RWStepShape_RWConnectedFaceShapeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 488:
    {
      DeclareAndCast(StepShape_EdgeBasedWireframeModel, anent, ent);
      RWStepShape_RWEdgeBasedWireframeModel tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 489:
    {
      DeclareAndCast(StepShape_EdgeBasedWireframeShapeRepresentation, anent, ent);
      RWStepShape_RWEdgeBasedWireframeShapeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 490:
    {
      DeclareAndCast(StepShape_FaceBasedSurfaceModel, anent, ent);
      RWStepShape_RWFaceBasedSurfaceModel tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 491:
    {
      DeclareAndCast(StepShape_NonManifoldSurfaceShapeRepresentation, anent, ent);
      RWStepShape_RWNonManifoldSurfaceShapeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 492:
    {
      DeclareAndCast(StepGeom_OrientedSurface, anent, ent);
      RWStepGeom_RWOrientedSurface tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 493:
    {
      DeclareAndCast(StepShape_Subface, anent, ent);
      RWStepShape_RWSubface tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 494:
    {
      DeclareAndCast(StepShape_Subedge, anent, ent);
      RWStepShape_RWSubedge tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 495:
    {
      DeclareAndCast(StepShape_SeamEdge, anent, ent);
      RWStepShape_RWSeamEdge tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 496:
    {
      DeclareAndCast(StepShape_ConnectedFaceSubSet, anent, ent);
      RWStepShape_RWConnectedFaceSubSet tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 500:
    {
      DeclareAndCast(StepBasic_EulerAngles, anent, ent);
      RWStepBasic_RWEulerAngles tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 501:
    {
      DeclareAndCast(StepBasic_MassUnit, anent, ent);
      RWStepBasic_RWMassUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 502:
    {
      DeclareAndCast(StepBasic_ThermodynamicTemperatureUnit, anent, ent);
      RWStepBasic_RWThermodynamicTemperatureUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 503:
    {
      DeclareAndCast(StepElement_AnalysisItemWithinRepresentation, anent, ent);
      RWStepElement_RWAnalysisItemWithinRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 504:
    {
      DeclareAndCast(StepElement_Curve3dElementDescriptor, anent, ent);
      RWStepElement_RWCurve3dElementDescriptor tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 505:
    {
      DeclareAndCast(StepElement_CurveElementEndReleasePacket, anent, ent);
      RWStepElement_RWCurveElementEndReleasePacket tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 506:
    {
      DeclareAndCast(StepElement_CurveElementSectionDefinition, anent, ent);
      RWStepElement_RWCurveElementSectionDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 507:
    {
      DeclareAndCast(StepElement_CurveElementSectionDerivedDefinitions, anent, ent);
      RWStepElement_RWCurveElementSectionDerivedDefinitions tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 508:
    {
      DeclareAndCast(StepElement_ElementDescriptor, anent, ent);
      RWStepElement_RWElementDescriptor tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 509:
    {
      DeclareAndCast(StepElement_ElementMaterial, anent, ent);
      RWStepElement_RWElementMaterial tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 510:
    {
      DeclareAndCast(StepElement_Surface3dElementDescriptor, anent, ent);
      RWStepElement_RWSurface3dElementDescriptor tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 511:
    {
      DeclareAndCast(StepElement_SurfaceElementProperty, anent, ent);
      RWStepElement_RWSurfaceElementProperty tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 512:
    {
      DeclareAndCast(StepElement_SurfaceSection, anent, ent);
      RWStepElement_RWSurfaceSection tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 513:
    {
      DeclareAndCast(StepElement_SurfaceSectionField, anent, ent);
      RWStepElement_RWSurfaceSectionField tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 514:
    {
      DeclareAndCast(StepElement_SurfaceSectionFieldConstant, anent, ent);
      RWStepElement_RWSurfaceSectionFieldConstant tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 515:
    {
      DeclareAndCast(StepElement_SurfaceSectionFieldVarying, anent, ent);
      RWStepElement_RWSurfaceSectionFieldVarying tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 516:
    {
      DeclareAndCast(StepElement_UniformSurfaceSection, anent, ent);
      RWStepElement_RWUniformSurfaceSection tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 517:
    {
      DeclareAndCast(StepElement_Volume3dElementDescriptor, anent, ent);
      RWStepElement_RWVolume3dElementDescriptor tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 518:
    {
      DeclareAndCast(StepFEA_AlignedCurve3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWAlignedCurve3dElementCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 519:
    {
      DeclareAndCast(StepFEA_ArbitraryVolume3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWArbitraryVolume3dElementCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 520:
    {
      DeclareAndCast(StepFEA_Curve3dElementProperty, anent, ent);
      RWStepFEA_RWCurve3dElementProperty tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 521:
    {
      DeclareAndCast(StepFEA_Curve3dElementRepresentation, anent, ent);
      RWStepFEA_RWCurve3dElementRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 522:
    {
      DeclareAndCast(StepFEA_Node, anent, ent);
      RWStepFEA_RWNode tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 524:
    {
      DeclareAndCast(StepFEA_CurveElementEndOffset, anent, ent);
      RWStepFEA_RWCurveElementEndOffset tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 525:
    {
      DeclareAndCast(StepFEA_CurveElementEndRelease, anent, ent);
      RWStepFEA_RWCurveElementEndRelease tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 526:
    {
      DeclareAndCast(StepFEA_CurveElementInterval, anent, ent);
      RWStepFEA_RWCurveElementInterval tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 527:
    {
      DeclareAndCast(StepFEA_CurveElementIntervalConstant, anent, ent);
      RWStepFEA_RWCurveElementIntervalConstant tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 528:
    {
      DeclareAndCast(StepFEA_DummyNode, anent, ent);
      RWStepFEA_RWDummyNode tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 529:
    {
      DeclareAndCast(StepFEA_CurveElementLocation, anent, ent);
      RWStepFEA_RWCurveElementLocation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 530:
    {
      DeclareAndCast(StepFEA_ElementGeometricRelationship, anent, ent);
      RWStepFEA_RWElementGeometricRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 531:
    {
      DeclareAndCast(StepFEA_ElementGroup, anent, ent);
      RWStepFEA_RWElementGroup tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 532:
    {
      DeclareAndCast(StepFEA_ElementRepresentation, anent, ent);
      RWStepFEA_RWElementRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 533:
    {
      DeclareAndCast(StepFEA_FeaAreaDensity, anent, ent);
      RWStepFEA_RWFeaAreaDensity tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 534:
    {
      DeclareAndCast(StepFEA_FeaAxis2Placement3d, anent, ent);
      RWStepFEA_RWFeaAxis2Placement3d tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 535:
    {
      DeclareAndCast(StepFEA_FeaGroup, anent, ent);
      RWStepFEA_RWFeaGroup tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 536:
    {
      DeclareAndCast(StepFEA_FeaLinearElasticity, anent, ent);
      RWStepFEA_RWFeaLinearElasticity tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 537:
    {
      DeclareAndCast(StepFEA_FeaMassDensity, anent, ent);
      RWStepFEA_RWFeaMassDensity tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 538:
    {
      DeclareAndCast(StepFEA_FeaMaterialPropertyRepresentation, anent, ent);
      RWStepFEA_RWFeaMaterialPropertyRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 539:
    {
      DeclareAndCast(StepFEA_FeaMaterialPropertyRepresentationItem, anent, ent);
      RWStepFEA_RWFeaMaterialPropertyRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 540:
    {
      DeclareAndCast(StepFEA_FeaModel, anent, ent);
      RWStepFEA_RWFeaModel tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 541:
    {
      DeclareAndCast(StepFEA_FeaModel3d, anent, ent);
      RWStepFEA_RWFeaModel3d tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 542:
    {
      DeclareAndCast(StepFEA_FeaMoistureAbsorption, anent, ent);
      RWStepFEA_RWFeaMoistureAbsorption tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 543:
    {
      DeclareAndCast(StepFEA_FeaParametricPoint, anent, ent);
      RWStepFEA_RWFeaParametricPoint tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 544:
    {
      DeclareAndCast(StepFEA_FeaRepresentationItem, anent, ent);
      RWStepFEA_RWFeaRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 545:
    {
      DeclareAndCast(StepFEA_FeaSecantCoefficientOfLinearThermalExpansion, anent, ent);
      RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 546:
    {
      DeclareAndCast(StepFEA_FeaShellBendingStiffness, anent, ent);
      RWStepFEA_RWFeaShellBendingStiffness tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 547:
    {
      DeclareAndCast(StepFEA_FeaShellMembraneBendingCouplingStiffness, anent, ent);
      RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 548:
    {
      DeclareAndCast(StepFEA_FeaShellMembraneStiffness, anent, ent);
      RWStepFEA_RWFeaShellMembraneStiffness tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 549:
    {
      DeclareAndCast(StepFEA_FeaShellShearStiffness, anent, ent);
      RWStepFEA_RWFeaShellShearStiffness tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 550:
    {
      DeclareAndCast(StepFEA_GeometricNode, anent, ent);
      RWStepFEA_RWGeometricNode tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 551:
    {
      DeclareAndCast(StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion, anent, ent);
      RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 552:
    {
      DeclareAndCast(StepFEA_NodeGroup, anent, ent);
      RWStepFEA_RWNodeGroup tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 553:
    {
      DeclareAndCast(StepFEA_NodeRepresentation, anent, ent);
      RWStepFEA_RWNodeRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 554:
    {
      DeclareAndCast(StepFEA_NodeSet, anent, ent);
      RWStepFEA_RWNodeSet tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 555:
    {
      DeclareAndCast(StepFEA_NodeWithSolutionCoordinateSystem, anent, ent);
      RWStepFEA_RWNodeWithSolutionCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 556:
    {
      DeclareAndCast(StepFEA_NodeWithVector, anent, ent);
      RWStepFEA_RWNodeWithVector tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 557:
    {
      DeclareAndCast(StepFEA_ParametricCurve3dElementCoordinateDirection, anent, ent);
      RWStepFEA_RWParametricCurve3dElementCoordinateDirection tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 558:
    {
      DeclareAndCast(StepFEA_ParametricCurve3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWParametricCurve3dElementCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 559:
    {
      DeclareAndCast(StepFEA_ParametricSurface3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWParametricSurface3dElementCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 560:
    {
      DeclareAndCast(StepFEA_Surface3dElementRepresentation, anent, ent);
      RWStepFEA_RWSurface3dElementRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 564:
    {
      DeclareAndCast(StepFEA_Volume3dElementRepresentation, anent, ent);
      RWStepFEA_RWVolume3dElementRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 565:
    {
      DeclareAndCast(StepRepr_DataEnvironment, anent, ent);
      RWStepRepr_RWDataEnvironment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 566:
    {
      DeclareAndCast(StepRepr_MaterialPropertyRepresentation, anent, ent);
      RWStepRepr_RWMaterialPropertyRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 567:
    {
      DeclareAndCast(StepRepr_PropertyDefinitionRelationship, anent, ent);
      RWStepRepr_RWPropertyDefinitionRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 568:
    {
      DeclareAndCast(StepShape_PointRepresentation, anent, ent);
      RWStepShape_RWPointRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 569:
    {
      DeclareAndCast(StepRepr_MaterialProperty, anent, ent);
      RWStepRepr_RWMaterialProperty tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 570:
    {
      DeclareAndCast(StepFEA_FeaModelDefinition, anent, ent);
      RWStepFEA_RWFeaModelDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 571:
    {
      DeclareAndCast(StepFEA_FreedomAndCoefficient, anent, ent);
      RWStepFEA_RWFreedomAndCoefficient tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 572:
    {
      DeclareAndCast(StepFEA_FreedomsList, anent, ent);
      RWStepFEA_RWFreedomsList tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 573:
    {
      DeclareAndCast(StepBasic_ProductDefinitionFormationRelationship, anent, ent);
      RWStepBasic_RWProductDefinitionFormationRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 574:
    {
      DeclareAndCast(StepBasic_SiUnitAndMassUnit, anent, ent);
      RWStepBasic_RWSiUnitAndMassUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 575:
    {
      DeclareAndCast(StepFEA_NodeDefinition, anent, ent);
      RWStepFEA_RWNodeDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 576:
    {
      DeclareAndCast(StepRepr_StructuralResponseProperty, anent, ent);
      RWStepRepr_RWStructuralResponseProperty tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 577:
    {
      DeclareAndCast(StepRepr_StructuralResponsePropertyDefinitionRepresentation, anent, ent);
      RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 578:
    {
      DeclareAndCast(StepBasic_SiUnitAndThermodynamicTemperatureUnit, anent, ent);
      RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 579:
    {
      DeclareAndCast(StepFEA_AlignedSurface3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWAlignedSurface3dElementCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 580:
    {
      DeclareAndCast(StepFEA_ConstantSurface3dElementCoordinateSystem, anent, ent);
      RWStepFEA_RWConstantSurface3dElementCoordinateSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 581:
    {
      DeclareAndCast(StepFEA_CurveElementIntervalLinearlyVarying, anent, ent);
      RWStepFEA_RWCurveElementIntervalLinearlyVarying tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 582:
    {
      DeclareAndCast(StepFEA_FeaCurveSectionGeometricRelationship, anent, ent);
      RWStepFEA_RWFeaCurveSectionGeometricRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 583:
    {
      DeclareAndCast(StepFEA_FeaSurfaceSectionGeometricRelationship, anent, ent);
      RWStepFEA_RWFeaSurfaceSectionGeometricRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 600:
    {
      DeclareAndCast(StepBasic_DocumentProductAssociation, anent, ent);
      RWStepBasic_RWDocumentProductAssociation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 601:
    {
      DeclareAndCast(StepBasic_DocumentProductEquivalence, anent, ent);
      RWStepBasic_RWDocumentProductEquivalence tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 609:
    {
      DeclareAndCast(StepDimTol_CylindricityTolerance, anent, ent);
      RWStepDimTol_RWCylindricityTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 610:
    {
      DeclareAndCast(StepShape_ShapeRepresentationWithParameters, anent, ent);
      RWStepShape_RWShapeRepresentationWithParameters tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 611:
    {
      DeclareAndCast(StepDimTol_AngularityTolerance, anent, ent);
      RWStepDimTol_RWAngularityTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 612:
    {
      DeclareAndCast(StepDimTol_ConcentricityTolerance, anent, ent);
      RWStepDimTol_RWConcentricityTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 613:
    {
      DeclareAndCast(StepDimTol_CircularRunoutTolerance, anent, ent);
      RWStepDimTol_RWCircularRunoutTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 614:
    {
      DeclareAndCast(StepDimTol_CoaxialityTolerance, anent, ent);
      RWStepDimTol_RWCoaxialityTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 615:
    {
      DeclareAndCast(StepDimTol_FlatnessTolerance, anent, ent);
      RWStepDimTol_RWFlatnessTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 616:
    {
      DeclareAndCast(StepDimTol_LineProfileTolerance, anent, ent);
      RWStepDimTol_RWLineProfileTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 617:
    {
      DeclareAndCast(StepDimTol_ParallelismTolerance, anent, ent);
      RWStepDimTol_RWParallelismTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 618:
    {
      DeclareAndCast(StepDimTol_PerpendicularityTolerance, anent, ent);
      RWStepDimTol_RWPerpendicularityTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 619:
    {
      DeclareAndCast(StepDimTol_PositionTolerance, anent, ent);
      RWStepDimTol_RWPositionTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 620:
    {
      DeclareAndCast(StepDimTol_RoundnessTolerance, anent, ent);
      RWStepDimTol_RWRoundnessTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 621:
    {
      DeclareAndCast(StepDimTol_StraightnessTolerance, anent, ent);
      RWStepDimTol_RWStraightnessTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 622:
    {
      DeclareAndCast(StepDimTol_SurfaceProfileTolerance, anent, ent);
      RWStepDimTol_RWSurfaceProfileTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 623:
    {
      DeclareAndCast(StepDimTol_SymmetryTolerance, anent, ent);
      RWStepDimTol_RWSymmetryTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 624:
    {
      DeclareAndCast(StepDimTol_TotalRunoutTolerance, anent, ent);
      RWStepDimTol_RWTotalRunoutTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 625:
    {
      DeclareAndCast(StepDimTol_GeometricTolerance, anent, ent);
      RWStepDimTol_RWGeometricTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 626:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceRelationship, anent, ent);
      RWStepDimTol_RWGeometricToleranceRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 627:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithDatumReference, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithDatumReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 628:
    {
      DeclareAndCast(StepDimTol_ModifiedGeometricTolerance, anent, ent);
      RWStepDimTol_RWModifiedGeometricTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 629:
    {
      DeclareAndCast(StepDimTol_Datum, anent, ent);
      RWStepDimTol_RWDatum tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 630:
    {
      DeclareAndCast(StepDimTol_DatumFeature, anent, ent);
      RWStepDimTol_RWDatumFeature tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 631:
    {
      DeclareAndCast(StepDimTol_DatumReference, anent, ent);
      RWStepDimTol_RWDatumReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 632:
    {
      DeclareAndCast(StepDimTol_CommonDatum, anent, ent);
      RWStepDimTol_RWCommonDatum tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 633:
    {
      DeclareAndCast(StepDimTol_DatumTarget, anent, ent);
      RWStepDimTol_RWDatumTarget tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 634:
    {
      DeclareAndCast(StepDimTol_PlacedDatumTargetFeature, anent, ent);
      RWStepDimTol_RWPlacedDatumTargetFeature tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 635:
    {
      DeclareAndCast(StepRepr_ReprItemAndLengthMeasureWithUnit, anent, ent);
      RWStepRepr_RWReprItemAndLengthMeasureWithUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 636:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 650:
    {
      DeclareAndCast(StepBasic_ConversionBasedUnitAndMassUnit, anent, ent);
      RWStepBasic_RWConversionBasedUnitAndMassUnit tool;
      tool.WriteStep(SW, anent);
    }

    break;
    case 651:
    {
      DeclareAndCast(StepBasic_MassMeasureWithUnit, anent, ent);
      RWStepBasic_RWMassMeasureWithUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 660:
    {
      DeclareAndCast(StepRepr_Apex, anent, ent);
      RWStepRepr_RWApex tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 661:
    {
      DeclareAndCast(StepRepr_CentreOfSymmetry, anent, ent);
      RWStepRepr_RWCentreOfSymmetry tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 662:
    {
      DeclareAndCast(StepRepr_GeometricAlignment, anent, ent);
      RWStepRepr_RWGeometricAlignment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 663:
    {
      DeclareAndCast(StepRepr_PerpendicularTo, anent, ent);
      RWStepRepr_RWPerpendicularTo tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 664:
    {
      DeclareAndCast(StepRepr_Tangent, anent, ent);
      RWStepRepr_RWTangent tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 665:
    {
      DeclareAndCast(StepRepr_ParallelOffset, anent, ent);
      RWStepRepr_RWParallelOffset tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 666:
    {
      DeclareAndCast(StepAP242_GeometricItemSpecificUsage, anent, ent);
      RWStepAP242_RWGeometricItemSpecificUsage tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 667:
    {
      DeclareAndCast(StepAP242_IdAttribute, anent, ent);
      RWStepAP242_RWIdAttribute tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 668:
    {
      DeclareAndCast(StepAP242_ItemIdentifiedRepresentationUsage, anent, ent);
      RWStepAP242_RWItemIdentifiedRepresentationUsage tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 669:
    {
      DeclareAndCast(StepRepr_AllAroundShapeAspect, anent, ent);
      RWStepRepr_RWAllAroundShapeAspect tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 670:
    {
      DeclareAndCast(StepRepr_BetweenShapeAspect, anent, ent);
      RWStepRepr_RWBetweenShapeAspect tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 671:
    {
      DeclareAndCast(StepRepr_CompositeGroupShapeAspect, anent, ent);
      RWStepRepr_RWCompositeGroupShapeAspect tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 672:
    {
      DeclareAndCast(StepRepr_ContinuosShapeAspect, anent, ent);
      RWStepRepr_RWContinuosShapeAspect tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 673:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithDefinedAreaUnit, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 674:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithDefinedUnit, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithDefinedUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 675:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithMaximumTolerance, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithMaximumTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 676:
    {
      DeclareAndCast(StepDimTol_GeometricToleranceWithModifiers, anent, ent);
      RWStepDimTol_RWGeometricToleranceWithModifiers tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 677:
    {
      DeclareAndCast(StepDimTol_UnequallyDisposedGeometricTolerance, anent, ent);
      RWStepDimTol_RWUnequallyDisposedGeometricTolerance tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 678:
    {
      DeclareAndCast(StepDimTol_NonUniformZoneDefinition, anent, ent);
      RWStepDimTol_RWNonUniformZoneDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 679:
    {
      DeclareAndCast(StepDimTol_ProjectedZoneDefinition, anent, ent);
      RWStepDimTol_RWProjectedZoneDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 680:
    {
      DeclareAndCast(StepDimTol_RunoutZoneDefinition, anent, ent);
      RWStepDimTol_RWRunoutZoneDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 681:
    {
      DeclareAndCast(StepDimTol_RunoutZoneOrientation, anent, ent);
      RWStepDimTol_RWRunoutZoneOrientation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 682:
    {
      DeclareAndCast(StepDimTol_ToleranceZone, anent, ent);
      RWStepDimTol_RWToleranceZone tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 683:
    {
      DeclareAndCast(StepDimTol_ToleranceZoneDefinition, anent, ent);
      RWStepDimTol_RWToleranceZoneDefinition tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 684:
    {
      DeclareAndCast(StepDimTol_ToleranceZoneForm, anent, ent);
      RWStepDimTol_RWToleranceZoneForm tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 685:
    {
      DeclareAndCast(StepShape_ValueFormatTypeQualifier, anent, ent);
      RWStepShape_RWValueFormatTypeQualifier tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 686:
    {
      DeclareAndCast(StepDimTol_DatumReferenceCompartment, anent, ent);
      RWStepDimTol_RWDatumReferenceCompartment tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 687:
    {
      DeclareAndCast(StepDimTol_DatumReferenceElement, anent, ent);
      RWStepDimTol_RWDatumReferenceElement tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 688:
    {
      DeclareAndCast(StepDimTol_DatumReferenceModifierWithValue, anent, ent);
      RWStepDimTol_RWDatumReferenceModifierWithValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 689:
    {
      DeclareAndCast(StepDimTol_DatumSystem, anent, ent);
      RWStepDimTol_RWDatumSystem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 690:
    {
      DeclareAndCast(StepDimTol_GeneralDatumReference, anent, ent);
      RWStepDimTol_RWGeneralDatumReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 691:
    {
      DeclareAndCast(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit, anent, ent);
      RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnit tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 692:
    {
      DeclareAndCast(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI, anent, ent);
      RWStepRepr_RWReprItemAndLengthMeasureWithUnitAndQRI tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 693:
    {
      DeclareAndCast(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI, anent, ent);
      RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 694:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRef, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRef tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 695:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndGeoTolWthMod tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 696:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthMod, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthMod tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 697:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndUneqDisGeoTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndUneqDisGeoTol tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 698:
    {
      DeclareAndCast(StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp, anent, ent);
      RWStepRepr_RWCompGroupShAspAndCompShAspAndDatumFeatAndShAsp tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 699:
    {
      DeclareAndCast(StepRepr_CompShAspAndDatumFeatAndShAsp, anent, ent);
      RWStepRepr_RWCompShAspAndDatumFeatAndShAsp tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 700:
    {
      DeclareAndCast(StepRepr_IntegerRepresentationItem, anent, ent);
      RWStepRepr_RWIntegerRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 701:
    {
      DeclareAndCast(StepRepr_ValueRepresentationItem, anent, ent);
      RWStepRepr_RWValueRepresentationItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 702:
    {
      DeclareAndCast(StepRepr_FeatureForDatumTargetRelationship, anent, ent);
      RWStepRepr_RWFeatureForDatumTargetRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 703:
    {
      DeclareAndCast(StepAP242_DraughtingModelItemAssociation, anent, ent);
      RWStepAP242_RWDraughtingModelItemAssociation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 704:
    {
      DeclareAndCast(StepVisual_AnnotationPlane, anent, ent);
      RWStepVisual_RWAnnotationPlane tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 705:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 706:
    {
      DeclareAndCast(StepDimTol_GeoTolAndGeoTolWthMaxTol, anent, ent);
      RWStepDimTol_RWGeoTolAndGeoTolWthMaxTol tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 707:
    {
      DeclareAndCast(StepVisual_TessellatedAnnotationOccurrence, anent, ent);
      RWStepVisual_RWTessellatedAnnotationOccurrence tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 708:
    {
      DeclareAndCast(StepVisual_TessellatedItem, anent, ent);
      RWStepVisual_RWTessellatedItem tool;
      tool.WriteStep(SW, anent);
    }
    break;

    case 709:
    {
      DeclareAndCast(StepVisual_TessellatedGeometricSet, anent, ent);
      RWStepVisual_RWTessellatedGeometricSet tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 710:
    {
      DeclareAndCast(StepVisual_TessellatedCurveSet, anent, ent);
      RWStepVisual_RWTessellatedCurveSet tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 711:
    {
      DeclareAndCast(StepVisual_CoordinatesList, anent, ent);
      RWStepVisual_RWCoordinatesList tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 712:
    {
      DeclareAndCast(StepRepr_ConstructiveGeometryRepresentation, anent, ent);
      RWStepRepr_RWConstructiveGeometryRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 713:
    {
      DeclareAndCast(StepRepr_ConstructiveGeometryRepresentationRelationship, anent, ent);
      RWStepRepr_RWConstructiveGeometryRepresentationRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 714:
    {
      DeclareAndCast(StepRepr_CharacterizedRepresentation, anent, ent);
      RWStepRepr_RWCharacterizedRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 715:
    {
      DeclareAndCast(StepVisual_CharacterizedObjAndRepresentationAndDraughtingModel, anent, ent);
      RWStepVisual_RWCharacterizedObjAndRepresentationAndDraughtingModel tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 716:
    {
      DeclareAndCast(StepVisual_CameraModelD3MultiClipping, anent, ent);
      RWStepVisual_RWCameraModelD3MultiClipping tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 717:
    {
      DeclareAndCast(StepVisual_CameraModelD3MultiClippingIntersection, anent, ent);
      RWStepVisual_RWCameraModelD3MultiClippingIntersection tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 718:
    {
      DeclareAndCast(StepVisual_CameraModelD3MultiClippingUnion, anent, ent);
      RWStepVisual_RWCameraModelD3MultiClippingUnion tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 719:
    {
      DeclareAndCast(StepVisual_AnnotationCurveOccurrenceAndGeomReprItem, anent, ent);
      RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 720:
    {
      DeclareAndCast(StepVisual_SurfaceStyleTransparent, anent, ent);
      RWStepVisual_RWSurfaceStyleTransparent tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 721:
    {
      DeclareAndCast(StepVisual_SurfaceStyleReflectanceAmbient, anent, ent);
      RWStepVisual_RWSurfaceStyleReflectanceAmbient tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 722:
    {
      DeclareAndCast(StepVisual_SurfaceStyleRendering, anent, ent);
      RWStepVisual_RWSurfaceStyleRendering tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 723:
    {
      DeclareAndCast(StepVisual_SurfaceStyleRenderingWithProperties, anent, ent);
      RWStepVisual_RWSurfaceStyleRenderingWithProperties tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 724:
    {
      DeclareAndCast(StepRepr_RepresentationContextReference, anent, ent);
      RWStepRepr_RWRepresentationContextReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 725:
    {
      DeclareAndCast(StepRepr_RepresentationReference, anent, ent);
      RWStepRepr_RWRepresentationReference tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 726:
    {
      DeclareAndCast(StepGeom_SuParameters, anent, ent);
      RWStepGeom_RWSuParameters tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 727:
    {
      DeclareAndCast(StepKinematics_RotationAboutDirection, anent, ent);
      RWStepKinematics_RWRotationAboutDirection tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 728:
    {
      DeclareAndCast(StepKinematics_KinematicJoint, anent, ent);
      RWStepKinematics_RWKinematicJoint tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 729:
    {
      DeclareAndCast(StepKinematics_ActuatedKinematicPair, anent, ent);
      RWStepKinematics_RWActuatedKinematicPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 730:
    {
      DeclareAndCast(StepKinematics_ContextDependentKinematicLinkRepresentation, anent, ent);
      RWStepKinematics_RWContextDependentKinematicLinkRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 731:
    {
      DeclareAndCast(StepKinematics_CylindricalPair, anent, ent);
      RWStepKinematics_RWCylindricalPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 732:
    {
      DeclareAndCast(StepKinematics_CylindricalPairValue, anent, ent);
      RWStepKinematics_RWCylindricalPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 733:
    {
      DeclareAndCast(StepKinematics_CylindricalPairWithRange, anent, ent);
      RWStepKinematics_RWCylindricalPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 734:
    {
      DeclareAndCast(StepKinematics_FullyConstrainedPair, anent, ent);
      RWStepKinematics_RWFullyConstrainedPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 735:
    {
      DeclareAndCast(StepKinematics_GearPair, anent, ent);
      RWStepKinematics_RWGearPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 736:
    {
      DeclareAndCast(StepKinematics_GearPairValue, anent, ent);
      RWStepKinematics_RWGearPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 737:
    {
      DeclareAndCast(StepKinematics_GearPairWithRange, anent, ent);
      RWStepKinematics_RWGearPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 738:
    {
      DeclareAndCast(StepKinematics_HomokineticPair, anent, ent);
      RWStepKinematics_RWHomokineticPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 739:
    {
      DeclareAndCast(StepKinematics_KinematicLink, anent, ent);
      RWStepKinematics_RWKinematicLink tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 740:
    {
      DeclareAndCast(StepKinematics_KinematicLinkRepresentationAssociation, anent, ent);
      RWStepKinematics_RWKinematicLinkRepresentationAssociation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 741:
    {
      DeclareAndCast(StepKinematics_KinematicPropertyMechanismRepresentation, anent, ent);
      RWStepKinematics_RWKinematicPropertyMechanismRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 742:
    {
      DeclareAndCast(StepKinematics_KinematicTopologyStructure, anent, ent);
      RWStepKinematics_RWKinematicTopologyStructure tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 743:
    {
      DeclareAndCast(StepKinematics_LowOrderKinematicPair, anent, ent);
      RWStepKinematics_RWLowOrderKinematicPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 744:
    {
      DeclareAndCast(StepKinematics_LowOrderKinematicPairValue, anent, ent);
      RWStepKinematics_RWLowOrderKinematicPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 745:
    {
      DeclareAndCast(StepKinematics_LowOrderKinematicPairWithRange, anent, ent);
      RWStepKinematics_RWLowOrderKinematicPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 746:
    {
      DeclareAndCast(StepKinematics_MechanismRepresentation, anent, ent);
      RWStepKinematics_RWMechanismRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 747:
    {
      DeclareAndCast(StepKinematics_OrientedJoint, anent, ent);
      RWStepKinematics_RWOrientedJoint tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 748:
    {
      DeclareAndCast(StepKinematics_PlanarCurvePair, anent, ent);
      RWStepKinematics_RWPlanarCurvePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 749:
    {
      DeclareAndCast(StepKinematics_PlanarCurvePairRange, anent, ent);
      RWStepKinematics_RWPlanarCurvePairRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 750:
    {
      DeclareAndCast(StepKinematics_PlanarPair, anent, ent);
      RWStepKinematics_RWPlanarPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 751:
    {
      DeclareAndCast(StepKinematics_PlanarPairValue, anent, ent);
      RWStepKinematics_RWPlanarPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 752:
    {
      DeclareAndCast(StepKinematics_PlanarPairWithRange, anent, ent);
      RWStepKinematics_RWPlanarPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 753:
    {
      DeclareAndCast(StepKinematics_PointOnPlanarCurvePair, anent, ent);
      RWStepKinematics_RWPointOnPlanarCurvePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 754:
    {
      DeclareAndCast(StepKinematics_PointOnPlanarCurvePairValue, anent, ent);
      RWStepKinematics_RWPointOnPlanarCurvePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 755:
    {
      DeclareAndCast(StepKinematics_PointOnPlanarCurvePairWithRange, anent, ent);
      RWStepKinematics_RWPointOnPlanarCurvePairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 756:
    {
      DeclareAndCast(StepKinematics_PointOnSurfacePair, anent, ent);
      RWStepKinematics_RWPointOnSurfacePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 757:
    {
      DeclareAndCast(StepKinematics_PointOnSurfacePairValue, anent, ent);
      RWStepKinematics_RWPointOnSurfacePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 758:
    {
      DeclareAndCast(StepKinematics_PointOnSurfacePairWithRange, anent, ent);
      RWStepKinematics_RWPointOnSurfacePairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 759:
    {
      DeclareAndCast(StepKinematics_PrismaticPair, anent, ent);
      RWStepKinematics_RWPrismaticPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 760:
    {
      DeclareAndCast(StepKinematics_PrismaticPairValue, anent, ent);
      RWStepKinematics_RWPrismaticPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 761:
    {
      DeclareAndCast(StepKinematics_PrismaticPairWithRange, anent, ent);
      RWStepKinematics_RWPrismaticPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 762:
    {
      DeclareAndCast(StepKinematics_ProductDefinitionKinematics, anent, ent);
      RWStepKinematics_RWProductDefinitionKinematics tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 763:
    {
      DeclareAndCast(StepKinematics_ProductDefinitionRelationshipKinematics, anent, ent);
      RWStepKinematics_RWProductDefinitionRelationshipKinematics tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 764:
    {
      DeclareAndCast(StepKinematics_RackAndPinionPair, anent, ent);
      RWStepKinematics_RWRackAndPinionPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 765:
    {
      DeclareAndCast(StepKinematics_RackAndPinionPairValue, anent, ent);
      RWStepKinematics_RWRackAndPinionPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 766:
    {
      DeclareAndCast(StepKinematics_RackAndPinionPairWithRange, anent, ent);
      RWStepKinematics_RWRackAndPinionPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 767:
    {
      DeclareAndCast(StepKinematics_RevolutePair, anent, ent);
      RWStepKinematics_RWRevolutePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 768:
    {
      DeclareAndCast(StepKinematics_RevolutePairValue, anent, ent);
      RWStepKinematics_RWRevolutePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 769:
    {
      DeclareAndCast(StepKinematics_RevolutePairWithRange, anent, ent);
      RWStepKinematics_RWRevolutePairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 770:
    {
      DeclareAndCast(StepKinematics_RollingCurvePair, anent, ent);
      RWStepKinematics_RWRollingCurvePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 771:
    {
      DeclareAndCast(StepKinematics_RollingCurvePairValue, anent, ent);
      RWStepKinematics_RWRollingCurvePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 772:
    {
      DeclareAndCast(StepKinematics_RollingSurfacePair, anent, ent);
      RWStepKinematics_RWRollingSurfacePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 773:
    {
      DeclareAndCast(StepKinematics_RollingSurfacePairValue, anent, ent);
      RWStepKinematics_RWRollingSurfacePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 774:
    {
      DeclareAndCast(StepKinematics_ScrewPair, anent, ent);
      RWStepKinematics_RWScrewPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 775:
    {
      DeclareAndCast(StepKinematics_ScrewPairValue, anent, ent);
      RWStepKinematics_RWScrewPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 776:
    {
      DeclareAndCast(StepKinematics_ScrewPairWithRange, anent, ent);
      RWStepKinematics_RWScrewPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 777:
    {
      DeclareAndCast(StepKinematics_SlidingCurvePair, anent, ent);
      RWStepKinematics_RWSlidingCurvePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 778:
    {
      DeclareAndCast(StepKinematics_SlidingCurvePairValue, anent, ent);
      RWStepKinematics_RWSlidingCurvePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 779:
    {
      DeclareAndCast(StepKinematics_SlidingSurfacePair, anent, ent);
      RWStepKinematics_RWSlidingSurfacePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 780:
    {
      DeclareAndCast(StepKinematics_SlidingSurfacePairValue, anent, ent);
      RWStepKinematics_RWSlidingSurfacePairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 781:
    {
      DeclareAndCast(StepKinematics_SphericalPair, anent, ent);
      RWStepKinematics_RWSphericalPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 782:
    {
      DeclareAndCast(StepKinematics_SphericalPairValue, anent, ent);
      RWStepKinematics_RWSphericalPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 783:
    {
      DeclareAndCast(StepKinematics_SphericalPairWithPin, anent, ent);
      RWStepKinematics_RWSphericalPairWithPin tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 784:
    {
      DeclareAndCast(StepKinematics_SphericalPairWithPinAndRange, anent, ent);
      RWStepKinematics_RWSphericalPairWithPinAndRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 785:
    {
      DeclareAndCast(StepKinematics_SphericalPairWithRange, anent, ent);
      RWStepKinematics_RWSphericalPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 786:
    {
      DeclareAndCast(StepKinematics_SurfacePairWithRange, anent, ent);
      RWStepKinematics_RWSurfacePairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 787:
    {
      DeclareAndCast(StepKinematics_UnconstrainedPair, anent, ent);
      RWStepKinematics_RWUnconstrainedPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 788:
    {
      DeclareAndCast(StepKinematics_UnconstrainedPairValue, anent, ent);
      RWStepKinematics_RWUnconstrainedPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 789:
    {
      DeclareAndCast(StepKinematics_UniversalPair, anent, ent);
      RWStepKinematics_RWUniversalPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 790:
    {
      DeclareAndCast(StepKinematics_UniversalPairValue, anent, ent);
      RWStepKinematics_RWUniversalPairValue tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 791:
    {
      DeclareAndCast(StepKinematics_UniversalPairWithRange, anent, ent);
      RWStepKinematics_RWUniversalPairWithRange tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 792:
    {
      DeclareAndCast(StepKinematics_PairRepresentationRelationship, anent, ent);
      RWStepKinematics_RWPairRepresentationRelationship tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 793:
    {
      DeclareAndCast(StepKinematics_RigidLinkRepresentation, anent, ent);
      RWStepKinematics_RWRigidLinkRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 794:
    {
      DeclareAndCast(StepKinematics_KinematicTopologyDirectedStructure, anent, ent);
      RWStepKinematics_RWKinematicTopologyDirectedStructure tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 795:
    {
      DeclareAndCast(StepKinematics_KinematicTopologyNetworkStructure, anent, ent);
      RWStepKinematics_RWKinematicTopologyNetworkStructure tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 796:
    {
      DeclareAndCast(StepKinematics_LinearFlexibleAndPinionPair, anent, ent);
      RWStepKinematics_RWLinearFlexibleAndPinionPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 797:
    {
      DeclareAndCast(StepKinematics_LinearFlexibleAndPlanarCurvePair, anent, ent);
      RWStepKinematics_RWLinearFlexibleAndPlanarCurvePair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 798:
    {
      DeclareAndCast(StepKinematics_LinearFlexibleLinkRepresentation, anent, ent);
      RWStepKinematics_RWLinearFlexibleLinkRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 800:
    {
      DeclareAndCast(StepKinematics_ActuatedKinPairAndOrderKinPair, anent, ent);
      RWStepKinematics_RWActuatedKinPairAndOrderKinPair tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 801:
    {
      DeclareAndCast(StepKinematics_MechanismStateRepresentation, anent, ent);
      RWStepKinematics_RWMechanismStateRepresentation tool;
      tool.WriteStep(SW, anent);
    }
    break;
    case 802:
    {
      DeclareAndCast(StepVisual_RepositionedTessellatedGeometricSet, anEnt, ent);
      RWStepVisual_RWRepositionedTessellatedGeometricSet aTool;
      aTool.WriteStep(SW, anEnt);
      break;
    }
    case 803:
    {
      DeclareAndCast(StepVisual_RepositionedTessellatedItem, anEnt, ent);
      RWStepVisual_RWRepositionedTessellatedItem aTool;
      aTool.WriteStep(SW, anEnt);
      break;
    }

    case 804:
    {
      DeclareAndCast(StepVisual_TessellatedConnectingEdge, anEnt, ent);
      RWStepVisual_RWTessellatedConnectingEdge aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 805:
    {
      DeclareAndCast(StepVisual_TessellatedEdge, anEnt, ent);
      RWStepVisual_RWTessellatedEdge aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 806:
    {
      DeclareAndCast(StepVisual_TessellatedPointSet, anEnt, ent);
      RWStepVisual_RWTessellatedPointSet aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 807:
    {
      DeclareAndCast(StepVisual_TessellatedShapeRepresentation, anEnt, ent);
      RWStepVisual_RWTessellatedShapeRepresentation aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 808:
    {
      DeclareAndCast(StepVisual_TessellatedShapeRepresentationWithAccuracyParameters, anEnt, ent);
      RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 809:
    {
      DeclareAndCast(StepVisual_TessellatedShell, anEnt, ent);
      RWStepVisual_RWTessellatedShell aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 810:
    {
      DeclareAndCast(StepVisual_TessellatedSolid, anEnt, ent);
      RWStepVisual_RWTessellatedSolid aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 811:
    {
      DeclareAndCast(StepVisual_TessellatedStructuredItem, anEnt, ent);
      RWStepVisual_RWTessellatedStructuredItem aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 812:
    {
      DeclareAndCast(StepVisual_TessellatedVertex, anEnt, ent);
      RWStepVisual_RWTessellatedVertex aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 813:
    {
      DeclareAndCast(StepVisual_TessellatedWire, anEnt, ent);
      RWStepVisual_RWTessellatedWire aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 814:
    {
      DeclareAndCast(StepVisual_TriangulatedFace, anEnt, ent);
      RWStepVisual_RWTriangulatedFace aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 815:
    {
      DeclareAndCast(StepVisual_ComplexTriangulatedFace, anEnt, ent);
      RWStepVisual_RWComplexTriangulatedFace aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 816:
    {
      DeclareAndCast(StepVisual_ComplexTriangulatedSurfaceSet, anEnt, ent);
      RWStepVisual_RWComplexTriangulatedSurfaceSet aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 817:
    {
      DeclareAndCast(StepVisual_CubicBezierTessellatedEdge, anEnt, ent);
      RWStepVisual_RWCubicBezierTessellatedEdge aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 818:
    {
      DeclareAndCast(StepVisual_CubicBezierTriangulatedFace, anEnt, ent);
      RWStepVisual_RWCubicBezierTriangulatedFace aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 819:
    {
      DeclareAndCast(StepVisual_TriangulatedSurfaceSet, anEnt, ent);
      RWStepVisual_RWTriangulatedSurfaceSet aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 820:
    {
      DeclareAndCast(StepBasic_GeneralPropertyAssociation, anEnt, ent);
      RWStepBasic_RWGeneralPropertyAssociation aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 821:
    {
      DeclareAndCast(StepBasic_GeneralPropertyRelationship, anEnt, ent);
      RWStepBasic_RWGeneralPropertyRelationship aTool;
      aTool.WriteStep(SW, anEnt);
    }
    break;
    case 822:
    {
      DeclareAndCast(StepRepr_BooleanRepresentationItem, anent, ent);
      RWStepRepr_RWBooleanRepresentationItem aTool;
      aTool.WriteStep(SW, anent);
    }
    break;
    case 823:
    {
      DeclareAndCast(StepRepr_RealRepresentationItem, anent, ent);
      RWStepRepr_RWRealRepresentationItem aTool;
      aTool.WriteStep(SW, anent);
    }
    break;
    case 824:
    {
      DeclareAndCast(StepRepr_MechanicalDesignAndDraughtingRelationship, anent, ent);
      RWStepRepr_RWMechanicalDesignAndDraughtingRelationship aTool;
      aTool.WriteStep(SW, anent);
    }
    break;
    default:
      return;
  }
}
