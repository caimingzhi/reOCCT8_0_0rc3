#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
class StepShape_Loop;
class TCollection_HAsciiString;

class StepShape_FaceBound : public StepShape_TopologicalRepresentationItem
{

public:
  //! Returns a FaceBound
  Standard_EXPORT StepShape_FaceBound();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Loop>&           aBound,
                            const bool                                   aOrientation);

  Standard_EXPORT void SetBound(const occ::handle<StepShape_Loop>& aBound);

  Standard_EXPORT occ::handle<StepShape_Loop> Bound() const;

  Standard_EXPORT void SetOrientation(const bool aOrientation);

  Standard_EXPORT bool Orientation() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_FaceBound, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<StepShape_Loop> bound;
  bool                        orientation;
};

