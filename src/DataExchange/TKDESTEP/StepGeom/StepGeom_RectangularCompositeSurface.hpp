#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_SurfacePatch.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepGeom_SurfacePatch;

class StepGeom_RectangularCompositeSurface : public StepGeom_BoundedSurface
{

public:
  //! Returns a RectangularCompositeSurface
  Standard_EXPORT StepGeom_RectangularCompositeSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                aName,
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>>& aSegments);

  Standard_EXPORT void SetSegments(
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>>& aSegments);

  Standard_EXPORT occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>> Segments()
    const;

  Standard_EXPORT occ::handle<StepGeom_SurfacePatch> SegmentsValue(const int num1,
                                                                   const int num2) const;

  Standard_EXPORT int NbSegmentsI() const;

  Standard_EXPORT int NbSegmentsJ() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_RectangularCompositeSurface, StepGeom_BoundedSurface)

private:
  occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>> segments;
};
