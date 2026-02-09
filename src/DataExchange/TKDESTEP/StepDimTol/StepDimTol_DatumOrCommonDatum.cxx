#include <StepDimTol_DatumOrCommonDatum.hpp>

#include <MoniTool_Macros.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepDimTol_DatumReferenceElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

StepDimTol_DatumOrCommonDatum::StepDimTol_DatumOrCommonDatum() = default;

int StepDimTol_DatumOrCommonDatum::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_Datum)))
    return 1;
  if (ent->IsKind(
        STANDARD_TYPE(NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceElement>>)))
    return 2;
  return 0;
}

occ::handle<StepDimTol_Datum> StepDimTol_DatumOrCommonDatum::Datum() const
{
  return GetCasted(StepDimTol_Datum, Value());
}

occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceElement>>>
  StepDimTol_DatumOrCommonDatum::CommonDatumList() const
{
  return GetCasted(NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceElement>>, Value());
}
