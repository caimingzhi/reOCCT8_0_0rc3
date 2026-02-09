#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

class Graphic3d_ArrayOfPolygons : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfPolygons, Graphic3d_ArrayOfPrimitives)
public:
  Graphic3d_ArrayOfPolygons(int                  theMaxVertexs,
                            int                  theMaxBounds,
                            int                  theMaxEdges,
                            Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_POLYGONS,
                                    theMaxVertexs,
                                    theMaxBounds,
                                    theMaxEdges,
                                    theArrayFlags)
  {
  }

  Graphic3d_ArrayOfPolygons(const int  theMaxVertexs,
                            const int  theMaxBounds   = 0,
                            const int  theMaxEdges    = 0,
                            const bool theHasVNormals = false,
                            const bool theHasVColors  = false,
                            const bool theHasBColors  = false,
                            const bool theHasVTexels  = false)
      : Graphic3d_ArrayOfPrimitives(
          Graphic3d_TOPA_POLYGONS,
          theMaxVertexs,
          theMaxBounds,
          theMaxEdges,
          (theHasVNormals ? Graphic3d_ArrayFlags_VertexNormal : Graphic3d_ArrayFlags_None)
            | (theHasVColors ? Graphic3d_ArrayFlags_VertexColor : Graphic3d_ArrayFlags_None)
            | (theHasBColors ? Graphic3d_ArrayFlags_BoundColor : Graphic3d_ArrayFlags_None)
            | (theHasVTexels ? Graphic3d_ArrayFlags_VertexTexel : Graphic3d_ArrayFlags_None))
  {
  }
};
