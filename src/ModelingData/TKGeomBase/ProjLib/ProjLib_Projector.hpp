#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_CurveType.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab2d.hpp>
class Geom2d_BSplineCurve;
class Geom2d_BezierCurve;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

//! Root class for projection algorithms, stores the result.
class ProjLib_Projector
{
public:
  DEFINE_STANDARD_ALLOC

  //! Sets the type to OtherCurve
  Standard_EXPORT ProjLib_Projector();
  Standard_EXPORT virtual ~ProjLib_Projector();

  Standard_EXPORT bool IsDone() const;

  //! Set isDone = true;
  Standard_EXPORT void Done();

  Standard_EXPORT GeomAbs_CurveType GetType() const;

  Standard_EXPORT void SetBSpline(const occ::handle<Geom2d_BSplineCurve>& C);

  Standard_EXPORT void SetBezier(const occ::handle<Geom2d_BezierCurve>& C);

  Standard_EXPORT void SetType(const GeomAbs_CurveType Type);

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT void SetPeriodic();

  Standard_EXPORT const gp_Lin2d& Line() const;

  Standard_EXPORT const gp_Circ2d& Circle() const;

  Standard_EXPORT const gp_Elips2d& Ellipse() const;

  Standard_EXPORT const gp_Hypr2d& Hyperbola() const;

  Standard_EXPORT const gp_Parab2d& Parabola() const;

  Standard_EXPORT occ::handle<Geom2d_BezierCurve> Bezier() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSpline() const;

  Standard_EXPORT virtual void Project(const gp_Lin& L);

  Standard_EXPORT virtual void Project(const gp_Circ& C);

  Standard_EXPORT virtual void Project(const gp_Elips& E);

  Standard_EXPORT virtual void Project(const gp_Parab& P);

  Standard_EXPORT virtual void Project(const gp_Hypr& H);

  //! Translates the 2d curve
  //! to set the part of the curve [CFirst, CLast]
  //! in the range [ UFirst, UFirst + Period [
  Standard_EXPORT void UFrame(const double CFirst,
                              const double CLast,
                              const double UFirst,
                              const double Period);

  //! Translates the 2d curve
  //! to set the part of the curve [CFirst, CLast]
  //! in the range [ VFirst, VFirst + Period [
  Standard_EXPORT void VFrame(const double CFirst,
                              const double CLast,
                              const double VFirst,
                              const double Period);

protected:
  GeomAbs_CurveType                myType;
  gp_Lin2d                         myLin;
  gp_Circ2d                        myCirc;
  gp_Elips2d                       myElips;
  gp_Hypr2d                        myHypr;
  gp_Parab2d                       myParab;
  occ::handle<Geom2d_BSplineCurve> myBSpline;
  occ::handle<Geom2d_BezierCurve>  myBezier;
  bool                             myIsPeriodic;
  bool                             isDone;
};
