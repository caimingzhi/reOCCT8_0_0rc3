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

  //! Resets on the same shape.
  Standard_EXPORT void Clear();

  //! Changes the basis shape and resets.
  Standard_EXPORT void Init(const TopoDS_Shape& S);

  //! Adds the face F and propagates the draft
  //! modification to its neighbour faces if they are
  //! tangent. If an error occurs, will return False and
  //! ProblematicShape will return the "bad" face.
  Standard_EXPORT bool Add(const TopoDS_Face& F,
                           const gp_Dir&      Direction,
                           const double       Angle,
                           const gp_Pln&      NeutralPlane,
                           const bool         Flag = true);

  //! Removes the face F and the neighbour faces if they
  //! are tangent. It will be necessary to call this
  //! method if the method Add returns false,
  //! to unset ProblematicFace.
  Standard_EXPORT void Remove(const TopoDS_Face& F);

  //! Performs the draft angle modification and sets the
  //! value returned by the method IsDone. If an error
  //! occurs, IsDone will return false, and an
  //! error status will be given by the method Error,
  //! and the shape on which the problem appeared will
  //! be given by ProblematicShape
  Standard_EXPORT void Perform();

  //! Returns True if Perform has been successfully
  //! called. Otherwise more information can be obtained
  //! using the methods Error() and ProblematicShape().
  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT Draft_ErrorStatus Error() const;

  //! Returns the shape (Face, Edge or Vertex) on which
  //! an error occurred.
  Standard_EXPORT const TopoDS_Shape& ProblematicShape() const;

  //! Returns all the faces which have been added
  //! together with the face <F>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ConnectedFaces(const TopoDS_Face& F);

  //! Returns all the faces on which a modification has
  //! been given.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ModifiedFaces();

  //! Returns true if the face <F> has been
  //! modified. In this case, <S> is the new geometric
  //! support of the face, <L> the new location, <Tol>
  //! the new tolerance.<RevWires> has to be set to
  //! true when the modification reverses the
  //! normal of the surface. (the wires have to be
  //! reversed). <RevFace> has to be set to
  //! true if the orientation of the modified
  //! face changes in the shells which contain it. Here
  //! it will be set to false.
  //!
  //! Otherwise, returns false, and <S>, <L>,
  //! <Tol> , <RevWires> ,<RevFace> are not significant.
  Standard_EXPORT bool NewSurface(const TopoDS_Face&         F,
                                  occ::handle<Geom_Surface>& S,
                                  TopLoc_Location&           L,
                                  double&                    Tol,
                                  bool&                      RevWires,
                                  bool&                      RevFace) override;

  //! Returns true if the edge <E> has been
  //! modified. In this case, <C> is the new geometric
  //! support of the edge, <L> the new location, <Tol>
  //! the new tolerance. Otherwise, returns
  //! false, and <C>, <L>, <Tol> are not
  //! significant.
  Standard_EXPORT bool NewCurve(const TopoDS_Edge&       E,
                                occ::handle<Geom_Curve>& C,
                                TopLoc_Location&         L,
                                double&                  Tol) override;

  //! Returns true if the vertex <V> has been
  //! modified. In this case, <P> is the new geometric
  //! support of the vertex, <Tol> the new tolerance.
  //! Otherwise, returns false, and <P>, <Tol>
  //! are not significant.
  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) override;

  //! Returns true if the edge <E> has a new
  //! curve on surface on the face <F>.In this case, <C>
  //! is the new geometric support of the edge, <L> the
  //! new location, <Tol> the new tolerance.
  //!
  //! Otherwise, returns false, and <C>, <L>,
  //! <Tol> are not significant.
  //!
  //! <NewE> is the new edge created from <E>. <NewF>
  //! is the new face created from <F>. They may be useful.
  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         E,
                                  const TopoDS_Face&         F,
                                  const TopoDS_Edge&         NewE,
                                  const TopoDS_Face&         NewF,
                                  occ::handle<Geom2d_Curve>& C,
                                  double&                    Tol) override;

  //! Returns true if the Vertex <V> has a new
  //! parameter on the edge <E>. In this case, <P> is
  //! the parameter, <Tol> the new tolerance.
  //! Otherwise, returns false, and <P>, <Tol>
  //! are not significant.
  Standard_EXPORT bool NewParameter(const TopoDS_Vertex& V,
                                    const TopoDS_Edge&   E,
                                    double&              P,
                                    double&              Tol) override;

  //! Returns the continuity of <NewE> between <NewF1>
  //! and <NewF2>.
  //!
  //! <NewE> is the new edge created from <E>. <NewF1>
  //! (resp. <NewF2>) is the new face created from <F1>
  //! (resp. <F2>).
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

