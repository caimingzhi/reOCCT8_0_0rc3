#include <GeometryTest_DrawableQualifiedCurve2d.hpp>

#include <GccEnt.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeometryTest_DrawableQualifiedCurve2d, DrawTrSurf_Curve2d)

GeometryTest_DrawableQualifiedCurve2d::GeometryTest_DrawableQualifiedCurve2d(
  const occ::handle<Geom2d_Curve>& theCurve,
  const GccEnt_Position            thePosition,
  const bool                       theDispOrigin)
    : DrawTrSurf_Curve2d(theCurve, theDispOrigin),
      myPosition(thePosition)
{
  look = Draw_orange;
}

GeometryTest_DrawableQualifiedCurve2d::GeometryTest_DrawableQualifiedCurve2d(
  const occ::handle<Geom2d_Curve>& theCurve,
  const Draw_Color&                theColor,
  const int                        theDiscret,
  const GccEnt_Position            thePosition,
  const bool                       theDispOrigin,
  const bool                       theDispCurvRadius,
  const double                     theRadiusMax,
  const double                     theRatioOfRadius)
    : DrawTrSurf_Curve2d(theCurve,
                         theColor,
                         theDiscret,
                         theDispOrigin,
                         theDispCurvRadius,
                         theRadiusMax,
                         theRatioOfRadius),
      myPosition(thePosition)
{
  look = Draw_orange;
}

void GeometryTest_DrawableQualifiedCurve2d::DrawOn(Draw_Display& theDisplay) const
{
  DrawTrSurf_Curve2d::DrawOn(theDisplay);
}

void GeometryTest_DrawableQualifiedCurve2d::Dump(Standard_OStream& theStream) const
{
  theStream << "Qualified curve 2D: \n";
  theStream << "Position :" << GccEnt::PositionToString(myPosition) << "\n";
  DrawTrSurf_Curve2d::Dump(theStream);
}

void GeometryTest_DrawableQualifiedCurve2d::Whatis(Draw_Interpretor& theDI) const
{
  occ::handle<Standard_Type> aType = GetCurve()->DynamicType();

  if (aType == STANDARD_TYPE(Geom2d_Circle))
  {
    theDI << "qualified 2d Circle";
  }
  else if (aType == STANDARD_TYPE(Geom2d_Line))
  {
    theDI << "qualified 2d Line";
  }
}
