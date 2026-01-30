// Created on: 2005-10-14
// Created by: Mikhail KLOKOV
// Copyright (c) 2005-2014 OPEN CASCADE SAS
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

#ifndef _IntTools_CurveRangeLocalizeData_HeaderFile
#define _IntTools_CurveRangeLocalizeData_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <IntTools_CurveRangeSample.hpp>
#include <NCollection_Map.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>

class IntTools_CurveRangeSample;
class Bnd_Box;

class IntTools_CurveRangeLocalizeData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_CurveRangeLocalizeData(const int theNbSample, const double theMinRange);

  int GetNbSample() const { return myNbSampleC; }

  double GetMinRange() const { return myMinRangeC; }

  Standard_EXPORT void AddOutRange(const IntTools_CurveRangeSample& theRange);

  Standard_EXPORT void AddBox(const IntTools_CurveRangeSample& theRange, const Bnd_Box& theBox);

  Standard_EXPORT bool FindBox(const IntTools_CurveRangeSample& theRange, Bnd_Box& theBox) const;

  Standard_EXPORT bool IsRangeOut(const IntTools_CurveRangeSample& theRange) const;

  Standard_EXPORT void ListRangeOut(NCollection_List<IntTools_CurveRangeSample>& theList) const;

private:
  int                                                     myNbSampleC;
  double                                                  myMinRangeC;
  NCollection_Map<IntTools_CurveRangeSample>              myMapRangeOut;
  NCollection_DataMap<IntTools_CurveRangeSample, Bnd_Box> myMapBox;
};

#endif // _IntTools_CurveRangeLocalizeData_HeaderFile
