#pragma once

#include <Standard.hpp>
#include <DrawTrSurf_Curve2d.hpp>
#include <GccEnt_Position.hpp>

class Geom2d_Curve;

//! Create geom curve drawable presentation with the position of a solution of a construction
//! algorithm.
class GeometryTest_DrawableQualifiedCurve2d : public DrawTrSurf_Curve2d
{

public:
  //! Creates a drawable curve from a curve of package Geom.
  Standard_EXPORT GeometryTest_DrawableQualifiedCurve2d(const occ::handle<Geom2d_Curve>& theCurve,
                                                        const GccEnt_Position thePosition,
                                                        const bool            theDispOrigin = true);

  //! Creates a drawable curve from a curve of package Geom.
  Standard_EXPORT GeometryTest_DrawableQualifiedCurve2d(const occ::handle<Geom2d_Curve>& theCurve,
                                                        const Draw_Color&                theColor,
                                                        const int                        theDiscret,
                                                        const GccEnt_Position thePosition,
                                                        const bool            theDispOrigin = true,
                                                        const bool   theDispCurvRadius      = false,
                                                        const double theRadiusMax           = 1.0e3,
                                                        const double theRatioOfRadius       = 0.1);

  //! \returns position of a solution
  GccEnt_Position GetPosition() const { return myPosition; }

  //! Sets position of a solution
  //! \param thePosition the value
  void SetPosition(const GccEnt_Position thePosition) { myPosition = thePosition; }

  //! Paints the drawable presentation in given display
  //! \param theDisplay
  Standard_EXPORT void DrawOn(Draw_Display& theDisplay) const override;

  //! For variable dump.
  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  //! For variable whatis command. Set as a result the
  //! type of the variable.
  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(GeometryTest_DrawableQualifiedCurve2d, DrawTrSurf_Curve2d)

private:
  GccEnt_Position myPosition;
};
