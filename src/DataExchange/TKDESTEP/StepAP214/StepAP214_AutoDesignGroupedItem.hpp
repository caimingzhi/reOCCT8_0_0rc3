#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_AdvancedBrepShapeRepresentation;
class StepShape_CsgShapeRepresentation;
class StepShape_FacetedBrepShapeRepresentation;
class StepShape_GeometricallyBoundedSurfaceShapeRepresentation;
class StepShape_GeometricallyBoundedWireframeShapeRepresentation;
class StepShape_ManifoldSurfaceShapeRepresentation;
class StepRepr_Representation;
class StepRepr_RepresentationItem;
class StepRepr_ShapeAspect;
class StepShape_ShapeRepresentation;
class StepVisual_TemplateInstance;

class StepAP214_AutoDesignGroupedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_AutoDesignGroupedItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_AdvancedBrepShapeRepresentation>
                  AdvancedBrepShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepShape_CsgShapeRepresentation> CsgShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepShape_FacetedBrepShapeRepresentation>
                  FacetedBrepShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepShape_GeometricallyBoundedSurfaceShapeRepresentation>
                  GeometricallyBoundedSurfaceShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepShape_GeometricallyBoundedWireframeShapeRepresentation>
                  GeometricallyBoundedWireframeShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepShape_ManifoldSurfaceShapeRepresentation>
                  ManifoldSurfaceShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> ShapeRepresentation() const;

  Standard_EXPORT occ::handle<StepVisual_TemplateInstance> TemplateInstance() const;
};
