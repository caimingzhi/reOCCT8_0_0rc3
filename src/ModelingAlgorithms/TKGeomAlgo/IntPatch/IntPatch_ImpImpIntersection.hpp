#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_Line.hpp>
#include <IntPatch_TheSOnBounds.hpp>

class Adaptor3d_TopolTool;

class IntPatch_ImpImpIntersection
{
public:
  DEFINE_STANDARD_ALLOC

  enum IntStatus
  {

    IntStatus_OK,

    IntStatus_InfiniteSectionCurve,

    IntStatus_Fail
  };

  Standard_EXPORT IntPatch_ImpImpIntersection();

  Standard_EXPORT IntPatch_ImpImpIntersection(const occ::handle<Adaptor3d_Surface>&   S1,
                                              const occ::handle<Adaptor3d_TopolTool>& D1,
                                              const occ::handle<Adaptor3d_Surface>&   S2,
                                              const occ::handle<Adaptor3d_TopolTool>& D2,
                                              const double                            TolArc,
                                              const double                            TolTang,
                                              const bool theIsReqToKeepRLine = false);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   S1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const occ::handle<Adaptor3d_Surface>&   S2,
                               const occ::handle<Adaptor3d_TopolTool>& D2,
                               const double                            TolArc,
                               const double                            TolTang,
                               const bool                              theIsReqToKeepRLine = false);

  bool IsDone() const;

  IntStatus GetStatus() const;

  bool IsEmpty() const;

  bool TangentFaces() const;

  bool OppositeFaces() const;

  int NbPnts() const;

  const IntPatch_Point& Point(const int Index) const;

  int NbLines() const;

  const occ::handle<IntPatch_Line>& Line(const int Index) const;

private:
  IntStatus                                        myDone;
  bool                                             empt;
  bool                                             tgte;
  bool                                             oppo;
  NCollection_Sequence<IntPatch_Point>             spnt;
  NCollection_Sequence<occ::handle<IntPatch_Line>> slin;
  IntPatch_TheSOnBounds                            solrst;
};

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <IntPatch_Line.hpp>

inline bool IntPatch_ImpImpIntersection::IsDone() const
{
  return (GetStatus() != IntStatus_Fail);
}

inline IntPatch_ImpImpIntersection::IntStatus IntPatch_ImpImpIntersection::GetStatus() const
{
  return myDone;
}

inline bool IntPatch_ImpImpIntersection::IsEmpty() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return empt;
}

inline bool IntPatch_ImpImpIntersection::TangentFaces() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return tgte;
}

inline bool IntPatch_ImpImpIntersection::OppositeFaces() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  if (!tgte)
  {
    throw Standard_DomainError();
  }
  return oppo;
}

inline int IntPatch_ImpImpIntersection::NbPnts() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return spnt.Length();
}

inline const IntPatch_Point& IntPatch_ImpImpIntersection::Point(const int Index) const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return spnt(Index);
}

inline int IntPatch_ImpImpIntersection::NbLines() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return slin.Length();
}

inline const occ::handle<IntPatch_Line>& IntPatch_ImpImpIntersection::Line(const int Index) const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return slin(Index);
}
