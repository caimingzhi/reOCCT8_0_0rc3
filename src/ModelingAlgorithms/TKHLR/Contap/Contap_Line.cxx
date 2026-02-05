#include <Adaptor2d_Curve2d.hpp>
#include <Contap_Line.hpp>
#include <Contap_Point.hpp>
#include <gp_Circ.hpp>
#include <gp_Lin.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <Standard_DomainError.hpp>

Contap_Line::Contap_Line()
{
  svtx  = new NCollection_HSequence<Contap_Point>();
  Trans = IntSurf_Undecided;
}

void Contap_Line::ResetSeqOfVertex()
{
  svtx = new NCollection_HSequence<Contap_Point>();
}

void Contap_Line::Add(const Contap_Point& P)
{
  int n = svtx->Length();
  if (n == 0)
  {
    svtx->Append(P);
  }
  else
  {
    double prm = P.ParameterOnLine();
    if (prm > svtx->Value(n).ParameterOnLine())
    {
      svtx->Append(P);
    }
    else
    {
      for (int i = n - 1; i > 0; i--)
      {
        if (prm > svtx->Value(i).ParameterOnLine())
        {
          svtx->InsertBefore(i + 1, P);
          return;
        }
      }
      svtx->Prepend(P);
    }
  }
}

void Contap_Line::Clear()
{
  if (!curv.IsNull())
    curv->Clear();
  svtx = new NCollection_HSequence<Contap_Point>();
  typL = Contap_Walking;
}

void Contap_Line::SetValue(const gp_Lin& L)
{
  pt   = L.Location();
  dir1 = L.Direction();
  typL = Contap_Lin;
}

void Contap_Line::SetValue(const gp_Circ& C)
{
  pt   = C.Location();
  dir1 = C.Position().Direction();
  dir2 = C.Position().XDirection();
  rad  = C.Radius();
  typL = Contap_Circle;
}

void Contap_Line::SetValue(const occ::handle<Adaptor2d_Curve2d>& A)
{
  thearc = A;
  typL   = Contap_Restriction;
}

void Contap_Line::SetLineOn2S(const occ::handle<IntSurf_LineOn2S>& L)
{
  curv = L;
  typL = Contap_Walking;
}

void Contap_Line::SetTransitionOnS(const IntSurf_TypeTrans T)
{
  Trans = T;
}

IntSurf_TypeTrans Contap_Line::TransitionOnS() const
{
  return (Trans);
}

const occ::handle<Adaptor2d_Curve2d>& Contap_Line::Arc() const
{
  if (typL != Contap_Restriction)
  {
    throw Standard_DomainError();
  }
  return thearc;
}
