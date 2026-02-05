#include <IGESGeom_BoundedSurface.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_BoundedSurface, IGESData_IGESEntity)

IGESGeom_BoundedSurface::IGESGeom_BoundedSurface() = default;

void IGESGeom_BoundedSurface::Init(
  const int                                                               aType,
  const occ::handle<IGESData_IGESEntity>&                                 aSurface,
  const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_Boundary>>>& aBoundary)
{
  if (aBoundary->Lower() != 1)
    throw Standard_DimensionMismatch("IGESGeom_BoundedSurface : Init");
  theType       = aType;
  theSurface    = aSurface;
  theBoundaries = aBoundary;
  InitTypeAndForm(143, 0);
}

int IGESGeom_BoundedSurface::RepresentationType() const
{
  return theType;
}

occ::handle<IGESData_IGESEntity> IGESGeom_BoundedSurface::Surface() const
{
  return theSurface;
}

int IGESGeom_BoundedSurface::NbBoundaries() const
{

  return (theBoundaries.IsNull() ? 0 : theBoundaries->Length());
}

occ::handle<IGESGeom_Boundary> IGESGeom_BoundedSurface::Boundary(const int Index) const
{
  return theBoundaries->Value(Index);
}
