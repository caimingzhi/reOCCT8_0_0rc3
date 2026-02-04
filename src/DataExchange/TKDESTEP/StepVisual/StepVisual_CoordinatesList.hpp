#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_TessellatedItem.hpp>

class StepVisual_CoordinatesList : public StepVisual_TessellatedItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a coordinate list
  Standard_EXPORT StepVisual_CoordinatesList();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    theName,
                            const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints);

  Standard_EXPORT occ::handle<NCollection_HArray1<gp_XYZ>> Points() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CoordinatesList, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> myPoints;
};
