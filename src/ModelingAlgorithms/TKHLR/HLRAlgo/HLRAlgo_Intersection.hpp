// Created on: 1992-08-21
// Created by: Christophe MARION
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

#ifndef _HLRAlgo_Intersection_HeaderFile
#define _HLRAlgo_Intersection_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_Orientation.hpp>
#include <Standard_ShortReal.hpp>
#include <TopAbs_State.hpp>

//! Describes an intersection on an edge to hide.
//! Contains a parameter and a state (ON = on the
//! face, OUT = above the face, IN = under the Face)
class HLRAlgo_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAlgo_Intersection();

  Standard_EXPORT HLRAlgo_Intersection(const TopAbs_Orientation Ori,
                                       const int                Lev,
                                       const int                SegInd,
                                       const int                Ind,
                                       const double             P,
                                       const float              Tol,
                                       const TopAbs_State       S);

  void Orientation(const TopAbs_Orientation Ori);

  TopAbs_Orientation Orientation() const;

  void Level(const int Lev);

  int Level() const;

  void SegIndex(const int SegInd);

  int SegIndex() const;

  void Index(const int Ind);

  int Index() const;

  void Parameter(const double P);

  double Parameter() const;

  void Tolerance(const float T);

  float Tolerance() const;

  void State(const TopAbs_State S);

  TopAbs_State State() const;

private:
  TopAbs_Orientation myOrien;
  int                mySegIndex;
  int                myIndex;
  int                myLevel;
  double             myParam;
  float              myToler;
  TopAbs_State       myState;
};
// Created on: 1992-02-19
// Created by: Christophe MARION
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

//=================================================================================================

inline void HLRAlgo_Intersection::Orientation(const TopAbs_Orientation Ori)
{
  myOrien = Ori;
}

//=================================================================================================

inline TopAbs_Orientation HLRAlgo_Intersection::Orientation() const
{
  return myOrien;
}

//=================================================================================================

inline void HLRAlgo_Intersection::Level(const int Lev)
{
  myLevel = Lev;
}

//=================================================================================================

inline int HLRAlgo_Intersection::Level() const
{
  return myLevel;
}

//=================================================================================================

inline void HLRAlgo_Intersection::SegIndex(const int SegInd)
{
  mySegIndex = SegInd;
}

//=================================================================================================

inline int HLRAlgo_Intersection::SegIndex() const
{
  return mySegIndex;
}

//=================================================================================================

inline void HLRAlgo_Intersection::Index(const int Ind)
{
  myIndex = Ind;
}

//=================================================================================================

inline int HLRAlgo_Intersection::Index() const
{
  return myIndex;
}

//=================================================================================================

inline void HLRAlgo_Intersection::Parameter(const double P)
{
  myParam = P;
}

//=================================================================================================

inline double HLRAlgo_Intersection::Parameter() const
{
  return myParam;
}

//=================================================================================================

inline void HLRAlgo_Intersection::Tolerance(const float T)
{
  myToler = T;
}

//=================================================================================================

inline float HLRAlgo_Intersection::Tolerance() const
{
  return myToler;
}

//=================================================================================================

inline void HLRAlgo_Intersection::State(const TopAbs_State St)
{
  myState = St;
}

//=================================================================================================

inline TopAbs_State HLRAlgo_Intersection::State() const
{
  return myState;
}


#endif // _HLRAlgo_Intersection_HeaderFile
