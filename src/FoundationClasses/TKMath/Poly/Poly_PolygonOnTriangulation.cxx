#include <Poly_PolygonOnTriangulation.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Poly_PolygonOnTriangulation, Standard_Transient)

Poly_PolygonOnTriangulation::Poly_PolygonOnTriangulation(const int  theNbNodes,
                                                         const bool theHasParams)
    : myDeflection(0.0),
      myNodes(1, theNbNodes)
{
  if (theHasParams)
  {
    myParameters = new NCollection_HArray1<double>(1, theNbNodes);
  }
}

Poly_PolygonOnTriangulation::Poly_PolygonOnTriangulation(const NCollection_Array1<int>& Nodes)
    : myDeflection(0.0),
      myNodes(1, Nodes.Length())
{
  myNodes = Nodes;
}

Poly_PolygonOnTriangulation::Poly_PolygonOnTriangulation(
  const NCollection_Array1<int>&    Nodes,
  const NCollection_Array1<double>& Parameters)
    : myDeflection(0.0),
      myNodes(1, Nodes.Length())
{
  myNodes                      = Nodes;
  myParameters                 = new NCollection_HArray1<double>(1, Parameters.Length());
  myParameters->ChangeArray1() = Parameters;
}

occ::handle<Poly_PolygonOnTriangulation> Poly_PolygonOnTriangulation::Copy() const
{
  occ::handle<Poly_PolygonOnTriangulation> aCopy;
  if (myParameters.IsNull())
    aCopy = new Poly_PolygonOnTriangulation(myNodes);
  else
    aCopy = new Poly_PolygonOnTriangulation(myNodes, myParameters->Array1());
  aCopy->Deflection(myDeflection);
  return aCopy;
}

void Poly_PolygonOnTriangulation::SetParameters(
  const occ::handle<NCollection_HArray1<double>>& theParameters)
{
  if (!theParameters.IsNull()
      && (theParameters->Lower() != myNodes.Lower() || theParameters->Upper() != myNodes.Upper()))
  {
    throw Standard_OutOfRange("Poly_PolygonOnTriangulation::SetParameters() - invalid array size");
  }
  myParameters = theParameters;
}

void Poly_PolygonOnTriangulation::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDeflection)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myNodes.Size())
  if (!myParameters.IsNull())
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myParameters->Size())
}
