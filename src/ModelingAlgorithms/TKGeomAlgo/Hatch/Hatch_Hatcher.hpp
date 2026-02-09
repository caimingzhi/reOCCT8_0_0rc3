#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Hatch_Line.hpp>
#include <NCollection_Sequence.hpp>
#include <Hatch_LineForm.hpp>
#include <Standard_Integer.hpp>
class gp_Lin2d;
class gp_Dir2d;
class gp_Pnt2d;

class Hatch_Hatcher
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Hatch_Hatcher(const double Tol, const bool Oriented = true);

  void Tolerance(const double Tol);

  double Tolerance() const;

  Standard_EXPORT void AddLine(const gp_Lin2d& L, const Hatch_LineForm T = Hatch_ANYLINE);

  Standard_EXPORT void AddLine(const gp_Dir2d& D, const double Dist);

  Standard_EXPORT void AddXLine(const double X);

  Standard_EXPORT void AddYLine(const double Y);

  Standard_EXPORT void Trim(const gp_Lin2d& L, const int Index = 0);

  Standard_EXPORT void Trim(const gp_Lin2d& L,
                            const double    Start,
                            const double    End,
                            const int       Index = 0);

  Standard_EXPORT void Trim(const gp_Pnt2d& P1, const gp_Pnt2d& P2, const int Index = 0);

  Standard_EXPORT int NbIntervals() const;

  Standard_EXPORT int NbLines() const;

  Standard_EXPORT const gp_Lin2d& Line(const int I) const;

  Standard_EXPORT Hatch_LineForm LineForm(const int I) const;

  bool IsXLine(const int I) const;

  bool IsYLine(const int I) const;

  Standard_EXPORT double Coordinate(const int I) const;

  Standard_EXPORT int NbIntervals(const int I) const;

  Standard_EXPORT double Start(const int I, const int J) const;

  Standard_EXPORT void StartIndex(const int I, const int J, int& Index, double& Par2) const;

  Standard_EXPORT double End(const int I, const int J) const;

  Standard_EXPORT void EndIndex(const int I, const int J, int& Index, double& Par2) const;

private:
  double                           myToler;
  NCollection_Sequence<Hatch_Line> myLines;
  bool                             myOrient;
};

inline void Hatch_Hatcher::Tolerance(const double Tol)
{
  myToler = Tol;
}

inline double Hatch_Hatcher::Tolerance() const
{
  return myToler;
}

inline bool Hatch_Hatcher::IsXLine(const int I) const
{
  return LineForm(I) == Hatch_XLINE;
}

inline bool Hatch_Hatcher::IsYLine(const int I) const
{
  return LineForm(I) == Hatch_YLINE;
}
