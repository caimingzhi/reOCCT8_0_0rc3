#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class StepDimTol_Datum;

//! Representation of STEP entity DatumReference
class StepDimTol_DatumReference : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumReference();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const int                            thePrecedence,
                            const occ::handle<StepDimTol_Datum>& theReferencedDatum);

  //! Returns field Precedence
  Standard_EXPORT int Precedence() const;

  //! Set field Precedence
  Standard_EXPORT void SetPrecedence(const int thePrecedence);

  //! Returns field ReferencedDatum
  Standard_EXPORT occ::handle<StepDimTol_Datum> ReferencedDatum() const;

  //! Set field ReferencedDatum
  Standard_EXPORT void SetReferencedDatum(const occ::handle<StepDimTol_Datum>& theReferencedDatum);

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumReference, Standard_Transient)

private:
  int                           myPrecedence;
  occ::handle<StepDimTol_Datum> myReferencedDatum;
};

