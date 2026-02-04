#pragma once


//! Modification type after a topologic operation.
enum BRepLib_ShapeModification
{
  BRepLib_Preserved,
  BRepLib_Deleted,
  BRepLib_Trimmed,
  BRepLib_Merged,
  BRepLib_BoundaryModified
};

