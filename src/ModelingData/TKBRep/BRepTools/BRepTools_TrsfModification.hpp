#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Trsf.hpp>
#include <BRepTools_Modification.hpp>
#include <GeomAbs_Shape.hpp>
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Vertex;
class gp_Pnt;
class Geom2d_Curve;

//! Describes a modification that uses a gp_Trsf to
//! change the geometry of a shape. All functions return
//! true and transform the geometry of the shape.
class BRepTools_TrsfModification : public BRepTools_Modification
{

public:
  Standard_EXPORT BRepTools_TrsfModification(const gp_Trsf& T);

  //! Provides access to the gp_Trsf associated with this
  //! modification. The transformation can be changed.
  Standard_EXPORT gp_Trsf& Trsf();

  //! Sets a flag to indicate the need to copy mesh.
  Standard_EXPORT bool& IsCopyMesh();

  //! Returns true if the face F has been modified.
  //! If the face has been modified:
  //! - S is the new geometry of the face,
  //! - L is its new location, and
  //! - Tol is the new tolerance.
  //! RevWires is set to true when the modification
  //! reverses the normal of the surface (the wires have to be reversed).
  //! RevFace is set to true if the orientation of the
  //! modified face changes in the shells which contain it.
  //! For this class, RevFace returns true if the gp_Trsf
  //! associated with this modification is negative.
  Standard_EXPORT bool NewSurface(const TopoDS_Face&         F,
                                  occ::handle<Geom_Surface>& S,
                                  TopLoc_Location&           L,
                                  double&                    Tol,
                                  bool&                      RevWires,
                                  bool&                      RevFace) override;

  //! Returns true if the face has been modified according to changed triangulation.
  //! If the face has been modified:
  //! - T is a new triangulation on the face
  Standard_EXPORT bool NewTriangulation(const TopoDS_Face&               F,
                                        occ::handle<Poly_Triangulation>& T) override;

  //! Returns true if the edge has been modified according to changed polygon.
  //! If the edge has been modified:
  //! - P is a new polygon
  Standard_EXPORT bool NewPolygon(const TopoDS_Edge& E, occ::handle<Poly_Polygon3D>& P) override;

  //! Returns true if the edge has been modified according to changed polygon on triangulation.
  //! If the edge has been modified:
  //! - P is a new polygon on triangulation
  Standard_EXPORT bool NewPolygonOnTriangulation(
    const TopoDS_Edge&                        E,
    const TopoDS_Face&                        F,
    occ::handle<Poly_PolygonOnTriangulation>& P) override;

  //! Always returns true indicating that the edge E is always modified.
  //! - C is the new geometric support of the edge,
  //! - L is the new location, and
  //! - Tol is the new tolerance.
  Standard_EXPORT bool NewCurve(const TopoDS_Edge&       E,
                                occ::handle<Geom_Curve>& C,
                                TopLoc_Location&         L,
                                double&                  Tol) override;

  //! Returns true if the vertex V has been modified.
  //! If the vertex has been modified:
  //! - P is the new geometry of the vertex, and
  //! - Tol is the new tolerance.
  //! If the vertex has not been modified this function
  //! returns false, and the values of P and Tol are not significant.
  Standard_EXPORT bool NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol) override;

  //! Returns true if the edge E has a new curve on surface on the face F.
  //! If a new curve exists:
  //! - C is the new geometric support of the edge,
  //! - L is the new location, and
  //! - Tol the new tolerance.
  //! If no new curve exists, this function returns false, and
  //! the values of C, L and Tol are not significant.
  Standard_EXPORT bool NewCurve2d(const TopoDS_Edge&         E,
                                  const TopoDS_Face&         F,
                                  const TopoDS_Edge&         NewE,
                                  const TopoDS_Face&         NewF,
                                  occ::handle<Geom2d_Curve>& C,
                                  double&                    Tol) override;

  //! Returns true if the Vertex V has a new parameter on the edge E.
  //! If a new parameter exists:
  //! - P is the parameter, and
  //! - Tol is the new tolerance.
  //! If no new parameter exists, this function returns false,
  //! and the values of P and Tol are not significant.
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

  DEFINE_STANDARD_RTTIEXT(BRepTools_TrsfModification, BRepTools_Modification)

private:
  gp_Trsf myTrsf;
  bool    myCopyMesh;
};

