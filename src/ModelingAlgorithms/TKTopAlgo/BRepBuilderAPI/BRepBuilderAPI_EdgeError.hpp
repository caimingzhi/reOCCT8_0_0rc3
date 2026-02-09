#pragma once

enum BRepBuilderAPI_EdgeError
{
  BRepBuilderAPI_EdgeDone,
  BRepBuilderAPI_PointProjectionFailed,
  BRepBuilderAPI_ParameterOutOfRange,
  BRepBuilderAPI_DifferentPointsOnClosedCurve,
  BRepBuilderAPI_PointWithInfiniteParameter,
  BRepBuilderAPI_DifferentsPointAndParameter,
  BRepBuilderAPI_LineThroughIdenticPoints
};
