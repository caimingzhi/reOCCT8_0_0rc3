#pragma once

//! Enumeration defining objects identifiers in the shape read/write format.
enum BinTools_ObjectType
{
  BinTools_ObjectType_Unknown = 0,
  BinTools_ObjectType_Reference8,  //!< 8-bits reference
  BinTools_ObjectType_Reference16, //!< 16-bits reference
  BinTools_ObjectType_Reference32, //!< 32-bits reference
  BinTools_ObjectType_Reference64, //!< 64-bits reference
  BinTools_ObjectType_Location,
  BinTools_ObjectType_SimpleLocation,
  BinTools_ObjectType_EmptyLocation,
  BinTools_ObjectType_LocationEnd,
  BinTools_ObjectType_Curve,
  BinTools_ObjectType_EmptyCurve,
  BinTools_ObjectType_Curve2d,
  BinTools_ObjectType_EmptyCurve2d,
  BinTools_ObjectType_Surface,
  BinTools_ObjectType_EmptySurface,
  BinTools_ObjectType_Polygon3d,
  BinTools_ObjectType_EmptyPolygon3d,
  BinTools_ObjectType_PolygonOnTriangulation,
  BinTools_ObjectType_EmptyPolygonOnTriangulation,
  BinTools_ObjectType_Triangulation,
  BinTools_ObjectType_EmptyTriangulation,
  BinTools_ObjectType_EmptyShape = 198, //!< identifier of the null shape
  BinTools_ObjectType_EndShape   = 199, //!< identifier of the shape record end
  // here is the space for TopAbs_ShapeEnum+Orientation types
};
