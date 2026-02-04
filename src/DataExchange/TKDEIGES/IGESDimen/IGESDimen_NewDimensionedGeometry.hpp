#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
class gp_Pnt;

//! defines New Dimensioned Geometry, Type <402>, Form <21>
//! in package IGESDimen
//! Links a dimension entity with the geometry entities it
//! is dimensioning, so that later, in the receiving
//! database, the dimension can be automatically recalculated
//! and redrawn should the geometry be changed.
class IGESDimen_NewDimensionedGeometry : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_NewDimensionedGeometry();

  //! This method is used to set the fields of the class
  //! NewDimensionedGeometry
  //! - nbDimen       : Number of Dimensions, default = 1
  //! - aDimen        : Dimension Entity
  //! - anOrientation : Dimension Orientation Flag
  //! - anAngle       : Angle Value
  //! - allEntities   : Geometric Entities
  //! - allLocations  : Dimension Location Flags
  //! - allPoints     : Points on the Geometry Entities
  //! exception raised if lengths of entities, locations, points
  //! are not the same
  Standard_EXPORT void Init(
    const int                                                                 nbDimens,
    const occ::handle<IGESData_IGESEntity>&                                   aDimen,
    const int                                                                 anOrientation,
    const double                                                              anAngle,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities,
    const occ::handle<NCollection_HArray1<int>>&                              allLocations,
    const occ::handle<NCollection_HArray1<gp_XYZ>>&                           allPoints);

  //! returns the number of dimensions
  Standard_EXPORT int NbDimensions() const;

  //! returns the number of associated geometry entities
  Standard_EXPORT int NbGeometries() const;

  //! returns the dimension entity
  Standard_EXPORT occ::handle<IGESData_IGESEntity> DimensionEntity() const;

  //! returns the dimension orientation flag
  Standard_EXPORT int DimensionOrientationFlag() const;

  //! returns the angle value
  Standard_EXPORT double AngleValue() const;

  //! returns the Index'th geometry entity
  //! raises exception if Index <= 0 or Index > NbGeometries()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> GeometryEntity(const int Index) const;

  //! returns the Index'th geometry entity's dimension location flag
  //! raises exception if Index <= 0 or Index > NbGeometries()
  Standard_EXPORT int DimensionLocationFlag(const int Index) const;

  //! coordinate of point on Index'th geometry entity
  //! raises exception if Index <= 0 or Index > NbGeometries()
  Standard_EXPORT gp_Pnt Point(const int Index) const;

  //! coordinate of point on Index'th geometry entity after Transformation
  //! raises exception if Index <= 0 or Index > NbGeometries()
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

