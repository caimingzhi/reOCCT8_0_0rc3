#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_ViewKindEntity.hpp>
class IGESGeom_Plane;
class IGESData_TransfEntity;
class gp_XYZ;

class IGESDraw_View : public IGESData_ViewKindEntity
{

public:
  Standard_EXPORT IGESDraw_View();

  Standard_EXPORT void Init(const int                          aViewNum,
                            const double                       aScale,
                            const occ::handle<IGESGeom_Plane>& aLeftPlane,
                            const occ::handle<IGESGeom_Plane>& aTopPlane,
                            const occ::handle<IGESGeom_Plane>& aRightPlane,
                            const occ::handle<IGESGeom_Plane>& aBottomPlane,
                            const occ::handle<IGESGeom_Plane>& aBackPlane,
                            const occ::handle<IGESGeom_Plane>& aFrontPlane);

  Standard_EXPORT bool IsSingle() const override;

  Standard_EXPORT int NbViews() const override;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int num) const override;

  Standard_EXPORT int ViewNumber() const;

  Standard_EXPORT double ScaleFactor() const;

  Standard_EXPORT bool HasLeftPlane() const;

  Standard_EXPORT occ::handle<IGESGeom_Plane> LeftPlane() const;

  Standard_EXPORT bool HasTopPlane() const;

  Standard_EXPORT occ::handle<IGESGeom_Plane> TopPlane() const;

  Standard_EXPORT bool HasRightPlane() const;

  Standard_EXPORT occ::handle<IGESGeom_Plane> RightPlane() const;

  Standard_EXPORT bool HasBottomPlane() const;

  Standard_EXPORT occ::handle<IGESGeom_Plane> BottomPlane() const;

  Standard_EXPORT bool HasBackPlane() const;

  Standard_EXPORT occ::handle<IGESGeom_Plane> BackPlane() const;

  Standard_EXPORT bool HasFrontPlane() const;

  Standard_EXPORT occ::handle<IGESGeom_Plane> FrontPlane() const;

  Standard_EXPORT occ::handle<IGESData_TransfEntity> ViewMatrix() const;

  Standard_EXPORT gp_XYZ ModelToView(const gp_XYZ& coords) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_View, IGESData_ViewKindEntity)

private:
  int                         theViewNumber;
  double                      theScaleFactor;
  occ::handle<IGESGeom_Plane> theLeftPlane;
  occ::handle<IGESGeom_Plane> theTopPlane;
  occ::handle<IGESGeom_Plane> theRightPlane;
  occ::handle<IGESGeom_Plane> theBottomPlane;
  occ::handle<IGESGeom_Plane> theBackPlane;
  occ::handle<IGESGeom_Plane> theFrontPlane;
};
