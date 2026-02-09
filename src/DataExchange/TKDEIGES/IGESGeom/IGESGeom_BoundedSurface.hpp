#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESGeom_Boundary.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESGeom_Boundary;

class IGESGeom_BoundedSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_BoundedSurface();

  Standard_EXPORT void Init(
    const int                                                               aType,
    const occ::handle<IGESData_IGESEntity>&                                 aSurface,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_Boundary>>>& allBounds);

  Standard_EXPORT int RepresentationType() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  Standard_EXPORT int NbBoundaries() const;

  Standard_EXPORT occ::handle<IGESGeom_Boundary> Boundary(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_BoundedSurface, IGESData_IGESEntity)

private:
  int                                                              theType;
  occ::handle<IGESData_IGESEntity>                                 theSurface;
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_Boundary>>> theBoundaries;
};
