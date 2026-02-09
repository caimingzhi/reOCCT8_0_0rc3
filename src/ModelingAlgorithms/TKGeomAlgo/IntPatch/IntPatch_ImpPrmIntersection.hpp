#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_Line.hpp>
#include <IntPatch_TheSOnBounds.hpp>
#include <IntPatch_TheSearchInside.hpp>

class Adaptor3d_TopolTool;

class IntPatch_ImpPrmIntersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_ImpPrmIntersection();

  Standard_EXPORT IntPatch_ImpPrmIntersection(const occ::handle<Adaptor3d_Surface>&   Surf1,
                                              const occ::handle<Adaptor3d_TopolTool>& D1,
                                              const occ::handle<Adaptor3d_Surface>&   Surf2,
                                              const occ::handle<Adaptor3d_TopolTool>& D2,
                                              const double                            TolArc,
                                              const double                            TolTang,
                                              const double                            Fleche,
                                              const double                            Pas);

  Standard_EXPORT void SetStartPoint(const double U, const double V);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Surf1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const occ::handle<Adaptor3d_Surface>&   Surf2,
                               const occ::handle<Adaptor3d_TopolTool>& D2,
                               const double                            TolArc,
                               const double                            TolTang,
                               const double                            Fleche,
                               const double                            Pas);

  bool IsDone() const;

  bool IsEmpty() const;

  int NbPnts() const;

  const IntPatch_Point& Point(const int Index) const;

  int NbLines() const;

  const occ::handle<IntPatch_Line>& Line(const int Index) const;

private:
  bool                                             done;
  bool                                             empt;
  NCollection_Sequence<IntPatch_Point>             spnt;
  NCollection_Sequence<occ::handle<IntPatch_Line>> slin;
  IntPatch_TheSOnBounds                            solrst;
  IntPatch_TheSearchInside                         solins;
  bool                                             myIsStartPnt;
  double                                           myUStart;
  double                                           myVStart;
};

#include <StdFail_NotDone.hpp>
#include <IntPatch_Line.hpp>

inline bool IntPatch_ImpPrmIntersection::IsDone() const
{
  return done;
}

inline bool IntPatch_ImpPrmIntersection::IsEmpty() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return empt;
}

inline int IntPatch_ImpPrmIntersection::NbPnts() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt.Length();
}

inline const IntPatch_Point& IntPatch_ImpPrmIntersection::Point(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt(Index);
}

inline int IntPatch_ImpPrmIntersection::NbLines() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin.Length();
}

inline const occ::handle<IntPatch_Line>& IntPatch_ImpPrmIntersection::Line(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin(Index);
}
