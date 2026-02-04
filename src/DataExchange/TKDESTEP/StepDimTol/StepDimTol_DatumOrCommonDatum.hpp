#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectType.hpp>
#include <NCollection_HArray1.hpp>

class Standard_Transient;
class StepDimTol_Datum;
class StepDimTol_DatumReferenceElement;

class StepDimTol_DatumOrCommonDatum : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DatumOrCommonDatum select type
  Standard_EXPORT StepDimTol_DatumOrCommonDatum();

  //! Recognizes a DatumOrCommonDatum Kind Entity that is :
  //! 1 -> Datum
  //! 2 -> CommonDatumList
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Datum (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_Datum> Datum() const;

  //! returns Value as a CommonDatumList (Null if another type)
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceElement>>>
                  CommonDatumList() const;
};
