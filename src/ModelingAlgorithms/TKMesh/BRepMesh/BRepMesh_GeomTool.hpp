#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <GCPnts_TangentialDeflection.hpp>
#include <GeomAbs_IsoType.hpp>
#include <TopoDS_Edge.hpp>
#include <Precision.hpp>

class BRepAdaptor_Curve;
class gp_Pnt2d;
class BRepMesh_DefaultRangeSplitter;

class BRepMesh_GeomTool
{
public:
  enum IntFlag
  {
    NoIntersection,
    Cross,
    EndPointTouch,
    PointOnSegment,
    Glued,
    Same
  };

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepMesh_GeomTool(const BRepAdaptor_Curve& theCurve,
                                    const double             theFirstParam,
                                    const double             theLastParam,
                                    const double             theLinDeflection,
                                    const double             theAngDeflection,
                                    const int                theMinPointsNb = 2,
                                    const double             theMinSize = Precision::Confusion());

  Standard_EXPORT BRepMesh_GeomTool(const occ::handle<BRepAdaptor_Surface>& theSurface,
                                    const GeomAbs_IsoType                   theIsoType,
                                    const double                            theParamIso,
                                    const double                            theFirstParam,
                                    const double                            theLastParam,
                                    const double                            theLinDeflection,
                                    const double                            theAngDeflection,
                                    const int                               theMinPointsNb = 2,
                                    const double theMinSize = Precision::Confusion());

  int AddPoint(const gp_Pnt& thePoint, const double theParam, const bool theIsReplace = true)
  {
    return myDiscretTool.AddPoint(thePoint, theParam, theIsReplace);
  }

  int NbPoints() const { return myDiscretTool.NbPoints(); }

  Standard_EXPORT bool Value(const int    theIndex,
                             const double theIsoParam,
                             double&      theParam,
                             gp_Pnt&      thePoint,
                             gp_Pnt2d&    theUV) const;

  Standard_EXPORT bool Value(const int                               theIndex,
                             const occ::handle<BRepAdaptor_Surface>& theSurface,
                             double&                                 theParam,
                             gp_Pnt&                                 thePoint,
                             gp_Pnt2d&                               theUV) const;

public:
  Standard_EXPORT static bool Normal(const occ::handle<BRepAdaptor_Surface>& theSurface,
                                     const double                            theParamU,
                                     const double                            theParamV,
                                     gp_Pnt&                                 thePoint,
                                     gp_Dir&                                 theNormal);

  Standard_EXPORT static IntFlag IntLinLin(const gp_XY& theStartPnt1,
                                           const gp_XY& theEndPnt1,
                                           const gp_XY& theStartPnt2,
                                           const gp_XY& theEndPnt2,
                                           gp_XY&       theIntPnt,
                                           double (&theParamOnSegment)[2]);

  Standard_EXPORT static IntFlag IntSegSeg(const gp_XY& theStartPnt1,
                                           const gp_XY& theEndPnt1,
                                           const gp_XY& theStartPnt2,
                                           const gp_XY& theEndPnt2,
                                           const bool   isConsiderEndPointTouch,
                                           const bool   isConsiderPointOnSegment,
                                           gp_Pnt2d&    theIntPnt);

  static double SquareDeflectionOfSegment(const gp_Pnt& theFirstPoint,
                                          const gp_Pnt& theLastPoint,
                                          const gp_Pnt& theMidPoint)
  {

    if (theFirstPoint.SquareDistance(theLastPoint) > Precision::SquareConfusion())
    {
      gp_Lin aLin(theFirstPoint, gp_Dir(gp_Vec(theFirstPoint, theLastPoint)));
      return aLin.SquareDistance(theMidPoint);
    }

    return theFirstPoint.SquareDistance(theMidPoint);
  }

  Standard_EXPORT static std::pair<int, int> CellsCount(
    const occ::handle<Adaptor3d_Surface>& theSurface,
    const int                             theVerticesNb,
    const double                          theDeflection,
    const BRepMesh_DefaultRangeSplitter*  theRangeSplitter);

private:
  static int classifyPoint(const gp_XY& thePoint1,
                           const gp_XY& thePoint2,
                           const gp_XY& thePointToCheck);

private:
  const TopoDS_Edge*          myEdge;
  GCPnts_TangentialDeflection myDiscretTool;
  GeomAbs_IsoType             myIsoType;
};
