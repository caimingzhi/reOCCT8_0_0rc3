

#include <Poly_ArrayOfNodes.hpp>

Poly_ArrayOfNodes::Poly_ArrayOfNodes(const Poly_ArrayOfNodes& theOther)

  = default;

Poly_ArrayOfNodes::~Poly_ArrayOfNodes() = default;

Poly_ArrayOfNodes& Poly_ArrayOfNodes::Assign(const Poly_ArrayOfNodes& theOther)
{
  if (&theOther == this)
  {
    return *this;
  }

  if (myStride == theOther.myStride)
  {

    NCollection_AliasedArray::Assign(theOther);
    return *this;
  }

  if (mySize != theOther.mySize)
  {
    throw Standard_DimensionMismatch("Poly_ArrayOfNodes::Assign(), arrays have different sizes");
  }
  for (int anIter = 0; anIter < mySize; ++anIter)
  {
    const gp_Pnt aPnt = theOther.Value(anIter);
    SetValue(anIter, aPnt);
  }
  return *this;
}
