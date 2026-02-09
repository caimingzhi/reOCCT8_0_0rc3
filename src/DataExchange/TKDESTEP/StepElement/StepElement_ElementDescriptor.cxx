#include <StepElement_ElementDescriptor.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_ElementDescriptor, Standard_Transient)

StepElement_ElementDescriptor::StepElement_ElementDescriptor() = default;

void StepElement_ElementDescriptor::Init(const StepElement_ElementOrder aTopologyOrder,
                                         const occ::handle<TCollection_HAsciiString>& aDescription)
{

  theTopologyOrder = aTopologyOrder;

  theDescription = aDescription;
}

StepElement_ElementOrder StepElement_ElementDescriptor::TopologyOrder() const
{
  return theTopologyOrder;
}

void StepElement_ElementDescriptor::SetTopologyOrder(const StepElement_ElementOrder aTopologyOrder)
{
  theTopologyOrder = aTopologyOrder;
}

occ::handle<TCollection_HAsciiString> StepElement_ElementDescriptor::Description() const
{
  return theDescription;
}

void StepElement_ElementDescriptor::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}
