#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DataMap.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <Standard_Integer.hpp>
#include <Precision.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_State.hpp>
#include <BRepAdaptor_Surface.hpp>
class IntTools_FClass2d;
class TopoDS_Face;
class GeomAPI_ProjectPointOnSurf;
class GeomAPI_ProjectPointOnCurve;
class TopoDS_Edge;
class Geom_Curve;
class IntTools_SurfaceRangeLocalizeData;
class BRepClass3d_SolidClassifier;
class TopoDS_Solid;
class Geom2dHatch_Hatcher;
class gp_Pnt;
class TopoDS_Vertex;
class gp_Pnt2d;
class IntTools_Curve;
class Bnd_Box;
class Bnd_OBB;

class IntTools_Context : public Standard_Transient
{
public:
  Standard_EXPORT IntTools_Context();
  Standard_EXPORT ~IntTools_Context() override;

  Standard_EXPORT IntTools_Context(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT IntTools_FClass2d& FClass2d(const TopoDS_Face& aF);

  Standard_EXPORT GeomAPI_ProjectPointOnSurf& ProjPS(const TopoDS_Face& aF);

  Standard_EXPORT GeomAPI_ProjectPointOnCurve& ProjPC(const TopoDS_Edge& aE);

  Standard_EXPORT GeomAPI_ProjectPointOnCurve& ProjPT(const occ::handle<Geom_Curve>& aC);

  Standard_EXPORT IntTools_SurfaceRangeLocalizeData& SurfaceData(const TopoDS_Face& aF);

  Standard_EXPORT BRepClass3d_SolidClassifier& SolidClassifier(const TopoDS_Solid& aSolid);

  Standard_EXPORT Geom2dHatch_Hatcher& Hatcher(const TopoDS_Face& aF);

  Standard_EXPORT BRepAdaptor_Surface& SurfaceAdaptor(const TopoDS_Face& theFace);

  Standard_EXPORT Bnd_OBB& OBB(const TopoDS_Shape& theShape,
                               const double        theFuzzyValue = Precision::Confusion());

  Standard_EXPORT void UVBounds(const TopoDS_Face& theFace,
                                double&            UMin,
                                double&            UMax,
                                double&            VMin,
                                double&            VMax);

  Standard_EXPORT int ComputePE(const gp_Pnt&      theP,
                                const double       theTolP,
                                const TopoDS_Edge& theE,
                                double&            theT,
                                double&            theDist);

  Standard_EXPORT int ComputeVE(const TopoDS_Vertex& theV,
                                const TopoDS_Edge&   theE,
                                double&              theT,
                                double&              theTol,
                                const double         theFuzz = Precision::Confusion());

  Standard_EXPORT int ComputeVF(const TopoDS_Vertex& theVertex,
                                const TopoDS_Face&   theFace,
                                double&              theU,
                                double&              theV,
                                double&              theTol,
                                const double         theFuzz = Precision::Confusion());

  Standard_EXPORT TopAbs_State StatePointFace(const TopoDS_Face& aF, const gp_Pnt2d& aP2D);

  Standard_EXPORT bool IsPointInFace(const TopoDS_Face& aF, const gp_Pnt2d& aP2D);

  Standard_EXPORT bool IsPointInFace(const gp_Pnt& aP3D, const TopoDS_Face& aF, const double aTol);

  Standard_EXPORT bool IsPointInOnFace(const TopoDS_Face& aF, const gp_Pnt2d& aP2D);

  Standard_EXPORT bool IsValidPointForFace(const gp_Pnt&      aP3D,
                                           const TopoDS_Face& aF,
                                           const double       aTol);

  Standard_EXPORT bool IsValidPointForFaces(const gp_Pnt&      aP3D,
                                            const TopoDS_Face& aF1,
                                            const TopoDS_Face& aF2,
                                            const double       aTol);

  Standard_EXPORT bool IsValidBlockForFace(const double          aT1,
                                           const double          aT2,
                                           const IntTools_Curve& aIC,
                                           const TopoDS_Face&    aF,
                                           const double          aTol);

  Standard_EXPORT bool IsValidBlockForFaces(const double          aT1,
                                            const double          aT2,
                                            const IntTools_Curve& aIC,
                                            const TopoDS_Face&    aF1,
                                            const TopoDS_Face&    aF2,
                                            const double          aTol);

  Standard_EXPORT bool IsVertexOnLine(const TopoDS_Vertex&  aV,
                                      const IntTools_Curve& aIC,
                                      const double          aTolC,
                                      double&               aT);

  Standard_EXPORT bool IsVertexOnLine(const TopoDS_Vertex&  aV,
                                      const double          aTolV,
                                      const IntTools_Curve& aIC,
                                      const double          aTolC,
                                      double&               aT);

  Standard_EXPORT bool ProjectPointOnEdge(const gp_Pnt& aP, const TopoDS_Edge& aE, double& aT);

  Standard_EXPORT Bnd_Box& BndBox(const TopoDS_Shape& theS);

  Standard_EXPORT bool IsInfiniteFace(const TopoDS_Face& theFace);

  Standard_EXPORT void SetPOnSProjectionTolerance(const double theValue);

  DEFINE_STANDARD_RTTIEXT(IntTools_Context, Standard_Transient)

protected:
  occ::handle<NCollection_BaseAllocator>                                         myAllocator;
  NCollection_DataMap<TopoDS_Shape, IntTools_FClass2d*, TopTools_ShapeMapHasher> myFClass2dMap;
  NCollection_DataMap<TopoDS_Shape, GeomAPI_ProjectPointOnSurf*, TopTools_ShapeMapHasher>
    myProjPSMap;
  NCollection_DataMap<TopoDS_Shape, GeomAPI_ProjectPointOnCurve*, TopTools_ShapeMapHasher>
    myProjPCMap;
  NCollection_DataMap<TopoDS_Shape, BRepClass3d_SolidClassifier*, TopTools_ShapeMapHasher>
                                                                                   mySClassMap;
  NCollection_DataMap<occ::handle<Geom_Curve>, GeomAPI_ProjectPointOnCurve*>       myProjPTMap;
  NCollection_DataMap<TopoDS_Shape, Geom2dHatch_Hatcher*, TopTools_ShapeMapHasher> myHatcherMap;
  NCollection_DataMap<TopoDS_Shape, IntTools_SurfaceRangeLocalizeData*, TopTools_ShapeMapHasher>
                                                                                   myProjSDataMap;
  NCollection_DataMap<TopoDS_Shape, Bnd_Box*, TopTools_ShapeMapHasher>             myBndBoxDataMap;
  NCollection_DataMap<TopoDS_Shape, BRepAdaptor_Surface*, TopTools_ShapeMapHasher> mySurfAdaptorMap;

  NCollection_DataMap<TopoDS_Shape, Bnd_OBB*, TopTools_ShapeMapHasher> myOBBMap;

  int    myCreateFlag;
  double myPOnSTolerance;

private:
  Standard_EXPORT void clearCachedPOnSProjectors();
};
