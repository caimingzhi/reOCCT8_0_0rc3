#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

class Graphic3d_ArrayOfPolylines : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfPolylines, Graphic3d_ArrayOfPrimitives)
public:
  Graphic3d_ArrayOfPolylines(int                  theMaxVertexs,
                             int                  theMaxBounds,
                             int                  theMaxEdges,
                             Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_POLYLINES,
                                    theMaxVertexs,
                                    theMaxBounds,
                                    theMaxEdges,
                                    theArrayFlags)
  {
  }

  Graphic3d_ArrayOfPolylines(int  theMaxVertexs,
                             int  theMaxBounds  = 0,
                             int  theMaxEdges   = 0,
                             bool theHasVColors = false,
                             bool theHasBColors = false)
      : Graphic3d_ArrayOfPrimitives(
          Graphic3d_TOPA_POLYLINES,
          theMaxVertexs,
          theMaxBounds,
          theMaxEdges,
          (theHasVColors ? Graphic3d_ArrayFlags_VertexColor : Graphic3d_ArrayFlags_None)
            | (theHasBColors ? Graphic3d_ArrayFlags_BoundColor : Graphic3d_ArrayFlags_None))
  {
  }
};
