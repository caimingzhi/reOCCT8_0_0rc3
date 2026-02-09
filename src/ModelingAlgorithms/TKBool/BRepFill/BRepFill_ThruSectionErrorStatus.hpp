#pragma once

enum BRepFill_ThruSectionErrorStatus
{
  BRepFill_ThruSectionErrorStatus_Done,
  BRepFill_ThruSectionErrorStatus_NotDone,
  BRepFill_ThruSectionErrorStatus_NotSameTopology,

  BRepFill_ThruSectionErrorStatus_ProfilesInconsistent,
  BRepFill_ThruSectionErrorStatus_WrongUsage,
  BRepFill_ThruSectionErrorStatus_Null3DCurve,
  BRepFill_ThruSectionErrorStatus_Failed
};
