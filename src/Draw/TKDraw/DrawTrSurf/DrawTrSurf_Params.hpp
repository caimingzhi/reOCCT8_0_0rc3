#pragma once

#include <Draw_Color.hpp>
#include <Draw_MarkerShape.hpp>

//! DrawTrSurf parameters.
struct DrawTrSurf_Params
{
public:
  Draw_Color PntColor;
  Draw_Color CurvColor;
  Draw_Color BoundsColor;
  Draw_Color IsosColor;
  Draw_Color PolesColor;
  Draw_Color KnotsColor;

  Draw_MarkerShape PntMarker;
  Draw_MarkerShape KnotsMarker;
  bool             IsShowPoles;
  bool             IsShowKnots;
  bool             NeedKnotsIsos;
  double           Deflection;
  int              KnotsSize;
  int              Discret;
  int              DrawMode;
  int              NbUIsos;
  int              NbVIsos;

  DrawTrSurf_Params()
      : PntColor(Draw_rouge),
        CurvColor(Draw_jaune),
        BoundsColor(Draw_vert),
        IsosColor(Draw_bleu),
        PolesColor(Draw_rouge),
        KnotsColor(Draw_violet),
        PntMarker(Draw_Plus),
        KnotsMarker(Draw_Losange),
        IsShowPoles(true),
        IsShowKnots(true),
        NeedKnotsIsos(true),
        Deflection(0.01),
        KnotsSize(5),
        Discret(30),
        DrawMode(0),
        NbUIsos(10),
        NbVIsos(10)
  {
  }
};
