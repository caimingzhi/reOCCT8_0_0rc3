#pragma once

#include <StepVisual_TessellatedGeometricSet.hpp>

class StepGeom_Axis2Placement3d;

//! Representation of complex STEP entity RepositionedTessellatedGeometricSet
class StepVisual_RepositionedTessellatedGeometricSet : public StepVisual_TessellatedGeometricSet
{
public:
  DEFINE_STANDARD_ALLOC

  DEFINE_STANDARD_RTTIEXT(StepVisual_RepositionedTessellatedGeometricSet,
                          StepVisual_TessellatedGeometricSet)

  //! Default constructor
  StepVisual_RepositionedTessellatedGeometricSet() = default;

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                           theName,
    const NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>>& theItems,
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
