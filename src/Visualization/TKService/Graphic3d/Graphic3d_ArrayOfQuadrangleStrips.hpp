#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

class Graphic3d_ArrayOfQuadrangleStrips : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfQuadrangleStrips, Graphic3d_ArrayOfPrimitives)
public:
  Graphic3d_ArrayOfQuadrangleStrips(int                  theMaxVertexs,
                                    int                  theMaxStrips,
                                    Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_QUADRANGLESTRIPS,
                                    theMaxVertexs,
                                    theMaxStrips,
                                    0,
                                    theArrayFlags)
  {
  }

  Graphic3d_ArrayOfQuadrangleStrips(int  theMaxVertexs,
                                    int  theMaxStrips   = 0,
                                    bool theHasVNormals = false,
                                    bool theHasVColors  = false,
                                    bool theHasSColors  = false,
                                    bool theHasVTexels  = false)
      : Graphic3d_ArrayOfPrimitives(
          Graphic3d_TOPA_QUADRANGLESTRIPS,
          theMaxVertexs,
          theMaxStrips,
          0,
          (theHasVNormals ? Graphic3d_ArrayFlags_VertexNormal : Graphic3d_ArrayFlags_None)
            | (theHasVColors ? Graphic3d_ArrayFlags_VertexColor : Graphic3d_ArrayFlags_None)
            | (theHasVTexels ? Graphic3d_ArrayFlags_VertexTexel : Graphic3d_ArrayFlags_None)
            | (theHasSColors ? Graphic3d_ArrayFlags_BoundColor : Graphic3d_ArrayFlags_None))
  {
  }
};
