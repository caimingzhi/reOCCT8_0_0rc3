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

class ShapeAnalysis_TransferParametersProj : public ShapeAnalysis_TransferParameters
{

public:
  Standard_EXPORT ShapeAnalysis_TransferParametersProj();

  Standard_EXPORT ShapeAnalysis_TransferParametersProj(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Edge& E, const TopoDS_Face& F) override;

  Standard_EXPORT occ::handle<NCollection_HSequence<double>> Perform(
    const occ::handle<NCollection_HSequence<double>>& Papams,
    const bool                                        To2d) override;

  Standard_EXPORT double Perform(const double Param, const bool To2d) override;

  Standard_EXPORT bool& ForceProjection();

  Standard_EXPORT void TransferRange(TopoDS_Edge& newEdge,
                                     const double prevPar,
                                     const double currPar,
                                     const bool   Is2d) override;

  Standard_EXPORT bool IsSameRange() const override;

  Standard_EXPORT static TopoDS_Vertex CopyNMVertex(const TopoDS_Vertex& theVert,
                                                    const TopoDS_Edge&   toedge,
                                                    const TopoDS_Edge&   fromedge);

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
