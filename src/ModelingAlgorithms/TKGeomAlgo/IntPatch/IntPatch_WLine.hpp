#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Real.hpp>
#include <IntPatch_PointLine.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <IntSurf_Situation.hpp>
#include <IntSurf_TypeTrans.hpp>

class IntPatch_Point;
class IntSurf_PntOn2S;
class gp_Pnt2d;
class gp_Pnt;

class IntPatch_WLine : public IntPatch_PointLine
{

public:
  enum IntPatch_WLType
  {
    IntPatch_WLUnknown,
    IntPatch_WLImpImp,
    IntPatch_WLImpPrm,
    IntPatch_WLPrmPrm
  };

  Standard_EXPORT IntPatch_WLine(const occ::handle<IntSurf_LineOn2S>& Line,
                                 const bool                           Tang,
                                 const IntSurf_TypeTrans              Trans1,
                                 const IntSurf_TypeTrans              Trans2);

  Standard_EXPORT IntPatch_WLine(const occ::handle<IntSurf_LineOn2S>& Line,
                                 const bool                           Tang,
                                 const IntSurf_Situation              Situ1,
                                 const IntSurf_Situation              Situ2);

  Standard_EXPORT IntPatch_WLine(const occ::handle<IntSurf_LineOn2S>& Line, const bool Tang);

  void AddVertex(const IntPatch_Point& Pnt, const bool theIsPrepend = false) override;

  Standard_EXPORT void SetPoint(const int Index, const IntPatch_Point& Pnt);

  void Replace(const int Index, const IntPatch_Point& Pnt);

  void SetFirstPoint(const int IndFirst);

  void SetLastPoint(const int IndLast);

  int NbPnts() const override;

  const IntSurf_PntOn2S& Point(const int Index) const override;

  bool HasFirstPoint() const;

  bool HasLastPoint() const;

  const IntPatch_Point& FirstPoint() const;

  const IntPatch_Point& LastPoint() const;

  const IntPatch_Point& FirstPoint(int& Indfirst) const;

  const IntPatch_Point& LastPoint(int& Indlast) const;

  int NbVertex() const override;

  const IntPatch_Point& Vertex(const int Index) const override;

  IntPatch_Point& ChangeVertex(const int Index) override;

  Standard_EXPORT void ComputeVertexParameters(const double Tol);

  Standard_EXPORT occ::handle<IntSurf_LineOn2S> Curve() const override;

  bool IsOutSurf1Box(const gp_Pnt2d& theP) const override { return curv->IsOutSurf1Box(theP); }

  bool IsOutSurf2Box(const gp_Pnt2d& theP) const override { return curv->IsOutSurf2Box(theP); }

  bool IsOutBox(const gp_Pnt& theP) const override { return curv->IsOutBox(theP); }

  Standard_EXPORT void SetPeriod(const double pu1,
                                 const double pv1,
                                 const double pu2,
                                 const double pv2);

  Standard_EXPORT double U1Period() const;

  Standard_EXPORT double V1Period() const;

  Standard_EXPORT double U2Period() const;

  Standard_EXPORT double V2Period() const;

  Standard_EXPORT void SetArcOnS1(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT bool HasArcOnS1() const;

  Standard_EXPORT const occ::handle<Adaptor2d_Curve2d>& GetArcOnS1() const;

  Standard_EXPORT void SetArcOnS2(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT bool HasArcOnS2() const;

  Standard_EXPORT const occ::handle<Adaptor2d_Curve2d>& GetArcOnS2() const;

  void ClearVertexes() override;

  void RemoveVertex(const int theIndex) override;

  void InsertVertexBefore(const int theIndex, const IntPatch_Point& thePnt);

  Standard_EXPORT void Dump(const int theMode) const;

  void EnablePurging(const bool theIsEnabled) { myIsPurgerAllowed = theIsEnabled; }

  bool IsPurgingAllowed() { return myIsPurgerAllowed; }

  IntPatch_WLType GetCreatingWay() const { return myCreationWay; }

  void SetCreatingWayInfo(IntPatch_WLType theAlgo) { myCreationWay = theAlgo; }

  DEFINE_STANDARD_RTTIEXT(IntPatch_WLine, IntPatch_PointLine)

private:
  occ::handle<IntSurf_LineOn2S>        curv;
  bool                                 fipt;
  bool                                 lapt;
  int                                  indf;
  int                                  indl;
  NCollection_Sequence<IntPatch_Point> svtx;
  double                               u1period;
  double                               v1period;
  double                               u2period;
  double                               v2period;
  bool                                 hasArcOnS1;
  occ::handle<Adaptor2d_Curve2d>       theArcOnS1;
  bool                                 hasArcOnS2;
  occ::handle<Adaptor2d_Curve2d>       theArcOnS2;
  bool                                 myIsPurgerAllowed;

  IntPatch_WLType myCreationWay;
};

#include <Standard_DomainError.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <IntPatch_Point.hpp>

inline void IntPatch_WLine::AddVertex(const IntPatch_Point& thePnt, const bool theIsPrepend)
{
  if (theIsPrepend)
    svtx.Prepend(thePnt);
  else
    svtx.Append(thePnt);
}

inline void IntPatch_WLine::Replace(const int Index, const IntPatch_Point& Pnt)
{
  svtx(Index) = Pnt;
}

inline void IntPatch_WLine::SetFirstPoint(const int IndFirst)
{
  fipt = true;
  indf = IndFirst;
}

inline void IntPatch_WLine::SetLastPoint(const int IndLast)
{
  lapt = true;
  indl = IndLast;
}

inline int IntPatch_WLine::NbPnts() const
{
  return curv->NbPoints();
}

inline const IntSurf_PntOn2S& IntPatch_WLine::Point(const int Index) const
{
  return curv->Value(Index);
}

inline bool IntPatch_WLine::HasFirstPoint() const
{
  return fipt;
}

inline bool IntPatch_WLine::HasLastPoint() const
{
  return lapt;
}

inline const IntPatch_Point& IntPatch_WLine::FirstPoint() const
{
  if (!fipt)
  {
    throw Standard_DomainError();
  }
  return svtx(indf);
}

inline const IntPatch_Point& IntPatch_WLine::LastPoint() const
{
  if (!lapt)
  {
    throw Standard_DomainError();
  }
  return svtx(indl);
}

inline const IntPatch_Point& IntPatch_WLine::FirstPoint(int& Indfirst) const
{
  if (!fipt)
  {
    throw Standard_DomainError();
  }
  Indfirst = indf;
  return svtx(indf);
}

inline const IntPatch_Point& IntPatch_WLine::LastPoint(int& Indlast) const
{
  if (!lapt)
  {
    throw Standard_DomainError();
  }
  Indlast = indl;
  return svtx(indl);
}

inline int IntPatch_WLine::NbVertex() const
{
  return svtx.Length();
}

inline const IntPatch_Point& IntPatch_WLine::Vertex(const int Index) const
{
  return svtx(Index);
}

inline IntPatch_Point& IntPatch_WLine::ChangeVertex(const int Index)
{
  return svtx(Index);
}

inline void IntPatch_WLine::ClearVertexes()
{
  svtx.Clear();
}

inline void IntPatch_WLine::RemoveVertex(const int theIndex)
{
  if ((theIndex < 1) || (theIndex > NbVertex()))
    throw Standard_OutOfRange("Cannot delete not existing vertex");
  svtx.Remove(theIndex);
}

inline void IntPatch_WLine::InsertVertexBefore(const int theIndex, const IntPatch_Point& thePnt)
{
  const int aNbVertexes = NbVertex();
  int       anIndex     = std::max(theIndex, 1);

  if (anIndex > aNbVertexes)
    svtx.Append(thePnt);
  else
    svtx.InsertBefore(theIndex, thePnt);
}
