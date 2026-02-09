#pragma once

enum BRepOffset_Error
{
  BRepOffset_NoError,
  BRepOffset_UnknownError,
  BRepOffset_BadNormalsOnGeometry,
  BRepOffset_C0Geometry,
  BRepOffset_NullOffset,
  BRepOffset_NotConnectedShell,
  BRepOffset_CannotTrimEdges,
  BRepOffset_CannotFuseVertices,
  BRepOffset_CannotExtentEdge,
  BRepOffset_UserBreak,
  BRepOffset_MixedConnectivity
};
