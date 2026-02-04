#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductDefinition.hpp>

class StepBasic_ExternalSource;

class StepBasic_ProductDefinitionReferenceWithLocalRepresentation
    : public StepBasic_ProductDefinition
{

public:
  //! Returns a ProductDefinitionReferenceWithLocalRepresentation
  Standard_EXPORT StepBasic_ProductDefinitionReferenceWithLocalRepresentation();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_ExternalSource>&             theSource,
    const occ::handle<TCollection_HAsciiString>&             theId,
    const occ::handle<TCollection_HAsciiString>&             theDescription,
    const occ::handle<StepBasic_ProductDefinitionFormation>& theFormation,
    const occ::handle<StepBasic_ProductDefinitionContext>&   theFrameOfReference);

  //! Returns field Source
  inline occ::handle<StepBasic_ExternalSource> Source() const { return mySource; }

  //! Set field Source
  inline void SetSource(const occ::handle<StepBasic_ExternalSource>& theSource)
  {
    mySource = theSource;
  }

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionReferenceWithLocalRepresentation,
                          StepBasic_ProductDefinition)

private:
  occ::handle<StepBasic_ExternalSource> mySource;
};
