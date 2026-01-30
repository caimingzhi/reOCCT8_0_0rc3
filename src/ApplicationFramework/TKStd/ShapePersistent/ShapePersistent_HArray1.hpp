// Copyright (c) 2015 OPEN CASCADE SAS
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

#ifndef _ShapePersistent_HArray1_HeaderFile
#define _ShapePersistent_HArray1_HeaderFile

#include <StdLPersistent_HArray1.hpp>
#include <StdObject_gp_Vectors.hpp>
#include <StdObject_gp_Curves.hpp>

#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <gp_XY.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <Poly_Triangle.hpp>

class ShapePersistent_HArray1 : private StdLPersistent_HArray1
{
public:
  typedef instance<NCollection_HArray1<gp_XYZ>>        XYZ;
  typedef instance<NCollection_HArray1<gp_Pnt>>        Pnt;
  typedef instance<NCollection_HArray1<gp_Dir>>        Dir;
  typedef instance<NCollection_HArray1<gp_Vec>>        Vec;
  typedef instance<NCollection_HArray1<gp_XY>>         XY;
  typedef instance<NCollection_HArray1<gp_Pnt2d>>      Pnt2d;
  typedef instance<NCollection_HArray1<gp_Dir2d>>      Dir2d;
  typedef instance<NCollection_HArray1<gp_Vec2d>>      Vec2d;
  typedef instance<NCollection_HArray1<gp_Lin2d>>      Lin2d;
  typedef instance<NCollection_HArray1<gp_Circ2d>>     Circ2d;
  typedef instance<NCollection_HArray1<Poly_Triangle>> Triangle;
};

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, Poly_Triangle& theTriangle)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  int N1, N2, N3;
  theReadData >> N1 >> N2 >> N3;
  theTriangle.Set(N1, N2, N3);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData,
                                       const Poly_Triangle& theTriangle)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  int N1, N2, N3;
  theTriangle.Get(N1, N2, N3);
  theWriteData << N1 << N2 << N3;
  return theWriteData;
}

#endif
