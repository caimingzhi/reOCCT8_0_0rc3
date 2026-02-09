#pragma once

#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <Geom_Curve.hpp>

class ChFi2d_ChamferAPI
{
public:
  Standard_EXPORT ChFi2d_ChamferAPI();

  Standard_EXPORT ChFi2d_ChamferAPI(const TopoDS_Wire& theWire);

  Standard_EXPORT ChFi2d_ChamferAPI(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2);

  Standard_EXPORT void Init(const TopoDS_Wire& theWire);

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2);

  Standard_EXPORT bool Perform();

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
