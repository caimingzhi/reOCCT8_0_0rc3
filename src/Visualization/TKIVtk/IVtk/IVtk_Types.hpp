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

typedef enum
{
  SM_None      = -1,
  SM_Shape     = 0,
  SM_Vertex    = 1,
  SM_Edge      = 2,
  SM_Wire      = 3,
  SM_Face      = 4,
  SM_Shell     = 5,
  SM_Solid     = 6,
  SM_CompSolid = 7,
  SM_Compound  = 8,
} IVtk_SelectionMode;

typedef enum
{
  MT_Undefined     = -1,
  MT_IsoLine       = 0,
  MT_FreeVertex    = 1,
  MT_SharedVertex  = 2,
  MT_FreeEdge      = 3,
  MT_BoundaryEdge  = 4,
  MT_SharedEdge    = 5,
  MT_WireFrameFace = 6,
  MT_ShadedFace    = 7,
  MT_SeamEdge      = 8
} IVtk_MeshType;

typedef enum
{
  DM_Wireframe = 0,
  DM_Shading   = 1
} IVtk_DisplayMode;
