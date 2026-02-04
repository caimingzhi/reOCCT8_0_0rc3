#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESData_ViewKindEntity;
class gp_Pnt2d;
class gp_XY;
class gp_XYZ;

//! defines IGESDrawingWithRotation, Type <404> Form <1>
//! in package IGESDraw
//!
//! Permits rotation, in addition to transformation and
//! scaling, between the view and drawing coordinate systems
class IGESDraw_DrawingWithRotation : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_DrawingWithRotation();

  //! This method is used to set the fields of the class
  //! DrawingWithRotation
  //! - allViews             : Pointers to View entities
  //! - allViewOrigins       : Origin coords of transformed views
  //! - allOrientationAngles : Orientation angles of transformed views
  //! - allAnnotations       : Pointers to Annotation entities
  //! raises exception if Lengths of allViews, allViewOrigins and
  //! allOrientationAngles are not same.
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViews,
    const occ::handle<NCollection_HArray1<gp_XY>>&                                allViewOrigins,
    const occ::handle<NCollection_HArray1<double>>&                           allOrientationAngles,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allAnnotations);

  //! returns the number of view pointers in <me>
  Standard_EXPORT int NbViews() const;

  //! returns the View entity indicated by Index
  //! raises an exception if Index <= 0 or Index > NbViews().
  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int Index) const;

  //! returns the Drawing space coordinates of the origin of the
  //! Transformed view indicated by Index
  //! raises an exception if Index <= 0 or Index > NbViews().
  Standard_EXPORT gp_Pnt2d ViewOrigin(const int Index) const;

  //! returns the Orientation angle for the Transformed view
  //! indicated by Index
  //! raises an exception if Index <= 0 or Index > NbViews().
  Standard_EXPORT double OrientationAngle(const int Index) const;

  //! returns the number of Annotation entities in <me>
  Standard_EXPORT int NbAnnotations() const;

  //! returns the Annotation entity in this Drawing, indicated by Index
  //! raises an exception if Index <= 0 or Index > NbAnnotations().
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Annotation(const int Index) const;

  Standard_EXPORT gp_XY ViewToDrawing(const int NumView, const gp_XYZ& ViewCoords) const;

  //! Returns the Drawing Unit Value if it is specified (by a
  //! specific property entity)
  //! If not specified, returns False, and val as zero :
  //! unit to consider is then the model unit in GlobalSection
  Standard_EXPORT bool DrawingUnit(double& value) const;

  //! Returns the Drawing Size if it is specified (by a
  //! specific property entity)
  //! If not specified, returns False, and X,Y as zero :
  //! unit to consider is then the model unit in GlobalSection
  Standard_EXPORT bool DrawingSize(double& X, double& Y) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_DrawingWithRotation, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViews;
  occ::handle<NCollection_HArray1<gp_XY>>                                theViewOrigins;
  occ::handle<NCollection_HArray1<double>>                               theOrientationAngles;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theAnnotations;
};

