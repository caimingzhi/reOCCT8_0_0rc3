#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

class Graphic3d_ArrayOfPoints : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfPoints, Graphic3d_ArrayOfPrimitives)
public:
  Graphic3d_ArrayOfPoints(int theMaxVertexs, Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_POINTS, theMaxVertexs, 0, 0, theArrayFlags)
  {
  }

  Graphic3d_ArrayOfPoints(int  theMaxVertexs,
                          bool theHasVColors  = false,
                          bool theHasVNormals = false)
      : Graphic3d_ArrayOfPrimitives(
          Graphic3d_TOPA_POINTS,
          theMaxVertexs,
          0,
          0,
          (theHasVColors ? Graphic3d_ArrayFlags_VertexColor : Graphic3d_ArrayFlags_None)
            | (theHasVNormals ? Graphic3d_ArrayFlags_VertexNormal : Graphic3d_ArrayFlags_None))
  {
  }
};
