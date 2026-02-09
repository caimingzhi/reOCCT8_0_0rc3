#pragma once

#include <TopoDS_Wire.hpp>
#include <TopoDS_Edge.hpp>
#include <gp_Pln.hpp>

class ChFi2d_AnaFilletAlgo
{
public:
  Standard_EXPORT ChFi2d_AnaFilletAlgo();

  Standard_EXPORT ChFi2d_AnaFilletAlgo(const TopoDS_Wire& theWire, const gp_Pln& thePlane);

  Standard_EXPORT ChFi2d_AnaFilletAlgo(const TopoDS_Edge& theEdge1,
                                       const TopoDS_Edge& theEdge2,
                                       const gp_Pln&      thePlane);

  Standard_EXPORT void Init(const TopoDS_Wire& theWire, const gp_Pln& thePlane);

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge1,
                            const TopoDS_Edge& theEdge2,
                            const gp_Pln&      thePlane);

  Standard_EXPORT bool Perform(const double radius);

  Standard_EXPORT const TopoDS_Edge& Result(TopoDS_Edge& e1, TopoDS_Edge& e2);

private:
  bool SegmentFilletSegment(const double radius,
                            double&      xc,
                            double&      yc,
                            bool&        cw,
                            double&      start,
                            double&      end);

  bool SegmentFilletArc(const double radius,
                        double&      xc,
                        double&      yc,
                        bool&        cw,
                        double&      start,
                        double&      end,
                        double&      xend,
                        double&      yend);

  bool ArcFilletSegment(const double radius,
                        double&      xc,
                        double&      yc,
                        bool&        cw,
                        double&      start,
                        double&      end,
                        double&      xstart,
                        double&      ystart);

  bool ArcFilletArc(const double radius,
                    double&      xc,
                    double&      yc,
                    bool&        cw,
                    double&      start,
                    double&      end);

  bool Cut(const gp_Pln& plane, TopoDS_Edge& e1, TopoDS_Edge& e2);

  gp_Pln plane;

  TopoDS_Edge e1;
  bool        segment1;
  double      x11;
  double      y11;
  double      x12;
  double      y12;
  double      xc1;
  double      yc1;
  double      radius1;
  bool        cw1;

  TopoDS_Edge e2;
  bool        segment2;
  double      x21;
  double      y21;
  double      x22;
  double      y22;
  double      xc2;
  double      yc2;
  double      radius2;
  bool        cw2;

  TopoDS_Edge fillet;
  TopoDS_Edge shrinke1;
  TopoDS_Edge shrinke2;
};
