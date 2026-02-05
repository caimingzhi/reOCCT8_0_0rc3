#include <DrawTrSurf_Polygon3D.hpp>

#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <Draw_MarkerShape.hpp>
#include <Poly.hpp>
#include <Poly_Polygon3D.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawTrSurf_Polygon3D, Draw_Drawable3D)

//=================================================================================================

DrawTrSurf_Polygon3D::DrawTrSurf_Polygon3D(const occ::handle<Poly_Polygon3D>& P)
    : myPolygon3D(P),
      myNodes(false)
{
}

//=================================================================================================

void DrawTrSurf_Polygon3D::DrawOn(Draw_Display& dis) const
{
  dis.SetColor(Draw_jaune);

  const NCollection_Array1<gp_Pnt>& Points = myPolygon3D->Nodes();
  for (int i = Points.Lower(); i <= Points.Upper() - 1; i++)
  {
    dis.Draw(Points(i), Points(i + 1));
  }

  if (myNodes)
  {
    for (int i = Points.Lower(); i <= Points.Upper(); i++)
    {
      dis.DrawMarker(Points(i), Draw_X);
    }
  }
}

//=================================================================================================

occ::handle<Draw_Drawable3D> DrawTrSurf_Polygon3D::Copy() const
{
  return new DrawTrSurf_Polygon3D(myPolygon3D);
}

//=================================================================================================

void DrawTrSurf_Polygon3D::Dump(Standard_OStream& S) const
{
  Poly::Dump(myPolygon3D, S);
}

//=================================================================================================

void DrawTrSurf_Polygon3D::Save(Standard_OStream& theStream) const
{
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  std::ios::fmtflags aFlags = theStream.flags();
  theStream.setf(std::ios::scientific, std::ios::floatfield);
  theStream.precision(15);
#else
  long            aForm = theStream.setf(std::ios::scientific);
  std::streamsize aPrec = theStream.precision(15);
#endif
  Poly::Write(myPolygon3D, theStream);
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  theStream.setf(aFlags);
#else
  theStream.setf(aForm);
  theStream.precision(aPrec);
#endif
}

//=================================================================================================

occ::handle<Draw_Drawable3D> DrawTrSurf_Polygon3D::Restore(Standard_IStream& theStream)
{
  return new DrawTrSurf_Polygon3D(Poly::ReadPolygon3D(theStream));
}

//=================================================================================================

void DrawTrSurf_Polygon3D::Whatis(Draw_Interpretor& I) const
{
  I << "polygon3D";
}
