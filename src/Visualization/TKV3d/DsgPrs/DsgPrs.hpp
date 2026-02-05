#pragma once

#include <DsgPrs_ArrowSide.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <Prs3d_Presentation.hpp>

class Geom_Curve;
class Geom_Surface;
class Prs3d_DimensionAspect;

//! Describes Standard Presentations for DsgIHM objects
class DsgPrs
{
public:
  DEFINE_STANDARD_ALLOC

  //! draws symbols ((one or two) arrows,(one or two)points
  //! at thebeginning and at the end of the dimension
  Standard_EXPORT static void ComputeSymbol(const occ::handle<Prs3d_Presentation>&    aPresentation,
                                            const occ::handle<Prs3d_DimensionAspect>& anAspect,
                                            const gp_Pnt&                             pt1,
                                            const gp_Pnt&                             pt2,
                                            const gp_Dir&                             dir1,
                                            const gp_Dir&                             dir2,
                                            const DsgPrs_ArrowSide                    ArrowSide,
                                            const bool drawFromCenter = true);

  Standard_EXPORT static void ComputePlanarFacesLengthPresentation(const double  FirstArrowLength,
                                                                   const double  SecondArrowLength,
                                                                   const gp_Pnt& AttachmentPoint1,
                                                                   const gp_Pnt& AttachmentPoint2,
                                                                   const gp_Dir& DirAttach,
                                                                   const gp_Pnt& OffsetPoint,
                                                                   const gp_Pln& PlaneOfFaces,
                                                                   gp_Pnt&       EndOfArrow1,
                                                                   gp_Pnt&       EndOfArrow2,
                                                                   gp_Dir&       DirOfArrow1);

  Standard_EXPORT static void ComputeCurvilinearFacesLengthPresentation(
    const double                     FirstArrowLength,
    const double                     SecondArrowLength,
    const occ::handle<Geom_Surface>& SecondSurf,
    const gp_Pnt&                    AttachmentPoint1,
    const gp_Pnt&                    AttachmentPoint2,
    const gp_Dir&                    DirAttach,
    gp_Pnt&                          EndOfArrow2,
    gp_Dir&                          DirOfArrow1,
    occ::handle<Geom_Curve>&         VCurve,
    occ::handle<Geom_Curve>&         UCurve,
    double&                          FirstU,
    double&                          deltaU,
    double&                          FirstV,
    double&                          deltaV);

  Standard_EXPORT static void ComputeFacesAnglePresentation(const double  ArrowLength,
                                                            const double  Value,
                                                            const gp_Pnt& CenterPoint,
                                                            const gp_Pnt& AttachmentPoint1,
                                                            const gp_Pnt& AttachmentPoint2,
                                                            const gp_Dir& dir1,
                                                            const gp_Dir& dir2,
                                                            const gp_Dir& axisdir,
                                                            const bool    isPlane,
                                                            const gp_Ax1& AxisOfSurf,
                                                            const gp_Pnt& OffsetPoint,
                                                            gp_Circ&      AngleCirc,
                                                            double&       FirstParAngleCirc,
                                                            double&       LastParAngleCirc,
                                                            gp_Pnt&       EndOfArrow1,
                                                            gp_Pnt&       EndOfArrow2,
                                                            gp_Dir&       DirOfArrow1,
                                                            gp_Dir&       DirOfArrow2,
                                                            gp_Pnt&       ProjAttachPoint2,
                                                            gp_Circ&      AttachCirc,
                                                            double&       FirstParAttachCirc,
                                                            double&       LastParAttachCirc);

  Standard_EXPORT static void ComputeRadiusLine(const gp_Pnt& aCenter,
                                                const gp_Pnt& anEndOfArrow,
                                                const gp_Pnt& aPosition,
                                                const bool    drawFromCenter,
                                                gp_Pnt&       aRadLineOrign,
                                                gp_Pnt&       aRadLineEnd);

  //! computes Geometry for fillet radius presentation;
  //! special case flag SpecCase equal true if
  //! radius of fillet circle = 0 or if angle between
  //! Vec1(Center, FirstPoint) and Vec2(Center,SecondPoint) equal 0 or PI
  Standard_EXPORT static void ComputeFilletRadiusPresentation(const double  ArrowLength,
                                                              const double  Value,
                                                              const gp_Pnt& Position,
                                                              const gp_Dir& NormalDir,
                                                              const gp_Pnt& FirstPoint,
                                                              const gp_Pnt& SecondPoint,
                                                              const gp_Pnt& Center,
                                                              const gp_Pnt& BasePnt,
                                                              const bool    drawRevers,
                                                              bool&         SpecCase,
                                                              gp_Circ&      FilletCirc,
                                                              double&       FirstParCirc,
                                                              double&       LastParCirc,
                                                              gp_Pnt&       EndOfArrow,
                                                              gp_Dir&       DirOfArrow,
                                                              gp_Pnt&       DrawPosition);

  //! computes length of ellipse arc in parametric units
  Standard_EXPORT static double DistanceFromApex(const gp_Elips& elips,
                                                 const gp_Pnt&   Apex,
                                                 const double    par);
};
