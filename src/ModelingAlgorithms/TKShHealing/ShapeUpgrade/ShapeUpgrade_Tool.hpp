// Created on: 1999-08-31
// Created by: Pavel DURANDIN
// Copyright (c) 1999 Matra Datavision
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

#ifndef _ShapeUpgrade_Tool_HeaderFile
#define _ShapeUpgrade_Tool_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class ShapeBuild_ReShape;

//! Tool is a root class for splitting classes
//! Provides context for recording changes, basic
//! precision value and limit (minimal and maximal)
//! values for tolerances
class ShapeUpgrade_Tool : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT ShapeUpgrade_Tool();

  //! Copy all fields from another Root object
  Standard_EXPORT void Set(const occ::handle<ShapeUpgrade_Tool>& tool);

  //! Sets context
  void SetContext(const occ::handle<ShapeBuild_ReShape>& context);

  //! Returns context
  occ::handle<ShapeBuild_ReShape> Context() const;

  //! Sets basic precision value
  void SetPrecision(const double preci);

  //! Returns basic precision value
  double Precision() const;

  //! Sets minimal allowed tolerance
  void SetMinTolerance(const double mintol);

  //! Returns minimal allowed tolerance
  double MinTolerance() const;

  //! Sets maximal allowed tolerance
  void SetMaxTolerance(const double maxtol);

  //! Returns maximal allowed tolerance
  double MaxTolerance() const;

  //! Returns tolerance limited by [myMinTol,myMaxTol]
  double LimitTolerance(const double toler) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_Tool, Standard_Transient)

private:
  occ::handle<ShapeBuild_ReShape> myContext;
  double                          myPrecision;
  double                          myMinTol;
  double                          myMaxTol;
};
// Created on: 1999-08-31
// Created by: Pavel DURANDIN
// Copyright (c) 1999-1999 Matra Datavision
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

inline void ShapeUpgrade_Tool::SetContext(const occ::handle<ShapeBuild_ReShape>& context)
{
  myContext = context;
}

//=================================================================================================

inline occ::handle<ShapeBuild_ReShape> ShapeUpgrade_Tool::Context() const
{
  return myContext;
}

//=================================================================================================

inline void ShapeUpgrade_Tool::SetPrecision(const double preci)
{
  myPrecision = preci;
  if (myMaxTol < myPrecision)
    myMaxTol = myPrecision;
  if (myMinTol > myPrecision)
    myMinTol = myPrecision;
}

//=================================================================================================

inline double ShapeUpgrade_Tool::Precision() const
{
  return myPrecision;
}

//=================================================================================================

inline void ShapeUpgrade_Tool::SetMinTolerance(const double mintol)
{
  myMinTol = mintol;
}

//=================================================================================================

inline double ShapeUpgrade_Tool::MinTolerance() const
{
  return myMinTol;
}

//=================================================================================================

inline void ShapeUpgrade_Tool::SetMaxTolerance(const double maxtol)
{
  myMaxTol = maxtol;
}

//=================================================================================================

inline double ShapeUpgrade_Tool::MaxTolerance() const
{
  return myMaxTol;
}

//=================================================================================================

inline double ShapeUpgrade_Tool::LimitTolerance(const double toler) const
{
  // only maximal restriction implemented.
  return std::min(myMaxTol, toler);
}


#endif // _ShapeUpgrade_Tool_HeaderFile
