#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepVisual_TessellatedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Handle.hpp>

class StepVisual_TessellatedGeometricSet : public StepVisual_TessellatedItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DraughtingCalloutElement select type
  Standard_EXPORT StepVisual_TessellatedGeometricSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>>&
      theItems);

  Standard_EXPORT NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>>
                  Items() const;

private:
  NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>> myItems;

public:
  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedGeometricSet, StepVisual_TessellatedItem)
};
