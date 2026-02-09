#include <DrawTrSurf_Triangulation.hpp>

#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <Poly.hpp>
#include <Poly_Connect.hpp>
#include <Poly_Triangle.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

#include <cstdio>

IMPLEMENT_STANDARD_RTTIEXT(DrawTrSurf_Triangulation, Draw_Drawable3D)

DrawTrSurf_Triangulation::DrawTrSurf_Triangulation(const occ::handle<Poly_Triangulation>& T)
    : myTriangulation(T),
      myNodes(false),
      myTriangles(false)
{

  Poly_Connect pc(T);

  int i, j, nFree, nInternal, nbTriangles = T->NbTriangles();
  int t[3];

  nFree = 0;
  for (i = 1; i <= nbTriangles; i++)
  {
    pc.Triangles(i, t[0], t[1], t[2]);
    for (j = 0; j < 3; j++)
      if (t[j] == 0)
        nFree++;
  }

  myFree      = new NCollection_HArray1<int>(1, 2 * nFree);
  nInternal   = (3 * nbTriangles - nFree) / 2;
  myInternals = new NCollection_HArray1<int>(1, 2 * nInternal);

  NCollection_Array1<int>& Free     = myFree->ChangeArray1();
  NCollection_Array1<int>& Internal = myInternals->ChangeArray1();

  int fr = 1, in = 1;
  int n[3];
  for (i = 1; i <= nbTriangles; i++)
  {
    pc.Triangles(i, t[0], t[1], t[2]);
    T->Triangle(i).Get(n[0], n[1], n[2]);
    for (j = 0; j < 3; j++)
    {
      int k = (j + 1) % 3;
      if (t[j] == 0)
      {
        Free(fr)     = n[j];
        Free(fr + 1) = n[k];
        fr += 2;
      }

      else if (i < t[j])
      {
        Internal(in)     = n[j];
        Internal(in + 1) = n[k];
        in += 2;
      }
    }
  }
}

void DrawTrSurf_Triangulation::DrawOn(Draw_Display& dis) const
{

  int i, n;

  dis.SetColor(Draw_rouge);
  const NCollection_Array1<int>& Free = myFree->Array1();
  n                                   = Free.Length() / 2;
  for (i = 1; i <= n; i++)
  {
    dis.Draw(myTriangulation->Node(Free[2 * i - 1]), myTriangulation->Node(Free[2 * i]));
  }

  dis.SetColor(Draw_bleu);
  const NCollection_Array1<int>& Internal = myInternals->Array1();
  n                                       = Internal.Length() / 2;
  for (i = 1; i <= n; i++)
  {
    dis.Draw(myTriangulation->Node(Internal[2 * i - 1]), myTriangulation->Node(Internal[2 * i]));
  }

  char text[50];
  if (myNodes)
  {
    dis.SetColor(Draw_jaune);
    n = myTriangulation->NbNodes();
    for (i = 1; i <= n; i++)
    {
      Sprintf(text, "%d", i);
      dis.DrawString(myTriangulation->Node(i), text);
    }
  }

  if (myTriangles)
  {
    dis.SetColor(Draw_vert);
    n = myTriangulation->NbTriangles();
    int t[3], j;
    for (i = 1; i <= n; i++)
    {
      myTriangulation->Triangle(i).Get(t[0], t[1], t[2]);
      gp_Pnt  P(0, 0, 0);
      gp_XYZ& bary = P.ChangeCoord();
      for (j = 0; j < 3; j++)
        bary.Add(myTriangulation->Node(t[j]).Coord());
      bary.Multiply(1. / 3.);

      Sprintf(text, "%d", i);
      dis.DrawString(P, text);
    }
  }
}

occ::handle<Draw_Drawable3D> DrawTrSurf_Triangulation::Copy() const
{
  return new DrawTrSurf_Triangulation(myTriangulation);
}

void DrawTrSurf_Triangulation::Dump(Standard_OStream& S) const
{
  Poly::Dump(myTriangulation, S);
}

void DrawTrSurf_Triangulation::Save(Standard_OStream& theStream) const
{
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  std::ios::fmtflags aFlags = theStream.flags();
  theStream.setf(std::ios::scientific, std::ios::floatfield);
  theStream.precision(15);
#else
  long            aForm = theStream.setf(std::ios::scientific);
  std::streamsize aPrec = theStream.precision(15);
#endif
  Poly::Write(myTriangulation, theStream);
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  theStream.setf(aFlags);
#else
  theStream.setf(aForm);
  theStream.precision(aPrec);
#endif
}

occ::handle<Draw_Drawable3D> DrawTrSurf_Triangulation::Restore(Standard_IStream& theStream)
{
  return new DrawTrSurf_Triangulation(Poly::ReadTriangulation(theStream));
}

void DrawTrSurf_Triangulation::Whatis(Draw_Interpretor& I) const
{
  I << "triangulation";
}
