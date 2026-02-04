#pragma once


enum BRepOffset_Error
{
  BRepOffset_NoError,
  BRepOffset_UnknownError,
  BRepOffset_BadNormalsOnGeometry,
  BRepOffset_C0Geometry,
  BRepOffset_NullOffset,
  BRepOffset_NotConnectedShell,
  BRepOffset_CannotTrimEdges,    //!< exception while trim edges
  BRepOffset_CannotFuseVertices, //!< exception while fuse vertices
  BRepOffset_CannotExtentEdge,   //!< exception while extent edges
  BRepOffset_UserBreak,          //!< user break
  BRepOffset_MixedConnectivity   //!< Different connectivity of faces along edge: partially C0 and
                                 //!< tangent
};

