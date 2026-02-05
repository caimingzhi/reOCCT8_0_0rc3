#pragma once

#include <gp_XY.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <vtkType.h>

#include <limits>

#ifdef VTK_USE_64BIT_IDS
  #if defined(_WIN32) && !defined(_WIN64)
    #error "64-bit VTK library can not be linked for 32-bit target platform"
  #endif
#else
  #ifdef _WIN64
    #error "32-bit VTK library can not be linked for 64-bit target platform"
  #endif
#endif

typedef vtkIdType   IVtk_IdType;
typedef IVtk_IdType IVtk_PointId;

typedef IVtk_IdType IVtk_FaceId;
typedef IVtk_IdType IVtk_EdgeId;

//! @enum IVtk_SelectionMode Selection modes for 3D shapes
//!
//! Enumeration that describes all supported selection modes for 3D shapes.
//! SM_None means that the shape should become non-selectable.
//! SM_Shape makes the shape selectable as a whole.
//! Other modes activate selection of sub-shapes of corresponding types.
typedef enum
{
  SM_None      = -1, //!< No selection
  SM_Shape     = 0,  //!< Shape selection
  SM_Vertex    = 1,  //!< Vertex selection
  SM_Edge      = 2,  //!< Edge selection
  SM_Wire      = 3,  //!< Wire selection
  SM_Face      = 4,  //!< Face selection
  SM_Shell     = 5,  //!< Shell selection
  SM_Solid     = 6,  //!< Solid selection
  SM_CompSolid = 7,  //!< CompSolid selection
  SM_Compound  = 8,  //!< Compound selection
} IVtk_SelectionMode;

//! @enum IVtk_MeshType Types of mesh parts for 3D shapes
//!
//! Enumeration that describes all supported types of mesh parts for 3D shapes.
typedef enum
{
  MT_Undefined     = -1, //!< Undefined
  MT_IsoLine       = 0,  //!< Isoline
  MT_FreeVertex    = 1,  //!< Free vertex
  MT_SharedVertex  = 2,  //!< Shared vertex
  MT_FreeEdge      = 3,  //!< Free edge
  MT_BoundaryEdge  = 4,  //!< Boundary edge (related to a single face)
  MT_SharedEdge    = 5,  //!< Shared edge (related to several faces)
  MT_WireFrameFace = 6,  //!< Wireframe face
  MT_ShadedFace    = 7,  //!< Shaded face
  MT_SeamEdge      = 8   //!< Seam edge between faces
} IVtk_MeshType;

//! @enum IVtk_DisplayMode Display modes for 3D shapes
//!
//! Enumeration that describes all supported display modes for 3D shapes.
typedef enum
{
  DM_Wireframe = 0, //!< Wireframe display mode
  DM_Shading   = 1  //!< Shaded display mode
} IVtk_DisplayMode;
