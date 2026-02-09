#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <IntSurf_Transition.hpp>

class BRepBlend_PointOnRst
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_PointOnRst();

  Standard_EXPORT BRepBlend_PointOnRst(const occ::handle<Adaptor2d_Curve2d>& A,
                                       const double                          Param,
                                       const IntSurf_Transition&             TLine,
                                       const IntSurf_Transition&             TArc);

  Standard_EXPORT void SetArc(const occ::handle<Adaptor2d_Curve2d>& A,
                              const double                          Param,
                              const IntSurf_Transition&             TLine,
                              const IntSurf_Transition&             TArc);

  const occ::handle<Adaptor2d_Curve2d>& Arc() const;

  const IntSurf_Transition& TransitionOnLine() const;

  const IntSurf_Transition& TransitionOnArc() const;

  double ParameterOnArc() const;

private:
  occ::handle<Adaptor2d_Curve2d> arc;
  IntSurf_Transition             traline;
  IntSurf_Transition             traarc;
  double                         prm;
};

#include <Standard_DomainError.hpp>

inline const occ::handle<Adaptor2d_Curve2d>& BRepBlend_PointOnRst::Arc() const
{
  return arc;
}

inline const IntSurf_Transition& BRepBlend_PointOnRst::TransitionOnLine() const
{
  return traline;
}

inline const IntSurf_Transition& BRepBlend_PointOnRst::TransitionOnArc() const
{
  return traarc;
}

inline double BRepBlend_PointOnRst::ParameterOnArc() const
{
  return prm;
}
