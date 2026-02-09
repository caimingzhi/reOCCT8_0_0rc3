#pragma once

#include <NCollection_Array1.hpp>
#include <IntTools_Root.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Edge;
class gp_Pnt;
class Geom_Curve;
class BRepAdaptor_Curve;

class IntTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double Length(const TopoDS_Edge& E);

  Standard_EXPORT static void RemoveIdenticalRoots(NCollection_Sequence<IntTools_Root>& aSeq,
                                                   const double                         anEpsT);

  Standard_EXPORT static void SortRoots(NCollection_Sequence<IntTools_Root>& aSeq,
                                        const double                         anEpsT);

  Standard_EXPORT static void FindRootStates(NCollection_Sequence<IntTools_Root>& aSeq,
                                             const double                         anEpsNull);

  Standard_EXPORT static int Parameter(const gp_Pnt&                  P,
                                       const occ::handle<Geom_Curve>& Curve,
                                       double&                        aParm);

  Standard_EXPORT static int GetRadius(const BRepAdaptor_Curve& C,
                                       const double             t1,
                                       const double             t3,
                                       double&                  R);

  Standard_EXPORT static int PrepareArgs(BRepAdaptor_Curve&          C,
                                         const double                tMax,
                                         const double                tMin,
                                         const int                   Discret,
                                         const double                Deflect,
                                         NCollection_Array1<double>& anArgs);
};
