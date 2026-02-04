#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESCurveOnSurface, Type <142> Form <0>
//! in package IGESGeom
//! A curve on a parametric surface entity associates a given
//! curve with a surface and identifies the curve as lying on
//! the surface.
class IGESGeom_CurveOnSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CurveOnSurface();

  //! This method is used to set the fields of the class
  //! CurveOnSurface
  //! - aMode       : Way the curve on the surface has been created
  //! - aSurface    : Surface on which the curve lies
  //! - aCurveUV    : Curve S (UV)
  //! - aCurve3D    : Curve C (3D)
  //! - aPreference : 0 = Unspecified
  //! 1 = S o B is preferred
  //! 2 = C is preferred
  //! 3 = C and S o B are equally preferred
  Standard_EXPORT void Init(const int                               aMode,
                            const occ::handle<IGESData_IGESEntity>& aSurface,
                            const occ::handle<IGESData_IGESEntity>& aCurveUV,
                            const occ::handle<IGESData_IGESEntity>& aCurve3D,
                            const int                               aPreference);

  //! returns the mode in which the curve is created on the surface
  //! 0 = Unspecified
  //! 1 = Projection of a given curve on the surface
  //! 2 = Intersection of two surfaces
  //! 3 = Isoparametric curve, i.e:- either a `u` parametric
  //! or a `v` parametric curve
  Standard_EXPORT int CreationMode() const;

  //! returns the surface on which the curve lies
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  //! returns curve S
  Standard_EXPORT occ::handle<IGESData_IGESEntity> CurveUV() const;

  //! returns curve C
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve3D() const;

  //! returns preference mode
  //! 0 = Unspecified
  //! 1 = S o B is preferred
  //! 2 = C is preferred
  //! 3 = C and S o B are equally preferred
  Standard_EXPORT int PreferenceMode() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CurveOnSurface, IGESData_IGESEntity)

private:
  int                              theCreationMode;
  occ::handle<IGESData_IGESEntity> theSurface;
  occ::handle<IGESData_IGESEntity> theCurveUV;
  occ::handle<IGESData_IGESEntity> theCurve3D;
  int                              thePreferenceMode;
};

