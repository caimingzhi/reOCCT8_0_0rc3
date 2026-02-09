#include <Standard_Type.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepDimTol_DatumReference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepDimTol_DatumReference, Standard_Transient)

StepDimTol_DatumReference::StepDimTol_DatumReference() = default;

void StepDimTol_DatumReference::Init(const int                            thePrecedence,
                                     const occ::handle<StepDimTol_Datum>& theReferencedDatum)
{

  myPrecedence = thePrecedence;

  myReferencedDatum = theReferencedDatum;
}

int StepDimTol_DatumReference::Precedence() const
{
  return myPrecedence;
}

void StepDimTol_DatumReference::SetPrecedence(const int thePrecedence)
{
  myPrecedence = thePrecedence;
}

occ::handle<StepDimTol_Datum> StepDimTol_DatumReference::ReferencedDatum() const
{
  return myReferencedDatum;
}

void StepDimTol_DatumReference::SetReferencedDatum(
  const occ::handle<StepDimTol_Datum>& theReferencedDatum)
{
  myReferencedDatum = theReferencedDatum;
}
