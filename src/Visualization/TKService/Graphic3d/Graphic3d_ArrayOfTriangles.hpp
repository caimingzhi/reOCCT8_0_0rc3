#pragma once


#include <Graphic3d_ArrayOfPrimitives.hpp>

//! Contains triangles array definition
class Graphic3d_ArrayOfTriangles : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfTriangles, Graphic3d_ArrayOfPrimitives)
public:
  //! Creates an array of triangles (Graphic3d_TOPA_TRIANGLES), a triangle can be filled as:
  //! 1) Creating a set of triangles defined with his vertexes, i.e:
  //! @code
  //!   myArray = Graphic3d_ArrayOfTriangles (6);
  //!   myArray->AddVertex (x1, y1, z1);
  //!   ....
  //!   myArray->AddVertex (x6, y6, z6);
  //! @endcode
  //! 3) Creating a set of indexed triangles defined with his vertex and edges, i.e:
  //! @code
  //!   myArray = Graphic3d_ArrayOfTriangles (4, 6);
  //!   myArray->AddVertex (x1, y1, z1);
  //!   ....
  //!   myArray->AddVertex (x4, y4, z4);
  //!   myArray->AddEdges (1, 2, 3);
  //!   myArray->AddEdges (2, 3, 4);
  //! @endcode
  //! @param theMaxVertexs  defines the maximum allowed vertex number in the array
  //! @param theMaxEdges    defines the maximum allowed edge   number in the array
  //! @param theArrayFlags array flags
  Graphic3d_ArrayOfTriangles(int theMaxVertexs, int theMaxEdges, Graphic3d_ArrayFlags theArrayFlags)
      : Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_TRIANGLES,
                                    theMaxVertexs,
                                    0,
                                    theMaxEdges,
                                    theArrayFlags)
  {
  }

  //! Creates an array of triangles (Graphic3d_TOPA_TRIANGLES).
  //! @param theMaxVertexs  defines the maximum allowed vertex number in the array
  //! @param theMaxEdges    defines the maximum allowed edge   number in the array
  //! @param theHasVNormals when TRUE,  AddVertex(Point,Normal), AddVertex(Point,Normal,Color) or
  //! AddVertex(Point,Normal,Texel) should be used to specify vertex normal;
  //!                       vertex normals should be specified coherent to triangle orientation
  //!                       (defined by order of vertexes within triangle) for proper rendering
  //! @param theHasVColors  when TRUE,  AddVertex(Point,Color) or AddVertex(Point,Normal,Color)
  //! should be used to specify vertex color
  //! @param theHasVTexels  when TRUE,  AddVertex(Point,Texel) or AddVertex(Point,Normal,Texel)
  //! should be used to specify vertex UV coordinates
  Graphic3d_ArrayOfTriangles(int  theMaxVertexs,
                             int  theMaxEdges    = 0,
                             bool theHasVNormals = false,
                             bool theHasVColors  = false,
                             bool theHasVTexels  = false)
      : Graphic3d_ArrayOfPrimitives(
          Graphic3d_TOPA_TRIANGLES,
          theMaxVertexs,
          0,
          theMaxEdges,
          (theHasVNormals ? Graphic3d_ArrayFlags_VertexNormal : Graphic3d_ArrayFlags_None)
            | (theHasVColors ? Graphic3d_ArrayFlags_VertexColor : Graphic3d_ArrayFlags_None)
            | (theHasVTexels ? Graphic3d_ArrayFlags_VertexTexel : Graphic3d_ArrayFlags_None))
  {
  }
};

