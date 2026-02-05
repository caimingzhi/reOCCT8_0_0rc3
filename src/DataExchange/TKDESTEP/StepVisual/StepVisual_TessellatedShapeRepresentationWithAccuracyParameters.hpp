#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_TessellatedShapeRepresentation.hpp>

//! Representation of STEP entity TessellatedShapeRepresentationWithAccuracyParameters
class StepVisual_TessellatedShapeRepresentationWithAccuracyParameters
    : public StepVisual_TessellatedShapeRepresentation
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedShapeRepresentationWithAccuracyParameters();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                       theRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>& theRepresentation_ContextOfItems,
    const occ::handle<NCollection_HArray1<double>>&    theTessellationAccuracyParameters);

  //! Returns field TessellationAccuracyParameters
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> TessellationAccuracyParameters() const;

  //! Sets field TessellationAccuracyParameters
  Standard_EXPORT void SetTessellationAccuracyParameters(
    const occ::handle<NCollection_HArray1<double>>& theTessellationAccuracyParameters);

  //! Returns number of TessellationAccuracyParameters
  Standard_EXPORT int NbTessellationAccuracyParameters() const;

  //! Returns value of TessellationAccuracyParameters by its num
  Standard_EXPORT const double& TessellationAccuracyParametersValue(const int theNum) const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedShapeRepresentationWithAccuracyParameters,
                          StepVisual_TessellatedShapeRepresentation)

private:
  occ::handle<NCollection_HArray1<double>> myTessellationAccuracyParameters;
};
