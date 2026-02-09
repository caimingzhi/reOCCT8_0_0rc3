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

class IGESDraw_Drawing : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_Drawing();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViews,
    const occ::handle<NCollection_HArray1<gp_XY>>&                                allViewOrigins,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&     allAnnotations);

  Standard_EXPORT int NbViews() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int ViewIndex) const;

  Standard_EXPORT gp_Pnt2d ViewOrigin(const int TViewIndex) const;

  Standard_EXPORT int NbAnnotations() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Annotation(const int AnnotationIndex) const;

  Standard_EXPORT gp_XY ViewToDrawing(const int NumView, const gp_XYZ& ViewCoords) const;

  Standard_EXPORT bool DrawingUnit(double& value) const;

  Standard_EXPORT bool DrawingSize(double& X, double& Y) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_Drawing, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViews;
  occ::handle<NCollection_HArray1<gp_XY>>                                theViewOrigins;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theAnnotations;
};
