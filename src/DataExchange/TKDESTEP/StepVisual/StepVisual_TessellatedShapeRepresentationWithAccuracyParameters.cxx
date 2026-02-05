// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedShapeRepresentationWithAccuracyParameters.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedShapeRepresentationWithAccuracyParameters,
                           StepVisual_TessellatedShapeRepresentation)

//=================================================================================================

StepVisual_TessellatedShapeRepresentationWithAccuracyParameters::
  StepVisual_TessellatedShapeRepresentationWithAccuracyParameters() = default;

//=================================================================================================

void StepVisual_TessellatedShapeRepresentationWithAccuracyParameters::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     theRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& theRepresentation_ContextOfItems,
  const occ::handle<NCollection_HArray1<double>>&    theTessellationAccuracyParameters)
{
  StepVisual_TessellatedShapeRepresentation::Init(theRepresentation_Name,
                                                  theRepresentation_Items,
                                                  theRepresentation_ContextOfItems);

  myTessellationAccuracyParameters = theTessellationAccuracyParameters;
}

//=================================================================================================

occ::handle<NCollection_HArray1<double>>
  StepVisual_TessellatedShapeRepresentationWithAccuracyParameters::TessellationAccuracyParameters()
    const
{
  return myTessellationAccuracyParameters;
}

//=================================================================================================

void StepVisual_TessellatedShapeRepresentationWithAccuracyParameters::
  SetTessellationAccuracyParameters(
    const occ::handle<NCollection_HArray1<double>>& theTessellationAccuracyParameters)
{
  myTessellationAccuracyParameters = theTessellationAccuracyParameters;
}

//=================================================================================================

int StepVisual_TessellatedShapeRepresentationWithAccuracyParameters::
  NbTessellationAccuracyParameters() const
{
  if (myTessellationAccuracyParameters.IsNull())
  {
    return 0;
  }
  return myTessellationAccuracyParameters->Length();
}

//=================================================================================================

const double& StepVisual_TessellatedShapeRepresentationWithAccuracyParameters::
  TessellationAccuracyParametersValue(const int theNum) const
{
  return myTessellationAccuracyParameters->Value(theNum);
}
