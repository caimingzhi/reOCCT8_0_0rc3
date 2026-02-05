#pragma once

//! Standard coordinate system definition.
//! Open CASCADE does not force application using specific coordinate system,
//! although Draw Harness and samples define +Z-up +Y-forward coordinate system for camera view
//! manipulation. This enumeration defines two commonly used conventions - Z-up and Y-up..
enum RWMesh_CoordinateSystem
{
  RWMesh_CoordinateSystem_Undefined      = -1, //!< undefined
  RWMesh_CoordinateSystem_posYfwd_posZup = 0,  //!< +YForward+Zup+Xright
  RWMesh_CoordinateSystem_negZfwd_posYup,      //!< -ZForward+Yup+Xright

  RWMesh_CoordinateSystem_Blender =
    RWMesh_CoordinateSystem_posYfwd_posZup, //!< coordinate system used by Blender
                                            //!< (+YForward+Zup+Xright)
  RWMesh_CoordinateSystem_glTF =
    RWMesh_CoordinateSystem_negZfwd_posYup, //!< coordinate system used by glTF
                                            //!< (-ZForward+Yup+Xright)
  RWMesh_CoordinateSystem_Zup =
    RWMesh_CoordinateSystem_Blender, //!< Z-up coordinate system (+YForward+Zup+Xright)
  RWMesh_CoordinateSystem_Yup =
    RWMesh_CoordinateSystem_glTF, //!< Y-up coordinate system (-ZForward+Yup+Xright)
};
