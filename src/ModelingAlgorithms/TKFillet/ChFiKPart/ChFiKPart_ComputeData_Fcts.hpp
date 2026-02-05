#pragma once

#include <Geom2d_BSplineCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>

double ChFiKPart_InPeriod(const double U,
                          const double UFirst,
                          const double ULast,
                          const double Eps);

occ::handle<Geom2d_BSplineCurve> ChFiKPart_PCurve(const gp_Pnt2d& UV1,
                                                  const gp_Pnt2d& UV2,
                                                  const double    Pardeb,
                                                  const double    Parfin);

void ChFiKPart_ProjPC(const GeomAdaptor_Curve&   Cg,
                      const GeomAdaptor_Surface& Sg,
                      occ::handle<Geom2d_Curve>& Pcurv);

Standard_EXPORT int ChFiKPart_IndexCurveInDS(const occ::handle<Geom_Curve>& C,
                                             TopOpeBRepDS_DataStructure&    DStr);

Standard_EXPORT int ChFiKPart_IndexSurfaceInDS(const occ::handle<Geom_Surface>& S,
                                               TopOpeBRepDS_DataStructure&      DStr);
