#pragma once


//! Describes the error.
enum BRepFeat_StatusError
{
  BRepFeat_OK,
  BRepFeat_BadDirect,
  BRepFeat_BadIntersect,
  BRepFeat_EmptyBaryCurve,
  BRepFeat_EmptyCutResult,
  BRepFeat_FalseSide,
  BRepFeat_IncDirection,
  BRepFeat_IncSlidFace,
  BRepFeat_IncParameter,
  BRepFeat_IncTypes,
  BRepFeat_IntervalOverlap,
  BRepFeat_InvFirstShape,
  BRepFeat_InvOption,
  BRepFeat_InvShape,
  BRepFeat_LocOpeNotDone,
  BRepFeat_LocOpeInvNotDone,
  BRepFeat_NoExtFace,
  BRepFeat_NoFaceProf,
  BRepFeat_NoGluer,
  BRepFeat_NoIntersectF,
  BRepFeat_NoIntersectU,
  BRepFeat_NoParts,
  BRepFeat_NoProjPt,
  BRepFeat_NotInitialized,
  BRepFeat_NotYetImplemented,
  BRepFeat_NullRealTool,
  BRepFeat_NullToolF,
  BRepFeat_NullToolU
};

