#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <TopLoc_Location.hpp>
#include <ShapeAnalysis_TransferParameters.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Geom_Curve;
class Geom2d_Curve;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Vertex;

//! This tool is used for transferring parameters
//! from 3d curve of the edge to pcurve and vice versa.
//! This tool transfers parameters with help of
//! projection points from curve 3d on curve 2d and
//! vice versa
class ShapeAnalysis_TransferParametersProj : public ShapeAnalysis_TransferParameters
{

public:
  //! Creates empty constructor.
  Standard_EXPORT ShapeAnalysis_TransferParametersProj();

  Standard_EXPORT ShapeAnalysis_TransferParametersProj(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Edge& E, const TopoDS_Face& F) override;

  //! Transfers parameters given by sequence Params from 3d curve
  //! to pcurve (if To2d is True) or back (if To2d is False)
  Standard_EXPORT occ::handle<NCollection_HSequence<double>> Perform(
    const occ::handle<NCollection_HSequence<double>>& Papams,
    const bool                                        To2d) override;

  //! Transfers parameter given by Param from 3d curve
  //! to pcurve (if To2d is True) or back (if To2d is False)
  Standard_EXPORT double Perform(const double Param, const bool To2d) override;

  //! Returns modifiable flag forcing projection
  //! If it is False (default), projection is done only
  //! if edge is not SameParameter or if tolerance of edge
  //! is greater than MaxTolerance()
  Standard_EXPORT bool& ForceProjection();

  //! Recomputes range of curves from NewEdge.
  //! If Is2d equals True parameters are recomputed by curve2d else by curve3d.
  Standard_EXPORT void TransferRange(TopoDS_Edge& newEdge,
                                     const double prevPar,
                                     const double currPar,
                                     const bool   Is2d) override;

  //! Returns False;
  Standard_EXPORT bool IsSameRange() const override;

  //! Make a copy of non-manifold vertex theVert
  //! (i.e. create new TVertex and replace PointRepresentations for this vertex
  //! from fromedge to toedge. Other representations were copied)
  Standard_EXPORT static TopoDS_Vertex CopyNMVertex(const TopoDS_Vertex& theVert,
                                                    const TopoDS_Edge&   toedge,
                                                    const TopoDS_Edge&   fromedge);

  //! Make a copy of non-manifold vertex theVert
  //! (i.e. create new TVertex and replace PointRepresentations for this vertex
  //! from fromFace to toFace. Other representations were copied)
  Standard_EXPORT static TopoDS_Vertex CopyNMVertex(const TopoDS_Vertex& theVert,
                                                    const TopoDS_Face&   toFace,
                                                    const TopoDS_Face&   fromFace);

  DEFINE_STANDARD_RTTIEXT(ShapeAnalysis_TransferParametersProj, ShapeAnalysis_TransferParameters)

private:
  Standard_EXPORT double PreformSegment(const double Param,
                                        const bool   To2d,
                                        const double First,
                                        const double Last);

  occ::handle<Geom_Curve>   myCurve;
  occ::handle<Geom2d_Curve> myCurve2d;
  Adaptor3d_CurveOnSurface  myAC3d;
  double                    myPrecision;
  TopLoc_Location           myLocation;
  bool                      myForceProj;
  bool                      myInitOK;
};

