#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class IGESDimen_DimensionedGeometry : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DimensionedGeometry();

  Standard_EXPORT void Init(
    const int                                                                 nbDims,
    const occ::handle<IGESData_IGESEntity>&                                   aDimension,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& entities);

  Standard_EXPORT int NbDimensions() const;

  Standard_EXPORT int NbGeometryEntities() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DimensionEntity() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> GeometryEntity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_DimensionedGeometry, IGESData_IGESEntity)

private:
  int                                                                theNbDimensions;
  occ::handle<IGESData_IGESEntity>                                   theDimension;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theGeometryEntities;
};
