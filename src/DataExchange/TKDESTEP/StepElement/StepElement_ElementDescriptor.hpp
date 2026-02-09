#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepElement_ElementOrder.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepElement_ElementDescriptor : public Standard_Transient
{

public:
  Standard_EXPORT StepElement_ElementDescriptor();

  Standard_EXPORT void Init(const StepElement_ElementOrder               aTopologyOrder,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT StepElement_ElementOrder TopologyOrder() const;

  Standard_EXPORT void SetTopologyOrder(const StepElement_ElementOrder TopologyOrder);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  DEFINE_STANDARD_RTTIEXT(StepElement_ElementDescriptor, Standard_Transient)

private:
  StepElement_ElementOrder              theTopologyOrder;
  occ::handle<TCollection_HAsciiString> theDescription;
};
