#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntRes2d_IntersectionPoint.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopOpeBRepDS_Transition.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRep_P2Dstatus.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <TopOpeBRepDS_Config.hpp>
class TopOpeBRep_Hctxff2d;
class TopOpeBRep_Hctxee2d;

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

class TopOpeBRep_Point2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_Point2d();

  Standard_EXPORT void Dump(const int ie1 = 0, const int ie2 = 0) const;

  void SetPint(const IntRes2d_IntersectionPoint& P);

  bool HasPint() const;

  const IntRes2d_IntersectionPoint& Pint() const;

  void SetIsVertex(const int I, const bool B);

  bool IsVertex(const int I) const;

  void SetVertex(const int I, const TopoDS_Vertex& V);

  Standard_EXPORT const TopoDS_Vertex& Vertex(const int I) const;

  void SetTransition(const int I, const TopOpeBRepDS_Transition& T);

  Standard_EXPORT const TopOpeBRepDS_Transition& Transition(const int I) const;

  Standard_EXPORT TopOpeBRepDS_Transition& ChangeTransition(const int I);

  void SetParameter(const int I, const double P);

  double Parameter(const int I) const;

  void SetIsPointOfSegment(const bool B);

  bool IsPointOfSegment() const;

  void SetSegmentAncestors(const int IP1, const int IP2);

  bool SegmentAncestors(int& IP1, int& IP2) const;

  void SetStatus(const TopOpeBRep_P2Dstatus S);

  TopOpeBRep_P2Dstatus Status() const;

  void SetIndex(const int X);

  int Index() const;

  void SetValue(const gp_Pnt& P);

  const gp_Pnt& Value() const;

  void SetValue2d(const gp_Pnt2d& P);

  const gp_Pnt2d& Value2d() const;

  void SetKeep(const bool B);

  bool Keep() const;

  void SetEdgesConfig(const TopOpeBRepDS_Config C);

  TopOpeBRepDS_Config EdgesConfig() const;

  void SetTolerance(const double T);

  double Tolerance() const;

  void SetHctxff2d(const occ::handle<TopOpeBRep_Hctxff2d>& ff2d);

  occ::handle<TopOpeBRep_Hctxff2d> Hctxff2d() const;

  void SetHctxee2d(const occ::handle<TopOpeBRep_Hctxee2d>& ee2d);

  occ::handle<TopOpeBRep_Hctxee2d> Hctxee2d() const;

  friend class TopOpeBRep_EdgesIntersector;

private:
  IntRes2d_IntersectionPoint       mypint;
  bool                             myhaspint;
  bool                             myisvertex1;
  TopoDS_Vertex                    myvertex1;
  TopOpeBRepDS_Transition          mytransition1;
  double                           myparameter1;
  bool                             myisvertex2;
  TopoDS_Vertex                    myvertex2;
  TopOpeBRepDS_Transition          mytransition2;
  double                           myparameter2;
  bool                             myispointofsegment;
  int                              myips1;
  int                              myips2;
  bool                             myhasancestors;
  TopOpeBRep_P2Dstatus             mystatus;
  int                              myindex;
  gp_Pnt                           mypnt;
  gp_Pnt2d                         mypnt2d;
  bool                             mykeep;
  TopOpeBRepDS_Config              myedgesconfig;
  double                           mytolerance;
  occ::handle<TopOpeBRep_Hctxff2d> myctxff2d;
  occ::handle<TopOpeBRep_Hctxee2d> myctxee2d;
};
// Created on: 1998-10-29
// Created by: Jean Yves LEBEY
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

#include <TopOpeBRep_define.hpp>

//=================================================================================================

inline void TopOpeBRep_Point2d::SetPint(const IntRes2d_IntersectionPoint& P)
{
  mypint    = P;
  myhaspint = true;
}

//=================================================================================================

inline bool TopOpeBRep_Point2d::HasPint() const
{
  return myhaspint;
}

//=================================================================================================

inline const IntRes2d_IntersectionPoint& TopOpeBRep_Point2d::Pint() const
{
  if (!HasPint())
    throw Standard_Failure("TopOpeBRep_Point2d::Pint");
  return mypint;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetIsVertex(const int Index, const bool B)
{
  if (Index == 1)
    myisvertex1 = B;
  else if (Index == 2)
    myisvertex2 = B;
  else
    throw Standard_Failure("TopOpeBRep_Point2d::SetIsVertex");
}

//=================================================================================================

inline bool TopOpeBRep_Point2d::IsVertex(const int Index) const
{
  if (Index == 1)
    return myisvertex1;
  else if (Index == 2)
    return myisvertex2;
  else
    throw Standard_Failure("TopOpeBRep_Point2d::IsVertex");
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetVertex(const int Index, const TopoDS_Vertex& V)
{
  if (Index == 1)
  {
    myvertex1   = V;
    myisvertex1 = true;
  }
  else if (Index == 2)
  {
    myvertex2   = V;
    myisvertex2 = true;
  }
  else
    throw Standard_Failure("TopOpeBRep_Point2d::SetVertex");
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetTransition(const int Index, const TopOpeBRepDS_Transition& T)
{
  if (Index == 1)
    mytransition1 = T;
  else if (Index == 2)
    mytransition2 = T;
  else
    throw Standard_Failure("TopOpeBRep_Point2d::SetTransition");
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetParameter(const int Index, const double P)
{
  if (Index == 1)
    myparameter1 = P;
  else if (Index == 2)
    myparameter2 = P;
  else
    throw Standard_Failure("TopOpeBRep_Point2d::SetParameter");
}

//=================================================================================================

inline double TopOpeBRep_Point2d::Parameter(const int Index) const
{
  if (Index == 1)
    return myparameter1;
  else if (Index == 2)
    return myparameter2;
  else
    throw Standard_Failure("TopOpeBRep_Point2d::Parameter");
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetIsPointOfSegment(const bool B)
{
  myispointofsegment = B;
}

//=================================================================================================

inline bool TopOpeBRep_Point2d::IsPointOfSegment() const
{
  return myispointofsegment;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetSegmentAncestors(const int IP1, const int IP2)
{
  myips1         = IP1;
  myips2         = IP2;
  myhasancestors = (myips1 != 0 && myips2 != 0);
  if (myhasancestors)
    mystatus = TopOpeBRep_P2DNEW;
}

//=================================================================================================

inline bool TopOpeBRep_Point2d::SegmentAncestors(int& IP1, int& IP2) const
{
  IP1 = myips1;
  IP2 = myips2;
  return myhasancestors;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetStatus(const TopOpeBRep_P2Dstatus I)
{
  mystatus = I;
}

//=================================================================================================

inline TopOpeBRep_P2Dstatus TopOpeBRep_Point2d::Status() const
{
  return mystatus;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetIndex(const int I)
{
  myindex = I;
}

//=================================================================================================

inline int TopOpeBRep_Point2d::Index() const
{
  return myindex;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetValue(const gp_Pnt& P)
{
  mypnt = P;
}

//=================================================================================================

inline const gp_Pnt& TopOpeBRep_Point2d::Value() const
{
  return mypnt;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetValue2d(const gp_Pnt2d& P)
{
  mypnt2d = P;
}

//=================================================================================================

inline const gp_Pnt2d& TopOpeBRep_Point2d::Value2d() const
{
  return mypnt2d;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetKeep(const bool B)
{
  mykeep = B;
}

//=================================================================================================

inline bool TopOpeBRep_Point2d::Keep() const
{
  return mykeep;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetEdgesConfig(const TopOpeBRepDS_Config B)
{
  myedgesconfig = B;
}

//=================================================================================================

inline TopOpeBRepDS_Config TopOpeBRep_Point2d::EdgesConfig() const
{
  return myedgesconfig;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetTolerance(const double t)
{
  mytolerance = t;
}

//=================================================================================================

inline double TopOpeBRep_Point2d::Tolerance() const
{
  return mytolerance;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetHctxff2d(const occ::handle<TopOpeBRep_Hctxff2d>& h)
{
  myctxff2d = h;
}

//=================================================================================================

inline occ::handle<TopOpeBRep_Hctxff2d> TopOpeBRep_Point2d::Hctxff2d() const
{
  return myctxff2d;
}

//=================================================================================================

inline void TopOpeBRep_Point2d::SetHctxee2d(const occ::handle<TopOpeBRep_Hctxee2d>& h)
{
  myctxee2d = h;
}

//=================================================================================================

inline occ::handle<TopOpeBRep_Hctxee2d> TopOpeBRep_Point2d::Hctxee2d() const
{
  return myctxee2d;
}


