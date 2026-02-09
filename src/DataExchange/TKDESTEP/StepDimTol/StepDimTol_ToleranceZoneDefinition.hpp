#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepDimTol_ToleranceZone.hpp>

class StepDimTol_ToleranceZoneDefinition : public Standard_Transient
{

public:
  Standard_EXPORT StepDimTol_ToleranceZoneDefinition();

  Standard_EXPORT void Init(
    const occ::handle<StepDimTol_ToleranceZone>&                               theZone,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries);

  inline occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>> Boundaries() const
  {
    return myBoundaries;
  }

  inline void SetBoundaries(
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>>& theBoundaries)
  {
    myBoundaries = theBoundaries;
  }

  inline int NbBoundaries() const { return (myBoundaries.IsNull() ? 0 : myBoundaries->Length()); }

  inline occ::handle<StepRepr_ShapeAspect> BoundariesValue(const int theNum) const
  {
    return myBoundaries->Value(theNum);
  }

  inline void SetBoundariesValue(const int theNum, const occ::handle<StepRepr_ShapeAspect>& theItem)
  {
    myBoundaries->SetValue(theNum, theItem);
  }

  inline occ::handle<StepDimTol_ToleranceZone> Zone() { return myZone; }

  inline void SetZone(const occ::handle<StepDimTol_ToleranceZone>& theZone) { myZone = theZone; }

  DEFINE_STANDARD_RTTIEXT(StepDimTol_ToleranceZoneDefinition, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>> myBoundaries;
  occ::handle<StepDimTol_ToleranceZone>                               myZone;
};
