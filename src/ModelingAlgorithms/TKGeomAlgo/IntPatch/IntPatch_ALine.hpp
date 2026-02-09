#pragma once

#include <Standard_Handle.hpp>

#include <IntAna_Curve.hpp>
#include <IntPatch_Line.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>

class IntPatch_Point;

class IntPatch_ALine : public IntPatch_Line
{

public:
  Standard_EXPORT IntPatch_ALine(const IntAna_Curve&     C,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_ALine(const IntAna_Curve&     C,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_ALine(const IntAna_Curve& C, const bool Tang);

  Standard_EXPORT void AddVertex(const IntPatch_Point& Pnt);

  void Replace(const int Index, const IntPatch_Point& Pnt);

  void SetFirstPoint(const int IndFirst);

  void SetLastPoint(const int IndLast);

  double FirstParameter(bool& IsIncluded) const;

  double LastParameter(bool& IsIncluded) const;

  gp_Pnt Value(const double U);

  bool D1(const double U, gp_Pnt& P, gp_Vec& Du);

  void FindParameter(const gp_Pnt& P, NCollection_List<double>& theParams) const;

  bool HasFirstPoint() const;

  bool HasLastPoint() const;

  const IntPatch_Point& FirstPoint() const;

  const IntPatch_Point& LastPoint() const;

  int NbVertex() const;

  const IntPatch_Point& Vertex(const int Index) const;

  IntPatch_Point& ChangeVertex(const int theIndex) { return svtx.ChangeValue(theIndex); }

  Standard_EXPORT void ComputeVertexParameters(const double Tol);

  Standard_EXPORT const IntAna_Curve& Curve() const;

  DEFINE_STANDARD_RTTIEXT(IntPatch_ALine, IntPatch_Line)

private:
  IntAna_Curve                         curv;
  bool                                 fipt;
  bool                                 lapt;
  int                                  indf;
  int                                  indl;
  NCollection_Sequence<IntPatch_Point> svtx;
};

#include <Standard_DomainError.hpp>
#include <Precision.hpp>
#include <IntPatch_Point.hpp>

inline void IntPatch_ALine::Replace(const int Index, const IntPatch_Point& Pnt)
{
  svtx(Index) = Pnt;
}

inline void IntPatch_ALine::SetFirstPoint(const int IndFirst)
{
  fipt = true;
  indf = IndFirst;
}

inline void IntPatch_ALine::SetLastPoint(const int IndLast)
{
  lapt = true;
  indl = IndLast;
}

inline double IntPatch_ALine::FirstParameter(bool& IsIncluded) const
{
  double bid, first;
  curv.Domain(first, bid);
  IsIncluded = !curv.IsFirstOpen();
  return first;
}

inline double IntPatch_ALine::LastParameter(bool& IsIncluded) const
{
  double bid, last;
  curv.Domain(bid, last);
  IsIncluded = !curv.IsLastOpen();
  return last;
}

inline gp_Pnt IntPatch_ALine::Value(const double U)
{
  return curv.Value(U);
}

inline bool IntPatch_ALine::D1(const double U, gp_Pnt& P, gp_Vec& Du)
{
  return curv.D1u(U, P, Du);
}

inline void IntPatch_ALine::FindParameter(const gp_Pnt&             theP,
                                          NCollection_List<double>& theParams) const
{
  curv.FindParameter(theP, theParams);
}

inline bool IntPatch_ALine::HasFirstPoint() const
{
  return fipt;
}

inline bool IntPatch_ALine::HasLastPoint() const
{
  return lapt;
}

inline const IntPatch_Point& IntPatch_ALine::FirstPoint() const
{
  if (!fipt)
  {
    throw Standard_DomainError();
  }
  return svtx(indf);
}

inline const IntPatch_Point& IntPatch_ALine::LastPoint() const
{
  if (!lapt)
  {
    throw Standard_DomainError();
  }
  return svtx(indl);
}

inline int IntPatch_ALine::NbVertex() const
{
  return svtx.Length();
}

inline const IntPatch_Point& IntPatch_ALine::Vertex(const int Index) const
{
  return svtx(Index);
}
