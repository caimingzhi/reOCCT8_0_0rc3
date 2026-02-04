#pragma once


#include <Adaptor3d_Surface.hpp>
#include <Contap_TFunction.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Vec.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class math_Matrix;

//! This class describes the function on a parametric surface.
//! the form of the function is F(u,v) = 0 where u and v are
//! the parametric coordinates of a point on the surface,
//! to compute the contours of the surface.
class Contap_SurfFunction : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_SurfFunction();

  Standard_EXPORT void Set(const occ::handle<Adaptor3d_Surface>& S);

  void Set(const gp_Pnt& Eye);

  void Set(const gp_Dir& Dir);

  void Set(const gp_Dir& Dir, const double Angle);

  void Set(const gp_Pnt& Eye, const double Angle);

  void Set(const double Tolerance);

  //! This method has to return 2.
  Standard_EXPORT int NbVariables() const override;

  //! This method has to return 1.
  Standard_EXPORT int NbEquations() const override;

  //! The dimension of F is 1.
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  //! The dimension of D is (1,2).
  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  //! Root is the value of the function at the solution.
  //! It is a vector of dimension 1, i-e a real.
  double Root() const;

  //! Returns the value Tol so that if std::abs(Func.Root())<Tol
  //! the function is considered null.
  double Tolerance() const;

  //! Returns the value of the solution point on the surface.
  const gp_Pnt& Point() const;

  Standard_EXPORT bool IsTangent();

  const gp_Vec& Direction3d();

  const gp_Dir2d& Direction2d();

  Contap_TFunction FunctionType() const;

  const gp_Pnt& Eye() const;

  const gp_Dir& Direction() const;

  double Angle() const;

  const occ::handle<Adaptor3d_Surface>& Surface() const;

  //! Method is entered for compatibility with IntPatch_TheSurfFunction.
  const occ::handle<Adaptor3d_Surface>& PSurface() const { return Surface(); }

private:
  occ::handle<Adaptor3d_Surface> mySurf;
  double                         myMean;
  Contap_TFunction               myType;
  gp_Dir                         myDir;
  gp_Pnt                         myEye;
  double                         myAng;
  double                         myCosAng;
  double                         tol;
  gp_Pnt                         solpt;
  double                         valf;
  double                         Usol;
  double                         Vsol;
  double                         Fpu;
  double                         Fpv;
  gp_Dir2d                       d2d;
  gp_Vec                         d3d;
  bool                           tangent;
  bool                           computed;
  bool                           derived;
};
// Created on: 1993-06-03
// Created by: Jacques GOUSSARD
// Copyright (c) 1993-1999 Matra Datavision
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

#include <StdFail_UndefinedDerivative.hpp>

inline void Contap_SurfFunction::Set(const gp_Pnt& Eye)
{
  myType = Contap_ContourPrs; // pers
  myEye  = Eye;
  myAng  = 0.;
}

inline void Contap_SurfFunction::Set(const gp_Dir& Direction)
{
  myType = Contap_ContourStd; // Contour app
  myDir  = Direction;
  myAng  = 0.;
}

inline void Contap_SurfFunction::Set(const gp_Dir& Direction, const double Angle)
{
  myType   = Contap_DraftStd; // Contour vu
  myDir    = Direction;
  myAng    = Angle;
  myCosAng = std::cos(M_PI / 2. + Angle);
}

inline void Contap_SurfFunction::Set(const gp_Pnt& Eye, const double Angle)
{
  myType   = Contap_DraftPrs; // Contour vu "conique"...
  myEye    = Eye;
  myAng    = Angle;
  myCosAng = std::cos(M_PI / 2. + Angle);
}

inline void Contap_SurfFunction::Set(const double Tolerance)
{
  tol = std::max(Tolerance, 1.e-12);
}

inline const gp_Pnt& Contap_SurfFunction::Point() const
{
  return solpt;
}

inline double Contap_SurfFunction::Root() const
{
  return valf;
}

inline double Contap_SurfFunction::Tolerance() const
{
  return tol;
}

inline const gp_Vec& Contap_SurfFunction::Direction3d()
{
  if (IsTangent())
    throw StdFail_UndefinedDerivative();
  return d3d;
}

inline const gp_Dir2d& Contap_SurfFunction::Direction2d()
{
  if (IsTangent())
    throw StdFail_UndefinedDerivative();
  return d2d;
}

inline const occ::handle<Adaptor3d_Surface>& Contap_SurfFunction::Surface() const
{
  return mySurf;
}

inline const gp_Pnt& Contap_SurfFunction::Eye() const
{
  return myEye;
}

inline const gp_Dir& Contap_SurfFunction::Direction() const
{
  return myDir;
}

inline double Contap_SurfFunction::Angle() const
{
  return myAng;
}

inline Contap_TFunction Contap_SurfFunction::FunctionType() const
{
  return myType;
}


