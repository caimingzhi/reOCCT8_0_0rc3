#pragma once

#include <ChFi2d_FilletAlgo.hpp>
#include <ChFi2d_AnaFilletAlgo.hpp>

class ChFi2d_FilletAPI
{
public:
  Standard_EXPORT ChFi2d_FilletAPI();

  Standard_EXPORT ChFi2d_FilletAPI(const TopoDS_Wire& theWire, const gp_Pln& thePlane);

  Standard_EXPORT ChFi2d_FilletAPI(const TopoDS_Edge& theEdge1,
                                   const TopoDS_Edge& theEdge2,
                                   const gp_Pln&      thePlane);

  Standard_EXPORT void Init(const TopoDS_Wire& theWire, const gp_Pln& thePlane);

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge1,
                            const TopoDS_Edge& theEdge2,
                            const gp_Pln&      thePlane);

  Standard_EXPORT bool Perform(const double theRadius);

  Standard_EXPORT int NbResults(const gp_Pnt& thePoint);

  Standard_EXPORT TopoDS_Edge Result(const gp_Pnt& thePoint,
                                     TopoDS_Edge&  theEdge1,
                                     TopoDS_Edge&  theEdge2,
                                     const int     iSolution = -1);

private:
  bool IsAnalytical(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2);

  ChFi2d_FilletAlgo    myFilletAlgo;
  ChFi2d_AnaFilletAlgo myAnaFilletAlgo;
  bool                 myIsAnalytical;
};
