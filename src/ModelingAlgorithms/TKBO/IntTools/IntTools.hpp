#pragma once

#include <NCollection_Array1.hpp>
#include <IntTools_Root.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Edge;
class gp_Pnt;
class Geom_Curve;
class BRepAdaptor_Curve;

//! Contains classes for intersection and classification purposes and accompanying classes.
class IntTools
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns the length of the edge;
  Standard_EXPORT static double Length(const TopoDS_Edge& E);

  //! Remove from the sequence aSeq the Roots that have
  //! values ti and tj such as |ti-tj] < anEpsT.
  Standard_EXPORT static void RemoveIdenticalRoots(NCollection_Sequence<IntTools_Root>& aSeq,
                                                   const double                         anEpsT);

  //! Sort the sequence aSeq of the Roots to arrange the Roots in increasing order.
  Standard_EXPORT static void SortRoots(NCollection_Sequence<IntTools_Root>& aSeq,
                                        const double                         anEpsT);

  //! Find the states (before and after) for each Root from the sequence aSeq
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
