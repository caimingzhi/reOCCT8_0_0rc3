

#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ShapeAspect, Standard_Transient)

StepRepr_ShapeAspect::StepRepr_ShapeAspect() = default;

void StepRepr_ShapeAspect::Init(const occ::handle<TCollection_HAsciiString>&        aName,
                                const occ::handle<TCollection_HAsciiString>&        aDescription,
                                const occ::handle<StepRepr_ProductDefinitionShape>& aOfShape,
                                const StepData_Logical aProductDefinitional)
{

  name                = aName;
  description         = aDescription;
  ofShape             = aOfShape;
  productDefinitional = aProductDefinitional;
}

void StepRepr_ShapeAspect::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_ShapeAspect::Name() const
{
  return name;
}

void StepRepr_ShapeAspect::SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepRepr_ShapeAspect::Description() const
{
  return description;
}

void StepRepr_ShapeAspect::SetOfShape(const occ::handle<StepRepr_ProductDefinitionShape>& aOfShape)
{
  ofShape = aOfShape;
}

occ::handle<StepRepr_ProductDefinitionShape> StepRepr_ShapeAspect::OfShape() const
{
  return ofShape;
}

void StepRepr_ShapeAspect::SetProductDefinitional(const StepData_Logical aProductDefinitional)
{
  productDefinitional = aProductDefinitional;
}

StepData_Logical StepRepr_ShapeAspect::ProductDefinitional() const
{
  return productDefinitional;
}
