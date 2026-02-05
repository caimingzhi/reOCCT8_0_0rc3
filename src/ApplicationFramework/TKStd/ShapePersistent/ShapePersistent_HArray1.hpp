#pragma once

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
