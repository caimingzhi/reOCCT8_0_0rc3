#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepSelect_StepType.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

class STEPSelections_SelectDerived : public StepSelect_StepType
{

public:
  Standard_EXPORT STEPSelections_SelectDerived();

  Standard_EXPORT bool Matches(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model,
                               const TCollection_AsciiString&               text,
                               const bool                                   exact) const override;

  DEFINE_STANDARD_RTTIEXT(STEPSelections_SelectDerived, StepSelect_StepType)
};
