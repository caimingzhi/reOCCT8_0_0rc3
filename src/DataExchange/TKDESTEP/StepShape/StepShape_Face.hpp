#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_FaceBound;

class StepShape_Face : public StepShape_TopologicalRepresentationItem
{

public:
  //! Returns a Face
  Standard_EXPORT StepShape_Face();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                              aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds);

  Standard_EXPORT virtual void SetBounds(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds);

  Standard_EXPORT virtual occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>
    Bounds() const;

  Standard_EXPORT virtual occ::handle<StepShape_FaceBound> BoundsValue(const int num) const;

  Standard_EXPORT virtual int NbBounds() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_Face, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> bounds;
};
