#pragma once


#include <Standard.hpp>

#include <StepGeom_TrimmingSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Boolean.hpp>
#include <StepGeom_TrimmingPreference.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <Standard_Integer.hpp>
class StepGeom_Curve;
class TCollection_HAsciiString;
class StepGeom_TrimmingSelect;

class StepGeom_TrimmedCurve : public StepGeom_BoundedCurve
{

public:
  //! Returns a TrimmedCurve
  Standard_EXPORT StepGeom_TrimmedCurve();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Curve>&           aBasisCurve,
                            const occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>>& aTrim1,
                            const occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>>& aTrim2,
                            const bool                        aSenseAgreement,
                            const StepGeom_TrimmingPreference aMasterRepresentation);

  Standard_EXPORT void SetBasisCurve(const occ::handle<StepGeom_Curve>& aBasisCurve);

  Standard_EXPORT occ::handle<StepGeom_Curve> BasisCurve() const;

  Standard_EXPORT void SetTrim1(
    const occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>>& aTrim1);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>> Trim1() const;

  Standard_EXPORT StepGeom_TrimmingSelect Trim1Value(const int num) const;

  Standard_EXPORT int NbTrim1() const;

  Standard_EXPORT void SetTrim2(
    const occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>>& aTrim2);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>> Trim2() const;

  Standard_EXPORT StepGeom_TrimmingSelect Trim2Value(const int num) const;

  Standard_EXPORT int NbTrim2() const;

  Standard_EXPORT void SetSenseAgreement(const bool aSenseAgreement);

  Standard_EXPORT bool SenseAgreement() const;

  Standard_EXPORT void SetMasterRepresentation(
    const StepGeom_TrimmingPreference aMasterRepresentation);

  Standard_EXPORT StepGeom_TrimmingPreference MasterRepresentation() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_TrimmedCurve, StepGeom_BoundedCurve)

private:
  occ::handle<StepGeom_Curve>                               basisCurve;
  occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>> trim1;
  occ::handle<NCollection_HArray1<StepGeom_TrimmingSelect>> trim2;
  bool                                                      senseAgreement;
  StepGeom_TrimmingPreference                               masterRepresentation;
};

