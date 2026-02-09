#pragma once

enum AIS_KindOfInteractive
{
  AIS_KindOfInteractive_None,
  AIS_KindOfInteractive_Datum,

  AIS_KindOfInteractive_Shape,
  AIS_KindOfInteractive_Object,
  AIS_KindOfInteractive_Relation,
  AIS_KindOfInteractive_Dimension,

  AIS_KindOfInteractive_LightSource,

  AIS_KOI_None      = AIS_KindOfInteractive_None,
  AIS_KOI_Datum     = AIS_KindOfInteractive_Datum,
  AIS_KOI_Shape     = AIS_KindOfInteractive_Shape,
  AIS_KOI_Object    = AIS_KindOfInteractive_Object,
  AIS_KOI_Relation  = AIS_KindOfInteractive_Relation,
  AIS_KOI_Dimension = AIS_KindOfInteractive_Dimension
};
