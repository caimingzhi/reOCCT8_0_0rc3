#pragma once

#include <BRepAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <GeomAbs_CurveType.hpp>
#include <ChFiDS_ChamfMode.hpp>
#include <ChFiDS_ErrorStatus.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_State.hpp>
#include <ChFiDS_TypeOfConcavity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Edge;
class gp_Lin;
class gp_Circ;
class TopoDS_Vertex;

#ifdef Status
  #undef Status
#endif

class ChFiDS_Spine : public Standard_Transient
{

public:
  Standard_EXPORT ChFiDS_Spine();

  Standard_EXPORT ChFiDS_Spine(const double Tol);

  void SetEdges(const TopoDS_Edge& E);

  void SetOffsetEdges(const TopoDS_Edge& E);

  void PutInFirst(const TopoDS_Edge& E);

  void PutInFirstOffset(const TopoDS_Edge& E);

  int NbEdges() const;

  const TopoDS_Edge& Edges(const int I) const;

  const TopoDS_Edge& OffsetEdges(const int I) const;

  void SetFirstStatus(const ChFiDS_State S);

  void SetLastStatus(const ChFiDS_State S);

  Standard_EXPORT virtual void AppendElSpine(const occ::handle<ChFiDS_ElSpine>& Els);

  Standard_EXPORT virtual void AppendOffsetElSpine(const occ::handle<ChFiDS_ElSpine>& Els);

  Standard_EXPORT occ::handle<ChFiDS_ElSpine> ElSpine(const int IE) const;

  Standard_EXPORT occ::handle<ChFiDS_ElSpine> ElSpine(const TopoDS_Edge& E) const;

  Standard_EXPORT occ::handle<ChFiDS_ElSpine> ElSpine(const double W) const;

  Standard_EXPORT NCollection_List<occ::handle<ChFiDS_ElSpine>>& ChangeElSpines();

  Standard_EXPORT NCollection_List<occ::handle<ChFiDS_ElSpine>>& ChangeOffsetElSpines();

  Standard_EXPORT virtual void Reset(const bool AllData = false);

  Standard_EXPORT bool SplitDone() const;

  Standard_EXPORT void SplitDone(const bool B);

  Standard_EXPORT void Load();

  Standard_EXPORT double Resolution(const double R3d) const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT double FirstParameter() const;

  Standard_EXPORT double LastParameter() const;

  Standard_EXPORT void SetFirstParameter(const double Par);

  Standard_EXPORT void SetLastParameter(const double Par);

  Standard_EXPORT double FirstParameter(const int IndexSpine) const;

  Standard_EXPORT double LastParameter(const int IndexSpine) const;

  Standard_EXPORT double Length(const int IndexSpine) const;

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT double Period() const;

  Standard_EXPORT double Absc(const double U);

  Standard_EXPORT double Absc(const double U, const int I);

  Standard_EXPORT void Parameter(const double AbsC, double& U, const bool Oriented = true);

  Standard_EXPORT void Parameter(const int    Index,
                                 const double AbsC,
                                 double&      U,
                                 const bool   Oriented = true);

  Standard_EXPORT gp_Pnt Value(const double AbsC);

  Standard_EXPORT void D0(const double AbsC, gp_Pnt& P);

  Standard_EXPORT void D1(const double AbsC, gp_Pnt& P, gp_Vec& V1);

  Standard_EXPORT void D2(const double AbsC, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  Standard_EXPORT void SetCurrent(const int Index);

  Standard_EXPORT const BRepAdaptor_Curve& CurrentElementarySpine(const int Index);

  int CurrentIndexOfElementarySpine() const;

  Standard_EXPORT GeomAbs_CurveType GetType() const;

  Standard_EXPORT gp_Lin Line() const;

  Standard_EXPORT gp_Circ Circle() const;

  ChFiDS_State FirstStatus() const;

  ChFiDS_State LastStatus() const;

  ChFiDS_State Status(const bool IsFirst) const;

  ChFiDS_TypeOfConcavity GetTypeOfConcavity() const;

  void SetStatus(const ChFiDS_State S, const bool IsFirst);

  void SetTypeOfConcavity(const ChFiDS_TypeOfConcavity theType);

  bool IsTangencyExtremity(const bool IsFirst) const;

  void SetTangencyExtremity(const bool IsTangency, const bool IsFirst);

  Standard_EXPORT double Absc(const TopoDS_Vertex& V) const;

  Standard_EXPORT TopoDS_Vertex FirstVertex() const;

  Standard_EXPORT TopoDS_Vertex LastVertex() const;

  Standard_EXPORT void SetFirstTgt(const double W);

  Standard_EXPORT void SetLastTgt(const double W);

  Standard_EXPORT bool HasFirstTgt() const;

  Standard_EXPORT bool HasLastTgt() const;

  Standard_EXPORT void SetReference(const double W);

  Standard_EXPORT void SetReference(const int I);

  Standard_EXPORT int Index(const double W, const bool Forward = true) const;

  Standard_EXPORT int Index(const TopoDS_Edge& E) const;

  Standard_EXPORT void UnsetReference();

  Standard_EXPORT void SetErrorStatus(const ChFiDS_ErrorStatus state);

  Standard_EXPORT ChFiDS_ErrorStatus ErrorStatus() const;

  Standard_EXPORT ChFiDS_ChamfMode Mode() const;

  Standard_EXPORT double GetTolesp() const;

  DEFINE_STANDARD_RTTIEXT(ChFiDS_Spine, Standard_Transient)

protected:
  bool                                          splitdone;
  NCollection_List<occ::handle<ChFiDS_ElSpine>> elspines;
  NCollection_List<occ::handle<ChFiDS_ElSpine>> offset_elspines;
  ChFiDS_ChamfMode                              myMode;

private:
  Standard_EXPORT void Prepare(double& L, int& Index) const;

  BRepAdaptor_Curve                        myCurve;
  BRepAdaptor_Curve                        myOffsetCurve;
  int                                      indexofcurve;
  ChFiDS_TypeOfConcavity                   myTypeOfConcavity;
  ChFiDS_State                             firstState;
  ChFiDS_State                             lastState;
  NCollection_Sequence<TopoDS_Shape>       spine;
  NCollection_Sequence<TopoDS_Shape>       offsetspine;
  occ::handle<NCollection_HArray1<double>> abscissa;
  occ::handle<NCollection_HArray1<double>> offset_abscissa;
  double                                   tolesp;
  double                                   firstparam;
  double                                   lastparam;
  bool                                     firstprolon;
  bool                                     lastprolon;
  bool                                     firstistgt;
  bool                                     lastistgt;
  double                                   firsttgtpar;
  double                                   lasttgtpar;
  bool                                     hasfirsttgt;
  bool                                     haslasttgt;
  gp_Pnt                                   firstori;
  gp_Pnt                                   lastori;
  gp_Vec                                   firsttgt;
  gp_Vec                                   lasttgt;
  double                                   valref;
  bool                                     hasref;
  ChFiDS_ErrorStatus                       errorstate;
};

#include <TopoDS.hpp>

inline void ChFiDS_Spine::SetTypeOfConcavity(const ChFiDS_TypeOfConcavity theType)
{
  myTypeOfConcavity = theType;
}

inline void ChFiDS_Spine::SetFirstStatus(const ChFiDS_State S)
{
  firstState = S;
}

inline void ChFiDS_Spine::SetLastStatus(const ChFiDS_State S)
{
  lastState = S;
}

inline ChFiDS_TypeOfConcavity ChFiDS_Spine::GetTypeOfConcavity() const
{
  return myTypeOfConcavity;
}

inline ChFiDS_State ChFiDS_Spine::FirstStatus() const
{
  return firstState;
}

inline ChFiDS_State ChFiDS_Spine::LastStatus() const
{
  return lastState;
}

inline void ChFiDS_Spine::SetStatus(const ChFiDS_State S, const bool IsFirst)
{
  if (IsFirst)
    firstState = S;
  else
    lastState = S;
}

inline ChFiDS_State ChFiDS_Spine::Status(const bool IsFirst) const
{
  if (IsFirst)
    return firstState;
  else
    return lastState;
}

inline void ChFiDS_Spine::SetTangencyExtremity(const bool IsTangency, const bool IsFirst)
{
  if (IsFirst)
    firstistgt = IsTangency;
  else
    lastistgt = IsTangency;
}

inline bool ChFiDS_Spine::IsTangencyExtremity(const bool IsFirst) const
{
  if (IsFirst)
    return firstistgt;
  else
    return lastistgt;
}

inline int ChFiDS_Spine::NbEdges() const
{
  return spine.Length();
}

inline const TopoDS_Edge& ChFiDS_Spine::Edges(const int I) const
{
  return TopoDS::Edge(spine.Value(I));
}

inline const TopoDS_Edge& ChFiDS_Spine::OffsetEdges(const int I) const
{
  return TopoDS::Edge(offsetspine.Value(I));
}

inline void ChFiDS_Spine::SetEdges(const TopoDS_Edge& E)
{
  spine.Append(E);
}

inline void ChFiDS_Spine::SetOffsetEdges(const TopoDS_Edge& E)
{
  offsetspine.Append(E);
}

inline void ChFiDS_Spine::PutInFirst(const TopoDS_Edge& E)
{
  spine.InsertBefore(1, E);
}

inline void ChFiDS_Spine::PutInFirstOffset(const TopoDS_Edge& E)
{
  offsetspine.InsertBefore(1, E);
}

inline int ChFiDS_Spine::CurrentIndexOfElementarySpine() const
{
  return indexofcurve;
}

inline ChFiDS_ChamfMode ChFiDS_Spine::Mode() const
{

  return myMode;
}

inline double ChFiDS_Spine::GetTolesp() const
{
  return tolesp;
}
