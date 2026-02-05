#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Ax1.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Extrema_ExtPC.hpp>
#include <gp_Pnt.hpp>
class GeomFill_LocationLaw;
class Geom_Curve;
class Geom_Geometry;
class gp_Trsf;
class gp_Mat;
class gp_Vec;

//! To place section in sweep Function
class GeomFill_SectionPlacement
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_SectionPlacement(const occ::handle<GeomFill_LocationLaw>& L,
                                            const occ::handle<Geom_Geometry>&        Section);

  //! To change the section Law
  Standard_EXPORT void SetLocation(const occ::handle<GeomFill_LocationLaw>& L);

  Standard_EXPORT void Perform(const double Tol);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>& Path, const double Tol);

  Standard_EXPORT void Perform(const double ParamOnPath, const double Tol);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double ParameterOnPath() const;

  Standard_EXPORT double ParameterOnSection() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT double Angle() const;

  Standard_EXPORT gp_Trsf Transformation(const bool WithTranslation,
                                         const bool WithCorrection = false) const;

  //! Compute the Section, in the coordinate system given by
  //! the Location Law.
  //! If <WithTranslation> contact between
  //! <Section> and <Path> is forced.
  Standard_EXPORT occ::handle<Geom_Curve> Section(const bool WithTranslation) const;

  //! Compute the Section, in the coordinate system given by
  //! the Location Law.
  //! To have the Normal to section equal to the Location
  //! Law Normal. If <WithTranslation> contact between
  //! <Section> and <Path> is forced.
  Standard_EXPORT occ::handle<Geom_Curve> ModifiedSection(const bool WithTranslation) const;

private:
  Standard_EXPORT void SectionAxis(const gp_Mat& M, gp_Vec& T, gp_Vec& N, gp_Vec& BN) const;

  Standard_EXPORT bool Choix(const double Dist, const double Angle) const;

  bool                              done;
  bool                              isplan;
  gp_Ax1                            TheAxe;
  double                            Gabarit;
  occ::handle<GeomFill_LocationLaw> myLaw;
  GeomAdaptor_Curve                 myAdpSection;
  occ::handle<Geom_Curve>           mySection;
  double                            SecParam;
  double                            PathParam;
  double                            Dist;
  double                            AngleMax;
  Extrema_ExtPC                     myExt;
  bool                              myIsPoint;
  gp_Pnt                            myPoint;
};
