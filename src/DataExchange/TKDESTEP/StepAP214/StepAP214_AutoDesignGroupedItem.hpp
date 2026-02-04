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

  //! Returns a AutoDesignGroupedItem SelectType
  Standard_EXPORT StepAP214_AutoDesignGroupedItem();

  //! Recognizes a AutoDesignGroupedItem Kind Entity that is :
  //! 1 -> AdvancedBrepShapeRepresentation
  //! 2 -> CsgShapeRepresentation
  //! 3 -> FacetedBrepShapeRepresentation
  //! 4 -> GeometricallyBoundedSurfaceShapeRepresentation
  //! 5 -> GeometricallyBoundedWireframeShapeRepresentation
  //! 6 -> ManifoldSurfaceShapeRepresentation
  //! 7 -> Representation
  //! 8 -> RepresentationItem
  //! 9 -> ShapeAspect
  //! 10 -> ShapeRepresentation
  //! 11 -> TemplateInstance
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a AdvancedBrepShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_AdvancedBrepShapeRepresentation>
                  AdvancedBrepShapeRepresentation() const;

  //! returns Value as a CsgShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_CsgShapeRepresentation> CsgShapeRepresentation() const;

  //! returns Value as a FacetedBrepShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_FacetedBrepShapeRepresentation>
                  FacetedBrepShapeRepresentation() const;

  //! returns Value as a GeometricallyBoundedSurfaceShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_GeometricallyBoundedSurfaceShapeRepresentation>
                  GeometricallyBoundedSurfaceShapeRepresentation() const;

  //! returns Value as a GeometricallyBoundedWireframeShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_GeometricallyBoundedWireframeShapeRepresentation>
                  GeometricallyBoundedWireframeShapeRepresentation() const;

  //! returns Value as a ManifoldSurfaceShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_ManifoldSurfaceShapeRepresentation>
                  ManifoldSurfaceShapeRepresentation() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a RepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;

  //! returns Value as a ShapeAspect (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! returns Value as a ShapeRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> ShapeRepresentation() const;

  //! returns Value as a TemplateInstance (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_TemplateInstance> TemplateInstance() const;
};

