#pragma once

#include <StepVisual_TessellatedItem.hpp>

class StepGeom_Axis2Placement3d;

class StepVisual_RepositionedTessellatedItem : public StepVisual_TessellatedItem
{
public:
  DEFINE_STANDARD_RTTIEXT(StepVisual_RepositionedTessellatedItem, StepVisual_TessellatedItem)

  DEFINE_STANDARD_ALLOC

  StepVisual_RepositionedTessellatedItem() = default;

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  theName,
                            const occ::handle<StepGeom_Axis2Placement3d>& theLocation);

  occ::handle<StepGeom_Axis2Placement3d> Location() const { return myLocation; }

  void SetLocation(const occ::handle<StepGeom_Axis2Placement3d>& theLocation)
  {
    myLocation = theLocation;
  }

private:
  occ::handle<StepGeom_Axis2Placement3d> myLocation;
};
