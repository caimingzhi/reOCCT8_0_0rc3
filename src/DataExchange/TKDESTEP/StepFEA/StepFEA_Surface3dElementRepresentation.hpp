#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_ElementRepresentation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_NodeRepresentation.hpp>
class StepFEA_FeaModel3d;
class StepElement_Surface3dElementDescriptor;
class StepElement_SurfaceElementProperty;
class StepElement_ElementMaterial;
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

//! Representation of STEP entity Surface3dElementRepresentation
class StepFEA_Surface3dElementRepresentation : public StepFEA_ElementRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_Surface3dElementRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                       aRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>&
                                                               aElementRepresentation_NodeList,
    const occ::handle<StepFEA_FeaModel3d>&                     aModelRef,
    const occ::handle<StepElement_Surface3dElementDescriptor>& aElementDescriptor,
    const occ::handle<StepElement_SurfaceElementProperty>&     aProperty,
    const occ::handle<StepElement_ElementMaterial>&            aMaterial);

  //! Returns field ModelRef
  Standard_EXPORT occ::handle<StepFEA_FeaModel3d> ModelRef() const;

  //! Set field ModelRef
  Standard_EXPORT void SetModelRef(const occ::handle<StepFEA_FeaModel3d>& ModelRef);

  //! Returns field ElementDescriptor
  Standard_EXPORT occ::handle<StepElement_Surface3dElementDescriptor> ElementDescriptor() const;

  //! Set field ElementDescriptor
  Standard_EXPORT void SetElementDescriptor(
    const occ::handle<StepElement_Surface3dElementDescriptor>& ElementDescriptor);

  //! Returns field Property
  Standard_EXPORT occ::handle<StepElement_SurfaceElementProperty> Property() const;

  //! Set field Property
  Standard_EXPORT void SetProperty(const occ::handle<StepElement_SurfaceElementProperty>& Property);

  //! Returns field Material
  Standard_EXPORT occ::handle<StepElement_ElementMaterial> Material() const;

  //! Set field Material
  Standard_EXPORT void SetMaterial(const occ::handle<StepElement_ElementMaterial>& Material);

  DEFINE_STANDARD_RTTIEXT(StepFEA_Surface3dElementRepresentation, StepFEA_ElementRepresentation)

private:
  occ::handle<StepFEA_FeaModel3d>                     theModelRef;
  occ::handle<StepElement_Surface3dElementDescriptor> theElementDescriptor;
  occ::handle<StepElement_SurfaceElementProperty>     theProperty;
  occ::handle<StepElement_ElementMaterial>            theMaterial;
};
