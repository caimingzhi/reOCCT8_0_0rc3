// Created on: 1993-06-17
// Created by: Jean Yves LEBEY
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

#ifndef _TopOpeBRepDS_CurveIterator_HeaderFile
#define _TopOpeBRepDS_CurveIterator_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_InterferenceIterator.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepDS_Interference;
class Geom2d_Curve;

class TopOpeBRepDS_CurveIterator : public TopOpeBRepDS_InterferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an iterator on the curves on surface
  //! described by the interferences in <L>.
  Standard_EXPORT TopOpeBRepDS_CurveIterator(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  //! Returns True if the Interference <I> has a
  //! GeometryType() TopOpeBRepDS_CURVE
  //! returns False else.
  Standard_EXPORT bool MatchInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I) const override;

  //! Index of the curve in the data structure.
  Standard_EXPORT int Current() const;

  Standard_EXPORT TopAbs_Orientation Orientation(const TopAbs_State S) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve() const;
};

#endif // _TopOpeBRepDS_CurveIterator_HeaderFile
