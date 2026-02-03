// Created on: 1996-08-30
// Created by: Xavier BENVENISTE
// Copyright (c) 1996-1999 Matra Datavision
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

#ifndef _GeomLib_Interpolate_HeaderFile
#define _GeomLib_Interpolate_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created on: 1993-07-07
// Created by: Jean Claude VAUTHIER
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

#ifndef _GeomLib_InterpolationErrors_HeaderFile
#define _GeomLib_InterpolationErrors_HeaderFile

//! in case the interpolation errors out, this
//! tells what happened
enum GeomLib_InterpolationErrors
{
  GeomLib_NoError,
  GeomLib_NotEnoughtPoints,
  GeomLib_DegreeSmallerThan3,
  GeomLib_InversionProblem
};

#endif // _GeomLib_InterpolationErrors_HeaderFile

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
class Geom_BSplineCurve;

//! This class is used to construct a BSpline curve by
//! interpolation of points at given parameters. The
//! continuity of the curve is degree - 1 and the
//! method used when boundary conditions are not given
//! is to use odd degrees and null the derivatives on
//! both sides from degree -1 down to (degree+1) / 2
//! When even degree is given the returned curve is of
//! degree - 1 so that the degree of the curve is odd
class GeomLib_Interpolate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_Interpolate(const int                         Degree,
                                      const int                         NumPoints,
                                      const NCollection_Array1<gp_Pnt>& Points,
                                      const NCollection_Array1<double>& Parameters);

  //! returns if everything went OK
  bool IsDone() const;

  //! returns the error type if any
  GeomLib_InterpolationErrors Error() const;

  //! returns the interpolated curve of the requested degree
  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve() const;

private:
  occ::handle<Geom_BSplineCurve> myCurve;
  bool                           myIsDone;
  GeomLib_InterpolationErrors    myError;
};
// Created on: 1996-09-02
// Created by: Xavier BENVENISTE
// Copyright (c) 1996-1999 Matra Datavision
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

//=================================================================================================

inline bool GeomLib_Interpolate::IsDone() const
{
  return myIsDone;
}

//=================================================================================================

inline GeomLib_InterpolationErrors GeomLib_Interpolate::Error() const
{
  return myError;
}


#endif // _GeomLib_Interpolate_HeaderFile
