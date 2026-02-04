#pragma once


#include <StdLPersistent_HArray2.hpp>
#include <StdObject_gp_Vectors.hpp>
#include <StdObject_gp_Curves.hpp>

#include <gp_XYZ.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <gp_XY.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>

class ShapePersistent_HArray2 : private StdLPersistent_HArray2
{
public:
  typedef instance<NCollection_HArray2<gp_XYZ>>    XYZ;
  typedef instance<NCollection_HArray2<gp_Pnt>>    Pnt;
  typedef instance<NCollection_HArray2<gp_Dir>>    Dir;
  typedef instance<NCollection_HArray2<gp_Vec>>    Vec;
  typedef instance<NCollection_HArray2<gp_XY>>     XY;
  typedef instance<NCollection_HArray2<gp_Pnt2d>>  Pnt2d;
  typedef instance<NCollection_HArray2<gp_Dir2d>>  Dir2d;
  typedef instance<NCollection_HArray2<gp_Vec2d>>  Vec2d;
  typedef instance<NCollection_HArray2<gp_Lin2d>>  Lin2d;
  typedef instance<NCollection_HArray2<gp_Circ2d>> Circ2d;
};

