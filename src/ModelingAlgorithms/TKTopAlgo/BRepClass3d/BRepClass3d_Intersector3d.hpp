#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Face.hpp>
class gp_Lin;

class BRepClass3d_Intersector3d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass3d_Intersector3d();

  Standard_EXPORT void Perform(const gp_Lin&      L,
                               const double       Prm,
                               const double       Tol,
                               const TopoDS_Face& F);

  bool IsDone() const;

  bool HasAPoint() const;

  double UParameter() const;

  double VParameter() const;

  double WParameter() const;

  const gp_Pnt& Pnt() const;

  IntCurveSurface_TransitionOnCurve Transition() const;

  TopAbs_State State() const;

  const TopoDS_Face& Face() const;

private:
  gp_Pnt                            pnt;
  double                            U;
  double                            V;
  double                            W;
  IntCurveSurface_TransitionOnCurve transition;
  bool                              done;
  bool                              hasapoint;
  TopAbs_State                      state;
  TopoDS_Face                       face;
};

inline bool BRepClass3d_Intersector3d::IsDone() const
{
  return (done);
}

inline bool BRepClass3d_Intersector3d::HasAPoint() const
{
  return (hasapoint);
}

inline const gp_Pnt& BRepClass3d_Intersector3d::Pnt() const
{
  return (pnt);
}

inline double BRepClass3d_Intersector3d::UParameter() const
{
  return (U);
}

inline double BRepClass3d_Intersector3d::VParameter() const
{
  return (V);
}

inline double BRepClass3d_Intersector3d::WParameter() const
{
  return (W);
}

inline IntCurveSurface_TransitionOnCurve BRepClass3d_Intersector3d::Transition() const
{
  return (transition);
}

inline TopAbs_State BRepClass3d_Intersector3d::State() const
{
  return (state);
}

inline const TopoDS_Face& BRepClass3d_Intersector3d::Face() const
{
  return (face);
}
