#pragma once

#include <Standard.hpp>
#include <DrawTrSurf_Curve2d.hpp>
#include <GccEnt_Position.hpp>

class Geom2d_Curve;

class GeometryTest_DrawableQualifiedCurve2d : public DrawTrSurf_Curve2d
{

public:
  Standard_EXPORT GeometryTest_DrawableQualifiedCurve2d(const occ::handle<Geom2d_Curve>& theCurve,
                                                        const GccEnt_Position thePosition,
                                                        const bool            theDispOrigin = true);

  Standard_EXPORT GeometryTest_DrawableQualifiedCurve2d(const occ::handle<Geom2d_Curve>& theCurve,
                                                        const Draw_Color&                theColor,
                                                        const int                        theDiscret,
                                                        const GccEnt_Position thePosition,
                                                        const bool            theDispOrigin = true,
                                                        const bool   theDispCurvRadius      = false,
                                                        const double theRadiusMax           = 1.0e3,
                                                        const double theRatioOfRadius       = 0.1);

  GccEnt_Position GetPosition() const { return myPosition; }

  void SetPosition(const GccEnt_Position thePosition) { myPosition = thePosition; }

  Standard_EXPORT void DrawOn(Draw_Display& theDisplay) const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(GeometryTest_DrawableQualifiedCurve2d, DrawTrSurf_Curve2d)

private:
  GccEnt_Position myPosition;
};
