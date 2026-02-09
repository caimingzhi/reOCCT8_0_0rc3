#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_PointLine.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <IntSurf_Situation.hpp>
#include <IntSurf_TypeTrans.hpp>

class IntPatch_Point;
class IntSurf_PntOn2S;

class IntPatch_RLine : public IntPatch_PointLine
{

public:
  Standard_EXPORT IntPatch_RLine(const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_RLine(const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_RLine(const bool Tang);

  void AddVertex(const IntPatch_Point& Pnt, const bool theIsPrepend = false) override;

  void Replace(const int Index, const IntPatch_Point& Pnt);

  void SetFirstPoint(const int IndFirst);

  void SetLastPoint(const int IndLast);

  void Add(const occ::handle<IntSurf_LineOn2S>& L);

  bool IsArcOnS1() const;

  bool IsArcOnS2() const;

  Standard_EXPORT void SetArcOnS1(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT void SetArcOnS2(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT void SetParamOnS1(const double p1, const double p2);

  Standard_EXPORT void SetParamOnS2(double& p1, double& p2);

  const occ::handle<Adaptor2d_Curve2d>& ArcOnS1() const;

  const occ::handle<Adaptor2d_Curve2d>& ArcOnS2() const;

  Standard_EXPORT void ParamOnS1(double& p1, double& p2) const;

  Standard_EXPORT void ParamOnS2(double& p1, double& p2) const;

  bool HasFirstPoint() const;

  bool HasLastPoint() const;

  const IntPatch_Point& FirstPoint() const;

  const IntPatch_Point& LastPoint() const;

  int NbVertex() const override;

  const IntPatch_Point& Vertex(const int Index) const override;

  IntPatch_Point& ChangeVertex(const int Index) override;

  void RemoveVertex(const int theIndex) override;

  bool HasPolygon() const;

  int NbPnts() const override;

  const IntSurf_PntOn2S& Point(const int Index) const override;

  Standard_EXPORT void SetPoint(const int Index, const IntPatch_Point& Pnt);

  Standard_EXPORT void ComputeVertexParameters(const double Tol);

  occ::handle<IntSurf_LineOn2S> Curve() const override;

  bool IsOutSurf1Box(const gp_Pnt2d& theP) const override { return curv->IsOutSurf1Box(theP); }

  bool IsOutSurf2Box(const gp_Pnt2d& theP) const override { return curv->IsOutSurf2Box(theP); }

  bool IsOutBox(const gp_Pnt& theP) const override { return curv->IsOutBox(theP); }

  void ClearVertexes() override { svtx.Clear(); }

  void SetCurve(const occ::handle<IntSurf_LineOn2S>& theNewCurve) { curv = theNewCurve; }

  Standard_EXPORT void Dump(const int theMode) const;

  DEFINE_STANDARD_RTTIEXT(IntPatch_RLine, IntPatch_PointLine)

private:
  occ::handle<Adaptor2d_Curve2d>       theArcOnS1;
  occ::handle<Adaptor2d_Curve2d>       theArcOnS2;
  bool                                 onS1;
  bool                                 onS2;
  double                               ParamInf1;
  double                               ParamSup1;
  double                               ParamInf2;
  double                               ParamSup2;
  occ::handle<IntSurf_LineOn2S>        curv;
  bool                                 fipt;
  bool                                 lapt;
  int                                  indf;
  int                                  indl;
  NCollection_Sequence<IntPatch_Point> svtx;
};

#include <Standard_DomainError.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <IntPatch_Point.hpp>

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_RLine::ArcOnS1() const
{
  return theArcOnS1;
}

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_RLine::ArcOnS2() const
{
  return theArcOnS2;
}

inline void IntPatch_RLine::AddVertex(const IntPatch_Point& thePnt, const bool theIsPrepend)
{
  if (theIsPrepend)
    svtx.Prepend(thePnt);
  else
    svtx.Append(thePnt);
}

inline void IntPatch_RLine::Replace(const int Index, const IntPatch_Point& Pnt)
{
  svtx(Index) = Pnt;
}

inline void IntPatch_RLine::SetFirstPoint(const int IndFirst)
{
  fipt = true;
  indf = IndFirst;
}

inline void IntPatch_RLine::SetLastPoint(const int IndLast)
{
  lapt = true;
  indl = IndLast;
}

inline void IntPatch_RLine::Add(const occ::handle<IntSurf_LineOn2S>& L)
{
  curv = L;
}

inline bool IntPatch_RLine::IsArcOnS1() const
{
  return onS1;
}

inline bool IntPatch_RLine::IsArcOnS2() const
{
  return onS2;
}

inline bool IntPatch_RLine::HasFirstPoint() const
{
  return fipt;
}

inline bool IntPatch_RLine::HasLastPoint() const
{
  return lapt;
}

inline const IntPatch_Point& IntPatch_RLine::FirstPoint() const
{
  if (!fipt)
  {
    throw Standard_DomainError();
  }
  return svtx(indf);
}

inline const IntPatch_Point& IntPatch_RLine::LastPoint() const
{
  if (!lapt)
  {
    throw Standard_DomainError();
  }
  return svtx(indl);
}

inline int IntPatch_RLine::NbVertex() const
{
  return svtx.Length();
}

inline const IntPatch_Point& IntPatch_RLine::Vertex(const int Index) const
{
  return svtx(Index);
}

inline IntPatch_Point& IntPatch_RLine::ChangeVertex(const int Index)
{
  return svtx(Index);
}

inline void IntPatch_RLine::RemoveVertex(const int theIndex)
{
  if ((theIndex < 1) || (theIndex > NbVertex()))
    throw Standard_OutOfRange("Cannot delete not existing vertex");
  svtx.Remove(theIndex);
}

inline bool IntPatch_RLine::HasPolygon() const
{
  return (!curv.IsNull());
}

inline int IntPatch_RLine::NbPnts() const
{
  if (curv.IsNull())
  {
    throw Standard_DomainError();
  }
  return curv->NbPoints();
}

inline const IntSurf_PntOn2S& IntPatch_RLine::Point(const int Index) const
{
  if (curv.IsNull())
  {
    throw Standard_DomainError();
  }
  return curv->Value(Index);
}

inline occ::handle<IntSurf_LineOn2S> IntPatch_RLine::Curve() const
{
  return (curv);
}
