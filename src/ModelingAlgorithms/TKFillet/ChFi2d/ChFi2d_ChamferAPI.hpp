#pragma once

#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <Geom_Curve.hpp>

//! A class making a chamfer between two linear edges.
class ChFi2d_ChamferAPI
{
public:
  //! An empty constructor.
  Standard_EXPORT ChFi2d_ChamferAPI();

  //! A constructor accepting a wire consisting of two linear edges.
  Standard_EXPORT ChFi2d_ChamferAPI(const TopoDS_Wire& theWire);

  //! A constructor accepting two linear edges.
  Standard_EXPORT ChFi2d_ChamferAPI(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2);

  //! Initializes the class by a wire consisting of two libear edges.
  Standard_EXPORT void Init(const TopoDS_Wire& theWire);

  //! Initializes the class by two linear edges.
  Standard_EXPORT void Init(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2);

  //! Constructs a chamfer edge.
  //! Returns true if the edge is constructed.
  Standard_EXPORT bool Perform();

  // Returns the result (chamfer edge, modified edge1, modified edge2).
  Standard_EXPORT TopoDS_Edge Result(TopoDS_Edge& theEdge1,
                                     TopoDS_Edge& theEdge2,
                                     const double theLength1,
                                     const double theLength2);

private:
  TopoDS_Edge             myEdge1, myEdge2;
  occ::handle<Geom_Curve> myCurve1, myCurve2;
  double                  myStart1, myEnd1, myStart2, myEnd2;
  bool                    myCommonStart1, myCommonStart2;
};
