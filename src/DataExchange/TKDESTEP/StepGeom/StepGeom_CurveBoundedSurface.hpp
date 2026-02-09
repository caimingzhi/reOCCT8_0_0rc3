#pragma once

#include <Standard.hpp>

#include <StepGeom_SurfaceBoundary.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Boolean.hpp>
#include <StepGeom_BoundedSurface.hpp>
class StepGeom_Surface;
class TCollection_HAsciiString;

class StepGeom_CurveBoundedSurface : public StepGeom_BoundedSurface
{

public:
  Standard_EXPORT StepGeom_CurveBoundedSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                      aRepresentationItem_Name,
    const occ::handle<StepGeom_Surface>&                              aBasisSurface,
    const occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>>& aBoundaries,
    const bool                                                        aImplicitOuter);

  Standard_EXPORT occ::handle<StepGeom_Surface> BasisSurface() const;

  Standard_EXPORT void SetBasisSurface(const occ::handle<StepGeom_Surface>& BasisSurface);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>> Boundaries() const;

  Standard_EXPORT void SetBoundaries(
    const occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>>& Boundaries);

  Standard_EXPORT bool ImplicitOuter() const;

  Standard_EXPORT void SetImplicitOuter(const bool ImplicitOuter);

  DEFINE_STANDARD_RTTIEXT(StepGeom_CurveBoundedSurface, StepGeom_BoundedSurface)

private:
  occ::handle<StepGeom_Surface>                              theBasisSurface;
  occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>> theBoundaries;
  bool                                                       theImplicitOuter;
};
