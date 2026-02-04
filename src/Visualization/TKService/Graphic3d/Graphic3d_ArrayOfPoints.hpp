#pragma once


#include <Graphic3d_ArrayOfPrimitives.hpp>

//! Contains points array definition.
class Graphic3d_ArrayOfPoints : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfPoints, Graphic3d_ArrayOfPrimitives)
public:
  //! Creates an array of points (Graphic3d_TOPA_POINTS).
  //! The array must be filled using the AddVertex(Point) method.
  //! @param theMaxVertexs maximum number of points
  //! @param theArrayFlags array flags
  Graphic3d_ArrayOfPoints(int theMaxVertexs, Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_POINTS, theMaxVertexs, 0, 0, theArrayFlags)
  {
  }

  //! Creates an array of points (Graphic3d_TOPA_POINTS).
  //! The array must be filled using the AddVertex(Point) method.
  //! @param theMaxVertexs  maximum number of points
  //! @param theHasVColors  when TRUE, AddVertex(Point,Color)  should be used for specifying vertex
  //! color
  //! @param theHasVNormals when TRUE, AddVertex(Point,Normal) should be used for specifying vertex
  //! normal
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

