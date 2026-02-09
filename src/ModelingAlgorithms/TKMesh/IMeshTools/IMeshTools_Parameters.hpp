#pragma once

enum IMeshTools_MeshAlgoType
{
  IMeshTools_MeshAlgoType_DEFAULT = -1,
  IMeshTools_MeshAlgoType_Watson  = 0,
  IMeshTools_MeshAlgoType_Delabella,
};

#include <Precision.hpp>

struct IMeshTools_Parameters
{

  IMeshTools_Parameters()
      : MeshAlgo(IMeshTools_MeshAlgoType_DEFAULT),
        Angle(0.5),
        Deflection(0.001),
        AngleInterior(-1.0),
        DeflectionInterior(-1.0),
        MinSize(-1.0),
        InParallel(false),
        Relative(false),
        InternalVerticesMode(true),
        ControlSurfaceDeflection(true),
        EnableControlSurfaceDeflectionAllSurfaces(false),
        CleanModel(true),
        AdjustMinSize(false),
        ForceFaceDeflection(false),
        AllowQualityDecrease(false)
  {
  }

  static double RelMinSize() { return 0.1; }

  IMeshTools_MeshAlgoType MeshAlgo;

  double Angle;

  double Deflection;

  double AngleInterior;

  double DeflectionInterior;

  double MinSize;

  bool InParallel;

  bool Relative;

  bool InternalVerticesMode;

  bool ControlSurfaceDeflection;

  bool EnableControlSurfaceDeflectionAllSurfaces;

  bool CleanModel;

  bool AdjustMinSize;

  bool ForceFaceDeflection;

  bool AllowQualityDecrease;
};
