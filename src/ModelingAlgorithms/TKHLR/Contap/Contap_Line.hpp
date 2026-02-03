// Created on: 1993-02-05
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

#ifndef _Contap_Line_HeaderFile
#define _Contap_Line_HeaderFile
// Created on: 1993-02-05
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

#ifndef _Contap_IType_HeaderFile
#define _Contap_IType_HeaderFile

enum Contap_IType
{
  Contap_Lin,
  Contap_Circle,
  Contap_Walking,
  Contap_Restriction
};

#endif // _Contap_IType_HeaderFile

#include <Contap_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <IntSurf_TypeTrans.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>

class IntSurf_LineOn2S;
class IntSurf_PntOn2S;
class gp_Lin;
class gp_Circ;
class Contap_Point;

class Contap_Line
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_Line();

  Standard_EXPORT void SetLineOn2S(const occ::handle<IntSurf_LineOn2S>& L);

  Standard_EXPORT void Clear();

  const occ::handle<IntSurf_LineOn2S>& LineOn2S() const;

  Standard_EXPORT void ResetSeqOfVertex();

  void Add(const IntSurf_PntOn2S& P);

  Standard_EXPORT void SetValue(const gp_Lin& L);

  Standard_EXPORT void SetValue(const gp_Circ& C);

  Standard_EXPORT void SetValue(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT void Add(const Contap_Point& P);

  int NbVertex() const;

  Contap_Point& Vertex(const int Index) const;

  //! Returns Contap_Lin for a line, Contap_Circle for
  //! a circle, and Contap_Walking for a Walking line,
  //! Contap_Restriction for a part of boundary.
  Contap_IType TypeContour() const;

  int NbPnts() const;

  const IntSurf_PntOn2S& Point(const int Index) const;

  gp_Lin Line() const;

  gp_Circ Circle() const;

  Standard_EXPORT const occ::handle<Adaptor2d_Curve2d>& Arc() const;

  //! Set The Transition of the line.
  Standard_EXPORT void SetTransitionOnS(const IntSurf_TypeTrans T);

  //! returns IN if at the "left" of the line, the normale of the
  //! surface is oriented to the observator.
  Standard_EXPORT IntSurf_TypeTrans TransitionOnS() const;

private:
  IntSurf_TypeTrans                                Trans;
  occ::handle<IntSurf_LineOn2S>                    curv;
  occ::handle<NCollection_HSequence<Contap_Point>> svtx;
  occ::handle<Adaptor2d_Curve2d>                   thearc;
  Contap_IType                                     typL;
  gp_Pnt                                           pt;
  gp_Dir                                           dir1;
  gp_Dir                                           dir2;
  double                                           rad;
};
// Created on: 1993-02-05
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

#include <Standard_DomainError.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <IntSurf_LineOn2S.hpp>

#include <Contap_Point.hpp>

inline const occ::handle<IntSurf_LineOn2S>& Contap_Line::LineOn2S() const
{
  return curv;
}

inline void Contap_Line::Add(const IntSurf_PntOn2S& POn2S)
{
  curv->Add(POn2S);
}

inline int Contap_Line::NbVertex() const
{
  return svtx->Length();
}

inline Contap_Point& Contap_Line::Vertex(const int Index) const
{
  return svtx->ChangeSequence()(Index);
}

inline Contap_IType Contap_Line::TypeContour() const
{
  return typL;
}

inline int Contap_Line::NbPnts() const
{
  if (typL != Contap_Walking)
  {
    throw Standard_DomainError();
  }
  return (curv->NbPoints());
}

inline const IntSurf_PntOn2S& Contap_Line::Point(const int Index) const
{
  if (typL != Contap_Walking)
  {
    throw Standard_DomainError();
  }
  return (curv->Value(Index));
}

inline gp_Lin Contap_Line::Line() const
{
  if (typL != Contap_Lin)
  {
    throw Standard_DomainError();
  }
  return gp_Lin(pt, dir1);
}

inline gp_Circ Contap_Line::Circle() const
{
  if (typL != Contap_Circle)
  {
    throw Standard_DomainError();
  }
  return gp_Circ(gp_Ax2(pt, dir1, dir2), rad);
}


#endif // _Contap_Line_HeaderFile
