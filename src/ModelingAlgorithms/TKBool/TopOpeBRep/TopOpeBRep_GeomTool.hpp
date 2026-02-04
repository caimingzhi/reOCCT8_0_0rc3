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

//! Provide services needed by the DSFiller
class TopOpeBRep_GeomTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make the DS curve <C> and the pcurves <PC1,PC2> from
  //! intersection line <L> lying on shapes <S1,S2>. <min,max> = <L> bounds
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

