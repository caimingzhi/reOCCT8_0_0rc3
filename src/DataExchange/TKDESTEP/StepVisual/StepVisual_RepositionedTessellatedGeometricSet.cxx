

#include <StepVisual_RepositionedTessellatedGeometricSet.hpp>

#include <StepGeom_Axis2Placement3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_RepositionedTessellatedGeometricSet,
                           StepVisual_TessellatedGeometricSet)

void StepVisual_RepositionedTessellatedGeometricSet::Init(
  const occ::handle<TCollection_HAsciiString>&                                           theName,
  const NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>>& theItems,
  const occ::handle<StepGeom_Axis2Placement3d>& theLocation)
{
  StepVisual_TessellatedGeometricSet::Init(theName, theItems);
  myLocation = theLocation;
}
