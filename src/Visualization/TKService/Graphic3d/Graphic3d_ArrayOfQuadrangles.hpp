#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

class Graphic3d_ArrayOfQuadrangles : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfQuadrangles, Graphic3d_ArrayOfPrimitives)
public:
  Graphic3d_ArrayOfQuadrangles(int                  theMaxVertexs,
                               int                  theMaxEdges,
                               Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_QUADRANGLES,
                                    theMaxVertexs,
                                    0,
                                    theMaxEdges,
                                    theArrayFlags)
  {
  }

  Graphic3d_ArrayOfQuadrangles(int  theMaxVertexs,
                               int  theMaxEdges    = 0,
                               bool theHasVNormals = false,
                               bool theHasVColors  = false,
                               bool theHasVTexels  = false)
      : Graphic3d_ArrayOfPrimitives(
          Graphic3d_TOPA_QUADRANGLES,
          theMaxVertexs,
          0,
          theMaxEdges,
          (theHasVNormals ? Graphic3d_ArrayFlags_VertexNormal : Graphic3d_ArrayFlags_None)
            | (theHasVColors ? Graphic3d_ArrayFlags_VertexColor : Graphic3d_ArrayFlags_None)
            | (theHasVTexels ? Graphic3d_ArrayFlags_VertexTexel : Graphic3d_ArrayFlags_None))
  {
  }
};
