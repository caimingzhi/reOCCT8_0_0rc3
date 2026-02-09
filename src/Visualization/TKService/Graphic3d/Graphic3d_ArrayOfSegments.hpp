#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

class Graphic3d_ArrayOfSegments : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfSegments, Graphic3d_ArrayOfPrimitives)
public:
  Graphic3d_ArrayOfSegments(int theMaxVertexs, int theMaxEdges, Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_SEGMENTS,
                                    theMaxVertexs,
                                    0,
                                    theMaxEdges,
                                    theArrayFlags)
  {
  }

  Graphic3d_ArrayOfSegments(int theMaxVertexs, int theMaxEdges = 0, bool theHasVColors = false)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_SEGMENTS,
                                    theMaxVertexs,
                                    0,
                                    theMaxEdges,
                                    theHasVColors ? Graphic3d_ArrayFlags_VertexColor
                                                  : Graphic3d_ArrayFlags_None)
  {
  }
};
