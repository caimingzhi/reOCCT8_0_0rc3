// Created on: 1991-02-20
// Created by: Jacques GOUSSARD
// Copyright (c) 1991-1999 Matra Datavision
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

#ifndef _IntAna2d_IntPoint_HeaderFile
#define _IntAna2d_IntPoint_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <Standard_Boolean.hpp>

//! Geometrical intersection between two 2d elements.
class IntAna2d_IntPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create an intersection point between 2 parametric 2d lines.
  //! X,Y are the coordinate of the point. U1 is the parameter
  //! on the first element, U2 the parameter on the second one.
  Standard_EXPORT IntAna2d_IntPoint(const double X,
                                    const double Y,
                                    const double U1,
                                    const double U2);

  //! Create an intersection point between a parametric 2d line,
  //! and a line given by an implicit equation (ImplicitCurve).
  //! X,Y are the coordinate of the point. U1 is the parameter
  //! on the parametric element.
  //! Empty constructor. It's necessary to use one of
  //! the SetValue method after this one.
  Standard_EXPORT IntAna2d_IntPoint(const double X, const double Y, const double U1);

  Standard_EXPORT IntAna2d_IntPoint();

  //! Set the values for a "non-implicit" point.
  Standard_EXPORT virtual void SetValue(const double X,
                                        const double Y,
                                        const double U1,
                                        const double U2);

  //! Set the values for an "implicit" point.
  Standard_EXPORT virtual void SetValue(const double X, const double Y, const double U1);

  //! Returns the geometric point.
  const gp_Pnt2d& Value() const;

  //! Returns True if the second curve is implicit.
  bool SecondIsImplicit() const;

  //! Returns the parameter on the first element.
  double ParamOnFirst() const;

  //! Returns the parameter on the second element.
  //! If the second element is an implicit curve, an exception
  //! is raised.
  double ParamOnSecond() const;

private:
  double   myu1;
  double   myu2;
  gp_Pnt2d myp;
  bool     myimplicit;
};
// Created on: 1992-10-07
// Created by: Laurent BUCHARD
// Copyright (c) 1992-1999 Matra Datavision
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

inline const gp_Pnt2d& IntAna2d_IntPoint::Value() const
{
  return myp;
}

inline double IntAna2d_IntPoint::ParamOnFirst() const
{
  return myu1;
}

inline double IntAna2d_IntPoint::ParamOnSecond() const
{

  if (myimplicit)
  {
    throw Standard_DomainError();
  }
  return myu2;
}

inline bool IntAna2d_IntPoint::SecondIsImplicit() const
{
  return (myimplicit);
}


#endif // _IntAna2d_IntPoint_HeaderFile
