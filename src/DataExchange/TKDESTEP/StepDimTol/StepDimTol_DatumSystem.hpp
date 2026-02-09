#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepDimTol_DatumReferenceCompartment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepDimTol_DatumSystem : public StepRepr_ShapeAspect
{

public:
  Standard_EXPORT StepDimTol_DatumSystem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theName,
    const occ::handle<TCollection_HAsciiString>&        theDescription,
    const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
    const StepData_Logical                              theProductDefinitional,
    const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>&
      theConstituents);

  inline occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>
    Constituents()
  {
    return myConstituents;
  }

  inline void SetConstituents(
    const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>&
      theConstituents)
  {
    myConstituents = theConstituents;
  }

  inline int NbConstituents() const
  {
    return (myConstituents.IsNull() ? 0 : myConstituents->Length());
  }

  inline occ::handle<StepDimTol_DatumReferenceCompartment> ConstituentsValue(const int num) const
  {
    return myConstituents->Value(num);
  }

  inline void ConstituentsValue(const int                                                num,
                                const occ::handle<StepDimTol_DatumReferenceCompartment>& theItem)
  {
    myConstituents->SetValue(num, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumSystem, StepRepr_ShapeAspect)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>
    myConstituents;
};
