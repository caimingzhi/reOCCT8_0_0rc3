#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeCustom_Modification.hpp>
class ShapeCustom_RestrictionParameters;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class TopoDS_Edge;
class Geom_Curve;
class Geom2d_Curve;
class TopoDS_Vertex;
class gp_Pnt;

class ShapeCustom_BSplineRestriction : public ShapeCustom_Modification
{

public:
  Standard_EXPORT ShapeCustom_BSplineRestriction();

  Standard_EXPORT ShapeCustom_BSplineRestriction(const bool          anApproxSurfaceFlag,
                                                 const bool          anApproxCurve3dFlag,
                                                 const bool          anApproxCurve2dFlag,
                                                 const double        aTol3d,
                                                 const double        aTol2d,
                                                 const GeomAbs_Shape aContinuity3d,
                                                 const GeomAbs_Shape aContinuity2d,
                                                 const int           aMaxDegree,
                                                 const int           aNbMaxSeg,
                                                 const bool          Degree,
                                                 const bool          Rational);

  Standard_EXPORT ShapeCustom_BSplineRestriction(
    const bool                                            anApproxSurfaceFlag,
    const bool                                            anApproxCurve3dFlag,
    const bool                                            anApproxCurve2dFlag,
    const double                                          aTol3d,
    const double                                          aTol2d,
    const GeomAbs_Shape                                   aContinuity3d,
    const GeomAbs_Shape                                   aContinuity2d,
    const int                                             aMaxDegree,
    const int                                             aNbMaxSeg,
    const bool                                            Degree,
    const bool                                            Rational,
    const occ::handle<ShapeCustom_RestrictionParameters>& aModes);

  Standard_EXPORT bool NewSurface(const TopoDS_Face&         F,
                                  occ::handle<Geom_Surface>& S,
                                  TopLoc_Location&           L,
                                  double&                    Tol,
                                  bool&                      RevWires,
                                  bool&                      RevFace) override;

  Standard_EXPORT bool NewCurve(const TopoDS_Edge&       E,
                                occ::handle<Geom_Curve>& C,
                                TopLoc_Location&         L,
                                double&                  Tol) override;

  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         E,
                                  const TopoDS_Face&         F,
                                  const TopoDS_Edge&         NewE,
                                  const TopoDS_Face&         NewF,
                                  occ::handle<Geom2d_Curve>& C,
                                  double&                    Tol) override;

  Standard_EXPORT bool ConvertSurface(const occ::handle<Geom_Surface>& aSurface,
                                      occ::handle<Geom_Surface>&       S,
                                      const double                     UF,
                                      const double                     UL,
                                      const double                     VF,
                                      const double                     VL,
                                      const bool                       IsOf = true);

  Standard_EXPORT bool ConvertCurve(const occ::handle<Geom_Curve>& aCurve,
                                    occ::handle<Geom_Curve>&       C,
                                    const bool                     IsConvert,
                                    const double                   First,
                                    const double                   Last,
                                    double&                        TolCur,
                                    const bool                     IsOf = true);

  Standard_EXPORT bool ConvertCurve2d(const occ::handle<Geom2d_Curve>& aCurve,
                                      occ::handle<Geom2d_Curve>&       C,
                                      const bool                       IsConvert,
                                      const double                     First,
                                      const double                     Last,
                                      double&                          TolCur,
                                      const bool                       IsOf = true);

  void SetTol3d(const double Tol3d);

  void SetTol2d(const double Tol2d);

  bool& ModifyApproxSurfaceFlag();

  bool& ModifyApproxCurve3dFlag();

  bool& ModifyApproxCurve2dFlag();

  void SetContinuity3d(const GeomAbs_Shape Continuity3d);

  void SetContinuity2d(const GeomAbs_Shape Continuity2d);

  void SetMaxDegree(const int MaxDegree);

  void SetMaxNbSegments(const int MaxNbSegments);

  void SetPriority(const bool Degree);

  void SetConvRational(const bool Rational);

  occ::handle<ShapeCustom_RestrictionParameters> GetRestrictionParameters() const;

  void SetRestrictionParameters(const occ::handle<ShapeCustom_RestrictionParameters>& aModes);

  double Curve3dError() const;

  double Curve2dError() const;

  double SurfaceError() const;

  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) override;

  Standard_EXPORT bool NewParameter(const TopoDS_Vertex& V,
                                    const TopoDS_Edge&   E,
                                    double&              P,
                                    double&              Tol) override;

  Standard_EXPORT GeomAbs_Shape Continuity(const TopoDS_Edge& E,
                                           const TopoDS_Face& F1,
                                           const TopoDS_Face& F2,
                                           const TopoDS_Edge& NewE,
                                           const TopoDS_Face& NewF1,
                                           const TopoDS_Face& NewF2) override;

  Standard_EXPORT double MaxErrors(double& aCurve3dErr, double& aCurve2dErr) const;

  Standard_EXPORT int NbOfSpan() const;

  DEFINE_STANDARD_RTTIEXT(ShapeCustom_BSplineRestriction, ShapeCustom_Modification)

private:
  GeomAbs_Shape                                  myContinuity3d;
  GeomAbs_Shape                                  myContinuity2d;
  int                                            myMaxDegree;
  int                                            myNbMaxSeg;
  double                                         myTol3d;
  double                                         myTol2d;
  double                                         mySurfaceError;
  double                                         myCurve3dError;
  double                                         myCurve2dError;
  int                                            myNbOfSpan;
  bool                                           myApproxSurfaceFlag;
  bool                                           myApproxCurve3dFlag;
  bool                                           myApproxCurve2dFlag;
  bool                                           myDeg;
  bool                                           myConvert;
  bool                                           myRational;
  occ::handle<ShapeCustom_RestrictionParameters> myParameters;
};

inline void ShapeCustom_BSplineRestriction::SetTol3d(const double Tol3d)
{
  myTol3d = Tol3d;
}

inline void ShapeCustom_BSplineRestriction::SetTol2d(const double Tol2d)
{
  myTol2d = Tol2d;
}

inline bool& ShapeCustom_BSplineRestriction::ModifyApproxSurfaceFlag()
{

  return myApproxSurfaceFlag;
}

inline bool& ShapeCustom_BSplineRestriction::ModifyApproxCurve3dFlag()
{
  return myApproxCurve3dFlag;
}

inline bool& ShapeCustom_BSplineRestriction::ModifyApproxCurve2dFlag()
{
  return myApproxCurve2dFlag;
}

inline void ShapeCustom_BSplineRestriction::SetContinuity3d(const GeomAbs_Shape Continuity3d)
{
  myContinuity3d = Continuity3d;
}

inline void ShapeCustom_BSplineRestriction::SetContinuity2d(const GeomAbs_Shape Continuity2d)
{
  myContinuity2d = Continuity2d;
}

inline void ShapeCustom_BSplineRestriction::SetMaxDegree(const int MaxDegree)
{
  myMaxDegree = MaxDegree;
}

inline void ShapeCustom_BSplineRestriction::SetMaxNbSegments(const int MaxNbSegments)
{
  myNbMaxSeg = MaxNbSegments;
}

inline double ShapeCustom_BSplineRestriction::Curve3dError() const
{
  return myCurve3dError;
}

inline double ShapeCustom_BSplineRestriction::Curve2dError() const
{
  return myCurve2dError;
}

inline double ShapeCustom_BSplineRestriction::SurfaceError() const
{
  return mySurfaceError;
}

inline void ShapeCustom_BSplineRestriction::SetPriority(const bool Degree)
{
  myDeg = Degree;
}

inline void ShapeCustom_BSplineRestriction::SetConvRational(const bool Rational)
{
  myRational = Rational;
}

inline occ::handle<ShapeCustom_RestrictionParameters> ShapeCustom_BSplineRestriction::
  GetRestrictionParameters() const
{
  return myParameters;
}

inline void ShapeCustom_BSplineRestriction::SetRestrictionParameters(
  const occ::handle<ShapeCustom_RestrictionParameters>& aModes)
{
  myParameters = aModes;
}
