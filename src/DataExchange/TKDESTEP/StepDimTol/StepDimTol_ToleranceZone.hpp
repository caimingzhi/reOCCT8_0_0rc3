#pragma once

#include <Standard.hpp>

#include <StepRepr_ShapeAspect.hpp>
#include <Standard_Integer.hpp>
#include <StepDimTol_ToleranceZoneTarget.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepDimTol_ToleranceZoneForm.hpp>

class TCollection_HAsciiString;

#ifdef SetForm
  #undef SetForm
#endif

class StepDimTol_ToleranceZone : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepDimTol_ToleranceZone();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                            theName,
    const occ::handle<TCollection_HAsciiString>&                            theDescription,
    const occ::handle<StepRepr_ProductDefinitionShape>&                     theOfShape,
    const StepData_Logical                                                  theProductDefinitional,
    const occ::handle<NCollection_HArray1<StepDimTol_ToleranceZoneTarget>>& theDefiningTolerance,
    const occ::handle<StepDimTol_ToleranceZoneForm>&                        theForm);

  inline occ::handle<NCollection_HArray1<StepDimTol_ToleranceZoneTarget>> DefiningTolerance() const
  {
    return myDefiningTolerance;
  }

  inline void SetDefiningTolerance(
    const occ::handle<NCollection_HArray1<StepDimTol_ToleranceZoneTarget>>& theDefiningTolerance)
  {
    myDefiningTolerance = theDefiningTolerance;
  }

  inline int NbDefiningTolerances() const
  {
    return (myDefiningTolerance.IsNull() ? 0 : myDefiningTolerance->Length());
  }

  inline StepDimTol_ToleranceZoneTarget DefiningToleranceValue(const int theNum) const
  {
    return myDefiningTolerance->Value(theNum);
  }

  inline void SetDefiningToleranceValue(const int                             theNum,
                                        const StepDimTol_ToleranceZoneTarget& theItem)
  {
    myDefiningTolerance->SetValue(theNum, theItem);
  }

  inline occ::handle<StepDimTol_ToleranceZoneForm> Form() { return myForm; }

  inline void SetForm(const occ::handle<StepDimTol_ToleranceZoneForm>& theForm)
  {
    myForm = theForm;
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ToleranceZone, StepRepr_ShapeAspect)

private:
  occ::handle<NCollection_HArray1<StepDimTol_ToleranceZoneTarget>> myDefiningTolerance;
  occ::handle<StepDimTol_ToleranceZoneForm>                        myForm;
};
