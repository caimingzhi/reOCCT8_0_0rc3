#include <BRepOffsetAPI_MakeFilling.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

BRepOffsetAPI_MakeFilling::BRepOffsetAPI_MakeFilling(const int    Degree,
                                                     const int    NbPtsOnCur,
                                                     const int    NbIter,
                                                     const bool   Anisotropie,
                                                     const double Tol2d,
                                                     const double Tol3d,
                                                     const double TolAng,
                                                     const double TolCurv,
                                                     const int    MaxDeg,
                                                     const int    MaxSegments)
    : myFilling(Degree,
                NbPtsOnCur,
                NbIter,
                Anisotropie,
                Tol2d,
                Tol3d,
                TolAng,
                TolCurv,
                MaxDeg,
                MaxSegments)
{
}

void BRepOffsetAPI_MakeFilling::SetConstrParam(const double Tol2d,
                                               const double Tol3d,
                                               const double TolAng,
                                               const double TolCurv)
{
  myFilling.SetConstrParam(Tol2d, Tol3d, TolAng, TolCurv);
}

void BRepOffsetAPI_MakeFilling::SetResolParam(const int  Degree,
                                              const int  NbPtsOnCur,
                                              const int  NbIter,
                                              const bool Anisotropie)
{
  myFilling.SetResolParam(Degree, NbPtsOnCur, NbIter, Anisotropie);
}

void BRepOffsetAPI_MakeFilling::SetApproxParam(const int MaxDeg, const int MaxSegments)
{
  myFilling.SetApproxParam(MaxDeg, MaxSegments);
}

void BRepOffsetAPI_MakeFilling::LoadInitSurface(const TopoDS_Face& Surf)
{
  myFilling.LoadInitSurface(Surf);
}

int BRepOffsetAPI_MakeFilling::Add(const TopoDS_Edge&  Constr,
                                   const GeomAbs_Shape Order,
                                   const bool          IsBound)
{
  return myFilling.Add(Constr, Order, IsBound);
}

int BRepOffsetAPI_MakeFilling::Add(const TopoDS_Edge&  Constr,
                                   const TopoDS_Face&  Support,
                                   const GeomAbs_Shape Order,
                                   const bool          IsBound)
{
  return myFilling.Add(Constr, Support, Order, IsBound);
}

int BRepOffsetAPI_MakeFilling::Add(const TopoDS_Face& Support, const GeomAbs_Shape Order)
{
  return myFilling.Add(Support, Order);
}

int BRepOffsetAPI_MakeFilling::Add(const gp_Pnt& Point)
{
  return myFilling.Add(Point);
}

int BRepOffsetAPI_MakeFilling::Add(const double        U,
                                   const double        V,
                                   const TopoDS_Face&  Support,
                                   const GeomAbs_Shape Order)
{
  return myFilling.Add(U, V, Support, Order);
}

void BRepOffsetAPI_MakeFilling::Build(const Message_ProgressRange&)
{
  myFilling.Build();
  myShape = myFilling.Face();
}

bool BRepOffsetAPI_MakeFilling::IsDone() const
{
  return myFilling.IsDone();
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_MakeFilling::Generated(const TopoDS_Shape& S)
{
  return myFilling.Generated(S);
}

double BRepOffsetAPI_MakeFilling::G0Error() const
{
  return myFilling.G0Error();
}

double BRepOffsetAPI_MakeFilling::G1Error() const
{
  return myFilling.G1Error();
}

double BRepOffsetAPI_MakeFilling::G2Error() const
{
  return myFilling.G2Error();
}

double BRepOffsetAPI_MakeFilling::G0Error(const int Index)
{
  return myFilling.G0Error(Index);
}

double BRepOffsetAPI_MakeFilling::G1Error(const int Index)
{
  return myFilling.G1Error(Index);
}

double BRepOffsetAPI_MakeFilling::G2Error(const int Index)
{
  return myFilling.G2Error(Index);
}
