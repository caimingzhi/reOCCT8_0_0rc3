#pragma once

#include <Graphic3d_ArrayOfPrimitives.hpp>

//! Contains quadrangles array definition.
//! WARNING! Quadrangle primitives might be unsupported by graphics library.
//! Triangulation should be used instead of quads for better compatibility.
class Graphic3d_ArrayOfQuadrangles : public Graphic3d_ArrayOfPrimitives
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfQuadrangles, Graphic3d_ArrayOfPrimitives)
public:
  //! Creates an array of quadrangles (Graphic3d_TOPA_QUADRANGLES), a quadrangle can be filled as:
  //! 1) Creating a set of quadrangles defined with his vertexes, i.e:
  //! @code
  //!   myArray = Graphic3d_ArrayOfQuadrangles (8);
  //!   myArray->AddVertex (x1, y1, z1);
  //!   ....
  //!   myArray->AddVertex (x8, y8, z8);
  //! @endcode
  //! 2) Creating a set of indexed quadrangles defined with his vertex ans edges, i.e:
  //! @code
  //!   myArray = Graphic3d_ArrayOfQuadrangles (6, 8);
  //!   myArray->AddVertex (x1, y1, z1);
  //!   ....
  //!   myArray->AddVertex (x6, y6, z6);
  //!   myArray->AddEdges (1, 2, 3, 4);
  //!   myArray->AddEdges (3, 4, 5, 6);
  //! @endcode
  //! @param theMaxVertexs defines the maximum allowed vertex number in the array
  //! @param theMaxEdges   defines the maximum allowed edge   number in the array (for indexed
  //! array)
  //! @param theArrayFlags array flags
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

  //! Creates an array of quadrangles (Graphic3d_TOPA_QUADRANGLES).
  //! @param theMaxVertexs defines the maximum allowed vertex number in the array
  //! @param theMaxEdges   defines the maximum allowed edge   number in the array (for indexed
  //! array)
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
