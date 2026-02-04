#pragma once


//! Low-level glTF enumeration defining Primitive type.
//! Similar to Graphic3d_TypeOfData but does not define actual type and includes matrices.
enum RWGltf_GltfPrimitiveMode
{
  RWGltf_GltfPrimitiveMode_UNKNOWN       = -1, //!< unknown or invalid type
  RWGltf_GltfPrimitiveMode_Points        = 0,  //!< GL_POINTS
  RWGltf_GltfPrimitiveMode_Lines         = 1,  //!< GL_LINES
  RWGltf_GltfPrimitiveMode_LineLoop      = 2,  //!< GL_LINE_LOOP
  RWGltf_GltfPrimitiveMode_LineStrip     = 3,  //!< GL_LINE_STRIP
  RWGltf_GltfPrimitiveMode_Triangles     = 4,  //!< GL_TRIANGLES
  RWGltf_GltfPrimitiveMode_TriangleStrip = 5,  //!< GL_TRIANGLE_STRIP
  RWGltf_GltfPrimitiveMode_TriangleFan   = 6,  //!< GL_TRIANGLE_FAN
};

