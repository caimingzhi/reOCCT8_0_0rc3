#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_Boolean.hpp>
#include <gp_Vec2d.hpp>
class gp_Vec2d;

class Blend_Point
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Blend_Point();

  //! Creates a point on 2 surfaces, with tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt&   Pt1,
                              const gp_Pnt&   Pt2,
                              const double    Param,
                              const double    U1,
                              const double    V1,
                              const double    U2,
                              const double    V2,
                              const gp_Vec&   Tg1,
                              const gp_Vec&   Tg2,
                              const gp_Vec2d& Tg12d,
                              const gp_Vec2d& Tg22d);

  //! Creates a point on 2 surfaces, without tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt& Pt1,
                              const gp_Pnt& Pt2,
                              const double  Param,
                              const double  U1,
                              const double  V1,
                              const double  U2,
                              const double  V2);

  //! Creates a point on a surface and a curve, with tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt&   Pts,
                              const gp_Pnt&   Ptc,
                              const double    Param,
                              const double    U,
                              const double    V,
                              const double    W,
                              const gp_Vec&   Tgs,
                              const gp_Vec&   Tgc,
                              const gp_Vec2d& Tg2d);

  //! Creates a point on a surface and a curve, without tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt& Pts,
                              const gp_Pnt& Ptc,
                              const double  Param,
                              const double  U,
                              const double  V,
                              const double  W);

  //! Creates a point on a surface and a curve on surface,
  //! with tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt&   Pt1,
                              const gp_Pnt&   Pt2,
                              const double    Param,
                              const double    U1,
                              const double    V1,
                              const double    U2,
                              const double    V2,
                              const double    PC,
                              const gp_Vec&   Tg1,
                              const gp_Vec&   Tg2,
                              const gp_Vec2d& Tg12d,
                              const gp_Vec2d& Tg22d);

  //! Creates a point on a surface and a curve on surface,
  //! without tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt& Pt1,
                              const gp_Pnt& Pt2,
                              const double  Param,
                              const double  U1,
                              const double  V1,
                              const double  U2,
                              const double  V2,
                              const double  PC);

  //! Creates a point on two curves on surfaces, with tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt&   Pt1,
                              const gp_Pnt&   Pt2,
                              const double    Param,
                              const double    U1,
                              const double    V1,
                              const double    U2,
                              const double    V2,
                              const double    PC1,
                              const double    PC2,
                              const gp_Vec&   Tg1,
                              const gp_Vec&   Tg2,
                              const gp_Vec2d& Tg12d,
                              const gp_Vec2d& Tg22d);

  //! Creates a point on two curves on surfaces, with tangents.
  Standard_EXPORT Blend_Point(const gp_Pnt& Pt1,
                              const gp_Pnt& Pt2,
                              const double  Param,
                              const double  U1,
                              const double  V1,
                              const double  U2,
                              const double  V2,
                              const double  PC1,
                              const double  PC2);

  //! Set the values for a point on 2 surfaces, with tangents.
  Standard_EXPORT void SetValue(const gp_Pnt&   Pt1,
                                const gp_Pnt&   Pt2,
                                const double    Param,
                                const double    U1,
                                const double    V1,
                                const double    U2,
                                const double    V2,
                                const gp_Vec&   Tg1,
                                const gp_Vec&   Tg2,
                                const gp_Vec2d& Tg12d,
                                const gp_Vec2d& Tg22d);

  //! Set the values for a point on 2 surfaces, without tangents.
  Standard_EXPORT void SetValue(const gp_Pnt& Pt1,
                                const gp_Pnt& Pt2,
                                const double  Param,
                                const double  U1,
                                const double  V1,
                                const double  U2,
                                const double  V2);

  //! Set the values for a point on a surface and a curve,
  //! with tangents.
  Standard_EXPORT void SetValue(const gp_Pnt&   Pts,
                                const gp_Pnt&   Ptc,
                                const double    Param,
                                const double    U,
                                const double    V,
                                const double    W,
                                const gp_Vec&   Tgs,
                                const gp_Vec&   Tgc,
                                const gp_Vec2d& Tg2d);

  //! Set the values for a point on a surface and a curve,
  //! without tangents.
  Standard_EXPORT void SetValue(const gp_Pnt& Pts,
                                const gp_Pnt& Ptc,
                                const double  Param,
                                const double  U,
                                const double  V,
                                const double  W);

  //! Creates a point on a surface and a curve on surface,
  //! with tangents.
  Standard_EXPORT void SetValue(const gp_Pnt&   Pt1,
                                const gp_Pnt&   Pt2,
                                const double    Param,
                                const double    U1,
                                const double    V1,
                                const double    U2,
                                const double    V2,
                                const double    PC,
                                const gp_Vec&   Tg1,
                                const gp_Vec&   Tg2,
                                const gp_Vec2d& Tg12d,
                                const gp_Vec2d& Tg22d);

  //! Creates a point on a surface and a curve on surface,
  //! without tangents.
  Standard_EXPORT void SetValue(const gp_Pnt& Pt1,
                                const gp_Pnt& Pt2,
                                const double  Param,
                                const double  U1,
                                const double  V1,
                                const double  U2,
                                const double  V2,
                                const double  PC);

  //! Creates a point on two curves on surfaces, with tangents.
  Standard_EXPORT void SetValue(const gp_Pnt&   Pt1,
                                const gp_Pnt&   Pt2,
                                const double    Param,
                                const double    U1,
                                const double    V1,
                                const double    U2,
                                const double    V2,
                                const double    PC1,
                                const double    PC2,
                                const gp_Vec&   Tg1,
                                const gp_Vec&   Tg2,
                                const gp_Vec2d& Tg12d,
                                const gp_Vec2d& Tg22d);

  //! Creates a point on two curves on surfaces, without tangents.
  Standard_EXPORT void SetValue(const gp_Pnt& Pt1,
                                const gp_Pnt& Pt2,
                                const double  Param,
                                const double  U1,
                                const double  V1,
                                const double  U2,
                                const double  V2,
                                const double  PC1,
                                const double  PC2);

  //! Creates a point on two curves.
  Standard_EXPORT void SetValue(const gp_Pnt& Pt1,
                                const gp_Pnt& Pt2,
                                const double  Param,
                                const double  PC1,
                                const double  PC2);

  //! Changes parameter on existing point
  void SetParameter(const double Param);

  double Parameter() const;

  //! Returns true if it was not possible to compute
  //! the tangent vectors at PointOnS1 and/or PointOnS2.
  bool IsTangencyPoint() const;

  const gp_Pnt& PointOnS1() const;

  const gp_Pnt& PointOnS2() const;

  void ParametersOnS1(double& U, double& V) const;

  void ParametersOnS2(double& U, double& V) const;

  const gp_Vec& TangentOnS1() const;

  const gp_Vec& TangentOnS2() const;

  gp_Vec2d Tangent2dOnS1() const;

  gp_Vec2d Tangent2dOnS2() const;

  const gp_Pnt& PointOnS() const;

  const gp_Pnt& PointOnC() const;

  void ParametersOnS(double& U, double& V) const;

  double ParameterOnC() const;

  const gp_Vec& TangentOnS() const;

  const gp_Vec& TangentOnC() const;

  gp_Vec2d Tangent2d() const;

  const gp_Pnt& PointOnC1() const;

  const gp_Pnt& PointOnC2() const;

  double ParameterOnC1() const;

  double ParameterOnC2() const;

  const gp_Vec& TangentOnC1() const;

  const gp_Vec& TangentOnC2() const;

private:
  gp_Pnt pt1;
  gp_Pnt pt2;
  gp_Vec tg1;
  gp_Vec tg2;
  double prm;
  double u1;
  double v1;
  double u2;
  double v2;
  double pc1;
  double pc2;
  double utg12d;
  double vtg12d;
  double utg22d;
  double vtg22d;
  bool   hass1;
  bool   hass2;
  bool   hasc1;
  bool   hasc2;
  bool   istgt;
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
#include <gp_Vec2d.hpp>

inline void Blend_Point::SetParameter(const double Param)
{
  prm = Param;
}

inline const gp_Pnt& Blend_Point::PointOnS1() const
{
  return pt1;
}

inline const gp_Pnt& Blend_Point::PointOnS2() const
{
  return pt2;
}

inline double Blend_Point::Parameter() const
{
  return prm;
}

inline void Blend_Point::ParametersOnS1(double& U1, double& V1) const
{
  if (!hass1)
  {
    throw Standard_DomainError();
  }
  U1 = u1;
  V1 = v1;
}

inline void Blend_Point::ParametersOnS2(double& U2, double& V2) const
{
  if (!hass2)
  {
    throw Standard_DomainError();
  }
  U2 = u2;
  V2 = v2;
}

inline bool Blend_Point::IsTangencyPoint() const
{
  return istgt;
}

inline const gp_Vec& Blend_Point::TangentOnS1() const
{
  if (istgt)
  {
    throw Standard_DomainError();
  }
  return tg1;
}

inline const gp_Vec& Blend_Point::TangentOnS2() const
{
  if (istgt)
  {
    throw Standard_DomainError();
  }
  return tg2;
}

inline gp_Vec2d Blend_Point::Tangent2dOnS1() const
{
  if (istgt || !hass1)
  {
    throw Standard_DomainError();
  }
  return gp_Vec2d(utg12d, vtg12d);
}

inline gp_Vec2d Blend_Point::Tangent2dOnS2() const
{
  if (istgt || !hass2)
  {
    throw Standard_DomainError();
  }
  return gp_Vec2d(utg22d, vtg22d);
}

inline const gp_Pnt& Blend_Point::PointOnS() const
{
  return pt1;
}

inline const gp_Pnt& Blend_Point::PointOnC() const
{
  return pt2;
}

inline void Blend_Point::ParametersOnS(double& U1, double& V1) const
{
  if (!hass1)
  {
    throw Standard_DomainError();
  }
  U1 = u1;
  V1 = v1;
}

inline double Blend_Point::ParameterOnC() const
{
  if (!hasc2)
  {
    throw Standard_DomainError();
  }
  return pc2;
}

inline const gp_Vec& Blend_Point::TangentOnS() const
{
  if (istgt || !hass1)
  {
    throw Standard_DomainError();
  }
  return tg1;
}

inline const gp_Vec& Blend_Point::TangentOnC() const
{
  if (istgt)
  {
    throw Standard_DomainError();
  }
  return tg2;
}

inline gp_Vec2d Blend_Point::Tangent2d() const
{
  if (istgt || !hass1)
  {
    throw Standard_DomainError();
  }
  return gp_Vec2d(utg12d, vtg12d);
}

inline const gp_Pnt& Blend_Point::PointOnC1() const
{
  return pt1;
}

inline const gp_Pnt& Blend_Point::PointOnC2() const
{
  return pt2;
}

inline double Blend_Point::ParameterOnC1() const
{
  if (!hasc1)
  {
    throw Standard_DomainError();
  }
  return pc1;
}

inline double Blend_Point::ParameterOnC2() const
{
  if (!hasc2)
  {
    throw Standard_DomainError();
  }
  return pc2;
}

inline const gp_Vec& Blend_Point::TangentOnC1() const
{
  if (istgt || !hass1)
  {
    throw Standard_DomainError();
  }
  return tg1;
}

inline const gp_Vec& Blend_Point::TangentOnC2() const
{
  if (istgt)
  {
    throw Standard_DomainError();
  }
  return tg2;
}


