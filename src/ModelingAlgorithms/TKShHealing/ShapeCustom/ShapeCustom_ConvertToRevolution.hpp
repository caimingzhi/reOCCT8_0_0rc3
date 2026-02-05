#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeCustom_Modification.hpp>
#include <GeomAbs_Shape.hpp>
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Vertex;
class gp_Pnt;
class Geom2d_Curve;

//! implements a modification for the BRepTools
//! Modifier algorithm. Converts all elementary
//! surfaces into surfaces of revolution.
class ShapeCustom_ConvertToRevolution : public ShapeCustom_Modification
{

public:
  Standard_EXPORT ShapeCustom_ConvertToRevolution();

  //! Returns true if the face <F> has been
  //! modified. In this case, <S> is the new geometric
  //! support of the face, <L> the new location, <Tol>
  //! the new tolerance. Otherwise, returns
  //! false, and <S>, <L>, <Tol> are not
  //! significant.
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

  DEFINE_STANDARD_RTTIEXT(ShapeCustom_ConvertToRevolution, ShapeCustom_Modification)
};
