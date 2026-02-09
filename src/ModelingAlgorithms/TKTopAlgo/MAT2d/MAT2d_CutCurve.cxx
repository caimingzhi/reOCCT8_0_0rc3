#include <Geom2d_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dLProp_CurAndInf2d.hpp>
#include <gp_Pnt2d.hpp>
#include <MAT2d_CutCurve.hpp>
#include <Precision.hpp>
#include <Standard_OutOfRange.hpp>
#include <NCollection_Sequence.hpp>

MAT2d_CutCurve::MAT2d_CutCurve() = default;

MAT2d_CutCurve::MAT2d_CutCurve(const occ::handle<Geom2d_Curve>& C)
{
  Perform(C);
}

void MAT2d_CutCurve::Perform(const occ::handle<Geom2d_Curve>& C)
{
  theCurves.Clear();

  Geom2dLProp_CurAndInf2d          Sommets;
  occ::handle<Geom2d_TrimmedCurve> TrimC;
  double                           UF, UL, UC;
  gp_Pnt2d                         PF, PL, PC;
  constexpr double                 PTol  = Precision::PConfusion() * 10;
  constexpr double                 Tol   = Precision::Confusion() * 10;
  bool                             YaCut = false;
  Sommets.Perform(C);

  if (Sommets.IsDone() && !Sommets.IsEmpty())
  {
    UF = C->FirstParameter();
    UL = C->LastParameter();
    PF = C->Value(UF);
    PL = C->Value(UL);

    for (int i = 1; i <= Sommets.NbPoints(); i++)
    {
      UC = Sommets.Parameter(i);

      PC = C->Value(UC);
      if (UC - UF > PTol && PC.Distance(PF) > Tol)
      {
        if (UL - UC < PTol || PL.Distance(PC) < Tol)
        {
          break;
        }
        TrimC = new Geom2d_TrimmedCurve(C, UF, UC);
        theCurves.Append(TrimC);
        UF    = UC;
        PF    = PC;
        YaCut = true;
      }
    }
    if (YaCut)
    {
      TrimC = new Geom2d_TrimmedCurve(C, UF, UL);
      theCurves.Append(TrimC);
    }
  }
}

bool MAT2d_CutCurve::UnModified() const
{
  return theCurves.IsEmpty();
}

int MAT2d_CutCurve::NbCurves() const
{
  if (UnModified())
  {
    throw Standard_OutOfRange();
  }
  return theCurves.Length();
}

occ::handle<Geom2d_TrimmedCurve> MAT2d_CutCurve::Value(const int Index) const
{
  if (UnModified())
  {
    throw Standard_OutOfRange();
  }
  if (Index < 1 || Index > theCurves.Length())
  {
    throw Standard_OutOfRange();
  }
  return occ::down_cast<Geom2d_TrimmedCurve>(theCurves.Value(Index));
}
