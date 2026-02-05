#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepDimTol_DatumReferenceCompartment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity DatumSystem
class StepDimTol_DatumSystem : public StepRepr_ShapeAspect
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumSystem();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&        theName,
    const occ::handle<TCollection_HAsciiString>&        theDescription,
    const occ::handle<StepRepr_ProductDefinitionShape>& theOfShape,
    const StepData_Logical                              theProductDefinitional,
    const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>&
      theConstituents);

  //! Returns field Constituents
  inline occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>
    Constituents()
  {
    return myConstituents;
  }

  //! Set field Constituents
  inline void SetConstituents(
    const occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>>&
      theConstituents)
  {
    myConstituents = theConstituents;
  }

  //! Returns number of Constituents
  inline int NbConstituents() const
  {
    return (myConstituents.IsNull() ? 0 : myConstituents->Length());
  }

  //! Returns Constituents with the given number
  inline occ::handle<StepDimTol_DatumReferenceCompartment> ConstituentsValue(const int num) const
  {
    return myConstituents->Value(num);
  }

  //! Sets Constituents with given number
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
