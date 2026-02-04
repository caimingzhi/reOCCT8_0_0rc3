#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_Logical.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_ProductDefinitionShape;

class StepRepr_ShapeAspect : public Standard_Transient
{

public:
  //! Returns a ShapeAspect
  Standard_EXPORT StepRepr_ShapeAspect();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        aName,
                            const occ::handle<TCollection_HAsciiString>&        aDescription,
                            const occ::handle<StepRepr_ProductDefinitionShape>& aOfShape,
                            const StepData_Logical aProductDefinitional);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetOfShape(const occ::handle<StepRepr_ProductDefinitionShape>& aOfShape);

  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> OfShape() const;

  Standard_EXPORT void SetProductDefinitional(const StepData_Logical aProductDefinitional);

  Standard_EXPORT StepData_Logical ProductDefinitional() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeAspect, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>        name;
  occ::handle<TCollection_HAsciiString>        description;
  occ::handle<StepRepr_ProductDefinitionShape> ofShape;
  StepData_Logical                             productDefinitional;
};

