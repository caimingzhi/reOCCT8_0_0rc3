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

  //! Creates an extremity on a surface
  Standard_EXPORT BRepBlend_Extremity(const gp_Pnt& P,
                                      const double  U,
                                      const double  V,
                                      const double  Param,
                                      const double  Tol);

  //! Creates an extremity on a surface. This extremity matches
  //! the vertex <Vtx>.
  Standard_EXPORT BRepBlend_Extremity(const gp_Pnt&                         P,
                                      const double                          U,
                                      const double                          V,
                                      const double                          Param,
                                      const double                          Tol,
                                      const occ::handle<Adaptor3d_HVertex>& Vtx);

  //! Creates an extremity on a curve
  Standard_EXPORT BRepBlend_Extremity(const gp_Pnt& P,
                                      const double  W,
                                      const double  Param,
                                      const double  Tol);

  //! Set the values for an extremity on a surface.
  Standard_EXPORT void SetValue(const gp_Pnt& P,
                                const double  U,
                                const double  V,
                                const double  Param,
                                const double  Tol);

  //! Set the values for an extremity on a surface.This
  //! extremity matches the vertex <Vtx>.
  Standard_EXPORT void SetValue(const gp_Pnt&                         P,
                                const double                          U,
                                const double                          V,
                                const double                          Param,
                                const double                          Tol,
                                const occ::handle<Adaptor3d_HVertex>& Vtx);

  //! Set the values for an extremity on curve.
  Standard_EXPORT void SetValue(const gp_Pnt& P,
                                const double  W,
                                const double  Param,
                                const double  Tol);

  //! This method returns the value of the point in 3d space.
  const gp_Pnt& Value() const;

  //! Set the tangent vector for an extremity on a
  //! surface.
  void SetTangent(const gp_Vec& Tangent);

  //! Returns TRUE if the Tangent is stored.
  bool HasTangent() const;

  //! This method returns the value of tangent in 3d
  //! space.
  const gp_Vec& Tangent() const;

  //! This method returns the fuzziness on the point
  //! in 3d space.
  double Tolerance() const;

  //! Set the values for an extremity on a curve.
  Standard_EXPORT void SetVertex(const occ::handle<Adaptor3d_HVertex>& V);

  //! Sets the values of a point which is on the arc
  //! A, at parameter Param.
  Standard_EXPORT void AddArc(const occ::handle<Adaptor2d_Curve2d>& A,
                              const double                          Param,
                              const IntSurf_Transition&             TLine,
                              const IntSurf_Transition&             TArc);

  //! This method returns the parameters of the point
  //! on the concerned surface.
  void Parameters(double& U, double& V) const;

  //! Returns true when the point coincide with
  //! an existing vertex.
  bool IsVertex() const;

  //! Returns the vertex when IsVertex returns true.
  const occ::handle<Adaptor3d_HVertex>& Vertex() const;

  //! Returns the number of arc containing the extremity.
  //! If the method returns 0, the point is inside the
  //! surface.
  //! Otherwise, the extremity lies on at least 1 arc,
  //! and all the information (arc, parameter, transitions)
  //! are given by the point on restriction (PointOnRst)
  //! returned by the next method.
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

// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

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
