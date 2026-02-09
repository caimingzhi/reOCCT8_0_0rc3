#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepBlend_PointOnRst.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
class Adaptor3d_HVertex;
class IntSurf_Transition;
class BRepBlend_PointOnRst;

class BRepBlend_Extremity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_Extremity();

  Standard_EXPORT BRepBlend_Extremity(const gp_Pnt& P,
                                      const double  U,
                                      const double  V,
                                      const double  Param,
                                      const double  Tol);

  Standard_EXPORT BRepBlend_Extremity(const gp_Pnt&                         P,
                                      const double                          U,
                                      const double                          V,
                                      const double                          Param,
                                      const double                          Tol,
                                      const occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT BRepBlend_Extremity(const gp_Pnt& P,
                                      const double  W,
                                      const double  Param,
                                      const double  Tol);

  Standard_EXPORT void SetValue(const gp_Pnt& P,
                                const double  U,
                                const double  V,
                                const double  Param,
                                const double  Tol);

  Standard_EXPORT void SetValue(const gp_Pnt&                         P,
                                const double                          U,
                                const double                          V,
                                const double                          Param,
                                const double                          Tol,
                                const occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT void SetValue(const gp_Pnt& P,
                                const double  W,
                                const double  Param,
                                const double  Tol);

  const gp_Pnt& Value() const;

  void SetTangent(const gp_Vec& Tangent);

  bool HasTangent() const;

  const gp_Vec& Tangent() const;

  double Tolerance() const;

  Standard_EXPORT void SetVertex(const occ::handle<Adaptor3d_HVertex>& V);

  Standard_EXPORT void AddArc(const occ::handle<Adaptor2d_Curve2d>& A,
                              const double                          Param,
                              const IntSurf_Transition&             TLine,
                              const IntSurf_Transition&             TArc);

  void Parameters(double& U, double& V) const;

  bool IsVertex() const;

  const occ::handle<Adaptor3d_HVertex>& Vertex() const;

  int NbPointOnRst() const;

  const BRepBlend_PointOnRst& PointOnRst(const int Index) const;

  double Parameter() const;

  double ParameterOnGuide() const;

private:
  occ::handle<Adaptor3d_HVertex>             vtx;
  NCollection_Sequence<BRepBlend_PointOnRst> seqpt;
  gp_Pnt                                     pt;
  gp_Vec                                     tang;
  double                                     param;
  double                                     u;
  double                                     v;
  double                                     tol;
  bool                                       isvtx;
  bool                                       hastang;
};

#include <Standard_DomainError.hpp>

inline const gp_Pnt& BRepBlend_Extremity::Value() const
{
  return pt;
}

inline void BRepBlend_Extremity::SetTangent(const gp_Vec& Tangent)
{
  hastang = true;
  tang    = Tangent;
}

inline bool BRepBlend_Extremity::HasTangent() const
{
  return hastang;
}

inline const gp_Vec& BRepBlend_Extremity::Tangent() const
{
  if (!hastang)
  {
    throw Standard_DomainError();
  }
  return tang;
}

inline void BRepBlend_Extremity::Parameters(double& U, double& V) const
{
  U = u;
  V = v;
}

inline double BRepBlend_Extremity::Tolerance() const
{
  return tol;
}

inline bool BRepBlend_Extremity::IsVertex() const
{
  return isvtx;
}

inline const occ::handle<Adaptor3d_HVertex>& BRepBlend_Extremity::Vertex() const
{
  if (!isvtx)
  {
    throw Standard_DomainError();
  }
  return vtx;
}

inline int BRepBlend_Extremity::NbPointOnRst() const
{
  return seqpt.Length();
}

inline const BRepBlend_PointOnRst& BRepBlend_Extremity::PointOnRst(const int Index) const
{
  return seqpt(Index);
}

inline double BRepBlend_Extremity::Parameter() const

{
  return u;
}

inline double BRepBlend_Extremity::ParameterOnGuide() const

{
  return param;
}
