#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <CSLib_Class2d.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Face.hpp>
#include <TopAbs_State.hpp>

class gp_Pnt2d;

class BRepTopAdaptor_FClass2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTopAdaptor_FClass2d(const TopoDS_Face& F, const double Tol);

  Standard_EXPORT TopAbs_State PerformInfinitePoint() const;

  Standard_EXPORT TopAbs_State Perform(const gp_Pnt2d& Puv,
                                       const bool      RecadreOnPeriodic = true) const;

  Standard_EXPORT void Destroy();

  ~BRepTopAdaptor_FClass2d() { Destroy(); }

  Standard_EXPORT const BRepTopAdaptor_FClass2d& Copy(const BRepTopAdaptor_FClass2d& Other) const;

  const BRepTopAdaptor_FClass2d& operator=(const BRepTopAdaptor_FClass2d& Other) const
  {
    return Copy(Other);
  }

  //! Test a point with +- an offset (Tol) and returns
  //! On if some points are OUT an some are IN
  //! (Caution: Internal use. see the code for more details)
  Standard_EXPORT TopAbs_State TestOnRestriction(const gp_Pnt2d& Puv,
                                                 const double    Tol,
                                                 const bool      RecadreOnPeriodic = true) const;

private:
  NCollection_Sequence<CSLib_Class2d> TabClass;
  NCollection_Sequence<int>           TabOrien;
  double                              Toluv;
  TopoDS_Face                         Face;
  double                              U1;
  double                              V1;
  double                              U2;
  double                              V2;
  double                              Umin;
  double                              Umax;
  double                              Vmin;
  double                              Vmax;
};

