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

//! defines IGESDrawing, Type <404> Form <0>
//! in package IGESDraw
//!
//! Specifies a drawing as a collection of annotation entities
//! defined in drawing space, and views which together
//! constitute a single representation of a part
class IGESDraw_Drawing : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_Drawing();

  //! This method is used to set the fields of the class
  //! Drawing
  //! - allViews       : Pointers to DEs of View entities
  //! - allViewOrigins : Origin coordinates of transformed Views
  //! - allAnnotations : Pointers to DEs of Annotation entities
  //! raises exception if Lengths of allViews and allViewOrigins are
  //! not same.
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViews,
    const occ::handle<NCollection_HArray1<gp_XY>>&                                allViewOrigins,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&     allAnnotations);

  //! returns the number of view pointers in <me>
  Standard_EXPORT int NbViews() const;

  //! returns the ViewKindEntity indicated by ViewIndex
  //! raises an exception if ViewIndex <= 0 or ViewIndex > NbViews().
  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int ViewIndex) const;

  //! returns the Drawing space coordinates of the origin of the
  //! Transformed view indicated by TViewIndex
  //! raises an exception if TViewIndex <= 0 or TViewIndex > NbViews().
  Standard_EXPORT gp_Pnt2d ViewOrigin(const int TViewIndex) const;

  //! returns the number of Annotation entities in <me>
  Standard_EXPORT int NbAnnotations() const;

  //! returns the Annotation entity in this Drawing, indicated by the
  //! AnnotationIndex
  //! raises an exception if AnnotationIndex <= 0 or
  //! AnnotationIndex > NbAnnotations().
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Annotation(const int AnnotationIndex) const;

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

  DEFINE_STANDARD_RTTIEXT(IGESDraw_Drawing, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViews;
  occ::handle<NCollection_HArray1<gp_XY>>                                theViewOrigins;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theAnnotations;
};
