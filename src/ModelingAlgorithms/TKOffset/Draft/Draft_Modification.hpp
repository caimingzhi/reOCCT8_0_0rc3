#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <Draft_FaceInfo.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <Draft_EdgeInfo.hpp>
#include <TopoDS_Vertex.hpp>
#include <Draft_VertexInfo.hpp>
#include <TopoDS_Shape.hpp>
#include <Draft_ErrorStatus.hpp>
#include <NCollection_List.hpp>
#include <BRepTools_Modification.hpp>
#include <GeomAbs_Shape.hpp>
#include <TopAbs_Orientation.hpp>
class gp_Dir;
class gp_Pln;
class Geom_Surface;
class TopLoc_Location;
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Vertex;
class gp_Pnt;
class Geom2d_Curve;

class Draft_Modification : public BRepTools_Modification
{

public:
  Standard_EXPORT Draft_Modification(const TopoDS_Shape& S);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT bool Add(const TopoDS_Face& F,
                           const gp_Dir&      Direction,
                           const double       Angle,
                           const gp_Pln&      NeutralPlane,
                           const bool         Flag = true);

  Standard_EXPORT void Remove(const TopoDS_Face& F);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT Draft_ErrorStatus Error() const;

  Standard_EXPORT const TopoDS_Shape& ProblematicShape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ConnectedFaces(const TopoDS_Face& F);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ModifiedFaces();

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

  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) override;

  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         E,
                                  const TopoDS_Face&         F,
                                  const TopoDS_Edge&         NewE,
                                  const TopoDS_Face&         NewF,
                                  occ::handle<Geom2d_Curve>& C,
                                  double&                    Tol) override;

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

  DEFINE_STANDARD_RTTIEXT(Draft_Modification, BRepTools_Modification)

private:
  Standard_EXPORT bool InternalAdd(const TopoDS_Face& F,
                                   const gp_Dir&      Direction,
                                   const double       Angle,
                                   const gp_Pln&      NeutralPlane,
                                   const bool         Flag = true);

  Standard_EXPORT bool Propagate();

  Standard_EXPORT occ::handle<Geom_Curve> NewCurve(const occ::handle<Geom_Curve>&   C,
                                                   const occ::handle<Geom_Surface>& S,
                                                   const TopAbs_Orientation         OriS,
                                                   const gp_Dir&                    Direction,
                                                   const double                     Angle,
                                                   const gp_Pln&                    NeutralPlane,
                                                   const bool                       Flag = true);

  Standard_EXPORT occ::handle<Geom_Surface> NewSurface(const occ::handle<Geom_Surface>& S,
                                                       const TopAbs_Orientation         OriS,
                                                       const gp_Dir&                    Direction,
                                                       const double                     Angle,
                                                       const gp_Pln& NeutralPlane);

  NCollection_IndexedDataMap<TopoDS_Face, Draft_FaceInfo, TopTools_ShapeMapHasher>     myFMap;
  NCollection_IndexedDataMap<TopoDS_Edge, Draft_EdgeInfo, TopTools_ShapeMapHasher>     myEMap;
  NCollection_IndexedDataMap<TopoDS_Vertex, Draft_VertexInfo, TopTools_ShapeMapHasher> myVMap;
  bool                                                                                 myComp;
  TopoDS_Shape                                                                         myShape;
  TopoDS_Shape                                                                         badShape;
  Draft_ErrorStatus                                                                    errStat;
  TopoDS_Face                                                                          curFace;
  NCollection_List<TopoDS_Shape>                                                       conneF;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myEFMap;
};
