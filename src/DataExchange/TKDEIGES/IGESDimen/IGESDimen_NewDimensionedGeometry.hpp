#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
class gp_Pnt;

class IGESDimen_NewDimensionedGeometry : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_NewDimensionedGeometry();

  Standard_EXPORT void Init(
    const int                                                                 nbDimens,
    const occ::handle<IGESData_IGESEntity>&                                   aDimen,
    const int                                                                 anOrientation,
    const double                                                              anAngle,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities,
    const occ::handle<NCollection_HArray1<int>>&                              allLocations,
    const occ::handle<NCollection_HArray1<gp_XYZ>>&                           allPoints);

  Standard_EXPORT int NbDimensions() const;

  Standard_EXPORT int NbGeometries() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DimensionEntity() const;

  Standard_EXPORT int DimensionOrientationFlag() const;

  Standard_EXPORT double AngleValue() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> GeometryEntity(const int Index) const;

  Standard_EXPORT int DimensionLocationFlag(const int Index) const;

  Standard_EXPORT gp_Pnt Point(const int Index) const;

  Standard_EXPORT gp_Pnt TransformedPoint(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_NewDimensionedGeometry, IGESData_IGESEntity)

private:
  int                                                                theNbDimensions;
  occ::handle<IGESData_IGESEntity>                                   theDimensionEntity;
  int                                                                theDimensionOrientationFlag;
  double                                                             theAngleValue;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theGeometryEntities;
  occ::handle<NCollection_HArray1<int>>                              theDimensionLocationFlags;
  occ::handle<NCollection_HArray1<gp_XYZ>>                           thePoints;
};
