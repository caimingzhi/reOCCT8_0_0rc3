#include <IGESGeom_TrimmedSurface.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_TrimmedSurface, IGESData_IGESEntity)

IGESGeom_TrimmedSurface::IGESGeom_TrimmedSurface() = default;

void IGESGeom_TrimmedSurface::Init(
  const occ::handle<IGESData_IGESEntity>&                                       aSurface,
  const int                                                                     aFlag,
  const occ::handle<IGESGeom_CurveOnSurface>&                                   anOuter,
  const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_CurveOnSurface>>>& anInner)
{
  if (!anInner.IsNull())
    if (anInner->Lower() != 1)
      throw Standard_DimensionMismatch("IGESGeom_TrimmedSurface : Init");

  theSurface     = aSurface;
  theFlag        = aFlag;
  theOuterCurve  = anOuter;
  theInnerCurves = anInner;
  InitTypeAndForm(144, 0);
}

occ::handle<IGESData_IGESEntity> IGESGeom_TrimmedSurface::Surface() const
{
  return theSurface;
}

bool IGESGeom_TrimmedSurface::HasOuterContour() const
{
  return (!theOuterCurve.IsNull());
}

occ::handle<IGESGeom_CurveOnSurface> IGESGeom_TrimmedSurface::OuterContour() const
{
  return theOuterCurve;
}

int IGESGeom_TrimmedSurface::NbInnerContours() const
{
  return (theInnerCurves.IsNull() ? 0 : theInnerCurves->Length());
}

int IGESGeom_TrimmedSurface::OuterBoundaryType() const
{
  return theFlag;
}

occ::handle<IGESGeom_CurveOnSurface> IGESGeom_TrimmedSurface::InnerContour(const int anIndex) const
{
  return (theInnerCurves->Value(anIndex));
  // Exception OutOfRange will be raises if anIndex <= 0 or
  //                                        anIndex > NbInnerCounters()
}
