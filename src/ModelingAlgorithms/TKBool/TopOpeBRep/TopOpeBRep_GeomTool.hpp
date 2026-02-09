#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class TopOpeBRep_LineInter;
class TopoDS_Shape;
class TopOpeBRepDS_Curve;
class Geom2d_Curve;
class Geom_Curve;

class TopOpeBRep_GeomTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void MakeCurves(const double                min,
                                         const double                max,
                                         const TopOpeBRep_LineInter& L,
                                         const TopoDS_Shape&         S1,
                                         const TopoDS_Shape&         S2,
                                         TopOpeBRepDS_Curve&         C,
                                         occ::handle<Geom2d_Curve>&  PC1,
                                         occ::handle<Geom2d_Curve>&  PC2);

  Standard_EXPORT static void MakeCurve(const double                min,
                                        const double                max,
                                        const TopOpeBRep_LineInter& L,
                                        occ::handle<Geom_Curve>&    C);

  Standard_EXPORT static occ::handle<Geom_Curve> MakeBSpline1fromWALKING3d(
    const TopOpeBRep_LineInter& L);

  Standard_EXPORT static occ::handle<Geom2d_Curve> MakeBSpline1fromWALKING2d(
    const TopOpeBRep_LineInter& L,
    const int                   SI);
};
