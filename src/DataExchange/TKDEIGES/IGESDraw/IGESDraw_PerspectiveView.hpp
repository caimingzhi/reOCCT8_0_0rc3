#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <gp_XY.hpp>
#include <IGESData_ViewKindEntity.hpp>
class gp_Vec;
class gp_Pnt;
class gp_Pnt2d;
class IGESData_TransfEntity;

class IGESDraw_PerspectiveView : public IGESData_ViewKindEntity
{

public:
  Standard_EXPORT IGESDraw_PerspectiveView();

  Standard_EXPORT void Init(const int     aViewNumber,
                            const double  aScaleFactor,
                            const gp_XYZ& aViewNormalVector,
                            const gp_XYZ& aViewReferencePoint,
                            const gp_XYZ& aCenterOfProjection,
                            const gp_XYZ& aViewUpVector,
                            const double  aViewPlaneDistance,
                            const gp_XY&  aTopLeft,
                            const gp_XY&  aBottomRight,
                            const int     aDepthClip,
                            const double  aBackPlaneDistance,
                            const double  aFrontPlaneDistance);

  Standard_EXPORT bool IsSingle() const override;

  Standard_EXPORT int NbViews() const override;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int num) const override;

  Standard_EXPORT int ViewNumber() const;

  Standard_EXPORT double ScaleFactor() const;

  Standard_EXPORT gp_Vec ViewNormalVector() const;

  Standard_EXPORT gp_Pnt ViewReferencePoint() const;

  Standard_EXPORT gp_Pnt CenterOfProjection() const;

  Standard_EXPORT gp_Vec ViewUpVector() const;

  Standard_EXPORT double ViewPlaneDistance() const;

  Standard_EXPORT gp_Pnt2d TopLeft() const;

  Standard_EXPORT gp_Pnt2d BottomRight() const;

  Standard_EXPORT int DepthClip() const;

  Standard_EXPORT double BackPlaneDistance() const;

  Standard_EXPORT double FrontPlaneDistance() const;

  Standard_EXPORT occ::handle<IGESData_TransfEntity> ViewMatrix() const;

  Standard_EXPORT gp_XYZ ModelToView(const gp_XYZ& coords) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_PerspectiveView, IGESData_ViewKindEntity)

private:
  int    theViewNumber;
  double theScaleFactor;
  gp_XYZ theViewNormalVector;
  gp_XYZ theViewReferencePoint;
  gp_XYZ theCenterOfProjection;
  gp_XYZ theViewUpVector;
  double theViewPlaneDistance;
  gp_XY  theTopLeft;
  gp_XY  theBottomRight;
  int    theDepthClip;
  double theBackPlaneDistance;
  double theFrontPlaneDistance;
};
