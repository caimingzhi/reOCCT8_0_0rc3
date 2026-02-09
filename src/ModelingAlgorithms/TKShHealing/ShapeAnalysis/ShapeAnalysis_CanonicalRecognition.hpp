#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Edge.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomConvert_ConvType.hpp>
#include <NCollection_Array1.hpp>

class gp_Pln;
class gp_Cone;
class gp_Cylinder;
class gp_Sphere;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class Geom_Curve;
class Geom_Surface;

class ShapeAnalysis_CanonicalRecognition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_CanonicalRecognition();

  Standard_EXPORT ShapeAnalysis_CanonicalRecognition(const TopoDS_Shape& theShape);

  Standard_EXPORT void SetShape(const TopoDS_Shape& theShape);

  const TopoDS_Shape& GetShape() const { return myShape; }

  double GetGap() const { return myGap; }

  int GetStatus() const { return myStatus; }

  void ClearStatus() { myStatus = 0; }

  Standard_EXPORT bool IsPlane(const double theTol, gp_Pln& thePln);

  Standard_EXPORT bool IsCylinder(const double theTol, gp_Cylinder& theCyl);

  Standard_EXPORT bool IsCone(const double theTol, gp_Cone& theCone);

  Standard_EXPORT bool IsSphere(const double theTol, gp_Sphere& theSphere);

  Standard_EXPORT bool IsLine(const double theTol, gp_Lin& theLin);

  Standard_EXPORT bool IsCircle(const double theTol, gp_Circ& theCirc);

  Standard_EXPORT bool IsEllipse(const double theTol, gp_Elips& theElips);

private:
  bool IsElementarySurf(const GeomAbs_SurfaceType   theTarget,
                        const double                theTol,
                        gp_Ax3&                     thePos,
                        NCollection_Array1<double>& theParams);

  bool IsConic(const GeomAbs_CurveType     theTarget,
               const double                theTol,
               gp_Ax2&                     thePos,
               NCollection_Array1<double>& theParams);

  static occ::handle<Geom_Surface> GetSurface(const TopoDS_Face&         theFace,
                                              const double               theTol,
                                              const GeomConvert_ConvType theType,
                                              const GeomAbs_SurfaceType  theTarget,
                                              double&                    theGap,
                                              int&                       theStatus);

  static occ::handle<Geom_Surface> GetSurface(const TopoDS_Shell&        theShell,
                                              const double               theTol,
                                              const GeomConvert_ConvType theType,
                                              const GeomAbs_SurfaceType  theTarget,
                                              double&                    theGap,
                                              int&                       theStatus);

  static occ::handle<Geom_Surface> GetSurface(const TopoDS_Edge&          theEdge,
                                              const double                theTol,
                                              const GeomConvert_ConvType  theType,
                                              const GeomAbs_SurfaceType   theTarget,
                                              gp_Ax3&                     thePos,
                                              NCollection_Array1<double>& theParams,
                                              double&                     theGap,
                                              int&                        theStatus);

  static occ::handle<Geom_Surface> GetSurface(const TopoDS_Wire&          theWire,
                                              const double                theTol,
                                              const GeomConvert_ConvType  theType,
                                              const GeomAbs_SurfaceType   theTarget,
                                              gp_Ax3&                     thePos,
                                              NCollection_Array1<double>& theParams,
                                              double&                     theGap,
                                              int&                        theStatus);

  static occ::handle<Geom_Curve> GetCurve(const TopoDS_Edge&         theEdge,
                                          const double               theTol,
                                          const GeomConvert_ConvType theType,
                                          const GeomAbs_CurveType    theTarget,
                                          double&                    theGap,
                                          int&                       theStatus);

  static bool GetSurfaceByLS(const TopoDS_Wire&          theWire,
                             const double                theTol,
                             const GeomAbs_SurfaceType   theTarget,
                             gp_Ax3&                     thePos,
                             NCollection_Array1<double>& theParams,
                             double&                     theGap,
                             int&                        theStatus);

  void Init(const TopoDS_Shape& theShape);

private:
  TopoDS_Shape     myShape;
  TopAbs_ShapeEnum mySType;
  double           myGap;
  int              myStatus;
};
