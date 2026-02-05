#include <Poly_Polygon2D.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Poly_Polygon2D, Standard_Transient)

//=================================================================================================

Poly_Polygon2D::Poly_Polygon2D(const int theNbNodes)
    : myDeflection(0.0),
      myNodes(1, theNbNodes)
{
}

//=================================================================================================

Poly_Polygon2D::Poly_Polygon2D(const NCollection_Array1<gp_Pnt2d>& Nodes)
    : myDeflection(0.),
      myNodes(1, Nodes.Length())
{
  int i, j = 1;
  for (i = Nodes.Lower(); i <= Nodes.Upper(); i++)
    myNodes(j++) = Nodes(i);
}

//=================================================================================================

void Poly_Polygon2D::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDeflection)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myNodes.Size())
}
