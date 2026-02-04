#pragma once


//! Error that can occur during the fillet construction on planar wire.
enum ChFi2d_ConstructionError
{
  ChFi2d_NotPlanar,           //!< the face is not planar
  ChFi2d_NoFace,              //!< the face is null
  ChFi2d_InitialisationError, //!< the two faces used for the initialisation are uncompatible
  ChFi2d_ParametersError, //!< the parameters as distances or angle for chamfer are less or equal to
                          //!< zero
  ChFi2d_Ready,           //!< the initialization has been successful
  ChFi2d_IsDone,
  ChFi2d_ComputationError, //!< the algorithm could not find a solution
  ChFi2d_ConnexionError, //!< the vertex given to locate the fillet or the chamfer is not connected
                         //!< to 2 edges
  ChFi2d_TangencyError,  //!< the two edges connected to the vertex are tangent
  ChFi2d_FirstEdgeDegenerated, //!< the first edge is degenerated
  ChFi2d_LastEdgeDegenerated,  //!< the last edge is degenerated
  ChFi2d_BothEdgesDegenerated, //!< the two edges are degenerated
  ChFi2d_NotAuthorized //!< One or the two edges connected to the vertex is a fillet or a chamfer;
                       //!< One or the two edges connected to the vertex is not a line or a circle
};

