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

#ifndef _IntTools_SurfaceRangeLocalizeData_HeaderFile
#define _IntTools_SurfaceRangeLocalizeData_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <IntTools_SurfaceRangeSample.hpp>
#include <NCollection_Map.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_List.hpp>
class IntTools_SurfaceRangeSample;
class Bnd_Box;
class gp_Pnt;

class IntTools_SurfaceRangeLocalizeData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData();

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData(const int    theNbSampleU,
                                                    const int    theNbSampleV,
                                                    const double theMinRangeU,
                                                    const double theMinRangeV);

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData(const IntTools_SurfaceRangeLocalizeData& Other);

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData& Assign(
    const IntTools_SurfaceRangeLocalizeData& Other);

  IntTools_SurfaceRangeLocalizeData& operator=(const IntTools_SurfaceRangeLocalizeData& Other)
  {
    return Assign(Other);
  }

  int GetNbSampleU() const;

  int GetNbSampleV() const;

  double GetMinRangeU() const;

  double GetMinRangeV() const;

  Standard_EXPORT void AddOutRange(const IntTools_SurfaceRangeSample& theRange);

  Standard_EXPORT void AddBox(const IntTools_SurfaceRangeSample& theRange, const Bnd_Box& theBox);

  Standard_EXPORT bool FindBox(const IntTools_SurfaceRangeSample& theRange, Bnd_Box& theBox) const;

  Standard_EXPORT bool IsRangeOut(const IntTools_SurfaceRangeSample& theRange) const;

  Standard_EXPORT void ListRangeOut(NCollection_List<IntTools_SurfaceRangeSample>& theList) const;

  Standard_EXPORT void RemoveRangeOutAll();

  //! Set the grid deflection.
  void SetGridDeflection(const double theDeflection);

  //! Query the grid deflection.
  double GetGridDeflection() const;

  //! Set the range U of the grid of points.
  Standard_EXPORT void SetRangeUGrid(const int theNbUGrid);

  //! Query the range U of the grid of points.
  int GetRangeUGrid() const;

  //! Set the U parameter of the grid points at that index.
  void SetUParam(const int theIndex, const double theUParam);

  //! Query the U parameter of the grid points at that index.
  double GetUParam(const int theIndex) const;

  //! Set the range V of the grid of points.
  Standard_EXPORT void SetRangeVGrid(const int theNbVGrid);

  //! Query the range V of the grid of points.
  int GetRangeVGrid() const;

  //! Set the V parameter of the grid points at that index.
  void SetVParam(const int theIndex, const double theVParam);

  //! Query the V parameter of the grid points at that index.
  double GetVParam(const int theIndex) const;

  //! Set the grid point.
  void SetGridPoint(const int theUIndex, const int theVIndex, const gp_Pnt& thePoint);

  //! Set the grid point.
  const gp_Pnt& GetGridPoint(const int theUIndex, const int theVIndex) const;

  //! Sets the frame area. Used to work with grid points.
  Standard_EXPORT void SetFrame(const double theUMin,
                                const double theUMax,
                                const double theVMin,
                                const double theVMax);

  //! Returns the number of grid points on U direction in frame.
  int GetNBUPointsInFrame() const;

  //! Returns the number of grid points on V direction in frame.
  int GetNBVPointsInFrame() const;

  //! Returns the grid point in frame.
  Standard_EXPORT const gp_Pnt& GetPointInFrame(const int theUIndex, const int theVIndex) const;

  //! Query the U parameter of the grid points
  //! at that index in frame.
  Standard_EXPORT double GetUParamInFrame(const int theIndex) const;

  //! Query the V parameter of the grid points
  //! at that index in frame.
  Standard_EXPORT double GetVParamInFrame(const int theIndex) const;

  //! Clears the grid of points.
  Standard_EXPORT void ClearGrid();

private:
  int                                                       myNbSampleU;
  int                                                       myNbSampleV;
  double                                                    myMinRangeU;
  double                                                    myMinRangeV;
  NCollection_Map<IntTools_SurfaceRangeSample>              myMapRangeOut;
  NCollection_DataMap<IntTools_SurfaceRangeSample, Bnd_Box> myMapBox;
  occ::handle<NCollection_HArray1<double>>                  myUParams;
  occ::handle<NCollection_HArray1<double>>                  myVParams;
  occ::handle<NCollection_HArray2<gp_Pnt>>                  myGridPoints;
  int                                                       myUIndMin;
  int                                                       myUIndMax;
  int                                                       myVIndMin;
  int                                                       myVIndMax;
  double                                                    myDeflection;
};
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

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

inline int IntTools_SurfaceRangeLocalizeData::GetNbSampleU() const
{
  return myNbSampleU;
}

inline int IntTools_SurfaceRangeLocalizeData::GetNbSampleV() const
{
  return myNbSampleV;
}

inline double IntTools_SurfaceRangeLocalizeData::GetMinRangeU() const
{
  return myMinRangeU;
}

inline double IntTools_SurfaceRangeLocalizeData::GetMinRangeV() const
{
  return myMinRangeV;
}

//  Modified by skv - Thu Nov  3 09:59:43 2005 Optimization Begin
inline void IntTools_SurfaceRangeLocalizeData::SetGridDeflection(const double theDeflection)
{
  myDeflection = theDeflection;
}

inline double IntTools_SurfaceRangeLocalizeData::GetGridDeflection() const
{
  return myDeflection;
}

inline int IntTools_SurfaceRangeLocalizeData::GetRangeUGrid() const
{
  return (myUParams.IsNull()) ? 0 : myUParams->Length();
}

inline void IntTools_SurfaceRangeLocalizeData::SetUParam(const int theIndex, const double theUParam)
{
  myUParams->SetValue(theIndex, theUParam);
}

inline double IntTools_SurfaceRangeLocalizeData::GetUParam(const int theIndex) const
{
  return myUParams->Value(theIndex);
}

inline int IntTools_SurfaceRangeLocalizeData::GetRangeVGrid() const
{
  return (myVParams.IsNull()) ? 0 : myVParams->Length();
}

inline void IntTools_SurfaceRangeLocalizeData::SetVParam(const int theIndex, const double theVParam)
{
  myVParams->SetValue(theIndex, theVParam);
}

inline double IntTools_SurfaceRangeLocalizeData::GetVParam(const int theIndex) const
{
  return myVParams->Value(theIndex);
}

inline void IntTools_SurfaceRangeLocalizeData::SetGridPoint(const int     theUIndex,
                                                            const int     theVIndex,
                                                            const gp_Pnt& thePoint)
{
  myGridPoints->SetValue(theUIndex, theVIndex, thePoint);
}

inline const gp_Pnt& IntTools_SurfaceRangeLocalizeData::GetGridPoint(const int theUIndex,
                                                                     const int theVIndex) const
{
  return myGridPoints->Value(theUIndex, theVIndex);
}

inline int IntTools_SurfaceRangeLocalizeData::GetNBUPointsInFrame() const
{
  return myUIndMax - myUIndMin + 1;
}

inline int IntTools_SurfaceRangeLocalizeData::GetNBVPointsInFrame() const
{
  return myVIndMax - myVIndMin + 1;
}

//  Modified by skv - Thu Nov  3 09:59:43 2005 Optimization End


#endif // _IntTools_SurfaceRangeLocalizeData_HeaderFile
