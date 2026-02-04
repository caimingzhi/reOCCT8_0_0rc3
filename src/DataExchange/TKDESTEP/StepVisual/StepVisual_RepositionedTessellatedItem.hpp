#pragma once


#include <StepVisual_TessellatedItem.hpp>

class StepGeom_Axis2Placement3d;

//! Representation of STEP entity RepositionedTessellatedItem
class StepVisual_RepositionedTessellatedItem : public StepVisual_TessellatedItem
{
public:
  DEFINE_STANDARD_RTTIEXT(StepVisual_RepositionedTessellatedItem, StepVisual_TessellatedItem)

  DEFINE_STANDARD_ALLOC

  //! Default constructor
  StepVisual_RepositionedTessellatedItem() = default;

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  theName,
                            const occ::handle<StepGeom_Axis2Placement3d>& theLocation);

  //! Returns location
  occ::handle<StepGeom_Axis2Placement3d> Location() const { return myLocation; }

  //! Sets location
  void SetLocation(const occ::handle<StepGeom_Axis2Placement3d>& theLocation)
  {
    myLocation = theLocation;
  }

private:
  occ::handle<StepGeom_Axis2Placement3d> myLocation;
};
