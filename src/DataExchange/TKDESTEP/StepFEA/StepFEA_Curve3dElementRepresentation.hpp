#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_ElementRepresentation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_NodeRepresentation.hpp>
class StepFEA_FeaModel3d;
class StepElement_Curve3dElementDescriptor;
class StepFEA_Curve3dElementProperty;
class StepElement_ElementMaterial;
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

class StepFEA_Curve3dElementRepresentation : public StepFEA_ElementRepresentation
{

public:
  Standard_EXPORT StepFEA_Curve3dElementRepresentation();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                       aRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>&
                                                             aElementRepresentation_NodeList,
    const occ::handle<StepFEA_FeaModel3d>&                   aModelRef,
    const occ::handle<StepElement_Curve3dElementDescriptor>& aElementDescriptor,
    const occ::handle<StepFEA_Curve3dElementProperty>&       aProperty,
    const occ::handle<StepElement_ElementMaterial>&          aMaterial);

  Standard_EXPORT occ::handle<StepFEA_FeaModel3d> ModelRef() const;

  Standard_EXPORT void SetModelRef(const occ::handle<StepFEA_FeaModel3d>& ModelRef);

  Standard_EXPORT occ::handle<StepElement_Curve3dElementDescriptor> ElementDescriptor() const;

  Standard_EXPORT void SetElementDescriptor(
    const occ::handle<StepElement_Curve3dElementDescriptor>& ElementDescriptor);

  Standard_EXPORT occ::handle<StepFEA_Curve3dElementProperty> Property() const;

  Standard_EXPORT void SetProperty(const occ::handle<StepFEA_Curve3dElementProperty>& Property);

  Standard_EXPORT occ::handle<StepElement_ElementMaterial> Material() const;

  Standard_EXPORT void SetMaterial(const occ::handle<StepElement_ElementMaterial>& Material);

  DEFINE_STANDARD_RTTIEXT(StepFEA_Curve3dElementRepresentation, StepFEA_ElementRepresentation)

private:
  occ::handle<StepFEA_FeaModel3d>                   theModelRef;
  occ::handle<StepElement_Curve3dElementDescriptor> theElementDescriptor;
  occ::handle<StepFEA_Curve3dElementProperty>       theProperty;
  occ::handle<StepElement_ElementMaterial>          theMaterial;
};
