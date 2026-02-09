#pragma once

#include <Standard_Macro.hpp>
#include <TopAbs_ShapeEnum.hpp>

struct DE_ShapeFixParameters
{

  enum class FixMode : signed char
  {
    FixOrNot = -1,
    NotFix   = 0,
    Fix      = 1
  };

  double           Tolerance3d                         = 1.e-6;
  double           MaxTolerance3d                      = 1.0;
  double           MinTolerance3d                      = 1.e-7;
  TopAbs_ShapeEnum DetalizationLevel                   = TopAbs_ShapeEnum::TopAbs_VERTEX;
  bool             NonManifold                         = false;
  FixMode          FixFreeShellMode                    = FixMode::FixOrNot;
  FixMode          FixFreeFaceMode                     = FixMode::FixOrNot;
  FixMode          FixFreeWireMode                     = FixMode::FixOrNot;
  FixMode          FixSameParameterMode                = FixMode::FixOrNot;
  FixMode          FixSolidMode                        = FixMode::FixOrNot;
  FixMode          FixShellOrientationMode             = FixMode::FixOrNot;
  FixMode          CreateOpenSolidMode                 = FixMode::NotFix;
  FixMode          FixShellMode                        = FixMode::FixOrNot;
  FixMode          FixFaceOrientationMode              = FixMode::FixOrNot;
  FixMode          FixFaceMode                         = FixMode::FixOrNot;
  FixMode          FixWireMode                         = FixMode::FixOrNot;
  FixMode          FixOrientationMode                  = FixMode::FixOrNot;
  FixMode          FixAddNaturalBoundMode              = FixMode::FixOrNot;
  FixMode          FixMissingSeamMode                  = FixMode::FixOrNot;
  FixMode          FixSmallAreaWireMode                = FixMode::FixOrNot;
  FixMode          RemoveSmallAreaFaceMode             = FixMode::FixOrNot;
  FixMode          FixIntersectingWiresMode            = FixMode::FixOrNot;
  FixMode          FixLoopWiresMode                    = FixMode::FixOrNot;
  FixMode          FixSplitFaceMode                    = FixMode::FixOrNot;
  FixMode          AutoCorrectPrecisionMode            = FixMode::Fix;
  FixMode          ModifyTopologyMode                  = FixMode::NotFix;
  FixMode          ModifyGeometryMode                  = FixMode::Fix;
  FixMode          ClosedWireMode                      = FixMode::Fix;
  FixMode          PreferencePCurveMode                = FixMode::Fix;
  FixMode          FixReorderMode                      = FixMode::FixOrNot;
  FixMode          FixSmallMode                        = FixMode::FixOrNot;
  FixMode          FixConnectedMode                    = FixMode::FixOrNot;
  FixMode          FixEdgeCurvesMode                   = FixMode::FixOrNot;
  FixMode          FixDegeneratedMode                  = FixMode::FixOrNot;
  FixMode          FixLackingMode                      = FixMode::FixOrNot;
  FixMode          FixSelfIntersectionMode             = FixMode::FixOrNot;
  FixMode          RemoveLoopMode                      = FixMode::FixOrNot;
  FixMode          FixReversed2dMode                   = FixMode::FixOrNot;
  FixMode          FixRemovePCurveMode                 = FixMode::FixOrNot;
  FixMode          FixRemoveCurve3dMode                = FixMode::FixOrNot;
  FixMode          FixAddPCurveMode                    = FixMode::FixOrNot;
  FixMode          FixAddCurve3dMode                   = FixMode::FixOrNot;
  FixMode          FixSeamMode                         = FixMode::FixOrNot;
  FixMode          FixShiftedMode                      = FixMode::FixOrNot;
  FixMode          FixEdgeSameParameterMode            = FixMode::NotFix;
  FixMode          FixNotchedEdgesMode                 = FixMode::FixOrNot;
  FixMode          FixTailMode                         = FixMode::NotFix;
  FixMode          MaxTailAngle                        = FixMode::NotFix;
  FixMode          MaxTailWidth                        = FixMode::FixOrNot;
  FixMode          FixSelfIntersectingEdgeMode         = FixMode::FixOrNot;
  FixMode          FixIntersectingEdgesMode            = FixMode::FixOrNot;
  FixMode          FixNonAdjacentIntersectingEdgesMode = FixMode::FixOrNot;
  FixMode          FixVertexPositionMode               = FixMode::NotFix;
  FixMode          FixVertexToleranceMode              = FixMode::FixOrNot;
};
