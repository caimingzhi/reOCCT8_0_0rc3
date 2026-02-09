#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Ax2.hpp>
#include <Standard_Integer.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_Line.hpp>
#include <IntSurf_TypeTrans.hpp>
#include <IntSurf_Situation.hpp>
#include <gp_Circ.hpp>
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;
class IntPatch_Point;

class IntPatch_GLine : public IntPatch_Line
{

public:
  Standard_EXPORT IntPatch_GLine(const gp_Lin&           L,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_GLine(const gp_Lin&           L,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_GLine(const gp_Lin& L, const bool Tang);

  Standard_EXPORT IntPatch_GLine(const gp_Circ&          C,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_GLine(const gp_Circ&          C,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_GLine(const gp_Circ& C, const bool Tang);

  Standard_EXPORT IntPatch_GLine(const gp_Elips&         E,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_GLine(const gp_Elips&         E,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_GLine(const gp_Elips& E, const bool Tang);

  Standard_EXPORT IntPatch_GLine(const gp_Parab&         P,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_GLine(const gp_Parab&         P,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_GLine(const gp_Parab& P, const bool Tang);

  Standard_EXPORT IntPatch_GLine(const gp_Hypr&          H,
                                 const bool              Tang,
                                 const IntSurf_TypeTrans Trans1,
                                 const IntSurf_TypeTrans Trans2);

  Standard_EXPORT IntPatch_GLine(const gp_Hypr&          H,
                                 const bool              Tang,
                                 const IntSurf_Situation Situ1,
                                 const IntSurf_Situation Situ2);

  Standard_EXPORT IntPatch_GLine(const gp_Hypr& H, const bool Tang);

  Standard_EXPORT void AddVertex(const IntPatch_Point& Pnt);

  Standard_EXPORT void Replace(const int Index, const IntPatch_Point& Pnt);

  void SetFirstPoint(const int IndFirst);

  void SetLastPoint(const int IndLast);

  gp_Lin Line() const;

  gp_Circ Circle() const;

  gp_Elips Ellipse() const;

  gp_Parab Parabola() const;

  gp_Hypr Hyperbola() const;

  bool HasFirstPoint() const;

  bool HasLastPoint() const;

  const IntPatch_Point& FirstPoint() const;

  const IntPatch_Point& LastPoint() const;

  int NbVertex() const;

  const IntPatch_Point& Vertex(const int Index) const;

  Standard_EXPORT void ComputeVertexParameters(const double Tol);

  DEFINE_STANDARD_RTTIEXT(IntPatch_GLine, IntPatch_Line)

private:
  gp_Ax2                               pos;
  double                               par1;
  double                               par2;
  bool                                 fipt;
  bool                                 lapt;
  int                                  indf;
  int                                  indl;
  NCollection_Sequence<IntPatch_Point> svtx;
};

#include <Standard_DomainError.hpp>

#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Parab.hpp>
#include <gp_Hypr.hpp>

#include <Precision.hpp>

inline void IntPatch_GLine::SetFirstPoint(const int IndFirst)
{
  fipt = true;
  indf = IndFirst;
}

inline void IntPatch_GLine::SetLastPoint(const int IndLast)
{
  lapt = true;
  indl = IndLast;
}

inline gp_Lin IntPatch_GLine::Line() const
{
  if (typ != IntPatch_Lin)
  {
    throw Standard_DomainError();
  }
  return gp_Lin(pos.Axis());
}

inline gp_Circ IntPatch_GLine::Circle() const
{
  if (typ != IntPatch_Circle)
  {
    throw Standard_DomainError();
  }
  return gp_Circ(pos, par1);
}

inline gp_Elips IntPatch_GLine::Ellipse() const
{
  if (typ != IntPatch_Ellipse)
  {
    throw Standard_DomainError();
  }
  return gp_Elips(pos, par1, par2);
}

inline gp_Parab IntPatch_GLine::Parabola() const
{
  if (typ != IntPatch_Parabola)
  {
    throw Standard_DomainError();
  }
  return gp_Parab(pos, par1);
}

inline gp_Hypr IntPatch_GLine::Hyperbola() const
{
  if (typ != IntPatch_Hyperbola)
  {
    throw Standard_DomainError();
  }
  return gp_Hypr(pos, par1, par2);
}

inline bool IntPatch_GLine::HasFirstPoint() const
{
  return fipt;
}

inline bool IntPatch_GLine::HasLastPoint() const
{
  return lapt;
}

inline const IntPatch_Point& IntPatch_GLine::FirstPoint() const
{
  if (!fipt)
  {
    throw Standard_DomainError();
  }
  return svtx(indf);
}

inline const IntPatch_Point& IntPatch_GLine::LastPoint() const
{
  if (!lapt)
  {
    throw Standard_DomainError();
  }
  return svtx(indl);
}

inline int IntPatch_GLine::NbVertex() const
{
  return svtx.Length();
}

inline const IntPatch_Point& IntPatch_GLine::Vertex(const int Index) const
{
  return svtx(Index);
}
