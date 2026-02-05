#pragma once

#include <Extrema_ExtPC.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Vertex;
class TopoDS_Edge;

class BRepExtrema_ExtPC
{
public:
  DEFINE_STANDARD_ALLOC

  BRepExtrema_ExtPC() = default;

  //! It calculates all the distances.
  Standard_EXPORT BRepExtrema_ExtPC(const TopoDS_Vertex& V, const TopoDS_Edge& E);

  Standard_EXPORT void Initialize(const TopoDS_Edge& E);
  //! An exception is raised if the fields have not been initialized.
  Standard_EXPORT void Perform(const TopoDS_Vertex& V);

  //! True if the distances are found.
  bool IsDone() const { return myExtPC.IsDone(); }

  //! Returns the number of extremum distances.
  int NbExt() const { return myExtPC.NbExt(); }

  //! Returns True if the <N>th extremum distance is a minimum.
  bool IsMin(const int N) const { return myExtPC.IsMin(N); }

  //! Returns the value of the <N>th extremum square distance.
  double SquareDistance(const int N) const { return myExtPC.SquareDistance(N); }

  //! Returns the parameter on the edge of the <N>th extremum distance.
  double Parameter(const int N) const { return myExtPC.Point(N).Parameter(); }

  //! Returns the Point of the <N>th extremum distance.
  gp_Pnt Point(const int N) const { return myExtPC.Point(N).Value(); }

  //! if the curve is a trimmed curve,
  //! dist1 is a square distance between <P> and the point
  //! of parameter FirstParameter <pnt1> and
  //! dist2 is a square distance between <P> and the point
  //! of parameter LastParameter <pnt2>.
  void TrimmedSquareDistances(double& dist1, double& dist2, gp_Pnt& pnt1, gp_Pnt& pnt2) const
  {
    myExtPC.TrimmedSquareDistances(dist1, dist2, pnt1, pnt2);
  }

private:
  Extrema_ExtPC                  myExtPC;
  occ::handle<BRepAdaptor_Curve> myHC;
};
