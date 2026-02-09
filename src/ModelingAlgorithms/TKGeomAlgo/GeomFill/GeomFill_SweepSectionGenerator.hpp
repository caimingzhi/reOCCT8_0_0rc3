#pragma once

#include <Adaptor3d_Curve.hpp>
#include <gp_Ax1.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

class Geom_BSplineCurve;
class Geom_Curve;
class gp_Trsf;

class GeomFill_SweepSectionGenerator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_SweepSectionGenerator();

  Standard_EXPORT GeomFill_SweepSectionGenerator(const occ::handle<Geom_Curve>& Path,
                                                 const double                   Radius);

  Standard_EXPORT GeomFill_SweepSectionGenerator(const occ::handle<Geom_Curve>& Path,
                                                 const occ::handle<Geom_Curve>& FirstSect);

  Standard_EXPORT GeomFill_SweepSectionGenerator(const occ::handle<Geom_Curve>& Path,
                                                 const occ::handle<Geom_Curve>& FirstSect,
                                                 const occ::handle<Geom_Curve>& LastSect);

  Standard_EXPORT GeomFill_SweepSectionGenerator(const occ::handle<Geom_Curve>& Path,
                                                 const occ::handle<Geom_Curve>& Curve1,
                                                 const occ::handle<Geom_Curve>& Curve2,
                                                 const double                   Radius);

  Standard_EXPORT GeomFill_SweepSectionGenerator(const occ::handle<Adaptor3d_Curve>& Path,
                                                 const occ::handle<Adaptor3d_Curve>& Curve1,
                                                 const occ::handle<Adaptor3d_Curve>& Curve2,
                                                 const double                        Radius);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path, const double Radius);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path,
                            const occ::handle<Geom_Curve>& FirstSect);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path,
                            const occ::handle<Geom_Curve>& FirstSect,
                            const occ::handle<Geom_Curve>& LastSect);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Path,
                            const occ::handle<Geom_Curve>& Curve1,
                            const occ::handle<Geom_Curve>& Curve2,
                            const double                   Radius);

  Standard_EXPORT void Init(const occ::handle<Adaptor3d_Curve>& Path,
                            const occ::handle<Adaptor3d_Curve>& Curve1,
                            const occ::handle<Adaptor3d_Curve>& Curve2,
                            const double                        Radius);

  Standard_EXPORT void Perform(const bool Polynomial = false);

  Standard_EXPORT void GetShape(int& NbPoles, int& NbKnots, int& Degree, int& NbPoles2d) const;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) const;

  int NbSections() const;

  Standard_EXPORT bool Section(const int                     P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths) const;

  Standard_EXPORT void Section(const int                     P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths) const;

  Standard_EXPORT const gp_Trsf& Transformation(const int Index) const;

  Standard_EXPORT double Parameter(const int P) const;

private:
  occ::handle<Geom_BSplineCurve> myPath;
  occ::handle<Geom_BSplineCurve> myFirstSect;
  occ::handle<Geom_BSplineCurve> myLastSect;
  occ::handle<Adaptor3d_Curve>   myAdpPath;
  occ::handle<Adaptor3d_Curve>   myAdpFirstSect;
  occ::handle<Adaptor3d_Curve>   myAdpLastSect;
  gp_Ax1                         myCircPathAxis;
  double                         myRadius;
  bool                           myIsDone;
  int                            myNbSections;
  NCollection_Sequence<gp_Trsf>  myTrsfs;
  int                            myType;
  bool                           myPolynomial;
};

inline int GeomFill_SweepSectionGenerator::NbSections() const
{
  return myNbSections;
}
