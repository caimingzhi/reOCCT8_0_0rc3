#pragma once


#include <Standard.hpp>

#include <TopoDS_Wire.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

//! This class is intended to represent free bound and to store
//! its properties.
//!
//! This class is used by ShapeAnalysis_FreeBoundsProperties
//! class when storing each free bound and its properties.
//!
//! The properties stored in this class are the following:
//! - area of the contour,
//! - perimeter of the contour,
//! - ratio of average length to average width of the contour,
//! - average width of contour,
//! - notches (narrow 'V'-like sub-contours) on the contour and
//! their maximum width.
//!
//! This class provides methods for setting and getting fields
//! only.
class ShapeAnalysis_FreeBoundData : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT ShapeAnalysis_FreeBoundData();

  //! Creates object with contour given in the form of TopoDS_Wire
  Standard_EXPORT ShapeAnalysis_FreeBoundData(const TopoDS_Wire& freebound);

  //! Clears all properties of the contour.
  //! Contour bound itself is not cleared.
  Standard_EXPORT void Clear();

  //! Sets contour
  void SetFreeBound(const TopoDS_Wire& freebound);

  //! Sets area of the contour
  void SetArea(const double area);

  //! Sets perimeter of the contour
  void SetPerimeter(const double perimeter);

  //! Sets ratio of average length to average width of the contour
  void SetRatio(const double ratio);

  //! Sets average width of the contour
  void SetWidth(const double width);

  //! Adds notch on the contour with its maximum width
  Standard_EXPORT void AddNotch(const TopoDS_Wire& notch, const double width);

  //! Returns contour
  TopoDS_Wire FreeBound() const;

  //! Returns area of the contour
  double Area() const;

  //! Returns perimeter of the contour
  double Perimeter() const;

  //! Returns ratio of average length to average width of the contour
  double Ratio() const;

  //! Returns average width of the contour
  double Width() const;

  //! Returns number of notches on the contour
  int NbNotches() const;

  //! Returns sequence of notches on the contour
  occ::handle<NCollection_HSequence<TopoDS_Shape>> Notches() const;

  //! Returns notch on the contour
  TopoDS_Wire Notch(const int index) const;

  //! Returns maximum width of notch specified by its rank number
  //! on the contour
  Standard_EXPORT double NotchWidth(const int index) const;

  //! Returns maximum width of notch specified as TopoDS_Wire
  //! on the contour
  Standard_EXPORT double NotchWidth(const TopoDS_Wire& notch) const;

  DEFINE_STANDARD_RTTIEXT(ShapeAnalysis_FreeBoundData, Standard_Transient)

private:
  TopoDS_Wire                                                        myBound;
  double                                                             myArea;
  double                                                             myPerimeter;
  double                                                             myRatio;
  double                                                             myWidth;
  occ::handle<NCollection_HSequence<TopoDS_Shape>>                   myNotches;
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> myNotchesParams;
};
// Created on: 1998-09-17
// Created by: data exchange team
// Copyright (c) 1998-1999 Matra Datavision
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

#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

//=================================================================================================

inline void ShapeAnalysis_FreeBoundData::SetFreeBound(const TopoDS_Wire& freebound)
{
  myBound = freebound;
}

//=======================================================================
// function : SetArea
// purpose  : Sets area of the contour
//=======================================================================

inline void ShapeAnalysis_FreeBoundData::SetArea(const double area)
{
  myArea = area;
}

//=======================================================================
// function : SetPerimeter
// purpose  : Sets perimeter of the contour
//=======================================================================

inline void ShapeAnalysis_FreeBoundData::SetPerimeter(const double perimeter)
{
  myPerimeter = perimeter;
}

//=======================================================================
// function : SetRatio
// purpose  : Sets ratio of average length to average width of the contour
//=======================================================================

inline void ShapeAnalysis_FreeBoundData::SetRatio(const double ratio)
{
  myRatio = ratio;
}

//=======================================================================
// function : SetWidth
// purpose  : Sets average width of the contour
//=======================================================================

inline void ShapeAnalysis_FreeBoundData::SetWidth(const double width)
{
  myWidth = width;
}

//=======================================================================
// function : AddNotch
// purpose  : Adds notch on free bound with its maximum width
//=======================================================================

//=================================================================================================

inline TopoDS_Wire ShapeAnalysis_FreeBoundData::FreeBound() const
{
  return myBound;
}

//=======================================================================
// function : Area
// purpose  : Returns area of the contour
//=======================================================================

inline double ShapeAnalysis_FreeBoundData::Area() const
{
  return myArea;
}

//=======================================================================
// function : Perimeter
// purpose  : Returns perimeter of the contour
//=======================================================================

inline double ShapeAnalysis_FreeBoundData::Perimeter() const
{
  return myPerimeter;
}

//=======================================================================
// function : Ratio
// purpose  : Returns ratio of average length to average width of the contour
//=======================================================================

inline double ShapeAnalysis_FreeBoundData::Ratio() const
{
  return myRatio;
}

//=======================================================================
// function : Width
// purpose  : Returns average width of the contour
//=======================================================================

inline double ShapeAnalysis_FreeBoundData::Width() const
{
  return myWidth;
}

//=======================================================================
// function : NbNotches
// purpose  : Returns number of notches on the contour
//=======================================================================

inline int ShapeAnalysis_FreeBoundData::NbNotches() const
{
  return myNotches->Length();
}

//=======================================================================
// function : Notches
// purpose  : Returns sequence of notches on the contour
//=======================================================================

inline occ::handle<NCollection_HSequence<TopoDS_Shape>> ShapeAnalysis_FreeBoundData::Notches() const
{
  return myNotches;
}

//=======================================================================
// function : Notch
// purpose  : Returns notch on the contour
//=======================================================================

inline TopoDS_Wire ShapeAnalysis_FreeBoundData::Notch(const int index) const
{
  return TopoDS::Wire(myNotches->Value(index));
}


