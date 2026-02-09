#include <Poly_Polygon3D.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Poly_Polygon3D, Standard_Transient)

Poly_Polygon3D::Poly_Polygon3D(const int theNbNodes, const bool theHasParams)
    : myDeflection(0.0),
      myNodes(1, theNbNodes)
{
  if (theHasParams)
  {
    myParameters = new NCollection_HArray1<double>(1, theNbNodes);
  }
}

Poly_Polygon3D::Poly_Polygon3D(const NCollection_Array1<gp_Pnt>& Nodes)
    : myDeflection(0.),
      myNodes(1, Nodes.Length())
{
  int i, j = 1;
  for (i = Nodes.Lower(); i <= Nodes.Upper(); i++)
    myNodes(j++) = Nodes(i);
}

Poly_Polygon3D::Poly_Polygon3D(const NCollection_Array1<gp_Pnt>& Nodes,
                               const NCollection_Array1<double>& P)
    : myDeflection(0.),
      myNodes(1, Nodes.Length())

{
  myParameters = new NCollection_HArray1<double>(1, P.Length());
  int i, j = 1;
  for (i = Nodes.Lower(); i <= Nodes.Upper(); i++)
  {
    myNodes(j) = Nodes(i);
    myParameters->SetValue(j, P(i));
    j++;
  }
}

occ::handle<Poly_Polygon3D> Poly_Polygon3D::Copy() const
{
  occ::handle<Poly_Polygon3D> aCopy;
  if (myParameters.IsNull())
    aCopy = new Poly_Polygon3D(myNodes);
  else
    aCopy = new Poly_Polygon3D(myNodes, myParameters->Array1());
  aCopy->Deflection(myDeflection);
  return aCopy;
}

void Poly_Polygon3D::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDeflection)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myNodes.Size())
  if (!myParameters.IsNull())
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myParameters->Size())
}
