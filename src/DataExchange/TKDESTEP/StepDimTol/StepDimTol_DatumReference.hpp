#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class StepDimTol_Datum;

class StepDimTol_DatumReference : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_DatumReference();

  Standard_EXPORT void Init(const int                            thePrecedence,
                            const occ::handle<StepDimTol_Datum>& theReferencedDatum);

  Standard_EXPORT int Precedence() const;

  Standard_EXPORT void SetPrecedence(const int thePrecedence);

  Standard_EXPORT occ::handle<StepDimTol_Datum> ReferencedDatum() const;

  Standard_EXPORT void SetReferencedDatum(const occ::handle<StepDimTol_Datum>& theReferencedDatum);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumReference, Standard_Transient)

private:
  int                           myPrecedence;
  occ::handle<StepDimTol_Datum> myReferencedDatum;
};
