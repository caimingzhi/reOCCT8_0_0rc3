#pragma once

#include <Standard.hpp>

#include <StepShape_Shell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_Shell;

class StepShape_ShellBasedSurfaceModel : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepShape_ShellBasedSurfaceModel();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&             aName,
                            const occ::handle<NCollection_HArray1<StepShape_Shell>>& aSbsmBoundary);

  Standard_EXPORT void SetSbsmBoundary(
    const occ::handle<NCollection_HArray1<StepShape_Shell>>& aSbsmBoundary);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepShape_Shell>> SbsmBoundary() const;

  Standard_EXPORT StepShape_Shell SbsmBoundaryValue(const int num) const;

  Standard_EXPORT int NbSbsmBoundary() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_ShellBasedSurfaceModel, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<StepShape_Shell>> sbsmBoundary;
};
