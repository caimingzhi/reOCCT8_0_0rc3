#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepElement_ElementOrder.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity ElementDescriptor
class StepElement_ElementDescriptor : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_ElementDescriptor();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepElement_ElementOrder               aTopologyOrder,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  //! Returns field TopologyOrder
  Standard_EXPORT StepElement_ElementOrder TopologyOrder() const;

  //! Set field TopologyOrder
  Standard_EXPORT void SetTopologyOrder(const StepElement_ElementOrder TopologyOrder);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  DEFINE_STANDARD_RTTIEXT(StepElement_ElementDescriptor, Standard_Transient)

private:
  StepElement_ElementOrder              theTopologyOrder;
  occ::handle<TCollection_HAsciiString> theDescription;
};

